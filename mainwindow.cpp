#include "mainwindow.h"
#include "leftview.h"
#include "modeltablebase.h"
#include "settingsdlg.h"
#include "tableview.h"
#include "types.h"

#include <QSqlRelationalDelegate>
#include <QGuiApplication>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QToolBar>
#include <QAction>
#include <QIcon>
#include <QGridLayout>
#include <QStyleHints>
#include <QTimer>
#include <qevent.h>

//MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow{parent}
  , schemeHelper(new SchemeHelper(this, ":/images/admin.png"))
  , settings(new Settings(this))
  , db(new DB(settings->hostName(), settings->hostPort(), settings->databaseName(), settings->userName(), settings->password(), settings->timeout(), this))
  , optionView(new TreeView("Установки", this))
  , dictionView(new TreeView("Справочник", this))
  , tabView(new TabView(this))
  , splitter(new QSplitter(this))
  , toolbar(addToolBar("Главный"))
  , windowActionGroup(new QActionGroup(this)) {

  //instance = this;

  /// группа акшенов открытых документов
  windowActionGroup->setExclusive(true);
  connect(windowActionGroup, &QActionGroup::triggered, this, &MainWindow::switchTab);
  /// ==================================

  leftView = new LeftView(dictionView, optionView);

  setWindowTitle(title);
  createActions();
  createControlBar();
  statusBar()->setSizeGripEnabled(true);
  createControlBox();

  restoreLayout();
}

void MainWindow::createActions() {
  openAction = schemeHelper->create(tr("Открыть..."), ":/images/tb/open.png", QKeySequence::Open);
  saveAction = schemeHelper->create(tr("Сохранить"), ":/images/tb/save.png", QKeySequence::Save);
  cancelAction = schemeHelper->create(tr("Отменить"), ":/images/tb/cancel.png", QKeySequence(Qt::ALT | Qt::Key_Escape));
  clearAction = schemeHelper->create(tr("Очистить"), ":/images/tb/clear.png", QKeySequence(Qt::SHIFT | Qt::Key_Backspace));
  lightAction = schemeHelper->createLightAction(tr("Дневной режим"), ":/images/tb/light.svg");
  darkAction = schemeHelper->createDarkAction(tr("Ночной режим"), ":/images/tb/dark.svg");
  settingsAction = schemeHelper->create(tr("Установки..."), ":/images/tb/settings.png");
  appendAction = schemeHelper->create(tr("Добавить..."), ":/images/tb/add.png", QKeySequence(Qt::CTRL | Qt::Key_Insert));
  removeAction = schemeHelper->create(tr("Удалить"), ":/images/tb/del.png", QKeySequence(Qt::CTRL | Qt::Key_Delete));
  aboutAction = schemeHelper->create(tr("&О программе..."));
  copyAction = schemeHelper->create(tr("Скопировать"), ":/images/tb/copy.png", QKeySequence(Qt::SHIFT | Qt::CTRL | Qt::Key_C));
  pasteAction = schemeHelper->create(tr("Вставить"), ":/images/tb/paste.png", QKeySequence(Qt::SHIFT | Qt::CTRL | Qt::Key_V));

  toggleOptionAction = leftView->toggleOptionAction();
  toggleDictionAction = leftView->toggleDictionAction();

  connect(settingsAction, &QAction::triggered, this, &MainWindow::doSettings);
  connect(appendAction, &QAction::triggered, this, &MainWindow::append);
  connect(removeAction, &QAction::triggered, this, &MainWindow::remove);
  connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
  connect(saveAction, &QAction::triggered, this, &MainWindow::save);
  connect(cancelAction, &QAction::triggered, this, &MainWindow::cancel);
  connect(clearAction, &QAction::triggered, this, &MainWindow::clear);
  connect(copyAction, &QAction::triggered, this, &MainWindow::copy);
  connect(pasteAction, &QAction::triggered, this, &MainWindow::paste);

  schemeHelper->applayColorScheme(settings->colorScheme(), true);
}

