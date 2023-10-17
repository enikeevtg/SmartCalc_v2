#ifndef SMARTCALC_V2_MVCMODEL_CREDIT_CALCULATOR_H_
#define SMARTCALC_V2_MVCMODEL_CREDIT_CALCULATOR_H_

#include "cmath"

namespace e_calc {

struct CreditPayments {
  double first_month_payment;
  double last_month_payment;
  double overpayment;
  double total_payment;

  CreditPayments() {
    first_month_payment = 0;
    last_month_payment = 0;
    overpayment = 0;
    total_payment = 0;
  }

  CreditPayments& operator=(CreditPayments& other) {
    first_month_payment = other.first_month_payment;
    last_month_payment = other.last_month_payment;
    overpayment = other.overpayment;
    total_payment = other.total_payment;

    return *this;
  }
};

enum CreditType { kAnnuity, kDiffer };

class CreditCalculator {
 public:
  CreditCalculator();
  ~CreditCalculator();

  void SetCreditTerms(int& credit_type, double& total_amount, int& term,
                      double& rate);
  CreditPayments& PaymentsCalculation();

 private:
  int credit_type_;
  double total_amount_;
  int term_;
  double rate_;
  CreditPayments payments_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_CREDIT_CALCULATOR_H_
