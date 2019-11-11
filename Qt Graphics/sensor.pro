QMAKE_CXX = /usr/bin/clang++-3.8

CONFIG += c++14

QT += core widgets

ALEPH = /home/luis/Aleph-w

INCLUDEPATH += $${ALEPH}

LIBS += -L $${ALEPH} -lAleph -lgsl -lgslcblas -lm -lX11


HEADERS += \
  manual_panel.h \
  auto_panel.h \
  player.h \
  object.h \
  menu.h \


SOURCES += \
  main.cpp \
  manual_panel.cpp \
  auto_panel.cpp \
  player.cpp \
  object.cpp \
  menu.cpp \



RESOURCES += \
    sprites.qrc
