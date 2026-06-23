#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>
#include <QMetaEnum>
#include <QMap>

class Enums : public QObject {
  Q_OBJECT
public:
  explicit Enums(QObject *parent = nullptr);

  template <typename T>
  static QMap<int, QString> create() {
    QMap<int, QString> enumMap;
    QMetaEnum metaEnum = QMetaEnum::fromType<T>();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
      QString name = QString::fromUtf8(metaEnum.key(i)).replace("_", "-");
      if (name == "-") name = "";
      enumMap.insert(metaEnum.value(i), name);
    }
    return enumMap;
  }

  /// Типы крейтов
  enum crateType : int {
    _ = 0,
    LTR_EU_2 = 1, // 2-местный портативный крейт с интерфейсами USB 2.0, Ethernet и источником питания.
    LTR_EU_8 = 2, // 8-местный крейт с интерфейсами USB 2.0, Ethernet и источником питания.
    LTR_EU_16 = 3,// 16-местный крейт с интерфейсами USB 2.0, Ethernet и источником питания.
    PXI_1045 = 4  // 18-слотовый 3U PXI крейт с стандартным AC блоком питания
  };

  Q_ENUM(crateType) // Предоставляет доступ к перечислению crateType системе метаобъектов
};

#endif // ENUMS_H
