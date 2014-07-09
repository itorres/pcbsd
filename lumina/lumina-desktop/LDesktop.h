//===========================================
//  Lumina-DE source code
//  Copyright (c) 2012, Ken Moore
//  Available under the 3-clause BSD license
//  See the LICENSE file for full details
//===========================================
#ifndef _LUMINA_DESKTOP_LDESKTOP_H
#define _LUMINA_DESKTOP_LDESKTOP_H

#include <QCoreApplication>


#include <QSettings>
#include <QFile>
#include <QList>
#include <QDebug>
#include <QTimer>
#include <QFileSystemWatcher>
#include <QLabel>
#include <QWidgetAction>
#include <QMdiArea>
#include <QMdiSubWindow>


#include <LuminaXDG.h>

#include "LPanel.h"
#include "Globals.h"
#include "LSession.h"
#include "desktop-plugins/LDPlugin.h"
#include "desktop-plugins/LDPluginContainer.h"
#include "desktop-plugins/NewDP.h"

class LDesktop : public QObject{
	Q_OBJECT
public:
	LDesktop(int deskNum=0);
	~LDesktop();
	
public slots:
	void SystemLogout(){ LSession::systemWindow(); }
	void SystemTerminal();
	void SystemFileManager();
	void SystemApplication(QAction*);
	
private:
	QSettings *settings;
	QTimer *bgtimer;
	QDesktopWidget *desktop;
	QString DPREFIX;
	int desktopnumber;
	int xoffset;
	bool defaultdesktop, desktoplocked, changingsettings;
	QList<LPanel*> PANELS;
	QMdiArea *bgDesktop; //desktop widget area
	QWidget *bgWindow; //full screen background
	QMenu *deskMenu;
	AppMenu *appmenu;
	QLabel *workspacelabel;
	QWidgetAction *wkspaceact;
	QList<LDPlugin*> PLUGINS;
	QFileSystemWatcher *watcher;
	QString CBG; //current background
	
	void CreateDesktopPluginContainer(LDPlugin*);

private slots:
	void SettingsChanged();
	void UpdateMenu(bool fast = false);
	void ShowMenu(){
	  UpdateMenu(true); //run the fast version
	  deskMenu->popup(QCursor::pos());
	}
	
	void UpdateDesktop();
	void ToggleDesktopLock();
	
	void UpdatePanels();
	
	void UpdateDesktopPluginArea();

	void UpdateBackground();

};
#endif
