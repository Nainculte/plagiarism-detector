#include "resultmodel.h"
#include "summarymodule.h"

ResultModel::ResultModel(QList<ModuleResultWrapper> results, int matrixSize, QObject *parent) :
    QAbstractItemModel(parent), matrixSize(matrixSize)
{
    QList<QVariant> data;
    data << "Modules" << "Matrixes";
    root = new TreeNode(data);
    initialize(results);
}

ResultModel::~ResultModel()
{
    delete root;
}

QVariant ResultModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeNode *item = static_cast<TreeNode *>(index.internalPointer());

    QVariant data = item->data(index.column());

    if (data.canConvert(QVariant::String))
    {
        return data;
    }
    else
    {
        AnalysisResult *res = (AnalysisResult *)data.value<void *>();
        return res->similarity();
    }
}

Qt::ItemFlags ResultModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant ResultModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)
//    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
//        return rootItem->data(section);

    return QVariant();
}

QModelIndex ResultModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeNode *parentItem;

    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<TreeNode*>(parent.internalPointer());

    TreeNode *childItem = parentItem->getNode(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex ResultModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeNode *childItem = static_cast<TreeNode*>(index.internalPointer());
    TreeNode *parentItem = childItem->parent();

    if (parentItem == root)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int ResultModel::rowCount(const QModelIndex &parent) const
{
    TreeNode *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = root;
    else
        parentItem = static_cast<TreeNode*>(parent.internalPointer());

    return parentItem->nodeCount();
}

int ResultModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<TreeNode*>(parent.internalPointer())->getNode(parent.row())->columnCount();
    else
        return root->columnCount();
}

QModelIndex ResultModel::tableIndexForRow(int row)
{
    return index(row, 0);
}

void ResultModel::initialize(QList<ModuleResultWrapper> results)
{
    QList<TreeNode *>nodes;
    QList<QList<AnalysisResult *> >lists;
    foreach (ModuleResultWrapper wrapper, results) {
        QList<QVariant> data;
        data << QVariant(wrapper.module()->getModuleInformation());

        lists << wrapper.results();

        TreeNode *moduleNode = new TreeNode(data, root);
        int offsetx = 0;
        for (int i = 0; i < matrixSize; ++i)
        {
            offsetx += i + 1;
            QList<QVariant> rowData;
            int offsety = 0;
            for (int j = 0; j < matrixSize; ++j)
            {
                offsety += j + 1;
                if (i == j)
                    rowData << qVariantFromValue((void *)new AnalysisResult());
                else if (i > j) {
                    int index = (matrixSize * j + i) - offsety;
                    rowData << qVariantFromValue((void *)wrapper.results().at(index));
                } else {
                    int index = (matrixSize * i + j) - offsetx;
                    rowData << qVariantFromValue((void *)wrapper.results().at(index));
                }
            }
            TreeNode *rowNode = new TreeNode(rowData, moduleNode);
            moduleNode->addNode(rowNode);
        }
        nodes << moduleNode;
    }

    if (lists.count() > 1) {
        SummaryModule *summary = new SummaryModule();

        QList<QVariant> data;
        data << QVariant(QMetaType::QObjectStar, summary);
        TreeNode *moduleNode = new TreeNode(data, root);
        for (int i = 0; i < matrixSize; ++i)
        {
            QList<QVariant> rowData;
            for (int j = 0; j < matrixSize; ++j)
                rowData << qVariantFromValue((void *)summary->getAnalysisResults().at(matrixSize * i + j));
            TreeNode *rowNode = new TreeNode(rowData, moduleNode);
            moduleNode->addNode(rowNode);
        }
        nodes.insert(0, moduleNode);
    }

    foreach (TreeNode *node, nodes) {
        root->addNode(node);
    }
}
