#ifndef SMARTCALC_V2_MVCVIEW_CREDITCALCWINDOW_H_
#define SMARTCALC_V2_MVCVIEW_CREDITCALCWINDOW_H_

#include <QMainWindow>

#include "../MVCController/smartcalc_controller.h"

namespace Ui {
class CreditCalcWindow;
}

class CreditCalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit CreditCalcWindow(QWidget* parent = nullptr);
  explicit CreditCalcWindow(e_calc::Controller* controller);
  ~CreditCalcWindow();

 private slots:

  void on_pushButton_calculate_clicked();
  void print_result(e_calc::CreditPayments* payment);

 private:
  Ui::CreditCalcWindow* ui;
  e_calc::Controller* controller_;
};

#endif  // SMARTCALC_V2_MVCVIEW_CREDITCALCWINDOW_H_
