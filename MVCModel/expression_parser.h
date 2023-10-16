#ifndef SMARTCALC_V2_MVCMODEL_EXPRESSION_PARSER_H_
#define SMARTCALC_V2_MVCMODEL_EXPRESSION_PARSER_H_

#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "token.h"

namespace e_calc {

class ExpressionParser {
 public:
  ExpressionParser();
  ExpressionParser(std::queue<Token>* reverse_polish_notation);
  ~ExpressionParser();

  void ConvertInfixToPostfix(const std::string& infix_expression);

 private:
  enum Address { kStack, kQueue };

  void TokenProcessing();
  void ValueTokenProcessing();
  void VariableTokenProcessing();
  void OperatorTokenProcessing();
  void FunctionTokenProcessing();

  void CloseBracketProcessing();
  void EndOfExpressionProcessing();
  void TranslateFromStackToQueue();

  std::string str_;
  size_t pos_{0};
  Token container_{kNumber, kPrior1, 0.0};
  Address last_address_ = kStack;
  std::stack<Token> stack_;
  std::queue<Token>* queue_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_EXPRESSION_PARSER_H_
