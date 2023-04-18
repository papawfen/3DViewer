#include "parser.h"

Parser::Parser() {}
Parser::~Parser() {}

void Parser::GetVertexesCount(const QString &path) {
  int result = 0;
  std::string line;
  std::ifstream file(path.toStdString());
  if (file.is_open()) {
    while (std::getline(file, line))
      if (line[0] == 'v' && line[1] == ' ') result++;
    file.close();
  } else {
    throw std::invalid_argument("Cannot open the file");
  }
  DataClass::getDataClass()->setVertex_count(result);
}

void Parser::GetVertexesAndFacetsCount(const QString &path) {
  int v = 0;
  facets_count = 0;
  std::string line;
  std::ifstream file(path.toStdString());
  if (file.is_open()) {
    while (std::getline(file, line)) {
      if (line[1] == ' ') {
        if (line[0] == 'v') {
          v++;
        } else if (line[0] == 'f') {
          facets_count++;
        }
      }
    }
    file.close();
    DataClass::getDataClass()->setVertex_count(v);
  } else {
    throw std::invalid_argument("Cannot open the file");
  }
}

void Parser::GetVertexesArray(const QString &path) {
  QVector<double> result(3 * DataClass::getDataClass()->getVertex_count());
  int i = 0;
  int first_time = 1;
  std::string line;
  std::ifstream file(path.toStdString());
  if (file.is_open()) {
    while (std::getline(file, line)) {
      double x, y, z;
      if (std::sscanf(line.c_str(), "v %lf %lf %lf", &x, &y, &z) == 3) {
        result[i] = x;
        result[i + 1] = y;
        result[i + 2] = z;
        i += 3;
        if (first_time == 0) {
          if (x < DataClass::getDataClass()->getSizes().x_min) {
            DataClass::getDataClass()->getSizes().x_min = x;
          } else if (x > DataClass::getDataClass()->getSizes().x_max) {
            DataClass::getDataClass()->getSizes().x_max = x;
          }
          if (y < DataClass::getDataClass()->getSizes().y_min) {
            DataClass::getDataClass()->getSizes().y_min = y;
          } else if (y > DataClass::getDataClass()->getSizes().y_max) {
            DataClass::getDataClass()->getSizes().y_max = y;
          }
        } else {
          DataClass::getDataClass()->getSizes().x_min = x;
          DataClass::getDataClass()->getSizes().x_max = x;
          DataClass::getDataClass()->getSizes().y_min = y;
          DataClass::getDataClass()->getSizes().y_max = y;
          first_time = 0;
        }
      }
    }
    file.close();
  } else {
    throw std::invalid_argument("Cannot open the file");
  }
  DataClass::getDataClass()->setVertex_data(result);
}

void Parser::GetEdgeArray(const QString &path) {
  std::string line;
  std::ifstream file(path.toStdString());
  int edges_count = 0;
  int k = 2;
  if (file.is_open()) {
    while (std::getline(file, line)) {
      k = 2;
      if (line[0] == 'f' && line[1] == ' ') {
        while (line[k] != '\n' && line[k] != '\0' && line[k] != EOF) {
          if (line[k] >= '0' && line[k] <= '9') {
            while (line[k] >= '0' && line[k] <= '9') {
              k++;
            }
            while (line[k] != ' ' && line[k] != '\n' && line[k] != '\0' &&
                   line[k] != EOF) {
              k++;
            }
            k--;
            edges_count++;
          }
          k++;
        }
      }
    }
    DataClass::getDataClass()->setEdges_array_count(edges_count * 2);
    QVector<int> array(DataClass::getDataClass()->getEdges_array_count());
    file.clear();
    file.seekg(0);
    int counter = 0;
    while (std::getline(file, line)) {
      k = 2;
      if (line[0] == 'f' && line[1] == ' ') {
        int diff_counter = 0;
        int first_in_face = 0;
        while (line[k] != '\n' && line[k] != '\0' && line[k] != EOF) {
          int vertex_index = 0;
          if (line[k] >= '0' && line[k] <= '9') {
            while (line[k] >= '0' && line[k] <= '9') {
              vertex_index *= 10;
              vertex_index += line[k] - '0';
              k++;
            }
            while (line[k] != ' ' && line[k] != '\n' && line[k] != '\0' &&
                   line[k] != EOF) {
              k++;
            }
            k--;
            array[counter] = vertex_index;
            if (counter != 0 && array[counter - 1] == 0) {
              array[counter - 1] = vertex_index;
            }
            counter += 2;
            diff_counter += 2;
            first_in_face = array[counter - diff_counter];
          }
          k++;
        }
        array[counter - 1] = first_in_face;
      }
    }
    for (int i = 0; i < counter; i++) {
      array[i] -= 1;
    }
    DataClass::getDataClass()->setEdges_data(array);
    file.close();
  } else {
    throw std::invalid_argument("Cannot open the file");
  }
}

void Parser::GetRealEdgeCount() {
  DataClass::getDataClass()->setEdges_count(
      DataClass::getDataClass()->getVertex_count() + facets_count - 2);
}
