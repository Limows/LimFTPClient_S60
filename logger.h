/*
 * Logger.h
 *
 *  Created on: 01.09.2019
 *      Author: artem78
 *      Description: Simple module for writing log to file.
 *      
 *      Usage:
 *      First you need to create instance of CLogger. After that set this logger
 *      as default calling LoggerStatic::SetLogger() static method. Use LOG, DEBUG,
 *      INFO, WARNING or ERROR macros from any place of your code for write messages
 *      to the log. If no logger has been set up, nothing will happen. Prefer to use
 *      macroses instead of directly call LoggerStatic::WriteFormat() method.
 *      Preprocessor constant LOGGING_ENABLED globally enables or disables logging
 *      functionality at compile time. For turn on logging add:
 *      	#define LOGGING_ENABLED 1
 *
 */

#ifndef LOGGER_H_
#define LOGGER_H_

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <f32file.h>
#include <s32file.h>
//#include "LoggingDefs.h"


// Check that ENABLE_LOGGING is defined
#ifndef LOGGING_ENABLED
#warning LOGGING_ENABLED not defined! Set it to 0.
#define LOGGING_ENABLED 0
#endif


// ToDo: Write to log additinal info: __FILE__, __LINE__, etc...
// ToDo: Write 16bit descriptors
// ToDo: Allow to create logger by filename and file server
// ToDo: Add formatting of date and time in message (ex.: %date, %time, %datetime)
// ToDo: Allow to safe using of logger with threads (add mutex)

#if LOGGING_ENABLED
#define LOG(aMsg, anArgs...)		LoggerStatic::WriteFormat(CLogger::ELevelUnknown,	_L8(__PRETTY_FUNCTION__), aMsg, ##anArgs);
#define DEBUG(aMsg, anArgs...)		LoggerStatic::WriteFormat(CLogger::ELevelDebug,		_L8(__PRETTY_FUNCTION__), aMsg, ##anArgs);
#define INFO(aMsg, anArgs...)		LoggerStatic::WriteFormat(CLogger::ELevelInfo,		_L8(__PRETTY_FUNCTION__), aMsg, ##anArgs);
#define WARNING(aMsg, anArgs...)	LoggerStatic::WriteFormat(CLogger::ELevelWarning,	_L8(__PRETTY_FUNCTION__), aMsg, ##anArgs);
#define ERROR(aMsg, anArgs...)		LoggerStatic::WriteFormat(CLogger::ELevelError,		_L8(__PRETTY_FUNCTION__), aMsg, ##anArgs);
// We can`t use _L16(__PRETTY_FUNCTION__), only 8bit - https://www.cyberforum.ru/cpp-beginners/thread2503039.html
// https://ru.stackoverflow.com/questions/1026888/%d0%a1%d1%83%d1%89%d0%b5%d1%81%d1%82%d0%b2%d1%83%d0%b5%d1%82-%d0%bb%d0%b8-%d0%b2-c-%d0%bc%d0%b0%d0%ba%d1%80%d0%be%d1%81-%d1%81-%d0%b8%d0%bc%d0%b5%d0%bd%d0%b5%d0%bc-%d0%ba%d0%bb%d0%b0%d1%81%d1%81%d0%b0?noredirect=1#comment1747251_1026888

/*
 * Main class for logging
 */
class CLogger : public CBase
	{
public:
	enum TLoggingLevel
		{
		ELevelUnknown	= 0x00000000, // For compatibility with older (uncategorized) code
		ELevelDebug		= 0x00000001,
		ELevelInfo		= 0x00000002,
		//ELevelNotice
		ELevelWarning	= 0x00000004,
		ELevelError		= 0x00000008,
		//ELevelFatalError/ELevelCritical
		
		ELevelAll		= /*-1*/ ELevelUnknown | ELevelDebug |
					ELevelInfo | ELevelWarning | ELevelError,		
		};
	
	enum TOutputEncoding
		{
		EASCII,
		EUnicode, // USC2 Little Endian (UTF-16)
		EUtf8
		};

	~CLogger();
	static CLogger* NewL(RFile &aFile, TUint aLoggingLevels = ELevelAll,
			TOutputEncoding anOutputEncoding = EASCII, TBool anAutoFlush = EFalse);
	static CLogger* NewLC(RFile &aFile, TUint aLoggingLevels = ELevelAll,
			TOutputEncoding anOutputEncoding = EASCII, TBool anAutoFlush = EFalse);

private:
	void WriteL(const TDesC16 &aModule, const TDesC16 &aDes, TLoggingLevel aLoggingLevel = ELevelUnknown);
	void WriteFormatL(const TDesC16 &aModule, TRefByValue<const TDesC16> aFmt, ...);
	void WriteFormatListL(const TDesC16 &aModule, const TDesC16 &aFmt, VA_LIST aList, TBool anIsDes16, TLoggingLevel aLoggingLevel = ELevelUnknown);
	//static void WriteEmptyLine();
	void WriteToFileL(const TDesC16 &aDes);
	
private:
	CLogger(RFile &aFile, TUint aLoggingLevels, TOutputEncoding anOutputEncoding,
			TBool anAutoFlush);
	void ConstructL();
	
	RFileBuf iFileBuf;
	TUint iLoggingLevels;
	TOutputEncoding iOutputEncoding;
	TBool iAutoFlush; // If set to ETrue, make flush after each line 
	
	friend class LoggerStatic;
	};


/*
 * Static class for providing access to logger from everywhere. Set current logger
 * with LoggerStatic::SetLogger() method and than every call to logging macroses
 * will be send to this logger. When logger destructor runs, it automatically disables
 * itself in LoggerStatic and future calls to LOG, DEBUG, INFO, ERROR or WARNING
 * will cause no action.
 */
class LoggerStatic
	{
private:
	static CLogger* iLogger;
public:
	static void SetLogger(CLogger* aLogger);
	static void WriteFormat/*WriteLog*/(CLogger::TLoggingLevel aLoggingLevel, const TDesC8 &aModule, TRefByValue<const TDesC16> aFmt, ...);
	static void WriteFormat/*WriteLog*/(CLogger::TLoggingLevel aLoggingLevel, const TDesC8 &aModule, TRefByValue<const TDesC8> aFmt, ...);
	
	friend class CLogger;
	};


#else
#define LOG(aMsg, anArgs...)
#define DEBUG(aMsg, anArgs...)
#define INFO(aMsg, anArgs...)
#define WARNING(aMsg, anArgs...)
#define ERROR(aMsg, anArgs...)
#endif

#endif /* LOGGER_H_ */
