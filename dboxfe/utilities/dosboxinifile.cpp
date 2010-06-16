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

#include <QFile>
#include <QRegExp>
#include <QStringList>
#include <QTextStream>


QString m_iniFile;

using namespace asaal;

DOSBoxConfiguration *DOSBoxIniFile::defaultConfiguration() {

  DOSBoxConfiguration *dosboxConfig = new DOSBoxConfiguration;

  QSettings emptySettings;
  dosboxConfig->sdl = sdlSection(emptySettings, true);
  dosboxConfig->dosbox = dosboxSection(emptySettings, true);
  dosboxConfig->render = renderSection(emptySettings, true);
  dosboxConfig->cpu = cpuSection(emptySettings, true);
  dosboxConfig->mixer = mixerSection(emptySettings, true);
  dosboxConfig->mdi = mdiSection(emptySettings, true);
  dosboxConfig->soundBlaster = sblasterSection(emptySettings, true);
  dosboxConfig->gus = gusSection(emptySettings, true);
  dosboxConfig->speaker = speakerSection(emptySettings, true);
  dosboxConfig->joystick = joystickSection(emptySettings, true);
  dosboxConfig->serial = serialSection(emptySettings, true);
  dosboxConfig->dos = dosSection(emptySettings, true);
  dosboxConfig->ipx = ipxSection(emptySettings, true);
  dosboxConfig->autoexec = autoexecSection(true);

  return dosboxConfig;
}

DOSBoxConfiguration *DOSBoxIniFile::read( const QString &file ) {

  m_iniFile.clear();
  m_iniFile = file;
  return read();
}

void DOSBoxIniFile::write( const QString &file, const DOSBoxConfiguration *config ) {

  m_iniFile.clear();
  m_iniFile = file;
  write(config);
}

/************************************************************
 * Private methods/functions
 ************************************************************/
DOSBoxConfiguration *DOSBoxIniFile::read() {

  if( m_iniFile.isNull() || m_iniFile.isEmpty() )
    return 0;

  QFile dosboxIni(m_iniFile);
  if( !dosboxIni.exists() )
    return 0;

  DOSBoxConfiguration *dosboxConfig = DOSBoxIniFile::defaultConfiguration();

  QSettings dosboxSettings(m_iniFile, QSettings::IniFormat);

  dosboxConfig->sdl = sdlSection(dosboxSettings, false);
  dosboxConfig->dosbox = dosboxSection(dosboxSettings, false);
  dosboxConfig->render = renderSection(dosboxSettings, false);
  dosboxConfig->cpu = cpuSection(dosboxSettings, false);
  dosboxConfig->mixer = mixerSection(dosboxSettings, false);
  dosboxConfig->mdi = mdiSection(dosboxSettings, false);
  dosboxConfig->soundBlaster = sblasterSection(dosboxSettings, false);
  dosboxConfig->gus = gusSection(dosboxSettings, false);
  dosboxConfig->speaker = speakerSection(dosboxSettings, false);
  dosboxConfig->joystick = joystickSection(dosboxSettings, false);
  dosboxConfig->serial = serialSection(dosboxSettings, false);
  dosboxConfig->dos = dosSection(dosboxSettings, false);
  dosboxConfig->ipx = ipxSection(dosboxSettings, false);
  dosboxConfig->autoexec = autoexecSection(false);

  return dosboxConfig;
}

