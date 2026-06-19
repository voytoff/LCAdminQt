#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>

class TreeView : public QTreeView {
  Q_OBJECT
public:
  explicit TreeView(const QString &title, QWidget *parent = nullptr);

private:

signals:
};

#endif // TREEVIEW_H
