#include "paramshelper.h"

ParamsHelper::ParamsHelper()
{

}

QUrl ParamsHelper::ServerURI = QUrl("ftp://anon@limowski.xyz:2121");
QUrl ParamsHelper::SystemURI = QUrl();
QUrl ParamsHelper::CurrentURI = QUrl();
QUrl ParamsHelper::AppURI = QUrl();
QList<QString> ParamsHelper::AppsList = QList<QString>();
QSysInfo::S60Version ParamsHelper::OSVersion = QSysInfo::S60Version();
bool ParamsHelper::IsAutoInstall = false;
bool ParamsHelper::IsOverwrite = false;
bool ParamsHelper::IsRmPackage = false;
QString ParamsHelper::DownloadPath = "";
QString ParamsHelper::InstallPath = "C:/";
ulong ParamsHelper::TempSize = 0;
