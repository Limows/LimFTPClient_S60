/*
 * Logger.cpp
 *
 *  Created on: 01.09.2019
 *      Author: artem78
 */

#include "logger.h"
#include <utf.h>

#if LOGGING_ENABLED

_LIT16(KLineBreak, "\r\n");
_LIT16(KTab, "\t");


/* CLogger */

CLogger::CLogger(RFile &aFile, TUint aLoggingLevels,
		TOutputEncoding anOutputEncoding, TBool anAutoFlush)
		: iLoggingLevels(aLoggingLevels),
		  iOutputEncoding(anOutputEncoding),
		  iAutoFlush(anAutoFlush)
	{
	// Leave iFileBuf buffer size as default (4Kb)
	iFileBuf.Attach(aFile, 0);
	}

CLogger::~CLogger()
	{
	iFileBuf.Synch/*L*/();
	iFileBuf.Close();
	
	if (this == LoggerStatic::iLogger)
		LoggerStatic::SetLogger(NULL);
	}

CLogger* CLogger::NewLC(RFile &aFile, TUint aLoggingLevels,
		TOutputEncoding anOutputEncoding, TBool anAutoFlush)
	{
	CLogger* self = new (ELeave) CLogger(aFile, aLoggingLevels, anOutputEncoding,
			anAutoFlush);
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}

CLogger* CLogger::NewL(RFile &aFile, TUint aLoggingLevels,
		TOutputEncoding anOutputEncoding, TBool anAutoFlush)
	{
	CLogger* self = CLogger::NewLC(aFile, aLoggingLevels, anOutputEncoding, anAutoFlush);
	CleanupStack::Pop(); // self;
	return self;
	}

void CLogger::ConstructL()
	{
	}

void CLogger::WriteL(const TDesC16 &aModule, const TDesC16 &aDes, TLoggingLevel aLoggingLevel)
	{
	// Check reporting level
	if (aLoggingLevel != ELevelUnknown && !(aLoggingLevel & iLoggingLevels))
		return;
	
	// Strings
	_LIT16(KTimeFormat, "%H:%T:%S.%*C3");
	_LIT16(KOpeningBracket, "(");
	_LIT16(KClosingBracket, ")");
	_LIT16(KOpeningSquareBracket, "[");
	_LIT16(KClosingSquareBracket, "]");
	_LIT16(KThreeSpaces, "   ");
	
	_LIT16(KDebugText,	"Debug");
	_LIT16(KInfoText,	"Info");
	_LIT16(KWarningText,	"Warning");
	_LIT16(KErrorText,	"Error");
	
	// Print current time
	TBuf16<20> timeBuff;
	TTime time;
	time.HomeTime();
	time.FormatL(timeBuff, KTimeFormat);
	WriteToFileL(timeBuff);
	
	// Print message level
	if (aLoggingLevel != ELevelUnknown)
		{
		WriteToFileL(KTab);
		WriteToFileL(KOpeningBracket);
		
		if (aLoggingLevel & ELevelDebug)
			WriteToFileL(KDebugText);
		else if (aLoggingLevel & ELevelInfo)
			WriteToFileL(KInfoText);
		else if (aLoggingLevel & ELevelWarning)
			WriteToFileL(KWarningText);
		else if (aLoggingLevel & ELevelError)
			WriteToFileL(KErrorText);
		
		WriteToFileL(KClosingBracket);
		}

	// Print module/class/function name
	WriteToFileL(KTab);
	WriteToFileL(KOpeningSquareBracket);
	WriteToFileL(aModule);
	WriteToFileL(KClosingSquareBracket);
	WriteToFileL(KThreeSpaces);
	
	// Print message
	WriteToFileL(aDes);
	WriteToFileL(KLineBreak);
	
	if (iAutoFlush)
		iFileBuf.SynchL();
	}

void CLogger::WriteFormatL(const TDesC16 &aModule, TRefByValue<const TDesC16> aFmt, ...)
	{
	VA_LIST list;
	VA_START(list, aFmt);
	WriteFormatListL(aModule, aFmt, list, ETrue);
	// VA_END(list); // As I understand it, this is not necessary
	}

