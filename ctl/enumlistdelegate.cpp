#include "enumlistdelegate.h"

EnumListDelegate::EnumListDelegate(const QMap<int, QString> &enumMap, QObject *parent)
  : QStyledItemDelegate(parent), m_enumMap(enumMap) {}

void EnumListDelegate::initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const {
  // Вызываем базовую инициализацию
  QStyledItemDelegate::initStyleOption(option, index);
  // Получаем числовое значение enum из базы данных
  int enumValue = index.data(Qt::DisplayRole).toInt();
  // Если это значение есть в нашем словаре, подменяем текст для отрисовки
  if (m_enumMap.contains(enumValue)) {
    option->text = m_enumMap.value(enumValue);
  }
}

QWidget *EnumListDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  Q_UNUSED(option);
  Q_UNUSED(index);

  QComboBox *editor = new QComboBox(parent);
  editor->setFrame(false); // Убираем рамку, чтобы редактор вписывался в ячейку
  // Наполняем комбобокс: видимый ТЕКСТ и скрытый ENUM в UserRole
  for (auto it = m_enumMap.constBegin(); it != m_enumMap.constEnd(); ++it)
    editor->addItem(it.value(), it.key());
  return editor;
}

void EnumListDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
  QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
  if (comboBox) {
    // Получаем текущее числовое значение enum из базы данных
    int currentEnum = index.data(Qt::EditRole).toInt();
    // Ищем элемент в комбобоксе, у которого UserRole равен нашему enum
    int comboIndex = comboBox->findData(currentEnum, Qt::UserRole);

    if (comboIndex >= 0)
      comboBox->setCurrentIndex(comboIndex);
  }
}

void EnumListDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
  QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
  if (comboBox) {
    // Получаем скрытое числовое значение (enum), привязанное к выбранной строке
    int selectedEnum = comboBox->currentData(Qt::UserRole).toInt();
    // Записываем число обратно в SQL-модель
    model->setData(index, selectedEnum, Qt::EditRole);
  }
}

void EnumListDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  Q_UNUSED(index);
  editor->setGeometry(option.rect);
}
