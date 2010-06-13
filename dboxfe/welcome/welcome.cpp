/*
 *
 * Copyright (C) 2004 - 2010 Alexander Saal.
 * All rights reserved.
 * Contact: Alexander Saal (alex.saal@gmx.de)
 *
 * This file is part of DBoxFE.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include "dboxfe.h"
#include "welcome.h"
#include "global.h"

using namespace asaal;

Welcome::Welcome( QWidget *parent )
: QWidget( parent ) {

  setupUi(this);

  QString headerText = 
  "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
  "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
  "p, li { white-space: pre-wrap; }"
  "</style></head><body style=\" font-family:'Lucida Grande'; font-size:13pt; font-weight:400; font-style:normal;\">"
  "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600;\">Welcome to DBoxFE</span></p>"
  "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-style:italic;\">DOSBox Front End for Linux, Mac and Windows</span></p>"
  "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:11pt; font-style:italic;\"></p>"
  "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt; font-style:italic;\">Version: " + QString(DBoxFEVersion) + "</span></p></body></html>";

  mLabelHeader->setText(headerText);
}

void Welcome::setMainWindow( QMainWindow *mainWindow ) {

  DBoxFE *dboxfe = qobject_cast<DBoxFE*>(mainWindow);
  if( dboxfe ) {

    connect(mCmdButtonNewProfile, SIGNAL(clicked()), dboxfe, SLOT(slotNewProfile()));
    connect(mCmdButtonShowProfiles, SIGNAL(clicked()), dboxfe, SLOT(slotShowProfiles()));
    connect(mCmdButtonPreferences, SIGNAL(clicked()), dboxfe, SLOT(slotPreferences()));
    connect(mCmdButtonDOSBoxGames, SIGNAL(clicked()), dboxfe, SLOT(slotDOSBoxGames()));
    connect(mCmdButtonDOSBoxDatabaseUpdate, SIGNAL(clicked()), dboxfe, SLOT(slotDOSBoxDatabaseUpdate()));
  }
}
