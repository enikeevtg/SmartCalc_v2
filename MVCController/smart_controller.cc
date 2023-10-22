#include "../MVCController/smart_controller.h"

namespace e_calc {

SmartController::SmartController(SmartCalculator* model) : model_(model) {}

void SmartController::SetCalculator(const std::string& infix_expression) {
  model_->SetCalculator(infix_expression, 0.0);
}

void SmartController::SetCalculator(const std::string& infix_expression,
                                    const double& var) {
  model_->SetCalculator(infix_expression, var);
}

double SmartController::GetResult() { return model_->GetResult(); }

const PlotPoints& SmartController::GetPlotPoints(double x_min, double x_max,
                                                 double x_step) {
  return model_->GetPlotPoints(x_min, x_max, x_step);
}

}  // namespace e_calc
