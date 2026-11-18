/*
 *
 * ©K. D. Hedger. Sun 15 Nov 15:58:07 GMT 2026 keithdhedger@gmail.com

 * This file (functions.cpp) is part of KUTEGui.

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

#include "functions.h"

QWidget *setUpTag(const char* label)
{
	QWidget		*hbox;
	QHBoxLayout	*hlayout;

	entryBox eb;
	eb.noupdate=new QCheckBox("Static");
	eb.use=new QCheckBox(label);
	eb.tag=new QLineEdit;

	hbox=new QWidget;
	hlayout=new QHBoxLayout;	
	hlayout->setContentsMargins(0,0,0,0);
	hbox->setLayout(hlayout);
	hlayout->addWidget(eb.noupdate,1);
	hlayout->addWidget(eb.use,2);
	hlayout->addWidget(eb.tag,8);
	tags.append(eb);

	return(hbox);
}

void clearTags(void)
{
	for(auto te:tags)
		{
			if(te.noupdate->checkState()==Qt::Unchecked)
				te.tag->setText("");
		}
}

void setTags(void)
{
	QT_RunExternalProc	procs;
	QStringList			tsl=QStringList()<<QString("kute -q \"%1/%2\"").arg(folder.path()).arg(list->currentItem()->text());

	procs.readByLine=true;
	procs.connectCB([](QString msg)
		{
			QString tagdata=msg;
			QString tagname=msg;

			tagname.replace(QRegularExpression(R"RX((.*)="(.*)")RX"),"\\1");
			tagdata.replace(QRegularExpression(R"RX((.*)="(.*)")RX"),"\\2");
			for(int j=TITLE;j<NOMORETAGS;j++)
				{
					if(tagname==QString(tagNames[j]).toUpper())
						{
							if(tags.at(j).noupdate->checkState()==Qt::Unchecked)
								tags.at(j).tag->setText(tagdata);
						}
				}
		});
	procs.setCommands(tsl);
	procs.runCommands();
}

void writeTags(void)
{
	int			tagnum=0;
	QString	command;	
	QT_RunExternalProc	procs;

	QMessageBox::StandardButton ret=QMessageBox::warning(mainWindow,"Write Tags","Do you want to write these tags?",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel);

	if(ret==QMessageBox::Ok)
		{
			QString corrected;
			command="kute";

			status->showMessage(QString("Setting tags for %1/%2 ...").arg(folder.path()).arg(list->currentItem()->text()),0);
			status->repaint();
			for(entryBox eb:tags)
				{
					if(eb.use->checkState()==Qt::Checked)
						{
							corrected=eb.tag->text();
							corrected.replace("\"","\\\"");
							command+=QString(" %1=\"%2\"").arg(tagOpts[tagnum]).arg(corrected);
						}
					tagnum++;
				}
			command+=QString(" \"%1/%2\"").arg(folder.path()).arg(list->currentItem()->text());

			procs.setStdErrFileOption(stdErrOption::toFile,"/tmp/kutegui-error.log");
			procs.setCommands(QStringList()<<command);
			procs.runCommands();
			setTags();
		}
	status->clearMessage();
}

void writeAllTags(void)
{
	QString				corrected;
	QString				command;
	QT_RunExternalProc	procs;
	int					tagnum;

	QMessageBox::StandardButton ret=QMessageBox::warning(mainWindow,"Write Tags For All Files","Do you want to write all tags to all files?",QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel);

	if(ret==QMessageBox::Ok)
		{			
			for(int j=0;j<list->count();j++)
				{
					tagnum=0;
					command="kute";

					list->setCurrentItem(list->item(j));
					setTags();
					status->showMessage(QString("Setting tags for %1/%2 ...").arg(folder.path()).arg(list->currentItem()->text()),0);
					status->repaint();
					for(entryBox eb:tags)
						{
							if(eb.use->checkState()==Qt::Checked)
								{
									corrected=eb.tag->text();
									corrected.replace("\"","\\\"");
									command+=QString(" %1=\"%2\"").arg(tagOpts[tagnum]).arg(corrected);
								}
							tagnum++;
						}
					command+=QString(" \"%1/%2\"").arg(folder.path()).arg(list->currentItem()->text());

					procs.setStdErrFileOption(stdErrOption::toFile,"/tmp/kutegui-error.log");
					procs.setCommands(QStringList()<<command);
					procs.runCommands();
				}
		}
	list->setCurrentItem(list->item(0));
	setTags();
	status->clearMessage();	
}

void selectAllTags(void)
{
	for(entryBox te:tags)
		{
			te.use->setCheckState(Qt::Checked);
		}
}

void deSelectAllTags(void)
{
	for(entryBox te:tags)
		{
			te.use->setCheckState(Qt::Unchecked);
		}
}

QMenu* setHelpMenu(void)
{
	QActionGroup		*actions;
	QAction			*act;
	QMenu			*menu;

	menu=mainWindow->menuBar()->addMenu("&Help");

	actions=new QActionGroup(menu);
	actions->setExclusive(true);

	act=new QAction(QIcon::fromTheme("help-about"),"About",actions);
	act->setData(ABOUTITEM);

	act=new QAction(QIcon::fromTheme("help-contents"),"Help",actions);
	act->setData(HELPITEM);

	act=new QAction(actions);
	act->setSeparator(true);

	menu->addActions(actions->actions());
	QObject::connect(actions,&QActionGroup::triggered,actions,[&](QAction *action)
		{
			switch(action->data().toInt())
				{
					case ABOUTITEM:
						{
							AboutBoxClass	about(qApp->activeWindow(),QString("%1/pixmaps/KUTEGui.png").arg(DATADIR));
							QFile			file(QString("%1/docs/gpl-3.0.txt").arg(DATADIR));
							if(file.open(QIODevice::ReadOnly | QIODevice::Text))
								{
									QTextStream in(&file);
									about.licence=in.readAll();
									file.close();
								}
							about.credits=credits;

							about.hpLabel->setText(QString("%1<br>%2<br>%3").arg("<a href=\"https://github.com/KeithDHedger/Kute\">K.U.T.E.</a>").arg("<a href=\"https://github.com/KeithDHedger/KuteGui\">K.U.T.E.Gui</a>").arg("<a href=\"https://keithdhedger.github.io/\">Homepage</a>"));

							about.setBodyText("A GUI Frontend for K.U.T.E");
							about.showAboutQtButton(true);
							about.showLicenceButton(true);
							about.showCreditsButton(true);

							about.runAbout();
						}
						break;

					case HELPITEM:
						{
							AboutBoxClass::showHelp(QString("%1/docs/help/help.html").arg(DATADIR));
						}
						break;
				}
		});
	return(menu);
}