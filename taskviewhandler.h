/*
    Copyright (c) 2011 Carlos López Sánchez <musikolo{AT}hotmail[DOT]com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TASKVIEWHANDLER_H
#define TASKVIEWHANDLER_H

#include <QList>
#include <QTableWidget>
#include <KMenu>
#include <KAction>
#include <QTimer>

#include "reportviewhandler.h"
#include "taskrowviewhandler.h"

class MainWindow;

namespace RowSelection {
	enum RowSelectionEnum { ALL, FINISHED, UNFINISHED };
}

class TaskViewHandler : public QObject
{
Q_OBJECT
private:
	MainWindow* mainwindow;
	QTableWidget* tableWidget;
	ReportViewHandler* reportViewHandler;
	QList< TaskRowViewHandler* > rowViewHandlers;
	QTimer* timer;
	KMenu* ctxMenu;

    void setupObject( QTableWidget* reportTableWidget );
    void setupContextMenu();
	bool hasDuplicateUnfinished( const QString& item );
	void prepareTable();
	void addRow2Timer( TaskRowViewHandler * rowViewHandler );
	void writeSelectedRowIndexes( QSet< int >& rowIds, RowSelection::RowSelectionEnum selection = RowSelection::ALL );

public:
    TaskViewHandler( MainWindow* mainwindow, QTableWidget* taskTableWidget, QTableWidget* reportTableWidget );
    virtual ~TaskViewHandler();
	
	inline QTableWidget* getTableWidget(){ return this->tableWidget; }
	bool isUnfinishedTasks() ;
	void showFileTooBigMsg( const QString& msg );

private slots:
	void removeSelectedRows();
	void selectedRowChanged();
	void removeRow( int rowIndex );
	void selectRow( int rowIndex );
	void reportCompleted( int rowIndex );
	void showContextMenu( const QPoint& point );

public slots:
	void removeRow2Timer( TaskRowViewHandler * rowViewHandler );
	void submitFile( const QFile& file );
	void submitRemoteFile( QNetworkAccessManager*const networkManager, const QUrl& url );
	void submitUrl( const QUrl& url );
	void abortSelectedTask();
	void clearFinishedRows();
	void rescanTasks();
	void tableWidthChanged( int width );
	void selectAll();
	void invertSelection();
};

#endif // TASKVIEWHANDLER_H