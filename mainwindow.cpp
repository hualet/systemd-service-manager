#include "mainwindow.h"

#include <QDBusArgument>
#include <QDebug>
#include <QVBoxLayout>
#include <QHeaderView>

#include "systemdunit.h"
#include "unitslistmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_start = new QPushButton("启动");
    m_stop = new QPushButton("停止");
    m_restart = new QPushButton("重新启动");
    m_disable = new QPushButton("禁用自动启动");
    m_enable = new QPushButton("启用自动启动");
    m_edit = new QPushButton("编辑启动级别");

    QHBoxLayout *controlBtnsLayout = new QHBoxLayout;
    controlBtnsLayout->addWidget(m_start);
    controlBtnsLayout->addWidget(m_stop);
    controlBtnsLayout->addWidget(m_restart);
    controlBtnsLayout->addWidget(m_disable);
    controlBtnsLayout->addWidget(m_enable);
    controlBtnsLayout->addWidget(m_edit);

    m_unitsModel = new UnitsListModel;
    m_unitsView = new UnitsView;
    m_unitsView->setModel(m_unitsModel);
    m_unitsView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(m_unitsView);
    centralLayout->addLayout(controlBtnsLayout);

    resize(800, 600);
    setCentralWidget(new QWidget);
    centralWidget()->setLayout(centralLayout);

    connect(m_unitsView, &UnitsView::currentIndexChanged, this, &MainWindow::onCurrentIndexChanged);
    connect(m_unitsModel, &UnitsListModel::layoutChanged, this, &MainWindow::updateCurrentUnitStat, Qt::QueuedConnection);
    connect(m_start, &QPushButton::clicked, this, [=] { exec("systemctl start %1"); });
    connect(m_stop, &QPushButton::clicked, this, [=] { exec("systemctl stop %1"); });
    connect(m_restart, &QPushButton::clicked, this, [=] { exec("systemctl restart %1"); });
    connect(m_enable, &QPushButton::clicked, this, [=] { exec("systemctl enable %1"); });
    connect(m_disable, &QPushButton::clicked, this, [=] { exec("systemctl disable %1"); });
    connect(m_edit, &QPushButton::clicked, this, &MainWindow::editStartLevel);

    QTimer::singleShot(100, this, [=] { m_unitsView->setCurrentIndex(m_unitsModel->index(0, 0)); });
}

MainWindow::~MainWindow()
{

}

void MainWindow::onCurrentIndexChanged(const QModelIndex &currentIdx)
{
    m_currentIdx = currentIdx;

    updateCurrentUnitStat();
}

void MainWindow::updateCurrentUnitStat()
{
    const QString &stat = m_currentIdx.data(UnitsListModel::UnitStatRole).toString();
    const bool enabled = stat == "enabled";
    const bool running = m_currentIdx.data(UnitsListModel::UnitRunningRole).toBool();

    m_enable->setVisible(!enabled);
    m_disable->setVisible(enabled);
    m_start->setVisible(!running);
    m_stop->setVisible(running);
    m_restart->setVisible(running);
}

void MainWindow::exec(const QString &cmd)
{
    Q_ASSERT(m_currentIdx.isValid());

    const QString &name = m_currentIdx.data(UnitsListModel::UnitBaseNameRole).toString();

    QProcess p;
    p.start("pkexec " + cmd.arg(name));
    p.waitForFinished();

    m_unitsModel->reload();
}

void MainWindow::editStartLevel()
{
    QProcess::startDetached("gksu dde-runlevel " + m_currentIdx.data(UnitsListModel::UnitPathRole).toString());
}
