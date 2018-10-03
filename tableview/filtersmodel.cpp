#include "filtersmodel.h"

FiltersModel::FiltersModel() : QAbstractTableModel(nullptr)
{
    m_dataModel.append({true, "black", "yellow", "Some Pattern"});
    m_dataModel.append({false, "green", "orange", "Some Pattern 2"});
    m_dataModel.append({false, "blue", "white", "Some Pattern 3"});
}

int FiltersModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_dataModel.size();
}

int FiltersModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 4;
}

QVariant FiltersModel::data(const QModelIndex &index, int role) const
{
    // Check boudaries
    if(index.column() < 0 ||
            columnCount() <= index.column() ||
            index.row() < 0 ||
            rowCount() <= index.row())
    {
        qDebug() << "Warning: " << index.row() << ", " << index.column();
        return QVariant();
    }

    // Nominal case
    qDebug() << "MyModel::data: " << index.column() << "; " << index.row();
    switch(static_cast<Role>(role))
    {
    case Role::Active:
        return m_dataModel[index.row()].m_active;
    case Role::BgColor:
        return m_dataModel[index.row()].m_bgColor;
    case Role::FontColor:
        return m_dataModel[index.row()].m_fontColor;
    case Role::Pattern:
        return m_dataModel[index.row()].m_pattern;
    default:
        qDebug() << "Not supposed to happen";
        return QVariant();
    }

    return QVariant();
}

bool FiltersModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

QHash<int, QByteArray> FiltersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Role::Active)] = "Role_Active";
    roles[static_cast<int>(Role::BgColor)] = "Role_BgColor";
    roles[static_cast<int>(Role::FontColor)] = "Role_FontColor";
    roles[static_cast<int>(Role::Pattern)] = "Role_Pattern";
    return roles;
}
