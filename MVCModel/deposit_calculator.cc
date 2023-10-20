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
  int accruals_number = terms_->term / terms_->periodicity;
  double last_earning = 0;
  double earnings = 0;
  for (int i = 1; i <= accruals_number; ++i) {
    for (int j = (i - 1) * terms_->periodicity; j < i * terms_->periodicity;
         ++j) {
      terms_->total_begin +=
          terms_->replenishments[j] - terms_->withdrawals[j + 1];
    }
    last_earning = terms_->total_begin * terms_->deposit_rate / 100.0 *
                   (double)terms_->periodicity / 12.0;
    earnings += last_earning;
    if (type_ == kCompound) terms_->total_begin += last_earning;
    if (terms_->total_begin < 0.0) {
      throw "Error: invalid account balance";
    }
  }

  payments_.tax_amount = 0.0;
  if (earnings > CB_key_rate_ * 1000000) {
    payments_.tax_amount =
        (earnings - CB_key_rate_ * 1000000) * terms_->tax_rate / 100.0;
  }
  payments_.accrued_interest = earnings;
  payments_.total_end = terms_->total_begin;
  if (type_ == kSimple) payments_.total_end += earnings;

  return payments_;
}

}  // namespace e_calc
