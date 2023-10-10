#ifndef SMARTCALC_V2_01_UI_CREDITCALCWINDOW_H_
#define SMARTCALC_V2_01_UI_CREDITCALCWINDOW_H_

#include <QMainWindow>

//extern "C" {
//#include "../04_credit_calculator/credit_calculator.h"
//}

namespace Ui {
class CreditCalcWindow;
}

class CreditCalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit CreditCalcWindow(QWidget *parent = nullptr);
  ~CreditCalcWindow();

 private slots:

  void on_pushButton_calculate_clicked();
//  void print_result(struct credit_output *result);

 private:
  Ui::CreditCalcWindow *ui;
};

#endif  // SMARTCALC_V2_01_UI_CREDITCALCWINDOW_H_
