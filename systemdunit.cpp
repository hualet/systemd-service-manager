#include "systemdunit.h"

SystemdUnit::SystemdUnit(const UnitFile &uf, QObject *parent)
    : QObject(parent),
      m_path(uf.path),
      m_enabled(uf.state == "enabled")
{
    const QString basename = m_path.split("/").last();

    QStringList args;
    args << "status" << basename;

    QProcess process;
    process.setProgram("systemctl");
    process.setArguments(args);
    process.start();
    process.waitForFinished();

    parseStatus(process.readAllStandardOutput());
}

QString SystemdUnit::getDescription() const
{
    return m_description;
}

void SystemdUnit::setDescription(const QString &value)
{
    m_description = value;
}

bool SystemdUnit::getRunning() const
{
    return m_running;
}

void SystemdUnit::setRunning(bool value)
{
    m_running = value;
}

bool SystemdUnit::getEnabled() const
{
    return m_enabled;
}

void SystemdUnit::setEnabled(bool value)
{
    m_enabled = value;
}

void SystemdUnit::parseStatus(const QString &output)
{
    const QString firstLine = output.split("\n").first();
    const QString description = firstLine.split("-").last();
    m_description = description.trimmed();

    QRegularExpression runningExp("Active: active");
    m_running = output.contains(runningExp);
}
