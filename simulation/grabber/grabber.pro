HEADERS       = glwidget.h \
                mainwindow.h \
    termioswrapper.h
SOURCES       = glwidget.cpp \
                main.cpp \
                mainwindow.cpp \
    termioswrapper.cpp
QT           += opengl widgets

QMAKE_CXXFLAGS += -std=c++11

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/grabber
INSTALLS += target

contains(QT_CONFIG, opengles.) {
    contains(QT_CONFIG, angle): \
        warning("Qt was built with ANGLE, which provides only OpenGL ES 2.0 on top of DirectX 9.0c")
    error("This example requires Qt to be configured with -opengl desktop")
}
