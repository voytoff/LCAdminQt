#ifndef MODULEVIEW_H
#define MODULEVIEW_H

#include <QDockWidget>

namespace Ui {
class ModuleView;
}

class ModuleView : public QDockWidget
{
  Q_OBJECT

public:
  explicit ModuleView(QWidget *parent = nullptr);
  ~ModuleView();

private:
  Ui::ModuleView *ui;
};

#endif // MODULEVIEW_H
