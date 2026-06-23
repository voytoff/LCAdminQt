#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>
#include <QCheckBox>

class CheckboxDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  CheckboxDelegate(QObject *parent = nullptr);

  // Отвечает за отрисовку состояния
  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

  QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
    Q_UNUSED(option)
    QCheckBox *editor = new QCheckBox(parent);
    return editor;
  }

  void setEditorData(QWidget *editor, const QModelIndex &index) const override {
    bool value = index.model()->data(index, Qt::EditRole).toBool();
    QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
    checkBox->setChecked(value);
  }

  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override {
    QCheckBox *checkBox = static_cast<QCheckBox*>(editor);
    bool value = checkBox->isChecked();
    model->setData(index, value, Qt::EditRole);
  }

  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override {
    Q_UNUSED(index)
    editor->setGeometry(option.rect);
  }
};

#endif // CHECKBOXDELEGATE_H
