#ifndef FILTERSLIST_H
#define FILTERSLIST_H

#include <QObject>
#include <QVector>

struct FilterItem
{
    bool m_active;
    QString m_bgColor;
    QString m_fontColor;
    QString m_pattern;

    bool operator==(const FilterItem &item) const
    {
        if (m_active != item.m_active)
        {
            return false;
        }

        if (m_bgColor != item.m_bgColor)
        {
            return false;
        }

        if (m_fontColor != item.m_fontColor)
        {
            return false;
        }

        if (m_pattern != item.m_pattern)
        {
            return false;
        }

        return true;
    }
};

class FiltersList : public QObject
{
    Q_OBJECT
public:
    explicit FiltersList(QObject *parent = nullptr);

    QVector<FilterItem> items();
    bool setItemAt(int row, const FilterItem &item);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int row);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeAll();

private:
    QVector<FilterItem> m_items;
};

#endif // FILTERSLIST_H