void DOSBoxIniFile::write( const DOSBoxConfiguration *config ) {

  if( !config )
    return;

  QSettings settings(m_iniFile, QSettings::IniFormat);
  settings.beginGroup("sdl");
  {
    settings.setValue("fullscreen", config->sdl->mFullScreen);
    settings.setValue("fulldouble", config->sdl->mFullDouble);
    settings.setValue("fullresolution", config->sdl->mFullResolution);
    settings.setValue("windowresolution", config->sdl->mWindowResolution);
    settings.setValue("output", config->sdl->mOutput);
    settings.setValue("autolock",config->sdl->mAutolock);
    settings.setValue("sensitivity", config->sdl->mSensitivity);
    settings.setValue("waitonerror", config->sdl->mWaitOnError);
    settings.setValue("priority", config->sdl->mPriority);
    settings.setValue("mapperfile", config->sdl->mMapperFile);
    settings.setValue("usescancodes", config->sdl->mUseScanCodes);
  }
  settings.endGroup();

  settings.beginGroup("dosbox");
  {
    settings.setValue("language", config->dosbox->mLanguage);
    settings.setValue("machine", config->dosbox->mMachine);
    settings.setValue("captures", config->dosbox->mCaptures);
    settings.setValue("memsize", config->dosbox->mMemsize);
  }
  settings.endGroup();

  settings.beginGroup("render");
  {
    settings.setValue("frameskip", config->render->mFrameSkip);
    settings.setValue("aspect", config->render->mAspect);
    settings.setValue("scaler", config->render->mScaler);
  }
  settings.endGroup();

  settings.beginGroup("cpu");
  {
    settings.setValue("core", config->cpu->mCore);
    settings.setValue("cputype", config->cpu->mType);

    QString cycleType = config->cpu->mCycles;
    QString cycles = "";
    if( cycleType.contains("fixed") )
      cycles = QString::number(config->cpu->mCycle);
    cycleType = cycleType.append( " " + cycles);
    cycleType = cycleType.trimmed();
    settings.setValue("cycles", cycleType);

    settings.setValue("cycleup", config->cpu->mCycleUp);
    settings.setValue("cycledown", config->cpu->mCycleDown);
  }
  settings.endGroup();

  settings.beginGroup("mixer");
  {
    settings.setValue("nosound", config->mixer->mNosound);
    settings.setValue("rate", config->mixer->mRate);
    settings.setValue("blocksize", config->mixer->mBlockSize);
    settings.setValue("prebuffer", config->mixer->mPreBuffer);
  }
  settings.endGroup();

  settings.beginGroup("midi");
  {
    settings.setValue("mpu401", config->mdi->mMpu401);
    settings.setValue("mididevice", config->mdi->mMidiDevice);
    settings.setValue("midiconfig", config->mdi->mMidiConfig);
  }
  settings.endGroup();

  settings.beginGroup("sblaster");
  {
    settings.setValue("sbtype", config->soundBlaster->mSBType);
    settings.setValue("sbbase", config->soundBlaster->mSBBase);
    settings.setValue("irq", config->soundBlaster->mIrq);
    settings.setValue("dma", config->soundBlaster->mDma);
    settings.setValue("hdma", config->soundBlaster->mHdma);
    settings.setValue("sbmixer", config->soundBlaster->mSBMixer);
    settings.setValue("oplmode", config->soundBlaster->mOplMode);
    settings.setValue("oplemu", config->soundBlaster->mOplEmu);
    settings.setValue("oplrate", config->soundBlaster->mOplRate);
  }
  settings.endGroup();

  settings.beginGroup("gus");
  {
    settings.setValue("gus", config->gus->mGus);
    settings.setValue("gusrate", config->gus->mGusRate);
    settings.setValue("gusbase", config->gus->mGusBase);
    settings.setValue("gusirq", config->gus->mGusIrq);
    settings.setValue("gusdma", config->gus->mGusDma);
    settings.setValue("ultradir", config->gus->mUltraDir);
  }
  settings.endGroup();

  settings.beginGroup("speaker");
  {
    settings.setValue("pcspeaker", config->speaker->mPcSpeaker);
    settings.setValue("pcrate", config->speaker->mPcRate);
    settings.setValue("tandy", config->speaker->mTandy);
    settings.setValue("tandyrate", config->speaker->mTandyRate);
    settings.setValue("disney", config->speaker->mDisney);
  }
  settings.endGroup();

  settings.beginGroup("joystick");
  {
    settings.setValue("joysticktype", config->joystick->mJoystickType);
    settings.setValue("timed", config->joystick->mTimed);
    settings.setValue("autofire", config->joystick->mAutoFire);
    settings.setValue("swap34", config->joystick->mSwap34);
    settings.setValue("buttonwrap", config->joystick->mButtonwrap);
  }
  settings.endGroup();

  settings.beginGroup("serial");
  {
    settings.setValue("serial1", config->serial->mSerial1);
    settings.setValue("serial2", config->serial->mSerial2);
    settings.setValue("serial3", config->serial->mSerial3);
    settings.setValue("serial4", config->serial->mSerial4);
  }
  settings.endGroup();

  settings.beginGroup("dos");
  {
    settings.setValue("xms", config->dos->mXms);
    settings.setValue("ems", config->dos->mEms);
    settings.setValue("umb", config->dos->mUmb);
    settings.setValue("keyboardlayout", config->dos->mKeyboardLayout);
  }
  settings.endGroup();

  settings.beginGroup("ipx");
  {
    settings.setValue("ipx", config->ipx->mIpx);
  }
  settings.endGroup();
  settings.sync();

  QFile iniFile(m_iniFile);
  if( !iniFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text) )
    return;

  QTextStream outStream( &iniFile );
  outStream << "\n[autoexec]\n";

  foreach( const QString autoexec, config->autoexec ) {
    outStream << autoexec << "\n";
  }

  outStream.flush();
  iniFile.flush();
  iniFile.close();
}

