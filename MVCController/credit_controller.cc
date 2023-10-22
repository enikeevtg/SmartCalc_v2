#include "../MVCController/credit_controller.h"

namespace e_calc {

CreditController::CreditController(CreditCalculator* model) : model_(model) {}

const CreditPayments& CreditController::CalculateCreditPayments(
    int credit_type, CreditTerms* terms) {
  return model_->CalculateCreditPayments(credit_type, terms);
}

}  // namespace e_calc
