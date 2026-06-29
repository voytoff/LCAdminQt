#include "tableview.h"
#include "mainwindow.h"
#include "types.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QString>
#include <QCloseEvent>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QItemSelectionModel>

TableView::TableView(ModelTableBase *model, const QString &title, QWidget *parent)
  : QTableView{parent} {

  setModel(model);
  // Скрываем служебные поля
  int id = model->fieldIndex("id");
  if (id > -1) // Скрываем id столбец
    hideColumn(id);
  foreach (auto column, model->hideFields()) {
    int index = model->fieldIndex(column);
    if (index > -1)
      hideColumn(index);
  }

  setWindowTitle(title);
  // Устанавливаем делегаты пользовательских редакторов
  model->setItemDelegates(this);
  // Внешний вид
  verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  verticalHeader()->setDefaultSectionSize(22); // pixels
  horizontalHeader()->setMinimumSectionSize(minColumnSize);
  resizeColumnsToContents();
  //setStyleSheet("QTableView{border:none;}"); // Убираем рамку, плохо смотрится в комплексном редакторе
}

ModelTableBase *TableView::model() const {
  return qobject_cast<ModelTableBase*>(QAbstractItemView::model());
}

int TableView::index(const QString &fieldName) const {
  return model()->fieldIndex(fieldName);
}

QWidget *TableView::widget() {
  return this;
}

TableView *TableView::table() {
  return this;
}

bool TableView::isModified() const {
  return model()->isDirty();
}

bool TableView::save() {
  return model()->submitAll();
}

void TableView::cancel() {
  model()->revertAll();
}

void TableView::clear() {
  // Получаем список всех выделенных ячеек
  QModelIndexList selectedIndexes = selectionModel()->selectedIndexes();
  // Проверяем, есть ли выделенные ячейки
  if (selectedIndexes.isEmpty()) {
    return;
  }
  // Записываем пустые значения в модель
  foreach (auto index, selectedIndexes) {
    // Проверяем, можно ли редактировать ячейку (опционально)
    //if (index.flags() & Qt::ItemIsEditable)
    model()->setData(index, QVariant(), Qt::EditRole);
  }
}

QString TableView::title() const {
  return windowTitle();
}

void TableView::hide(const int &index, const bool &hidden) {
  setColumnHidden(index, hidden);
}

void TableView::hide(const QString &name, const bool &hidden) {
  setColumnHidden(model()->fieldIndex(name), hidden);
}

void TableView::keyPressEvent(QKeyEvent *event) {
  // Перехватываем Ctrl+C (Копирование)
  if (event->matches(QKeySequence::Copy)) {
    copySelection();
    event->accept();
    return;
  }
  // Перехватываем Ctrl+V (Вставка)
  if (event->matches(QKeySequence::Paste)) {
    pasteClipboard();
    event->accept();
    return;
  }
  QTableView::keyPressEvent(event);
}

bool TableView::copySelection() {
  QItemSelectionModel *selectModel = selectionModel();
  if (!selectModel || !selectModel->hasSelection()) return false;

  QModelIndexList indexes = selectModel->selectedIndexes();
  // Сортируем индексы (Qt возвращает их в порядке кликов, а нам нужен порядок таблицы)
  std::sort(indexes.begin(), indexes.end());

  QString copiedText;
  for (int i = 0; i < indexes.size(); ++i) {
    // Извлекаем текст ячейки, который видит пользователь
    copiedText += model()->data(indexes.at(i), Qt::DisplayRole).toString();

    if (i < indexes.size() - 1) {
      // Если следующая ячейка на той же строке — ставим Табуляцию, иначе — Перенос строки
      if (indexes.at(i).row() == indexes.at(i + 1).row()) {
        copiedText += "\t";
      } else {
        copiedText += "\n";
      }
    }
  }
  copiedText += "\n";

  QApplication::clipboard()->setText(copiedText); // Публикуем в системный буфер
  return true;
}

bool TableView::pasteClipboard() {
  // 1. Проверяем буфер обмена и наличие модели
  const QMimeData *mimeData = QApplication::clipboard()->mimeData();
  if (!mimeData || !mimeData->hasText() || !model()) {
    return false;
  }

  QString text = mimeData->text();
  if (text.isEmpty()) return false;

  // 2. Логика определения начальной ячейки (row, col)
  QModelIndex currentIdx = currentIndex();
  int startRow = 0;
  int startCol = 0;

  if (currentIdx.isValid()) {
    // Если ячейка выбрана — вставляем начиная с нее
    startRow = currentIdx.row();
    startCol = currentIdx.column();
  } else {
    // Если ячейка НЕ выбрана ИЛИ таблица пустая:
    startRow = model()->rowCount(); // Вставляем в самый конец (для пустой будет 0)

    // Ищем первый ВИДИМЫЙ столбец на основе заголовка таблицы
    QHeaderView *header = horizontalHeader();
    bool foundVisible = false;

    if (header) {
      // Проходим по колонкам в порядке их отображения на экране (visualIndex)
      for (int visualIdx = 0; visualIdx < header->count(); ++visualIdx) {
        int logicalIdx = header->logicalIndex(visualIdx);

        if (!header->isSectionHidden(logicalIdx)) {
          startCol = logicalIdx;
          foundVisible = true;
          break; // Нашли самый левый видимый столбец
        }
      }
    }

    // Фолбэк на случай, если заголовок недоступен или все колонки скрыты
    if (!foundVisible) {
      startCol = 0;
    }
  }

  // 3. Подготовка текстовых данных
  text.replace("\r\n", "\n");
  QStringList rows = text.split('\n', Qt::SkipEmptyParts);
  if (rows.isEmpty()) return false;

  int totalRowsToInsert = rows.size();
  int currentModelRowCount = model()->rowCount();
  int lastRequiredRow = startRow + totalRowsToInsert - 1;

  // 4. Динамическое добавление строк в модель (OnManualSubmit)
  if (lastRequiredRow >= currentModelRowCount) {
    int rowsNeeded = lastRequiredRow - currentModelRowCount + 1;
    if (!model()->insertRows(currentModelRowCount, rowsNeeded)) {
      QMessageBox::information(parentWidget(), ::title, QString("Не удалось выделить дополнительные строки в таблице '%1'?").arg(title()));
      return false; // Не удалось выделить строки в кэше
    }
  }

  // 5. Поячеечная вставка данных
  for (int i = 0; i < rows.size(); ++i) {
    int currentRow = startRow + i;
    QStringList columns = rows.at(i).split('\t');

    for (int j = 0; j < columns.size(); ++j) {
      int currentCol = startCol + j;

      // Защита от выхода за пределы общего числа колонок СУБД
      if (currentCol >= model()->columnCount()) break;

      QModelIndex targetIndex = model()->index(currentRow, currentCol);
      QString cellValue = columns.at(j).trimmed();

      // Передаем данные в кэш модели
      model()->setData(targetIndex, cellValue, Qt::EditRole);
    }
  }

  // 6. Установка фокуса на стартовую ячейку вставки
  QModelIndex newFocusIndex = model()->index(startRow, startCol);
  if (newFocusIndex.isValid()) {
    setCurrentIndex(newFocusIndex);
  }
  return true;
}

void TableView::closeEvent(QCloseEvent *event) {
  if (isModified()) {
    auto response = QMessageBox::question(qobject_cast<MainWindow*>(parent()), title(), QString("Данные таблицы '%1' изменены. Сохранить эти изменения?").arg(title()), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (response == QMessageBox::Yes)
      save();
    else if (response == QMessageBox::Cancel) {
      event->ignore();
      return;
    }
  }
  event->accept();
}
