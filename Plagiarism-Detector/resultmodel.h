#ifndef RESULTMODEL_H
#define RESULTMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "treenode.h"
#include "moduleresultwrapper.h"

class ResultModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ResultModel(QList<ModuleResultWrapper> results, int matrixSize, QObject *parent = 0);
    ~ResultModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    QModelIndex tableIndexForRow(int row);

private:

    TreeNode *root;
    int matrixSize;

    void initialize(QList<ModuleResultWrapper> results);

};

#endif // RESULTMODEL_H
