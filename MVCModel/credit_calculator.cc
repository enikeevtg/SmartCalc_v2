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

// reference, const reference or lvalue terms?
void CreditCalculator::SetCreditTerms(int& credit_type, CreditTerms& terms) {
  if (terms.total_amount < 0.01) {
    throw "Error: total credit amount minimum value is 0.01";
  } else if (terms.term < 1) {
    throw "Error: credit term minimum value is 1 month";
  } else if (terms.term > 600) {
    throw "Error: credit term maximum value is 600 months";
  } else if (terms.rate < 0.01) {
    throw "Error: credit rate minimum value is 0.01";
  }

  credit_type_ = credit_type;
  terms_.total_amount = terms.total_amount;
  terms_.term = terms.term;
  terms_.rate = terms.rate / (100.0 * 12.0);

  payments_.first_month_payment = 0;
  payments_.last_month_payment = 0;
  payments_.overpayment = 0;
  payments_.total_payment = 0;
}

CreditPayments& CreditCalculator::GetCreditPayments() {
  if (credit_type_ == kAnnuity) {
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

}  // namespace e_calc
