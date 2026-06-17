#include "treeview.h"
#include "treecustomdelegate.h"

#include <QHeaderView>

TreeView::TreeView(Settings *settings, QWidget *parent)
  : QTreeView{parent}
  , settings(settings) {

  setRootIsDecorated(false);
  header()->setSectionResizeMode(QHeaderView::Stretch);

  QLocale locale = this->locale();
  locale.setNumberOptions(QLocale::OmitGroupSeparator);
  setLocale(locale);
  setItemDelegate(new TreeCustomDelegate());
}
