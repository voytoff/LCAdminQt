#ifndef SEPARATORACTION_H
#define SEPARATORACTION_H

#include <QAction>

class SeparatorAction : public QAction {
  Q_OBJECT
public:
  explicit SeparatorAction(QObject *parent = nullptr);

signals:
};

#endif // SEPARATORACTION_H
