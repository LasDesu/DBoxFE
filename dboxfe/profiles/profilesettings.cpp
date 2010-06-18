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
  : QWidget(parent), 
    mDosBoxConfig(0) {

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

  releaseConfiguration(mDosBoxConfig);
  initializeSettings();

  QString mWindowTitle = windowTitle();
  mWindowTitle = mWindowTitle.append(" [%1]").arg(mProfileName);
  setWindowTitle(mWindowTitle);
  mWindowTitle.clear();
}

void ProfileSettings::slotReset() {

}

void ProfileSettings::slotSave() {

  if( mProfileFile.isEmpty() || mProfileFile.isNull() )
    return;

  DOSBoxConfiguration *dosboxConfig = new DOSBoxConfiguration;

  setGraphic(dosboxConfig);
  setSound(dosboxConfig);
  setInternet(dosboxConfig);
  setDos(dosboxConfig);
  setAutoexec(dosboxConfig);

  DOSBoxIniFile::write(mProfileFile, dosboxConfig);

  releaseConfiguration(dosboxConfig);
}

void ProfileSettings::slotAbort() {

  releaseConfiguration(mDosBoxConfig);
  close();
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
/*******************************************************************************************
 * Read configuration
 *******************************************************************************************/
void ProfileSettings::initializeSettings() {

  if( mProfileFile.isEmpty() ) {

    mDosBoxConfig = DOSBoxIniFile::defaultConfiguration();
  }
  else {

    mDosBoxConfig = DOSBoxIniFile::read(mProfileFile);
  }

  if( mDosBoxConfig ) {

    initializeGraphic(mDosBoxConfig);
    initializeSound(mDosBoxConfig);
    initializeInternet(mDosBoxConfig);
    initializeDos(mDosBoxConfig);
    initializeAutoexec(mDosBoxConfig);
  }
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

  int comboIndex = 0;
  MixerSection *mixer = config->mixer;
  {
    mCheckBoxMixerNoSound->setChecked(mixer->mNosound);

    comboIndex = mComboBoxMixerRate->findText(QString("%1").arg(mixer->mRate));
    mComboBoxMixerRate->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxMixerBlockSize->findText(QString("%1").arg(mixer->mBlockSize));
    mComboBoxMixerBlockSize->setCurrentIndex(comboIndex);

    mSpinBoxMixerPreBuffer->setValue(mixer->mPreBuffer);
  }

  MdiSection *mdi = config->mdi;
  {
    comboIndex = mComboBoxMidiMPU401->findText(mdi->mMpu401);
    mComboBoxMidiMPU401->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxMidiDevice->findText(mdi->mMidiDevice);
    mComboBoxMidiDevice->setCurrentIndex(comboIndex);

    mLineEditMidiConfig->setText(mdi->mMidiConfig);
  }

  SBlasterSection *soundBlaster = config->soundBlaster;
  {
    comboIndex = mComboBoxSBType->findText(soundBlaster->mSBType);
    mComboBoxSBType->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxSBBase->findText(QString("%1").arg(soundBlaster->mSBBase));
    mComboBoxSBBase->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxSBIrq->findText(QString("%1").arg(soundBlaster->mIrq));
    mComboBoxSBIrq->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxSBDMA->findText(QString("%1").arg(soundBlaster->mDma));
    mComboBoxSBDMA->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxSBHDMA->findText(QString("%1").arg(soundBlaster->mHdma));
    mComboBoxSBHDMA->setCurrentIndex(comboIndex);

    mCheckBoxSBMixer->setChecked(soundBlaster->mSBMixer);

    comboIndex = mComboBoxSBOplMode->findText(soundBlaster->mOplMode);
    mComboBoxSBOplMode->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxSBOplEmu->findText(soundBlaster->mOplEmu);
    mComboBoxSBOplEmu->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxSBOplRate->findText(QString("%1").arg(soundBlaster->mOplRate));
    mComboBoxSBOplRate->setCurrentIndex(comboIndex);
  }

  GusSection *gus = config->gus;
  {
    mCheckBoxGus->setChecked(gus->mGus);
     
    comboIndex = mComboBoxGusRate->findText(QString("%1").arg(gus->mGusRate));
    mComboBoxGusRate->setCurrentIndex(comboIndex);
     
    comboIndex = mComboBoxGusBase->findText(QString("%1").arg(gus->mGusBase));
    mComboBoxGusBase->setCurrentIndex(comboIndex);
     
    comboIndex = mComboBoxGusIRQ->findText(QString("%1").arg(gus->mGusIrq));
    mComboBoxGusIRQ->setCurrentIndex(comboIndex);
     
    comboIndex = mComboBoxGusDMA->findText(QString("%1").arg(gus->mGusDma));
    mComboBoxGusDMA->setCurrentIndex(comboIndex);

    mLineEditGusUltraDir->setText(gus->mUltraDir);
  }

  SpeakerSection *speaker = config->speaker;
  {
    mCheckBoxSpeaker->setChecked(speaker->mPcSpeaker);

    comboIndex = mComboBoxSpeakerPCRate->findText(QString("%1").arg(speaker->mPcRate));
    mComboBoxSpeakerPCRate->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxSpeakerTandy->findText(speaker->mTandy);
    mComboBoxSpeakerTandy->setCurrentIndex(comboIndex);

    comboIndex = mComboBoxSpeakerTandyRate->findText(QString("%1").arg(speaker->mTandyRate));
    mComboBoxSpeakerTandyRate->setCurrentIndex(comboIndex);

    mCheckBoxSpeakerDisney->setChecked(speaker->mDisney);
  }
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

/*******************************************************************************************
 * Set configuration
 *******************************************************************************************/
void ProfileSettings::setGraphic( DOSBoxConfiguration *config ) {

  config->sdl = new SdlSection;
  config->render = new RenderSection;
  config->cpu = new CpuSection;
  
}

void ProfileSettings::setSound( DOSBoxConfiguration *config ) {
  
  config->mixer = new MixerSection;
  config->mdi = new MdiSection;
  config->soundBlaster = new SBlasterSection;
  config->gus = new GusSection;
  config->speaker = new SpeakerSection;
}

void ProfileSettings::setInternet( DOSBoxConfiguration *config ) {

  config->serial = new SerialSection;
  config->ipx = new IpxSection;
}

void ProfileSettings::setDos( DOSBoxConfiguration *config ) {
  
  config->dosbox = new DosboxSection;
  config->joystick = new JoystickSection;
  config->dos = new DosSection;
}

void ProfileSettings::setAutoexec( DOSBoxConfiguration *config ) {

  config->autoexec.clear();
}

/*******************************************************************************************
 * Release / Delete configuration object
 *******************************************************************************************/
void ProfileSettings::releaseConfiguration( DOSBoxConfiguration *config ) {

  if( !config )
    return;
    
  if( config->sdl )
    delete config->sdl;
  
  if( config->dosbox )
    delete config->dosbox;
  
  if( config->render )
    delete config->render;
  
  if( config->cpu )
    delete config->cpu;
  
  if( config->mixer )
    delete config->mixer;
  
  if( config->mdi )
    delete config->mdi;
  
  if( config->soundBlaster )
    delete config->soundBlaster;
  
  if( config->gus )
    delete config->gus;
  
  if( config->speaker )
    delete config->speaker;
  
  if( config->joystick )
    delete config->joystick;
  
  if( config->serial )
    delete config->serial;
  
  if( config->dos )
    delete config->dos;
  
  if( config->ipx )
    delete config->ipx;
  
  config->autoexec.clear();
  
  if( config )
    delete config;
  config = 0;
}
