#ifndef CLEANER_H
#define CLEANER_H

#include <QObject>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QString>
#include <QStringList>
#include "applicationinfo.h"
#include <QRegExp>
#include <mlite5/MDesktopEntry>
#include <QFileInfo>
#include <QDateTime>
#include <QProcess>
#include <QDataStream>



class Cleaner : public QObject
{
    Q_OBJECT
		Q_PROPERTY(QVariant applicationList READ applicationList NOTIFY applicationListChanged)
public:
    explicit Cleaner(QObject *parent = 0);
	QVariant applicationList();
    QString sPath_System = "/usr/share/applications/";
    QString sPath_Cache = QString(QStandardPaths::standardLocations(QStandardPaths::GenericCacheLocation).at(0)) + "/";
    QString sPath_Config = QString(QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).at(0)) + "/";

private:

	QList<QObject*> _listResults;



	QString parseIconPath(const QString &path);
	QString getStatusApp(QString sAppName);
	QString getSize_recurs(QString path);

	void clearDir(const QString path);
	signals:
	void applicationListChanged();
	void finishOperations();

public slots:
	void updateList();
	bool removeCache(QString sAppName);
	bool removeConfig(QString sAppName);
	bool stopApp(QString sAppName);
	void openAppDetails(QString sAppName);
	bool checkConfig(QString sAppName);
	bool checkRunApp(QString sAppName);
};

#endif // CLEANER_H
