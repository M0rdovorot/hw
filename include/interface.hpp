#pragma once

#include <memory>
#include <cmath>

class ICalculatable {
public:
  virtual double Calculate() = 0; 
};
