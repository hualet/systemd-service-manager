#ifndef UNITSLISTMODEL_H
#define UNITSLISTMODEL_H

#include "dbus/systemdmanager.h"
#include "systemdunit.h"

#include <QAbstractTableModel>

class UnitsListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum UnitsInfoRole
    {
        UnitNameRole = Qt::DisplayRole,
        UnitStatRole = Qt::UserRole,
        UnitPathRole,
        UnitRunningRole,
        UnitBaseNameRole,
    };

    explicit UnitsListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

public slots:
    void reload();

private:
    const QString cellData(const int r, const int c) const;

private:
    SystemdManager *m_systemdMgr;
    UnitFileList m_unitFiles;
    QList<SystemdUnit *> m_unitInfos;
};

#endif // UNITSLISTMODEL_H
