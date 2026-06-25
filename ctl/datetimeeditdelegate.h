#ifndef DATETIMEEDITDELEGATE_H
#define DATETIMEEDITDELEGATE_H

#include <QStyledItemDelegate>

class DateTimeEditDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  using QStyledItemDelegate::QStyledItemDelegate;
  // Конструктор принимает карту соответствий
  explicit DateTimeEditDelegate(QObject *parent = nullptr);
  // Создает виджет QDateEdit при переходе в режим редактирования
  QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
  // Переносит данные из модели в QDateEdit
  void setEditorData(QWidget* editor, const QModelIndex& index) const override;
  // Сохраняет измененную дату из QDateEdit обратно в модель
  void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};
#endif // DATETIMEEDITDELEGATE_H
