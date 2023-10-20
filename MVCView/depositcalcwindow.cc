#include "depositcalcwindow.h"

#include "ui_depositcalcwindow.h"

DepositCalcWindow::DepositCalcWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::DepositCalcWindow) {
  ui->setupUi(this);

  ui->doubleSpinBox_deposit_total_amount->setMinimum(0.0);
  ui->doubleSpinBox_deposit_total_amount->setMaximum(
      std::numeric_limits<double>::max());

  ui->doubleSpinBox_deposit_rate->setMinimum(0.0);
  ui->doubleSpinBox_deposit_rate->setMaximum(999.0);

  ui->doubleSpinBox_deposit_tax_rate->setMinimum(0.0);
  ui->doubleSpinBox_deposit_tax_rate->setMaximum(100.0);

  ui->spinBox_deposit_term->setMinimum(0);
  ui->spinBox_deposit_term->setMaximum(600);

  ui->tableWidget_replenishments_list->setEditTriggers(
      QAbstractItemView::NoEditTriggers);
  ui->tableWidget_withdrawals_list->setEditTriggers(
      QAbstractItemView::NoEditTriggers);

  ui->spinBox_replenishment_month->setMinimum(0);
  ui->spinBox_replenishment_month->setMaximum(std::numeric_limits<int>::max());
  ui->doubleSpinBox_replenishments_amount->setMinimum(0.0);
  ui->doubleSpinBox_replenishments_amount->setMaximum(
      std::numeric_limits<double>::max());

  ui->spinBox_withdrawals_month->setMinimum(0);
  ui->spinBox_withdrawals_month->setMaximum(std::numeric_limits<int>::max());
  ui->doubleSpinBox_withdrawals_amount->setMinimum(0.0);
  ui->doubleSpinBox_withdrawals_amount->setMaximum(
      std::numeric_limits<double>::max());

  connect(ui->pushButton_add_replenishment, SIGNAL(clicked()), this,
          SLOT(ClickedAddRow()));
  connect(ui->pushButton_add_withdrawal, SIGNAL(clicked()), this,
          SLOT(ClickedAddRow()));

  connect(ui->pushButton_remove_last_replenishment, SIGNAL(clicked()), this,
          SLOT(ClickedRemoveRow()));
  connect(ui->pushButton_remove_last_withdrawal, SIGNAL(clicked()), this,
          SLOT(ClickedRemoveRow()));
}

DepositCalcWindow::DepositCalcWindow(e_calc::Controller* controller)
    : DepositCalcWindow() {
  controller_ = controller;
}

DepositCalcWindow::~DepositCalcWindow() { delete ui; }

////////////////////////////////////////////////////////////////////////////////
// REPLENISHMENTS AND WITHDRAWALS
void DepositCalcWindow::ClickedAddRow() {
  QTableWidget* table;
  QSpinBox* month_box;
  QDoubleSpinBox* amount_box;
  QPushButton* button = (QPushButton*)sender();
  if (button->text() == "+ add new replenishment") {
    table = ui->tableWidget_replenishments_list;
    month_box = ui->spinBox_replenishment_month;
    amount_box = ui->doubleSpinBox_replenishments_amount;
  } else {
    table = ui->tableWidget_withdrawals_list;
    month_box = ui->spinBox_withdrawals_month;
    amount_box = ui->doubleSpinBox_withdrawals_amount;
  }

  int month = month_box->value();
  double amount = amount_box->value();
  int scale = 1;
  if (ui->comboBox_term_mode->currentText() == "years") scale = 12;

  if (month == 0) {
    ui->statusbar->showMessage("Month must be greater than nill");
  } else if (month > scale * ui->spinBox_deposit_term->value()) {
    ui->statusbar->showMessage(
        "Month must be less than or equal to Deposit term");
  } else {
    AddNewRow(table, month, amount);
  }
}

void DepositCalcWindow::AddNewRow(QTableWidget* table, int month,
                                  double amount) {
  table->insertRow(table->rowCount());
  int current_row = table->rowCount();

  QTableWidgetItem* item_month = new QTableWidgetItem(QString::number(month));
  table->setItem(current_row - 1, 0, item_month);
  QTableWidgetItem* item_amount = new QTableWidgetItem(QString::number(amount));
  table->setItem(current_row - 1, 1, item_amount);
}

