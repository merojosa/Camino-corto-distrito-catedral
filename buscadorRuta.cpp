/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   buscadorRuta.cpp
 * Author: Bailin
 * 
 * Created on 12 de noviembre de 2017, 12:11 PM
 */
#include "coordenadas.h"
#include "buscadorRuta.h"

buscadorRuta::buscadorRuta() {
    coordenada = new Coordenadas();
    vector_coordenada = coordenada->get_vector_coordenadas();
    vector_solucion = new std::vector<par_ordenado>();
    std::vector<par_ordenado> *solucion_mejor = new std::vector<par_ordenado>();
    // Valores por defecto.
    avenida_inicio = -1;
    avenida_destino = -1;
    calle_inicio = -1;
    calle_destino = -1;
    altos = 0;
}

buscadorRuta::~buscadorRuta() {
}

int buscadorRuta::buscarExhaustiva(int origenA, int origenC, int destinoA, int destinoC) {
    if(origenA == -1 || origenA == 120 || origenC == -1 || origenC == 120){
        return -1;
    }
    if (origenA > destinoA) {
        if (origenC >= destinoC) {
            return buscarNO(origenA, origenC, destinoA, destinoC, 0);
        } else {
            return buscarNE(origenA, origenC, destinoA, destinoC, 0);
        }
    } else {
        if (origenC >= destinoC) {
            return buscarSO(origenA, origenC, destinoA, destinoC, 0);
        } else {
            return buscarSE(origenA, origenC, destinoA, destinoC, 0);
        }
    }
}

int buscadorRuta::buscarNO(int origenA, int origenC, int destinoA, int destinoC, int contador) {
    int contador_local = contador;
    par_ordenado par;
    par.avenida = origenA;
    par.avenida = origenC;
    if (origenA < destinoA || origenC < destinoC) {
        return -1;
    } else {
        if (origenA == destinoA && origenC == destinoC) {
            return 0;
        }
        int mejorValor = -1;
        int temp = -1;
        //int valor1 = vector_coordenada[origenA][origenC][origenA][origenC - 1];
        int valor1;
        int calle;
        int ave;
        for(int i = 1; i < 119; i++){
            if(origenC - i < 0){
                break;
            }
            valor1 = vector_coordenada[origenA][origenC][origenA][origenC - i];
            if(valor1 != -1){
                calle = i;
                break;
            }
        }
        if (valor1 != -1) {
            altos += valor1;
            contador_local++;
            vector_solucion->push_back(par);
            temp = buscarNO(origenA, origenC-calle, destinoA, destinoC, contador_local);
            vector_solucion->pop_back();
            contador_local--;
            altos -= valor1;
            if (temp == -1) {
                valor1 = -1;
            } else {
                valor1 += temp;
            }
        }//REVISAR-----------------------------------------------------------------------
        int valor2 = vector_coordenada[origenA][origenC][origenA - 1][origenC - 1];
        if (valor2 != -1) {
            altos+= valor2;
            contador_local++;
            vector_solucion->push_back(par);
            temp = buscarNO(origenA - 1, origenC - 1, destinoA, destinoC, contador_local);
            vector_solucion->pop_back();
            contador_local--;
            altos-= valor2;
            if (temp == -1) {
                valor2 = -1;
            } else {
                valor2 += temp;
            }
        }
        int valor3 = vector_coordenada[origenA][origenC][origenA - 1][origenC];
        for(int i = 1; i < 120; i++){
            if(origenA - i < 0){
                break;
            }
            valor3 = vector_coordenada[origenA][origenC][origenA-i][origenC];
            if(valor3 != -1){
                ave = i;
                break;
            }
            if(origenA - i < 0){
                break;
            }
        }
        if (valor3 != -1) {
            altos += valor3;
            contador_local++;
            vector_solucion->push_back(par);
            temp = buscarNO(origenA-ave, origenC, destinoA, destinoC, contador++);
            vector_solucion->pop_back();
            contador_local--;
            altos -= valor3;
            if (temp == -1) {
                valor3 = -1;
            } else {
                valor3 += temp;
            }
        }
        if (valor1 != -1) {
            mejorValor = valor1;
        }
        if (valor2 != -1) {
            if (mejorValor == -1 || mejorValor > valor2) {
                mejorValor = valor2;
            }
        }
        if (valor3 != -1) {
            if (mejorValor == -1 || mejorValor > valor3) {
                mejorValor = valor3;
            }
        }
        return mejorValor;
    }
}

