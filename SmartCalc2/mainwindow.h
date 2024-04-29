#ifndef CPP3_SMARTCALC_V2_0_2_SRC_SMARTCALC2_MAINWINDOW_H
#define CPP3_SMARTCALC_V2_0_2_SRC_SMARTCALC2_MAINWINDOW_H

#include <QMainWindow>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(s21::Controller &cntr);
  ~View();

 private slots:
  void ResultProcessing();
  void NumberProc();
  void OperProc();
  void OperPlusMinesProc();
  void BracketsProc();
  void TrigProc();
  void ACProc();
  void DotProc();
  void ExpProc();
  void XProc();
  void GraphProc();

 private:
  s21::Controller *cntr_;
  Ui::View *ui;
};
#endif  // CPP3_SMARTCALC_V2_0_2_SRC_SMARTCALC2_MAINWINDOW_H
