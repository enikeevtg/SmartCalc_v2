#include "u_tests.h"

namespace e_calc {

// Smart Calculator
void CalculatorTests::SetUp() {
  model_ = new SmartCalculator();
  controller_ = new SmartController(model_);
}

void CalculatorTests::TearDown() {
  delete model_;
  delete controller_;
}

// Credit Calculator
void CreditTests::SetUp() {
  model_ = new CreditCalculator();
  controller_ = new CreditController(model_);
}

void CreditTests::TearDown() {
  delete model_;
  delete controller_;
}

// Deposit Calculator
void DepositTests::SetUp() {
  model_ = new DepositCalculator();
  controller_ = new DepositController(model_);
}

void DepositTests::TearDown() {
  delete model_;
  delete controller_;
}

}  // namespace e_calc
