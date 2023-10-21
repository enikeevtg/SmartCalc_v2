#ifndef SMARTCALC_V2_MVCMODEL_TYPES_H_
#define SMARTCALC_V2_MVCMODEL_TYPES_H_

namespace e_calc {

// Smart calculator types
enum TokenType {
  kCos,
  kSin,
  kTan,
  kAcos,
  kAsin,
  kAtan,
  kSqrt,
  kLn,
  kLog,
  kUplus,
  kUminus,
  kOpenBracket,
  kPlus,
  kMinus,
  kMult,
  kDiv,
  kMod,
  kPow,
  kNumber,
  kVar,
  kCloseBracket,
  kEndOfExpression
};

enum TokenPriority { kPrior1, kPrior2, kPrior3, kPrior4 };

struct Token {
  TokenType type;
  TokenPriority prior;
  double value;
};

// Credit calculator types
enum CreditType { kAnnuity, kDiffer };

struct CreditTerms {
  int term{0};
  double total_amount{0};
  double rate{0};  // in percentages

  CreditTerms& operator=(const CreditTerms& other) {
    term = other.term;
    total_amount = other.total_amount;
    rate = other.rate;
    return *this;
  }
};

struct CreditPayments {
  double first_month_payment{0};
  double last_month_payment{0};
  double overpayment{0};
  double total_payment{0};

  CreditPayments& operator=(const CreditPayments& other) {
    first_month_payment = other.first_month_payment;
    last_month_payment = other.last_month_payment;
    overpayment = other.overpayment;
    total_payment = other.total_payment;
    return *this;
  }
};

// Deposit calculator types
enum { kSimple, kCompound };

struct DepositTerms {
  int term{0};
  int periodicity{0};
  double total_begin{0};
  double deposit_rate{0};  // in percentages
  double tax_rate{0};      // in percentages
  double* replenishments{nullptr};
  double* withdrawals{nullptr};

  DepositTerms& operator=(const DepositTerms& other) {
    term = other.term;
    periodicity = other.periodicity;
    total_begin = other.total_begin;
    deposit_rate = other.deposit_rate;
    tax_rate = other.tax_rate;
    replenishments = other.replenishments;
    withdrawals = other.withdrawals;
    return *this;
  }
};

struct DepositPayments {
  double accrued_interest;
  double tax_amount;
  double total_end;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_TYPES_H_
