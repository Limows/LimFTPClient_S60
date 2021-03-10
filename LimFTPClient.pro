# Add files and directories to ship with the application 
# by adapting the examples below.
# file1.source = myfile
# dir1.source = mydir
DEPLOYMENTFOLDERS = # file1 dir1

symbian:TARGET.UID3 = 0xEE3EB787

# Smart Installer package's UID
# This UID is from the protected range 
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the
# MOBILITY variable.
#CONFIG += mobility
#MOBILITY +=

symbian {
    TARGET.CAPABILITY += \
        NetworkServices \
        TrustedUI

    RC_FILE += \
        Resources.rc

    QT += network \
        core \
        gui

    VERSION = "0.5.3"

    DEFINES += APP_VERSION=\"\\\"$${VERSION}-debug\\\"\"

    VENDOR = "LimSoft"

    DEFINES += APP_VENDOR=\"\\\"$${VENDOR}\\\"\"

    vendorinfo = "%{\"$$VENDOR\"}" ":\"$$VENDOR\""

    DATE = $$system(date /t)

    DEFINES += BUILDDATE=\"\\\"$${DATE}\\\"\"

    LimFTPClient_template.pkg_prerules = vendorinfo
    DEPLOYMENT += LimFTPClient_template

    INCLUDEPATH += "lib/quazip/include"

    LIBS += \
        -lezip \
        -lquazip \
        -lswinstcli \
        -lcommdb \
        -lapparc \
        -lefsrv \
        -lapgrfx \
        -lefsrv \
        -lestor \
        -lcharconv \
}

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    paramsdialog.cpp \
    aboutdialog.cpp \
    paramshelper.cpp \
    nethelper.cpp \
    iohelper.cpp \
    systemhelper.cpp \
    appdialog.cpp \
    installedform.cpp \
    logger.cpp

HEADERS += \
    mainwindow.h \
    paramsdialog.h \
    aboutdialog.h \
    paramshelper.h \
    nethelper.h \
    iohelper.h \
    systemhelper.h \
    appdialog.h \
    installedform.h \
    logger.h

FORMS += \
    mainwindow.ui \
    paramsdialog.ui \
    aboutdialog.ui \
    appdialog.ui \
    installedform.ui

RESOURCES += \
    Resources.rc

DEFINES += LOGGING_ENABLED=1

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    LimFTPClient.svg
