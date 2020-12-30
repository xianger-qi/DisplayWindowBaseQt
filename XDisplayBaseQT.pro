#-------------------------------------------------
#
# Project created by QtCreator 2020-06-03T14:11:40
#
#-------------------------------------------------

QT       += widgets
TARGET = XDisplayBaseQT
IMPORT_H_FILE = xdisplaybaseqt.h

CONFIG(debug, debug|release){
TARGET = $$join(TARGET,,,D)
DESTDIR += $$PWD/debug

    COPY_LIB = $$PWD/../../SPCI-PUBLIC/lib/algorithm/debug/lib
    COPY_DLL = $$PWD/../../SPCI-PUBLIC/lib/algorithm/debug/dll
    COPY_PDB = $$PWD/../../SPCI-PUBLIC/lib/algorithm/debug/pdb
    COPY_H   = $$PWD/../../SPCI-PUBLIC/lib/algorithm/include



    win32:{
        COPY_CMD = copy $$DESTDIR/*.lib $$COPY_LIB \
                    && copy $$DESTDIR/*.dll $$COPY_DLL \
                    && copy $$DESTDIR/$$join(TARGET,,,.pdb) $$COPY_PDB \
                    && copy $$PWD/IMPORT_H_FILE $$COPY_H
        QMAKE_POST_LINK = $$replace(COPY_CMD, /, \\)
    }
}else{
CONFIG += force_debug_info
DESTDIR += $$PWD/release

    COPY_LIB = $$PWD/../../SPCI-PUBLIC/lib/algorithm/release/lib
    COPY_DLL = $$PWD/../../SPCI-PUBLIC/lib/algorithm/release/dll
    COPY_PDB = $$PWD/../../SPCI-PUBLIC/lib/algorithm/release/pdb
    COPY_H   = $$PWD/../../SPCI-PUBLIC/lib/algorithm/include

    win32:{
        COPY_CMD = copy $$DESTDIR/*.lib $$COPY_LIB \
                    && copy $$DESTDIR/*.dll $$COPY_DLL \
                    && copy $$DESTDIR/$$join(TARGET,,,.pdb) $$COPY_PDB \
                    && copy $$PWD/IMPORT_H_FILE $$COPY_H
        QMAKE_POST_LINK = $$replace(COPY_CMD, /, \\)
    }
}

TEMPLATE = lib

DEFINES += XDISPLAYBASEQT_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    xdisplaybaseqt.cpp \
    xdisplaybaseqtimpl.cpp \
    xinfolabel.cpp

HEADERS += \
    xdisplaybaseqt.h \
    xdisplaybaseqtimpl.h \
    xinfolabel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    xdisplaybaseqt.ui \
    xdisplaybaseqtimpl.ui \
    xinfolabel.ui

#依赖的头文件路径
INCLUDEPATH += $$PWD/../../SPCI-PUBLIC/lib/algorithm/include
INCLUDEPATH += $$PWD/../../SPCI-PUBLIC/lib/system/include
INCLUDEPATH += $$PWD/../../SPCI-PUBLIC/lib/extern/include/halcon
INCLUDEPATH += $$PWD/../../SPCI-PUBLIC/lib/extern/include/opencv2
INCLUDEPATH += $$PWD/../../SPCI-PUBLIC/lib/extern/include


#依赖的库路径
CONFIG(debug, debug|release){
LIBS += $$PWD/../../SPCI-PUBLIC/lib/extern/lib/halcon/halconcpp.lib
LIBS += $$PWD/../../SPCI-PUBLIC/lib/extern/lib/opencv/opencv_worldd.lib
}else{
LIBS += $$PWD/../../SPCI-PUBLIC/lib/extern/lib/halcon/halconcpp.lib
LIBS += $$PWD/../../SPCI-PUBLIC/lib/extern/lib/opencv/opencv_world.lib
}

