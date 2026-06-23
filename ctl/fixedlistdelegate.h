#ifndef FIXEDLISTDELEGATE_H
#define FIXEDLISTDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>

class FixedListDelegate : public QStyledItemDelegate {
  Q_OBJECT
private:
  QStringList m_items; // Фиксированный список значений

public:
  explicit FixedListDelegate(const QStringList &items, QObject *parent = nullptr);
  // Создание виджета-редактора (QComboBox)
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  // Перенос данных из модели БД в QComboBox при открытии
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  // Сохранение выбранного значения из QComboBox обратно в модель БД
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
  // Обновление геометрии комбобокса, чтобы он идеально вписывался в ячейку
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // FIXEDLISTDELEGATE_H
