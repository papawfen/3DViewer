#ifndef DATACLASS_H_
#define DATACLASS_H_

#include <QColor>
#include <QSettings>
#include <QVector3D>

struct min_max_t {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
};

class DataClass;

class SingletonDestroyer {
 public:
  SingletonDestroyer(DataClass * = 0);
  ~SingletonDestroyer();
  void SetSingleton(DataClass *s);

 private:
  DataClass *singleton_;
};

class DataClass {
 public:
  static DataClass *getDataClass() {
    if (!data_class) {
      data_class = new DataClass;
      destroyer.SetSingleton(data_class);
      data_class->memento = new Memento();
      data_class->memento->settings = new QSettings("vuwer", "3DViewer");
      data_class->memento->SaveData();
    }
    return data_class;
  }

  class Memento {
    friend class DataClass;

   public:
    Memento() {}
    ~Memento() {}
    void LoadData();
    void SaveData();

   private:
    QSettings *settings;
    QColor mem_vertices_color;
    QColor mem_background_color;
    QColor mem_edges_color;
    bool mem_line_type;
    double mem_line_thickness;
    int mem_vertice_type;
    double mem_vertices_size;
    bool mem_projection_type;
  };

  QVector<double> &getVertex_data();
  void setVertex_data(QVector<double> &newVertex_data);
  QVector<int> &getEdges_data();
  void setEdges_data(QVector<int> &newEdges_data);
  int getVertex_count();
  void setVertex_count(int newVertex_count);
  int getEdges_count();
  void setEdges_count(int newEdges_count);
  int getEdges_array_count();
  void setEdges_array_count(int newEdges_array_count);
  double getScale();
  void setScale(double newScale);
  QVector3D &getPositions();
  void setPositions(QVector3D newPositions);
  QVector3D &getOffsets();
  void setOffsets(QVector3D &newOffsets);
  QVector3D &getAngles();
  void setAngles(QVector3D &newAngles);
  QColor &getBackground_color();
  void setBackground_color(QColor &newBackground_color);
  float *getBackground_red();
  void setBackground_red(float newBackground_red);
  float *getBackgroundGreen();
  void setBackgroundGreen(float newBackgroundGreen);
  float *getBackgroundBlue();
  void setBackgroundBlue(float newBackgroundBlue);
  float *getBackgroundAlpha();
  void setBackgroundAlpha(float newBackgroundAlpha);
  QColor &getEdges_color();
  void setEdges_color(QColor &newEdges_color);
  float *getEdge_red();
  void setEdge_red(float newEdge_red);
  float *getEdge_green();
  void setEdge_green(float newEdge_green);
  float *getEdge_blue();
  void setEdge_blue(float newEdge_blue);
  QColor &getVertices_color();
  void setVertices_color(QColor &newVertices_color);
  float *getVertice_red();
  void setVertice_red(float newVertice_red);
  float *getVertice_green();
  void setVertice_green(float newVertice_green);
  float *getVertice_blue();
  void setVertice_blue(float newVertice_blue);
  QPoint position();
  void setPosition(QPoint newPosition);
  double getTranslated_z();
  void setTranslated_z(double newTranslated_z);
  std::size_t getCount();
  void setCount(std::size_t newCount);
  double getAngle();
  void setAngle(double newAngle);
  QVector3D &getAxis();
  void setAxis(QVector3D &newAxis);
  DataClass *getData_class();
  void setData_class(DataClass *newData_class);
  bool getIsopen();
  void setIsopen(bool newIsopen);
  bool getLine_type();
  void setLine_type(bool newLine_type);
  double getLine_thickness();
  void setLine_thickness(double newLine_thickness);
  int getVertice_type();
  void setVertice_type(int newVertice_type);
  double getVertices_size();
  void setVertices_size(double newVertices_size);
  bool getIsOrthogonal();
  void setIsOrthogonal(bool newIsOrthogonal);
  bool getIsProjection();
  void setIsProjection(bool newIsProjection);

  min_max_t &getSizes();
  void setSizes(min_max_t &newSizes);

 protected:
  DataClass() {}
  DataClass(DataClass &other);
  DataClass(DataClass &&other);
  void operator=(DataClass &other);

  ~DataClass() {
    memento->LoadData();
    delete memento;
  }

  friend class SingletonDestroyer;

