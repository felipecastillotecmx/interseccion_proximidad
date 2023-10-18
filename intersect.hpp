#ifndef INTERSECT_HPP
#define INTERSECT_HPP

#include "line.hpp"
#include "lineareq.hpp"

// intersectAuxVertical ->pair<bool, Point>: función auxiliar de intersect. 
// Encuentra la intersección entre dos segmentos de línea, cuando uno de los
// segmentos es vertical. 
// O(1). 
pair <bool, Point> intersectAuxVertical(Line lineA, Line lineB){
  if (lineA.isVertical() && lineB.isVertical()) {
    if (lineA.pointA.x == lineB.pointA.x) {
      return yOverlapCollinear(lineA, lineB);
    }     
  } else if (lineA.isVertical()){ // LineA es vertical
    Point interPoint = LinearEq(lineB).solveSys(lineA.pointA.x);

    if (lineB.passesXValue(interPoint.x) && lineA.passesYValue(interPoint.y)){
      return pair<bool, Point>(true, interPoint); 
    }

  } else { // LineB es vertical 
    Point interPoint = LinearEq(lineA).solveSys(lineB.pointA.x);

    if (lineA.passesXValue(interPoint.x) && lineB.passesYValue(interPoint.y)){
      return pair<bool, Point>(true, interPoint); 
    }
  }  

  return pair<bool, Point>(false, Point(0,0)); 
}

// intersectAux ->pair<bool, Point>: función auxiliar de intersect. 
// Encuentra la intersección entre dos segmentos de línea, cuando ninguno de los 
// dos segmentos es vertical. 
// O(1). 
pair<bool, Point> intersectAux(Line lineA, Line lineB){
  LinearEq eqA(lineA);
  LinearEq eqB(lineB);

  if (eqA.slope == eqB.slope){
    if (eqA.yInter == eqB.yInter){
      return xOverlapCollinear(lineA, lineB);  
    }
    return pair<bool, Point>(false, Point(0,0));  
  } else {
    Point interPoint = eqA.solveSys(eqB);
    
    if (lineA.passesXValue(interPoint.x) && lineB.passesXValue(interPoint.x)) {
      return pair<bool, Point>(true, interPoint);  
    } else {
      return pair<bool, Point>(false, Point(0,0));
    } 
  }
}

// intersectAux ->pair<bool, Point>: determina si existe una interección entre 
// dos segmentos de línea, y dónde. El resultado de la función es un par; el 
// primer valor del par (bool) indica si existe una intersección, y el segundo 
// (Point), donde ocurre (si no ocurre una intersección, el valor de este elemento
// será un punto con las coordenadas [0, 0]). 
// O(1). 
pair<bool, Point> intersect(Line lineA, Line lineB){
  if (lineA == lineB){
    return pair<bool, Point>(true, lineA.pointA); 
  }
  else if (lineA.isVertical() || lineB.isVertical()){
    return intersectAuxVertical(lineA, lineB); 
  }
  else {
    return intersectAux(lineA, lineB); 
  } 
}

#endif 