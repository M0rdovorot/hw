#pragma once

#include "interface.hpp"

class Number : public ICalculatable {
 public:
  virtual double Calculate() override;
  double getValue() const;
  explicit Number(double);
  explicit Number(int);
 private:
  double value_;
};

class Plus : public ICalculatable {
 public:
  explicit Plus(std::unique_ptr<ICalculatable>, std::unique_ptr<ICalculatable>);
  virtual double Calculate() override;
 private:
  std::unique_ptr<ICalculatable> left_operand_;
  std::unique_ptr<ICalculatable> right_operand_;
};

class Minus : public ICalculatable {
 public:
  explicit Minus(std::unique_ptr<ICalculatable>, std::unique_ptr<ICalculatable>);
  virtual double Calculate() override;
 private:
  std::unique_ptr<ICalculatable> left_operand_;
  std::unique_ptr<ICalculatable> right_operand_;
};

class UnaryMinus : public ICalculatable {
 public:
  explicit UnaryMinus(std::unique_ptr<ICalculatable>);
  virtual double Calculate() override;
 private:
  std::unique_ptr<ICalculatable> operand_;
};

class Divide : public ICalculatable {
 public:
  explicit Divide(std::unique_ptr<ICalculatable>, std::unique_ptr<ICalculatable>);
  virtual double Calculate() override;
 private:
  std::unique_ptr<ICalculatable> left_operand_;
  std::unique_ptr<ICalculatable> right_operand_;
};

class Atan : public ICalculatable {
 public:
  explicit Atan(std::unique_ptr<ICalculatable>);
  virtual double Calculate() override;
 private:
  std::unique_ptr<ICalculatable> operand_;
};

class Abs : public ICalculatable {
 public:
  explicit Abs(std::unique_ptr<ICalculatable>);
  virtual double Calculate() override;
 private:
  std::unique_ptr<ICalculatable> operand_;
};
