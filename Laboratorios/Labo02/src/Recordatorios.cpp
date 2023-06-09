#include <iostream>
#include <list>

using namespace std;

using uint = unsigned int;

// Pre: 0 <= mes < 12
uint dias_en_mes(uint mes) {
    uint dias[] = {
        // ene, feb, mar, abr, may, jun
        31, 28, 31, 30, 31, 30,
        // jul, ago, sep, oct, nov, dic
        31, 31, 30, 31, 30, 31
    };
    return dias[mes - 1];
}

// Ejercicio 7, 8, 9 y 10

// Clase Fecha
class Fecha {
  public:
    Fecha(uint mes, uint dia) : _mes(mes), _dia(dia){};
    int mes(){
        return _mes;
    }
    int dia(){
        return _dia;
    }

    void incrementar_dia(){
        _dia ++;
        if (_dia > dias_en_mes(_mes)) {
            _dia = 1;
            _mes ++;
            if (_mes > 12) _mes = 1;
        }
    }

    #if EJ >= 9 // Para ejercicio 9
    bool operator==(Fecha o);
    #endif

  private:
    uint _dia;
    uint _mes;
};

ostream& operator<<(ostream& os, Fecha f){
    os << f.dia() << "/" << f.mes();
    return os;
}


#if EJ >= 9
bool Fecha::operator==(Fecha o) {
    /*
    bool igual_dia = this->dia() == o.dia();
    // Completar iguadad (ej 9)
    return igual_dia;

    NO ENTIENDO COMO FUNCIONA ESO, LO HAGO DE OTRA FORMA
     */
    return (_mes == o.mes() && _dia == o.dia());
}
#endif

// Ejercicio 11, 12

class Horario{
    private:
        uint _hora;
        uint _min;
    public:
        Horario(uint hora, uint min): _hora(hora), _min(min){};

        uint hora(){ return _hora; }
        uint min(){ return _min; }

        bool operator==(Horario h){
            return (_hora == h.hora() && _min == h.min());
        }

        bool operator<(Horario h){
            bool output = (_hora < h.hora() || (_hora == h.hora() && _min < h.min()));
            return output;
        }
};

ostream& operator<<(ostream& os, Horario h){
    os << h.hora() << ":"<< h.min();
    return os;
}


// Ejercicio 13

class Recordatorio{
    private:
        Fecha _fecha;
        Horario _hora;
        string _mensaje;
    public:
        Recordatorio(Fecha f, Horario h, string msj): _fecha(f), _hora(h), _mensaje(msj){}

        string mensaje(){ return _mensaje; }
        Fecha fecha(){ return _fecha; }
        Horario hora() { return _hora; }
};

ostream& operator<<(ostream& os, Recordatorio r){
    os << r.mensaje() << " @ "<< r.fecha() << " "<< r.hora();
    return os;
}


// Ejercicio 14
// agrego clase list

class Agenda{
    private:
        Fecha _fechaHoy;
        list<Recordatorio> _records;
    public:
        Agenda(Fecha fecha_inicial): _fechaHoy(fecha_inicial){}

        void agregar_recordatorio(Recordatorio rec);
        void incrementar_dia();
        list<Recordatorio> recordatorios_de_hoy();
        Fecha hoy();
};

void Agenda::agregar_recordatorio(Recordatorio rec) {
    _records.push_back(rec);
}

void Agenda::incrementar_dia() {
    _fechaHoy.incrementar_dia();
}

list<Recordatorio> Agenda::recordatorios_de_hoy() {
    vector<Recordatorio> recs, recsHoy;
    for(Recordatorio r : _records){
        recs.push_back(r);
    }

    for(Recordatorio r1 : recs) {
        if (r1.fecha() == _fechaHoy) {
            if (recsHoy.empty())
                recsHoy.push_back(r1);
            else {
                int i = 0;
                for (Recordatorio r2: recsHoy) {
                    if (r1.hora().hora() < r2.hora().hora() or
                        (r1.hora().hora() == r2.hora().hora() and r1.hora().min() <= r2.hora().min())) {
                        i++;
                    }
                    recsHoy.insert(recsHoy.begin() + i, r1);
                }
            }
        }
    }
    list<Recordatorio> recsHoyLista;
    for (Recordatorio r : recsHoy)
        recsHoyLista.push_front(r);

    // hice un choclazo de funcion para poder operar con vectores pues
    // para operar con listas hay que usar interators y pointers (creo)

    return recsHoyLista;
}

Fecha Agenda::hoy(){
    return _fechaHoy;
}

ostream& operator<<(ostream& os, Agenda ag){
    os << ag.hoy() << "\n=====" << endl;
    for (Recordatorio r : ag.recordatorios_de_hoy()){
         os << r << endl;
    }
    return os;
}