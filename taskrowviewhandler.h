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

#ifndef TASKROWVIEWHANDLER_H
#define TASKROWVIEWHANDLER_H

#include <QFile>

#include "core/report.h"
#include "httpconnector.h"
#include "httpconnectorlistener.h"
#include "taskschedulerjob.h"

class TaskViewHandler;

namespace Column {
	enum ColumnEnum { TYPE, NAME, SIZE, STATUS, TIME };
}

class TaskRowViewHandler : public HttpConnectorListener
{
Q_OBJECT
private:
    TaskViewHandler* viewHandler;
	Report* report;
    int rowIndex;
    int seconds;
	int startUploadSeconds;
	bool finished;
	uint jobId;

    void setType( const QString& type);
    void setName( const QString& name );
    void setSize( qint64 size );
    void setStatus( const QString& status, const QString& toolTip = QString() );
    void setTime( int seconds );
	void setReport( Report*const report );
    void addRowItem(int column, const QString& text, const QString& toolTip = QString() );
    void setupObject( TaskViewHandler* viewHandler, int rowIndex, const QString& type, const QString& name, int size, JobType::JobTypeEnum jobType );

protected slots:
	void onQueued();
    void onScanningStarted();
    void onErrorOccurred( const QString& message );
	void onUploadProgressRate( qint64 bytesSent, qint64 bytesTotal );
	void onRetrievingReport();
	void onWaitingForReport( int seconds );
	void onServiceLimitReached( int seconds );
	void onAborted();
	void onReportReady( Report*const report );
    QString getItemText( Column::ColumnEnum column ) const;

public slots:
	void nextSecond();

signals:
	void reportCompleted( int rowIndex );
	void unsubscribeNextSecond( TaskRowViewHandler* );
	void rowRemoved( int rowIndex );

public:
	TaskRowViewHandler( TaskViewHandler* viewHandler, int rowIndex, const QFile& file );
	TaskRowViewHandler( TaskViewHandler* viewHandler, int rowIndex, const QUrl& url );
	virtual ~TaskRowViewHandler();
	void setRowIndex( int index );
	QString getName() const;
	bool isFinished() { return finished; }
	static int getHintColumnSize( int column, int availableWidth );
    Report* getReport() const;
	bool abort();
	bool rescan();
};

#endif // TASKROWVIEWHANDLER_H