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

#include "dosboxinifile.h"
#include "profilesettings.h"

using namespace asaal;

ProfileSettings::ProfileSettings( QWidget *parent )
  : QWidget(parent) {

  setupUi(this);

  connect(mToolBtnAutoexec, SIGNAL(clicked()), this, SLOT(slotSwitchSettings()));
  connect(mToolBtnDos, SIGNAL(clicked()), this, SLOT(slotSwitchSettings()));
  connect(mToolBtnGraphic, SIGNAL(clicked()), this, SLOT(slotSwitchSettings()));
  connect(mToolBtnInternet, SIGNAL(clicked()), this, SLOT(slotSwitchSettings()));
  connect(mToolBtnSound, SIGNAL(clicked()), this, SLOT(slotSwitchSettings()));

  mStackedWidgetProfileSettings->setCurrentIndex(0);
}

void ProfileSettings::setProfile( const QString &profileName, const QString &profileFile ) {

  mProfileName.clear();
  mProfileName = profileName;

  mProfileFile.clear();
  mProfileFile = profileFile;

  initializeSettings();

  QString mWindowTitle = windowTitle();
  mWindowTitle = mWindowTitle.append(" [%1]").arg(mProfileName);
  setWindowTitle(mWindowTitle);
  mWindowTitle.clear();
}

void ProfileSettings::slotReset() {
}

void ProfileSettings::slotSave() {
}

void ProfileSettings::slotAbort() {
}

void ProfileSettings::slotSwitchSettings() {

  QToolButton *button = qobject_cast<QToolButton *>(sender());
  if( button ) {
    if( button == mToolBtnGraphic ) {
      mStackedWidgetProfileSettings->setCurrentIndex(0);
    }
    else if( button == mToolBtnSound ) {
      mStackedWidgetProfileSettings->setCurrentIndex(1);
    }
    else if( button == mToolBtnInternet ) {
      mStackedWidgetProfileSettings->setCurrentIndex(2);
    }
    else if( button == mToolBtnDos ) {
      mStackedWidgetProfileSettings->setCurrentIndex(3);
    }
    else if( button == mToolBtnAutoexec ) {
      mStackedWidgetProfileSettings->setCurrentIndex(4);
    }
  }
}

void ProfileSettings::initializeSettings() {

  DOSBoxConfiguration *dosboxConfig = 0;
  if( mProfileFile.isEmpty() ) {

    dosboxConfig = DOSBoxIniFile::defaultConfiguration();
  }
  else {

    dosboxConfig = DOSBoxIniFile::read(mProfileFile);
  }

  if( dosboxConfig ) {

    initializeGraphic(dosboxConfig);
    initializeSound(dosboxConfig);
    initializeInternet(dosboxConfig);
    initializeDos(dosboxConfig);
    initializeAutoexec(dosboxConfig);
  }

  if( dosboxConfig )
    delete dosboxConfig;
  dosboxConfig = 0;
}

void ProfileSettings::initializeGraphic( const DOSBoxConfiguration *config ) {

  int comboIndex = 0;
  SdlSection *sdlSection = config->sdl;
  {
    mCheckBoxAutolock->setChecked(sdlSection->mAutolock);
    mHorizontalSliderSensitivity->setValue(sdlSection->mSensitivity);
    mCheckBoxWaitOnError->setChecked(sdlSection->mWaitOnError);
    mCheckBoxFullScreen->setChecked(sdlSection->mFullScreen);
    mCheckBoxFullDouble->setChecked(sdlSection->mFullDouble);
    mLineEditMapperFile->setText(sdlSection->mMapperFile);
    mCheckBoxUseScanCodes->setChecked(sdlSection->mUseScanCodes);

    comboIndex = mComboBoxWindowSize->findText(sdlSection->mFullResolution);
    mComboBoxWindowSize->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxWindowWidthHeight->findText(sdlSection->mWindowResolution);
    mComboBoxWindowWidthHeight->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxOutput->findText(sdlSection->mOutput);
    mComboBoxOutput->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxPriority->findText(sdlSection->mPriority);
    mComboBoxPriority->setCurrentIndex(comboIndex);
  }

  RenderSection *render = config->render;
  {
    mCheckBoxAspect->setChecked(render->mAspect);
    mSpinBoxFrameSkip->setValue(render->mFrameSkip);

    comboIndex = mComboBoxScaler->findText(render->mScaler);
    mComboBoxScaler->setCurrentIndex(comboIndex);
  }

  // CPU
  CpuSection *cpu = config->cpu;
  {
    comboIndex = mComboBoxCore->findText(cpu->mCore);
    mComboBoxCore->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxCycles->findText(cpu->mCycles);
    mComboBoxCycles->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxType->findText(cpu->mType);
    mComboBoxType->setCurrentIndex(comboIndex);

    mSpinBoxCycles->setValue(cpu->mCycle);
    mSpinBoxCycleDown->setValue(cpu->mCycleDown);
    mSpinBoxCycleUp->setValue(cpu->mCycleUp);
  }

}

void ProfileSettings::initializeSound( const DOSBoxConfiguration *config ) {

  Q_UNUSED(config)
}

void ProfileSettings::initializeInternet( const DOSBoxConfiguration *config ) {

  Q_UNUSED(config)
}

void ProfileSettings::initializeDos( const DOSBoxConfiguration *config ) {

  Q_UNUSED(config)
}

void ProfileSettings::initializeAutoexec( const DOSBoxConfiguration *config ) {

  Q_UNUSED(config)
}
