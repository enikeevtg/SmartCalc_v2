#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  e_calc::Model model;
  e_calc::Controller controller{&model};
  MainWindow window_smart_calc{&controller};

  window_smart_calc.setFixedSize(1000, 656);
  window_smart_calc.show();
  return app.exec();
}
