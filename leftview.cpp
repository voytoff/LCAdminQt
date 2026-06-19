#include "leftview.h"
#include "docbase.h"

LeftView::LeftView(TreeView *dictionView, TreeView *optionView, QWidget *parent)
  : QWidget{parent}
  , dictionView(dictionView)
  , optionView(optionView) {

  splitter = new QSplitter(Qt::Vertical);
  splitter->setContentsMargins(0, 0, 0, 0);
  splitter->addWidget(new DocBase(dictionView));
  splitter->addWidget(new DocBase(optionView));
  QGridLayout *layout = new QGridLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(splitter);
  setLayout(layout);
}

QByteArray LeftView::saveState() const {
  return splitter->saveState();
}

bool LeftView::restoreState(const QByteArray &state) {
 return splitter->restoreState(state);
}
