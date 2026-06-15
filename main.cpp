#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QApplication>
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  app.setStyle("fusion");

  QTranslator qtTranslator;
  QString lang = QLocale::system().name();
  // Загружаем системный перевод (ищет файлы вида qt_ru.qm)
  if (qtTranslator.load("qt_" + lang, QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
    app.installTranslator(&qtTranslator);
  }
  // Здесь загружается перевод для вашего собственного приложения
  QTranslator myTranslator;
  if (myTranslator.load("acdanalizer_" + lang, ":/translations")) {
    app.installTranslator(&myTranslator);
  }

  MainWindow window;
  window.show();
  return app.exec();
 }
