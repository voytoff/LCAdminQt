#ifndef LEFTVIEW_H
#define LEFTVIEW_H

#include "treeview.h"
#include <QWidget>
#include <QGridLayout>
#include <QSplitter>
#include <QByteArray>

class LeftView : public QWidget
{
  Q_OBJECT
public:
  explicit LeftView(TreeView *dictionView, TreeView *optionView, QWidget *parent = nullptr);

  QByteArray saveState() const;
  bool restoreState(const QByteArray &state);

private:
  TreeView *optionView;
  TreeView *dictionView;
  QSplitter *splitter;

signals:
};

#endif // LEFTVIEW_H
