#ifndef COMPLEXVIEWBASE_H
#define COMPLEXVIEWBASE_H

#include "../istatewidget.h"
#include "../settings.h"
#include "../tableview.h"
#include "tableviewcache.h"
#include "modelviewcache.h"

#include <QWidget>
#include <QSplitter>
#include <QGridLayout>

class ComplexViewBase : public QWidget, public IStateWidget {
  Q_OBJECT
  Q_INTERFACES(IStateWidget)

public:
  explicit ComplexViewBase(QWidget *parent = nullptr);

  void setOrientation(Qt::Orientation orientation);
  void addTable(Enums::documentType type, TableView *table);
  void addWidget(QWidget *widget);
  void addLayout(QLayout *layout);
  /** Используем для вызова виртуальных и переопределенных методов */
  virtual void init() {}

  QWidget *widget() override;
  /** Возвращает текущий TableView в фокусе */
  TableView *table() override;
  bool isModified() const override;
  bool save() override;
  void cancel() override;
  void clear() override;

  /** Возвращает объект QSplitter */
  QSplitter *getSplitter();

  ModelViewCache modeles;

protected:
  void closeEvent(QCloseEvent *event) override;
  void showEvent(QShowEvent *event) override;
  virtual void restoreLayout();
  virtual void saveLayout();

  TableViewCache tables;

private:
  QGridLayout *layout;
  QSplitter *splitter;
  Settings *settings;

};

#endif // COMPLEXVIEWBASE_H
