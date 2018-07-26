#include "coordenadas.h"

Coordenadas::Coordenadas()
{
    controlador_coordenadas();
}

Coordenadas::~Coordenadas()
{

}

vector4_char Coordenadas::get_vector_coordenadas()
{
    return vector_coordenadas;
}

void Coordenadas::controlador_coordenadas()
{
    dimensionar_vector();
    llenar_vector();

    // Para efectos de esta tarea, solo se va a necesitar las hojas de "Altos y reductores".
    // Leo los del archivos respectivos.  OJO, ruta NO general, hay que especificar la ruta junto con los nombres.

    leer_archivos("C:\\Users\\defaultuser\\Desktop\\Altos y reductores - N.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - Navenida.csv");

    leer_archivos("C:\\Users\\defaultuser\\Desktop\\Altos y reductores - S.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - Savenida.csv");

    leer_archivos("C:\\Users\\defaultuser\\Desktop\\Altos y reductores - E.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - Ecalle.csv");

    leer_archivos("C:\\Users\\defaultuser\\Desktop\\Altos y reductores - O.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - Ocalle.csv");

    leer_archivos("C:\\Users\\defaultuser\\Desktop\\Altos y reductores - NE.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - NEavenida.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - NEcalle.csv");

    leer_archivos("C:\\Users\\defaultuser\\Desktop\\Altos y reductores - SE.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - SEavenida.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - SEcalle.csv");

    leer_archivos("C:\\Users\\defaultuser\\Desktop\\Altos y reductores - NO.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - NOavenida.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - NOcalle.csv");

    leer_archivos("C:\\Users\\defaultuser\\Desktop\\Altos y reductores - SO.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - SOavenida.csv",
                  "C:\\Users\\defaultuser\\Desktop\\Intersecciones aledannas - SOcalle.csv");
}

/*
 * Función que procesa un string para poder asignarle valores al vector coordenadas.
 * Por parámetro recibe el string de la línea del archivo.
 * Además del número de fila, donde se encuentra (se asume que al inicio debería de pasar un 0).
 * linea_direcciones tiene la información de hacia donde dónde están los destinos, es decir, dondé asignar los valores
 * correspondientes.
 * Note que si NO existe el archivo para diagonales, el contador es un -1.
 * ToDo: manejar las líneas de destino y las hipotéticas diagonales.
 */
void Coordenadas::procesar_linea( size_t avenida, std::string linea_valores, std::string linea_direcciones, std::string linea_diagonales )
{
    // Lo que hay que restar para poder asignar el vector desde 0.
    size_t contador_calles = 0;

    // Estos contadores se irán moviendo de manera sincronizada.
    size_t contador_linea_valores = retornar_tercer_cuadro(linea_valores); // Variable para recorrer línea.
    size_t contador_linea_direcciones = retornar_tercer_cuadro(linea_direcciones);
    size_t contador_linea_diagonales = retornar_tercer_cuadro(linea_diagonales);

    char numero_string[] = "       "; // Se asume que por cuadro hay pocos caracteres.

    size_t contador_numero = 0;
    int numero_recibido = 0;

    // Para guardar las coordenadas necesarias para asignar los valores.
    std::string coordenada_destino("      ");
    std::string coordenada_diagonal("      ");

    // Para moverme en los strings.
    size_t contador_string_destino = 0;
    size_t contador_string_diagonal = 0;

    while( contador_calles < CALLES ) // Note que linea.size() incluye el último cuadro, que no debe de ser incluido en el vector.
    {
        if( linea_valores[contador_linea_valores] != ',' )
        {
            // Si hay un valor, necesito procesar cuál es la coordenada destino.

            do // Ciclo para recorrer el string linea_valores
            {
                numero_string[contador_numero] = linea_valores[contador_linea_valores];
                ++contador_linea_valores;
                ++contador_numero;

            }while( linea_valores[contador_linea_valores] != ',' && contador_linea_valores < linea_valores.size() );
            numero_string[contador_numero] = '\0'; // Agregar fin de línea para atoi.
            // Convierto el número recibido.
            numero_recibido = atoi(numero_string);


            // Para guardar la coodenada de direccion, DEBE de existir. DIRECCIONES
            do
            {
                coordenada_destino[contador_string_destino] = linea_direcciones[contador_linea_direcciones];
                ++contador_string_destino;
                ++contador_linea_direcciones;

            }while( linea_direcciones[contador_linea_direcciones] != ',' && contador_linea_direcciones < linea_direcciones.size() );
            coordenada_destino[contador_string_destino] = '\0';

            // La coodenada diagonal PUEDE O NO que exista, por lo que se verifica de primero.
            // NOTA: se hicieron los ciclos por separado ya que puede que las coodenadas sean de distinto tamaño
            // por lo que puede crear conflicto, además de que son ciclos pequeños, no afectan la eficiencia.
            // DIAGONALES
            while( contador_linea_diagonales < linea_diagonales.size() && linea_diagonales[contador_linea_diagonales] != ',' )
            {
                coordenada_diagonal[contador_string_diagonal] = linea_diagonales[contador_linea_diagonales];
                ++contador_string_diagonal;
                ++contador_linea_diagonales;
            }
            coordenada_diagonal[contador_string_diagonal] = '\0';

            // Asigno valor al vector_coordenadas
            asginar_valor_vector_coordenadas(numero_recibido, avenida, contador_calles, coordenada_destino, coordenada_diagonal );

            // Restauro valores.
            contador_numero = 0;
            contador_string_destino = 0;
            contador_string_diagonal = 0;
        }
        ++contador_calles; // Cada vez que se pasa una coma, se está recorriendo una calle.
        ++contador_linea_valores;
        ++contador_linea_diagonales;
        ++contador_linea_direcciones;
    }
}

