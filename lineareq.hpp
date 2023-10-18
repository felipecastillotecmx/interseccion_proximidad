#ifndef LINEAREQ_HPP
#define LINEAREQ_HPP

#include "line.hpp"
#include "point.hpp"
#include <stdexcept>

using namespace std;

// LinearEq: clase que representa matemáticamente una línea del plano cartesiano, 
// mediante la forma y = mx + b. 
class LinearEq{
    private: 
    float findSlope(Line); 
    float findYInter(float, Point); 

    public: 
    float slope; 
    float yInter; 

    LinearEq(Line); 
    Point solveSys(const LinearEq&) const;
    Point solveSys(float) const;
    float solveForX(float) const; 
    float solveForY(float) const;  
    bool operator==(const LinearEq&) const; 
}; 

// LinearEq::findSlope ->float: obtiene la pendiente de una línea, a partir de uno de 
// sus segmentos (representado con la clase Line). La función asume que la línea
// tiene una pendiente definida. 
// Complejidad temporal: O(1). 
float LinearEq::findSlope(Line line){
    // m = y2 - y1 / x2 - x1 = rise / run 
    return (line.pointB.y - line.pointA.y) / (line.pointB.x - line.pointA.x); 
}

// LinearEq::findYInter ->float: obtiene el valor de b (y-intercept) de la forma y = mx + b. 
// O(1). 
float LinearEq::findYInter(float slope, Point point){
    // y = mx + b
    // y - mx = b = yInter
    return point.y - slope * point.x; 
}

// LinearEq::LinearEq: constructor de la clase LinearEq. Utiliza una instancia de la clase 
// Line, para lograr la representación matemática de la línea. Se produce un error si la 
// línea dada tiene una pendiente indefinida. 
// O(1). 
LinearEq::LinearEq(Line line){
    if (line.isVertical()){
        throw invalid_argument("La línea tiene una pendiente indefinida, y no puede ser representada con LinearEq"); 
    }

    slope = findSlope(line); 
    yInter = findYInter(slope, line.pointA); 
}

// LinearEq::solveSys ->Point: regresa el punto del plano en el que la instancia
// actual se interseca con la línea dada (line). 
// O(1). 
Point LinearEq::solveSys(const LinearEq& line) const{
    if (slope == line.slope){
        throw invalid_argument("Una sola intersección entre dos líneas con pendientes iguales no es posible"); 
    }

    // zx + b = hx + r
    // (z - h)x = r - b
    // x = (r - b) / (z - h)
    float x = (line.yInter - yInter) / (slope - line.slope); 
    return Point(x, solveForY(x)); 
}

// LinearEq::solveSys ->Point: regresa el punto del plano en el que la instancia
// actual se interseca con la línea vertical dada. Dicha línea es representada con 
// un solo valor flotante, que es el valor de x.  
// O(1). 
Point LinearEq::solveSys(float x) const{
    return Point(x, solveForY(x)); 
}

// LinearEq::solveForX ->float: obtiene el valor de x de la función, cuando y tiene el valor 
// dado como argumento. 
// O(1). 
float LinearEq::solveForX(float y) const{
    // y = mx + b
    // (y - b) / m = x 
    return (y - yInter) / slope; 
}

// LinearEq::solveForX ->float: obtiene el valor de y de la función, cuando x tiene el valor 
// dado como argumento. 
// O(1). 
float LinearEq::solveForY(float x) const{
    // y = mx + b
    return slope * x + yInter; 
}

// LinearEq::operator== ->bool: sobrecarga del operador ==. Determina si dos
// instancias de LinearEq son iguales. 
// O(1). 
bool LinearEq::operator==(const LinearEq& line) const{
    return slope == line.slope && yInter == line.yInter; 
}

#endif 