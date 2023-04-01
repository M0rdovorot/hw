

#include "calculator.hpp"

class ICalculatable
{
private:
  double value_;
public:
  virtual double Calculate() = 0; 
  explicit ICalculatable(double value): value_(value) {};
  ICalculatable(ICalculatable& object): value_(object.value_) {};
};

class Plus
{
private:
  /* data */
public:
  Plus(/* args */);
  Plus();
};
 Plus:: Plus(/* args */)
{
}
 Plus:: Plus()
{
}
