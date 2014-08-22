#ifndef TREENODE_H
#define TREENODE_H

#include <QVariant>
#include <QList>

class TreeNode
{
public:
    TreeNode(const QList<QVariant> &data, TreeNode *parent = 0);
    ~TreeNode();

    void addNode(TreeNode *node);

    TreeNode *getNode(int row);
    int nodeCount() const;
    int columnCount() const;
    int row() const;
    QVariant data(int column) const;
    TreeNode *parent() const;

    QList<QVariant> &dataSet();

private:
    TreeNode *parentNode;
    QList<TreeNode *> nodes;
    QList<QVariant> _dataSet;
};

#endif // TREENODE_H
