#ifndef SMARTCALC_V2_MVCVIEW_CREDITCALCWINDOW_H_
#define SMARTCALC_V2_MVCVIEW_CREDITCALCWINDOW_H_

#include <QMainWindow>

#include "../MVCController/credit_controller.h"

namespace Ui {
class CreditCalcWindow;
}

class CreditCalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit CreditCalcWindow(QWidget* parent = nullptr);
  explicit CreditCalcWindow(e_calc::CreditController* controller);
  ~CreditCalcWindow();

 private slots:

  void on_pushButton_calculate_clicked();
  void DisplayPayments();

 private:
  Ui::CreditCalcWindow* ui;
  e_calc::CreditTerms terms_;
  e_calc::CreditPayments payments_;
  e_calc::CreditController* controller_;
};

#endif  // SMARTCALC_V2_MVCVIEW_CREDITCALCWINDOW_H_
