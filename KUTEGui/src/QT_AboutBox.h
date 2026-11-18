/*
 *
 * ©K. D. Hedger. Tue 17 Nov 13:51:55 GMT 2026 keithdhedger@gmail.com

 * This file (QT_AboutBox.h) is part of KUTEGui.

 * KUTEGui is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * KUTEGui is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with KUTEGui.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "globals.h"
#include "credits.h"

#ifndef _QT_ABOUTBOX_
#define _QT_ABOUTBOX_

class AboutBoxClass : public QObject
{
	public:
		AboutBoxClass(QWidget *window,QString pixpath=NULL);
		~AboutBoxClass();

		QString		licence;
		QString		credits;

		void			runAbout(void);
		void			setHomepage(QString hpaddr,QString hpstr);
		void			setBodyText(QString bodystr);
		void			showAboutQtButton(bool show=false);
		void			showLicenceButton(bool show=false);
		void			showCreditsButton(bool show=false);
		static void	showHelp(QString htmlpath);
		QLabel		*hpLabel;

	private:
		QDialog		*aboutDialog;
		QDialog		*licenceDialog;
		QDialog		*creditsDialog;
		QLabel		*bodyLabel;
		QLabel		*appNameLabel;
		QPushButton	*aboutQtButton;
		QPushButton	*licenseButton;
		QPushButton	*creditsButton;

		void			setAppName(void);
		void			showLicence(void);
		void			showCredits(void);
		void			killLicenceBox(void);
		void			killAboutBox(void);
		void			killCreditsBox(void);
};

#endif
