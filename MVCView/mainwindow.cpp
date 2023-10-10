#include "mainwindow.h"

#include <memory>

#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  setlocale(LC_NUMERIC, "C");

  last_token_type = num_token;
  is_dot_input = false;
  is_u_minus_input = false;
  brackets_counter = 0;

  // INPUT_LABEL
  ui->label_input->setWordWrap(true);

  // DIGIT BUTTONS
  for (auto button : ui->buttonGroup_numbers->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(clickedButtonDigits()));
  }

  // OPERATORS BUTTONS
  for (auto button : ui->buttonGroup_operators->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(clickedButtonOperations()));
  }

  // MATH FUNCTIONS BUTTONS
  ui->pushButton_mfunc_inv->setCheckable(true);
  for (auto button : ui->buttonGroup_mfunctions->buttons()) {
    connect(button, SIGNAL(clicked()), this, SLOT(clickedButtonMathFunctions()));
  }

  // VARIABLE SPINBOX
  ui->doubleSpinBox_var->setValue(0.0);
  ui->doubleSpinBox_var->setEnabled(false);
  ui->doubleSpinBox_var->setMaximum(std::numeric_limits<double>::max());
  ui->doubleSpinBox_var->setMinimum(-std::numeric_limits<double>::max());
  ui->doubleSpinBox_var->setDecimals(7);

  // GRAPH
  // GRAPH SETTINGS
  ui->expression_graph->setBackground(QColor(58, 70, 90));
  ui->expression_graph->xAxis->setRange(0.0, 21.0);
  ui->expression_graph->yAxis->setRange(-11.0, 11.0);

  // RANGE SPINBOXES
  ui->doubleSpinBox_xmin->setMinimum(-1000000.0);
  ui->doubleSpinBox_xmin->setMaximum(1000000.0);

  ui->doubleSpinBox_xmax->setMinimum(-1000000.0);
  ui->doubleSpinBox_xmax->setMaximum(1000000.0);

  ui->doubleSpinBox_ymin->setMinimum(-1000000.0);
  ui->doubleSpinBox_ymin->setMaximum(1000000.0);

  ui->doubleSpinBox_ymax->setMinimum(-1000000.0);
  ui->doubleSpinBox_ymax->setMaximum(1000000.0);

  ui->doubleSpinBox_xmin->setValue(0.0);
  ui->doubleSpinBox_xmax->setValue(21.0);
  ui->doubleSpinBox_ymin->setValue(-11.0);
  ui->doubleSpinBox_ymax->setValue(11.0);

  // TOOLBAR
  ui->toolBar->setMovable(false);
}

MainWindow::~MainWindow() { delete ui; }

////////////////////////////////////////////////////////////////////////////////
// FINANCIAL MODES
void MainWindow::on_action_credit_calculator_triggered() {
  window_credit_calc = new CreditCalcWindow();
  window_credit_calc->setFixedSize(640, 549);
  window_credit_calc->show();
}

void MainWindow::on_action_deposit_calculator_triggered() {
  window_deposit_calc = new DepositCalcWindow();
  window_deposit_calc->setFixedSize(640, 910);
  window_deposit_calc->show();
}

////////////////////////////////////////////////////////////////////////////////
// SERVICE
void MainWindow::on_pushButton_AC_clicked() {
  last_token_type = all_clean;
  ui->statusBar->showMessage("");
  ui->label_output->setText("");
  ui->doubleSpinBox_var->setEnabled(false);
  ui->doubleSpinBox_var->setValue(0.0);
  ui->expression_graph->removeGraph(0);
  ui->expression_graph->replot();

  ui->label_input->setText("");
  ui->pushButton_0->click();
  is_dot_input = false;
  is_u_minus_input = false;
  brackets_counter = 0;
}

