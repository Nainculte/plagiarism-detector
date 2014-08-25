#include "resultfilterproxymodel.h"
#include "treenode.h"
#include "analysisresult.h"
#include "resultmodel.h"

ResultFilterProxyModel::ResultFilterProxyModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    _value = 0;
}

bool ResultFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (!source_parent.isValid())
        return true;
    int i = 0;
    QModelIndex index;
    bool accept = false;
    while ((index = sourceModel()->index(source_row, i, source_parent)).isValid())
    {
        TreeNode *item = static_cast<TreeNode *>(index.internalPointer());
        QVariant data = item->data(index.column());
        AnalysisResult *res = (AnalysisResult *)data.value<void *>();
        if (res->similarity() > _value)
        {
            accept = true;
            break;
        }
        ++i;
    }
    return accept;
}

bool ResultFilterProxyModel::filterAcceptsColumn(int source_column, const QModelIndex &source_parent) const
{
    if (!source_parent.isValid())
        return true;
    int i = 0;
    QModelIndex index;
    bool accept = false;
    while ((index = sourceModel()->index(i, source_column, source_parent)).isValid())
    {
        TreeNode *item = static_cast<TreeNode *>(index.internalPointer());
        QVariant data = item->data(index.column());
        AnalysisResult *res = (AnalysisResult *)data.value<void *>();
        if (res->similarity() > _value)
        {
            accept = true;
            break;
        }
        ++i;
    }
    return accept;
}

void ResultFilterProxyModel::setFilterValue(int value)
{
    _value = value;
    invalidateFilter();
}

QVariant ResultFilterProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            QModelIndex index = mapToSource(this->index(0, section, this->index(0, 0)));
            return sourceModel()->headerData(index.column(), orientation, role);
        }
        else
        {
            QModelIndex index = mapToSource(this->index(section, 0, this->index(0, 0)));
            return sourceModel()->headerData(index.row(), orientation, role);
        }
//        if (headers.empty())
//            return sourceModel()->headerData(section, orientation, role);
//        return headers.at(section);
    }
    return QVariant();
}
