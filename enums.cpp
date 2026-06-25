#include "enums.h"
#include "QMetaEnum"

Enums::Enums(QObject *parent)
  : QObject{parent} {}

const EnumMap Enums::calibrationTypeMap = {
  {Enums::calibrationType::tabular, {"Табличная"}},
  {Enums::calibrationType::polynomial, {"Полиномиальная"}},
  {Enums::calibrationType::thermalResistance, {"Термосопротивление"}},
  {Enums::calibrationType::multiRange, {"Мультидиапазонная"}},
  {Enums::calibrationType::thermoPair, {"Термопара"}},
  {Enums::calibrationType::strainGauge, {"Тензометрическая"}}
};

const EnumMap Enums::calibrationSourceMap = {
  {Enums::calibrationSource::passport, {"Паспорт"}},
  {Enums::calibrationSource::throughRoute, {"Сквозная градуировка"}},
};

const EnumMap Enums::interpolationTypeMap = {
  {Enums::interpolationType::piecewiseLine, {"Кусочно-линейная"}},
  {Enums::interpolationType::piecewiseLineExtra, {"Кусочно-линейная с экстраполяцией"}},
};

EnumAttributes Enums::getAttributes(calibrationType value) {
  return calibrationTypeMap.value(value);
}

EnumAttributes Enums::getAttributes(calibrationSource value) {
  return calibrationSourceMap.value(value);
}

EnumAttributes Enums::getAttributes(interpolationType value) {
  return interpolationTypeMap.value(value);
}