void MainWindow::on_pushButton_delete_prev_clicked() {
  QString input_label_text = ui->label_input->text();
  size_t input_text_length = input_label_text.length();
  size_t reduced_size = input_text_length - 1;
  QString last_input_char = input_label_text.last(1);

  if (last_token_type == calculation) {
    reduced_size--;
  } else if (last_input_char == " ") {
    reduced_size -= 2;
  } else if (last_input_char == "(") {
    while (reduced_size > 0 && input_label_text[reduced_size - 1] != ' ' &&
           input_label_text[reduced_size - 1] != '(' &&
           input_label_text[reduced_size - 1] != ')' &&
           input_label_text[reduced_size - 1] != '^') {
      reduced_size--;
    }
    if (reduced_size > 0 && input_label_text[reduced_size - 1] == '^') {
      reduced_size--;
    }
    brackets_counter--;
  } else if (last_input_char == ")") {
    brackets_counter++;
  }
  input_label_text.resize(reduced_size);
  ui->label_input->setText(input_label_text);
  if (input_label_text == "") {
    ui->pushButton_0->click();
  } else {
    lastTokenChecking();
  }
}

void MainWindow::lastTokenChecking() {
  QString last_label_char = ui->label_input->text().last(1);

  is_dot_input = false;
  is_u_minus_input = false;

  if (last_label_char == " ") {
    last_token_type = op_token;
  } else if (last_label_char == "-") {
    last_token_type = op_token;
    is_u_minus_input = true;
  } else if (last_label_char == "(") {
    last_token_type = open_bracket_token;
  } else if (last_label_char == ")") {
    last_token_type = close_bracket_token;
  } else if (last_label_char == "x") {
    last_token_type = var_token;
  } else {
    QString input_label_text = ui->label_input->text();
    size_t input_text_length = input_label_text.length();
    int i = input_text_length - 1;
    while (i >= 0 && input_label_text[i] != ' ' && input_label_text[i] != '(' &&
           input_label_text[i] != '-') {
      if (input_label_text[i] == '.') {
        is_dot_input = true;
      }
      i--;
    }
    last_token_type = num_token;
  }
}

////////////////////////////////////////////////////////////////////////////////
// DIGITS AND VARIABLE
void MainWindow::clickedButtonDigits() {
  if (last_token_type == calculation) {
    on_pushButton_delete_prev_clicked();
  }

  QPushButton* button = (QPushButton*)sender();

  if (ui->label_input->text() == "0" || ui->label_input->text() == "") {
    ui->label_input->setText(button->text());
  } else if (ui->label_input->text().length() > 1 &&
             (ui->label_input->text().last(2) == "(0" ||
              ui->label_input->text().last(2) == "-0" ||
              ui->label_input->text().last(2) == " 0")) {
  } else {
    if (last_token_type == var_token ||
        last_token_type == close_bracket_token) {
      ui->pushButton_op_mult->click();
    }
    ui->label_input->setText(ui->label_input->text() + button->text());
  }
  last_token_type = num_token;
  is_u_minus_input = false;
}

void MainWindow::on_pushButton_dot_clicked() {
  if (last_token_type == calculation) {
    on_pushButton_delete_prev_clicked();
  }

  if (is_dot_input == false && last_token_type != var_token) {
    if (last_token_type != num_token) {
      ui->pushButton_0->click();
    }
    ui->label_input->setText(ui->label_input->text() + '.');
    last_token_type = dot_token;
    is_dot_input = true;
  }
}

void MainWindow::on_pushButton_var_clicked() {
  if (last_token_type == calculation) {
    on_pushButton_delete_prev_clicked();
  }

  if (ui->doubleSpinBox_var->isEnabled() == false) {
    ui->doubleSpinBox_var->setEnabled(true);
  }

  if (ui->label_input->text() == "0") {
    ui->label_input->setText("x");
  } else {
    if (last_token_type == num_token || last_token_type == var_token ||
        last_token_type == close_bracket_token) {
      ui->pushButton_op_mult->click();
    }
    ui->label_input->setText(ui->label_input->text() + "x");
  }
  last_token_type = var_token;
  is_u_minus_input = false;
}

