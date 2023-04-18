#include "affine.h"

void Affine::AffineMoveAll() {
  for (std::size_t i = 0;
       i < (DataClass::getDataClass()->getVertex_count() * 3); i += 3) {
    DataClass::getDataClass()->getVertex_data()[i] +=
        DataClass::getDataClass()->getOffsets().x();
    DataClass::getDataClass()->getVertex_data()[i + 1] +=
        DataClass::getDataClass()->getOffsets().y();
    DataClass::getDataClass()->getVertex_data()[i + 2] +=
        DataClass::getDataClass()->getOffsets().z();
  }
}

void Affine::AffineRotateOX() {
  for (int i = 0; i < (DataClass::getDataClass()->getVertex_count() * 3);
       i += 3) {
    double temp_y = DataClass::getDataClass()->getVertex_data()[i + 1];
    double temp_z = DataClass::getDataClass()->getVertex_data()[i + 2];
    DataClass::getDataClass()->getVertex_data()[i + 1] =
        temp_y * cos(DataClass::getDataClass()->getAngles().x()) -
        temp_z * sin(DataClass::getDataClass()->getAngles().x());
    DataClass::getDataClass()->getVertex_data()[i + 2] =
        temp_y * sin(DataClass::getDataClass()->getAngles().x()) +
        temp_z * cos(DataClass::getDataClass()->getAngles().x());
  }
}

void Affine::AffineRotateOY() {
  for (int i = 0; i < (DataClass::getDataClass()->getVertex_count() * 3);
       i += 3) {
    double temp_x = DataClass::getDataClass()->getVertex_data()[i];
    double temp_z = DataClass::getDataClass()->getVertex_data()[i + 2];
    DataClass::getDataClass()->getVertex_data()[i] =
        temp_x * cos(DataClass::getDataClass()->getAngles().y()) +
        temp_z * sin(DataClass::getDataClass()->getAngles().y());
    DataClass::getDataClass()->getVertex_data()[i + 2] =
        -temp_x * sin(DataClass::getDataClass()->getAngles().y()) +
        temp_z * cos(DataClass::getDataClass()->getAngles().y());
  }
}

void Affine::AffineRotateOZ() {
  for (int i = 0; i < (DataClass::getDataClass()->getVertex_count() * 3);
       i += 3) {
    double temp_x = DataClass::getDataClass()->getVertex_data()[i];
    double temp_y = DataClass::getDataClass()->getVertex_data()[i + 1];
    DataClass::getDataClass()->getVertex_data()[i] =
        temp_x * cos(DataClass::getDataClass()->getAngles().z()) -
        temp_y * sin(DataClass::getDataClass()->getAngles().z());
    DataClass::getDataClass()->getVertex_data()[i + 1] =
        temp_x * sin(DataClass::getDataClass()->getAngles().z()) +
        temp_y * cos(DataClass::getDataClass()->getAngles().z());
  }
}

void Affine::AffineScale() {
  for (int i = 0; i < (DataClass::getDataClass()->getVertex_count() * 3); ++i) {
    DataClass::getDataClass()->getVertex_data()[i] *=
        DataClass::getDataClass()->getScale();
  }
}
