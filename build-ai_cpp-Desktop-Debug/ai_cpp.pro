
CONFIG -= qt

TEMPLATE = lib
DEFINES += AI_CPP_LIBRARY

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ai_cpp.cpp

HEADERS += \
    ai_cpp_global.h \
    ai_cpp.h

LIBS+= -L/home/user/Desktop/AI/fann/src -lgmock -lgmock_main -lgtest -lgtest_main -lfann -ldoublefann -lfloatfann -lfixedfann

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

# this copies the configuration files etc to the build direcory. So user has only to edit the source directory.
copydata.commands = $(COPY_DIR) $$PWD/* $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata
