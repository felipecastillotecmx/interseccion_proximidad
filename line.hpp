#ifndef LINE_HPP
#define LINE_HPP

#include "point.hpp"
#include <vector>
#include <utility>
#include <stdexcept>
using namespace std;

// Line: estructura mediante la cual se representa un segmento de línea del plano cartesiano.
struct Line {
    Point pointA; 
    Point pointB; 

    Line(float, float, float, float);
    Line(Point, Point); 
    Line(vector<float>); 
    bool isVertical(); 
    bool isHorizontal(); 
    bool passesXValue(float); 
    bool passesYValue(float); 
    bool operator==(Line);
    Point highestPointY();
    Point lowestPointY(); 
}; 

// Line::Line: constructor de Line. Instancia la clase utilizando cuatro valores
// de tipo float. El primer par de argumentos son las coordenadas del primer punto
// del segmento, el segundo las del segundo punto. El punto A del segmento será
// siempre el punto que tenga el menor valor de x.
// Complejidad temporal: O(1).
Line::Line(float x1, float y1, float x2, float y2){
  this->pointA = (x1 <= x2)? Point(x1, y1) : Point(x2, y2); 
  this->pointB = (x1 <= x2)? Point(x2, y2) : Point(x1, y1); 

  if (this->pointA == this->pointB){
    throw invalid_argument("Los dos puntos de la línea no pueden ser iguales"); 
  }
}

// Line::Line: constructor de Line. Instancia el segmento de línea a partir de dos
// puntos.
// O(1).
Line::Line(Point pointA, Point pointB){
  this->pointA = (pointA.x <= pointB.x)? pointA : pointB; 
  this->pointB = (pointA.x <= pointB.x)? pointB : pointA; 

  if (this->pointA == this->pointB){
    throw invalid_argument("Los dos puntos de la línea no pueden ser iguales"); 
  }
}

// Line: constructor de Line. Crea un segmento de línea utilizando el par de puntos presente
// en el vector<float> points.
// O(1).
Line::Line(vector<float> points){
  if (points.size() != 4){
    throw invalid_argument("Número inválido de puntos dado"); 
  }

  if (points[0] <= points[2]){
    pointA = Point(points[0], points[1]); 
    pointB = Point(points[2], points[3]); 
  } else {
     pointA = Point(points[2], points[3]); 
     pointB = Point(points[0], points[1]); 
  } 

  if (pointA == pointB){
    throw invalid_argument("Los dos puntos de la línea no pueden ser iguales"); 
  }
}

// Line::isVertical ->bool: determina si la instancia actual representa
// una línea vertical.
// O(1).
bool Line::isVertical(){
  return pointA.x == pointB.x; 
}

// Line::isHorizontal ->bool: determina si la instancia actual representa
// una línea horizontal.
// O(1).
bool Line::isHorizontal(){
  return pointA.y == pointB.y; 
}

// Line::passesXValue ->bool: determina si en el rango de x que el segmento de línea
// abarca, se encuentra el valor de x dado. El punto A de un segmento siempre
// tiene el menor valor de x.
// O(1).
bool Line::passesXValue(float x){
  return pointA.x <= x && x <= pointB.x; 
}

// Line::passesYValue ->bool: determina si en el rango de y que el segmento de línea
// abarca, se encuentra el valor de y dado.
// O(1).
bool Line::passesYValue(float y){
  if (pointA.y < pointB.y){
    return pointA.y <= y && y <= pointB.y; 
  } 
  return pointB.y <= y && y <= pointA.y; 
}

// Line::operator== ->bool: sobrecarga del operador '=='. Determina si dos
// instancias de Line son iguales.
// O(1).
bool Line::operator==(Line line){
    return pointA == line.pointA && pointB == line.pointB; 
}

// Line::highestPointY ->Point: regresa el punto (Point) del segmento
// que tiene el mayor valor de y.
// O(1).
Point Line::highestPointY(){
  return (pointB.y >= pointA.y)? pointB : pointA; 
}

// Line::lowestPointY ->Point: regresa el punto (Point) del segmento
// que tiene el menor valor de y.
// O(1).
Point Line::lowestPointY(){
  return (pointA.y < pointB.y)? pointA : pointB; 
}

// Line::buildLines ->pair<Line, Line>: crea dos instancias de Line
// utilizando los valores de un vector<float> de 8 elementos. En el vector, 
// cada par representa un punto. 
// O(n). 
pair<Line, Line> buildLines(vector<float> points){
    if (points.size() != 8){
        throw invalid_argument("Número inválido de puntos dado"); 
    }

    vector<float> points1(points.begin(), points.end() -  4); 
    vector<float> points2(points.begin() + 4, points.end()); 

    return pair<Line, Line>(Line(points1), Line(points2)); 
}

// xOverlapCollinear ->pair<bool, Point>: determina si existe (y dónde) una intersección entre
// dos segmentos de línea colineales y no verticales.
// O(1). 
pair<bool, Point> xOverlapCollinear(Line lineA, Line lineB){
  if (lineA.pointA.x <= lineB.pointA.x){
    if (lineA.pointB.x >= lineB.pointA.x){
      return pair<bool, Point>(true, lineB.pointA); 
    }
  } else {
    if (lineB.pointB.x >= lineA.pointA.x){
      return pair<bool, Point>(true, lineA.pointA); 
    }
  }
  return pair<bool, Point>(false, Point(0,0)); 
}

// yOverlapCollinear ->pair<bool, Point>: determina si existe (y dónde) una 
// intersección entre dos segmentos de línea colineales y verticales.
// O(1). 
pair<bool, Point> yOverlapCollinear(Line lineA, Line lineB){
  if (lineA.lowestPointY().y <= lineB.lowestPointY().y){
    if (lineA.highestPointY().y >= lineB.lowestPointY().y){
      return pair<bool, Point>(true, lineB.lowestPointY()); 
    }
  } else {
    if (lineB.highestPointY().y >= lineA.lowestPointY().y){
      return pair<bool, Point>(true, lineA.lowestPointY()); 
    }
  }
  return pair<bool, Point>(false, Point(0,0)); 
}

#endif 