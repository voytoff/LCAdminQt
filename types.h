#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QObject>

const QString title = "Администратор";
const QString ready = "Готово";
const int readyTimeout = 5000;

enum documentType : int {
  crate,
  module,
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
