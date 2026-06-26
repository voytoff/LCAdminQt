#ifndef TABVIEW_H
#define TABVIEW_H

#include <QTabWidget>
#include <QWidget>
#include <QVector>

#include "tableview.h"

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
  int append(QWidget *widget, const QString &title, const Enums::documentType &type, const int &id = 0, const QString &icon = nullptr);
  int append(QWidget *widget, const QString &title, const QVariantList &data);
  bool removeTab(int index);
  bool closeAll();
  template<typename T>
  T *view() const {
    return currentIndex() < 0 ? nullptr : qobject_cast<T*>(widget(currentIndex()));
  }
  template<typename T>
  T *model() const {
    auto vw = view<TableView>();
    return vw ? qobject_cast<T*>(vw->model()) : nullptr;
  }

protected:
  void closeEvent(QCloseEvent *event) override;
  int indexOf(const QVariantList &data) const;
  void tabRemoved(int index) override;
  void tabInserted(int index) override;

signals:
  void inserted(int index);
  void removed(int index);

};

#endif // TABVIEW_H
