#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariantList>
#include <QStandardItem>

class TreeItem : public QStandardItem  {
public:
  TreeItem(const QVariantList &data, int id, int level, TreeItem *parent = nullptr);
  ~TreeItem();

  void appendChild(TreeItem *child) { m_childItems.append(child); }
  TreeItem *child(int row) { return m_childItems.value(row); }
  int childCount() const { return m_childItems.count(); }
  int columnCount() const { return m_itemData.count(); }
  QVariant data(int column) const { return m_itemData.value(column); }
  int row() const { return m_parentItem ? m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this)) : 0; }
  TreeItem *parentItem() { return m_parentItem; }

  int id() const { return m_id; }
  int level() const { return m_level; }
  bool isLoaded() const { return m_isLoaded; }
  void setLoaded(bool loaded) { m_isLoaded = loaded; }

private:
  QVector<QVariant> m_itemData;
  int m_id;
  int m_level; // 0 = Таблица1, 1 = Таблица2, и т.д.
  TreeItem *m_parentItem;
  QVector<TreeItem*> m_childItems;
  bool m_isLoaded; // Флаг подгрузки из БД
};

#endif // TREEITEM_H
