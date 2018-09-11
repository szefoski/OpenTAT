#include "mymodel.h"

MyModel::MyModel() : QAbstractTableModel(nullptr)
{
    m_the_data << SimpleData{"Alpha", 10, 100.0}
               << SimpleData{"Beta", 20, 200.0}
               << SimpleData{"Gamma", 30, 300.0}
               << SimpleData{"Delta", 40, 400.0};
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_the_data.size();
}

int MyModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    // Check DisplayRole

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
    switch(role)
    {
        case OneRole:
            return m_the_data[index.row()].m_one;
        case TwoRole:
            return m_the_data[index.row()].m_two;
        case ThreeRole:
            return m_the_data[index.row()].m_three;;
        default:
            qDebug() << "Not supposed to happen";
            return QVariant();
    }
}

QHash<int, QByteArray> MyModel::roleNames() const
{
    QHash<int, QByteArray> roles;
        roles[OneRole] = "one";
        roles[TwoRole] = "two";
        roles[ThreeRole] = "three";
        return roles;

}

void MyModel::theDataChanged()
{
    //TODO
}
