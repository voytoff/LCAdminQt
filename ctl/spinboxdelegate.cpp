#include "spinboxdelegate.h"
#include <QSpinBox>

SpinBoxDelegate::SpinBoxDelegate(const int &min, const int &max, QObject *parent)
  : QStyledItemDelegate(parent)
  , min(min)
  , max(max) {}

QWidget* SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  Q_UNUSED(option)
  Q_UNUSED(index)

  QSpinBox *editor = new QSpinBox(parent);
  editor->setFrame(false); // Убираем рамку, чтобы редактор вписывался в ячейку
  editor->setMinimum(min);   // Настройте свои лимиты
  editor->setMaximum(max);

  return editor;
}

// Загружаем данные из модели в QSpinBox
void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
  int value = index.model()->data(index, Qt::EditRole).toInt();
  QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
  spinBox->setValue(value);
}

// Передаем измененные данные из QSpinBox обратно в модель
void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
  QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
  spinBox->interpretText(); // Применяем введенный текст (актуально для незавершенного ввода)
  int value = spinBox->value();
  model->setData(index, value, Qt::EditRole);
}

// Устанавливаем геометрию редактора по размеру ячейки
void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  Q_UNUSED(index)
  editor->setGeometry(option.rect);
}