int buscadorRuta::buscarNE(int origenA, int origenC, int destinoA, int destinoC, int contador) {
    int contador_local = contador;
    par_ordenado par;
    par.avenida = origenA;
    par.avenida = origenC;
    if (origenA < destinoA || origenC > destinoC) {
        return -1;
    } else {
        if (origenA == destinoA && origenC == destinoC) {
            return 0;
        }
        int mejorValor = -1;
        int temp = -1;
        int valor1;
        int i;
        int calle = 0;
        int ave = 0;
        for(i = 1; i < 120; i++){
            if(origenC + i == 120){
                break;
            }
            valor1 = vector_coordenada[origenA][origenC][origenA][origenC + i];
            if(valor1 != -1){
                calle = i;
                break;
            }

        }
        if (valor1 != -1) {
            contador_local++;
            altos += valor1;
            vector_solucion->push_back(par);
            temp = buscarNE(origenA, origenC+calle, destinoA, destinoC, contador_local);
            vector_solucion->pop_back();
            altos -= valor1;
            contador_local--;
            if (temp == -1) {
                valor1 = -1;
            } else {
                valor1 += temp;
            }
        }
        int valor2;
        for(i = 1; i < 7; i++){
            valor2 = vector_coordenada[origenA][origenC][origenA - i][origenC + i];
            if(valor2 != -1){
                break;
            }
        }
        if (valor2 != -1) {
            contador_local++;
            altos += valor2;
            vector_solucion->push_back(par);
            temp = buscarNE(origenA - 1, origenC +1, destinoA, destinoC, contador_local);
            vector_solucion->pop_back();
            contador_local--;
            altos -= valor2;
            if (temp == -1) {
                valor2 = -1;
            } else {
                valor2 += temp;
            }
        }
        int valor3 = vector_coordenada[origenA][origenC][origenA - 1][origenC];
        for(i = 1; i < 120; i++){
            if(origenA - i < 0){
                break;
            }
            valor3 = vector_coordenada[origenA][origenC][origenA - i][origenC];
            if(valor3 != -1){
                ave = i;
                break;
            }
        }
        if (valor3 != -1) {
            contador_local++;
            altos += valor3;
            vector_solucion->push_back(par);
            temp = buscarNE(origenA - ave, origenC, destinoA, destinoC, contador_local);
            vector_solucion->pop_back();
            altos -= valor3;
            contador_local--;
            if (temp == -1) {
                valor3 = -1;
            } else {
                valor3 += temp;
            }
        }
        if (valor1 != -1) {
            mejorValor = valor1;
        }
        if (valor2 != -1) {
            if (mejorValor == -1 || mejorValor > valor2) {
                mejorValor = valor2;
            }
        }
        if (valor3 != -1) {
            if (mejorValor == -1 || mejorValor > valor3) {
                mejorValor = valor3;
            }
        }
        return mejorValor;
    }
}

