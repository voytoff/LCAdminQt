#include "styledelegatebase.h"
#include <QCalendar>
#include <QCalendarWidget>
#include "../types.h"

StyleDelegateBase::StyleDelegateBase(QObject *parent)
  : QStyledItemDelegate{parent} {}

void StyleDelegateBase::configureDateEdit(QDateTimeEdit *editor) {
  editor->setCalendarPopup(true); // Включает удобный выпадающий календарь
  //if (editor.isde)
  editor->setDisplayFormat(dateTimeFormat);
  auto w = editor->calendarWidget();
  w->setFirstDayOfWeek(Qt::DayOfWeek::Monday);
  w->setSelectionMode(QCalendarWidget::SelectionMode::SingleSelection);
  w->setHorizontalHeaderFormat(QCalendarWidget::HorizontalHeaderFormat::SingleLetterDayNames);
  w->setVerticalHeaderFormat(QCalendarWidget::VerticalHeaderFormat::ISOWeekNumbers);
  w->setMinimumDate(QDate(2000, 1, 1));
  w->setMaximumDate(QDate(QDate::currentDate().year() + 1, 1, 1));
  w->setGridVisible(true);

}
