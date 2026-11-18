/*
 *
 * ©K. D. Hedger. Sun 15 Nov 15:59:11 GMT 2026 keithdhedger@gmail.com

 * This file (globals.cpp) is part of KUTEGui.

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

const char *tagNames[]={"Title","Artist","Album","Track","Totaltracks","CD","Genre","Year","Compilation","Composer","Comment","Discid"};
const char *tagOpts[]={"--title","--artist","--album","--track","--total-tracks","--cd","--genre","--year","--compilation","--composer","--comment","--discid"};

QMainWindow			*mainWindow=NULL;
QVector<entryBox>	tags;
QMenu				*fileMenu;
QMenu				*tagMenu;
QListWidget			*list;
QStatusBar			*status;
QString				folderPath="";
QDir					folder;
QString				path;