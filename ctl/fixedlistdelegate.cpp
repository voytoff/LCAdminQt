#include "fixedlistdelegate.h"

FixedListDelegate::FixedListDelegate(const QStringList &items, QObject *parent)
  : QStyledItemDelegate(parent)
  , m_items(items) {}

QWidget *FixedListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  Q_UNUSED(option);
  Q_UNUSED(index);

  QComboBox *editor = new QComboBox(parent);
  editor->setFrame(false); // Убираем рамку, чтобы редактор вписывался в ячейку
  editor->addItems(m_items);
  return editor;
}

void FixedListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
  QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
  if (comboBox) {
    // Получаем текст, который уже сохранен в базе данных
    QString currentText = index.data(Qt::EditRole).toString();
    int comboIndex = comboBox->findText(currentText);

    if (comboIndex >= 0) {
      comboBox->setCurrentIndex(comboIndex);
    }
  }
}

void FixedListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
  QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
  if (comboBox) {
    // Записываем выбранную строку в модель
    model->setData(index, comboBox->currentText(), Qt::EditRole);
  }
}

void FixedListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  Q_UNUSED(index);
  editor->setGeometry(option.rect);
}
