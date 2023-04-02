#include <iostream>

using namespace std;

using uint = unsigned int;

// ######################################## Ejercicio 1 ########################################

class Rectangulo {
    public:
        Rectangulo(uint alto, uint ancho); // constructor
        uint alto();
        uint ancho();
        float area();

    private:
        int alto_;
        int ancho_;

};

Rectangulo::Rectangulo(uint alto, uint ancho) : alto_(alto), ancho_(ancho){};

uint Rectangulo::alto() {
    return alto_;
}

uint Rectangulo::ancho() {
    return ancho_;
}

float Rectangulo::area() {
    return (alto_ * ancho_);
}

// ######################################## Ejercicio 2 ########################################

class Elipse{
public:
    // constructor primero
    Elipse (uint a, uint b) : _a(a), _b(b){};

    uint r_a(){
        return _a;
    }
    uint r_b(){
        return _b;
    }
    float area(){
        return (3.14 * _a * _b);
    }
private:
    uint _a;
    uint _b;
};

// ######################################## Ejercicio 3 ########################################

class Cuadrado {
    public:
        Cuadrado(uint lado);
        uint lado();
        float area();

    private:
        Rectangulo r_;
};

Cuadrado::Cuadrado(uint lado): r_(lado, lado) {}

uint Cuadrado::lado() {
    return r_.alto();
}

float Cuadrado::area() {
    return (r_.ancho() * r_.alto());
}

// ######################################## Ejercicio 4 ########################################

class Circulo{
    private:
        Elipse _c;
    public:
        Circulo(uint radio): _c(radio, radio){};
        uint radio(){
            return _c.r_a();
        }
        float area(){
            return _c.r_a() * _c.r_a() * 3.14;
        }
};


// ######################################## Ejercicio 5 ########################################

ostream& operator<<(ostream& os, Rectangulo r) {
    os << "Rect(" << r.alto() << ", " << r.ancho() << ")";
    return os;
}

// ostream Elipse

ostream& operator<<(ostream& os, Elipse e){
    os << "Elipse(" << e.r_a() << ", " << e.r_b() << ")";
    return os;
}

// ######################################## Ejercicio 6 ########################################

ostream& operator<<(ostream& os, Cuadrado c){
    os << "Cuad(" << c.lado() << ")";
    return os;
}

ostream& operator<<(ostream& os, Circulo c){
    os << "Circ(" << c.radio() << ")";
    return os;
}