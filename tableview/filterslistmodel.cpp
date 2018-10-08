#include "filterslistmodel.h"

#include <QDebug>

FiltersListModel::FiltersListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int FiltersListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return 100;
}

int FiltersListModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return 5;
}

QVariant FiltersListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch(static_cast<Role>(role))
    {
    case Role::Active:
        return true;
    case Role::BgColor:
        return QStringLiteral("pink");
    case Role::FontColor:
        return QStringLiteral("blue");
    case Role::Hits:
        return QStringLiteral("hits");
    case Role::Pattern:
        return QStringLiteral("Some Text");
    default:
        qDebug() << "Not supposed to happen";
        return QVariant();
    }

    return QVariant();
}

bool FiltersListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags FiltersListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> FiltersListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Role::Active)] = "Role_Active";
    roles[static_cast<int>(Role::BgColor)] = "Role_BgColor";
    roles[static_cast<int>(Role::FontColor)] = "Role_FontColor";
    roles[static_cast<int>(Role::Hits)] = "Role_Hits";
    roles[static_cast<int>(Role::Pattern)] = "Role_Pattern";
    return roles;
}
