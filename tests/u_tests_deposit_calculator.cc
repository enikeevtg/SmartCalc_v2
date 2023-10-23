#include "u_tests.h"

namespace e_calc {

/*
EXCEPTIONS
*/

TEST_F(DepositTests, ThrowInvalidTerm) {
  int deposit_type = kSimple;
  DepositTerms terms;
  terms.term = 0;
  terms.periodicity = 1;
  terms.total_begin = 11;
  terms.deposit_rate = 11;
  terms.tax_rate = 11;
  terms.replenishments = nullptr;
  terms.withdrawals = nullptr;
  EXPECT_ANY_THROW(controller_->CalculateDepositPayments(deposit_type, &terms));
}

TEST_F(DepositTests, ThrowInvalidPeroiodicity) {
  int deposit_type = kSimple;
  DepositTerms terms;
  terms.term = 1;
  terms.periodicity = 0;
  terms.total_begin = 11;
  terms.deposit_rate = 11;
  terms.tax_rate = 11;
  terms.replenishments = nullptr;
  terms.withdrawals = nullptr;
  EXPECT_ANY_THROW(controller_->CalculateDepositPayments(deposit_type, &terms));
}

TEST_F(DepositTests, ThrowInvalidTotalBegin) {
  int deposit_type = kSimple;
  DepositTerms terms;
  terms.term = 1;
  terms.periodicity = 1;
  terms.total_begin = 0;
  terms.deposit_rate = 11;
  terms.tax_rate = 11;
  terms.replenishments = nullptr;
  terms.withdrawals = nullptr;
  EXPECT_ANY_THROW(controller_->CalculateDepositPayments(deposit_type, &terms));
}

TEST_F(DepositTests, ThrowInvalidDepositRate) {
  int deposit_type = kSimple;
  DepositTerms terms;
  terms.term = 1;
  terms.periodicity = 1;
  terms.total_begin = 11;
  terms.deposit_rate = -11;
  terms.tax_rate = 11;
  terms.replenishments = nullptr;
  terms.withdrawals = nullptr;
  EXPECT_ANY_THROW(controller_->CalculateDepositPayments(deposit_type, &terms));
}

TEST_F(DepositTests, ThrowInvalidTaxRate) {
  int deposit_type = kSimple;
  DepositTerms terms;
  terms.term = 1;
  terms.periodicity = 1;
  terms.total_begin = 11;
  terms.deposit_rate = 11;
  terms.tax_rate = -11;
  terms.replenishments = nullptr;
  terms.withdrawals = nullptr;
  EXPECT_ANY_THROW(controller_->CalculateDepositPayments(deposit_type, &terms));
}

TEST_F(DepositTests, ThrowInvalidAccountBalance) {
  int deposit_type = kSimple;
  DepositTerms terms;
  terms.term = 12;
  terms.periodicity = 12;
  terms.total_begin = 100000;
  terms.deposit_rate = 6;
  terms.tax_rate = 0;
  terms.replenishments = new double[terms.term]{};
  terms.withdrawals = new double[terms.term]{};
  terms.withdrawals[1] = 100001;
  EXPECT_ANY_THROW(controller_->CalculateDepositPayments(deposit_type, &terms));
  delete[] terms.replenishments;
  delete[] terms.withdrawals;
}

// /*
// NORMAL
// */

TEST_F(DepositTests, SimpleDeposit) {
  int deposit_type = kSimple;
  DepositTerms terms;
  terms.term = 1;
  terms.periodicity = 1;
  terms.total_begin = 100000;
  terms.deposit_rate = 6;
  terms.tax_rate = 0;
  terms.replenishments = new double[terms.term]{};
  terms.withdrawals = new double[terms.term]{};
  DepositPayments payments;
  DepositPayments reference_payments{500, 0, 100500};
  payments = controller_->CalculateDepositPayments(deposit_type, &terms);
  EXPECT_NEAR(payments.accrued_interest, reference_payments.accrued_interest,
              1e-7);
  EXPECT_NEAR(payments.tax_amount, reference_payments.tax_amount, 1e-7);
  EXPECT_NEAR(payments.total_end, reference_payments.total_end, 1e-7);
  delete[] terms.replenishments;
  delete[] terms.withdrawals;
}

TEST_F(DepositTests, SimpleDepositWithTax) {
  int deposit_type = kSimple;
  DepositTerms terms;
  terms.term = 12;
  terms.periodicity = 12;
  terms.total_begin = 1000000;
  terms.deposit_rate = 10;
  terms.tax_rate = 10;
  terms.replenishments = new double[terms.term]{};
  terms.withdrawals = new double[terms.term]{};
  DepositPayments payments;
  DepositPayments reference_payments{100000, 2500, 1100000};
  payments = controller_->CalculateDepositPayments(deposit_type, &terms);
  EXPECT_NEAR(payments.accrued_interest, reference_payments.accrued_interest,
              1e-7);
  EXPECT_NEAR(payments.tax_amount, reference_payments.tax_amount, 1e-7);
  EXPECT_NEAR(payments.total_end, reference_payments.total_end, 1e-7);
  delete[] terms.replenishments;
  delete[] terms.withdrawals;
}

TEST_F(DepositTests, CompoundDeposit) {
  int deposit_type = kCompound;
  DepositTerms terms;
  terms.term = 1;
  terms.periodicity = 1;
  terms.total_begin = 100000;
  terms.deposit_rate = 6;
  terms.tax_rate = 0;
  terms.replenishments = new double[terms.term]{};
  terms.withdrawals = new double[terms.term]{};
  DepositPayments payments;
  DepositPayments reference_payments{500, 0, 100500};
  payments = controller_->CalculateDepositPayments(deposit_type, &terms);
  EXPECT_NEAR(payments.accrued_interest, reference_payments.accrued_interest,
              1e-7);
  EXPECT_NEAR(payments.tax_amount, reference_payments.tax_amount, 1e-7);
  EXPECT_NEAR(payments.total_end, reference_payments.total_end, 1e-7);
  delete[] terms.replenishments;
  delete[] terms.withdrawals;
}

}  // namespace e_calc
