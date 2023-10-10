#include "creditcalcwindow.h"

#include "ui_creditcalcwindow.h"

CreditCalcWindow::CreditCalcWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::CreditCalcWindow) {
  ui->setupUi(this);

  ui->doubleSpinBox_credit_total_amount->setValue(0.0);
  ui->spinBox_credit_term->setValue(0);
  ui->doubleSpinBox_credit_rate->setValue(0.0);

  ui->doubleSpinBox_credit_total_amount->setMinimum(0.0);
  ui->doubleSpinBox_credit_total_amount->setMaximum(
      std::numeric_limits<double>::max());

  ui->spinBox_credit_term->setMinimum(0);
  ui->spinBox_credit_term->setMaximum(600);

  ui->doubleSpinBox_credit_rate->setMinimum(0.0);
  ui->doubleSpinBox_credit_rate->setMaximum(999.0);

  ui->statusBar->showMessage("");
  ui->radioButton_annuity->setChecked(true);
}

CreditCalcWindow::~CreditCalcWindow() { delete ui; }

void CreditCalcWindow::on_pushButton_calculate_clicked() {
//  ui->statusBar->showMessage("");
//  struct credit_input data = {0, 0, 0};
//  struct credit_output result = {0, 0, 0, 0};
//  data.total_amount = ui->doubleSpinBox_credit_total_amount->value();
//  int scale = 1;
//  if (ui->comboBox_term_mode->currentText() == "years") scale = 12;
//  data.term = scale * ui->spinBox_credit_term->value();
//  data.rate = ui->doubleSpinBox_credit_rate->value();

//  if (data.total_amount < 0.01) {
//    ui->statusBar->showMessage("Total credit amount: minimum value is 0.01");
//  } else if (data.term < 1) {
//    ui->statusBar->showMessage("Credit term: minimum value is 1");
//  } else if (scale == 1 && data.term > 600) {
//    ui->statusBar->showMessage("Credit term: maximum value is 600");
//  } else if (scale == 12 && data.term > 600) {
//    ui->statusBar->showMessage("Credit term: maximum value is 50");
//  } else if (data.rate < 0.01) {
//    ui->statusBar->showMessage("Credit rate: minimum value is 0.01");
//  } else if (ui->radioButton_annuity->isChecked()) {
//    result = credit_calculation(&data, ANNUITY);
//  } else if (ui->radioButton_differentiated->isChecked()) {
//    result = credit_calculation(&data, DIFFER);
//  }
//  print_result(&result);
}

//void CreditCalcWindow::print_result(struct credit_output* result) {
//  QString currency = " " + ui->comboBox_currency_mode->currentText();
//  QString month_payment = QString::number(result->first_month_payment, 'f', 2);
//  if (ui->radioButton_differentiated->isChecked()) {
//    month_payment +=
//        "..." + QString::number(result->last_month_payment, 'f', 2);
//  }
//  QString overpayment = QString::number(result->overpayment, 'f', 2);
//  QString total_payment = QString::number(result->total_payment, 'f', 2);

//  ui->label_value_monthly_payment->setText(month_payment + currency);
//  ui->label_value_credit_overpayment->setText(overpayment + currency);
//  ui->label_value_credit_total_payment->setText(total_payment + currency);
//}
