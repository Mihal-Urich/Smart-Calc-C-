#ifndef CPP3_SMARTCALC_V2_0_2_SRC_SMARTCALC2_MODEL_H_
#define CPP3_SMARTCALC_V2_0_2_SRC_SMARTCALC2_MODEL_H_

#include <cmath>
#include <iostream>
#include <list>
#include <stack>
#include <string>
#include <vector>
namespace s21 {
class Model {
 public:
  std::string ModelCalc(std::string &str);

 private:
  int Correcting(std::string &str);
  int ToList(std::string &str);
  int ToPolish();
  int Calc();
  int Priority(const std::string &str);
  std::string CalcUn(std::string &num, std::string &oper);
  std::string CalcBin(std::string &num1, std::string &num2, std::string &oper);

  std::list<std::string> expression_;
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_0_2_SRC_SMARTCALC2_MODEL_H_
