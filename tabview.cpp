#include "tabview.h"
#include "mainwindow.h"
#include <QTabBar>
#include <QIcon>

TabView::TabView(QWidget *parent)
  : QTabWidget{parent} {

  setTabsClosable(true);
  setIconSize(QSize(16, 16));

  connect(this, &QTabWidget::tabCloseRequested, this, &TabView::removeTab);

  auto mainWindow = (MainWindow*)parentWidget();
  connect(this, &QTabWidget::currentChanged, mainWindow, &MainWindow::updateWindowMenu);
  connect(this, &TabView::inserted, mainWindow, &MainWindow::updateWindowMenu);
  connect(this, &TabView::removed, mainWindow, &MainWindow::updateWindowMenu);
}

bool TabView::removeTab(int index) {
  QWidget *w = widget(index);
  if (w && w->close()) {
    QTabWidget::removeTab(index);
    delete w;
  } else return false;
  return true;
}

bool TabView::closeAll() {
  while (count() > 0)
    if (!removeTab(0)) return false;
  return true;
}

DocumentIdent TabView::document() {
  IStateWidget *widget = currentWidget<IStateWidget>();
  if (widget) {
    auto t = table();
    if (t) {
      auto m = model<ModelTableBase>();
      if (m) return {widget, m, t};
    }
  }
  return {};
}

TableView *TabView::table() {
  IStateWidget *widget = currentWidget<IStateWidget>();
  return widget ? widget->table() : nullptr;
}

void TabView::closeEvent(QCloseEvent *event) {
  closeAll();
}

int TabView::indexOf(const QVariantList &data) const {
  int length = data.length();
  for (int i = 0; i < count(); ++i) {
    auto tag = (QVariantList)tabBar()->tabData(i).toList();
    if (length != tag.length()) continue;
    bool equal = true;
    for (int n = 0; n < length; n++) {
      if (data[n] != tag[n]) {
        equal = false;
        break;
      }
    }
    if (equal) return i;
  }
  return -1;
}

void TabView::tabRemoved(int index) {
  QTabWidget::tabRemoved(index);
  emit removed(index);
}

void TabView::tabInserted(int index) {
  QTabWidget::tabInserted(index);
  emit inserted(index);
}

int TabView::append(QWidget *widget, const QString &title, const Enums::documentType &type, const int &id, const QString &icon) {
  auto data = QVariantList({type, id, icon});
  int index = append(widget, title, data);
  if (icon.length() > 0)
    setTabIcon(index, QIcon(icon));
  return index;
}

int TabView::append(QWidget *control, const QString &title, const QVariantList &data) {
  int index = indexOf(data);
  if (index < 0) {
    index = addTab(control, title);
    tabBar()->setTabData(index, data);
    setCurrentIndex(index);
  }
  setCurrentIndex(index);
  return index;
}
