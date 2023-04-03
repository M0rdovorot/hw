#include "calculator.hpp"
#include <iostream> // LOL

ICalculatable::ICalculatable(){};

ICalculatable::ICalculatable(double value): value_(value) {};

ICalculatable::ICalculatable(int value): value_((double)value){};

double ICalculatable::getValue() const
{
  return value_;
}

double ICalculatable::Calculate()
{
  return value_;
}

void ICalculatable::Print() // LOL
{
  std::cout << "ICalculatable" << std::endl;
}

ICalculatable::ICalculatable(const ICalculatable& object): value_(object.getValue()) {}



Plus::Plus(std::unique_ptr<ICalculatable> left_operand, std::unique_ptr<ICalculatable> right_operand):
 left_operand_(std::move(left_operand)), right_operand_(std::move(right_operand))
{
}

double Plus::Calculate()
{
  return left_operand_->Calculate() + right_operand_->Calculate();
}

void Plus::Print() //LOL
{
  std::cout << "Plus" << std::endl;
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



Atan::Atan(std::unique_ptr<ICalculatable> operand):
 operand_(std::move(operand))
{
}

double Atan::Calculate()
{
  return std::atan(operand_->Calculate());
}



Abs::Abs(std::unique_ptr<ICalculatable> operand):
 operand_(std::move(operand))
{
}

double Abs::Calculate()
{
  return std::abs(operand_->Calculate());
}