#ifndef SOURCEMODEL_H
#define SOURCEMODEL_H

#include <QAbstractListModel>

class SourceModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SourceModel(QObject *parent = 0);

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
    QList<QHash<QString, QVariant> > getSources() const { return sources; }

private:
    QList<QHash<QString, QVariant> > sources;

};

#endif // SOURCEMODEL_H
