#include "sourcemodel.h"
#include <QStandardItem>
#include <QFileInfo>

SourceModel::SourceModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int SourceModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return sources.count();
}

QVariant SourceModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= sources.count() || index.row() < 0)
        return QVariant();

    if (role == Qt::DecorationRole)
    {
        if (sources.at(index.row())["file"].toBool())
        {
            QPixmap *icon = new QPixmap(":/icons/file-text.png");
            return QIcon(*icon);//file icon
        }
        else
        {
            QPixmap *icon = new QPixmap(":/icons/folder-open.png");
            return QIcon(*icon);//folder icon
        }
    }

    if (role == Qt::DisplayRole)
    {
        QFileInfo *fileInfo = new QFileInfo(sources.at(index.row())["fileName"].toString());
        return fileInfo->fileName();
    }
    if (role == Qt::CheckStateRole)
        return sources.at(index.row())["checked"].toBool() ? Qt::Checked : Qt::Unchecked;
    if (role == Qt::UserRole)
    {
        QFile *file = new QFile(sources.at(index.row())["fileName"].toString());
        return file;
    }
    return QVariant();
}

QVariant SourceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if (role != Qt::DisplayRole)
        return QVariant();
    switch (section) {
    case 0:
        return tr("Sources");
    default:
        return QVariant();
    }
}

bool SourceModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i)
    {
        QHash<QString, QVariant> *h = new QHash<QString, QVariant>();
        h->insert("fileName", "");
        h->insert("checked", true);
        h->insert("file", true);
        sources.insert(row, *h);
    }
    endInsertRows();
    return true;
}

bool SourceModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int i = 0; i < count; ++i)
    {
        sources.removeAt(row);
    }
    endRemoveRows();
    return true;
}

bool SourceModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        int row = index.row();
        QHash<QString, QVariant> h = sources.value(row);
        h["fileName"] = value.toString();
        sources.replace(row, h);
        emit(dataChanged(index, index));
        return true;
    }
    if (index.isValid() && role == Qt::CheckStateRole)
    {
        int row = index.row();
        QHash<QString, QVariant> h = sources.value(row);
        h["checked"] = value.toBool();
        sources.replace(row, h);
        emit(dataChanged(index, index));
        return true;
    }
    if (index.isValid() && role == Qt::DecorationRole)
    {
        int row = index.row();
        QHash<QString, QVariant> h = sources.value(row);
        h["file"] = value.toBool();
        sources.replace(row, h);
        emit(dataChanged(index, index));
        return true;
    }
    return false;
}

Qt::ItemFlags SourceModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
}
