#ifndef CUSTOMVIEWBASE_H
#define CUSTOMVIEWBASE_H

#include "../istatewidget.h"
#include "../settings.h"
#include "../tableview.h"
#include "tableviewcache.h"
#include "modelviewcache.h"

#include <QWidget>
#include <QSplitter>
#include <QGridLayout>

class CustomViewBase : public QWidget, public IStateWidget {
  Q_OBJECT
  Q_INTERFACES(IStateWidget)

public:
  explicit CustomViewBase(QWidget *parent = nullptr);

  void setOrientation(Qt::Orientation orientation);
  void addTable(Enums::documentType type, TableView *table);
  void addWidget(QWidget *widget);
  void addLayout(QLayout *layout);

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

#endif // CUSTOMVIEWBASE_H
