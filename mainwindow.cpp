#include "mainwindow.h"
#include "calibrationdlg.h"
#include "crate.h"
#include "leftview.h"
#include "modeltablebase.h"
#include "sensorview.h"
#include "separatoraction.h"
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
#include <QCloseEvent>
#include <QList>

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow{parent}
  , schemeHelper(new SchemeHelper(this, ":/images/admin.png"))
  , settings(new Settings(this))
  , db(new DB(DatabaseName, settings->hostName(), settings->hostPort(), settings->databaseName(), settings->userName(), settings->password(), settings->timeout(), this))
  , optionView(new TreeView("Эксперимент", this))
  , dictionView(new TreeView("Справочник", this))
  , tabView(new TabView(this))
  , splitter(new QSplitter(this))
  , toolbar(addToolBar("Главный"))
  , windowActionGroup(new QActionGroup(this)) {

  instance = this;

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
  //calibrationAction = schemeHelper->create(tr("Градуировки..."), ":/images/tb/calibration.png", QKeySequence(Qt::CTRL | Qt::Key_U));
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
  upAction = schemeHelper->create(tr("Вверх"), ":/images/tb/up.png", QKeySequence(Qt::SHIFT | Qt::CTRL | Qt::Key_C));
  downAction = schemeHelper->create(tr("Вниз"), ":/images/tb/down.png", QKeySequence(Qt::SHIFT | Qt::CTRL | Qt::Key_V));

  cratesAction = schemeHelper->create(tr("Подключенные крейты..."), ":/images/tb/crates.png");

  toggleOptionAction = leftView->toggleOptionAction();
  toggleDictionAction = leftView->toggleDictionAction();

  connect(settingsAction, &QAction::triggered, this, &MainWindow::doSettings);

  connect(openAction, &QAction::triggered, this, [this]() {openTable(dictionView->currentIndex());});
  connect(appendAction, &QAction::triggered, this, &MainWindow::append);
  connect(removeAction, &QAction::triggered, this, &MainWindow::remove);
  connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
  connect(saveAction, &QAction::triggered, this, &MainWindow::save);
  connect(cancelAction, &QAction::triggered, this, &MainWindow::cancel);
  connect(clearAction, &QAction::triggered, this, &MainWindow::clear);
  connect(copyAction, &QAction::triggered, this, &MainWindow::copy);
  connect(pasteAction, &QAction::triggered, this, &MainWindow::paste);
  connect(upAction, &QAction::triggered, this, &MainWindow::up);
  connect(downAction, &QAction::triggered, this, &MainWindow::down);
  connect(cratesAction, &QAction::triggered, this, &MainWindow::crates);

  dictionActionGroup.append(openAction);
  tableActionGroup.append({
    copyAction, pasteAction, new SeparatorAction(),
    appendAction, removeAction, new SeparatorAction(),
    cancelAction, clearAction, new SeparatorAction(),
    saveAction});
  calibrationActionGroup.append({
    copyAction, pasteAction, new SeparatorAction(),
    appendAction, removeAction, new SeparatorAction(),
    cancelAction, clearAction, new SeparatorAction(),
    upAction, downAction, new SeparatorAction(),
    saveAction});

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
  editMenu->addAction(upAction);
  editMenu->addAction(downAction);
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
  toolMenu->addSeparator();
  toolMenu->addAction(settingsAction);

  QMenu *crateMenu = menuBar()->addMenu(tr("Крейт"));
  crateMenu->addAction(cratesAction);

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
  toolbar->addAction(upAction);
  toolbar->addAction(downAction);
  toolbar->addSeparator();
  toolbar->addAction(clearAction);
  toolbar->addAction(cancelAction);
  toolbar->addSeparator();
  toolbar->addAction(settingsAction);
  //toolbar->addAction(calibrationAction);
}

void MainWindow::createControlBox() {
  //connect(treeView, &QTreeView::doubleClicked, this, &MainWindow::editSensor);
  //сonnect(optionView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::reload);

  // контекстное меню дерева справочников
  dictionView->addActions(dictionActionGroup);
  // контекстное меню дерева объектов
  optionView->addActions(optionActionGroup);

  // Включаем контекстное меню элемента закладок
  //tabView->setContextMenuPolicy(Qt::CustomContextMenu);
  //connect(tabView, &QTabBar::customContextMenuRequested, this, &MainWindow::showTabContextMenu);

  splitter->addWidget(leftView);
  splitter->addWidget(tabView);

  QGridLayout *layout = new QGridLayout();
  layout->addWidget(splitter, 0, 0);
  layout->setContentsMargins(3, 1, 3, 0);

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
  auto doc = tabView->document();
  if (doc.hasTable()) {
    // Получаем индекс текущей выделенной строки
    // Вставляем новую строку перед текущей (или в конец, если таблица пуста)
    // Вставляем новую строку перед за последней (или в конец, если таблица пуста)
    int row = doc.model->rowCount();
    doc.model->insertRow(row);
    // Переводим фокус и включаем режим редактирования для добавленной ячейки
    QModelIndex newIndex = doc.model->index(row, doc.model->fieldIndex("name"));
    doc.table->setCurrentIndex(newIndex);
    doc.table->edit(newIndex);
  }
}

