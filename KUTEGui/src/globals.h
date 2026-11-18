/*
 *
 * ©K. D. Hedger. Sun 15 Nov 15:59:02 GMT 2026 keithdhedger@gmail.com

 * This file (globals.h) is part of KUTEGui.

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

#ifndef _GLOBALS_
#define _GLOBALS_


#define QUITITEM 500
#define ABOUTITEM 600
#define ABOUTQTITEM 601
#define HELPITEM 602

#include <QtWidgets>

#include "QT_AboutBox.h"
#include "QT_RunExternalProc.h"
#include "functions.h"

struct entryBox
{
	QCheckBox	*noupdate;
	QCheckBox	*use;
	QLineEdit	*tag;
};

enum {TITLE=0,ARTIST,ALBUM,TRACK,TOTALTRACKS,CD,GENRE,YEAR,COMPILATION,COMPOSER,COMMENT,DISCID,NOMORETAGS};

extern const char		*tagNames[];
extern const char		*tagOpts[];
extern QVector<entryBox>	tags;
extern QMainWindow		*mainWindow;
extern QMenu				*fileMenu;
extern QMenu				*tagMenu;
extern QListWidget		*list;
extern QStatusBar		*status;
extern QString			folderPath;
extern QDir				folder;
extern QString			path;

#endif
