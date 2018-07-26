#include <iostream>
#include <vector>

#include "coordenadas.h"
#include "buscadorRuta.h"


int main()
{

    buscadorRuta* buscador = new buscadorRuta();
    Coordenadas * ce = new Coordenadas();
    int x = ce->procesar_calle_avenida("A22a");
    clock_t start = clock();
    int a = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A22a"),ce->procesar_calle_avenida("C5"),ce->procesar_calle_avenida("A2"),ce->procesar_calle_avenida("C35"));
    clock_t end = clock();
    double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    start = clock();
    int b = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A28"),ce->procesar_calle_avenida("C5b"),ce->procesar_calle_avenida("A38"),ce->procesar_calle_avenida("T13"));
    end = clock();
    double tiempo = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    int c = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A14"),ce->procesar_calle_avenida("C3"),ce->procesar_calle_avenida("A22"),ce->procesar_calle_avenida("C9"));
    int d = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A34"),ce->procesar_calle_avenida("C11"),ce->procesar_calle_avenida("A10"),ce->procesar_calle_avenida("C25a"));
    int e = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A2"),ce->procesar_calle_avenida("C1"),ce->procesar_calle_avenida("A34"),ce->procesar_calle_avenida("C11"));
    int f = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A28"),ce->procesar_calle_avenida("C5"),ce->procesar_calle_avenida("A2"),ce->procesar_calle_avenida("C0"));
    int g = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A0"),ce->procesar_calle_avenida("C21"),ce->procesar_calle_avenida("A12"),ce->procesar_calle_avenida("C5"));
    int h = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A22a"), ce->procesar_calle_avenida("C5"), ce->procesar_calle_avenida("A18"), ce->procesar_calle_avenida("C13"));
    int i = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A8"), ce->procesar_calle_avenida("C15"), ce->procesar_calle_avenida("A16"), ce->procesar_calle_avenida("C0"));
    int j = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A2"), ce->procesar_calle_avenida("C1"), ce->procesar_calle_avenida("A14"), ce->procesar_calle_avenida("C9"));
    int k = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A2"), ce->procesar_calle_avenida("C1"), ce->procesar_calle_avenida("A38"), ce->procesar_calle_avenida("C21"));
    int l = buscador->buscarExhaustiva(ce->procesar_calle_avenida("A30"), ce->procesar_calle_avenida("C1"), ce->procesar_calle_avenida("A2"), ce->procesar_calle_avenida("C35"));
    int m = buscador->buscarExhaustiva(ce->procesar_calle_avenida("a34"), ce->procesar_calle_avenida("C11"), ce->procesar_calle_avenida("A38"), ce->procesar_calle_avenida("C17a"));
    while( true )
    {
        buscador->leer_inicio_meta();
        std::cout << "(" << buscador->avenida_inicio << ", " << buscador->calle_inicio << ")\n";
        std::cout << "(" << buscador->avenida_destino << ", " << buscador->calle_destino << ")\n";

        //Variables globales asignadas, hacer llamado a búsqueda exhaustiva.
    }
    return 0;
}
