SOURCES += main.cpp \
 beptest.cpp \
 data.cpp \
 getdata.cpp \
 setdata.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = ../bin/beptest

QT += gui network
HEADERS += beptest.h \
 data.h \
 getdata.h \
 setdata.h

