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

CreditCalcWindow::CreditCalcWindow(e_calc::CreditController* controller)
    : CreditCalcWindow() {
  controller_ = controller;
}

CreditCalcWindow::~CreditCalcWindow() { delete ui; }

void CreditCalcWindow::on_pushButton_calculate_clicked() {
  ui->statusBar->showMessage("");

  terms_.total_amount = ui->doubleSpinBox_credit_total_amount->value();
  int scale = 1;
  if (ui->comboBox_term_mode->currentText() == "years") scale = 12;
  terms_.term = scale * ui->spinBox_credit_term->value();
  terms_.rate = ui->doubleSpinBox_credit_rate->value();
  int credit_type = e_calc::kAnnuity;
  if (ui->radioButton_differentiated->isChecked()) {
    credit_type = e_calc::kDiffer;
  }

  try {
    payments_ = controller_->CalculateCreditPayments(credit_type, &terms_);
    DisplayPayments();
  } catch (const char* message) {
    ui->statusBar->showMessage(message);
  }
}

void CreditCalcWindow::DisplayPayments() {
  QString currency = " " + ui->comboBox_currency_mode->currentText();
  QString month_payment =
      QString::number(payments_.first_month_payment, 'f', 2);
  if (ui->radioButton_differentiated->isChecked()) {
    month_payment +=
        "..." + QString::number(payments_.last_month_payment, 'f', 2);
  }
  QString overpayment = QString::number(payments_.overpayment, 'f', 2);
  QString total_payment = QString::number(payments_.total_payment, 'f', 2);

  ui->label_value_monthly_payment->setText(month_payment + currency);
  ui->label_value_credit_overpayment->setText(overpayment + currency);
  ui->label_value_credit_total_payment->setText(total_payment + currency);
}
