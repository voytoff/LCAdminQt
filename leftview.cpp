#include "leftview.h"
#include "DBExtension_global.h"
#include "db.h"
#include "sqlcombobox.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QSqlQuery>

LeftView::LeftView(TreeView *dictionView, TreeView *optionView, QWidget *parent)
  : QWidget{parent}
  , dictionView(dictionView)
  , optionView(optionView) {

  splitter = new QSplitter(Qt::Vertical);
  splitter->setContentsMargins(0, 0, 0, 0);
  dictionDoc = new DocBase(dictionView);
  splitter->addWidget(dictionDoc);
  optionDoc = new DocBase(optionView->windowTitle(), createOptionView());
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

QLayout* LeftView::createOptionView() {
  auto layout = new QVBoxLayout();
  // Настраиваем внутренние отступы контейнера (слева, сверху, справа, снизу)
  layout->setContentsMargins(0, 0, 0, 0);
  // Настраиваем расстояние между элементами внутри контейнера
  layout->setSpacing(2);
  SqlComboBox *experiment = new SqlComboBox("SELECT id,name FROM experiment ORDER BY name");
  experiment->setPlaceholderText("Название экперимента...");
  layout->addWidget(experiment);
  layout->addWidget(optionView);
  return layout;
}