SdlSection *DOSBoxIniFile::sdlSection( QSettings &settings, bool defaultSettings ) {

  SdlSection *sdl = new SdlSection;
  if( defaultSettings ) {

    sdl->mFullScreen = false;
    sdl->mFullDouble = false;
    sdl->mFullResolution = "original";
    sdl->mWindowResolution = "original";
    sdl->mOutput = "surface";
    sdl->mAutolock = true;
    sdl->mSensitivity = 100;
    sdl->mWaitOnError = false;
    sdl->mPriority = "higher,normal";
    sdl->mMapperFile = "mapper.txt";
    sdl->mUseScanCodes = true;

  } else {

    settings.beginGroup("sdl");
    sdl->mFullScreen = settings.value("fullscreen", QVariant(false)).toBool();
    sdl->mFullDouble = settings.value("fulldouble", QVariant(false)).toBool();
    sdl->mFullResolution = settings.value("fullresolution", QVariant("original")).toString();
    sdl->mWindowResolution = settings.value("windowresolution", QVariant("original")).toString();
    sdl->mOutput = settings.value("output", QVariant("surface")).toString();
    sdl->mAutolock = settings.value("autolock", QVariant(true)).toBool();
    sdl->mSensitivity = settings.value("sensitivity", QVariant(100)).toInt();
    sdl->mWaitOnError = settings.value("waitonerror", QVariant(true)).toBool();
    sdl->mPriority = settings.value("priority", QVariant("higher,normal")).toString();
    sdl->mMapperFile = settings.value("mapperfile", QVariant("mapper.txt")).toString();
    sdl->mUseScanCodes = settings.value("usescancodes", QVariant(true)).toBool();
    settings.endGroup();
  }

  return sdl;
}

DosboxSection *DOSBoxIniFile::dosboxSection( QSettings &settings, bool defaultSettings ) {

  DosboxSection *dosbox = new DosboxSection;
  if( defaultSettings ) {

    dosbox->mLanguage = "";
    dosbox->mMachine = "svga_s3";
    dosbox->mCaptures = "capture";
    dosbox->mMemsize = 16;

  }
  else {

    settings.beginGroup("dosbox");
    dosbox->mLanguage = settings.value("language", QVariant("")).toString();
    dosbox->mMachine = settings.value("machine", QVariant("")).toString();
    dosbox->mCaptures = settings.value("captures", QVariant("capture")).toString();
    dosbox->mMemsize = settings.value("memsize", QVariant(16)).toInt();
    settings.endGroup();
  }

  return dosbox;
}

RenderSection *DOSBoxIniFile::renderSection( QSettings &settings, bool defaultSettings ) {

  RenderSection *render = new RenderSection;
  if( defaultSettings ) {

    render->mFrameSkip = 0;
    render->mAspect = false;
    render->mScaler = "normal2x";
  }
  else {

    settings.beginGroup("render");
    render->mFrameSkip = settings.value("frameskip", QVariant(0)).toInt();
    render->mAspect = settings.value("aspect", QVariant(false)).toBool();
    render->mScaler = settings.value("scaler", QVariant("normal2x")).toString();
    settings.endGroup();
  }

  return render;
}

CpuSection *DOSBoxIniFile::cpuSection( QSettings &settings, bool defaultSettings ) {

  CpuSection *cpu = new CpuSection;
  if( defaultSettings ) {

    cpu->mCore = "auto";
    cpu->mType = "auto";
    cpu->mCycles = "auto";
    cpu->mCycle = 0;
    cpu->mCycleUp = 500;
    cpu->mCycleDown = 20;

  }
  else {

    settings.beginGroup("cpu");
    cpu->mCore = settings.value("core", QVariant("auto")).toString();
    cpu->mType = settings.value("cputype", QVariant("auto")).toString();
    
    QString cycleType = settings.value("cycles", QVariant("auto")).toString();
    QStringList cycleTypes = cycleType.split(" ");
    if( cycleTypes.count() == 2 ) {

      cpu->mCycles = cycleTypes.at(0);
      cpu->mCycle = cycleTypes.at(1).toInt();
    }
    else {
      cpu->mCycles = settings.value("cycles", QVariant("auto")).toString();
      cpu->mCycle = 0;
    }
    cycleType.clear();
    cycleTypes.clear();

    cpu->mCycleUp = settings.value("cycleup", QVariant(500)).toInt();
    cpu->mCycleDown = settings.value("cycledown", QVariant(20)).toInt();
    settings.endGroup();

  }

  return cpu;
}

