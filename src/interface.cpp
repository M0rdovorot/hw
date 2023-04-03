#include "interface.hpp"

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