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

#ifndef WEBFILEREPORT_H
#define WEBFILEREPORT_H

#include "base/basefilereport.h"
#include "filehasher.h"
#include "servicereply.h"

class WebFileReport : public BaseFileReport
{
private:
	FileHasher* hasher;

protected:
	void processReply( const ServiceReply*const reply );

public:
	WebFileReport( const ServiceReply*const reply, const QString& fileName, FileHasher*const hasher = NULL );;
    virtual ~WebFileReport();
	
	virtual void setPermanentLink( const QUrl& permanentLink );
    virtual QString getSha256Sum() const;
    virtual QString getSha1Sum() const;
    virtual QString getMd5Sum() const;
};

#endif // WEBFILEREPORT_H