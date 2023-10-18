#ifndef SMARTCALC_V2_MVCMODEL_CREDIT_CALCULATOR_H_
#define SMARTCALC_V2_MVCMODEL_CREDIT_CALCULATOR_H_

#include "cmath"

namespace e_calc {

enum CreditType { kAnnuity, kDiffer };

struct CreditTerms {
  int term{0};
  double total_amount{0};
  double rate{0};
};

struct CreditPayments {
  double first_month_payment{0};
  double last_month_payment{0};
  double overpayment{0};
  double total_payment{0};

  CreditPayments& operator=(CreditPayments& other) {  // translate to .cc file?
    first_month_payment = other.first_month_payment;
    last_month_payment = other.last_month_payment;
    overpayment = other.overpayment;
    total_payment = other.total_payment;
    return *this;
  }
};

class CreditCalculator {
 public:
  CreditCalculator();
  ~CreditCalculator();

  // Set and Get or omly Get with parameters?
  void SetCreditTerms(int& credit_type, CreditTerms& terms);
  CreditPayments& GetCreditPayments();

 private:
  int credit_type_;
  CreditTerms terms_;  // or pointer?
  CreditPayments payments_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_CREDIT_CALCULATOR_H_
