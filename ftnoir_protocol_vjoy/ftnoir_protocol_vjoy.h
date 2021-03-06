/********************************************************************************
* FaceTrackNoIR		This program is a private project of some enthusiastic		*
*					gamers from Holland, who don't like to pay much for			*
*					head-tracking.												*
*																				*
* Copyright (C) 2013	Wim Vriend (Developing)									*
*						Ron Hendriks (Researching and Testing)					*
*																				*
* Homepage																		*
*																				*
* This program is free software; you can redistribute it and/or modify it		*
* under the terms of the GNU General Public License as published by the			*
* Free Software Foundation; either version 3 of the License, or (at your		*
* option) any later version.													*
*																				*
* This program is distributed in the hope that it will be useful, but			*
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY	*
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for	*
* more details.																	*
*																				*
* You should have received a copy of the GNU General Public License along		*
* with this program; if not, see <http://www.gnu.org/licenses/>.				*
*																				*
* FGServer			FGServer is the Class, that communicates headpose-data		*
*					to FlightGear, using UDP.				         			*
*					It is based on the (Linux) example made by Melchior FRANZ.	*
********************************************************************************/
#pragma once
#include "ftnoir_protocol_base/ftnoir_protocol_base.h"
#include "ui_ftnoir_vjoy_controls.h"
#include <Windows.h>
#include <VJoy.h>
#include <QThread>
#include <QUdpSocket>
#include <QMessageBox>
#include <QSettings>
#include <math.h>
#include "facetracknoir/global-settings.h"

#define FT_PROGRAMID "FT_ProgramID"

class FTNoIR_Protocol : public IProtocol
{
public:
	FTNoIR_Protocol();
	~FTNoIR_Protocol();
    bool checkServerInstallationOK() {
        return true;
    }
    void sendHeadposeToGame( double *headpose, double *rawheadpose );
private:
    QString getGameName() {
        return "Virtual joystick";
    }
};

// Widget that has controls for FTNoIR protocol client-settings.
class VJoyControls: public QWidget, public IProtocolDialog
{
    Q_OBJECT
public:

	explicit VJoyControls();
    virtual ~VJoyControls();
    void showEvent ( QShowEvent *) {}

    void Initialize(QWidget *);
    void registerProtocol(IProtocol *l) {}
	void unRegisterProtocol() {}

private:
	Ui::UICVJoyControls ui;
	void save();

private slots:
	void doOK();
	void doCancel();
};

//*******************************************************************************************************
// FaceTrackNoIR Protocol DLL. Functions used to get general info on the Protocol
//*******************************************************************************************************
class FTNoIR_ProtocolDll : public Metadata
{
public:
	FTNoIR_ProtocolDll();
	~FTNoIR_ProtocolDll();

	void getFullName(QString *strToBeFilled) { *strToBeFilled = QString("VJoy"); }
	void getShortName(QString *strToBeFilled) { *strToBeFilled = QString("VJoy"); }
	void getDescription(QString *strToBeFilled) { *strToBeFilled = QString("VJoy"); }

    void getIcon(QIcon *icon) { *icon = QIcon(":/images/vjoy.png"); }
};
