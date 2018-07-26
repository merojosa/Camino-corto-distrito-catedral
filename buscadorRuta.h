#ifndef BUSCADORRUTA_H
#define BUSCADORRUTA_H


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   buscadorRuta.h
 * Author: Bailin
 *
 * Created on 12 de noviembre de 2017, 12:11 PM
 */
#include "coordenadas.h"

#include <locale>
#include <cstdlib>

struct par_ordenado{
    int avenida;
    int calle;
};

class buscadorRuta {
public:
    buscadorRuta();
    
    virtual ~buscadorRuta();
    
    int buscarExhaustiva(int origenA,int origenC, int destinoA, int destinoC);

    int buscarNO(int origenA,int origenC, int destinoA, int destinoC, int contador);
    int buscarNE(int origenA,int origenC, int destinoA, int destinoC, int contador);
    int buscarSO(int origenA,int origenC, int destinoA, int destinoC, int contador);
    int buscarSE(int origenA,int origenC, int destinoA, int destinoC, int contador);

    void leer_inicio_meta();
    
private:

    Coordenadas *coordenada;
    std::vector< std::vector< std::vector< std::vector<char> > > > vector_coordenada;

public:
    int avenida_inicio;
    int calle_inicio;
    int avenida_destino;
    int calle_destino;
    int altos;
    int solucion_valor;
    std::vector<par_ordenado> *vector_solucion;
    void procesar_coordenada(std::string par_ordenado, bool destino);
    void asignar_valor_coordenadas(int posicion, bool destino, char tipo);

    std::vector<par_ordenado> *getVector_solucion() const;
};

#endif /* BUSCADORRUTA_H */

