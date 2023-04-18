#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>

#include "controller.h"
#include "dataclass.h"
#include "myopenglwidjet.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public ObserverView {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void SetController(s21::Controller *controller);
  void mouse_rotation(double x, double y);
  void wheelEvent(QWheelEvent *event) override;
  void UpdateCounts(int edges_count, int vertex_count) override;
  void LoadLineType(bool type) override;
  void LoadPerspective(bool type) override;
  void LoadVertexType(int type) override;
  ObserverWidget *GetWidget();
  
 private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_3_clicked();

  void on_actionopen_triggered();

  void on_startTranslate_clicked();

  void on_startRotate_clicked();

  void on_scale_model_clicked();

  void on_smooth_button_clicked(bool checked);

  void on_stipple_button_clicked(bool checked);

  void on_thickness_textChanged(const QString &arg1);

  void on_vertice_none_clicked(bool checked);

  void on_vertice_circle_clicked(bool checked);

  void on_vertice_square_clicked(bool checked);

  void on_vertice_size_textChanged(const QString &arg1);

  void on_orthogonal_button_clicked(bool checked);

  void on_perspective_button_clicked(bool checked);

  void saveGifFrame();

  void on_actionSave_as_Gif_triggered();

  void on_actionSave_Image_triggered();

 private:
  Ui::MainWindow *ui;
  QString Qpath = NULL;
  QSettings *settings;
  s21::Controller *controller_;
  QGifImage *gif;
  QImage *frame;
  QTimer *timer;
  QString gifSavePath;
  int time;
};

#endif  // MAINWINDOW_H