int buscadorRuta::buscarSO(int origenA, int origenC, int destinoA, int destinoC,int contador) {
    int contador_local = contador;
    par_ordenado par;
    par.avenida = origenA;
    par.avenida = origenC;
    if (origenA > destinoA || origenC < destinoC) {
        return -1;
    } else {
        if (origenA == destinoA && origenC == destinoC) {
            return 0;
        }
        int mejorValor = -1;
        int temp = -1;
        int i;
        int ave;
        int calle;
        int valor1 = -1;
        for(i = 1; i < 120; i++){
            if(origenC - i < 0){
                break;
            }
            valor1 = vector_coordenada[origenA][origenC][origenA][origenC - i];
            if(valor1 != -1){
                calle = i;
                break;
            }
        }
        if (valor1 != -1) {
            contador_local++;
            altos += valor1;
            temp = buscarSO(origenA, origenC - calle, destinoA, destinoC, contador_local);
            altos -= valor1;
            contador_local--;
            if (temp == -1) {
                valor1 = -1;
            } else {
                valor1 += temp;
            }
        }
        int valor2 = vector_coordenada[origenA][origenC][origenA + 1][origenC - 1];
        if (valor2 != -1) {
            contador_local++;
            altos += valor2;
            temp = buscarSO(origenA + 1, origenC - 1, destinoC, destinoA, contador_local);
            altos -= valor2;
            contador_local--;
            if (temp == -1) {
                valor2 = -1;
            } else {
                valor2 += temp;
            }
        }
        int valor3 = vector_coordenada[origenA][origenC][origenA + 1][origenC];
        for(i = 1; i < 120; i++){
            if(origenA + i == 120){
                break;
            }
            valor3 = vector_coordenada[origenA][origenC][origenA + i][origenC];
            if(valor3 != -1){
                ave = i;
                break;
            }
        }
        if (valor3 != -1) {
            contador_local++;
            altos += valor3;
            temp = buscarSO(origenA + ave, origenC, destinoA, destinoC, contador_local++);
            altos -= valor3;
            contador_local--;
            if (temp == -1) {
                valor3 = -1;
            } else {
                valor3 += temp;
            }
        }
        if (valor1 != -1) {
            mejorValor = valor1;
        }
        if (valor2 != -1) {
            if (mejorValor == -1 || mejorValor > valor2) {
                mejorValor = valor2;
            }
        }
        if (valor3 != -1) {
            if (mejorValor == -1 || mejorValor > valor3) {
                mejorValor = valor3;
            }
        }
        vector_solucion->push_back(par);
        return mejorValor;
    }
}

int buscadorRuta::buscarSE(int origenA, int origenC, int destinoA, int destinoC, int contador) {
    par_ordenado par;
    par.avenida = origenA;
    par.avenida = origenC;
    int contador_local = contador;
    if (origenA > destinoA || origenC > destinoC) {
        return -1;
    } else {
        if (origenA == destinoA && origenC == destinoC) {
            return 0;
        }
        int mejorValor = -1;
        int temp = -1;
        int calle;
        int valor1 = vector_coordenada[origenA][origenC][origenA][origenC + 1];
        for(int i = 1; i < 120; i++){
            if(origenC + i == 120){
                break;
            }
            valor1 = vector_coordenada[origenA][origenC][origenA][origenC + i];
            if(valor1 != -1){
                calle = i;
                break;
            }
        }
        if (valor1 != -1) {
            contador_local++;
            altos += valor1;
            temp = buscarSE(origenA, origenC + calle, destinoA, destinoC, contador_local);
            altos -= valor1;
            contador_local--;
            if (temp == -1) {
                valor1 = -1;
            } else {
                valor1 += temp;
            }
        }
        int valor2 = vector_coordenada[origenA][origenC][origenA + 1][origenC + 1];
        if (valor2 != -1) {
            contador_local++;
            altos += valor2;
            temp = buscarSE(origenA+1, origenC + 1, destinoA, destinoC, contador_local);
            altos -= valor2;
            contador_local--;
            if (temp == -1) {
                valor2 = -1;
            } else {
                valor2 += temp;
            }
        }
        int valor3 = vector_coordenada[origenA][origenC][origenA + 1][origenC];
        int ave;
        for(int i = 1; i < 120; i++){
            if(origenA+i == 120){
                break;
            }
            valor3 = vector_coordenada[origenA][origenC][origenA+i][origenC];
            if(valor3 != -1){
                ave = i;
                break;
            }
        }
        if (valor3 != -1) {
            contador_local++;
            altos += valor3;
            temp = buscarSE(origenA+ ave, origenC, destinoA, destinoC, contador_local);
            altos -= valor3;
            contador_local--;
            if (temp == -1) {
                valor3 = -1;
            } else {
                valor3 += temp;
            }
        }
        if (valor1 != -1) {
            mejorValor = valor1;
        }
        if (valor2 != -1) {
            if (mejorValor == -1 || mejorValor > valor2) {
                mejorValor = valor2;
            }
        }
        if (valor3 != -1) {
            if (mejorValor == -1 || mejorValor > valor3) {
                mejorValor = valor3;
            }
        }
        vector_solucion->push_back(par);
        return mejorValor;
    }

}

