#ifndef IOHELPER_H
#define IOHELPER_H

#include <QString>

class IOHelper
{
public:
    IOHelper();

    static void LoadParameters();

    static QString ExtractToDirectory(QString CompressedFilePath, QString ExtractedFilePath);

    static void CleanBuffer();

    static void SaveParameters();

    static void RemoveParameters();

private:
    static QString GetConfigPath();
};

#endif // IOHELPER_H
