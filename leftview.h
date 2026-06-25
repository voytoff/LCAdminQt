#ifndef LEFTVIEW_H
#define LEFTVIEW_H

#include "docbase.h"
#include "treeview.h"
#include <QWidget>
#include <QGridLayout>
#include <QSplitter>
#include <QByteArray>
#include <QWidget>

class LeftView : public QWidget
{
  Q_OBJECT
public:
  explicit LeftView(TreeView *dictionView, TreeView *optionView, QWidget *parent = nullptr);

  QByteArray saveState() const;
  bool restoreState(const QByteArray &state);
  QAction *toggleOptionAction() const;
  QAction *toggleDictionAction() const;

private:
  DocBase *dictionDoc;
  DocBase *optionDoc;
  TreeView *optionView;
  TreeView *dictionView;
  QSplitter *splitter;

  QLayout* createOptionView();

signals:
};

#endif // LEFTVIEW_H