MixerSection *DOSBoxIniFile::mixerSection( QSettings &settings, bool defaultSettings ) {

  MixerSection *mixer = new MixerSection;
  if( defaultSettings ) {

    mixer->mNosound = false;
    mixer->mRate = 22050;
    mixer->mBlockSize = 2048;
    mixer->mPreBuffer = 10;
  }
  else {

    settings.beginGroup("mixer");
    mixer->mNosound = settings.value("nosound", QVariant(false)).toBool();
    mixer->mRate = settings.value("rate", QVariant(2205)).toInt();
    mixer->mBlockSize = settings.value("blocksize", QVariant(2048)).toInt();
    mixer->mPreBuffer = settings.value("prebuffer", QVariant(10)).toInt();
    settings.endGroup();
  }

  return mixer;
}

MdiSection *DOSBoxIniFile::mdiSection( QSettings &settings, bool defaultSettings ) {

  MdiSection *mdi = new MdiSection;
  if( defaultSettings ) {

    mdi->mMpu401 = "intelligent";
    mdi->mMidiDevice = "default";
    mdi->mMidiConfig = "";
  }
  else {

    settings.beginGroup("midi");
    mdi->mMpu401 = settings.value("mpu401", QVariant("intelligent")).toString();
    mdi->mMidiDevice = settings.value("mididevice", QVariant("default")).toString();
    mdi->mMidiConfig = settings.value("midiconfig", QVariant("")).toString();
    settings.endGroup();
  }

  return mdi;
}

SBlasterSection *DOSBoxIniFile::sblasterSection( QSettings &settings, bool defaultSettings ) {

  SBlasterSection *soundBlaster = new SBlasterSection;
  if( defaultSettings ) {

    soundBlaster->mSBType = "sb16";
    soundBlaster->mSBBase = 220;
    soundBlaster->mIrq = 7;
    soundBlaster->mDma = 1;
    soundBlaster->mHdma = 5;
    soundBlaster->mSBMixer = true;
    soundBlaster->mOplMode = "auto";
    soundBlaster->mOplEmu = "default";
    soundBlaster->mOplRate = 22050;
    settings.endGroup();
  }
  else {

    settings.beginGroup("sblaster");
    soundBlaster->mSBType = settings.value("sbtype", QVariant("sb16")).toString();
    soundBlaster->mSBBase = settings.value("sbbase", QVariant(220)).toInt();
    soundBlaster->mIrq = settings.value("irq", QVariant(7)).toInt();
    soundBlaster->mDma = settings.value("dma", QVariant(1)).toInt();
    soundBlaster->mHdma = settings.value("hdma", QVariant(5)).toInt();
    soundBlaster->mSBMixer = settings.value("sbmixer", QVariant(true)).toBool();
    soundBlaster->mOplMode = settings.value("oplmode", QVariant("auto")).toString();
    soundBlaster->mOplEmu = settings.value("oplemu", QVariant("default")).toString();
    soundBlaster->mOplRate = settings.value("oplrate", QVariant(22050)).toInt();
    settings.endGroup();
  }

  return soundBlaster;
}

GusSection *DOSBoxIniFile::gusSection( QSettings &settings, bool defaultSettings ) {

  GusSection *gus = new GusSection;
  if( defaultSettings ) {

    gus->mGus = false;
    gus->mGusRate = 22050;
    gus->mGusBase = 240;
    gus->mGusIrq = 5;
    gus->mGusDma = 3;
    gus->mUltraDir = "C:\\ULTRASND";
  }
  else {

    settings.beginGroup("gus");
    gus->mGus = settings.value("gus", QVariant(false)).toBool();
    gus->mGusRate = settings.value("gusrate", QVariant(22050)).toInt();
    gus->mGusBase = settings.value("gusbase", QVariant(240)).toInt();
    gus->mGusIrq = settings.value("gusirq", QVariant(5)).toInt();
    gus->mGusDma = settings.value("gusdma", QVariant(3)).toInt();
    gus->mUltraDir = settings.value("ultradir", QVariant("C:\\ULTRASND")).toString();
    settings.endGroup();
  }

  return gus;
}