void CLogger::WriteFormatListL(const TDesC16 &aModule, const TDesC16 &aFmt, VA_LIST aList, TBool anIsDes16, TLoggingLevel aLoggingLevel)
	{
	const TInt KDefaultBufferSize = 4 * KKilo; // 4096 chars
	
	RBuf16 buff;
	buff.CreateL(KDefaultBufferSize);
	buff.CleanupClosePushL();
	
	if (anIsDes16)
		{ // 16 bit
		buff.FormatList(aFmt, aList);
		}
	else
		{ // 8 bit
		RBuf8 buff8;
		TInt r = buff8.Create(KDefaultBufferSize);
		if (r == KErrNone)
			{
			RBuf8 fmt8;
			r = fmt8.Create(aFmt.Length());
			if (r == KErrNone)
				{
				fmt8.Copy(aFmt);
				buff8.FormatList(fmt8, aList);
				fmt8.Close();
				}
		
			buff.Copy(buff8);
			buff8.Close();
			}
		}
	
	WriteL(aModule, buff, aLoggingLevel);
	
	CleanupStack::PopAndDestroy(&buff);
	}

//void CLogger::WriteEmptyLine()
//	{
//	iFile.WriteL(KLineBreak);
//	}

void CLogger::WriteToFileL(const TDesC16 &aDes)
	{
	//__ASSERT_ALWAYS(aDes.Length(), return);
	if (!aDes.Length())
		return;
	
	RBuf8 buff8;
	TRequestStatus stat;

	switch (iOutputEncoding)
		{
		case EASCII:
			{
			buff8.CreateL(aDes.Length());
			buff8.CleanupClosePushL();
			buff8.Copy(aDes);
			}
		break;

		case EUnicode:
			{
			TPtrC8 writeBuf((const TUint8*)aDes.Ptr(),aDes.Size());
			buff8.CreateL(writeBuf.Length());
			buff8.CleanupClosePushL();
			buff8.Copy(writeBuf);
			}
		break;
		
		case EUtf8:
			{
			buff8.CreateL(aDes.Size()); // Not length! Max utf8 string size.
			buff8.CleanupClosePushL();
			CnvUtfConverter::ConvertFromUnicodeToUtf8(buff8, aDes);
			}
		break;
		
		default:
		break;
		}
	
	iFileBuf.WriteL(buff8, stat);
	User::WaitForRequest(stat);
	//iFileBuff.Synch/*L*/();
	
	CleanupStack::PopAndDestroy(&buff8);
	}


/* LoggerStatic */

CLogger* LoggerStatic::iLogger = NULL;

void LoggerStatic::SetLogger(CLogger* aLogger)
	{
	iLogger = aLogger;
	}

void LoggerStatic::WriteFormat(CLogger::TLoggingLevel aLoggingLevel,
		const TDesC8 &aModule, TRefByValue<const TDesC16> aFmt, ...)
	{
	// Deny write to not configured logger
	if (!iLogger)
		return;
	
	RBuf16 module16;
	TInt r = module16.Create(aModule.Length());
	// Pushing to cleanup stack not needed
	if (r != KErrNone)
		return;
	module16.Copy(aModule);
	
	VA_LIST list;
	VA_START(list, aFmt);
	TRAP_IGNORE(iLogger->WriteFormatListL(module16, aFmt, list, ETrue, aLoggingLevel));
	VA_END(list);
	
	module16.Close();
	}

void LoggerStatic::WriteFormat(CLogger::TLoggingLevel aLoggingLevel,
		const TDesC8 &aModule, TRefByValue<const TDesC8> aFmt, ...)
	{
	// Deny write to not configured logger
	if (!iLogger)
		return;
	
	RBuf16 module16;
	TInt r = module16.Create(aModule.Length());
	// Pushing to cleanup stack not needed
	if (r != KErrNone)
		return;
	module16.Copy(aModule);
	
	const TDesC8& fmt8 = aFmt;
	RBuf16 fmt16;
	r = fmt16.Create(fmt8.Length());
	if (r == KErrNone)
		{
		fmt16.Copy(fmt8);
		VA_LIST list;
		VA_START(list, aFmt);
		//WriteFormat(aLoggingLevel, aModule, fmt16, list);
		TRAP_IGNORE(iLogger->WriteFormatListL(module16, fmt16, list, EFalse, aLoggingLevel));
		VA_END(list);
		fmt16.Close();
		}
	
	module16.Close();
	}

#endif
