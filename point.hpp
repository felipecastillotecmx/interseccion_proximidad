#ifndef POINT_HPP
#define POINT_HPP

#include <string>
#include <sstream>
#include <vector>
using namespace std; 

// Point: estructura que representa un punto (x,y) del plano cartesiano.
struct Point{
    float x; 
    float y; 

    Point(): x(0), y(0) {}; 
    Point(float _x, float _y): x(_x), y(_y) {}; 
    Point(const vector<float>&); 
    bool operator==(Point); 
    string pointToString(); 
}; 

// Point::Point: constructor de Point. Crea una instancia de Point utilizando
// los valores de un vector<float>, el cual deberá tener únicamente dos
// elementos.
// Complejidad temporal: O(1).
Point::Point(const vector<float>& point){
  if (point.size() != 2){
    throw invalid_argument("Vector inválido; debe tener dos elementos"); 
  }

  x = point[0]; 
  y = point[1]; 
}

// Point::operator== ->bool: función que determina si dos instancias de Point son
// iguales.
// Complejidad temporal: O(1).
bool Point::operator==(Point point){
    return x == point.x && y == point.y; 
}

// Point::pointToString ->string: crea un string que representa el punto.
// O(1).
string Point::pointToString(){
    stringstream sstream; 
    sstream<< '(' << x << ", " << y << ')'; 
    return sstream.str(); 
}

#endif 