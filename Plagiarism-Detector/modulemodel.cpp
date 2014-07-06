#include "modulemodel.h"

ModuleModel::ModuleModel(QObject *parent)
{
}

int ModuleModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return modules.count();
}

QVariant ModuleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= modules.count() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole)
        return modules.at(index.row())["moduleName"].toString();
    if (role == Qt::CheckStateRole)
        return modules.at(index.row())["checked"].toBool() ? Qt::Checked : Qt::Unchecked;
    return QVariant();
}

QVariant ModuleModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation);
    if (role != Qt::DisplayRole)
        return QVariant();
    switch (section) {
    case 0:
        return tr("Modules");
    default:
        return QVariant();
    }
}

bool ModuleModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int i = 0; i < count; ++i)
    {
        QHash<QString, QVariant> *h = new QHash<QString, QVariant>();
        h->insert("moduleName", "");
        h->insert("checked", true);
        modules.insert(row, *h);
    }
    endInsertRows();
    return true;
}

bool ModuleModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int i = 0; i < count; ++i)
    {
        modules.removeAt(row);
    }
    endRemoveRows();
    return true;
}

bool ModuleModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        int row = index.row();
        QHash<QString, QVariant> h = modules.value(row);
        h["moduleName"] = value.toString();
        modules.replace(row, h);
        emit(dataChanged(index, index));
        return true;
    }
    if (index.isValid() && role == Qt::CheckStateRole)
    {
        int row = index.row();
        QHash<QString, QVariant> h = modules.value(row);
        h["checked"] = value.toBool();
        modules.replace(row, h);
        emit(dataChanged(index, index));
        return true;
    }
    return false;
}

Qt::ItemFlags ModuleModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
}
