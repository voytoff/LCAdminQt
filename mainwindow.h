#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QSqlDatabase>
#include "db.h"
#include "schemehelper.h"
#include "settings.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

protected:
  void closeEvent(QCloseEvent *event) override;

private:
  void createActions();
  void createControlBar();
  void restoreLayout();
  void saveLayout();

  SchemeHelper *schemeHelper;

  QAction *lightAction;
  QAction *darkAction;

  Settings *settings;

  DB *db;

signals:
};

#endif // MAINWINDOW_H
