#ifndef SMARTCALC_V2_01_UI_DEPOSITCALCWINDOW_H_
#define SMARTCALC_V2_01_UI_DEPOSITCALCWINDOW_H_

#include <QMainWindow>
#include <QTableWidget>

// extern "C" {
//#include "../05_deposit_calculator/deposit_calculator.h"
// }

namespace Ui {
class DepositCalcWindow;
}

class DepositCalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit DepositCalcWindow(QWidget* parent = nullptr);
  ~DepositCalcWindow();

 private slots:
  void on_pushButton_calculate_clicked();

  //  void generateData(struct deposit_input* pdata);
  void clickedAddRow();
  void addNewRow(QTableWidget* table, int month, double amount);

  void clickedRemoveRow();

  //  void print_result(struct deposit_output* result);

 private:
  Ui::DepositCalcWindow* ui;
};

#endif  // SMARTCALC_V2_01_UI_DEPOSITCALCWINDOW_H_