////////////////////////////////////////////////////////////////////////////////
// OPERATORS
void MainWindow::clickedButtonOperations() {
  if (last_token_type == calculation) {
    on_pushButton_delete_prev_clicked();
  }

  QPushButton* button = (QPushButton*)sender();
  QString button_text = button->text();

  if (button_text == "×")
    button_text = "*";
  else if (button_text == "÷")
    button_text = "/";
  else if (button_text == "−")
    button_text = "-";
  else if (button_text == "mod")
    button_text = "%";

  if (last_token_type != op_token) {
    if (last_token_type == dot_token) {
      ui->pushButton_0->click();
    }

    if ((ui->label_input->text() == "0" ||
         last_token_type == open_bracket_token) &&
        button_text == "-") {
      unaryMinusInput();
    } else if (last_token_type != open_bracket_token) {
      operatorInput(button_text);
    }
  } else {  // last_token_type is op_token
    if (ui->label_input->text() == "-" && button_text != "-") {
      unaryMinusChanging();
    } else if (is_u_minus_input == false) {
      on_pushButton_delete_prev_clicked();
      operatorInput(button_text);
    }
  }
}

void MainWindow::unaryMinusInput() {
  if (ui->label_input->text() == "0") {
    ui->label_input->setText("-");
  } else if (last_token_type == open_bracket_token) {
    ui->label_input->setText(ui->label_input->text() + "-");
  }
  last_token_type = op_token;
  is_u_minus_input = true;
}

void MainWindow::operatorInput(QString button_text) {
  ui->label_input->setText(ui->label_input->text() + " " + button_text + " ");
  is_dot_input = false;
  is_u_minus_input = false;
  last_token_type = op_token;
}

void MainWindow::unaryMinusChanging() {
  on_pushButton_delete_prev_clicked();
  ui->pushButton_0->click();
}

void MainWindow::on_pushButton_op_pow_clicked() {
  if (last_token_type == calculation) {
    on_pushButton_delete_prev_clicked();
  }

  if (last_token_type == dot_token) {
    ui->pushButton_0->click();
  }

  if (last_token_type == num_token || last_token_type == close_bracket_token ||
      last_token_type == var_token || ui->label_input->text() == "0") {
    ui->label_input->setText(ui->label_input->text() + "^");
    last_token_type = pow_token;
    on_pushButton_open_bracket_clicked();
  }
}

////////////////////////////////////////////////////////////////////////////////
// BRACKETS
void MainWindow::on_pushButton_open_bracket_clicked() {
  if (last_token_type == calculation) {
    on_pushButton_delete_prev_clicked();
  }

  if (ui->label_input->text() == "0") {
    ui->label_input->setText("(");
  } else if (is_u_minus_input == true || last_token_type == math_func_token ||
             last_token_type == open_bracket_token ||
             last_token_type == pow_token) {
    ui->label_input->setText(ui->label_input->text() + "(");
  } else {
    if (last_token_type == num_token || last_token_type == var_token ||
        last_token_type == close_bracket_token) {
      ui->pushButton_op_mult->click();
    }
    ui->label_input->setText(ui->label_input->text() + "(");
  }

  is_dot_input = false;
  is_u_minus_input = false;
  last_token_type = open_bracket_token;
  brackets_counter++;
}

void MainWindow::on_pushButton_close_bracket_clicked() {
  if (last_token_type == calculation) {
    on_pushButton_delete_prev_clicked();
  }

  if (brackets_counter > 0 && last_token_type != op_token &&
      last_token_type != open_bracket_token) {
    if (last_token_type == dot_token) {
      ui->pushButton_0->click();
    }
    ui->label_input->setText(ui->label_input->text() + ")");

    last_token_type = close_bracket_token;
    brackets_counter--;
  }
}

////////////////////////////////////////////////////////////////////////////////
// MATH FUNCTIONS
void MainWindow::on_pushButton_mfunc_inv_clicked() {
  if (last_token_type == calculation) {
    on_pushButton_delete_prev_clicked();
  }

  if (ui->pushButton_mfunc_inv->isChecked()) {
    ui->pushButton_mfunc_cos->setText("acos");
    ui->pushButton_mfunc_sin->setText("asin");
    ui->pushButton_mfunc_tan->setText("atan");
  } else {
    ui->pushButton_mfunc_cos->setText("cos");
    ui->pushButton_mfunc_sin->setText("sin");
    ui->pushButton_mfunc_tan->setText("tan");
  }
}

