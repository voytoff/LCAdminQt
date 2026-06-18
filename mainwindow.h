#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSplitter>

#include "db.h"
#include "schemehelper.h"
#include "settings.h"
#include "tabview.h"
#include "treeview.h"

const QString title = "Администратор";
const QString ready = "Готово";
const int readyTimeout = 5000;

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);

protected:
  void closeEvent(QCloseEvent *event) override;
  void showEvent(QShowEvent *event) override;

private:
  void showMessage(const QString &text);
  void createActions();
  void createControlBar();
  void createControlBox();
  void restoreLayout();
  void saveLayout();
  void loadData();
  void reload();

  void doSettings();

  SchemeHelper *schemeHelper;

  QAction *lightAction;
  QAction *darkAction;
  QAction *openAction;
  QAction *saveAction;
  QAction *settingsAction;
  QAction *addAction;
  QAction *delAction;

  Settings *settings;

  QSplitter *splitter;
  TreeView *treeView;
  TabView *tabView;
  QToolBar *toolbar;

  DB *db;

signals:
};

#endif // MAINWINDOW_H
