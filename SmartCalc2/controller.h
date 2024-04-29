#ifndef CPP3_SMARTCALC_V2_0_2_SRC_SMARTCALC2_CONTROLLER_H
#define CPP3_SMARTCALC_V2_0_2_SRC_SMARTCALC2_CONTROLLER_H

#include <QString>
#include <QVector>
#include <iostream>
#include <string>
#include <vector>

#include "model.h"

namespace s21 {
class Controller {
 public:
  Controller(Model &model) : model_(&model) {}
  QString CalcContr(QString qstr, QString X);
  QString NumberInput(QString qstr, QString button);
  QString OperInput(QString qstr, QString button);
  QString OperPlusMinesInput(QString qstr, QString button);
  QString BracketsInput(QString qstr);
  QString TrigInput(QString qstr, QString button);
  QString DotInput(QString qstr, QString button);
  QString ExpInput(QString qstr, QString button);
  QString XInput(QString qstr, QString button);
  QVector<QVector<double>> GraphProc(QString qstr, QVector<double> &confines,
                                     double &step);
  void СhangesToX(std::string &str, std::string &X);

 private:
  Model *model_;
};
}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_0_2_SRC_SMARTCALC2_CONTROLLER_H
