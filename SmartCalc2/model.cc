#include "model.h"
namespace s21 {
std::string Model::ModelCalc(std::string &str) {
  if (!expression_.empty()) {
    expression_.clear();
  }
  Correcting(str);
  ToList(str);
  ToPolish();
  if (Calc()) {
    return "nan";
  }
  return expression_.front();
}

int Model::Correcting(std::string &str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (((str[i] == '+') || (str[i] == '-')) &&
        ((i == 0) || !((str[i - 1] >= '0') && (str[i - 1] <= '9'))) &&
        (str[i - 1] != ')') && (str[i - 1] != 'e')) {
      switch (str[i]) {
        case '-':
          str[i] = 'm';
          break;
        case '+':
          str[i] = 'p';
          break;
      }
    }
  }
  return 0;
}

int Model::Calc() {
  for (auto it = expression_.begin(); it != expression_.end(); ++it) {
    if (!(((*it)[0] >= '0') && ((*it)[0] <= '9'))) {
      if (Priority(*it) >= 5) {
        auto oper1 = it--;
        if (!(((*it)[0] >= '0') && ((*it)[0] <= '9'))) {
          if (!((*it)[0] == '-') && !(((*it)[1] >= '0') && ((*it)[1] <= '9'))) {
            return 1;
          }
        }
        (*it) = CalcUn((*it), (*oper1));
        expression_.erase(oper1);
      } else {
        auto oper1 = it--;
        auto oper2 = it--;
        if (!(((*it)[0] >= '0') && ((*it)[0] <= '9')) && (((*it)[0] != '-'))) {
          return 1;
        }
        if (!(((*oper2)[0] >= '0') && ((*oper2)[0] <= '9')) &&
            (((*oper2)[0] != '-'))) {
          return 1;
        }
        (*it) = CalcBin((*it), (*oper2), (*oper1));
        expression_.erase(oper1);
        expression_.erase(oper2);
      }
    }
  }
  return 0;
}

std::string Model::CalcUn(std::string &num, std::string &oper) {
  double number = std::stod(num);
  std::string check = "cossintanacosasinatanlnlogsqrtmp";
  switch (check.find(oper)) {
    case 0:
      return std::to_string(cos(number));
    case 3:
      return std::to_string(sin(number));
    case 6:
      return std::to_string(tan(number));
    case 9:
      return std::to_string(acos(number));
    case 13:
      return std::to_string(asin(number));
    case 17:
      return std::to_string(atan(number));
    case 21:
      return std::to_string(log(number));
    case 23:
      return std::to_string(log10(number));
    case 26:
      return std::to_string(sqrt(number));
    case 30:
      return std::to_string(number * -1);
    case 31:
      return std::to_string(number);
    default:
      return "";
  }
  return "";
}

std::string Model::CalcBin(std::string &num1, std::string &num2,
                           std::string &oper) {
  double number1 = std::stod(num1);
  double number2 = std::stod(num2);
  std::string check = "+-*/^%";
  switch (check.find(oper)) {
    case 0:
      return std::to_string(number1 + number2);
    case 1:
      return std::to_string(number1 - number2);
    case 2:
      return std::to_string(number1 * number2);
    case 3:
      return std::to_string(number1 / number2);
    case 4:
      return std::to_string(pow(number1, number2));
    case 5:
      return std::to_string(fmod(number1, number2));
    default:
      return "";
  }
  return "";
}

int Model::ToPolish() {
  std::list<std::string> inverse_expression;
  std::stack<std::string> oper;
  for (auto it = expression_.begin(); it != expression_.end(); ++it) {
    if (((*it)[0] >= '0') && ((*it)[0] <= '9')) {
      inverse_expression.push_back(*it);
    } else if ((*it)[0] == '(') {
      oper.push(*it);
    } else if ((*it)[0] == ')') {
      while ((oper.top()[0] != '(') && (!oper.empty())) {
        inverse_expression.push_back(oper.top());
        oper.pop();
      }
      oper.pop();
    } else {
      if (!oper.empty()) {
        while ((!oper.empty()) && (Priority(oper.top()) > Priority(*it))) {
          inverse_expression.push_back(oper.top());
          oper.pop();
        }
        oper.push(*it);
      } else {
        oper.push(*it);
      }
    }
  }
  while (!oper.empty()) {
    inverse_expression.push_back(oper.top());
    oper.pop();
  }
  expression_ = inverse_expression;
  return 0;
}

int Model::ToList(std::string &str) {
  std::string opers = "()*/^%+-mp";
  for (size_t i = 0; i < str.size(); ++i) {
    if (opers.find(str[i]) != opers.npos) {
      std::string buffer;
      buffer.push_back(str[i]);
      expression_.push_back(buffer);
    } else if ((str[i] >= '0') && (str[i] <= '9')) {
      std::string buffer;
      for (; ((str[i] >= '0') && (str[i] <= '9')) || (str[i] == '.') ||
             (str[i] == 'e');
           ++i) {
        if ((str[i] == 'e') && (str[i + 1] == '-')) {
          buffer.push_back(str[i]);
          ++i;
          buffer.push_back(str[i]);
        } else {
          buffer.push_back(str[i]);
        }
      }
      --i;
      expression_.push_back(buffer);
    } else {
      std::string buffer;
      for (; str[i] != '('; ++i) {
        buffer.push_back(str[i]);
      }
      --i;
      expression_.push_back(buffer);
    }
  }
  return 0;
}

int Model::Priority(const std::string &str) {
  if (str.size() == 1) {
    switch (str[0]) {
      case '(':
        return 1;
        break;
      case ')':
        return 1;
        break;
      case '+':
        return 2;
        break;
      case '-':
        return 2;
        break;
      case '*':
        return 3;
        break;
      case '/':
        return 3;
        break;
      case '^':
        return 4;
        break;
      case '%':
        return 4;
        break;
      case 'p':
        return 5;
        break;
      case 'm':
        return 5;
        break;
      default:
        return 6;
        break;
    }
  } else {
    return 6;
  }
  return 0;
}
}  // namespace s21
