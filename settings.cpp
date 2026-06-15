#include "settings.h"
#include <QSettings>

Settings::Settings() : QSettings(Company, AppName) {}

ColorScheme Settings::colorScheme(QVariant value) {
  if (value.isValid() && value.toInt() > 0) {
    this->setValue("colorScheme", value);
    emit propertyChanged("colorScheme", this->value("colorScheme"));
  }
  auto result = this->value("colorScheme").toInt();
  return result == 0 ? ColorScheme::Light : (ColorScheme)this->value("colorScheme").toInt();
}
