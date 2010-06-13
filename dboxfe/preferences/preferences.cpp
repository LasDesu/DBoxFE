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

#include "global.h"
#include "preferences.h"

#include <QEvent>
#include <QMessageBox>

using namespace asaal;

Preferences::Preferences( QWidget *parent )
  : QDialog(parent) {

  setupUi(this);

  connect(mButtonReset, SIGNAL(clicked()), this, SLOT(slotReset()));
  connect(mButtonOk, SIGNAL(clicked()), this, SLOT(slotSave()));
  connect(mButtonCancel, SIGNAL(clicked()), this, SLOT(slotCancel()));

  connect(mToolButtonGlobal, SIGNAL(clicked()), this, SLOT(slotSwitchSettings()));
  connect(mToolButtonUpdate, SIGNAL(clicked()), this, SLOT(slotSwitchSettings()));

}

void Preferences::slotReset() {

  int result = QMessageBox::question(this,
                                     QApplication::applicationName(),
                                     tr("The default settings are used.\n\nIs this what you want?"),
                                     QMessageBox::Yes,
                                     QMessageBox::No);
  switch( result ) {
    case QMessageBox::Yes:
      defaultSettings();
      break;
    default:
      break;
  }
}

void Preferences::slotCancel() {

  QDialog::reject();
}

void Preferences::slotSave() {

  QDialog::accept();
}

void Preferences::slotSwitchSettings() {

  QToolButton *toolButton = qobject_cast<QToolButton*>(sender());
  if( toolButton ) {
    if( toolButton == mToolButtonGlobal )
      mStackedWidgetSettings->setCurrentIndex(0);
    else if( toolButton == mToolButtonUpdate )
      mStackedWidgetSettings->setCurrentIndex(1);
  }
}

void Preferences::defaultSettings() {
}

void Preferences::changeEvent( QEvent *event ) {

  switch( event -> type() ) {

    case QEvent::LanguageChange:

      retranslateUi(this);
      break;

    default:
      return;
  }
}
