#include "u_tests.h"

namespace e_calc {

TEST_F(CalculatorTests, LargeLengthThrow) {
  std::string expression;
  for (int i = 0; i < 256; ++i) {
    expression.push_back('1');
  }
  EXPECT_ANY_THROW(controller_->SetCalculator(expression));
}

TEST_F(CalculatorTests, IncorrectLastInput) {
  std::string expression{"1+"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

TEST_F(CalculatorTests, UndefinedToken) {
  std::string expression{"expression"};
  controller_->SetCalculator(expression);
  EXPECT_ANY_THROW(controller_->GetResult());
}

}  // namespace e_calc
