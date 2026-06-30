#include "treeview.h"
#include <QSize>

#include <QHeaderView>

TreeView::TreeView(const QString &title, QWidget *parent)
  : QTreeView{parent} {

  setWindowTitle(title);
  setIconSize(QSize(14, 14));
  setIndentation(12);
  header()->setSectionResizeMode(QHeaderView::Stretch);
  QLocale locale = this->locale();
  locale.setNumberOptions(QLocale::OmitGroupSeparator);
  setLocale(locale);
  setContextMenuPolicy(Qt::ActionsContextMenu);
}
