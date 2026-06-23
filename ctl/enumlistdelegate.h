#ifndef ENUMLISTDELEGATE_H
#define ENUMLISTDELEGATE_H

#include <QStyledItemDelegate>
#include <QComboBox>
#include <QMap>

class EnumListDelegate : public QStyledItemDelegate {
  Q_OBJECT
private:
  QMap<int, QString> m_enumMap; // Словарь: {Значение_Enum -> Текст}

public:
  // Конструктор принимает карту соответствий
  explicit EnumListDelegate(const QMap<int, QString> &enumMap, QObject *parent = nullptr);
  // Метод отвечает за ОТОБРАЖЕНИЕ текста вместо цифры, когда ячейка не редактируется
  void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override;
  // Создание QComboBox
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
  // Загрузка данных ИЗ модели В комбобокс при начале редактирования
  void setEditorData(QWidget *editor, const QModelIndex &index) const override;
  // Сохранение данных ИЗ комбобокса В модель после выбора
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
  void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // ENUMLISTDELEGATE_H
