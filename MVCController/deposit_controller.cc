#include "../MVCController/deposit_controller.h"

namespace e_calc {

DepositController::DepositController(DepositCalculator* model)
    : model_(model) {}

const DepositPayments& DepositController::CalculateDepositPayments(
    int deposit_type, DepositTerms* terms) {
  return model_->CalculateDepositPayments(deposit_type, terms);
}

}  // namespace e_calc
