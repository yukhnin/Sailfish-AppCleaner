#ifndef PROCESS_H
#define PROCESS_H

#include <QObject>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <QDir>
#include <QSettings>
#include <QDebug>

class Process : public QAbstractListModel
	{
		Q_OBJECT

	public:
		enum ProcessRoles {
			PIDRole = Qt::UserRole + 1,
			NameRole,
			CPUUsageRole,
			MemoryUsageRole
		};

		explicit Process(QObject *parent = 0);

		QHash<int, QByteArray> roleNames() const;
		Qt::ItemFlags flags(const QModelIndex & index) const;
		QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
		int rowCount(const QModelIndex & parent = QModelIndex()) const;
		int getSortBy() const;
		int getSummaryValue() const;
		bool getApplicationsOnly() const;
		int getSelectedPID() const;
		void selectPID(int pid);
		Q_INVOKABLE bool isKillable() const;
		Q_INVOKABLE void setSortBy(int sb);
		Q_INVOKABLE void nextApplicationsOnly();
		Q_INVOKABLE int killSelected();
	private:
		uid_t fUID;
		int fSortBy;
		int fSelectedPID;
		int fSelectedTick;
		const ProcMap* fProcMap;
		PIDList fProcKeys;
		PIDList fAppKeys;
		bool fApplicationsOnly;
		int fPageStatus;
		bool fApplicationActive;
		int fProcCount;
		bool fPauseUpdates;

		void removeKeys(const PIDList &deletes, PIDList& list, bool really);
		void appendKeys(const PIDList &adds, PIDList& list, bool really, bool appsOnly);
		void sort(PIDList& list);
		const PIDList& getKeys() const;
		const BaseComparer* getComparer() const;
		void beginRR(bool really, int first, int last);
		void endRR(bool really);
		void beginIR(bool really, int first, int last);
		void endIR(bool really);

		const QString getSelectedName() const;
		int getSelectedCPUUsage() const;
		int getSelectedMemoryUsage() const;
		int getSelectedTick() const;
	signals:
		void summaryValueChanged();
		void sortByChanged();
		void selectedPIDChanged();
		void applicationsOnlyChanged();
		void selectedChanged();
	public slots:
		void setProcesses(const ProcMap* procMap, const PIDList& adds, const PIDList& deletes);
		void setProcessCount(int count);
};

#endif // PROCESS_H
