#include "checkboxdelegate.h"
#include <QApplication>
#include <QPainter>
#include <QStyleOptionButton>

void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  // Получаем состояние чекбокса из модели
  QVariant checkState = index.data(Qt::CheckStateRole);

  if (checkState.isValid()) {
    // Подготавливаем базовые опции отрисовки ячейки (фоны, выделения, фокус)
    QStyleOptionViewItem viewOption = option;
    initStyleOption(&viewOption, index);

    // Очищаем текст в опциях, чтобы он случайно не наложился на чекбокс
    viewOption.text.clear();

    // 1. Рисуем стандартный фон ячейки (подсветка при наведении, выделение строки)
    QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &viewOption, painter, option.widget);

    // 2. Инициализируем настройки для рисования самого чекбокса
    QStyleOptionButton checkBoxOption;
    checkBoxOption.state |= QStyle::State_Enabled;

    // Устанавливаем состояние чекбокса в зависимости от данных модели
    if (checkState.value<Qt::CheckState>() == Qt::Checked) {
      checkBoxOption.state |= QStyle::State_On;
    } else {
      checkBoxOption.state |= QStyle::State_Off;
    }

    // Вычисляем стандартный размер чекбокса для текущей ОС
    checkBoxOption.rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkBoxOption, option.widget);

    // Формируем координаты строго по центру ячейки
    int x = option.rect.x() + (option.rect.width() - checkBoxOption.rect.width()) / 2;
    int y = option.rect.y() + (option.rect.height() - checkBoxOption.rect.height()) / 2;
    checkBoxOption.rect.moveTo(x, y);

    // 3. Отрисовываем чекбокс поверх фона
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkBoxOption, painter);
  } else {
    // Если это не bool колонка, используем стандартное поведение
    QStyledItemDelegate::paint(painter, option, index);
  }
}

bool CheckBoxDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
  if (event->type() == QEvent::MouseButtonRelease) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

    // Проверяем, что клик был именно левой кнопкой мыши
    if (mouseEvent->button() != Qt::LeftButton) {
      return false;
    }

    // Пересчитываем координаты чекбокса (так же, как в paint)
    QStyleOptionButton checkBoxOption;
    QRect checkBoxRect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkBoxOption);
    QPoint center(option.rect.x() + option.rect.width() / 2 - checkBoxRect.width() / 2,
                  option.rect.y() + option.rect.height() / 2 - checkBoxRect.height() / 2);
    QRect finalRect(center, checkBoxRect.size());

    // Если кликнули внутри чекбокса — инвертируем его состояние
    if (finalRect.contains(mouseEvent->pos())) {
      Qt::CheckState currentState = static_cast<Qt::CheckState>(index.data(Qt::CheckStateRole).toInt());
      Qt::CheckState newState = (currentState == Qt::Checked) ? Qt::Unchecked : Qt::Checked;
      return model->setData(index, newState, Qt::CheckStateRole);
    }
  }
  return QStyledItemDelegate::editorEvent(event, model, option, index);
}
