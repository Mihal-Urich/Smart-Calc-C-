#include "controller.h"

namespace s21 {
QString Controller::CalcContr(QString qstr, QString X) {
  std::string str = qstr.toStdString();
  if ((str.find("nan") != str.npos) || (str.find("inf") != str.npos)) {
    return "nan";
  }
  std::string StdX = X.toStdString();
  if (str.find("x") != str.npos) {
    if (StdX.size() != 0) {
      СhangesToX(str, StdX);
    } else {
      return "nan";
    }
  }
  std::string answer = model_->ModelCalc(str);
  if (answer.find(".") != answer.npos) {
    while (answer.back() == '0') {
      answer.pop_back();
    }
    if (answer.back() == '.') {
      answer.pop_back();
    }
  }
  return QString::fromStdString(answer);
}

void Controller::СhangesToX(std::string &str, std::string &X) {
  std::string back;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] != 'x') {
      back += str[i];
    } else {
      back += X;
    }
  }
  str = back;
}

QString Controller::NumberInput(QString qstr, QString button) {
  if (qstr.size() == 0) {
    return qstr + button;
  }
  QChar last = qstr[qstr.size() - 1];
  if (last == 'x') {
    return qstr;
  }
  return qstr + button;
}

QString Controller::OperInput(QString qstr, QString button) {
  if (qstr.size() == 0) {
    return qstr;
  }
  QChar last = qstr[qstr.size() - 1];
  if ((last == 'e') || (last == '(')) {
    return qstr;
  }
  if ((last == ')') || (last == 'x') || ((last >= '0') && (last <= '9'))) {
    return qstr + button;
  } else {
    if ((last == '+') || (last == '-')) {
      return qstr;
    } else {
      qstr[qstr.size() - 1] = button[0];
      return qstr;
    }
  }
}

QString Controller::OperPlusMinesInput(QString qstr, QString button) {
  if ((qstr.size() == 0) || (qstr.size() == 1)) {
    return qstr + button;
  }
  QChar last = qstr[qstr.size() - 1];
  QChar prelast = qstr[qstr.size() - 2];
  if (((last == '+') || (last == '-')) &&
      ((prelast == '+') || (prelast == '-'))) {
    return qstr;
  } else {
    return qstr + button;
  }
}

QString Controller::BracketsInput(QString qstr) {
  if (qstr.size() == 0) {
    return qstr + "(";
  }
  size_t left = qstr.count("(");
  size_t right = qstr.count(")");
  QChar last = qstr[qstr.size() - 1];
  if (last == '.') {
    return qstr;
  }
  if ((left > right) &&
      (((last >= '0') && (last <= '9')) || (last == ')') || (last == 'x'))) {
    return qstr + ")";
  } else {
    if (((last >= '0') && (last <= '9')) || (last == ')') || (last == 'x')) {
      return qstr + "*(";
    } else {
      return qstr + "(";
    }
  }
}

QString Controller::TrigInput(QString qstr, QString button) {
  if (qstr.size() == 0) {
    return qstr + button + "(";
  } else {
    QChar last = qstr[qstr.size() - 1];
    if ((last >= '0') && (last <= '9')) {
      return qstr + "*" + button + "(";
    } else {
      return qstr + button + "(";
    }
  }
}

QString Controller::DotInput(QString qstr, QString button) {
  if (qstr.size() == 0) {
    return "0.";
  } else {
    QChar last = qstr[qstr.size() - 1];
    if ((last >= '0') && (last <= '9')) {
      for (size_t i = qstr.size() - 1;
           (i > 0) && (((qstr[i] >= '0') && (qstr[i] <= '9')) ||
                       (qstr[i] == '.') || (qstr[i] == 'e'));
           --i) {
        if ((qstr[i] == '.') || (qstr[i] == 'e')) {
          return qstr;
        }
      }
      return qstr + ".";
    } else if (last == ')') {
      return qstr + "*0.";
    }
  }
  return qstr;
}

QString Controller::ExpInput(QString qstr, QString button) {
  if (qstr.size() == 0) {
    return qstr;
  } else {
    QChar last = qstr[qstr.size() - 1];
    if ((last >= '0') && (last <= '9')) {
      for (size_t i = qstr.size() - 1;
           (i > 0) && (((qstr[i] >= '0') && (qstr[i] <= '9')) ||
                       (qstr[i] == 'e') || (qstr[i] == '.'));
           --i) {
        if (qstr[i] == 'e') {
          return qstr;
        }
      }
      return qstr + "e";
    }
  }
  return qstr;
}

QString Controller::XInput(QString qstr, QString button) {
  if (qstr.size() == 0) {
    return qstr + "x";
  }
  QChar last = qstr[qstr.size() - 1];
  if (last == ')') {
    return qstr + "*x";
  }
  if (last == 'x') {
    return qstr;
  }
  if (!((last >= '0') && (last <= '9')) && (last != '.') && (last != 'e')) {
    return qstr + "x";
  }
  return qstr;
}

QVector<QVector<double>> Controller::GraphProc(QString qstr,
                                               QVector<double> &confines,
                                               double &step) {
  QVector<QVector<double>> answer(2);
  for (double i = confines[0]; i < confines[2]; i += step) {
    answer[0].push_back(i);
    answer[1].push_back(CalcContr(qstr, QString::number(i, 'g', 6)).toDouble());
  }
  return answer;
}

}  // namespace s21
