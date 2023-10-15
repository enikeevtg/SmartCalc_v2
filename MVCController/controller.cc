#include "controller.h"

namespace e_calc {

/*
CONSTRUCTORS/DESTRUCTOR
*/

Controller::Controller() {}
Controller::Controller(std::string expression, double var)
    : reverse_polish_notation_(),
      parser_(expression, &reverse_polish_notation_),
      solver_(&reverse_polish_notation_, var) {}
Controller::~Controller() {}

/*
PUBLIC METHODS
*/

double Controller::GetResult(double var) {
  parser_.ShuntingYardAlgorithm();
  return solver_.Solve();
}

}  // namespace e_calc
