#include "deposit_calculator.h"

namespace e_calc {

/*
PUBLIC METHODS
*/
const DepositPayments& DepositCalculator::CalculateDepositPayments(
    int type, DepositTerms* terms) {
  SetDepositTerms(type, terms);
  int payments_number = terms_.term / terms_.periodicity;
  double last_earning = 0;
  double earnings = 0;
  for (int i = 1; i <= payments_number; ++i) {
    for (int j = (i - 1) * terms_.periodicity; j < i * terms_.periodicity;
         ++j) {
      terms_.total_begin +=
          terms_.replenishments[j] - terms_.withdrawals[j + 1];
    }
    last_earning = terms_.total_begin * terms_.deposit_rate *
                   double(terms_.periodicity) / 12.0;
    earnings += last_earning;
    if (deposit_type_ == kCompound) terms_.total_begin += last_earning;
    if (terms_.total_begin < 0.0) {
      throw "Error: invalid account balance";
    }
  }

  if (earnings > key_rate_ * 1000000) {
    payments_.tax_amount = (earnings - key_rate_ * 1000000) * terms_.tax_rate;
  }
  payments_.accrued_interest = earnings;
  payments_.total_end = terms_.total_begin;
  if (deposit_type_ == kSimple) payments_.total_end += earnings;

  return payments_;
}

/*
PRIVATE METHODS
*/
void DepositCalculator::SetDepositTerms(int type, DepositTerms* terms) {
  deposit_type_ = type;
  terms_ = *terms;
  // cause view gives rates in percentages
  terms_.deposit_rate /= 100.0;
  terms_.tax_rate /= 100.0;

  payments_.accrued_interest = 0.0;
  payments_.tax_amount = 0.0;
  payments_.total_end = 0.0;
}

}  // namespace e_calc