void DepositCalcWindow::ClickedRemoveRow() {
  QTableWidget* table;
  QPushButton* button = (QPushButton*)sender();
  if (button->text() == "− remove last replenishment") {
    table = ui->tableWidget_replenishments_list;
  } else {
    table = ui->tableWidget_withdrawals_list;
  }

  int rows = table->rowCount();
  if (rows > 0) {
    table->setRowCount(rows - 1);
  }
}

////////////////////////////////////////////////////////////////////////////////
// CALCULATION
void DepositCalcWindow::on_pushButton_calculate_clicked() {
  e_calc::DepositTerms terms = {0, 0, 0.0, 0.0, 0.0, nullptr, nullptr};
  GenerateData(&terms);
  e_calc::DepositPayments payments;

  try {
    if (ui->checkBox_capitalization->isChecked()) {
      int deposit_type = e_calc::kCompound;
      controller_->SetDepositController(deposit_type, &terms);
      payments = controller_->GetDepositPayments();
    } else {
      int deposit_type = e_calc::kSimple;
      controller_->SetDepositController(deposit_type, &terms);
      payments = controller_->GetDepositPayments();
    }
    PrintPayments(&payments);
    ui->statusbar->showMessage("");
  } catch (const char* message) {
    PrintPayments(&payments);
    ui->statusbar->showMessage(message);
  }
}

void DepositCalcWindow::GenerateData(e_calc::DepositTerms* terms) {
  terms->total_begin = ui->doubleSpinBox_deposit_total_amount->value();
  int scale = 1;
  if (ui->comboBox_term_mode->currentText() == "years") scale = 12;
  terms->term = scale * ui->spinBox_deposit_term->value();
  terms->deposit_rate = ui->doubleSpinBox_deposit_rate->value();
  terms->tax_rate = ui->doubleSpinBox_deposit_tax_rate->value();
  terms->periodicity = 1;
  QString periodicity_text = ui->comboBox_periodicity->currentText();
  if (periodicity_text == "once a quarter") {
    terms->periodicity = 3;
  } else if (periodicity_text == "semiannually") {
    terms->periodicity = 6;
  } else if (periodicity_text == "once a year") {
    terms->periodicity = 12;
  } else if (periodicity_text == "at the end of the term") {
    terms->periodicity = terms->term;
  }

  QVector<double> vector_replenishments(terms->term + 1);
  QVector<double> vector_withdrawals(terms->term + 1);
  for (int i = 0; i <= terms->term; i++) {
    vector_replenishments[i] = 0;
    vector_withdrawals[i] = 0;
  }

  int month_number = 0;
  int replenishments_number = ui->tableWidget_replenishments_list->rowCount();
  for (int i = 0; i < replenishments_number; i++) {
    month_number =
        ui->tableWidget_replenishments_list->item(i, 0)->text().toInt();
    vector_replenishments[month_number] +=
        ui->tableWidget_replenishments_list->item(i, 1)->text().toDouble();
  }

  int withdrawals_number = ui->tableWidget_withdrawals_list->rowCount();
  for (int i = 0; i < withdrawals_number; i++) {
    month_number = ui->tableWidget_withdrawals_list->item(i, 0)->text().toInt();
    vector_withdrawals[month_number] +=
        ui->tableWidget_withdrawals_list->item(i, 1)->text().toDouble();
  }

  terms->replenishments = vector_replenishments.data();
  terms->withdrawals = vector_withdrawals.data();
}

void DepositCalcWindow::PrintPayments(e_calc::DepositPayments* payments) {
  QString currency = " " + ui->comboBox_currency_mode->currentText();
  QString accrues_interst = QString::number(payments->accrued_interest, 'f', 2);
  QString tax_amount = QString::number(payments->tax_amount, 'f', 2);
  QString total_end = QString::number(payments->total_end, 'f', 2);

  ui->label_value_deposit_accrued_interest->setText(accrues_interst + currency);
  ui->label_value_deposit_tax_amount->setText(tax_amount + currency);
  ui->label_value_deposit_end_amount->setText(total_end + currency);
}
