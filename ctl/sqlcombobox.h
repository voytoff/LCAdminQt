#ifndef SQLCOMBOBOX_H
#define SQLCOMBOBOX_H

#include <QComboBox>

class SqlComboBox : public QComboBox {
  Q_OBJECT
public:
  explicit SqlComboBox(const QString &query, QWidget *parent = nullptr);
  bool setCurrentData(const QVariant &data);

protected:
  void showPopup() override;

private:
  QString query;

signals:
};

#endif // SQLCOMBOBOX_H
