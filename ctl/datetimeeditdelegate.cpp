#include "datetimeeditdelegate.h"
#include <QDateTimeEdit>
#include <QCalendar>
#include <QCalendarWidget>
#include "../types.h"

DateTimeEditDelegate::DateTimeEditDelegate(QObject *parent)
  : QStyledItemDelegate{parent} {}

QWidget* DateTimeEditDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const {
  QDateTimeEdit* editor = new QDateTimeEdit(parent);
  editor->setCalendarPopup(true); // Включает удобный выпадающий календарь
  editor->setDisplayFormat(dateTimeFormat);
  auto w = editor->calendarWidget();
  w->setFirstDayOfWeek(Qt::DayOfWeek::Monday);
  w->setSelectionMode(QCalendarWidget::SelectionMode::SingleSelection);
  w->setHorizontalHeaderFormat(QCalendarWidget::HorizontalHeaderFormat::SingleLetterDayNames);
  w->setVerticalHeaderFormat(QCalendarWidget::VerticalHeaderFormat::ISOWeekNumbers);
  w->setMinimumDate(QDate(2000, 1, 1));
  w->setMaximumDate(QDate(QDate::currentDate().year() + 1, 1, 1));
  w->setGridVisible(true);
  return editor;
}

void DateTimeEditDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const {
  QDateTime date = index.model()->data(index, Qt::EditRole).toDateTime();
  QDateTimeEdit* dateEdit = qobject_cast<QDateTimeEdit*>(editor);
  if (dateEdit) dateEdit->setDateTime(date);
}

void DateTimeEditDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const {
  QDateTimeEdit* dateEdit = qobject_cast<QDateTimeEdit*>(editor);
  if (dateEdit) model->setData(index, dateEdit->dateTime(), Qt::EditRole);
}

QString DateTimeEditDelegate::displayText(const QVariant &value, const QLocale &locale) const {
  // Проверяем, содержит ли объект тип QDateTime
  if (value.userType() == QMetaType::QDateTime) return value.toDateTime().toString(dateTimeFormat);
  return QStyledItemDelegate::displayText(value, locale);
}