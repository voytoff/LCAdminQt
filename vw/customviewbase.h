#ifndef CUSTOMVIEWBASE_H
#define CUSTOMVIEWBASE_H

#include "../settings.h"

#include <QWidget>
#include <QSplitter>
#include <QGridLayout>

class CustomViewBase : public QWidget {
  Q_OBJECT
public:
  explicit CustomViewBase(QWidget *parent = nullptr);

  void setOrientation(Qt::Orientation orientation);
  void addWidget(QWidget *widget);
  void addLayout(QLayout *layout);

  QSplitter *getSplitter();

protected:
  void closeEvent(QCloseEvent *event) override;
  void showEvent(QShowEvent *event) override;
  virtual void restoreLayout();
  virtual void saveLayout();

private:
  QGridLayout *layout;
  QSplitter *splitter;
  Settings *settings;

signals:
};

#endif // CUSTOMVIEWBASE_H
