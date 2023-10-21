#ifndef SMARTCALC_V2_MVCVIEW_DEPOSITCALCWINDOW_H_
#define SMARTCALC_V2_MVCVIEW_DEPOSITCALCWINDOW_H_

#include <QMainWindow>
#include <QTableWidget>

#include "../MVCController/deposit_controller.h"

namespace Ui {
class DepositCalcWindow;
}

class DepositCalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit DepositCalcWindow(QWidget* parent = nullptr);
  explicit DepositCalcWindow(e_calc::DepositController* controller);
  ~DepositCalcWindow();

 private slots:
  void on_pushButton_calculate_clicked();

  void GenerateData();
  void ClickedAddRow();
  void AddNewRow(QTableWidget* table, int month, double amount);

  void ClickedRemoveRow();

  void PrintPayments();

 private:
  Ui::DepositCalcWindow* ui;
  e_calc::DepositTerms terms_;
  e_calc::DepositPayments payments_;
  e_calc::DepositController* controller_;
};

#endif  // SMARTCALC_V2_MVCVIEW_DEPOSITCALCWINDOW_H_
