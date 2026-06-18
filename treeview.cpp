#include "treeview.h"
#include "treecustomdelegate.h"
#include <QSize>

#include <QHeaderView>

TreeView::TreeView(Settings *settings, QWidget *parent)
  : QTreeView{parent}
  , settings(settings) {

  setIconSize(QSize(14, 14));
  setIndentation(12);
  header()->setSectionResizeMode(QHeaderView::Stretch);
  QLocale locale = this->locale();
  locale.setNumberOptions(QLocale::OmitGroupSeparator);
  setLocale(locale);
  setItemDelegate(new TreeCustomDelegate());
}
