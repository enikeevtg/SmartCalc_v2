#ifndef SMARTCALC_V2_MVCVIEW_DEPOSITCALCWINDOW_H_
#define SMARTCALC_V2_MVCVIEW_DEPOSITCALCWINDOW_H_

#include <QMainWindow>
#include <QTableWidget>

#include "../MVCController/main_controller.h"

namespace Ui {
class DepositCalcWindow;
}

class DepositCalcWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit DepositCalcWindow(QWidget* parent = nullptr);
  explicit DepositCalcWindow(e_calc::Controller* controller);
  ~DepositCalcWindow();

 private slots:
  void on_pushButton_calculate_clicked();

  void GenerateData(e_calc::DepositTerms* terms);
  void ClickedAddRow();
  void AddNewRow(QTableWidget* table, int month, double amount);

  void ClickedRemoveRow();

  void PrintPayments(e_calc::DepositPayments* payments);

 private:
  Ui::DepositCalcWindow* ui;
  e_calc::Controller* controller_;
};

#endif  // SMARTCALC_V2_MVCVIEW_DEPOSITCALCWINDOW_H_
