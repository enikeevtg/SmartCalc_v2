#ifndef SMARTCALC_V2_MVCMODEL_EXPRESSION_PARSER_H_
#define SMARTCALC_V2_MVCMODEL_EXPRESSION_PARSER_H_

#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "types.h"

namespace e_calc {

class ExpressionParser {
 public:
  ExpressionParser() = default;
  explicit ExpressionParser(std::queue<Token>* queue);
  ~ExpressionParser() = default;

  void SetParser(const std::string& infix_expression);
  void ConvertInfixToPostfix();

 private:
  enum Address { kStack, kQueue };

  void CleanStack();
  void TokenProcessing();
  void ValueTokenProcessing();
  void VariableTokenProcessing();
  void OperatorTokenProcessing();
  void FunctionTokenProcessing();
  void CloseBracketProcessing();
  void EndOfExpressionProcessing();
  void TranslateFromStackToQueue();

  inline static std::string token_chars_{"1234567890.+-*/^%(cstalx"};
  inline static std::string numbers_chars_ = "1234567890.";
  inline static std::string operators_chars_ = "+-*/^%()";
  inline static std::vector<std::string> math_functions_names_{
      "cos", "sin", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};
      
  std::string str_;
  size_t pos_{0};
  Token container_{kNumber, kPrior1, 0.0};
  Address last_address_{kStack};
  std::stack<Token> stack_;
  std::queue<Token>* queue_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_EXPRESSION_PARSER_H_
