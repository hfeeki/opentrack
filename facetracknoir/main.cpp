/********************************************************************************
* FaceTrackNoIR		This program is a private project of the some enthusiastic	*
*					gamers from Holland, who don't like to pay much for			*
*					head-tracking.												*
*																				*
* Copyright (C) 2010	Wim Vriend (Developing)									*
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
*********************************************************************************/
/*
	Modifications (last one on top):
		20100520 - WVR: Added class FaceApp, to override winEventFilter. It receives 
						messages from the Game.
*/

#include "facetracknoir.h"
#include "tracker.h"
#include <QtGui/QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QList>

#if defined(_WIN32)
#include <windows.h>
//#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")
#endif
int main(int argc, char** argv)
{
#if defined(_WIN32)
    (void) timeBeginPeriod(1);
#endif
    QApplication app(argc, argv);
    QFont font;
    font.setFamily(font.defaultFamily());
    font.setPointSize(9);
    app.setFont(font);
    FaceTrackNoIR w;
	//
	// Create the Main Window and DeskTop and Exec!
	//
	QDesktopWidget desktop;
    w.move(desktop.screenGeometry().width()/2-w.width()/2, 100);
	w.show();
    qApp->exec();

	return 0;
}

