#include "dateeditdelegate.h"
#include <QDateEdit>
#include "../types.h"

DateEditDelegate::DateEditDelegate(QObject *parent)
  : QStyledItemDelegate{parent} {}

QWidget* DateEditDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const {
  QDateEdit* editor = new QDateEdit(parent);
  editor->setCalendarPopup(true); // Включает удобный выпадающий календарь
  editor->setDisplayFormat(dateFormat);
  return editor;
}

void DateEditDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
  QDate date = index.model()->data(index, Qt::EditRole).toDate();
  QDateEdit* dateEdit = qobject_cast<QDateEdit*>(editor);
  if (dateEdit) dateEdit->setDate(date);
}

void DateEditDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
  QDateEdit* dateEdit = qobject_cast<QDateEdit*>(editor);
  if (dateEdit) model->setData(index, dateEdit->date(), Qt::EditRole);
}