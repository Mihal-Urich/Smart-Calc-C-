#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller cntr(model);
  View w(cntr);
  w.show();
  return a.exec();
}
