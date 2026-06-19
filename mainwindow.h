#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSplitter>

#include "db.h"
#include "dictionmodel.h"
#include "leftview.h"
#include "optionmodel.h"
#include "schemehelper.h"
#include "settings.h"
#include "tabview.h"
#include "treeview.h"

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
  void add();
  void del();

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
  LeftView *leftView;
  TreeView *optionView;
  TreeView *dictionView;
  DictionModel *dictionModel;
  OptionModel *optionModel;
  TabView *tabView;
  QToolBar *toolbar;

  DB *db;

protected slots:
  void openTable();

signals:
};

#endif // MAINWINDOW_H
