
#include "cleaner.h"

Cleaner::Cleaner(QObject *parent) : QObject(parent) {

}

/**
 * @brief Cleaner::applicationList
 * @return
 */
QVariant Cleaner::applicationList() {
	qDebug() << "C++_UPDATE_VALUES START";
	// Получаем список программ
	_listResults.clear();
	bool showHidden = false;
	QDir desktopDir(sPath_System);
	foreach (const QString &desktop, desktopDir.entryList(QStringList() << "*.desktop", QDir::Files, QDir::NoSort)) {
        MDesktopEntry entry(QString("%1/%2").arg(sPath_System).arg(desktop));
		QDateTime timestamp = QFileInfo(QString("%1/%2").arg(sPath_System).arg(desktop)).created();

		if (entry.isValid() && entry.type() == "Application") {
			if (!showHidden
					&& (entry.icon().isEmpty()
						|| entry.icon() == "icon-launcher-dummy"
						|| entry.noDisplay())) {
				continue;
			}

			QString appname = entry.exec().split("/").last().split(" ").at(0);
			//
			if (entry.exec().split("/").last().split(" ").at(0) == "sailfish-qml")
				appname = entry.exec().split("/").last().split(" ").at(1);
			else appname = entry.exec().split("/").last().split(" ").at(0);

			qDebug() << "Application: " + appname;
			_listResults.append(new ApplicationInfo(entry.name(),
													parseIconPath(entry.icon()),
													timestamp.toString("dd.MM.yyyy"),
													getSize_recurs("/usr/share/" + appname),
                                                    getSize_recurs(sPath_Cache +"/"+ appname),
                                                    appname,
                                                    checkRunApp(appname) ));
		}
	}
	qDebug() << "C++_UPDATE_VALUES STOP";
	return QVariant::fromValue(_listResults);
}


QString Cleaner::parseIconPath(const QString &path)
{
	if (path.isEmpty()) {
		return "";
	}
    else if (QFile(path).exists()) {
		return path;
	}
	else {
		return QString("image://theme/%1").arg(path);
	}
}


// -------------------------------------------------------------- //


/**
 * @brief Cleaner::removeCache
 * Function
 * @param uiAppID
 * @return
 */

bool Cleaner::removeCache(QString sAppName) {
	if (QDir(sPath_Cache + sAppName).exists()) {
		qDebug() << "REMOVE CACHE " + sAppName;
		clearDir(sPath_Cache + sAppName);
        emit applicationListChanged();
		return true;
	} else {
		qDebug() << "CACHE NOT FOUND " + sAppName;
		return false;
	}


}

bool Cleaner::removeConfig(QString sAppName) {
	if (QDir(sPath_Config + sAppName).exists()) {
		qDebug() << "REMOVE CONFIG " + sPath_Cache + sAppName;
		clearDir(sPath_Cache + sAppName);
        emit applicationListChanged();
		return true;
	} else {
		qDebug() << "CONFIG NOT FOUND " + sAppName;
		return false;
	}
}

bool Cleaner::stopApp(QString sAppName) {
	qDebug() << "STOP APP " + sAppName;
	QProcess p;
	p.start("killall " + sAppName);
	if (p.waitForFinished()) {
		if (p.exitCode() == 0) {
            emit applicationListChanged();
			return true;
		} else {
			return false;
		}
	}
    emit applicationListChanged();
}


bool Cleaner::checkRunApp(QString sAppName) {

	qDebug() << "CHECK APP RUNNING " + sAppName;
	//qDebug() << "ps -ef | grep \""+ sAppName +"\" | grep -v \"grep\" | wc -l";
	QProcess p;
	p.start(QString("/bin/bash -c \"ps -e | grep "+ sAppName +" | grep -v \"grep\" | wc -l"));
	if (p.waitForFinished()) {
		QByteArray result = p.readAll();

		qDebug() << "APP STATUS: " + result;

		if (result.contains('0')) {
			qDebug() << "APP INACTIVE";
			return false;
		}
		else {
			qDebug() << "APP ACTIVE";
			return true;
		}
	}
}



void Cleaner::openAppDetails(QString sAppName) {
	qDebug() << "OPEN APP DETAILS " + sAppName;

}

bool Cleaner::checkConfig(QString sAppName) {
	qDebug() << "Check configuration: " + sPath_Config + sAppName;
	QString sResult = getSize_recurs(sPath_Config + sAppName);
	if (sResult.isEmpty()) return false;
	else return true;
}


QString Cleaner::getSize_recurs(QString path) {
	//qDebug() << "Проверяем каталог: " + path;
	QProcess p;
	p.start("du -hs " + path);
	if (p.waitForFinished()) {
		QByteArray result = p.readAll();
		QString sResult = QString(result).split("\t").at(0);
		if (sResult.isEmpty()) sResult = tr("Empty");
		return sResult;
	}


}



void Cleaner::clearDir( const QString path ) {
	QDir dir( path + "/" );
	qDebug() << "Remove folder: " + path;
	dir.setFilter( QDir::NoDotAndDotDot | QDir::Files );
	foreach( QString dirItem, dir.entryList() )
		dir.remove( dirItem );
	dir.setFilter( QDir::NoDotAndDotDot | QDir::Dirs );
    foreach( QString dirItem, dir.entryList() ) {
		QDir subDir( dir.absoluteFilePath( dirItem ) );
		subDir.removeRecursively();
	}
	applicationList();
}

void Cleaner::updateList() {
	emit applicationListChanged();
}


