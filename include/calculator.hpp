#pragma once

#include <memory>
#include <cmath>

class ICalculatable
{
private:
  double value_;
public:
  virtual double Calculate(); 
  ICalculatable();//?
  explicit ICalculatable(double);
  ICalculatable(ICalculatable&);
  double getValue();
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

class atan: public ICalculatable
{
  private:
  std::unique_ptr<ICalculatable> operand_;
public:
  atan(std::unique_ptr<ICalculatable>);
  virtual double Calculate();
};

class abs: public ICalculatable
{
  private:
  std::unique_ptr<ICalculatable> operand_;
public:
  abs(std::unique_ptr<ICalculatable>);
  virtual double Calculate();
};