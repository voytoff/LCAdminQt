#ifndef DICTIONMODEL_H
#define DICTIONMODEL_H

#include "db.h"
#include "modeltreebase.h"
#include "treeitem.h"
#include "treeitemtype.h"
#include "types.h"

#include <QAbstractItemModel>
#include <QList>
#include <QVariant>
#include <QList>
#include <QVariantList>

class DictionModel : public ModelTreeBase {
  Q_OBJECT
public:
  explicit DictionModel(DB *db, const QVariantList &headers, const QStringList icons = {}, QObject *parent = nullptr);
  ~DictionModel() = default;

  TreeItemType get(const int &row) const;
  QVariant get(const int &row, const int &column) const;

protected:
  QVariant getIcon(const QModelIndex &index, TreeItem *item) const override;
  void loadChildren(TreeItem *parentItem) const override;
  QList<TreeItemType> defs = {
    {Enums::documentType::crate, "Крейт", "crate", icon_crate},
    {Enums::documentType::module, "Модуль", "module", icon_module},
    {Enums::documentType::sensortype, "Тип датчика", "sensortype", icon_sensortype},
    {Enums::documentType::sensor, "Датчик", "sensor", icon_sensor},
    {Enums::documentType::measureunit, "Единица измерения", "measureunit", icon_measureunit},
    {Enums::documentType::experiment, "Эксперимент", "experiment", icon_experiment},
  };
};

#endif // DICTIONMODEL_H
