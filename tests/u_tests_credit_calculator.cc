#include "u_tests.h"

namespace e_calc {

/*
EXCEPTIONS
*/

TEST_F(CreditTests, ThrowInvalidTerm1) {
  int credit_type = kAnnuity;
  CreditTerms terms;
  terms.term = 0;
  terms.total_amount = 11;
  terms.rate = 11;
  EXPECT_ANY_THROW(controller_->CalculateCreditPayments(credit_type, &terms));
}

TEST_F(CreditTests, ThrowInvalidTerm2) {
  int credit_type = kAnnuity;
  CreditTerms terms;
  terms.term = 601;
  terms.total_amount = 11;
  terms.rate = 11;
  EXPECT_ANY_THROW(controller_->CalculateCreditPayments(credit_type, &terms));
}

TEST_F(CreditTests, ThrowInvalidTotalAmount) {
  int credit_type = kAnnuity;
  CreditTerms terms;
  terms.term = 1;
  terms.total_amount = 0;
  terms.rate = 11;
  EXPECT_ANY_THROW(controller_->CalculateCreditPayments(credit_type, &terms));
}

TEST_F(CreditTests, ThrowInvalidRate) {
  int credit_type = kAnnuity;
  CreditTerms terms;
  terms.term = 1;
  terms.total_amount = 11;
  terms.rate = -0.01;
  EXPECT_ANY_THROW(controller_->CalculateCreditPayments(credit_type, &terms));
}

// /*
// NORMAL
// */

TEST_F(CreditTests, AnnuityCredit) {
  int credit_type = kAnnuity;
  CreditTerms terms;
  terms.term = 1;
  terms.total_amount = 100000;
  terms.rate = 6;
  CreditPayments payments;
  CreditPayments reference_payments{100500, 0, 500, 100500};
  payments = controller_->CalculateCreditPayments(credit_type, &terms);
  EXPECT_NEAR(payments.first_month_payment,
              reference_payments.first_month_payment, 1e-7);
  EXPECT_NEAR(payments.overpayment, reference_payments.overpayment, 1e-7);
  EXPECT_NEAR(payments.total_payment, reference_payments.total_payment, 1e-7);
}

TEST_F(CreditTests, DifferCredit) {
  int credit_type = kDiffer;
  CreditTerms terms;
  terms.term = 1;
  terms.total_amount = 100000;
  terms.rate = 6;
  CreditPayments payments;
  CreditPayments reference_payments{100500, 100500, 500, 100500};
  payments = controller_->CalculateCreditPayments(credit_type, &terms);
  EXPECT_NEAR(payments.first_month_payment,
              reference_payments.first_month_payment, 1e-7);
  EXPECT_NEAR(payments.last_month_payment,
              reference_payments.last_month_payment, 1e-7);
  EXPECT_NEAR(payments.overpayment, reference_payments.overpayment, 1e-7);
  EXPECT_NEAR(payments.total_payment, reference_payments.total_payment, 1e-7);
}

}  // namespace e_calc
