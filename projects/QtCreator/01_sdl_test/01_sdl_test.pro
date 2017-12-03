#--------------------------------------------------------------------
# global var
#--------------------------------------------------------------------

win32:SDL2_DIR = ../../../demos/thirdparty/Windows/SDL2-2.0.7
win32:SPARK_DIR = ../../../spark
win32:SPARK_GL_DIR = ../../../rendering
win32:GLEW_DIR = ../../../thirdparty/glew-2.1.0

#--------------------------------------------------------------------
# target
#--------------------------------------------------------------------

#TEMPLATE = app

#CONFIG -= qt
#CONFIG += console
##CONFIG += windows
#CONFIG += c++11
#CONFIG -= debug_and_release
#CONFIG -= debug_and_release_target


TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG -= debug_and_release
CONFIG -= debug_and_release_target



#--------------------------------------------------------------------
# output directory
#--------------------------------------------------------------------

CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../../../demos/bin
} else {
    DESTDIR = $$PWD/../../../demos/bin
}
QMAKE_CLEAN += $$DESTDIR/$$TARGET

#--------------------------------------------------------------------
# compilation flags
#--------------------------------------------------------------------

unix:!macx: QMAKE_CXXFLAGS_WARN_ON -= -Wall
unix:!macx: QMAKE_CFLAGS_WARN_ON -= -Wall
unix:!macx: QMAKE_CXXFLAGS += -Wall
unix:!macx: QMAKE_CXXFLAGS += -Wno-comment
unix:!macx: QMAKE_CXXFLAGS += -Wno-ignored-qualifiers
unix:!macx: QMAKE_CXXFLAGS += -Wno-unused-parameter
unix:!macx: QMAKE_CXXFLAGS += -std=c++11
unix:!macx: QMAKE_CXXFLAGS += -fpermissive
unix:!macx: QMAKE_CXXFLAGS += -Wno-unused-function
unix:!macx: QMAKE_CXXFLAGS += -Wno-reorder
#unix:!macx: QMAKE_CXXFLAGS += -Wfatal-errors
#unix:!macx: QMAKE_CXXFLAGS += -m32


CONFIG(debug,debug|release) {
    QMAKE_CXXFLAGS_RELEASE += -O0
} else {
    unix:!macx: QMAKE_CXXFLAGS += -Wno-strict-aliasing
    win32:QMAKE_CXXFLAGS_RELEASE -= -Zc:strictStrings
    QMAKE_CXXFLAGS_RELEASE += -O3
}

#--------------------------------------------------------------------
# pre-processor definitions
#--------------------------------------------------------------------

CONFIG(debug,debug|release) {
    #debug
    DEFINES +=  \
        SPK_GL_NO_EXT

} else {
    # release
    DEFINES +=  \
}


#--------------------------------------------------------------------
# REQUIRED libs
# sudo apt-get install libfreetype6-dev libglew-dev libsdl2-dev libftgl-dev
#--------------------------------------------------------------------


#--------------------------------------------------------------------
# libraries includes
#--------------------------------------------------------------------

INCLUDEPATH += $${SDL2_DIR}/include
INCLUDEPATH += $${SPARK_DIR}/include

INCLUDEPATH += $${GLEW_DIR}/include
INCLUDEPATH += $${SPARK_GL_DIR}
#INCLUDEPATH += /usr/include/freetype2




#--------------------------------------------------------------------
# libraries link
#--------------------------------------------------------------------

LIBS += -L$${DESTDIR}   -lSpark
LIBS += -L$${DESTDIR}   -lSpark_GL

win32: LIBS += -L$${SDL2_DIR}/lib/x64   -lSDL2
win32: LIBS += -L$${SDL2_DIR}/lib/x64   -lSDL2main

unix:!macx: LIBS += -lGL -lGLU -lftgl -lfreetype -lGLEW -lSDL2

win32:LIBS +=  msvcrtd.lib kernel32.lib user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib \
                ole32.lib oleaut32.lib uuid.lib imm32.lib winmm.lib wsock32.lib opengl32.lib glu32.lib version.lib


#--------------------------------------------------------------------
# project files
#--------------------------------------------------------------------

HEADERS += \


SOURCES += \
    ../../../thirdparty/glew-2.1.0/src/glew.c \
    ../../../demos/src/01_sdl_test/BasicDemo.cpp

