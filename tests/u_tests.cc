#include "u_tests.h"

namespace e_calc {

void CalculatorTests::SetUp() {
  model_ = new SmartCalculator();
  controller_ = new SmartController(model_);
}

void CalculatorTests::TearDown() {
  delete model_;
  delete controller_;
}

}  // namespace e_calc
