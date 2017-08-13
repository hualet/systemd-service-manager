#include "unitslistmodel.h"

UnitsListModel::UnitsListModel(QObject *parent)
    : QAbstractTableModel(parent),

    m_systemdMgr(new SystemdManager("org.freedesktop.systemd1", "/org/freedesktop/systemd1", QDBusConnection::systemBus(), this))
{
    QTimer::singleShot(1, this, &UnitsListModel::reload);
}

int UnitsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_unitFiles.size();
}

int UnitsListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return 3;
}

QVariant UnitsListModel::data(const QModelIndex &index, int role) const
{
    const int r = index.row();

    switch (role)
    {
    case UnitNameRole:
        return cellData(index.row(), index.column());
    case UnitPathRole:
        return m_unitFiles[r].path;
    case UnitStatRole:
        return m_unitFiles[r].state;
    case UnitRunningRole:
        return m_unitInfos[r]->getRunning();
    case UnitBaseNameRole:
        return m_unitFiles[r].path.split('/').last();
    }

    return QVariant();
}

QVariant UnitsListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case 0:     return "路径";
        case 1:     return "运行状态";
        case 2:     return "自动启动";
        default:;
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

void UnitsListModel::reload()
{
    m_unitFiles.clear();
    m_unitInfos.clear();
    const auto list = m_systemdMgr->ListUnitFiles();
    for (const auto &u : list.value())
    {
        if (u.state != "enabled" && u.state != "disabled")
            continue;

        m_unitFiles << u;
    }

    std::sort(m_unitFiles.begin(), m_unitFiles.end(), [](const UnitFile &u1, const UnitFile& u2) {
        return u1.path < u2.path;
    });

    for (const auto &u : m_unitFiles)
        m_unitInfos << new SystemdUnit(u);

    emit layoutChanged();
}

const QString UnitsListModel::cellData(const int r, const int c) const
{
    switch (c)
    {
    case 0:     return m_unitFiles[r].path;
    case 1:     return m_unitInfos[r]->getRunning() ? "正在运行" : "未启动";
    case 2:     return m_unitFiles[r].state == "enabled" ? "是" : "否";
    }

    return QString();
}
