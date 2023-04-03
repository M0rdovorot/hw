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

class Plus: public ICalculatable
{
private:
  std::unique_ptr<ICalculatable> left_operand_;
  std::unique_ptr<ICalculatable> right_operand_;
public:
  Plus(std::unique_ptr<ICalculatable>, std::unique_ptr<ICalculatable>);
  virtual double Calculate();
};

class Minus: public ICalculatable
{
  private:
  std::unique_ptr<ICalculatable> left_operand_;
  std::unique_ptr<ICalculatable> right_operand_;
public:
  Minus(std::unique_ptr<ICalculatable>, std::unique_ptr<ICalculatable>);
  virtual double Calculate();
};

class Divide: public ICalculatable
{
  private:
  std::unique_ptr<ICalculatable> left_operand_;
  std::unique_ptr<ICalculatable> right_operand_;
public:
  Divide(std::unique_ptr<ICalculatable>, std::unique_ptr<ICalculatable>);
  virtual double Calculate();
};

class Atan: public ICalculatable
{
  private:
  std::unique_ptr<ICalculatable> operand_;
public:
  Atan(std::unique_ptr<ICalculatable>);
  virtual double Calculate();
};

class Abs: public ICalculatable
{
  private:
  std::unique_ptr<ICalculatable> operand_;
public:
  Abs(std::unique_ptr<ICalculatable>);
  virtual double Calculate();
};
