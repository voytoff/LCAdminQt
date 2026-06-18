#ifndef MODULEVIEW_H
#define MODULEVIEW_H

#include <QScrollArea>

namespace Ui {
class ModuleView;
}

class ModuleView : public QScrollArea
{
  Q_OBJECT

public:
  explicit ModuleView(QWidget *parent = nullptr);
  ~ModuleView();

private:
  Ui::ModuleView *ui;
};

#endif // MODULEVIEW_H
