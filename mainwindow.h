#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSplitter>

#include "db.h"
#include "schemehelper.h"
#include "settings.h"
#include "treeview.h"

const QString title = "Администратор";

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

protected:
  void closeEvent(QCloseEvent *event) override;

private:
  void createActions();
  void createControlBar();
  void createControlBox();
  void restoreLayout();
  void saveLayout();
  void loadData();

  void doSettings();

  SchemeHelper *schemeHelper;

  QAction *lightAction;
  QAction *darkAction;
  QAction *openAction;
  QAction *saveAction;
  QAction *settingsAction;


  Settings *settings;

  QSplitter *splitter;
  TreeView *treeView;
  QTabWidget *tabWidget;
  QToolBar *toolbar;

  DB *db;

signals:
};

#endif // MAINWINDOW_H
