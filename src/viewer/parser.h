#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <QString>
#include <QVector>
#include <fstream>
#include <string>
#include <vector>

#include "dataclass.h"

class Parser {
 public:
  Parser();
  ~Parser();
  void GetVertexesCount(const QString &path);
  void GetVertexesAndFacetsCount(const QString &path);
  void GetVertexesArray(const QString &path);
  void GetEdgeArray(const QString &path);
  void GetRealEdgeCount();

 private:
  int facets_count = 0;
};

#endif  // SRC_PARSER_H_
