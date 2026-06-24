#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QApplication>
#include <QMouseEvent>

class CheckBoxDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  using QStyledItemDelegate::QStyledItemDelegate;
  // Переопределяем метод отрисовки
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  // Обработка клика мыши по центрированному чекбоксу
  bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};

#endif // CHECKBOXDELEGATE_H
