#ifndef TABVIEW_H
#define TABVIEW_H

#include <QTabWidget>
#include <QWidget>

class TabView : public QTabWidget
{
  Q_OBJECT
public:
  explicit TabView(QWidget *parent = nullptr);

signals:
};

#endif // TABVIEW_H
