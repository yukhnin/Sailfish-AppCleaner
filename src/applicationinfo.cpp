#include "applicationinfo.h"

ApplicationInfo::ApplicationInfo(QObject *parent) : QObject(parent){}

ApplicationInfo::ApplicationInfo(QString nameApp,
		QString iconpath,
		QString timestamp,
		QString sizeApp,
        QString sizeCache,
        QString SystemName,
        bool bAppRun)
{
	_name = nameApp;
    _isrunning = bAppRun;
	_iconpath = iconpath;
	_path = SystemName;

	_app_size_bytes = sizeApp;
	_cache_size_bytes = sizeCache;
	_date_create = timestamp;
}
