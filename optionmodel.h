#ifndef OPTIONMODEL_H
#define OPTIONMODEL_H

#include "db.h"
#include "modeltreebase.h"
#include "treeitem.h"
#include <QAbstractItemModel>
#include <QSqlQuery>

class OptionModel : public ModelTreeBase {
  Q_OBJECT
public:
  explicit OptionModel(DB *db, const QVariantList &headers, const QStringList icons = {}, QObject *parent = nullptr);
  ~OptionModel() = default;

protected:
  void loadChildren(TreeItem *parentItem) const override;

};

#endif // OPTIONMODEL_H
