#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "dbus/systemdmanager.h"
#include "unitsview.h"

class UnitsListModel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onCurrentIndexChanged(const QModelIndex &currentIdx);

private:
    void updateCurrentUnitStat();

    void exec(const QString &cmd);
    void editStartLevel();

private:
    UnitsView *m_unitsView;
    UnitsListModel *m_unitsModel;
    QModelIndex m_currentIdx;

    // control btns
    QPushButton *m_start;
    QPushButton *m_stop;
    QPushButton *m_restart;
    QPushButton *m_enable;
    QPushButton *m_disable;
    QPushButton *m_edit;
};

#endif // MAINWINDOW_H
