#include "mainwindow.h"

#include <QDBusArgument>
#include <QDebug>

#include "systemdunit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_sm(new SystemdManager("org.freedesktop.systemd1", "/org/freedesktop/systemd1", QDBusConnection::systemBus(), this))
{
    UnitFileList ufl = m_sm->ListUnitFiles();
    for (const UnitFile &uf : ufl) {
        if (uf.state == "enabled" || uf.state == "disabled") {
            SystemdUnit *su = new SystemdUnit(uf, this);
            qDebug() << su->getEnabled() << su->getRunning() << su->getDescription();
        }
    }
}

MainWindow::~MainWindow()
{

}
