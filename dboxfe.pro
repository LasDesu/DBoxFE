#/*
# *
# * Copyright (C) 2004 - 2010 Alexander Saal.
# * All rights reserved.
# * Contact: Alexander Saal (alex.saal@gmx.de)
# *
# * This file is part of DBoxFE.
# *
# * This program is free software; you can redistribute it and/or modify
# * it under the terms of the GNU General Public License as published by
# * the Free Software Foundation; either version 3 of the License, or (at
# * your option) any later version.
# *
# * This program is distributed in the hope that it will be useful, but
# * WITHOUT ANY WARRANTY; without even the implied warranty of
# * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# * GNU General Public License for more details.
# *
# * You should have received a copy of the GNU General Public License
# * along with this program; if not, write to the Free Software Foundation,
# * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
# *
# */

include(dboxfe/dboxfe.pri)

# Qt 4 Settings
TEMPLATE = app
DESTDIR	= build/bin

RESOURCES += resource/dboxfe.qrc
CONFIG += qt thread warn_on
QT += network sql xml

TARGET = DBoxFE
RCC_DIR = build/$${TARGET}/rcc
MOC_DIR += build/$${TARGET}/moc
OBJECTS_DIR += build/$${TARGET}/obj
UI_DIR += build/$${TARGET}/ui

# Config settings
CONFIG(debug, debug|release) {

  DEFINES += DEBUG

} else {

  DEFINES -= DEBUG

  mac {
    QMAKE_POST_LINK = strip -s build/bin/$${TARGET}.app/Contents/MacOS/$${TARGET}
  }
  unix:!mac {
    QMAKE_POST_LINK = strip -s build/bin/$${TARGET}
  }
}

# Windows settings
win32 {
  CONFIG += embed_manifest_dll
  CONFIG += embed_manifest_exe
  CONFIG += debug_and_release build_all
  RC_FILE = resource/dboxfe.rc
  CONFIG -= console
  CONFIG -= flat
}

# Unix settings
unix:!mac {
  CONFIG += debug
}

# Mac settings
mac {
  contains(QT_VERSION, ^4\.[0-6]\..*) {

    QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.6.sdk
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.6
    CONFIG(x86_64) {
      CONFIG += x86_64
    }
    else {
      CONFIG += x86
    }
  }
  else {
    contains(QT_VERSION, ^4\.[0-5]\..*) {
      error("Can't build $${TARGET} with Qt version $${QT_VERSION}.")
    }
  }
}