std::vector<par_ordenado> *buscadorRuta::getVector_solucion() const {
    return vector_solucion;
}
/**
int buscadorRuta::buscarExhaustiva(int origenC,int origenA, int destinoC, int destinoA) {
    if(origenC == destinoC && origenA == destinoA){
        return 0;
    }else{
    int mejorValor = -1;
    if(origenA > destinoA){ //vamos para arriba
        if(origenC > destinoC){//hacia la izquierda
            int valor1 = vector_coordenada[origenA][origenC][origenA][origenC-1];
            if(valor1 != -1){
                valor1 += buscarExhaustiva(origenC-1, origenA, destinoC, destinoA);
            }
            int valor2 = vector_coordenada[origenA][origenC][origenA-1][origenC-1];
            if(valor2 != -1){
                valor2 += buscarExhaustiva(origenC-1, origenA-1, destinoC, destinoA);
            }
            int valor3 = vector_coordenada[origenA][origenC][origenA-1][origenC];
            if(valor3 != -1){
                valor3 += buscarExhaustiva(origenC, origenA-1, destinoC, destinoA);
            }
            if(valor1 != -1){
                mejorValor = valor1;
            }
            if(valor2 != -1){
                if(mejorValor > valor2){
                    mejorValor = valor2;
                }
            }
            if(valor3 != -1){
                if(mejorValor > valor3){
                    mejorValor = valor3;
                }
            }
        } else{//hacia la derecha
            int valor1 = vector_coordenada[origenA][origenC][origenA][origenC+1];
            if(valor1 != -1){
                valor1 += buscarExhaustiva(origenC+1, origenA, destinoC, destinoA);
            }
            int valor2 = vector_coordenada[origenA][origenC][origenA-1][origenC+1];
            if(valor2 != -1){
                valor2 += buscarExhaustiva(origenC+1, origenA-1, destinoC, destinoA);
            }
            int valor3 = vector_coordenada[origenA][origenC][origenA-1][origenC];
            if(valor3 != -1){
                valor3 += buscarExhaustiva(origenC, origenA-1, destinoC, destinoA);
            }
            if(valor1 != -1){
                mejorValor = valor1;
            }
            if(valor2 != -1){
                if(mejorValor > valor2){
                    mejorValor = valor2;
                }
            }
            if(valor3 != -1){
                if(mejorValor > valor3){
                    mejorValor = valor3;
                }
            }
        }
    } else{ //vamos para abajo
        if(origenC > destinoC){//hacia la izq
            int valor1 = vector_coordenada[origenA][origenC][origenA][origenC-1];
            if(valor1 != -1){
                valor1 += buscarExhaustiva(origenC-1, origenA, destinoC, destinoA);
            }
            int valor2 = vector_coordenada[origenA][origenC][origenA+1][origenC-1];
            if(valor2 != -1){
                valor2 += buscarExhaustiva(origenC-1, origenA+1, destinoC, destinoA);
            }
            int valor3 = vector_coordenada[origenA][origenC][origenA+1][origenC];
            if(valor3 != -1){
                valor3 += buscarExhaustiva(origenC, origenA+1, destinoC, destinoA);
            }
            if(valor1 != -1){
                mejorValor = valor1;
            }
            if(valor2 != -1){
                if(mejorValor > valor2){
                    mejorValor = valor2;
                }
            }
            if(valor3 != -1){
                if(mejorValor > valor3){
                    mejorValor = valor3;
                }
            }
        } else{// hacia la derecha
            int valor1 = vector_coordenada[origenA][origenC][origenA][origenC+1];
            if(valor1 != -1){
                valor1 += buscarExhaustiva(origenC+1, origenA, destinoC, destinoA);
            }
            int valor2 = vector_coordenada[origenA][origenC][origenA+1][origenC+1];
            if(valor2 != -1){
                valor2 += buscarExhaustiva(origenC+1, origenA+1, destinoC, destinoA);
            }
            int valor3 = vector_coordenada[origenA][origenC][origenA+1][origenC];
            if(valor3 != -1){
                valor3 += buscarExhaustiva(origenC, origenA+1, destinoC, destinoA);
            }
            if(valor1 != -1){
                mejorValor = valor1;
            }
            if(valor2 != -1){
                if(mejorValor > valor2){
                    mejorValor = valor2;
                }
            }
            if(valor3 != -1){
                if(mejorValor > valor3){
                    mejorValor = valor3;
                }
            }
        }
    }
    return mejorValor;
    }
}
 */

