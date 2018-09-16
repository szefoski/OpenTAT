#ifndef MYMODEL_H
#define MYMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <QDebug>

struct SimpleData
{
    qint32 m_logNumber;
    QString m_logText;
};

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyModel();//MyData *the_data);
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex & index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    enum Role {
        LogNoRole=Qt::UserRole,
        LogTextRole,
    };
    void loadFromFile(const QString &filePath);
signals:

public slots:
    void theDataChanged();
    QString getLongestLog();

private:
   QList<SimpleData> m_the_data;
   QString m_longestLog;
};


#endif // MYMODEL_H