 private:
  min_max_t sizes;
  QVector<double> vertex_data;
  QVector<int> edges_data;
  int vertex_count{0};
  int edges_count{0};
  int edges_array_count{0};

  double scale{1.0};
  QVector3D positions = {.0, .0, .0};
  QVector3D offsets = {.0, .0, .0};
  QVector3D angles = {.0, .0, .0};

  QColor background_color = Qt::black;
  float background_red, backgroundGreen, backgroundBlue, backgroundAlpha;
  QColor edges_color = Qt::green;
  float edge_red, edge_green, edge_blue;
  QColor vertices_color = Qt::red;
  float vertice_red, vertice_green, vertice_blue;

  QPoint m_position;
  std::size_t count;
  double translated_z = .0;
  double angle;
  QVector3D axis;

  static DataClass *data_class;
  Memento *memento;
  static SingletonDestroyer destroyer;

  bool isopen = false;
  bool line_type = true;
  double line_thickness = 1;
  int vertice_type = 1;
  double vertices_size = 1;
  bool isOrthogonal = true;
  bool isProjection = true;
};

inline SingletonDestroyer DataClass::destroyer;

inline DataClass *DataClass::data_class = 0;

inline QVector<double> &DataClass::getVertex_data() { return vertex_data; }

inline void DataClass::setVertex_data(QVector<double> &newVertex_data) {
  vertex_data = newVertex_data;
}

inline QVector<int> &DataClass::getEdges_data() { return edges_data; }

inline void DataClass::setEdges_data(QVector<int> &newEdges_data) {
  edges_data = newEdges_data;
}

inline int DataClass::getVertex_count() { return vertex_count; }

inline void DataClass::setVertex_count(int newVertex_count) {
  vertex_count = newVertex_count;
}

inline int DataClass::getEdges_count() { return edges_count; }

inline void DataClass::setEdges_count(int newEdges_count) {
  edges_count = newEdges_count;
}

inline int DataClass::getEdges_array_count() { return edges_array_count; }

inline void DataClass::setEdges_array_count(int newEdges_array_count) {
  edges_array_count = newEdges_array_count;
}

inline double DataClass::getScale() { return scale; }

inline void DataClass::setScale(double newScale) { scale = newScale; }

inline QVector3D &DataClass::getPositions() { return positions; }

inline void DataClass::setPositions(QVector3D newPositions) {
  positions = newPositions;
}

inline QVector3D &DataClass::getOffsets() { return offsets; }

inline void DataClass::setOffsets(QVector3D &newOffsets) {
  offsets = newOffsets;
}

inline QVector3D &DataClass::getAngles() { return angles; }

inline void DataClass::setAngles(QVector3D &newAngles) { angles = newAngles; }

inline QColor &DataClass::getBackground_color() { return background_color; }

inline void DataClass::setBackground_color(QColor &newBackground_color) {
  background_color = newBackground_color;
}

inline float *DataClass::getBackground_red() { return &background_red; }

inline void DataClass::setBackground_red(float newBackground_red) {
  background_red = newBackground_red;
}

inline float *DataClass::getBackgroundGreen() { return &backgroundGreen; }

inline void DataClass::setBackgroundGreen(float newBackgroundGreen) {
  backgroundGreen = newBackgroundGreen;
}

inline float *DataClass::getBackgroundBlue() { return &backgroundBlue; }

inline void DataClass::setBackgroundBlue(float newBackgroundBlue) {
  backgroundBlue = newBackgroundBlue;
}

inline float *DataClass::getBackgroundAlpha() { return &backgroundAlpha; }

inline void DataClass::setBackgroundAlpha(float newBackgroundAlpha) {
  backgroundAlpha = newBackgroundAlpha;
}

inline QColor &DataClass::getEdges_color() { return edges_color; }

inline void DataClass::setEdges_color(QColor &newEdges_color) {
  edges_color = newEdges_color;
}

inline float *DataClass::getEdge_red() { return &edge_red; }

inline void DataClass::setEdge_red(float newEdge_red) {
  edge_red = newEdge_red;
}

inline float *DataClass::getEdge_green() { return &edge_green; }

inline void DataClass::setEdge_green(float newEdge_green) {
  edge_green = newEdge_green;
}

inline float *DataClass::getEdge_blue() { return &edge_blue; }

inline void DataClass::setEdge_blue(float newEdge_blue) {
  edge_blue = newEdge_blue;
}

