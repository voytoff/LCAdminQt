#ifndef ISTATEWIDGET_H
#define ISTATEWIDGET_H

#include <QtPlugin> // Required for Q_DECLARE_INTERFACE

class IStateWidget {
public:
  virtual ~IStateWidget() = default;
  virtual bool isModified() const = 0;
  virtual bool save() = 0;
  virtual void cancel() = 0;
};
Q_DECLARE_INTERFACE(IStateWidget, "com.admin.app.IStateWidget/1.0")
#endif // ISTATEWIDGET_H
