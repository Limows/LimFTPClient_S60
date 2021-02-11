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

# Allow network access on Symbian
symbian {
    TARGET.CAPABILITY += NetworkServices

    RC_FILE += \
        Resources.rc

    VERSION = 0.1.2

    vendorinfo = "%{\"LimSoft\"}" ":\"LimSoft\""

    LimFTPClient_template.pkg_prerules = vendorinfo
    DEPLOYMENT += LimFTPClient_template

    DEPLOYMENT.language = "&RU"
}

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the 
# MOBILITY variable. 
# CONFIG += mobility
# MOBILITY +=

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    paramsdialog.cpp \
    aboutdialog.cpp \
    paramshelper.cpp \
    nethelper.cpp \
    iohelper.cpp \
    systemhelper.cpp

HEADERS += \
    mainwindow.h \
    paramsdialog.h \
    aboutdialog.h \
    paramshelper.h \
    nethelper.h \
    iohelper.h \
    systemhelper.h

FORMS += \
    mainwindow.ui \
    paramsdialog.ui \
    aboutdialog.ui

RESOURCES += \
    Resources.rc

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    LimFTPClient.svg
