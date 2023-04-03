#include <utility>
using namespace std;
typedef unsigned int uint;

// Taller 1 - Juego

using Pos = pair<int, int>;

const char ARRIBA = '^';
const char ABAJO = 'v';
const char DERECHA = '<';
const char IZQUIERDA = '>';

class Juego {
    private:
        uint _casilleros;
        Pos _coord;
        uint _turno = 0;

    public:
        Juego(uint casilleros, Pos pos_inicial);
        Pos posicion_jugador();
        uint turno_actual();
        void mover_jugador(char dir);
        void ingerir_pocion(uint movimientos, uint turnos);
};

Juego:: Juego(uint casilleros, Pos pos_inicial): _casilleros(casilleros), _coord(pos_inicial){}

Pos Juego:: posicion_jugador() { return _coord; }

uint Juego:: turno_actual(){ return _turno; }

void Juego::mover_jugador(char dir) {
                    // asumo que no se va del mapa ¿?
    switch(dir){    // convierto las direcciones en const para usar el switch
        case ARRIBA:
            _coord.first--;
            _turno++;
            break;

        case IZQUIERDA:
            _coord.second--;
            _turno++;
            break;

        case ABAJO:
            _coord.first++;
            _turno++;
            break;

        case DERECHA:
            _coord.second++;
            _turno++;
            break;
    }
}

void Juego::ingerir_pocion(uint movimientos, uint turnos) {
    while(turnos != 0){
        while(movimientos != 0){
            char dir;
            mover_jugador(dir);
            movimientos--;
        }
        turnos--;
    }
}