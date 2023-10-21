#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  e_calc::Model main_model;
  e_calc::Controller main_controller{&main_model};
  e_calc::CreditCalculator credit_model;
  e_calc::CreditController credit_controller{&credit_model};
  e_calc::DepositCalculator deposit_model;
  e_calc::DepositController deposit_controller{&deposit_model};
  MainWindow main_window{&main_controller, &credit_controller,
                         &deposit_controller};

  main_window.setFixedSize(1000, 656);
  main_window.show();
  return app.exec();
}
