#include "SistemaDeMensajes.h"

SistemaDeMensajes::SistemaDeMensajes(): _conns(){}

SistemaDeMensajes::~SistemaDeMensajes(){
    for (ConexionJugador* c : _conns)
        delete c;

    for (Proxy* proxy: _proxys)
        delete proxy;
}

void SistemaDeMensajes::registrarJugador(int id, string ip){
    if (registrado(id)) {
        desregistrarJugador(id);
    }
    _conns[id] = new ConexionJugador(ip);
}

void SistemaDeMensajes::desregistrarJugador(int id) {
    delete _conns[id];
    _conns[id] = nullptr;
}

void SistemaDeMensajes::enviarMensaje(int id, string mensaje){
    _conns[id] -> enviarMensaje(mensaje);
}

bool SistemaDeMensajes::registrado(int id) const{
    return (_conns[id] != nullptr);
}

Proxy* SistemaDeMensajes::obtenerProxy(int id){
    Proxy* proxy = new Proxy(_conns[id]);
    _proxys.push_back(proxy);
    return proxy;
}