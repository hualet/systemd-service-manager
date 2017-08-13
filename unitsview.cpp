#include "unitsview.h"

#include <QDebug>
#include <QHeaderView>

UnitsView::UnitsView(QWidget *parent)
    : QTableView(parent)
{
    setSelectionMode(QTableView::SingleSelection);
}

void UnitsView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    if (current.isValid())
        emit currentIndexChanged(current);
}
