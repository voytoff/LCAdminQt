#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QByteArray>
#include <QVariant>
#include "SchemeHelper_global.h"

const QString Company = "NIIHM";
const QString AppName = "LCAdmin";

class Settings : public QSettings
{
  Q_OBJECT
public:
  Settings(QObject *parent = nullptr);

  ColorScheme colorScheme(QVariant value = 0);
  QByteArray geometry(QByteArray value = QByteArray());
  QByteArray windowState(QByteArray value = QByteArray());
  QByteArray splitter(QByteArray value = 0);
  QByteArray splitter2(QByteArray value = 0);
  QByteArray splitter3(QByteArray value = 0);

  QString hostName(QString value = nullptr);
  int hostPort(int value = 0);
  QString databaseName(QString value = nullptr);
  QString userName(QString value = nullptr);
  QString password(QString value = nullptr);
  int timeout(int value = 0);

signals:
  void propertyChanged(QString name, QVariant value);
};

#endif // SETTINGS_H