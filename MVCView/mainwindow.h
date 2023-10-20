#ifndef SMARTCALC_V2_MVCVIEW_MAINWINDOW_H_
#define SMARTCALC_V2_MVCVIEW_MAINWINDOW_H_

#include <QMainWindow>
#include <cstring>
#include <limits>
#include <string>

#include "../MVCController/main_controller.h"
#include "../MVCModel/smart_calculator.h"
#include "../MVCController/credit_controller.h"
#include "../MVCModel/credit_calculator.h"
#include "creditcalcwindow.h"

#include "depositcalcwindow.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  MainWindow(e_calc::Controller* controller, e_calc::CreditController* credit_controller);
  ~MainWindow();

 private slots:
  void on_pushButton_AC_clicked();
  void on_pushButton_delete_prev_clicked();
  void LastTokenChecking();

  void ClickedButtonDigits();
  void on_pushButton_dot_clicked();
  void on_pushButton_var_clicked();

  void ClickedButtonOperations();
  void UnaryMinusInput();
  void OperatorInput(QString button_text);
  void UnaryMinusChanging();
  void on_pushButton_op_pow_clicked();

  void on_pushButton_open_bracket_clicked();
  void on_pushButton_close_bracket_clicked();

  void on_pushButton_mfunc_inv_clicked();
  void ClickedButtonMathFunctions();

  void on_pushButton_calc_clicked();
  void on_pushButton_print_graph_clicked();
  void GraphPlot(double x_min, double x_max, double y_min, double y_max);

  void on_action_credit_calculator_triggered();
  void on_action_deposit_calculator_triggered();

 private:
  enum last_token_type_list {
    kAllClean,
    kNumToken,
    kDotToken,
    kVarToken,
    kOpToken,
    kPowToken,
    kOpenBracketToken,
    kCloseBracketToken,
    kMathFuncToken,
    kCalculation
  };

  Ui::MainWindow* ui;
  e_calc::Controller* controller_;
  e_calc::CreditController* credit_controller_;
  CreditCalcWindow* window_credit_calc_;

  e_calc::Controller* deposit_controller_;
  DepositCalcWindow* window_deposit_calc_;

  int last_token_type;
  bool is_dot_input;
  bool is_u_minus_input;
  int brackets_counter;
};
#endif  // SMARTCALC_V2_MVCVIEW_MAINWINDOW_H_
