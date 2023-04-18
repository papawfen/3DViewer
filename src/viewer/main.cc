#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Model model;
  Controller controller(&model);
  MainWindow w;
  w.SetController(&controller);
  w.show();
  model.addView(&w);
  model.addWidget(w.GetWidget());
  return a.exec();
}
