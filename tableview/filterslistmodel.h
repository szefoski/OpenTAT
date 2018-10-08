#ifndef FILTERSLISTMODEL_H
#define FILTERSLISTMODEL_H

#include <QAbstractTableModel>

class FiltersListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit FiltersListModel(QObject *parent = nullptr);

    enum class Role {
        Pattern = Qt::UserRole,
        FontColor,
        BgColor,
        Active,
        Hits
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
};

#endif // FILTERSLISTMODEL_H
