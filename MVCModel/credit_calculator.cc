#include "credit_calculator.h"

namespace e_calc {

/*
PUBLIC METHODS
*/

const CreditPayments& CreditCalculator::CalculateCreditPayments(
    int type, CreditTerms* terms) {
  SetCreditTerms(type, terms);

  if (type_ == kAnnuity) {
    payments_.first_month_payment = (terms_.total_amount * terms_.rate) /
                                    (1 - pow(1.0 + terms_.rate, -terms_.term));
    payments_.total_payment = payments_.first_month_payment * terms_.term;
    payments_.overpayment = payments_.total_payment - terms_.total_amount;
  } else {
    for (int month = 1; month <= (int)terms_.term; ++month) {
      payments_.last_month_payment =
          terms_.total_amount / terms_.term +
          (terms_.total_amount -
           (month - 1) * (terms_.total_amount / terms_.term)) *
              terms_.rate;
      if (payments_.first_month_payment == 0.0) {
        payments_.first_month_payment = payments_.last_month_payment;
      }
      payments_.total_payment += payments_.last_month_payment;
    }
    payments_.overpayment = payments_.total_payment - terms_.total_amount;
  }

  return payments_;
}

/*
PRIVATE METHODS
*/

void CreditCalculator::SetCreditTerms(int credit_type, CreditTerms* terms) {
  if (terms->term < 1) {
    throw "Error: credit term minimum value is 1 month";
  } else if (terms->term > 600) {
    throw "Error: credit term maximum value is 600 months";
  } else if (terms->total_amount < 0.01) {
    throw "Error: total credit amount minimum value is 0.01";
  } else if (terms->rate < 0.0) {
    throw "Error: credit rate minimum value is 0.0";
  }

  type_ = credit_type;
  terms_ = *terms;
  // cause view gives rates in percentages
  terms_.rate = terms_.rate / (100.0 * 12.0);

  payments_.first_month_payment = 0;
  payments_.last_month_payment = 0;
  payments_.overpayment = 0;
  payments_.total_payment = 0;
}

}  // namespace e_calc
