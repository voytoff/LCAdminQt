#include "leftview.h"

LeftView::LeftView(TreeView *dictionView, TreeView *optionView, QWidget *parent)
  : QWidget{parent}
  , dictionView(dictionView)
  , optionView(optionView) {

  splitter = new QSplitter(Qt::Vertical);
  splitter->setContentsMargins(0, 0, 0, 0);
  dictionDoc = new DocBase(dictionView);
  splitter->addWidget(dictionDoc);
  optionDoc = new DocBase(optionView);
  splitter->addWidget(optionDoc);
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

QAction *LeftView::toggleOptionAction() const {
  return optionDoc->toggleViewAction();
}

QAction *LeftView::toggleDictionAction() const {
  return dictionDoc->toggleViewAction();
}
