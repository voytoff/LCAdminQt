#ifndef ISTATEWIDGET_H
#define ISTATEWIDGET_H

#include <QtPlugin> // Required for Q_DECLARE_INTERFACE

class TableView;
class IStateWidget {
public:
  virtual ~IStateWidget() = default;
  //virtual QWidget *widget() = 0;
  virtual TableView *table() = 0;
  virtual bool isModified() const = 0;
  virtual bool save() = 0;
  virtual void cancel() = 0;
  virtual void clear() = 0;
};
Q_DECLARE_INTERFACE(IStateWidget, "com.admin.app.IStateWidget/1.0")
#endif // ISTATEWIDGET_H
