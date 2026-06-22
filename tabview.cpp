#include "tabview.h"
#include <QTabBar>
#include <QIcon>

TabView::TabView(QWidget *parent)
  : QTabWidget{parent} {

  setTabsClosable(true);
  //setIconSize(QSize(16, 16));

  connect(this, &QTabWidget::tabCloseRequested, this, [this](int index) {
    widget(index)->close();
  });
}

void TabView::remove(const int &index) {
  removeTab(index);
}

void TabView::closeAll() {
  while (count() > 0) {
    QWidget* w = widget(0);
    removeTab(0);
    delete w;
  }
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

int TabView::append(QWidget *control, const QString &title, const documentType &type, const int &id, const QString &icon) {
  auto data = QVariantList({type, id, icon});
  int index = append(control, title, data);
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
