/*
 *
 * ©K. D. Hedger. Mon 16 Nov 13:43:47 GMT 2026 keithdhedger@gmail.com

 * This file (main.cpp) is part of KUTEGui.

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

#include "config.h"
#include "globals.h"

int main(int argv, char **args)
{
	int			retval;
	QSettings	prefs("KDHedger",PACKAGE_NAME);
	QApplication	app(argv,args);
	QVBoxLayout	*vbox=NULL;
	QWidget		*hbox;
	QWidget		*centre;
	QMenuBar		*mbar;
	QAction		*act;
	QToolBar		*toolbar;
	QWidget		*stretchwidg;

	if(QProcess::execute("sh",QStringList()<<"-c"<<"which kute 2>&1 >/dev/null")==1)
		{
			qDebug()<<"Can't find KUTE in your $PATH, it can be found here: https://github.com/KeithDHedger/Kute";
			return(1);
		}
 	app.setOrganizationDomain("KDHedger");
	app.setApplicationName("K.U.T.E. Gui");
	app.setApplicationVersion(PACKAGE_VERSION);

	QIcon::setThemeSearchPaths(QStringList()<<QString("%1/icons").arg(DATADIR)<<QString("/usr/share/icons")<<QString("%1/.icons").arg(getenv("HOME")));
	QIcon::setFallbackSearchPaths(QStringList()<<QString("%1/icons").arg(DATADIR)<<QString("/usr/share/icons")<<QString("%1/.icons").arg(getenv("HOME")));
	QIcon::setFallbackThemeName("kuteguiicons");

	mainWindow=new QMainWindow;
	centre=new QWidget;
	vbox=new QVBoxLayout(centre);

	folderPath=prefs.value("app/lastfolder").toString();
	folder.setPath(folderPath);
	mbar=mainWindow->menuBar();
	toolbar=new QToolBar(mainWindow);
	mainWindow->addToolBar(toolbar);

	fileMenu=mbar->addMenu("&File");
	tagMenu=mbar->addMenu("&Tags");
	setHelpMenu();

	act=fileMenu->addAction(QIcon::fromTheme("document-open"),"Open File");
	toolbar->addAction(act);
	QObject::connect(act,&QAction::triggered,[&prefs](bool checked)
		{
			folderPath=QFileDialog::getOpenFileName(mainWindow,"Select File ...",folder.path(),("Images (*.mp3 *.m4a *.flac *.mp4)"));
			prefs.setValue("app/lastfolder",folder.path());
			list->clear();
			clearTags();
			
			list->addItem(QFileInfo(folderPath).fileName());
			folder.setPath(QFileInfo(folderPath).path());
			if(list->count()>0)
				{
					list->setCurrentRow(0,QItemSelectionModel::Current);
					setTags();
				}
		});

	act=fileMenu->addAction(QIcon::fromTheme("folder-open"),"Open Folder");
	toolbar->addAction(act);
	QObject::connect(act,&QAction::triggered,[&prefs](bool checked)
		{
			folderPath=QFileDialog::getExistingDirectory(mainWindow,"Select Folder ...",folder.path());
			folder.setPath(folderPath);
			prefs.setValue("app/lastfolder",folder.path());
			list->clear();
			clearTags();
			list->addItems(folder.entryList(QStringList()<<"*.flac"<<"*.mp3"<<"*.mp4"<<"*.m4a",QDir::Files | QDir::NoDotAndDotDot,QDir::Name));
			if(list->count()>0)
				{
					list->setCurrentItem(list->item(0));
					setTags();
				}
		});

	toolbar->addSeparator();
	fileMenu->addSeparator();
	act=fileMenu->addAction(QIcon::fromTheme("edit-copy"),"Copy Tags to Clipboard");
	toolbar->addAction(act);
	QObject::connect(act,&QAction::triggered,[](bool checked)
		{
			QString	data;
			int		tagnum=0;

			for(entryBox eb:tags)
				{
					data+=QString("%1=\"%2\"\n").arg(tagNames[tagnum]).arg(eb.tag->text());
					tagnum++;
				}

			qApp->clipboard()->setText(data);
		});

	toolbar->addSeparator();

	act=tagMenu->addAction(QIcon::fromTheme("document-save"),"Write Tags For File");
	toolbar->addAction(act);
	QObject::connect(act,&QAction::triggered,[](bool checked)
		{
			writeTags();
		});

	act=tagMenu->addAction(QIcon::fromTheme("document-save"),"Write Tags For All Files");
	toolbar->addAction(act);
	QObject::connect(act,&QAction::triggered,[](bool checked)
		{
			writeAllTags();
		});

	toolbar->addSeparator();
	act=tagMenu->addAction(QIcon::fromTheme("edit-select-all"),"Select All Tags");
	toolbar->addAction(act);
	QObject::connect(act,&QAction::triggered,[](bool checked)
		{
			selectAllTags();
		});

	act=tagMenu->addAction(QIcon::fromTheme("edit-clear"),"De-Select All Tags");
	toolbar->addAction(act);
	QObject::connect(act,&QAction::triggered,[](bool checked)
		{
			deSelectAllTags();
		});

	stretchwidg=new QWidget(toolbar);
	stretchwidg->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
	toolbar->addWidget(stretchwidg);

	fileMenu->addSeparator();
	act=fileMenu->addAction(QIcon::fromTheme("application-exit"),"Quit");
	toolbar->addSeparator();
	toolbar->addAction(act);
	QObject::connect(act,&QAction::triggered,[](bool checked)
		{
			qApp->quit();
		});

	for(int j=TITLE;j<NOMORETAGS;j++)
		{
			hbox=setUpTag(tagNames[j]);
			vbox->addWidget(hbox);
		}

	list=new QListWidget;
	list->addItems(folder.entryList(QStringList()<<"*.flac"<<"*.mp3"<<"*.mp4"<<"*.m4a",QDir::Files | QDir::NoDotAndDotDot,QDir::Name));
	list->setContextMenuPolicy(Qt::CustomContextMenu);
	QObject::connect(list, &QListWidget::customContextMenuRequested,[](const QPoint &pos)
		{
			QListWidgetItem	*item=list->itemAt(pos);
			if(item!=NULL)
				{
					QMenu	menu;
					QAction	*act=menu.addAction(QIcon::fromTheme("edit-copy"),"Copy Name");
					QObject::connect(act,&QAction::triggered,[item]()
						{
							qApp->clipboard()->setText(item->text());
						});
					act=menu.addAction(QIcon::fromTheme("edit-copy"),"Copy Path");
					QObject::connect(act,&QAction::triggered,[item]()
						{
							qApp->clipboard()->setText(folder.path()+"/"+item->text());
						});

					menu.exec(list->mapToGlobal(pos));
				}
		});

	if(list->count()>0)
		{
			list->setCurrentItem(list->item(0));
			setTags();
		}
	QObject::connect(list,&QListWidget::itemClicked,[](QListWidgetItem *item)
		{
			setTags();
        });
	QObject::connect(list,&QListWidget::itemSelectionChanged,[]()
		{
			setTags();
        });

	 vbox->addWidget(list);

	status=new QStatusBar;
	status->setSizeGripEnabled(false);
	vbox->addWidget(status);

	mainWindow->setCentralWidget(centre);
	selectAllTags();

	if(prefs.contains("app/geometry"))
		mainWindow->restoreGeometry(prefs.value("app/geometry").toByteArray());
	else
		mainWindow->setGeometry(100,100,600,480);

	mainWindow->show();
	retval=app.exec();

	prefs.setValue("app/geometry",mainWindow->saveGeometry());
	prefs.setValue("app/lastfolder",folder.path());

	delete mainWindow;

	return(retval);
}