#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "settings.h"
#include <QTreeView>

class TreeView : public QTreeView {
  Q_OBJECT
public:
  explicit TreeView(Settings *settings, QWidget *parent = nullptr);

private:
  Settings *settings;

signals:
};

#endif // TREEVIEW_H
