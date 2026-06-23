#include "checkboxdelegate.h"
#include <QApplication>

CheckboxDelegate::CheckboxDelegate(QObject *parent)
: QStyledItemDelegate(parent) {}

void CheckboxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
  // Получаем текущее значение bool из модели
  bool value = index.data(Qt::DisplayRole).toBool();

  // Заполняем опции элемента стиля (например, чтобы знать выделен ли он)
  QStyleOptionViewItem opt = option;
  initStyleOption(&opt, index);

  // Удаляем текстовое представление, оставляем только индикатор
  opt.text.clear();
  opt.features |= QStyleOptionViewItem::HasCheckIndicator;
  opt.state = value ? (opt.state | QStyle::State_On) : (opt.state | QStyle::State_Off);

  // Отрисовываем сам чекбокс средствами текущего стиля ОС
  QApplication::style()->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter);
  QApplication::style()->drawPrimitive(QStyle::PE_IndicatorItemViewItemCheck, &opt, painter);

}