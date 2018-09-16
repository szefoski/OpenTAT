#include "mymodel.h"

MyModel::MyModel() : QAbstractTableModel(nullptr)
{
    loadFromFile("/home/daniel/Downloads/logs1.txt");
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
        case LogNoRole:
            return m_the_data[index.row()].m_logNumber;
        case LogTextRole:
            return m_the_data[index.row()].m_logText;
        default:
            qDebug() << "Not supposed to happen";
            return QVariant();
    }
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
   qDebug() << "setData() called with:" << value;
   if (!hasIndex(index.row(), index.column(), index.parent()) || !value.isValid())
            return false;

    switch(role)
    {
        case LogNoRole:
            m_the_data[index.row()].m_logNumber = value.toInt();
        break;
        case LogTextRole:
            m_the_data[index.row()].m_logText = value.toString();
        break;
    }

    emit dataChanged(index, index, { role } );

    return true;
}

QString MyModel::getLongestLog()
{
   return m_longestLog;
}

QHash<int, QByteArray> MyModel::roleNames() const
{
    QHash<int, QByteArray> roles;
        roles[LogNoRole] = "line";
        roles[LogTextRole] = "text";
        return roles;

}

void MyModel::loadFromFile(const QString &filePath)
{
    int longestLog = 0;
    int longestLogIndex = 0;
    QFile inputFile(filePath);
    QFileDevice::FileError err = QFileDevice::NoError;
    const bool exists = inputFile.exists();
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        int lineNo = 1;
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (line.size() > longestLog)
            {
                longestLog = line.size();
                longestLogIndex = lineNo - 1;
            }
            m_the_data << SimpleData{lineNo, line};
            ++lineNo;
        }
        inputFile.close();
        m_longestLog = m_the_data[longestLogIndex].m_logText;
    }
}

void MyModel::theDataChanged()
{
    //TODO
}
