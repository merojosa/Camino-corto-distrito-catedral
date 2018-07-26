#ifndef COORDENADAS_H
#define COORDENADAS_H


#define CALLES 120
#define AVENIDAS 120

#define DEBUG 0 // Si DEBUG es 1, se está depurando, si 0, no (se omite o no código).

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>

// Vector de 4 dimensiones de char.
typedef std::vector< std::vector< std::vector< std::vector<char> > > > vector4_char;

class Coordenadas
{
    public:
        Coordenadas();
        ~Coordenadas();

        vector4_char get_vector_coordenadas();

        int procesar_calle_avenida(std::string elemento);

        // Para no gastar la memoria del segmento de datos.
    private:
        vector4_char vector_coordenadas;

    protected:
        void controlador_coordenadas();
        void dimensionar_vector();
        void llenar_vector();

        void leer_archivos(const std::string nombre_archivo_valores , const std::string nombre_archivo_direcciones,
                           std::string nombre_archivo_diagonales = "");

        void procesar_linea(size_t avenida, std::string linea_valores, std::string linea_direcciones, std::string linea_diagonales);

        void asginar_valor_vector_coordenadas(int valor, size_t avenida_inicio, size_t calle_inicio, std::string coordenada_destino, std::string coordenada_diagonal);

        size_t retornar_tercer_cuadro( const std::string linea ) const;
};

#endif // COORDENADAS_H
