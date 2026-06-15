#ifndef SETTINGS_H
#define SETTINGS_H

#include "SchemeHelper_global.h"
#include <QSettings>

const QString Company = "NIIHM";
const QString AppName = "LCAdmin";

class Settings : public QSettings {
  Q_OBJECT
public:
  Settings();

  ColorScheme colorScheme(QVariant value = 0);

signals:
  void propertyChanged(QString name, QVariant value);
};

#endif // SETTINGS_H