void MainWindow::clickedButtonMathFunctions() {
  if (last_token_type == calculation) {
    on_pushButton_delete_prev_clicked();
  }

  QPushButton* button = (QPushButton*)sender();
  QString button_text = button->text();

  if (button_text == "√") button_text = "sqrt";  //!!!!!

  if (ui->label_input->text() == "0") {
    ui->label_input->setText(button_text);
  } else {
    if (last_token_type == num_token || last_token_type == var_token ||
        last_token_type == close_bracket_token) {
      ui->pushButton_op_mult->click();
    }
    ui->label_input->setText(ui->label_input->text() + button_text);
  }
  last_token_type = math_func_token;
  on_pushButton_open_bracket_clicked();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CALCULATIONS LAUNCH
void MainWindow::on_pushButton_calc_clicked() {
  if (last_token_type == calculation) {
    on_pushButton_delete_prev_clicked();
  }

//  QString input_label_text = ui->label_input->text();
//  QByteArray tmp_byte_array = input_label_text.toLatin1();
//  tmp_byte_array.replace(" ", "");
//  char* str_for_calc = tmp_byte_array.data();

//  int error = OK;
//  double variable = ui->doubleSpinBox_var->value();
//  double result = 0.0;
//  node_t* q_root = NULL;
//  error = convert_infix_to_RPN(str_for_calc, &q_root);
//  if (error == OK) {
//    error = evaluate_expression(q_root, variable, &result);
//  }

//  QString result_string;
//  if (error == OK) {
//    ui->statusBar->showMessage("");
//    result_string = QString::number(result, 'g');
//    ui->label_input->setText(input_label_text + " =");
//    ui->label_output->setText(result_string);
//    last_token_type = calculation;
//  } else {
//    ERRORS_MESSAGES;
//    ui->statusBar->showMessage(errors_msg[error]);
//  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GRAPH
void MainWindow::on_pushButton_print_graph_clicked() {
//  double x_min = ui->doubleSpinBox_xmin->value();
//  double x_max = ui->doubleSpinBox_xmax->value();
//  double y_min = ui->doubleSpinBox_ymin->value();
//  double y_max = ui->doubleSpinBox_ymax->value();

//  if (x_max - x_min > 0 && y_max - y_min > 0) {
//    graphPlot(x_min, x_max, y_min, y_max);
//  } else {
//    ui->statusBar->showMessage("incorrect range");
//  }
}

//void MainWindow::graphPlot(double x_min, double x_max, double y_min,
//                           double y_max) {
//  QString input_label_text = ui->label_input->text();
//  QByteArray tmp_byte_array = input_label_text.toLatin1();
//  tmp_byte_array.replace(" ", "");
//  tmp_byte_array.replace("=", "");
//  char* str_for_calc = tmp_byte_array.data();

//  int error = OK;
//  double variable = 0.0;
//  double result = 0.0;
//  node_t* q_root = NULL;
//  error = convert_infix_to_RPN(str_for_calc, &q_root);
//  remove_struct(&q_root);

//  QVector<double> x, y;
//  if (error != OK) {
//    ERRORS_MESSAGES;
//    ui->statusBar->showMessage(errors_msg[error]);

//  } else {
//    ui->statusBar->showMessage("");
//    variable = x_min;
//    double step_size = (x_max - x_min) / ui->expression_graph->width();
//    while (variable <= x_max) {
//      int error = convert_infix_to_RPN(str_for_calc, &q_root);
//      if (error == OK) {
//        error = evaluate_expression(q_root, variable, &result);
//      }
//      if (error == OK && result == result && result != 1.0 / 0.0) {
//        x.push_back(variable);
//        y.push_back(result);
//      }
//      variable += step_size;
//    }

//    ui->expression_graph->xAxis->setRange(x_min, x_max);
//    ui->expression_graph->yAxis->setRange(y_min, y_max);
//    ui->expression_graph->expression_graph();
//    ui->expression_graph->graph(0)->setData(x, y);
//    QPen pen;
//    pen.setColor(QColor(114, 215, 151));
//    pen.setWidth(2);
//    ui->expression_graph->graph(0)->setPen(pen);
//    ui->expression_graph->replot();
//  }
//}
