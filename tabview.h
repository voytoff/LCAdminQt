#ifndef TABVIEW_H
#define TABVIEW_H

#include <QTabWidget>
#include <QWidget>
#include <QVector>

#include "types.h"

class TabView : public QTabWidget {
  Q_OBJECT
public:
  explicit TabView(QWidget *parent = nullptr);

  int append(QWidget *control, const QString &title, const documentType &type, const int &id = 0);
  int append(QWidget *control, const QString &title, const QVariantList &data);
  void remove(const int &index);

protected:
  int indexOf(const QVariantList &data) const;
//  void setTabData(const documentType &type, const int &id = 0);

private:
  QVector<DocumentID*> *tabs;

signals:

};

#endif // TABVIEW_H
