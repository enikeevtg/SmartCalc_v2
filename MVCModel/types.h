#ifndef SMARTCALC_V2_MVCMODEL_TOKEN_H_
#define SMARTCALC_V2_MVCMODEL_TOKEN_H_

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
  double rate{0};
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

// Deposit calculetor types

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_TOKEN_H_
