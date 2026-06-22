#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QObject>

using StringPair = std::pair<QString, QString>;

const QString title = "Администратор";
const QString ready = "Готово";
const int readyTimeout = 5000;
const int minColumnSize = 100;

/* Иконки */
const QString icon_crate = ":/images/db/crate.png";
const QString icon_cratetype = ":/images/db/cratetype.png";
const QString icon_module = ":/images/db/module.png";
const QString icon_moduletype = ":/images/db/moduletype.png";
const QString icon_calibration = ":/images/db/calibration.png";

enum documentType : int {
  cratetype,
  crate,
  moduletype,
  module,
  calibration,
};

class DocumentID {
public:
  DocumentID(const documentType &type, const int &id) {
    this->type = type;
    this->id = id;
  }
  int index;
  documentType type;
  int id;
  friend bool operator==(const DocumentID& s1, const DocumentID& s2) {
    return (s1.id == s2.id) && (s1.type == s2.type);
  }
  friend bool operator!=(const DocumentID& s1, const DocumentID& s2) {
    return !(s1 == s2);
  }
};
Q_DECLARE_METATYPE(DocumentID)

#endif // TYPES_H
