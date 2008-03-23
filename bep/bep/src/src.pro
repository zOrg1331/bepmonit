SOURCES += bep.cpp \
           main.cpp \
 kns.cpp \
 akb.cpp \
 empty.cpp \
 key.cpp \
 load.cpp \
 acpower.cpp \
 ldefense.cpp \
 ilabel.cpp \
 bepcontrol.cpp \
 mybasewidgets.cpp \
 data.cpp \
 getdata.cpp \
 knscontrol.cpp \
 akbcontrol.cpp \
 accontrol.cpp \
 log.cpp \
 statdata.cpp \
 zchart.cpp \
 zframes.cpp \
 setdata.cpp \
 conf.cpp \
 loadcontrol.cpp \
 cooler.cpp \
 coolercontrol.cpp \
 arrow.cpp \
 network.cpp
HEADERS += bep.h \
 kns.h \
 akb.h \
 empty.h \
 key.h \
 load.h \
 acpower.h \
 ldefense.h \
 ilabel.h \
 bepcontrol.h \
 mybasewidgets.h \
 data.h \
 getdata.h \
 knscontrol.h \
 akbcontrol.h \
 accontrol.h \
 log.h \
 statdata.h \
 zchart.h \
 zframes.h \
 setdata.h \
 conf.h \
 loadcontrol.h \
 cooler.h \
 coolercontrol.h \
 arrow.h \
 network.h
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = ../bin/bep
RESOURCES = application.qrc
QT += network
LIBS += -lnetsnmp \
-lcrypto
