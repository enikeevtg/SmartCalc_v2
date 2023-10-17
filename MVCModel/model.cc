#include "model.h"

namespace e_calc {

/*
CONSTRUCTORS/DESTRUCTOR
*/

Model::Model() : parser_(&queue_), solver_(&queue_){};
Model::~Model(){};

/*
PUBLIC METHODS
*/

void Model::SetModel(const std::string& infix_expression, const double& var) {
  str_ = infix_expression;
  var_ = var;
  CleanQueue();
  parser_.SetParser(infix_expression);
  points_.x_coord.clear();
  points_.y_coord.clear();
}

double Model::GetResult() {
  parser_.ConvertInfixToPostfix();
  return solver_.GetResult(var_);
}

PlotPoints Model::GetPlotPoints(const double& x_min, const double& x_max,
                                const double& x_step) {
  if (x_min < -1000000 || x_max > 1000000 || x_min >= x_max) {
    throw "Error: incorrect plot range";
  }

  CleanQueue();
  parser_.ConvertInfixToPostfix();
  double x = x_min;
  for (; x <= x_max; x += x_step) {
    points_.x_coord.push_back(x);

    try {
      points_.y_coord.push_back(solver_.GetResult(x));
    } catch (const char* message) {
      points_.x_coord.pop_back();
    }
  }

  return points_;
}

/*
PRIVATE METHODS
*/

void Model::CleanQueue() {
  std::queue<Token> empty_queue;
  queue_.swap(empty_queue);
}

}  // namespace e_calc