inline QColor &DataClass::getVertices_color() { return vertices_color; }

inline void DataClass::setVertices_color(QColor &newVertices_color) {
  vertices_color = newVertices_color;
}

inline float *DataClass::getVertice_red() { return &vertice_red; }

inline void DataClass::setVertice_red(float newVertice_red) {
  vertice_red = newVertice_red;
}

inline float *DataClass::getVertice_green() { return &vertice_green; }

inline void DataClass::setVertice_green(float newVertice_green) {
  vertice_green = newVertice_green;
}

inline float *DataClass::getVertice_blue() { return &vertice_blue; }

inline void DataClass::setVertice_blue(float newVertice_blue) {
  vertice_blue = newVertice_blue;
}

inline QPoint DataClass::position() { return m_position; }

inline void DataClass::setPosition(QPoint newPosition) {
  m_position = newPosition;
}

inline double DataClass::getTranslated_z() { return translated_z; }

inline void DataClass::setTranslated_z(double newTranslated_z) {
  translated_z = newTranslated_z;
}

inline std::size_t DataClass::getCount() { return count; }

inline void DataClass::setCount(std::size_t newCount) { count = newCount; }

inline double DataClass::getAngle() { return angle; }

inline void DataClass::setAngle(double newAngle) { angle = newAngle; }

inline QVector3D &DataClass::getAxis() { return axis; }

inline void DataClass::setAxis(QVector3D &newAxis) { axis = newAxis; }

inline DataClass *DataClass::getData_class() { return data_class; }

inline void DataClass::setData_class(DataClass *newData_class) {
  data_class = newData_class;
}

inline bool DataClass::getIsopen() { return isopen; }

inline void DataClass::setIsopen(bool newIsopen) { isopen = newIsopen; }

inline bool DataClass::getLine_type() { return line_type; }

inline void DataClass::setLine_type(bool newLine_type) {
  line_type = newLine_type;
}

inline double DataClass::getLine_thickness() { return line_thickness; }

inline void DataClass::setLine_thickness(double newLine_thickness) {
  line_thickness = newLine_thickness;
}

inline int DataClass::getVertice_type() { return vertice_type; }

inline void DataClass::setVertice_type(int newVertice_type) {
  vertice_type = newVertice_type;
}

inline double DataClass::getVertices_size() { return vertices_size; }

inline void DataClass::setVertices_size(double newVertices_size) {
  vertices_size = newVertices_size;
}

inline bool DataClass::getIsOrthogonal() { return isOrthogonal; }

inline void DataClass::setIsOrthogonal(bool newIsOrthogonal) {
  isOrthogonal = newIsOrthogonal;
}

inline bool DataClass::getIsProjection() { return isProjection; }

inline void DataClass::setIsProjection(bool newIsProjection) {
  isProjection = newIsProjection;
}

inline min_max_t &DataClass::getSizes() { return sizes; }

inline void DataClass::setSizes(min_max_t &newSizes) { sizes = newSizes; }

inline void DataClass::Memento::LoadData() {
  settings->setValue("vertice_color", data_class->vertices_color);
  settings->setValue("background_color", data_class->background_color);
  settings->setValue("edge_color", data_class->edges_color);
  settings->setValue("projection_type", data_class->isProjection);
  settings->setValue("line_type", data_class->line_type);
  settings->setValue("line_thickness", data_class->line_thickness);
  settings->setValue("vertice_type", data_class->vertice_type);
  settings->setValue("vertice_size", data_class->vertices_size);
}

inline void DataClass::Memento::SaveData() {
  QVariant backgoundColorSetting =
      settings->value("background_color", QColor(Qt::black));
  data_class->background_color = backgoundColorSetting.value<QColor>();
  QVariant vertice_color = settings->value("vertice_color", QColor(Qt::red));
  data_class->vertices_color = vertice_color.value<QColor>();
  QVariant edgesColor = settings->value("edge_color", QColor(Qt::red));
  data_class->edges_color = edgesColor.value<QColor>();
  data_class->isOrthogonal = settings->value("projection_type", true).toBool();
  data_class->line_type = settings->value("line_type", true).toBool();
  data_class->line_thickness = settings->value("line_thickness", 1).toDouble();
  data_class->vertice_type = settings->value("vertice_type", 1).toInt();
  data_class->vertices_size = settings->value("vertice_size", 1).toDouble();
}

#endif  // DATACLASS_H_
