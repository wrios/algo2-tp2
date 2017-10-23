#include "Indice.h"

Indice::Indice() {

}

Indice::Indice(Tabla tab, string campo, bool esString) {
    _campo = campo;
    _esString = esString;
    for (auto elem: tab.registros()){
        agregarRegistro(elem);
    }
}


string Indice::dameCampo() const {
    return _campo;
}

linear_set<const Registro*> Indice::dameRegistros(const Dato &d) {
    if (_esString){
        return _indicesStr[d.valorStr()];
    } else {
        return _indicesNat[d.valorNat()];
    }
}

Indice::~Indice() {
    if (_esString){
        _indicesStr.~string_map();
    } else{
        _indicesNat.~map();
    }
    //_campo.~string();
}
bool Indice::esVacio() {
    if (_esString)
        return _indicesStr.empty();
    else
        return _indicesNat.empty();
}

void Indice::agregarRegistro(const Registro &r) {
    if (_esString){
        string valorCampo = r.dato(_campo).valorStr();
        //chequear caso no definido
        _indicesStr[valorCampo].insert(&r);
    }else{
        int valorCampo = r.dato(_campo).valorNat();

        _indicesNat[valorCampo].insert(&r);
    }
}

