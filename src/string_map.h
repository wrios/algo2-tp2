#ifndef STRING_MAP_STRING_MAP_H
#define STRING_MAP_STRING_MAP_H

#include <cassert>
#include <string>
#include <vector>
#include <ostream>
#include "linear_set.h"


using std::string;
using std::pair;

/**
 * Implementacion de map<string,T> sobre Trie
 * Asume de T:
 * - tiene constructor por copia (con complejidad copy(T))
 * - tiene operador == (con complejidad cmp(T))
 * - solo permite utilizar el operator[] si T tiene constructor por defecto
 */
template<typename T>
class string_map {
public:
    typedef string key_type;
    typedef T mapped_type;
    typedef std::pair<const key_type, mapped_type> value_type;
    typedef size_t size_type;
    using difference_type = std::ptrdiff_t;


    class iterator;

    class const_iterator;

    friend class iterator;

    friend class const_iterator;


    /** @brief Construye mapa vacio
     *
     * \complexity{\O(1)}
     */
    string_map();

    /** @brief Destruye mapa
     *
     * \complexity{\O(sn * S)}
     */
    ~string_map();

    /** @brief Constructor por copia
     *
     * \complexity{\O(sn * S * copy(T))}
     */
    string_map(const string_map &other);

    /** @brief Operador de asignacion
     *
     * \complexity{\O(sn * S * copy(T))}
     */
    string_map &operator=(const string_map &other);

    /** @brief Operadores de comparacion
     *
     * \complexity{\O(sn * S * cmp(T))}
     */
    bool operator==(const string_map &otro) const;

    bool operator!=(const string_map &otro) const;

    /** @brief Cantidad de apariciones de la clave (0 o 1)
     *  @param key clave a buscar
     *
     *  \complexity{\O(S)}
     */
    size_type count(const key_type &key) const;

    /** @brief Devuelve cantidad de claves definidas */
    size_t size() const;

    /** @brief devuelve true si size() == 0 */
    bool empty() const;


    /** @brief Acceso / definición de pares clave/valor
     *  @param key clave a acceder, si no existe, se crea
     *  @returns una referencia a la definicion.
     *
     *  \complexity{
     *    * \O(S) si la clave esta definida 
     *    * \O(S) + copy(T) sino
     *  }
     */
    mapped_type &operator[](const key_type &key);

    /** @brief Acceso a una clave sin modificar mapa
     *  @param key clave a acceder que debe existir previamente
     *  @returns una referencia a la definicion.
     *
     *  \complexity{\O(S)}
     */
    mapped_type &at(const key_type &key);

    /** @brief Acceso a una clave sin modificar mapa
     *  @param key clave a acceder que debe existir previamente
     *  @returns una referencia const a la definicion.
     *
     *  \complexity{\O(S)}
     */
    const mapped_type &at(const key_type &key) const;

    /** @brief Vacia el mapa */
    void clear();

    // Accesos con iteradores

    /** @brief iterador al primer par <clave,significado> en orden lexicografico
     *  @returns iterador al elemento o end() si el mapa era vacio
     *
     *  \complexity{\O(S)}
     */
    iterator begin();

    /**  @brief iterador al fin de la coleccion
     *
     *  \complexity{\O(S)}
     */
    iterator end();

    /// Versiones const de begin/end
    const_iterator begin() const;

    const_iterator end() const;

    const const_iterator cbegin() const;

    const_iterator cend() const;

    /** @brief busca una clave
     *  @param key clave a buscar
     *  @returns un iterador al par <clave, significado>
     *
     *  \complexity{\O(S)}
     */
    iterator find(const key_type &key);

    /** @brief busca una clave
     *  @param key clave a buscar
     *  @returns un iterador const al par <clave, significado>
     *
     *  \complexity{\O(S)}
     */
    const_iterator find(const key_type &key) const;

    /** @brief insercion
     *
     * @param value par <clave,significado> a insertar
     * @returns un par con un iterador al par clave-significado agregado o
     * modificado y un bool que indica si la clave se insertó como una clave
     * nueva.
     * 
     * \complexity{\O(S + copy(T))}
     */

    pair<iterator, bool> insert(const value_type &value);

    /** @brief eliminar una clave
     *  @param key clave a eliminar
     *  @returns cantidad de elementos eliminados
     *
     *  \complexity{\O(S)}
     */
    size_type erase(const key_type &key);

    /** @brief eliminar una clave mediante irerador
     *  @param pos iterador apuntando a clave a eliminar
     *  @returns iterador apuntando el proximo de la clave eliminada (o end() si era la ultima)
     *
     *  \complexity{\O(S)}
     */
    iterator erase(iterator pos);

    //FALTA CHEQUEAR COMPLEJIDAD
    /** @brief claves del diccionario
     *  @returns conjunto con las claves del diccionario
     *
     *  \complexity{\O(S)}
     */
    linear_set<string> claves() const;


    //FALTA CHEQUEAR COMPLEJIDAD
    /** @brief Significados del diccionario
     *  @returns conjunto con la union de todos los significados del diccionario
     *
     *  \complexity{\O(S)}
     */
    linear_set<T> significados() const;

private:


    struct Nodo {
        value_type *definicion;
        Nodo **hijos;
        Nodo *padre;
        size_t cant_hijos;

        Nodo() {
            hijos = new Nodo *[256];
            for (int i = 0; i < 256; i++) {
                hijos[i] = NULL;
            }
            definicion = NULL;
            padre = NULL;
            cant_hijos = 0;
        }

