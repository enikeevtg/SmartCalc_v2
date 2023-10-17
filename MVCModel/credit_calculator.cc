#include "credit_calculator.h"

namespace e_calc {

/*
CONSTRUCTORS/DESTRUCTOR
*/

CreditCalculator::CreditCalculator() {}
CreditCalculator::~CreditCalculator() {}

/*
PUBLIC METHODS
*/

void CreditCalculator::SetCreditTerms(int& credit_type, double& total_amount,
                                      int& term, double& rate) {
  credit_type_ = credit_type;
  total_amount_ = total_amount;
  term_ = term;
  rate_ = rate / (100.0 * 12.0);
}

CreditPayments& CreditCalculator::PaymentsCalculation() {
  if (credit_type_ == kAnnuity) {
    payments_.first_month_payment =
        (total_amount_ * rate_) / (1 - pow(1.0 + rate_, -term_));
    payments_.total_payment = payments_.first_month_payment * term_;
    payments_.overpayment = payments_.total_payment - total_amount_;
  } else {
    for (int month = 1; month <= (int)term_; month++) {
      payments_.last_month_payment =
          total_amount_ / term_ +
          (total_amount_ - (month - 1) * (total_amount_ / term_)) * rate_;
      if (payments_.first_month_payment == 0.0)
        payments_.first_month_payment = payments_.last_month_payment;
      payments_.total_payment += payments_.last_month_payment;
    }
    payments_.overpayment = payments_.total_payment - total_amount_;
  }

  return payments_;
}

}  // namespace e_calc