/*
 * Direcciones:
 * 0: Norte
 * 1: Sur
 * 2: Este
 * 3: Oeste
 * 4: Noreste
 * 5: Sureste
 * 6: Noroeste
 * 7: Suroeste
 *
 * ERROR: especialmente en este y oeste, no es correcto asignar valores solo sumando 1 unidad, ya que, por ejemplo, para
 * pasar de C3 a C5 es pasar en enteros de 12 a 18, por lo que en este caso NO hay que sumar una unidad.
 *
 * Parámetros:
 * valor es el número que se la va a asignar al vector.
 * coodenada_destino se usa para saber dónde se le asigna valor.
 * coodenada_diagonal es opcional, en caso de que haya que moverse en una diagonal.
 *
 * ToDo: procesar los string.
 */
void Coordenadas::asginar_valor_vector_coordenadas(int valor, size_t avenida_inicio, size_t calle_inicio,
                                                   std::string coordenada_destino, std::string coordenada_diagonal)
{
    // Puede que alguna de estos valores no tengan que ser modificados
    size_t avenida_destino = avenida_inicio;
    size_t calle_destino = calle_inicio;

    int posicion = procesar_calle_avenida(coordenada_destino);
    int diagonal = procesar_calle_avenida(coordenada_diagonal); // Retorna -1 en caso de diagonal inexistente.

    if( coordenada_destino[0] == 'T' || coordenada_destino[0] == 'C' )
    {
        calle_destino = posicion;
        if( diagonal != -1 )
            avenida_destino = diagonal;
    }
    else
    {
        avenida_destino = posicion;
        if( diagonal != -1 )
            calle_destino = diagonal;
    }

    vector_coordenadas[avenida_inicio][calle_inicio][avenida_destino][calle_destino] =  valor;
}

/*
 * Leer un archivo, el cual el nombre se pasa por parámetro.
 * Luego de leer la línea, asigna los valores respectivos al vector coordenadas.
 * Note que con el nombre se tiene que pasar con la extensión, en este caso, .csv
 * Puede que se tenga que poner la ruta del archivo.
 * También lee el archivo de las direcciones.  Igual las procesa.
 * El archivo diagonal es opcional, en caso de que exista se tiene que tratar dos archivos simultáneos de diagonales.
 * Si no existe, el string es un "", para reconocer cuando no existe:
 * if( nombre_archivo_diagonal.compare("") == 0 )
 */
void Coordenadas::leer_archivos(const std::string nombre_archivo_valores, const std::string nombre_archivo_direcciones,
                                std::string nombre_archivo_diagonales)
{
    std::ifstream archivo_valores(nombre_archivo_valores.data());
    std::ifstream archivo_direcciones(nombre_archivo_direcciones.data());
    std::ifstream archivo_diagonales(nombre_archivo_diagonales.data());

    std::string linea_valores;
    std::string linea_direcciones;
    std::string linea_diagonales;

    size_t posicion_fila = 0;

    if( archivo_valores.is_open() == true ) // Si se abrió correctamente el archivo.
    {
        if( archivo_direcciones.is_open() == true )
        {
            // Si el archivo de diagonales se abrió o si NO existe.
            if( archivo_diagonales.is_open() == true || nombre_archivo_diagonales.compare("") == 0 )
            {

                // Empezar a leer desde la tercera línea.
                for( int contador = 1; contador < 3; ++contador )
                {
                    std::getline(archivo_valores, linea_valores);
                    std::getline(archivo_direcciones, linea_direcciones);
                    std::getline(archivo_diagonales, linea_diagonales);
                }

                // Mientras no haya llegado al final del archivo y no se haya superado la cantidad de filas requerida.
                while( archivo_valores.eof() == false && posicion_fila < AVENIDAS )
                {
                    std::getline(archivo_valores, linea_valores); // Lee una línea del archivo de valores.
                    std::getline(archivo_direcciones, linea_direcciones); // Lee una línea del archivo de valores.
                    std::getline(archivo_diagonales, linea_diagonales); // En caso de que no exista el archivo, el string es "".

                    procesar_linea(posicion_fila, linea_valores, linea_direcciones, linea_diagonales);
                    ++posicion_fila;

#if DEBUG
                    std::cout << linea << std::endl;
#endif
                }
            }
            else
            {
                std::cerr << "Error al abrir " << nombre_archivo_diagonales << std::endl;
            }
        }
        else
        {
            std::cerr << "Error al abrir " << nombre_archivo_direcciones << std::endl;
        }
    }
    else
    {
        std::cerr << "Error al abrir " << nombre_archivo_valores << std::endl;
    }

    // Cerrar los archivos, obligatorio en todo caso.
    archivo_valores.close();
    archivo_direcciones.close();
    archivo_diagonales.close();
}

