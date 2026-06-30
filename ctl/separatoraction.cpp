#include "separatoraction.h"

SeparatorAction::SeparatorAction(QObject *parent) : QAction{parent} {
  setSeparator(true);
}
