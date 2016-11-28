#ifndef APPLICATIONINFO_H
#define APPLICATIONINFO_H

#include <QObject>

class ApplicationInfo : public QObject
{
		Q_OBJECT
    Q_PROPERTY(QString Name READ Name NOTIFY NameChanged)
    Q_PROPERTY(QString IconPath READ IconPath NOTIFY IconPathChanged)
    Q_PROPERTY(QString Path READ Path NOTIFY PathChanged)
    Q_PROPERTY(bool isRunning READ isRunning NOTIFY isRunningChanged)
    Q_PROPERTY(QString AppSize READ AppSize NOTIFY AppSizeChanged)
    Q_PROPERTY(QString CacheSize READ CacheSize NOTIFY CacheSizeChanged)
    Q_PROPERTY(QString DateCreate READ DateCreate NOTIFY DateCreateChanged)

	public:
		explicit ApplicationInfo(QObject *parent = 0);
		// Пока так. Потом причешем и расчешем. Никто ж не увидит :)
        ApplicationInfo(QString title, QString iconpath, QString timestamp,
                        QString sizeApp, QString sizeCache, QString SystemName, bool bAppRun);
	signals:
        void NameChanged();
        void IconPathChanged();
        void PathChanged();
        void isRunningChanged();
        void AppSizeChanged();
        void CacheSizeChanged();
        void DateCreateChanged();

	public slots:
		QString Path() { return _path; }
		QString Name() { return _name; }
		bool isRunning() { return _isrunning; }
		QString IconPath() { return _iconpath; }

		QString AppSize(){ return _app_size_bytes; }
		QString CacheSize(){ return _cache_size_bytes; }
		QString DateCreate() { return _date_create; }


	private:
		QString _name;
		QString _iconpath;
		bool _isrunning;
		QString _path;


		QString _app_size_bytes;
		QString _cache_size_bytes;
		QString _date_create;

};

#endif // APPLICATIONINFO_H
