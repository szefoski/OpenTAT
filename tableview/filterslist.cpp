#include "filterslist.h"

FiltersList::FiltersList(QObject *parent) : QObject(parent)
{
   m_items.append({false, "pink", "yellow", "hits"});
   m_items.append({true, "green", "orange", "hits"});
}

QVector<FilterItem> FiltersList::items()
{
    return m_items;
}

bool FiltersList::setItemAt(int index, const FilterItem &item)
{
   if (index < 0 || index >= m_items.size())
   {
       return false;
   }

   FilterItem &oldItem = m_items[index];
   if (item == oldItem)
   {
       return false;
   }

   oldItem = item;
   return true;
}

void FiltersList::appendItem()
{
   emit preItemAppended();
   m_items.append({false, "red", "white", "hits"});
   emit postItemAppended();
}

void FiltersList::removeAll()
{

}
