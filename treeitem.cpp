#include "treeitem.h"

TreeItem::TreeItem(const QVariantList &data, int id, int level, TreeItem *parent)
  : m_itemData(data), m_id(id), m_level(level), m_parentItem(parent), m_isLoaded(false) {

}

TreeItem::~TreeItem() {
  qDeleteAll(m_childItems);
}