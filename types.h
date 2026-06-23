#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QObject>

using StringPair = std::pair<QString, QString>;

const QString title = "Администратор";
const QString ready = "Готово";
const int readyTimeout = 5000;
const int minColumnSize = 100;

/// Иконки
//const QString icon_cratetype = ":/images/db/cratetype.png";
const QString icon_crate = ":/images/db/crate.png";
const QString icon_moduletype = ":/images/db/moduletype.png";
const QString icon_module = ":/images/db/module.png";
const QString icon_calibration = ":/images/db/calibration.png";
const QString icon_measureunit = ":/images/db/measureunit.png";
const QString icon_sensortype = ":/images/db/sensortype.png";
const QString icon_sensor = ":/images/db/sensor.png";

/// Типы документов для идентификации в QTabWidget
enum documentType : int {
  cratetype,
  crate,
  moduletype,
  module,
  calibration,
  measureunit,
  sensortype,
  sensor,
};

#endif // TYPES_H
