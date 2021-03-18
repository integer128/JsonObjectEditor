QT += quick

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug | release) {
    DESTDIR = $$PWD/build/debug
    OBJECTS_DIR = debug
    MOC_DIR = debug
    RCC_DIR = debug
} else {
    DESTDIR = $$PWD/build/release
    OBJECTS_DIR = release
    MOC_DIR = release
    RCC_DIR = release
}
INCLUDEPATH += src/ \
               qml/

SOURCES += \
        src/jsoneditormodel.cpp \
        src/jsonworker.cpp \
        src/main.cpp \
        src/textfielddoublevalidator.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/jsoneditormodel.h \
    src/jsonworker.h \
    src/textfielddoublevalidator.h
