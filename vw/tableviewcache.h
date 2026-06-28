#ifndef TABLEVIEWCACHE_H
#define TABLEVIEWCACHE_H

#include "../tableview.h"
#include "../enums.h"
#include <QHash>

class TableViewCache : public QHash<Enums::documentType, TableView*> {
public:
  explicit TableViewCache();

  bool isModified() const;
  bool save();
  void cancel();
  void clear();
  TableView * first();
};

#endif // TABLEVIEWCACHE_H
