#ifndef MODULEMODEL_H
#define MODULEMODEL_H

#include <QAbstractListModel>

class ModuleModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ModuleModel(QObject *parent = 0);

// QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

public:
    QList<QHash<QString, QVariant> > getModules() const { return modules; }

private:
    QList<QHash<QString, QVariant> > modules;

};

#endif // MODULEMODEL_H
