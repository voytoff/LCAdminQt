#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class SpinBoxDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  explicit SpinBoxDelegate(const int &min = 0, const int &max = 100, QObject *parent = nullptr);
  // Создаем виджет для редактирования
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  // Загружаем данные из модели в виджет
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  // Передаем данные из виджета в модель
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
  // Задаем геометрию для виджета
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
  int min;
  int max;
};

#endif // SPINBOXDELEGATE_H
