#ifndef DOCBASE_H
#define DOCBASE_H

#include <QDockWidget>

class DocBase : public QDockWidget {
  Q_OBJECT
public:
  explicit DocBase(QWidget *widget, QWidget *parent = nullptr);
  explicit DocBase(const QString &title, QWidget *widget, QWidget *parent = nullptr);

signals:
};

#endif // DOCBASE_H
