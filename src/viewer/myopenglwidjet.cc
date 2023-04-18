#include "myopenglwidjet.h"

glView::glView(QWidget *parent) : QOpenGLWidget(parent) {
  setGeometry(400, 200, 800, 600);
}

glView::~glView() {}

void glView::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslated(0., 0., -2.);
}

void glView::resizeGL(int w, int h) {}

void glView::changeProjection() {
  if (DataClass::getDataClass()->getIsOrthogonal()) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double max = (DataClass::getDataClass()->getSizes().x_max * 1.5);
    glOrtho(-max, max, -max, max, -99999999999, 99999999999);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double max = (DataClass::getDataClass()->getSizes().x_max * 1.5);
    glOrtho(-max, max, -max, max, -99999999999, 99999999999);
    float fov = 5.0 * M_PI / 180;
    float heapHeight = 580 / (2 * tan(fov / 2));
    float far = 100000;
    glFrustum(-510, 510, -580, 580, heapHeight, far);
  }
}

void glView::paintGL() {
  if (DataClass::getDataClass()->getIsProjection()) changeProjection();
  DataClass::getDataClass()->getBackground_color().getRgbF(
      DataClass::getDataClass()->getBackground_red(),
      DataClass::getDataClass()->getBackgroundGreen(),
      DataClass::getDataClass()->getBackgroundBlue(),
      DataClass::getDataClass()->getBackgroundAlpha());

  glClearColor(*DataClass::getDataClass()->getBackground_red(),
               *DataClass::getDataClass()->getBackgroundGreen(),
               *DataClass::getDataClass()->getBackgroundBlue(),
               *DataClass::getDataClass()->getBackgroundAlpha());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glVertexPointer(3, GL_DOUBLE, 0,
                  DataClass::getDataClass()->getVertex_data().data());
  glEnableClientState(GL_VERTEX_ARRAY);
  if (DataClass::getDataClass()->getVertice_type() != 0) {
    if (DataClass::getDataClass()->getVertice_type() == 1)
      glEnable(GL_POINT_SMOOTH);
    else
      glDisable(GL_POINT_SMOOTH);
    glPointSize(DataClass::getDataClass()->getVertices_size());
    DataClass::getDataClass()->getVertices_color().getRgbF(
        DataClass::getDataClass()->getVertice_red(),
        DataClass::getDataClass()->getVertice_green(),
        DataClass::getDataClass()->getVertice_blue());
    glColor3d(*DataClass::getDataClass()->getVertice_red(),
              *DataClass::getDataClass()->getVertice_green(),
              *DataClass::getDataClass()->getVertice_blue());
    glDrawArrays(GL_POINTS, 0,
                 DataClass::getDataClass()->getVertex_count());
  }
  DataClass::getDataClass()->getEdges_color().getRgbF(
      DataClass::getDataClass()->getEdge_red(),
      DataClass::getDataClass()->getEdge_green(),
      DataClass::getDataClass()->getEdge_blue());
  glColor3d(*DataClass::getDataClass()->getEdge_red(),
            *DataClass::getDataClass()->getEdge_green(),
            *DataClass::getDataClass()->getEdge_blue());
  glLineWidth(DataClass::getDataClass()->getLine_thickness());
  glLineStipple(1, 0x3333);
  if (DataClass::getDataClass()->getLine_type())
    glEnable(GL_LINE_STIPPLE);
  else
    glDisable(GL_LINE_STIPPLE);

  glDrawElements(
      GL_LINES, DataClass::getDataClass()->getEdges_array_count(),
      GL_UNSIGNED_INT, DataClass::getDataClass()->getEdges_data().data());
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::mousePressEvent(QMouseEvent *apEvent) {
  controller_->MousePressEvent(apEvent);
}

void glView::mouseMoveEvent(QMouseEvent *apEvent) {
  double xMouseRot = (0.001 / M_PI *
                          (apEvent->pos().y() -
                           DataClass::getDataClass()->position().y()) +
                      DataClass::getDataClass()->getAngles().x());
  double yMouseRot = (0.001 / M_PI *
                          (apEvent->pos().x() -
                           DataClass::getDataClass()->position().x()) +
                      DataClass::getDataClass()->getAngles().y());
  controller_->MouseRotation(xMouseRot * 10, yMouseRot * 10);
}

void glView::Update() { update(); }

void glView::SetController(Controller *controller) {
  controller_ = controller;
}
