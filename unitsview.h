#ifndef UNITSVIEW_H
#define UNITSVIEW_H

#include <QTableView>

class UnitsView : public QTableView
{
    Q_OBJECT

public:
    explicit UnitsView(QWidget *parent = 0);

signals:
    void currentIndexChanged(const QModelIndex &idx) const;

private:
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
};

#endif // UNITSVIEW_H
