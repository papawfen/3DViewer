#ifndef VIEWER_MODEL_H_
#define VIEWER_MODEL_H_

#include <QColor>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>
#include <QWheelEvent>
#include <QtOpenGL>
#include <memory>

#include "affine.h"
#include "dataclass.h"
#include "parser.h"
#define GL_SILENCE_DEPRECATION

class ObserverView {
 public:
  virtual void UpdateCounts(int x, int y) = 0;
  virtual void LoadLineType(bool type) = 0;
  virtual void LoadPerspective(bool type) = 0;
  virtual void LoadVertexType(int type) = 0;
};

class ObserverWidget {
 public:
  virtual void Update() = 0;
};

class Observable {
 public:
  void addView(ObserverView *observer) {
    view_ = observer;
    LoadSettings();
  }
  void addWidget(ObserverWidget *observer) { widget_ = observer; }
  void NotifyUpdate() { widget_->Update(); }
  void NotifyUpdateModelInfo(int x, int y) { view_->UpdateCounts(x, y); }
  void NotifyLoadLineType(bool type) { view_->LoadLineType(type); };
  void NotifyLoadPerspective(bool type) { view_->LoadPerspective(type); };
  void NotifyLoadVertexType(int type) { view_->LoadVertexType(type); };

 private:
  void LoadSettings() {
    NotifyLoadLineType(DataClass::getDataClass()->getLine_type());
    NotifyLoadPerspective(DataClass::getDataClass()->getIsOrthogonal());
    NotifyLoadVertexType(DataClass::getDataClass()->getVertice_type());
  }
  ObserverView *view_;
  ObserverWidget *widget_;
};

class Renderer : public QOpenGLFunctions {
 public:
  Renderer(){};

  ~Renderer(){};

  void Rotate() {
    Center();
    DataClass::getDataClass()->getAngles().setX(
        DataClass::getDataClass()->getAngles().x() * M_PI / 180);
    DataClass::getDataClass()->getAngles().setY(
        DataClass::getDataClass()->getAngles().y() * M_PI / 180);
    DataClass::getDataClass()->getAngles().setZ(
        DataClass::getDataClass()->getAngles().z() * M_PI / 180);
    affine.AffineRotateOY();
    affine.AffineRotateOX();
    affine.AffineRotateOZ();
    affine.AffineMoveAll();
  }

  void Scale() {
    Center();
    affine.AffineScale();
    Center();
    affine.AffineMoveAll();
  }

  void Translate() {
    DataClass::getDataClass()->getPositions().setX(
        DataClass::getDataClass()->getOffsets().x() +
        DataClass::getDataClass()->getPositions().x());
    DataClass::getDataClass()->getPositions().setY(
        DataClass::getDataClass()->getOffsets().y() +
        DataClass::getDataClass()->getPositions().y());
    DataClass::getDataClass()->getPositions().setZ(
        DataClass::getDataClass()->getOffsets().z() +
        DataClass::getDataClass()->getPositions().z());
    affine.AffineMoveAll();
  }

  void Center() {
    DataClass::getDataClass()->setPositions(
        {-DataClass::getDataClass()->getPositions().x(),
         -DataClass::getDataClass()->getPositions().y(),
         -DataClass::getDataClass()->getPositions().z()});
    affine.AffineMoveAll();
    DataClass::getDataClass()->setPositions(
        {-DataClass::getDataClass()->getPositions().x(),
         -DataClass::getDataClass()->getPositions().y(),
         -DataClass::getDataClass()->getPositions().z()});
  }

 private:
  Affine affine;
};

class Model : public Observable {
 public:
  Model(){};
  ~Model(){};

  void OpenFile(QString &path) {
    DataClass::getDataClass()->setVertex_count(0);
    DataClass::getDataClass()->setEdges_array_count(0);
    DataClass::getDataClass()->getPositions() = {.0, .0, .0};
    DataClass::getDataClass()->getOffsets() = {.0, .0, .0};
    DataClass::getDataClass()->getAngles() = {.0, .0, .0};
    DataClass::getDataClass()->setScale(1.0);
    DataClass::getDataClass()->getEdges_data().clear();
    DataClass::getDataClass()->getVertex_data().clear();

    parser_->GetVertexesAndFacetsCount(path);
    parser_->GetVertexesArray(path);
    parser_->GetEdgeArray(path);
    parser_->GetRealEdgeCount();

    NotifyUpdate();
    NotifyUpdateModelInfo(DataClass::getDataClass()->getEdges_count(),
                          DataClass::getDataClass()->getVertex_count());
  }
  void WheelEvent(QWheelEvent *event) {
    double scale = 1.1;
    if (event->angleDelta().y() > 0) {
      DataClass::getDataClass()->setScale(scale);
      renderer_->Scale();
    } else if (event->angleDelta().y() < 0) {
      DataClass::getDataClass()->setScale(scale - 0.2);
      renderer_->Scale();
    }
    NotifyUpdate();
  }
  void MouseRotation(double x, double y) {
    DataClass::getDataClass()->getAngles().setX(x > .0 ? fmod(x, 2. * M_PI)
                                                       : fmod(x, -2. * M_PI));
    DataClass::getDataClass()->getAngles().setY(y > .0 ? fmod(y, 2. * M_PI)
                                                       : fmod(y, -2. * M_PI));
    renderer_->Rotate();
    NotifyUpdate();
  }
  void SetBackgroundColor(QColor &color) {
    DataClass::getDataClass()->setBackground_color(color);
    NotifyUpdate();
  }
  void SetEdgesColor(QColor &color) {
    DataClass::getDataClass()->setEdges_color(color);
    NotifyUpdate();
  }
  void SetVerticesColor(QColor &color) {
    DataClass::getDataClass()->setVertices_color(color);
    NotifyUpdate();
  }
  void MousePressEvent(QMouseEvent *apEvent) {
    DataClass::getDataClass()->setPosition(apEvent->pos());
  }
  void Translate(QVector3D &offsets) {
    DataClass::getDataClass()->setOffsets(offsets);
    renderer_->Translate();
    NotifyUpdate();
  }
  void Rotate(QVector3D &angles) {
    DataClass::getDataClass()->setAngles(angles);
    renderer_->Rotate();
    NotifyUpdate();
  }
  void Scale(double scale) {
    DataClass::getDataClass()->setScale(scale);
    renderer_->Scale();
    NotifyUpdate();
  }
  void Smooth() {
    DataClass::getDataClass()->setLine_type(false);
    NotifyUpdate();
  }
  void Stripple() {
    DataClass::getDataClass()->setLine_type(true);

    NotifyUpdate();
  }
  void ChangeThickness(double x) {
    DataClass::getDataClass()->setLine_thickness(x);
    NotifyUpdate();
  }
  void SetVerticeType(int type) {
    DataClass::getDataClass()->setVertice_type(type);
    NotifyUpdate();
  }
  void SetVerticeSize(double size) {
    DataClass::getDataClass()->setVertices_size(size);
    NotifyUpdate();
  }
  void SetPerspective(bool orthogonal) {
    DataClass::getDataClass()->setIsOrthogonal(orthogonal);
    NotifyUpdate();
  }

 private:
  std::unique_ptr<Parser> parser_ = std::make_unique<Parser>();
  std::unique_ptr<Renderer> renderer_ = std::make_unique<Renderer>();
};

#endif  // VIEWER_MODEL_H_