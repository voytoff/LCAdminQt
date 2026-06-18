#ifndef CRATEVIEW_H
#define CRATEVIEW_H

#include <QWidget>

namespace Ui {
class CrateView;
}

class CrateView : public QWidget
{
  Q_OBJECT

public:
  explicit CrateView(QWidget *parent = nullptr);
  ~CrateView();

private:
  Ui::CrateView *ui;
};

#endif // CRATEVIEW_H
