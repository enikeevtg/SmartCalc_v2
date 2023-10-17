#include "deposit_calculator.h"

namespace e_calc {

/*
CONSTRUCTORS/DESTRUCTOR
*/

DepositCalculator::DepositCalculator() {}
DepositCalculator::~DepositCalculator() {}

/*
PUBLIC METHODS
*/

void DepositCalculator::SetDepositTerms(int& type, DepositTerms* terms) {
  type_ = type;
  terms_ = terms;
}

DepositPayments& DepositCalculator::GetDepositPayments() {
  double CB_key_rate = 0.075;
  int periodicity = terms_->periodicity;
  int term = terms_->term;
  double total = terms_->total_begin;
  double deposit_rate = terms_->deposit_rate;
  double tax_rate = terms_->tax_rate;
  double* replenishments = terms_->replenishments;
  double* withdrawals = terms_->withdrawals;

  int accruals_number = term / periodicity;
  double last_earning = 0;
  double earnings = 0;
  for (int i = 1; i <= accruals_number; i++) {
    for (int j = (i - 1) * periodicity; j < i * periodicity; j++) {
      total += replenishments[j] - withdrawals[j + 1];
    }
    last_earning = total * deposit_rate / 100.0 * (double)periodicity / 12.0;
    earnings += last_earning;
    if (type_ == kCompound) total += last_earning;
    if (total < 0.0) {
      throw "Error: invalid account balance";
    }
  }

  payments_.tax_amount = 0.0;
  if (earnings > CB_key_rate * 1000000) {
    payments_.tax_amount =
        (earnings - CB_key_rate * 1000000) * tax_rate / 100.0;
  }
  payments_.accrued_interest = earnings;
  payments_.total_end = total;

  return payments_;
}

}  // namespace e_calc
