#ifndef SRC_AFFINE_H_
#define SRC_AFFINE_H_

#include <QVector3D>
#include <QVector>
#include <cmath>
#include <iostream>

#include "dataclass.h"


class Affine {
 public:
  Affine() {}

  void AffineMoveAll();
  void AffineRotateOX();
  void AffineRotateOY();
  void AffineRotateOZ();
  void AffineScale();
};

#endif  // SRC_AFFINE_H_
