#ifndef SMARTCALC_V2_MVCMODEL_MODEL_PARSER_H_
#define SMARTCALC_V2_MVCMODEL_MODEL_PARSER_H_

#include <queue>
#include <stack>
#include <string>

#include "token.h"

namespace e_calc {

class ModelParser {
 public:
  ModelParser();
  ModelParser(std::string infix_expression,
              std::queue<Token>* reverse_polish_notation);
  ~ModelParser();

 private:
  std::string str_;
  std::stack<Token> stack_;
  std::queue<Token>* queue_;
};

}  // namespace e_calc

#endif  // SMARTCALC_V2_MVCMODEL_MODEL_PARSER_H_