void MainWindow::createControlBar() {
  QMenu *fileMenu = menuBar()->addMenu(tr("Файл"));
  fileMenu->addAction(openAction);
  fileMenu->addAction(saveAction);

  QMenu *editMenu = menuBar()->addMenu(tr("Правка"));
  editMenu->addAction(copyAction);
  editMenu->addAction(pasteAction);
  editMenu->addSeparator();
  editMenu->addAction(appendAction);
  editMenu->addAction(removeAction);
  editMenu->addSeparator();
  editMenu->addAction(cancelAction);
  editMenu->addAction(clearAction);

  QMenu *viewMenu = menuBar()->addMenu(tr("Вид"));
  viewMenu->addAction(lightAction);
  viewMenu->addAction(darkAction);
  viewMenu->addSeparator();
  viewMenu->addAction(toggleOptionAction);
  viewMenu->addAction(toggleDictionAction);

  QMenu *toolMenu = menuBar()->addMenu(tr("Инструменты"));
  toolMenu->addAction(settingsAction);

  windowMenu = menuBar()->addMenu(tr("Окно"));
  windowMenu->addAction(aboutAction);
  windowMenu->addSeparator();

  schemeHelper->setupToolbar(toolbar);
  toolbar->setObjectName("General");
  toolbar->addAction(openAction);
  toolbar->addAction(saveAction);
  toolbar->addSeparator();
  toolbar->addAction(copyAction);
  toolbar->addAction(pasteAction);
  toolbar->addSeparator();
  toolbar->addAction(appendAction);
  toolbar->addAction(removeAction);
  toolbar->addSeparator();
  toolbar->addAction(clearAction);
  toolbar->addAction(cancelAction);
  toolbar->addSeparator();
  toolbar->addAction(settingsAction);
}

void MainWindow::createControlBox() {
  //connect(treeView, &QTreeView::doubleClicked, this, &MainWindow::editSensor);
  //сonnect(optionView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::reload);

  splitter->addWidget(leftView);
  splitter->addWidget(tabView);

  QGridLayout *layout = new QGridLayout();
  layout->addWidget(splitter, 0, 0);
  layout->setContentsMargins(2, 1, 2, 0);

  QWidget *widget = new QWidget;
  widget->setLayout(layout);
  setCentralWidget(widget);
}

void MainWindow::closeEvent(QCloseEvent *event) {
  if (tabView->closeAll()) {
    event->accept();
    saveLayout();
    QMainWindow::closeEvent(event);
  } else event->ignore();
}

void MainWindow::showEvent(QShowEvent *event) {
  QTimer::singleShot(200, this, [this]() {loadData();});
}

void MainWindow::showMessage(const QString &text) {
  statusBar()->showMessage(text);
  QTimer::singleShot(readyTimeout, this, [this]() {
    statusBar()->showMessage(ready);
  });
}

DocumentIdent MainWindow::getDocument() {
  auto model = tabView->model<ModelTableBase>();
  if (model) {
    auto view = tabView->view<TableView>();
    if (view)
      return {model, view};
  }
  return {};
}

void MainWindow::restoreLayout() {
  restoreGeometry(settings->geometry());
  restoreState(settings->windowState());
  splitter->restoreState(settings->splitter());
  leftView->restoreState(settings->splitter2());
}

void MainWindow::saveLayout() {
  settings->geometry(saveGeometry());
  settings->windowState(saveState());
  settings->splitter(splitter->saveState());
  settings->splitter2(leftView->saveState());
  //settings->colorScheme(schemeHelper->colorScheme());
}

void MainWindow::loadData() {
  optionView->setModel(nullptr);
  if (db->open()) {
    optionView->setModel(optionModel = new OptionModel(db, {"Название", "Инфо"}, {icon_crate, ":/images/db/table.png"}, this));
    dictionView->setModel(dictionModel = new DictionModel(db, {"Название"}, {icon_crate, icon_module}, this));
    dictionView->setHeaderHidden(true);
    //connect(optionView, &QTreeView::doubleClicked, this, &MainWindow::openTable);
    connect(dictionView, &QTreeView::doubleClicked, this, &MainWindow::openTable);
  } else {
    showMessage(db->lastError().text());
    QMessageBox::critical(this, title, db->lastError().text());
  }
}

