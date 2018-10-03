#ifndef FILTERSMODEL_H
#define FILTERSMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <QDebug>

struct FilterItemData
{
    bool m_active;
    QString m_bgColor;
    QString m_fontColor;
    QString m_pattern;
};

class FiltersModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit FiltersModel();
    int rowCount(const QModelIndex & parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex & index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    enum class Role {
        Pattern = Qt::UserRole,
        FontColor,
        BgColor,
        Active
    };

private:
    QList<FilterItemData> m_dataModel;
};

#endif // FILTERSMODEL_H
