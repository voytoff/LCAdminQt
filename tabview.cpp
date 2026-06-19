#include "tabview.h"
#include <QTabBar>

TabView::TabView(QWidget *parent)
  : QTabWidget{parent} {

  setTabsClosable(true);

  connect(this, &QTabWidget::tabCloseRequested, this, [this](int index) {
    auto w = widget(index);
    widget(index)->close();
    //removeTab(index);
    //if (tabs->length() > index)
    //  tabs->remove(index);
  });
}

void TabView::remove(const int &index) {
  removeTab(index);
  //if (tabs->length() > index)
  //  tabs->remove(index);
}

void TabView::closeAll() {
  while (count() > 0) {
    // Get the widget at the very first index
    QWidget* w = widget(0);
    removeTab(0);
    delete w;
  }
  //tabs->clear();
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

int TabView::append(QWidget *control, const QString &title, const documentType &type, const int &id) {
  auto data = QVariantList({type, id});
  int index = append(control, title, data);
  return index;
}

int TabView::append(QWidget *control, const QString &title, const QVariantList &data) {
  int index = indexOf(data);
  if (index < 0) {
    int index = addTab(control, title);
    tabBar()->setTabData(index, data);
    setCurrentIndex(index);
  }
  setCurrentIndex(index);
  return index;
}
