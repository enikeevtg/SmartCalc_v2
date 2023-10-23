#ifndef TESTS_U_TESTS_H_
#define TESTS_U_TESTS_H_

#include <gtest/gtest.h>

#include <string>

#include "../MVCController/credit_controller.h"
#include "../MVCController/deposit_controller.h"
#include "../MVCController/smart_controller.h"

namespace e_calc {

class CalculatorTests : public testing::Test {
 public:
  void SetUp();
  void TearDown();

 protected:
  SmartCalculator* model_{nullptr};
  SmartController* controller_{nullptr};
};

class CreditTests : public testing::Test {
 public:
  void SetUp();
  void TearDown();

 protected:
  CreditCalculator* model_{nullptr};
  CreditController* controller_{nullptr};
};

class DepositTests : public testing::Test {
 public:
  void SetUp();
  void TearDown();

 protected:
  DepositCalculator* model_{nullptr};
  DepositController* controller_{nullptr};
};

}  // namespace e_calc

#endif  // TESTS_U_TESTS_H_