void MainWindow::append() {
  auto doc = getDocument();
  if (doc.isValid()) {
    // Получаем индекс текущей выделенной строки
    ///QModelIndex currentIndex = doc.view->currentIndex();
    ///int row = currentIndex.isValid() ? currentIndex.row() : 0;
    // Вставляем новую строку перед текущей (или в конец, если таблица пуста)
    // Вставляем новую строку перед за последней (или в конец, если таблица пуста)
    int row = doc.model->rowCount();
    doc.model->insertRow(row);
    // Переводим фокус и включаем режим редактирования для добавленной ячейки
    QModelIndex newIndex = doc.model->index(row, 0); // 0 - индекс первой колонки
    doc.view->setCurrentIndex(newIndex);
    doc.view->edit(newIndex);
  }
}

void MainWindow::remove() {
  auto doc = getDocument();
  if (doc.isValid()) {
    // Получаем список всех выделенных индексов
    QModelIndexList selectedIndexes = doc.view->selectionModel()->selectedIndexes();
    if (!selectedIndexes.isEmpty()) {
      // Удаляем строку первого выделенного элемента
      if (QMessageBox::question(this, title, QString("Удалить выделенные строки из таблицы '%1'?").arg(doc.view->text())) == QMessageBox::Yes) {
        foreach (auto index, selectedIndexes)
          doc.model->removeRow(index.row());
      }
    }
  }
}

void MainWindow::save() {
  auto doc = getDocument();
  if (doc.isValid()) {
    if (doc.view->isModified())
      doc.view->save();
  }
}

void MainWindow::cancel() {
  auto doc = getDocument();
  if (doc.isValid()) {
    if (doc.view->isModified() && QMessageBox::question(this, title, QString("Отменить все изменения в таблице '%1'?").arg(doc.view->text())) == QMessageBox::Yes)
      doc.view->cancel();
  }
}

void MainWindow::clear() {
  auto doc = getDocument();
  if (doc.isValid()) {
    if (doc.view->isModified())
      doc.view->clear();
  }
}

void MainWindow::copy() {
  auto doc = getDocument();
  if (doc.isValid()) {
    if (doc.view->copySelection())
    QMessageBox::information(this, title, QString("Выделенные данные таблицы '%1' скопированы в буфер обмена.").arg(doc.view->text()));
  }
}

void MainWindow::paste() {
  auto doc = getDocument();
  if (doc.isValid())
     doc.view->pasteClipboard();
}

void MainWindow::doSettings() {
  SettingsDlg *dialog = new SettingsDlg(settings, this);
  int accepted = dialog->exec();
  if (accepted == QDialog::Accepted) {
    auto colorScheme = settings->colorScheme();
    if ((Qt::ColorScheme)colorScheme != QGuiApplication::styleHints()->colorScheme())
      schemeHelper->applayColorScheme(colorScheme);
    tabView->closeAll();
    db->close();
    delete db;
    db = new DB(settings->hostName(), settings->hostPort(), settings->databaseName(), settings->userName(), settings->password(), settings->timeout());
    loadData();
  }
}

void MainWindow::openTable(const QModelIndex &index) {
  if (index.isValid()) {
    auto data = dictionModel->get(index.row());
    ModelTableBase *model = ModelTableBase::create(data.type, data.table);
    if (model) {
      TableView *tableView = new TableView(model, data.title, this);
      tabView->append(tableView, data.title, data.type, data.type, data.icon);
      //tableView->setItemDelegate(new QSqlRelationalDelegate(tableView)); перенес вызов в TableView
    }
  }
}

void MainWindow::switchTab(QAction *action) {
  int index = action->data().toInt();
  tabView->setCurrentIndex(index);
}

void MainWindow::updateWindowMenu() {
  //windowMenu->clear();
  foreach (auto action, windowActionGroup->actions()) {
    windowMenu->removeAction(action);
  }

  for (int i = 0; i < tabView->count(); ++i) {
    QString tabName = tabView->tabText(i);
    QAction *action = windowMenu->addAction(tabName);
    action->setCheckable(true);
    action->setChecked(i == tabView->currentIndex());
    action->setData(i); // Store the tab index inside the action

    windowActionGroup->addAction(action);
  }
}

void MainWindow::about() {
  QMessageBox::about(
    this,
    tr("О программе..."),
    tr("<p><b>Администратор</b> программа управления справочником и настройками "
      "обработки экспериментов с датчиков регистрации параметров испытаний "
      "компанентов и изделий на стендах НИИХМ.</p>"));

}

