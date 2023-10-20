#ifndef SMARTCALC_V2_MVCMODEL_DEPOSIT_CALCULATOR_H_
#define SMARTCALC_V2_MVCMODEL_DEPOSIT_CALCULATOR_H_

#include "cmath"

namespace e_calc {

enum { kSimple, kCompound };

struct DepositTerms {
  int term;
  int periodicity;
  double total_begin;
  double deposit_rate;  // in percentages
  double tax_rate;
  double* replenishments;
  double* withdrawals;
};

struct DepositPayments {
  double accrued_interest;
  double tax_amount;
  double total_end;
};

class DepositCalculator {
 public:
  DepositCalculator();
  ~DepositCalculator();

  void SetDepositTerms(int& type, DepositTerms* terms);
  DepositPayments& GetDepositPayments();

 private:
  double CB_key_rate_{0.075};
  int type_;
  DepositTerms* terms_;  // or lvalue?
  DepositPayments payments_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_DEPOSIT_CALCULATOR_H_
