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
            QModelIndex index = mapToSource(this->index(0, section, rootIndex));
            return sourceModel()->headerData(index.column(), orientation, role);
        }
        else
        {
            QModelIndex index = mapToSource(this->index(section, 0, rootIndex));
            return sourceModel()->headerData(index.row(), orientation, role);
        }
    }
    return QVariant();
}

QVariant ResultFilterProxyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole)
    {
        return QSortFilterProxyModel::data(index, role);
    }
    else if (role == Qt::DisplayRole)
    {
        return QSortFilterProxyModel::data(index, role);
    }
    else if (role == Qt::BackgroundRole)
    {
        QModelIndex sourceIndex = mapToSource(this->index(index.row(), index.column(), rootIndex));
        TreeNode *item = static_cast<TreeNode *>(sourceIndex.internalPointer());
        QVariant data = item->data(sourceIndex.column());

        if (!data.canConvert(QVariant::String))
        {
            AnalysisResult *res = (AnalysisResult *)data.value<void *>();
            return res->color(_value);
        }
    }
    return QVariant();
}

void ResultFilterProxyModel::setRootIndex(QModelIndex root)
{
    rootIndex = root;
}
