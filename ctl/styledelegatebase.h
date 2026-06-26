#ifndef STYLEDELEGATEBASE_H
#define STYLEDELEGATEBASE_H

#include <QStyledItemDelegate>
#include <QDateTimeEdit>

class StyleDelegateBase : public QStyledItemDelegate {
  Q_OBJECT
public:
  explicit StyleDelegateBase(QObject *parent = nullptr);

protected:
  void configureDateEdit(QDateTimeEdit *editor);

};

#endif // STYLEDELEGATEBASE_H
