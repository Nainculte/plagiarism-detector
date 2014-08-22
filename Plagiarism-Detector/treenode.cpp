#include "treenode.h"

TreeNode::TreeNode( const QList<QVariant> &data, TreeNode *parent)
{
    _dataSet = data;
    parentNode = parent;
}

TreeNode::~TreeNode()
{
    qDeleteAll(nodes);
}

void TreeNode::addNode(TreeNode *node)
{
    nodes.append(node);
}

TreeNode *TreeNode::getNode(int row)
{
    return nodes.value(row, Q_NULLPTR);
}

int TreeNode::nodeCount() const
{
    return nodes.count();
}

int TreeNode::columnCount() const
{
    return _dataSet.count();
}

int TreeNode::row() const
{
    if (parentNode)
        return parentNode->nodes.indexOf(const_cast<TreeNode*>(this));
    return 0;
}

QVariant TreeNode::data(int column) const
{
    return _dataSet.value(column);
}

TreeNode * TreeNode::parent() const
{
    return parentNode;
}

QList<QVariant> &TreeNode::dataSet()
{
    return _dataSet;
}
