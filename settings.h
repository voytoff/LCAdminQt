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
  Settings();

  ColorScheme colorScheme(QVariant value = 0);
  QByteArray geometry(QByteArray value = QByteArray());
  QByteArray windowState(QByteArray value = QByteArray());

signals:
  void propertyChanged(QString name, QVariant value);
};

#endif // SETTINGS_H
