#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "modeltablebase.h"
#include "istatewidget.h"
#include <QTableView>
#include <QModelIndex>
#include <QList>

class TableView : public QTableView, public IStateWidget {
  Q_OBJECT
  Q_INTERFACES(IStateWidget)

public:
  explicit TableView(ModelTableBase *model, const QString &title, QWidget *parent = nullptr);

  int index(const QString & fieldName) const;
  bool isModified() const override;
  bool save() override;
  void cancel() override;
  ModelTableBase *model() const {return qobject_cast<ModelTableBase*>(QAbstractItemView::model());}

private:
  QString title;

protected:
  void closeEvent(QCloseEvent *event) override;

signals:

};

#endif // TABLEVIEW_H
