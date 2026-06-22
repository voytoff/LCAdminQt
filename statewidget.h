#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>

class StateWidget : public QWidget
{
  Q_OBJECT
public:
  explicit StateWidget(QWidget *parent = nullptr);
  bool isModified() const;

public slots:
  void setModified(bool modified);

private:
  bool m_isModified;
};

#endif // STATEWIDGET_H
