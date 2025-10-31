/*
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

    // Variables costos entre routers
    int AB, AC, AD, BC, BD, CD;

    // Leer los datos
    entrada >> AB >> AC >> AD >> BC >> BD >> CD;

    if (entrada.fail()) {
        cout << "Error al leer los datos del archivo.\n";
        return 1;
    }

    cout << "\nCalculando caminos más cortos \n";

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
    cout << "Camino más corto A a C = " << costoA_C << endl;
    cout << "Camino más corto B a D = " << costoB_D << endl;
    cout << "Camino más corto A a B = " << costoA_B << endl;
    cout << "Camino más corto C a D = " << costoC_D << endl;

    // Guardar resultados en el archivo de salida
    salida << "Camino más corto A a C = " << costoA_C << "\n";
    salida << "Camino más corto B a D = " << costoB_D << "\n";
    salida << "Camino más corto A a B = " << costoA_B << "\n";
    salida << "Camino más corto C a D = " << costoC_D << "\n";

    entrada.close();
    salida.close();

    cout << "\nResultados guardados en " << nombreSalida << endl;
    return 0;
}
*/


#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <limits>
#include <algorithm>
using namespace std;

class Red {
private:
    map<string, map<string, int>> costos; // costos[A][B] = costo de A a B
    const int INF = numeric_limits<int>::max();

public:
    // Cargar red desde archivo tipo: A,B,3
    bool cargarDesdeArchivo(string nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "Error al abrir el archivo.\n";
            return false;
        }

        string origen, destino;
        int costo;
        char coma1, coma2;

        // Lee línea por línea con formato A,B,5
        while (archivo >> origen >> coma1 >> destino >> coma2 >> costo) {
            if (coma1 != ',' || coma2 != ',') {
                cout << "Error: formato inválido en el archivo.\n";
                return false;
            }

            costos[origen][destino] = costo;
            costos[destino][origen] = costo;
        }

        archivo.close();
        return true;
    }

    // Algoritmo de Floyd–Warshall para caminos mínimos
    map<string, map<string, int>> calcularCaminos() {
        set<string> nodos;
        for (auto p : costos)
            nodos.insert(p.first);

        map<string, map<string, int>> dist;

        // Inicializar distancias
        for (auto i : nodos) {
            for (auto j : nodos) {
                if (i == j)
                    dist[i][j] = 0;
                else if (costos[i].count(j))
                    dist[i][j] = costos[i][j];
                else
                    dist[i][j] = INF;
            }
        }

        // 🔧 Aquí estaba el error: antes tenías este bloque fuera de la clase o duplicado.
        // Lo movemos aquí dentro correctamente:
        for (auto k : nodos) {
            for (auto i : nodos) {
                for (auto j : nodos) {
                    if (dist[i][k] != INF && dist[k][j] != INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        return dist;
    }

    // ✅ Ahora esta función está dentro de la clase y definida solo una vez.
    void mostrarCaminos(map<string, map<string, int>> dist) {
        cout << "\nTabla de costos mínimos:\n";

        for (auto &i : dist) {  // i = router origen
            for (auto &j : i.second) {  // j = router destino
                if (i.first != j.first) {
                    cout << "De " << i.first << " a " << j.first << " = ";
                    if (j.second == INF)
                        cout << "INF";
                    else
                        cout << j.second;
                    cout << endl;
                }
            }
        }
    }

    void guardarResultados(map<string, map<string, int>> dist, string nombreSalida) {
        ofstream salida(nombreSalida);
        if (!salida.is_open()) {
            cout << "Error al abrir el archivo de salida.\n";
            return;
        }

        salida << "Tabla de costos mínimos entre routers:\n";

        for (auto &i : dist) {
            for (auto &j : i.second) {
                if (i.first != j.first) {
                    salida << "De " << i.first << " a " << j.first << " = ";
                    if (j.second == INF)
                        salida << "INF";
                    else
                        salida << j.second;
                    salida << "\n";
                }
            }
        }

        salida.close();
        cout << "\nResultados guardados correctamente en " << nombreSalida << endl;
    }
};


int main() {
    Red red;
    string entrada, salida;

    cout << "Ingrese el nombre del archivo de entrada: ";
    cin >> entrada;
    cout << "Ingrese el nombre del archivo de salida: ";
    cin >> salida;

    if (!red.cargarDesdeArchivo(entrada)) return 1;

    cout << "\nCalculando caminos más cortos...\n";
    auto dist = red.calcularCaminos();

    red.mostrarCaminos(dist);
    red.guardarResultados(dist, salida);

    return 0;
}
