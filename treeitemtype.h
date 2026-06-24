#ifndef TREEITEMTYPE_H
#define TREEITEMTYPE_H

#include <qcontainerfwd.h>
#include <qobject.h>
#include <qvariant.h>
#include "enums.h"

struct TreeItemType {
  Enums::documentType type; /*тип документа*/
  QString title; /*заголовок*/
  QString table; /*имя таблицы*/
  QString icon; /*иконка*/
  QVariant at(const int &index) const {
    switch (index) {
    case 0: return type;
    case 1: return title;
    case 2: return table;
    case 3: return icon;
    default: return QVariant();
    }
  }
  static int length() {return 4;}
};

#endif // TREEITEMTYPE_H