// Llena el vector de -1's
void Coordenadas::llenar_vector()
{
    for( size_t contador_avenidas_partida = 0; contador_avenidas_partida < AVENIDAS; ++contador_avenidas_partida )
        for( size_t contador_calles_partida = 0; contador_calles_partida < CALLES; ++contador_calles_partida )
            for( size_t contador_avenidas_meta = 0; contador_avenidas_meta < AVENIDAS; ++contador_avenidas_meta )
                for( size_t contador_calles_meta = 0; contador_calles_meta < CALLES; ++contador_calles_meta )
                    vector_coordenadas[contador_avenidas_partida][contador_calles_partida][contador_avenidas_meta][contador_calles_meta] = -1;
}

void Coordenadas::dimensionar_vector()
{
    vector_coordenadas.resize(AVENIDAS);

    for( size_t contador_avenidas = 0; contador_avenidas < AVENIDAS; ++contador_avenidas )
        vector_coordenadas[contador_avenidas].resize(CALLES);

    for( size_t contador_avenidas = 0; contador_avenidas < AVENIDAS; ++contador_avenidas )
        for( size_t contador_calles = 0; contador_calles < CALLES; ++contador_calles )
            vector_coordenadas[contador_avenidas][contador_calles].resize(AVENIDAS);

    for( size_t contador_avenidas = 0; contador_avenidas < AVENIDAS; ++contador_avenidas )
        for( size_t contador_calles = 0; contador_calles < CALLES; ++contador_calles )
            for( size_t contador_avenidas_meta = 0; contador_avenidas_meta < AVENIDAS; ++contador_avenidas_meta )
                vector_coordenadas[contador_avenidas][contador_calles][contador_avenidas_meta].resize(CALLES);
}

// Retorna el contador al inicio del tercer cuadro.
size_t Coordenadas::retornar_tercer_cuadro(const std::string linea) const
{
    size_t contador = 0;
    int contador_comas = 0;

    // Buscar la segunda coma.  Después de la seguna coma es el inicio del tercer cuadro.
    while( contador < linea.size() && contador_comas < 2  )
    {
        if( linea[contador] == ',' ) // Si no es coma,
        {
            ++contador_comas;
        }
        ++contador;
    }
    return contador;
}

// Se asume que elemento tiene fin de hilera.
int Coordenadas::procesar_calle_avenida(std::string elemento)
{
    char tipo = elemento[0]; // Para saber si es avenida o calle.
    if( tipo == '\0' ) // ¿Coordenada vacía?
        return -1;

    char numero[] = "     "; //El número no debería de ser más de 2 dígitos.
    int posicion = -1; // La posición que se va a asignar en la variable local respectiva.

    size_t contador_numero = 0;
    size_t contador_elemento = 1; // Se empieza en 1, porque ya se verificó tipo.
    std::locale loc; // Para el isdigit

    while (elemento[contador_elemento] != '\0' && std::isdigit(elemento[contador_elemento], loc) == true)
    {
        numero[contador_numero] = elemento[contador_elemento];
        ++contador_elemento;
        ++contador_numero;
    }

    posicion = atoi(numero); // Convierto numero en int.
    posicion *= 3;

    if (posicion != 0)
    {
        if (tipo == 'C' || tipo == 'T')
        {
            posicion += 3; // Por definición.
        }
    }

    // Note que si posicion = 0, los siguientes if sí van acorde a lo que se requiere.

    if (tipo == 'T' || tipo == 'D')
    {
        posicion += 3; // Al ser diagonal o transversal me tengo que mover 3 más.
    }

    if (elemento[contador_elemento] != '\0') // Si hay una a, b
    {
        if (elemento[contador_elemento] == 'a')
        {
            ++posicion;
        } else {
            posicion += 2;
        }
    }
    return posicion;
}
