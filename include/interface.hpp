#pragma once

#include <memory>
#include <cmath>

class ICalculatable
{
private:
  double value_;
public:
  virtual double Calculate(); 
  ICalculatable();
  explicit ICalculatable(double);
  explicit ICalculatable(int);
  double getValue() const;
};