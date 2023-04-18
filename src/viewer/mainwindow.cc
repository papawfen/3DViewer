#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::SetController(Controller *controller) {
  controller_ = controller;
  ui->openGLWidget->SetController(controller_);
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  controller_->WheelEvent(event);
}

void MainWindow::mouse_rotation(double x, double y) {
  controller_->MouseRotation(x, y);
}

void MainWindow::on_pushButton_clicked() {
  controller_->SetBackgroundColor(
      QColorDialog::getColor(Qt::black, this, "Choose Background Color"));
}

void MainWindow::on_pushButton_2_clicked() {
  controller_->SetEdgesColor(
      QColorDialog::getColor(Qt::black, this, "Choose Background Color"));
}

void MainWindow::on_pushButton_3_clicked() {
  controller_->SetVerticesColor(
      QColorDialog::getColor(Qt::black, this, "Choose Background Color"));
}

void MainWindow::UpdateCounts(int edges_count, int vertex_count) {
  ui->edges->setText("Edges count:  " + QString::number(edges_count) + " ");
  ui->vertices->setText("Vertices count:  " + QString::number(vertex_count) +
                        " ");
}

void MainWindow::on_actionopen_triggered() {
  Qpath = QFileDialog::getOpenFileName(this, NULL, "/~", "OBJ (*.obj)");
  if (!Qpath.isNull()) {
    controller_->OpenFile(Qpath);
    int namePos = Qpath.lastIndexOf('/') + 1;
    QString name, edges, vertices;
    name = "File name:  " + Qpath.sliced(namePos) + " ";
    ui->file_name->setText(name);
  }
}

void MainWindow::on_startTranslate_clicked() {
  QVector3D offsets = {static_cast<float>(ui->ox->text().toDouble()),
                       static_cast<float>(ui->oy->text().toDouble()),
                       static_cast<float>(ui->oz->text().toDouble())};
  controller_->Translate(offsets);
}

void MainWindow::on_startRotate_clicked() {
  QVector3D angles = {static_cast<float>(ui->rot_ox->text().toDouble()),
                      static_cast<float>(ui->rot_oy->text().toDouble()),
                      static_cast<float>(ui->rot_oz->text().toDouble())};
  controller_->Rotate(angles);
}

void MainWindow::on_scale_model_clicked() {
  if (ui->scale->text().toDouble()) {
    controller_->Scale(ui->scale->text().toDouble());
  }
}

void MainWindow::on_smooth_button_clicked(bool checked) {
  if (checked) {
    controller_->Smooth();
  }
}

void MainWindow::on_stipple_button_clicked(bool checked) {
  if (checked) {
    controller_->Stripple();
  }
}

void MainWindow::on_thickness_textChanged(const QString &arg1) {
  if (!arg1.isEmpty()) {
    controller_->ChangeThickness(ui->thickness->text().toDouble());
  }
}

void MainWindow::on_vertice_none_clicked(bool checked) {
  if (checked) {
    controller_->SetVerticeType(0);
  }
}

void MainWindow::on_vertice_circle_clicked(bool checked) {
  if (checked) {
    controller_->SetVerticeType(1);
  }
}

void MainWindow::on_vertice_square_clicked(bool checked) {
  if (checked) {
    controller_->SetVerticeType(2);
  }
}

void MainWindow::on_vertice_size_textChanged(const QString &arg1) {
  if (!arg1.isEmpty()) {
    controller_->SetVerticeSize(ui->vertice_size->text().toDouble());
  }
}

void MainWindow::on_orthogonal_button_clicked(bool checked) {
  if (checked) {
    controller_->SetPerspective(true);
  }
}

void MainWindow::on_perspective_button_clicked(bool checked) {
  if (checked) {
    controller_->SetPerspective(false);
  }
}

ObserverWidget *MainWindow::GetWidget() { return ui->openGLWidget; }

void MainWindow::LoadLineType(bool type) {
  if (!type) {
    ui->smooth_button->setChecked(true);
  } else {
    ui->stipple_button->setChecked(true);
  }
}

void MainWindow::LoadPerspective(bool type) {
  if (type) {
    ui->orthogonal_button->setChecked(true);
  } else {
    ui->perspective_button->setChecked(true);
  }
}

void MainWindow::LoadVertexType(int type) {
  if (type == 0) {
    ui->vertice_none->setChecked(true);
  } else if (type == 1) {
    ui->vertice_circle->setChecked(true);
  } else {
    ui->vertice_square->setChecked(true);
  }
}

void MainWindow::saveGifFrame() {
  time++;
  *frame = ui->openGLWidget->grabFramebuffer();
  *frame = frame->scaled(640, 480);
  gif->addFrame(*frame, 100);
  if (time == 50) {
    timer->stop();
    gifSavePath = NULL;
    gifSavePath = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
    if (!gifSavePath.isNull()) gif->save(gifSavePath);
  }
}

void MainWindow::on_actionSave_as_Gif_triggered() {
  gif = new QGifImage;
  frame = new QImage;
  timer = new QTimer(this);
  time = 0;
  connect(timer, SIGNAL(timeout()), this, SLOT(saveGifFrame()));
  timer->start(100);
}

void MainWindow::on_actionSave_Image_triggered() {
  QImage frame = ui->openGLWidget->grabFramebuffer();
  QString imgSavePath =
      QFileDialog::getSaveFileName(this, NULL, NULL, "BMP JPEG (*.bmp *.jpeg)");
  frame.save(imgSavePath);
}

