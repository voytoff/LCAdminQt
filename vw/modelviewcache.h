#ifndef MODELVIEWCACHE_H
#define MODELVIEWCACHE_H

#include "../enums.h"
#include <QHash>

class ModelViewCache : public QHash<Enums::documentType, ModelTableBase*> {
public:
  ModelViewCache();
};

#endif // MODELVIEWCACHE_H
