#ifndef SYSTEMDUNIT_H
#define SYSTEMDUNIT_H

#include <QObject>

#include "dbus/types.h"

class SystemdUnit : public QObject
{
    Q_OBJECT
public:
    SystemdUnit(const UnitFile &uf, QObject *parent = Q_NULLPTR);

    QString getDescription() const;
    void setDescription(const QString &value);

    bool getRunning() const;
    void setRunning(bool value);

    bool getEnabled() const;
    void setEnabled(bool value);

private:
    bool m_enabled;
    bool m_running;
    QString m_path;
    QString m_description;

    void parseStatus(const QString &output);
};

#endif // SYSTEMDUNIT_H
