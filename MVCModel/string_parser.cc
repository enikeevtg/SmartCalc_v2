#include "string_parser.h"

namespace e_calc {

ModelParser::ModelParser() {}

ModelParser::ModelParser(std::string infix_expression,
                         std::queue<Token>* reverse_polish_notation)
    : str_(infix_expression), queue_(reverse_polish_notation) {}

ModelParser::~ModelParser() {}

}  // namespace e_calc
