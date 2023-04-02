#include "calculator.hpp"

ICalculatable::ICalculatable(){};

ICalculatable::ICalculatable(double value): value_(value) {};

ICalculatable::ICalculatable(ICalculatable& object): value_(object.value_) {};

double ICalculatable::getValue()
{
  return value_;
}

double ICalculatable::Calculate()
{
  return value_;
}



Plus::Plus(std::unique_ptr<ICalculatable> left_operand, std::unique_ptr<ICalculatable> right_operand):
 left_operand_(std::move(left_operand)), right_operand_(std::move(right_operand))
{
}

double Plus::Calculate()
{
  return left_operand_->Calculate() + right_operand_->Calculate();
}



Minus::Minus(std::unique_ptr<ICalculatable> left_operand, std::unique_ptr<ICalculatable> right_operand):
 left_operand_(std::move(left_operand)), right_operand_(std::move(right_operand))
{
}

double Minus::Calculate()
{
  return left_operand_->Calculate() - right_operand_->Calculate();
}



Divide::Divide(std::unique_ptr<ICalculatable> left_operand, std::unique_ptr<ICalculatable> right_operand):
 left_operand_(std::move(left_operand)), right_operand_(std::move(right_operand))
{
}

double Divide::Calculate()
{
  return left_operand_->Calculate() / right_operand_->Calculate();
}



atan::atan(std::unique_ptr<ICalculatable> operand):
 operand_(std::move(operand))
{
}

double atan::Calculate()
{
  return std::atan(operand_->Calculate());
}



abs::abs(std::unique_ptr<ICalculatable> operand):
 operand_(std::move(operand))
{
}

double abs::Calculate()
{
  return std::abs(operand_->Calculate());
}