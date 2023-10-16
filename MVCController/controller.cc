#include "controller.h"

namespace e_calc {

/*
CONSTRUCTORS/DESTRUCTOR
*/

Controller::Controller() {}
Controller::Controller(std::string expression)
    : parser_(expression, &reverse_polish_notation_),
      solver_(&reverse_polish_notation_) {}
Controller::~Controller() {}

/*
PUBLIC METHODS
*/

double Controller::GetResult(const double& var) {
  parser_.ShuntingYardAlgorithm();
  return solver_.GetResult(var);
}

}  // namespace e_calc
