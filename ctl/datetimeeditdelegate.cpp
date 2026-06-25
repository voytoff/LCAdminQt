#include "datetimeeditdelegate.h"
#include <QDateTimeEdit>
#include "../types.h"

DateTimeEditDelegate::DateTimeEditDelegate(QObject *parent)
  : QStyledItemDelegate{parent} {}

QWidget* DateTimeEditDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const {
  QDateTimeEdit* editor = new QDateTimeEdit(parent);
  editor->setCalendarPopup(true); // Включает удобный выпадающий календарь
  editor->setDisplayFormat(dateTimeFormat);
  return editor;
}

void DateTimeEditDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
  QDateTime date = index.model()->data(index, Qt::EditRole).toDateTime();
  QDateTimeEdit* dateEdit = qobject_cast<QDateTimeEdit*>(editor);
  if (dateEdit) {
    dateEdit->setDateTime(date);
  }
}

void DateTimeEditDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
  QDateTimeEdit* dateEdit = qobject_cast<QDateTimeEdit*>(editor);
  if (dateEdit)
    model->setData(index, dateEdit->dateTime(), Qt::EditRole);
}