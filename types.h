#ifndef TYPES_H
#define TYPES_H

#include "istatewidget.h"
#include <QString>
#include <QObject>
#include <QMap>

struct EnumAttributes {
  QString description;
  QVariantList param;
};

using StringPair = std::pair<QString, QString>;
using EnumMap = QMap<int, EnumAttributes>;

class ModelTableBase;
class TableView;
struct DocumentIdent {
  IStateWidget* widget = nullptr;
  ModelTableBase* model = nullptr;
  TableView *table = nullptr;
  bool isValid() {
    return model && widget;
  }
  bool hasTable() {
    return table;
  }
};

template<typename TSource, typename TDest>
TDest &cast(const TSource &source) {
  return dynamic_cast<TDest>(source);
}

template<typename TSource, typename TDest>
TDest &cast(const TSource &source, std::function<TDest(TSource)>& callback) {
  return callback(source);
}

const QString title = "Администратор";
const QString ready = "Готово";
const int readyTimeout = 5000;
const int minColumnSize = 100;
const QString dateFormat = "dd.MM.yyyy";
const QString dateTimeFormat = "dd.MM.yyyy HH:mm:ss";
const QString timeFormat = "HH:mm:ss,ff";

/// Иконки
//const QString icon_cratetype = ":/images/db/cratetype.png";
const QString icon_crate = ":/images/db/crate.png";
const QString icon_moduletype = ":/images/db/moduletype.png";
const QString icon_module = ":/images/db/module.png";
//const QString icon_calibration = ":/images/db/calibration.png";
const QString icon_measureunit = ":/images/db/measureunit.png";
const QString icon_sensortype = ":/images/db/sensortype.png";
const QString icon_sensor = ":/images/db/sensor.png";
const QString icon_experiment = ":/images/db/experiment.png";

#endif // TYPES_H
