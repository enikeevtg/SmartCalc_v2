#include <cmath>
#include "u_tests.h"

namespace e_calc {

TEST_F(CalculatorTests, AdditionOperation) {
  std::string expression{"1563.156 + 694.644"};
  double reference_value = 1563.156 + 694.644;
  controller_->SetCalculator(expression);
  EXPECT_EQ(controller_->GetResult(), reference_value);
}

TEST_F(CalculatorTests, SubtractionOperation) {
  std::string expression{"683.1 - 69.354"};
  double reference_value = 683.1 - 69.354;
  controller_->SetCalculator(expression);
  EXPECT_EQ(controller_->GetResult(), reference_value);
}

TEST_F(CalculatorTests, MultiplicationOperation) {
  std::string expression{"917.95 * 0.158"};
  double reference_value = 917.95 * 0.158;
  controller_->SetCalculator(expression);
  EXPECT_EQ(controller_->GetResult(), reference_value);
}

TEST_F(CalculatorTests, DivisionOperation) {
  std::string expression{"148.646 / 5.786"};
  double reference_value = 148.646 / 5.786;
  controller_->SetCalculator(expression);
  EXPECT_EQ(controller_->GetResult(), reference_value);
}

TEST_F(CalculatorTests, PowerOperation) {
  std::string expression{"467.65^2.45"};
  double reference_value = std::pow(467.65, 2.45);
  controller_->SetCalculator(expression);
  EXPECT_EQ(controller_->GetResult(), reference_value);
}

TEST_F(CalculatorTests, ModulusOperation) {
  std::string expression{"483.68 % 3.16"};
  double reference_value = std::fmod(483.68, 3.16);
  controller_->SetCalculator(expression);
  EXPECT_EQ(controller_->GetResult(), reference_value);
}

TEST_F(CalculatorTests, UnaryPlusOperation) {
  std::string expression{"+8687.473"};
  double reference_value = +8687.473;
  controller_->SetCalculator(expression);
  EXPECT_EQ(controller_->GetResult(), reference_value);
}

TEST_F(CalculatorTests, UnaryMinusOperation) {
  std::string expression{"-354.486"};
  double reference_value = -354.486;
  controller_->SetCalculator(expression);
  EXPECT_EQ(controller_->GetResult(), reference_value);
}

TEST_F(CalculatorTests, CombineOperation) {
  std::string expression{"(364 + 73) - 43.48 * 46 / 0.2486"};
  double reference_value = (364 + 73) - 43.48 * 46 / 0.2486;
  controller_->SetCalculator(expression);
  EXPECT_EQ(controller_->GetResult(), reference_value);
}

TEST_F(CalculatorTests, VariableToken) {
  std::string expression{"sin(x)"};
  double var = 0.7632;
  double reference_value = std::sin(var);
  controller_->SetCalculator(expression, var);
  EXPECT_EQ(controller_->GetResult(), reference_value);
}

TEST_F(CalculatorTests, GetPlotPointsX) {
  std::string expression{"x"};
  controller_->SetCalculator(expression);
  double x_min = -11;
  double x_max = 11;
  double x_step = 1;
  e_calc::PlotPoints points = controller_->GetPlotPoints(x_min, x_max, x_step);
  double reference_value = x_min;
  int i = 0;
  while (reference_value <= x_max) {
    EXPECT_EQ(points.y_coord[i], reference_value);
    reference_value += x_step;
    ++i;
  }
}

TEST_F(CalculatorTests, GetPlotPointsAsin) {
  std::string expression{"asin(x)"};
  controller_->SetCalculator(expression);
  double x_min = -11;
  double x_max = 11;
  double x_step = 1;
  e_calc::PlotPoints points = controller_->GetPlotPoints(x_min, x_max, x_step);
  double x = x_min;
  int i = 0;
  while (x <= x_max) {
    if (-1 <= x && x <= 1) {
      double reference_value = std::asin(x);
      EXPECT_EQ(points.y_coord[i], reference_value);
      ++i;
    }
    x += x_step;
  }
}

}  // namespace e_calc
