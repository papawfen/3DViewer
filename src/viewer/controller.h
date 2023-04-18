#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWheelEvent>

#include "model.h"

class Controller {
 public:
  explicit Controller(Model *model) : model_(model) {}
  ~Controller(){};

  void WheelEvent(QWheelEvent *event) { model_->WheelEvent(event); }
  void MouseRotation(double x, double y) { model_->MouseRotation(x, y); }
  void OpenFile(QString &path) { model_->OpenFile(path); }
  void Translate(QVector3D &offsets) { model_->Translate(offsets); }
  void Rotate(QVector3D &angles) { model_->Rotate(angles); }
  void Scale(double scale) { model_->Scale(scale); }
  void SetBackgroundColor(QColor color) { model_->SetBackgroundColor(color); }
  void SetEdgesColor(QColor color) { model_->SetEdgesColor(color); }
  void SetVerticesColor(QColor color) { model_->SetVerticesColor(color); }
  void Smooth() { model_->Smooth(); }
  void Stripple() { model_->Stripple(); }
  void ChangeThickness(double x) { model_->ChangeThickness(x); }
  void SetVerticeType(int type) { model_->SetVerticeType(type); }
  void SetVerticeSize(double size) { model_->SetVerticeSize(size); }
  void SetPerspective(bool orthogonal) { model_->SetPerspective(orthogonal); }
  void MousePressEvent(QMouseEvent *apEvent) {
    model_->MousePressEvent(apEvent);
  }

 private:
  s21::Model *model_;
};

#endif  // CONTROLLER_H
