#include <iostream>
#include <string>
#include <stdexcept>
#include "intersect.hpp"
#include "input.hpp"
using namespace std;

#define MAXINT 2147483647

int main(){
    // Creación de las lineas de entrada.
    int n = 0;
    string line;
    vector<float> points;
    vector<pair<Line, Line> > lines;

    cout<<"Ingrese el número de pares de segmentos: ";
    cin>>n;
    cin.ignore(MAXINT, '\n');

    if (n <= 0){
        throw invalid_argument("Se requiere como mínimo un par de segmentos");
    }

    cout<<"Ingrese, en cada línea, cuatro puntos (x & y): "<<endl;
    for (int i = 0; i < n; i++){
        getline(cin, line);
        points = strToFloatVec(line);

        if (points.size() != 8){
            throw invalid_argument("Cada línea debe tener cuatro puntos (8 valores)");
        }

        lines.push_back(buildLines(points));
    }

    // Búsqueda de intersecciones.
    cout<<"Resultados:"<<endl;
    pair<bool, Point> result;
    for (int i = 0; i < lines.size(); i++){
        result = intersect(lines[i].first, lines[i].second);

        if (result.first){
            cout<<"True - "<<result.second.pointToString();
        } else {
            cout<<"False";
        }
        cout<<endl;
    }

    return 0;
}