        void restar1padres();

        Nodo *primPadreCon1Hijo();

        Nodo *padreConHermanoODefinicion();

        Nodo *dameMayor();

        Nodo *minimo();

        Nodo *sucesor();

        bool tieneHM();

        Nodo *hermanoMayor(int key_i);

        void sumar1padres();
    };

    size_type cantElem;
    Nodo *raiz;

    /** @brief Preguntar
     *
     **/

    void restablecerCadena(Nodo *n, key_type key, int posicion);

    void eliminarAncestros(Nodo *n, key_type key, int posicion);

    bool mismosNodos(Nodo *n1, Nodo *n2);

    void eliminarNodos(Nodo *n);

    void eliminarNodosHijos(Nodo *n);

    void eliminarRec(Nodo *n);

    void eliminarRaiz(Nodo *n);


public:


    class iterator {
    public:

        using difference_type = std::ptrdiff_t;

        /**
         * @brief Constructor por copia del iterador.
         *
         * \complexity{\O(1)}
         */
        iterator(const iterator &otro);

        //FALTA CHEQUEAR QUE ESTE BIEN!!!!!
        /**
        * @brief Operador de asignación
        *
        * \pre true
        * \post true sii los iteradores apuntan al mismo elemento
        *
        * \complexity{\O(1)}
        */
        iterator &operator=(const iterator &otro);


        /**
        * @brief Comparación entre iteradores
        *
        * \pre ambos iteradores refieren a la misma colección
        * \post true sii los iteradores apuntan al mismo elemento
        *
        * \complexity{\O(1)}
        */
        bool operator==(const iterator &otro) const;

        /**
         * @brief Comparación entre iteradores
         *
         * \pre ambos iteradores refieren a la misma colección
         * \post true sii los iteradores no apuntan al mismo elemento
         *
         * \complexity{\O(1)}
         */
        bool operator!=(const iterator &otro) const;

        /**
         * @brief Avanza el iterador una posición.
         *
         * \pre El iterador no debe estar en la posición pasando-el-último.
         * \post \P{res} es una referencia a \P{this}. \P{this} apunta a la posición
         * siguiente.
         *
         * \complexity{\O(1)}
         */
        iterator operator++();

        iterator it_avanzarAlMin();

        /**
        * @brief Desreferencia el puntero
        *
        * El valor devuelto tiene aliasing dentro de la colección.
        *
        * \pre El iterador no debe estar en la posición pasando-el-último.
        * \post El valor resultado es una referencia al valor apuntado.
        *
        * \complexity{\O(1)}
        */
        value_type &operator*();

        /**
         * @brief Operador flechita
         *
         * El valor devuelvo tiene aliasing dentro de la colección.
         *
         * \pre El iterador no debe estar en la posición pasando-el-último.
         * \post El valor resultado es un puntero al valor apuntado.
         *
         * \complexity{\O(1)}
         */
        value_type *operator->();

        friend class string_map;

    private:

        Nodo *nodo;

        iterator(Nodo *n) : nodo(n) {};

        iterator avanzarMayor();

        iterator avanzarAlMin();


    };


    class const_iterator {
    public:

        using difference_type = std::ptrdiff_t;


        /**
         * @brief Constructor por copia del iterador.
         *
         * \complexity{\O(1)}
         */
        const_iterator(const const_iterator &);

        //FALTA CHEQUEAR QUE ESTE BIEN!!!!!
        /**
        * @brief Operador de asignación
        *
        * \pre true
        * \post true sii los iteradores apuntan al mismo elemento
        *
        * \complexity{\O(1)}
        */
        const_iterator &operator=(const const_iterator &);

        /**
         * @brief Comparación entre iteradores
         *
         * \pre ambos iteradores refieren a la misma colección
         * \post true sii los iteradores apuntan al mismo elemento
         *
         * \complexity{\O(1)}
         */
        bool operator==(const const_iterator &) const;

        /**
         * @brief Comparación entre iteradores
         *
         * \pre ambos iteradores refieren a la misma colección
         * \post true sii los iteradores no apuntan al mismo elemento
         *
         * \complexity{\O(1)}
         */
        bool operator!=(const const_iterator &) const;

        /**
         * @brief Avanza el iterador una posición.
         *
         * \pre El iterador no debe estar en la posición pasando-el-último.
         * \post \P{res} es una referencia a \P{this}. \P{this} apunta a la posición
         * siguiente.
         *
         * \complexity{\O(1)}
         */
        const_iterator operator++();

        const_iterator it_avanzarAlMin();

        /**
         * @brief Desreferencia el puntero
         *
         * El valor devuelto tiene aliasing dentro de la colección.
         *
         * \pre El iterador no debe estar en la posición pasando-el-último.
         * \post El valor resultado es una referencia constante al valor apuntado.
         *
          * \complexity{\O(1)}
          */
        value_type &operator*();

        /**
         * @brief Operador flechita
         *
         * El valor devuelvo tiene aliasing dentro de la colección.
         *
         * \pre El iterador no debe estar en la posición pasando-el-último.
         * \post El valor resultado es un puntero al valor apuntado.
         *
         * \complexity{\O(1)}
         */
        value_type *operator->();

        friend class string_map;

    private:

        Nodo *nodo;

        const_iterator(Nodo *n) : nodo(n) {};


        const_iterator avanzarMayor();

        const_iterator avanzarAlMin();

    };

};

#include "string_map.hpp"

#endif //STRING_MAP_STRING_MAP_H
