#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "modeltablebase.h"
#include <QTableView>
#include <QModelIndex>
#include <QList>

class TableView : public QTableView {
  Q_OBJECT
public:
  explicit TableView(ModelTableBase *model, const QString &title, QWidget *parent = nullptr);

  int index(const QString & fieldName) const;
  bool isModified() const;
  bool save();
  void cancel();

private:
  ModelTableBase *model;
  QString name;

protected:
  void closeEvent(QCloseEvent *event) override;

signals:

};

#endif // TABLEVIEW_H
