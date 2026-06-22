#ifndef DICTIONMODEL_H
#define DICTIONMODEL_H

#include "db.h"
#include "modeltreebase.h"
#include "treeitem.h"
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
    {documentType::cratetype, "Тип крейта", "cratetype", icon_cratetype},
    {documentType::crate, "Крейт", "crate", icon_crate},
    {documentType::moduletype, "Тип модуля", "moduletype", icon_moduletype},
    {documentType::module, "Модуль", "module", icon_module},
    {documentType::calibration, "Градуировки", "calibration", icon_calibration}
  };

};

#endif // DICTIONMODEL_H
