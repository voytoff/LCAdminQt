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
  //QWidget *widget() override;
  TableView *table() override;
  bool isModified() const override;
  bool save() override;
  void cancel() override;
  void clear() override;
  void setModel(QAbstractItemModel *model) override;
  ModelTableBase *model() const;
  QString title() const;
  void hide(const int &index, const bool &hidden = true);
  void hide(const QString &name, const bool &hidden = true);

protected:
  void closeEvent(QCloseEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

private:
  QString nodeName;

public slots:
  bool copySelection();
  bool pasteClipboard();

signals:

};

#endif // TABLEVIEW_H
