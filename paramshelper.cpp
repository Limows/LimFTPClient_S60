#include "paramshelper.h"

ParamsHelper::ParamsHelper()
{

}

QUrl ParamsHelper::ServerURI = QUrl("ftp://anon@limowski.xyz:2121");
QUrl ParamsHelper::SystemURI = QUrl();
QUrl ParamsHelper::CurrentURI = QUrl();
QUrl ParamsHelper::AppURI = QUrl();
QList<QString> ParamsHelper::AppsList = QList<QString>();
QSysInfo::SymbianVersion ParamsHelper::OSVersion = QSysInfo::SV_Unknown;
bool ParamsHelper::IsAutoInstall = false;
bool ParamsHelper::IsOverwrite = false;
bool ParamsHelper::IsRmPackage = false;
QString ParamsHelper::DownloadPath = QString();
QString ParamsHelper::TempPath = QString();
QString ParamsHelper::ConfigPath = QString();
QString ParamsHelper::InstallPath = "C:/";
ulong ParamsHelper::TempSize = 0;

double ParamsHelper::BytesToMegs(ulong Bytes)
{
    return ((double)Bytes / 1024 / 1024);
}

ulong ParamsHelper::MegsToBytes(double Megs)
{
    return (ulong)(Megs * 1024 * 1024);
}
