#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  e_calc::Model main_model;
  e_calc::Controller main_controller{&main_model};
  e_calc::CreditCalculator credit_model;
  e_calc::CreditController credit_controller{&credit_model};
  MainWindow calculator_window{&main_controller, &credit_controller};

  calculator_window.setFixedSize(1000, 656);
  calculator_window.show();
  return app.exec();
}
