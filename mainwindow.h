#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSplitter>
#include <QMenu>
#include <QActionGroup>

#include "db.h"
#include "optionmodel.h"
#include "dictionmodel.h"
#include "leftview.h"
#include "schemehelper.h"
#include "settings.h"
#include "tabview.h"
#include "treeview.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  //static MainWindow* getInstance() {return instance;}

protected:
  void closeEvent(QCloseEvent *event) override;
  void showEvent(QShowEvent *event) override;
  void contextMenuEvent(QContextMenuEvent *event) override;
  void showTabContextMenu(const QPoint &pos);

private:
  void showMessage(const QString &text);
  void createActions();
  void createControlBar();
  void createControlBox();
  void restoreLayout();
  void saveLayout();

  void doSettings();

  SchemeHelper *schemeHelper;

  QAction *lightAction;
  QAction *darkAction;
  QAction *openAction;
  QAction *saveAction;
  QAction *cancelAction;
  QAction *clearAction;
  QAction *settingsAction;
  QAction *calibrationAction;
  QAction *appendAction;
  QAction *removeAction;
  QAction *aboutAction;
  QAction *copyAction;
  QAction *pasteAction;

  QAction *toggleOptionAction;
  QAction *toggleDictionAction;

  QMenu *windowMenu;
  QActionGroup *windowActionGroup;

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

private:
  static MainWindow* instance;

private slots:
  void loadData();
  /** Открывает выбранную таблицу */
  void openTable(const QModelIndex &index);
  void switchTab(QAction *action);
  void about();
  void append();
  void remove();
  /** Сохранить изменения текущего элемента в базу данных */
  void save();
  /** Отмена предыдущих изменений */
  void cancel();
  /** Очистка выделения */
  void clear();
  /** Копирует выделенные данные в буфер обмена */
  void copy();
  /** Вставляет данные в фокус-элемент из буфера обмена */
  void paste();
  void calibration();

public slots:
  void updateWindowMenu();

signals:

};

#endif // MAINWINDOW_H
