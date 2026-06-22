#include "statewidget.h"

StateWidget::StateWidget(QWidget *parent)
  : QWidget{parent}
  , m_isModified(false) {
   setWindowTitle("Редактор [*]");
}

bool StateWidget::isModified() const {
  return m_isModified;
}

void StateWidget::setModified(bool modified) {
  if (m_isModified != modified) {
    m_isModified = modified;
    // Обновляем статус в заголовке окна (добавит/уберет звездочку)
    setWindowModified(m_isModified);
  }

}
