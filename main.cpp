/*
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int AB, AC, AD, BC, BD, CD;
    cout << "Ingrese los costos de enlace entre los routers:\n";
    cout << "A-B: "; cin >> AB;
    cout << "A-C: "; cin >> AC;
    cout << "A-D: "; cin >> AD;
    cout << "B-C: "; cin >> BC;
    cout << "B-D: "; cin >> BD;
    cout << "C-D: "; cin >> CD;

    cout << "\nCalculando caminos mas cortos\n";

    int costoA_C1 = AC;
    int costoA_C2 = AB + BC;          // A a B a C
    int costoA_C3 = AD + CD;          // A a D a C
    int costoA_C = min({costoA_C1, costoA_C2, costoA_C3});

    cout << "Camino mas corto A a C = " << costoA_C << endl;

    int costoB_D1 = BD;
    int costoB_D2 = BC + CD;          // B a C a D
    int costoB_D3 = AB + AD;          // B a A a D
    int costoB_D = min({costoB_D1, costoB_D2, costoB_D3});

    cout << "Camino mas corto B a D = " << costoB_D << endl;

    int costoA_B1 = AB;
    int costoA_B2 = AC + BC;
    int costoA_B3 = AD + BD;
    int costoA_B = min({costoA_B1, costoA_B2, costoA_B3});

    cout << "Camino mas corto A a B = " << costoA_B << endl;

    int costoC_D1 = CD;
    int costoC_D2 = BC + BD;
    int costoC_D3 = AC + AD;
    int costoC_D = min({costoC_D1, costoC_D2, costoC_D3});

    cout << "Camino mas corto C a D = " << costoC_D << endl;

    return 0;
}
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
    string nombreEntrada, nombreSalida;
    cout << "Por favor cree un archivo con 6 numeros para saber el costo entre routers, \nluego porfavor Ingrese el nombre del archivo de entrada: ";
    cin >> nombreEntrada;
    cout << "Ingrese el nombre del archivo de salida: ";
    cin >> nombreSalida;

    ifstream entrada(nombreEntrada, ios::binary);
    ofstream salida(nombreSalida, ios::binary);

    if (!entrada.is_open() || !salida.is_open()) {
        cout << "Error al abrir los archivos.\n";
        return 1;
    }

    // Variables para los costos entre routers
    int AB, AC, AD, BC, BD, CD;
    unsigned char c;

    // Leer datos del archivo de entrada
    entrada >> AB >> AC >> AD >> BC >> BD >> CD;

    if (entrada.fail()) {
        cout << "Error al leer los datos del archivo.\n";
        return 1;
    }

    cout << "\nCalculando caminos más cortos (sin Dijkstra)...\n";

    int costoA_C1 = AC;
    int costoA_C2 = AB + BC;          // A a B a C
    int costoA_C3 = AD + CD;          // A a D a C
    int costoA_C = min({costoA_C1, costoA_C2, costoA_C3});

    cout << "Camino mas corto A a C = " << costoA_C << endl;

    int costoB_D1 = BD;
    int costoB_D2 = BC + CD;          // B a C a D
    int costoB_D3 = AB + AD;          // B a A a D
    int costoB_D = min({costoB_D1, costoB_D2, costoB_D3});

    cout << "Camino mas corto B a D = " << costoB_D << endl;

    int costoA_B1 = AB;
    int costoA_B2 = AC + BC;
    int costoA_B3 = AD + BD;
    int costoA_B = min({costoA_B1, costoA_B2, costoA_B3});

    cout << "Camino mas corto A a B = " << costoA_B << endl;

    int costoC_D1 = CD;
    int costoC_D2 = BC + BD;
    int costoC_D3 = AC + AD;
    int costoC_D = min({costoC_D1, costoC_D2, costoC_D3});


    // Mostrar resultados en pantalla
    cout << "Camino más corto A → C = " << costoA_C << endl;
    cout << "Camino más corto B → D = " << costoB_D << endl;
    cout << "Camino más corto A → B = " << costoA_B << endl;
    cout << "Camino más corto C → D = " << costoC_D << endl;

    // Guardar resultados en el archivo de salida
    salida << "Camino más corto A → C = " << costoA_C << "\n";
    salida << "Camino más corto B → D = " << costoB_D << "\n";
    salida << "Camino más corto A → B = " << costoA_B << "\n";
    salida << "Camino más corto C → D = " << costoC_D << "\n";

    entrada.close();
    salida.close();

    cout << "\nResultados guardados en " << nombreSalida << endl;
    return 0;
}
