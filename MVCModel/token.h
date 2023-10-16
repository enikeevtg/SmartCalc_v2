#ifndef SMARTCALC_V2_MVCMODEL_TOKEN_H_
#define SMARTCALC_V2_MVCMODEL_TOKEN_H_

namespace e_calc {

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

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_TOKEN_H_
