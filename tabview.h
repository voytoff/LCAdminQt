#ifndef TABVIEW_H
#define TABVIEW_H

#include <QTabWidget>
#include <QWidget>
#include <QVector>

#include "types.h"

class TabView : public QTabWidget {
  Q_OBJECT
public:
  explicit TabView(QWidget *parent = nullptr);

  /** Добавит новый или откроит существующий документ
   * @brief append
   * @param control Элемент управления
   * @param title Заголовок
   * @param type Тип документа
   * @param id Дополнтельный идентификатор
   * @param icon Иконка
   * @return
   */
  int append(QWidget *control, const QString &title, const documentType &type, const int &id = 0, const QString &icon = nullptr);
  int append(QWidget *control, const QString &title, const QVariantList &data);
  void removeTab(int index);
  void closeAll();

protected:
  int indexOf(const QVariantList &data) const;

private:

signals:

};

#endif // TABVIEW_H
