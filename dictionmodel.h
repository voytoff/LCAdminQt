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

  QVariant get(const int &row, const int &column) const;

protected:
  void loadChildren(TreeItem *parentItem) const override;
  QList<QVariantList> defs = {
    {documentType::crate, "Крейт", "crate"},
    {documentType::module, "Модуль", "module"}
  };

};

#endif // DICTIONMODEL_H
