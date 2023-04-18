#ifndef MYOPENGLWIDJET_H
#define MYOPENGLWIDJET_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>
#include <QWheelEvent>
#include <QtOpenGL>

#include "controller.h"
#include "dataclass.h"

class glView : public QOpenGLWidget,
               public s21::ObserverWidget,
               public QOpenGLFunctions {
  Q_OBJECT

 public:
  glView(QWidget *parent = nullptr);
  ~glView();
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void changeProjection();
  void Update() override;
  void SetController(Controller *controller);

 private:
  Controller *controller_;
};

#endif  // MYOPENGLWIDJET_H