void MainWindow::remove() {
  auto doc = tabView->document();
  if (doc.hasTable()) {
    // Получаем список всех выделенных индексов
    QModelIndexList selectedIndexes = doc.table->selectionModel()->selectedIndexes();
    if (!selectedIndexes.isEmpty()) {
      // Удаляем все выделенные строки
      if (QMessageBox::question(this, title, QString("Удалить выделенные строки из таблицы '%1'?").arg(doc.table->title())) == QMessageBox::Yes) {
        foreach (auto index, selectedIndexes)
          doc.model->removeRow(index.row());
      }
    }
  }
}

void MainWindow::save() {
  auto doc = tabView->document();
  if (doc.isValid()) {
    if (doc.widget->isModified())
      doc.widget->save();
  }
}

void MainWindow::cancel() {
  auto doc = tabView->document();
  if (doc.isValid()) {
    if (doc.widget->isModified() && QMessageBox::question(this, title, QString("Отменить все изменения в таблице '%1'?").arg(doc.model->title())) == QMessageBox::Yes)
      doc.widget->cancel();
  }
}

void MainWindow::clear() {
  auto doc = tabView->document();
  if (doc.hasTable())
    doc.widget->clear();
}

void MainWindow::copy() {
  auto doc = tabView->document();
  if (doc.hasTable()) {
    if (doc.table->copySelection())
    QMessageBox::information(this, title, QString("Выделенные данные таблицы '%1' скопированы в буфер обмена.").arg(doc.model->title()));
  }
}

void MainWindow::paste() {
  auto doc = tabView->document();
  if (doc.hasTable())
     doc.table->pasteClipboard();
}

void MainWindow::calibration() {
  QList<Enums::documentType> list({Enums::documentType::sensor, Enums::documentType::sensortype});
  auto doc = tabView->document();
  if (doc.isValid()) {
    if (doc.model->documentType() == Enums::documentType::sensor) {
      SensorView *view = qobject_cast<SensorView*>(doc.widget->widget());
      auto id = doc.model->currentData("id");
      if (id.isValid()) { // Есть выбор записи?
        auto model = view->modeles.value(Enums::documentType::sensorcalibration);
        if (model) {
          CalibrationDlg dialog(model, id.toInt(), this);
          dialog.exec();
        }
      }
    }
  }
}

void MainWindow::up() {
  auto doc = tabView->document();
  if (doc.isValid() && doc.widget->hasUpDown())
    doc.widget->up();
}

void MainWindow::down() {
  auto doc = tabView->document();
  if (doc.isValid() && doc.widget->hasUpDown())
    doc.widget->down();
}

void MainWindow::crates() {
  QList<CrateInfo> list;
  auto result = Crate::cratesEx(list);
  if (result == OK) {
    QString s;
    if (list.length() == 0) s = "Нет подключенных устройств Lcard.";
    else {
      foreach (auto p, list)
        s.append(QString("%1 - %2 - %3\n").arg(p.sn).arg(LCEnums::string(p.type, LCEnums::LTR_CrateTypeMap)).arg(LCEnums::string(p.iface, LCEnums::LTR_CrateIfaceMap)));
      s = QString("Подключены следующие устройства:\n%1").arg(s);
    }
    QMessageBox::information(this, title, s);
  } else
    QMessageBox::warning(this, title, LCard::getErrorString(result));
}

void MainWindow::doSettings() {
  SettingsDlg dialog(settings, this);
  int accepted = dialog.exec();
  if (accepted == QDialog::Accepted) {
    auto colorScheme = settings->colorScheme();
    if ((Qt::ColorScheme)colorScheme != QGuiApplication::styleHints()->colorScheme())
      schemeHelper->applayColorScheme(colorScheme);
    tabView->closeAll();
    db->close();
    delete db;
    db = new DB(DatabaseName, settings->hostName(), settings->hostPort(), settings->databaseName(), settings->userName(), settings->password(), settings->timeout());
    loadData();
  }
}

void MainWindow::openTable(const QModelIndex &index) {
  if (index.isValid()) {
    TreeItemType data = dictionModel->get(index.row());
    ModelTableBase *model = ModelTableBase::create(data.type);
    if (model) {
      // таблица или комплексный редактор
      QWidget *editor = model->createEditView(data.title, tableActionGroup, this);
      tabView->append(editor, data.title, data.type, data.type, data.icon);
      tabView->addActions(tableActionGroup);
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
/*
void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
}

void MainWindow::showTabContextMenu(const QPoint &pos) {
  auto doc = tabView->document();
  if (doc.hasTable()) {
    QMenu menu(this);
    menu.addAction(appendAction);
    menu.addAction(saveAction);
    menu.addSeparator();
    menu.addAction(clearAction);
    menu.exec(tabView->mapToGlobal(pos));
  }
}
*/
