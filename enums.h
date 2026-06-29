#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>
#include <QMetaEnum>
#include <QMap>
#include "types.h"

class Enums : public QObject {
  Q_OBJECT
public:
  explicit Enums(QObject *parent = nullptr);

  template <typename T>
  static QMap<int, QString> create(QList<StringPair> replaces = {{"_", "-"}}) {
    QMap<int, QString> enumMap;
    QMetaEnum metaEnum = QMetaEnum::fromType<T>();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
      QString name = i == 0 ? "" : QString::fromUtf8(metaEnum.key(i));
      foreach (auto r, replaces)
        name = name.replace(r.first, r.second);
      enumMap.insert(metaEnum.value(i), name);
    }
    return enumMap;
  }
  template <typename T>
  static QMap<int, QString> create(const EnumMap &map) {
    QMap<int, QString> enumMap;
    QMetaEnum metaEnum = QMetaEnum::fromType<T>();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
      QString name = metaEnum.key(i) == 0 ? "" : map.value(i).description;
      enumMap.insert(metaEnum.value(i), name);
    }
    return enumMap;
  }
  template <typename T>
  static QString string(T key) {
    return QMetaEnum::fromType<T>().valueToKey(key);
  }

  /// Типы документов для идентификации в QTabWidget
  enum documentType : int {
    crate,
    module,
    measureunit,
    sensor,
    sensortype,
    sensorcalibration,
    sensortypecalibration,
    experiment,
  };
  Q_ENUM(documentType)

  /// Типы крейтов
  enum crateType : int {
    __crateType = 0,
    LTR_EU_2 = 1, // 2-местный портативный крейт с интерфейсами USB 2.0, Ethernet и источником питания.
    LTR_EU_8 = 2, // 8-местный крейт с интерфейсами USB 2.0, Ethernet и источником питания.
    LTR_EU_16 = 3,// 16-местный крейт с интерфейсами USB 2.0, Ethernet и источником питания.
    PXI_1045 = 4  // 18-слотовый 3U PXI крейт с стандартным AC блоком питания
  };
  Q_ENUM(crateType) // Предоставляет доступ к перечислению crateType системе метаобъектов

  /// Типы крейтов
  enum moduleType : int {
    __moduleType = 0,
    LTR11 = 11,   // Универсальный модуль АЦП с последовательным опросом каналов
    LTR114 = 114, // Универсальный прецизионный модуль АЦП с последовательным опросом каналов
    LTR212 = 212, // Специализированный модуль АЦП для тензоизмерений
    LTR27 = 27,   // Модуль АЦП с конфигурируемым числом и типом гальваноизолированных измерительных каналов
    LTR41 = 41,   // Модуль ввода дискретных сигналов с поканальной гальваноизоляцией
    LTR42 = 42,   // Модуль вывода дискретных сигналов с поканальной гальваноизоляцией
    LTR43DI4 = 43,// Универсальный модуль асинхронного цифрового ввода/вывода и синхронизации сбора данных в крейте и многокрейтовой системе, 32 канала программно объединены в 4 канала по 8 бит
    LTR51 = 51,   // Модуль - частотомер и измеритель интервалов времени
    LTR22	= 22,   // Сигма-дельта АЦП для виброакустических измерений
    LTR210 = 210, // Осциллографический модуль АЦП с частотой дискретизации до 10 МГц
    LTR24	= 24,   // Сигма-дельта АЦП для виброметрии, фазометрии, акустики, сейсмометрии
    LTR34 = 34,   // Многоканальный ЦАП для систем статического и динамического аналогового управления
  };
  Q_ENUM(moduleType)

  /// Тип градуировки
  enum calibrationType : int {
    __calibrationType = 0,
    tabular = 1,          // Табличная
    polynomial = 2,       // Полиномиальная
    thermalResistance = 3,// Термосопротивление
    multiRange = 4,       // Мультидиапазонная
    thermoPair = 5,       // Термопара
    strainGauge = 6,      // Тензометрическая
  };
  Q_ENUM(calibrationType)
  // атрибуты градуировки (можно сделать static внутри класса или cpp-файла)
  static const EnumMap calibrationTypeMap;

  /// Источник градуировки
  enum calibrationSource : int {
    __calibrationSource = 0,
    passport = 1,     // Паспорт
    throughRoute = 2, // Сквозная градуировка
  };
  Q_ENUM(calibrationSource)
  // атрибуты градуировки (можно сделать static внутри класса или cpp-файла)
  static const EnumMap calibrationSourceMap;

  /// Источник градуировки
  enum interpolationType : int {
    __interpolationType = 0,
    piecewiseLine = 1,      // Кусочно-линейная
    piecewiseLineExtra = 2, // Кусочно-линейная с экстраполяцией
  };
  Q_ENUM(interpolationType)
  // атрибуты градуировки (можно сделать static внутри класса или cpp-файла)
  static const EnumMap interpolationTypeMap;

public slots:
  EnumAttributes getAttributes(Enums::calibrationType value);
  EnumAttributes getAttributes(Enums::calibrationSource value);
  EnumAttributes getAttributes(Enums::interpolationType value);

};

#endif // ENUMS_H
