#include "settings.h"
#include <QSettings>

Settings::Settings()
  : QSettings(Company, AppName)
{}

ColorScheme Settings::colorScheme(QVariant value) {
  if (value.isValid() && value.toInt() > 0) {
    this->setValue("colorScheme", value);
    emit propertyChanged("colorScheme", this->value("colorScheme"));
  }
  auto result = this->value("colorScheme").toInt();
  return result == 0 ? ColorScheme::Light : (ColorScheme) this->value("colorScheme").toInt();
}

QByteArray Settings::geometry(QByteArray value) {
  if (!value.isEmpty())
    this->setValue("geometry", value);
  return this->value("geometry").toByteArray();
}

QByteArray Settings::windowState(QByteArray value) {
  if (!value.isEmpty())
    this->setValue("windowState", value);
  return this->value("windowState").toByteArray();
}

QByteArray Settings::splitter(QByteArray value) {
  if (!value.isEmpty())
    this->setValue("splitter", value);
  return this->value("splitter").toByteArray();
}

QString Settings::hostName(QString value) {
  if (!value.isEmpty())
    this->setValue("hostName", value);
  return this->value("hostName").toString();
}

int Settings::hostPort(int value) {
  if (value > 0)
    this->setValue("hostPort", value);
  return this->value("hostPort").toInt();
}

QString Settings::databaseName(QString value) {
  if (!value.isEmpty())
    this->setValue("databaseName", value);
  return this->value("databaseName").toString();
}

QString Settings::userName(QString value) {
  if (!value.isEmpty())
    this->setValue("userName", value);
  return this->value("userName").toString();
}

QString Settings::password(QString value) {
  if (!value.isEmpty())
    this->setValue("password", value);
  return this->value("password").toString();
}
