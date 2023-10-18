#ifndef INPUT_HPP
#define INPUT_HPP

#include "point.hpp"
#include <vector>
#include <stdexcept>
#include <stack>
#include <string>
#include <cmath>
using namespace std; 

// FloatVecBuilder: clase que auxilia en la construcción de un vector<float>
// a partir de un string, utiizada en la función strToFloatVec. 
class FloatVecBuilder{
  private: 
  bool prevNatural; 
  int size; 
  stack<float> naturals; 
  stack<float> fractions; 
  stack<bool> signs; 

  float join(float nat, float frac, bool isNeg) const {
    return (nat + frac) * ((isNeg && nat + frac > 0.0)? -1.0 : 1.0); 
  } 

  public: 
  FloatVecBuilder(){
    prevNatural = true; 
    size = 0; 
  }

  void add(float value, int numDigits, bool isFraction, bool isNeg){
    if (!isFraction){ // natural 
      if (prevNatural){
        fractions.push(0.0);
      } 
      naturals.push(value); 
      size++; 
      signs.push(isNeg); 
      prevNatural = true; 
      
    } else { // fraction 
      if (!prevNatural){
        naturals.push(0.0);
        size++; 
        signs.push(isNeg); 
      } 
      fractions.push((value == 0)? 0.0 : (value / (float)pow(10, numDigits))); 
      prevNatural = false; 
    }
  }

  vector<float> joinAll(){
    vector<float> numbers; 

    if (fractions.size() > naturals.size()){
      naturals.push(0.0); 
      size++; 
      signs.push(false); 
    }
    
    if (size == 0){
      return numbers; 
    }
    
    while (!naturals.empty()){
      numbers.push_back(join(naturals.top(), fractions.top(), signs.top())); 
      naturals.pop(); 
      fractions.pop(); 
      signs.pop(); 
    }

    prevNatural = false; 
    return numbers; 
  }
}; 

// isDigit ->bool: regresa un valor booleano que indica si 
// el cáracter c representa o no un dígito númerico. 
// Complejidad temporal: O(1). 
bool isDigit(char c){
  return (int)'0' <= (int)c && (int)c <= (int)'9'; 
}

// strToFloatVec ->vector<float>: crea un vector<float> que
// contiene todos los números presentes en el string line, los cuales 
// pueden ser positivos, negativos, enteros, o fraccionales. 
// Ignora los caracteres que no conforman un número. 
// O(n). 
vector<float> strToFloatVec(const string& line){
  FloatVecBuilder builder; 
  float number = 0.0; 
  int numDigits = 0; 
  
  for(int i = line.size() - 1; i >= 0; i--){
    if (isDigit(line[i])){
      number += (line[i] - (int)'0') * (float)pow(10, numDigits); 
      numDigits++; 
    } else if (numDigits > 0){ 
      builder.add(number, numDigits, line[i] == '.', line[i] == '-');  
      number = 0.0; 
      numDigits = 0; 
    } 
  }

  if (numDigits > 0){
    builder.add(number, numDigits, false, false);
  }
    
  return builder.joinAll();
}

// inputPoints ->vector<Point>: función que permite al usuario crear 
// n puntos (Point). La función regresa un vector que contiene 
// los n puntos ingresados por el usuario. 
// O(n^2). 
vector<Point> inputPoints(int n){
  vector<Point> points; 
  vector<float> point; 
  string auxStr; 

  for (int i = 0; i < n; i++){
    getline(cin, auxStr); 
    point = strToFloatVec(auxStr); 

    if (point.size() != 2){
      throw invalid_argument("Cada punto requiere 2 números validos"); 
    }

    points.push_back(Point(point)); 
  }
  
  return points; 
}

#endif  