#include "u_tests.h"

namespace e_calc {

TEST_F(CalculatorTests, ThrowTooLargeLength) {
  std::string expression;
  for (int i = 0; i < 256; ++i) {
    expression.push_back('1');
  }
  EXPECT_ANY_THROW(controller_->SetCalculator(expression));
}

TEST_F(CalculatorTests, ThrowIncorrectLastInputToken) {
  std::string expression{"18+"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

TEST_F(CalculatorTests, ThrowIncorrectInput) {
  std::string expression{"18+)"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

TEST_F(CalculatorTests, ThrowUndefinedToken1) {
  std::string expression{"expression"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

TEST_F(CalculatorTests, ThrowUndefinedToken2) {
  std::string expression{"sing(3.14)"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

TEST_F(CalculatorTests, ThrowUnbalancedBrackets) {
  std::string expression{"sin(3.14"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

TEST_F(CalculatorTests, ThrowIncorrectPlotRange1) {
  std::string expression{"cos(x)"};
  controller_->SetCalculator(expression);
  double x_min = -1000001;
  double x_max = 11;
  double x_step = 0.01;
  EXPECT_ANY_THROW(controller_->GetPlotPoints(x_min, x_max, x_step));
}

TEST_F(CalculatorTests, ThrowIncorrectPlotRange2) {
  std::string expression{"tan(x)"};
  controller_->SetCalculator(expression);
  double x_min = -11;
  double x_max = 1000001;
  double x_step = 0.01;
  EXPECT_ANY_THROW(controller_->GetPlotPoints(x_min, x_max, x_step));
}

TEST_F(CalculatorTests, ThrowIncorrectPlotRange3) {
  std::string expression{"sqrt(x)"};
  controller_->SetCalculator(expression);
  double x_min = 11;
  double x_max = -11;
  double x_step = 0.01;
  EXPECT_ANY_THROW(controller_->GetPlotPoints(x_min, x_max, x_step));
}

TEST_F(CalculatorTests, ThrowAcosInvalidArgument) {
  std::string expression{"acos(1.01)"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

TEST_F(CalculatorTests, ThrowAsinInvalidArgument) {
  std::string expression{"asin(-1.01)"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

TEST_F(CalculatorTests, ThrowLnInvalidArgument) {
  std::string expression{"ln(-0.01)"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

TEST_F(CalculatorTests, ThrowLogInvalidArgument) {
  std::string expression{"log(-0.01)"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

TEST_F(CalculatorTests, ThrowSqrtInvalidArgument) {
  std::string expression{"sqrt(-0.01)"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

}  // namespace e_calc
