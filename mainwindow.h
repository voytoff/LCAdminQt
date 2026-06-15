#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "schemehelper.h"
#include "settings.h"
#include <QMainWindow>
#include <QAction>

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

private:
  void createActions();
  void createControlBar();

  SchemeHelper *schemeHelper;

  QAction *lightAction;
  QAction *darkAction;

  Settings* settings;

signals:
};

#endif // MAINWINDOW_H