/*
 * Lee una coordenada para la partida y otra para la meta.
 * Para reconocer en cuál posición del vector, acorde al número que se dé:
 * Se multiplica por 3.  Luego, si es calle se suma 3, si no, así queda.
 * Por ejemplo:
 * C23 -> (23*3)+3 = 72.  Eso quiere decir que C23 corresponde a la posición 72 en el vector.
 * A38 -> (38*3) = 114.  A38 corresponde a la posición 114 en el vector.
 *
 * Hay una excepción: C0, el cual siempre va a ser 0.
 */
void buscadorRuta::leer_inicio_meta() {
    std::string coordenada;

    std::cout << "Coordenadas de inicio: " << std::endl;
    std::getline(std::cin, coordenada);

    if (coordenada.empty() == false) // Si se digitó algo
    {
        procesar_coordenada(coordenada, false); // Procesar la coordenada inicial.
    }

    std::cout << "Coordenadas del destino: " << std::endl;
    std::getline(std::cin, coordenada);

    if (coordenada.empty() == false) // Si se digitó algo
    {
        procesar_coordenada(coordenada, true); // Procesar la coordenada del destino..
    }
}

// Tiene que tener el formato (x, y)
// destino es para saber qué variables voy a modificar, si es false, modifico las de inicio.
void buscadorRuta::procesar_coordenada(std::string par_ordenado, bool destino) {
    // Elemento de 4 espacios y un fin de caracter.
    std::string elemento = "    \0";

    size_t contador_elemento = 0;
    size_t contador = 1; // Para evitar el paréntesis.

    while (contador < par_ordenado.size()) // -1 para evitar el paréntesis.
    {
        // Si se está en una coma o en la última posición de coordenada.
        if (par_ordenado[contador] == ',' || contador == (par_ordenado.size() - 1)) {
            // Hay un/a calle/avenida para procesar.
            elemento[contador_elemento] = '\0'; // Finalizo la hilera.

            asignar_valor_coordenadas( coordenada->procesar_calle_avenida(elemento), destino, elemento[0]);
            contador_elemento = 0; // Restauro valor.
            ++contador; // Me muevo para omitir la coma y el espacio que hay después.
            // (el espacio se omite con el contador que hay fuera del if).
        } else {
            elemento[contador_elemento] = par_ordenado[contador]; // Sigo copiando a elemento.
            ++contador_elemento;
        }

        ++contador;
    }
}

void buscadorRuta::asignar_valor_coordenadas(int posicion, bool destino, char tipo  ) {
    if (destino == false) {
        if (tipo == 'A' || tipo == 'D') {
            avenida_inicio = posicion;
        } else {
            calle_inicio = posicion;
        }
    } else {
        if (tipo == 'A' || tipo == 'D') {
            avenida_destino = posicion;
        } else {
            calle_destino = posicion;
        }
    }
}
