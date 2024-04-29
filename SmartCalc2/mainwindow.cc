#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "controller.h"

View::View(s21::Controller &cntr)
    : cntr_(&cntr), QMainWindow(nullptr), ui(new Ui::View) {
  ui->setupUi(this);
  connect(ui->B0, SIGNAL(clicked()), this, SLOT(NumberProc()));
  connect(ui->B1, SIGNAL(clicked()), this, SLOT(NumberProc()));
  connect(ui->B2, SIGNAL(clicked()), this, SLOT(NumberProc()));
  connect(ui->B3, SIGNAL(clicked()), this, SLOT(NumberProc()));
  connect(ui->B4, SIGNAL(clicked()), this, SLOT(NumberProc()));
  connect(ui->B5, SIGNAL(clicked()), this, SLOT(NumberProc()));
  connect(ui->B6, SIGNAL(clicked()), this, SLOT(NumberProc()));
  connect(ui->B7, SIGNAL(clicked()), this, SLOT(NumberProc()));
  connect(ui->B8, SIGNAL(clicked()), this, SLOT(NumberProc()));
  connect(ui->B9, SIGNAL(clicked()), this, SLOT(NumberProc()));
  connect(ui->Equel, SIGNAL(clicked()), this, SLOT(ResultProcessing()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(OperProc()));
  connect(ui->mult, SIGNAL(clicked()), this, SLOT(OperProc()));
  connect(ui->div, SIGNAL(clicked()), this, SLOT(OperProc()));
  connect(ui->pow, SIGNAL(clicked()), this, SLOT(OperProc()));
  connect(ui->mines, SIGNAL(clicked()), this, SLOT(OperPlusMinesProc()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(OperPlusMinesProc()));
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(BracketsProc()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(TrigProc()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(TrigProc()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(TrigProc()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(TrigProc()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(TrigProc()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(TrigProc()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(TrigProc()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(TrigProc()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(TrigProc()));
  connect(ui->AC, SIGNAL(clicked()), this, SLOT(ACProc()));
  connect(ui->dot, SIGNAL(clicked()), this, SLOT(DotProc()));
  connect(ui->Bexp, SIGNAL(clicked()), this, SLOT(ExpProc()));
  connect(ui->Bx, SIGNAL(clicked()), this, SLOT(XProc()));
  connect(ui->MakeGraph, SIGNAL(clicked()), this, SLOT(GraphProc()));

  //        for (auto button : ui->Number->buttons()) {
  //            connect(button, SIGNAL(clicked()), this, SLOT(NumberProc()));
  //        }

  //  ui->Graph->setInteraction(QCP::iRangeZoom, true);
  //  ui->Graph->setInteraction(QCP::iRangeDrag, true);
}

View::~View() { delete ui; }

void View::ResultProcessing() {
  QString qstr = ui->label->text();
  QString X = ui->LineX->text();
  qstr = cntr_->CalcContr(qstr, X);
  ui->label->setText(qstr);
}

void View::NumberProc() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(cntr_->NumberInput(ui->label->text(), button->text()));
}

void View::OperProc() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(cntr_->OperInput(ui->label->text(), button->text()));
}

void View::OperPlusMinesProc() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(
      cntr_->OperPlusMinesInput(ui->label->text(), button->text()));
}

void View::BracketsProc() {
  ui->label->setText(cntr_->BracketsInput(ui->label->text()));
}

void View::TrigProc() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(cntr_->TrigInput(ui->label->text(), button->text()));
}

void View::ACProc() { ui->label->clear(); }

void View::DotProc() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(cntr_->DotInput(ui->label->text(), button->text()));
}

void View::ExpProc() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(cntr_->ExpInput(ui->label->text(), button->text()));
}

void View::XProc() {
  QPushButton *button = (QPushButton *)sender();
  ui->label->setText(cntr_->XInput(ui->label->text(), button->text()));
}

void View::GraphProc() {
  QVector<double> confines;
  QString qstr = ui->label->text();
  if (qstr.size() != 0) {
    double step = 0.1;
    confines.push_back(ui->Xmin->text().toDouble());
    confines.push_back(ui->Ymin->text().toDouble());
    confines.push_back(ui->Xmax->text().toDouble());
    confines.push_back(ui->Ymax->text().toDouble());
    QVector<QVector<double>> answer = cntr_->GraphProc(qstr, confines, step);
    ui->Graph->xAxis->setRange(confines[0], confines[2]);
    ui->Graph->yAxis->setRange(confines[1], confines[3]);
    ui->Graph->clearGraphs();
    ui->Graph->addGraph();
    ui->Graph->graph(0)->setData(answer[0], answer[1]);
    ui->Graph->graph(0)->setPen(QColor(50, 50, 50, 255));
    ui->Graph->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->Graph->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssCircle, 4));
    ui->Graph->xAxis->setLabel("X");
    ui->Graph->yAxis->setLabel("Y");
    ui->Graph->replot();
  }
}