SpeakerSection *DOSBoxIniFile::speakerSection( QSettings &settings, bool defaultSettings ) {

  SpeakerSection *speaker = new SpeakerSection;
  if( defaultSettings ) {

    speaker->mPcSpeaker = true;
    speaker->mPcRate = 22050;
    speaker->mTandy = "auto";
    speaker->mTandyRate = 22050;
    speaker->mDisney = true;
  }
  else {

    settings.beginGroup("speaker");
    speaker->mPcSpeaker = settings.value("pcspeaker", QVariant(true)).toBool();
    speaker->mPcRate = settings.value("pcrate", QVariant(22050)).toInt();
    speaker->mTandy = settings.value("tandy", QVariant("auto")).toString();
    speaker->mTandyRate = settings.value("tandyrate", QVariant(22050)).toInt();
    speaker->mDisney = settings.value("disney", QVariant(true)).toBool();
    settings.endGroup();
  }

  return speaker;
}

JoystickSection *DOSBoxIniFile::joystickSection( QSettings &settings, bool defaultSettings ) {

  JoystickSection *joystick = new JoystickSection;
  if( defaultSettings ) {

    joystick->mJoystickType = "auto";
    joystick->mTimed = true;
    joystick->mAutoFire = false;
    joystick->mSwap34 = false;
    joystick->mButtonwrap = false;
  }
  else {

    settings.beginGroup("joystick");
    joystick->mJoystickType = settings.value("joysticktype", QVariant("auto")).toString();
    joystick->mTimed = settings.value("timed", QVariant(true)).toBool();
    joystick->mAutoFire = settings.value("autofire", QVariant(false)).toBool();
    joystick->mSwap34 = settings.value("swap34", QVariant(false)).toBool();
    joystick->mButtonwrap = settings.value("buttonwrap", QVariant(false)).toBool();
    settings.endGroup();
  }

  return joystick;
}

SerialSection *DOSBoxIniFile::serialSection( QSettings &settings, bool defaultSettings ) {

  SerialSection *serial = new SerialSection;
  if( defaultSettings ) {

    serial->mSerial1 = "dummy";
    serial->mSerial2 = "dummy";
    serial->mSerial3 = "disabled";
    serial->mSerial4 = "disabled";
  }
  else {

    settings.beginGroup("serial");
    serial->mSerial1 = settings.value("serial1", QVariant("dummy")).toString();
    serial->mSerial2 = settings.value("serial2", QVariant("dummy")).toString();
    serial->mSerial3 = settings.value("serial3", QVariant("disabled")).toString();
    serial->mSerial4 = settings.value("serial4", QVariant("disabled")).toString();
    settings.endGroup();
  }

  return serial;
}

DosSection *DOSBoxIniFile::dosSection( QSettings &settings, bool defaultSettings ) {

  DosSection *dos = new DosSection;
  if( defaultSettings ) {

    dos->mXms = true;
    dos->mEms = true;
    dos->mUmb = true;
    dos->mKeyboardLayout = "auto";
  }
  else {

    settings.beginGroup("dos");
    dos->mXms = settings.value("xms", QVariant(true)).toBool();
    dos->mEms = settings.value("ems", QVariant(true)).toBool();
    dos->mUmb = settings.value("umb", QVariant(true)).toBool();
    dos->mKeyboardLayout = settings.value("keyboardlayout", QVariant("auto")).toString();
    settings.endGroup();
  }

  return dos;
}

IpxSection *DOSBoxIniFile::ipxSection( QSettings &settings, bool defaultSettings ) {

  IpxSection *ipx = new IpxSection;
  if( defaultSettings ) {

    ipx->mIpx = false;
  }
  else {

    settings.beginGroup("ipx");
    ipx->mIpx = settings.value("ipx", QVariant(false)).toBool();
    settings.endGroup();
  }

  return ipx;
}

QStringList DOSBoxIniFile::autoexecSection( bool defaultSettings ) {

  QStringList autoexecList;
  if( defaultSettings )
    return autoexecList;

  if( m_iniFile.isNull() || m_iniFile.isEmpty() )
    return autoexecList;

  QFile iniFile(m_iniFile);
  if( !iniFile.open(QIODevice::ReadOnly | QIODevice::Text) )
    return autoexecList;

  QTextStream in(&iniFile);
  while( !in.atEnd() ) {

    QString line = in.readLine();
    if( line.isEmpty() )
      continue;

    if( line.startsWith("[autoexec]") ) {

      while( !in.atEnd() ) {

        line = in.readLine();
        if( line.startsWith("#") || line.isEmpty() )
          continue;

        autoexecList.append(line);

        // Not possible but sure is sure
        if( line.startsWith("[") && line.endsWith("]") )
          break;
      }
    }
  }
  iniFile.close();

  return autoexecList;
}
