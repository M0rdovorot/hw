#include "interface.hpp"
#include "operations.hpp"

Number::Number(double value): value_(value) {};

Number::Number(int value): value_(value) {};

double Number::getValue() const {
  return value_;
}

double Number::Calculate() {
  return value_;
}



Plus::Plus(std::unique_ptr<ICalculatable> left_operand, std::unique_ptr<ICalculatable> right_operand)
    : left_operand_(std::move(left_operand)),
      right_operand_(std::move(right_operand)) {
}

double Plus::Calculate() {
  return left_operand_->Calculate() + right_operand_->Calculate();
}



Minus::Minus(std::unique_ptr<ICalculatable> left_operand, std::unique_ptr<ICalculatable> right_operand)
    : left_operand_(std::move(left_operand)),
      right_operand_(std::move(right_operand)) {
}

double Minus::Calculate() {
  return left_operand_->Calculate() - right_operand_->Calculate();
}



UnaryMinus::UnaryMinus(std::unique_ptr<ICalculatable> operand) : operand_(std::move(operand)) {
}

double UnaryMinus::Calculate() {
  return -operand_->Calculate();
}



Divide::Divide(std::unique_ptr<ICalculatable> left_operand, std::unique_ptr<ICalculatable> right_operand)
    : left_operand_(std::move(left_operand)),
      right_operand_(std::move(right_operand)) {
}

double Divide::Calculate() {
  return left_operand_->Calculate() / right_operand_->Calculate();
}



Atan::Atan(std::unique_ptr<ICalculatable> operand) : operand_(std::move(operand)) {
}

double Atan::Calculate() {
  return std::atan(operand_->Calculate());
}



Abs::Abs(std::unique_ptr<ICalculatable> operand) : operand_(std::move(operand)) {
}

double Abs::Calculate() {
  return std::abs(operand_->Calculate());
}