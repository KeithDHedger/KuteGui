/*
 *
 * ©K. D. Hedger. Sun 15 Nov 15:58:30 GMT 2026 keithdhedger@gmail.com

 * This file (functions.h) is part of KUTEGui.

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

#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include "globals.h"

QWidget *setUpTag(const char* label);
void clearTags(void);
void setTags(void);
void writeTags(void);
void selectAllTags(void);
void deSelectAllTags(void);
void writeAllTags(void);
QMenu* setHelpMenu(void);

#endif
