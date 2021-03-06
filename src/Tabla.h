#ifndef TABLA_H
#define TABLA_H

#include <string>

#include "linear_map.h"
#include "linear_set.h"
#include "Dato.h"
#include "Registro.h"

using namespace std;

/**
 * @brief Representa una tabla de una base de datos.
 *
 * Una tabla es una colección de registros que cumplen la descripción de la
 * misma. La descripción de una tabla consiste en una serie de nombres que
 * describen los campos y un tipo para cada campo que explicita el tipo de dato
 * que un registro puede tener en ese campo.
 *
 * La descripción también selecciona un subconjunto de los campos como \i
 * claves. Dada las claves, una tabla no puede tener dos registros con los
 * mismos valores para todos los campos claves.
 *
 * **se explica con** TAD Tabla
 */
class Tabla {

public:

  // Forward declaration
  class const_iterador_registros;

  /**
   * @brief Inicializa una tabla sin registros y con la descripción parámetro.
   *
   * @param claves Subconjunto de los campos que son claves.
   * @param campos Conjunto de nombres de claves. El órden se corresponde con 
   * el de datos
   * @param tipos  Conjunto de datos cuyo tipo define el tipo admisible en cada
   * campo. El valor de los datos se ignora.
   * 
   * \pre \LNOT \EMPTYSET ?(c) \LAND 
   *      \FORALL (c: campo) c \in claves \IMPLIES esta?(c, campos) \LAND
   *      long(campos) = long(tipos) \LAND sinRepetidos(campos)
   * \post \P{res} = nuevaTabla(claves, nuevoRegistro(campos, tipos))
   *
   * \complexity{\O(long(campos) * (copy(campo) + copy(dato)))}
   */
  Tabla(const linear_set<string> &claves, const vector<string> &campos,
        const vector<Dato> &tipos);

  /**
   * @brief Inserta un nuevo registro en la tabla.
   *
   * @param r Registro a agregar
   *
   * \pre t = \P{this} \LAND campos(r) = campos(t) \LAND puedoInsertar?(r, t)
   * \post \P{this} = agregarRegistro(r, t) \LAND \P{res} apunta al registro
   * recién agregado.
   *
   * \complexity{\O(copy(registro))}
   */
  const_iterador_registros agregarRegistro(const Registro &r);

  /**
   * @brief Campos de la tabla
   *
   * El conjunto se devuelve por referencia no-modificable
   *
   * \pre true
   * \post \P{res} = campos(\P{this})
   *
   * \complexity{\O(C)}
   */
  const linear_set<string> campos() const;

  /**
   * @brief Tipo del campo parámetro para la tabla
   *
   * El dato se devuelve por referencia no-modificable.
   * El dato se utiliza solo para representar el tipo. Su valor se ignora.
   *
   * \pre campo \IN campos(\P{this})
   * \post tipoCampo(campo, \P{this})
   *
   * \complexity{\O(1)}
   */
  const Dato &tipoCampo(const string &campo) const;

  /**
   * @brief Subconjunto de campos que son clave
   *
   * El conjunto se devuelve por referencia no-modificable.
   *
   * \pre true
   * \post \P{res} = claves(\P{this})
   *
   * \complexity{\O(c)}
   */
  const linear_set<string> claves() const;

  /**
   * @brief Los registros de la tabla
   *
   * Se devuelve por referencia no-modificable.
   *
   * \pre true
   * \post \P{res} = Registros(\P{this})
   *
   * \complexity{\O(1)}
   */
  const linear_set<Registro>& registros() const;


  /**
   * @brief Cantidad de registros de la tabla
   *
   * Se devuelve por referencia no-modificable.
   *
   * \pre true
   * \post \P{res} = #Registros(\P{this})
   *
   * \complexity{\O(1)}
   */
  int cant_registros() const;

  /**
   * @brief Iterador al inicio de los registros de la tabla. 
   *
   * El iterador resultado es conformante con [std::InputIterator](http://en.cppreference.com/w/cpp/concept/InputIterator)
   *
   * \pre true
   * \post El iterador \P{res} recorre los registros de la tabla en un orden
   * no definido. 
   *
   * \complexity{\O(1)}
   */
  const_iterador_registros registros_begin() const;
  
  /**
   * @brief Iterador al final de los registros de la tabla. 
   *
   * El iterador resultado es conformante con [std::InputIterator](http://en.cppreference.com/w/cpp/concept/InputIterator)
   *
   * \pre true
   * \post El iterador \P{res} apunta al lugar-pasando-el-último de los
   * registros de la tabla. Puede utilizarse para comparar con otro
   * const_iterador_registros para saber si se llegó al final de la iteración.
   *
   * \complexity{\O(1)}
   */
  const_iterador_registros registros_end() const;

private:
	  ///////////////////////////////////////////////////////////////////////////////////////////////////
    /** \name Representación
     * rep: tabla \TO bool\n
     * rep(t) \EQUIV 
     *  * \LNOT \EMPTYSET?(claves(_claves)) \LAND
     *  * claves(_claves) \SUBSETEQ claves(_camposYtipos) \LAND
     *  * \FORALL (r : registro) r \IN _registros \IMPLIES (
     *    * campos(r) = claves(_camposYtipos)
     *    * \FORALL (c : campo) def?(c, _camposYtipos) \IMPLIES
     *        Nat?(valor(c, r)) = Nat?(obtener(c, _camposYtipos))
     *    * no se repiten claves \EQUIV
     *      \LNOT hayCoincidencia(r, claves(_claves), _registros)
     *  * )
     *
     * abs: tabla \TO Tabla\n
     * abs(t) \EQUIV t' \|
     *  * campos(t') = claves(_camposYtipos) \LAND
     *  * claves(t') = claves(_claves) \LAND
     *  * \FORALL (c : string) def?(c, _camposYtipos) \IMPLIES tipoCampo(c, t') =
     *    Nat?(obtener(c, _campostYtipos)) \LAND
     *  * registros(t') = _registros
     */
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    /** @{ */
    string_map<bool> _claves;
    string_map<Dato> _camposYtipos;
    linear_set<Registro> _registros;
    /** }@ */

};

bool operator==(const Tabla&, const Tabla&);
bool operator!=(const Tabla&, const Tabla&);

#include "const_iterador_registros.h"

#endif //TABLA_H
