#include <iostream>
#include <fstream>
#include <string>
#include <climits>
using namespace std;
 
// =====================================================
// CONSTANTES
// =====================================================
#define MAX_NODOS 50          // Máximo de nodos en el grafo
#define ARCHIVO_DATOS "datos_energia.txt"
 
// =====================================================
// PASO 1: ESTRUCTURAS DE DATOS
// =====================================================
 
// Tipos de nodo
#define TIPO_HIDROELECTRICA  1
#define TIPO_TERMOELECTRICA  2
#define TIPO_SOLAR           3
#define TIPO_EOLICA          4
#define TIPO_CIUDAD          5
 
struct Transaccion {
    int anio;
    int mes;
    double monto;       // en millones de pesos
    double energiaMWh;  // energía en MWh
};
 
struct Nodo {
    int id;
    char nombre[50];
    int tipo;               // TIPO_HIDROELECTRICA, TIPO_CIUDAD, etc.
    int activo;             // 1 = activo, 0 = desactivado
    double capacidadMW;     // capacidad en megavatios
    double consumoMWh;      // consumo/generación en MWh
    double costoBase;       // costo base en millones de pesos
    int anioRegistro;
    int mesRegistro;
    Transaccion transacciones[100];
    int numTransacciones;
};
 
struct Arista {
    int activa;             // 1 = activa, 0 = no existe conexión
    double costoTransmision; // costo en millones de pesos por MWh
    double capacidadMW;     // capacidad máxima de la línea
    double perdidas;        // % de pérdidas en transmisión
    int anio;
};
 
struct Grafo {
    Nodo nodos[MAX_NODOS];
    Arista matriz[MAX_NODOS][MAX_NODOS]; // Matriz de adyacencia
    int numNodos;
};
 
// =====================================================
// PASO 2: FUNCIONES AUXILIARES
// =====================================================
 
void limpiarPantalla() {
    cout << "\n========================================\n";
}
 
const char* nombreTipo(int tipo) {
    if (tipo == TIPO_HIDROELECTRICA) return "Hidroeléctrica";
    if (tipo == TIPO_TERMOELECTRICA) return "Termoeléctrica";
    if (tipo == TIPO_SOLAR)          return "Solar";
    if (tipo == TIPO_EOLICA)         return "Eólica";
    if (tipo == TIPO_CIUDAD)         return "Ciudad";
    return "Desconocido";
}
 
// =====================================================
// PASO 3: CREACIÓN E INICIALIZACIÓN
// =====================================================
 
void inicializarGrafo(Grafo &g) {
    g.numNodos = 0;
    for (int i = 0; i < MAX_NODOS; i++) {
        g.nodos[i].activo = 0;
        for (int j = 0; j < MAX_NODOS; j++) {
            g.matriz[i][j].activa = 0;
            g.matriz[i][j].costoTransmision = 0;
            g.matriz[i][j].capacidadMW = 0;
            g.matriz[i][j].perdidas = 0;
        }
    }
    cout << "[OK] Grafo inicializado.\n";
}
 
// =====================================================
// PASO 4: INCLUSIÓN (Agregar nodos y aristas)
// =====================================================
 
int agregarNodo(Grafo &g) {
    if (g.numNodos >= MAX_NODOS) {
        cout << "[ERROR] Grafo lleno.\n";
        return -1;
    }
 
    int id = g.numNodos;
    Nodo &n = g.nodos[id];
 
    cout << "\n--- AGREGAR NODO ---\n";
    cout << "Nombre: ";
    cin.ignore();
    cin.getline(n.nombre, 50);
 
    cout << "Tipo (1=Hidroeléctrica, 2=Termoeléctrica, 3=Solar, 4=Eólica, 5=Ciudad): ";
    cin >> n.tipo;
 
    cout << "Capacidad (MW): ";
    cin >> n.capacidadMW;
 
    cout << "Consumo/Generación (MWh): ";
    cin >> n.consumoMWh;
 
    cout << "Costo base (millones COP): ";
    cin >> n.costoBase;
 
    cout << "Año de registro: ";
    cin >> n.anioRegistro;
 
    cout << "Mes de registro (1-12): ";
    cin >> n.mesRegistro;
 
    n.id = id;
    n.activo = 1;
    n.numTransacciones = 0;
 
    g.numNodos++;
    cout << "[OK] Nodo '" << n.nombre << "' agregado con ID " << id << ".\n";
    return id;
}
 
void agregarArista(Grafo &g) {
    if (g.numNodos < 2) {
        cout << "[ERROR] Se necesitan al menos 2 nodos.\n";
        return;
    }
 
    int origen, destino;
    cout << "\n--- AGREGAR CONEXIÓN (ARISTA) ---\n";
    cout << "ID nodo origen: ";  cin >> origen;
    cout << "ID nodo destino: "; cin >> destino;
 
    if (origen < 0 || origen >= g.numNodos || destino < 0 || destino >= g.numNodos) {
        cout << "[ERROR] IDs inválidos.\n";
        return;
    }
 
    Arista &a = g.matriz[origen][destino];
    cout << "Costo de transmisión (millones COP/MWh): ";
    cin >> a.costoTransmision;
    cout << "Capacidad de la línea (MW): ";
    cin >> a.capacidadMW;
    cout << "% de pérdidas: ";
    cin >> a.perdidas;
    cout << "Año de instalación: ";
    cin >> a.anio;
 
    a.activa = 1;
    // Grafo no dirigido: la conexión es bidireccional
    g.matriz[destino][origen] = a;
 
    cout << "[OK] Conexión entre '" << g.nodos[origen].nombre
         << "' y '" << g.nodos[destino].nombre << "' creada.\n";
}
 
// =====================================================
// PASO 5: ELIMINACIÓN Y DESACTIVACIÓN
// =====================================================
 
void eliminarNodo(Grafo &g) {
    int id;
    cout << "\n--- ELIMINAR NODO ---\n";
    cout << "ID del nodo a eliminar: "; cin >> id;
 
    if (id < 0 || id >= g.numNodos || !g.nodos[id].activo) {
        cout << "[ERROR] Nodo inválido o ya eliminado.\n";
        return;
    }
 
    // Eliminar todas sus conexiones
    for (int j = 0; j < g.numNodos; j++) {
        g.matriz[id][j].activa = 0;
        g.matriz[j][id].activa = 0;
    }
 
    g.nodos[id].activo = 0;
    cout << "[OK] Nodo '" << g.nodos[id].nombre << "' eliminado.\n";
}
 
void desactivarNodo(Grafo &g) {
    int id;
    cout << "\n--- DESACTIVAR NODO ---\n";
    cout << "ID del nodo a desactivar: "; cin >> id;
 
    if (id < 0 || id >= g.numNodos) {
        cout << "[ERROR] ID inválido.\n";
        return;
    }
 
    g.nodos[id].activo = 0;
    cout << "[OK] Nodo '" << g.nodos[id].nombre << "' desactivado (sin eliminar datos).\n";
}
 
// =====================================================
// PASO 6: CONSULTA Y MODIFICACIÓN
// =====================================================
 
void consultarNodo(Grafo &g) {
    int id;
    cout << "\n--- CONSULTAR NODO ---\n";
    cout << "ID del nodo: "; cin >> id;
 
    if (id < 0 || id >= g.numNodos) {
        cout << "[ERROR] ID inválido.\n";
        return;
    }
 
    Nodo &n = g.nodos[id];
    cout << "\n  ID:          " << n.id << "\n";
    cout << "  Nombre:      " << n.nombre << "\n";
    cout << "  Tipo:        " << nombreTipo(n.tipo) << "\n";
    cout << "  Estado:      " << (n.activo ? "Activo" : "Inactivo") << "\n";
    cout << "  Capacidad:   " << n.capacidadMW << " MW\n";
    cout << "  Consumo:     " << n.consumoMWh << " MWh\n";
    cout << "  Costo base:  " << n.costoBase << " M COP\n";
    cout << "  Registrado:  " << n.mesRegistro << "/" << n.anioRegistro << "\n";
 
    cout << "\n  Conexiones con:\n";
    int hayConexiones = 0;
    for (int j = 0; j < g.numNodos; j++) {
        if (g.matriz[id][j].activa) {
            cout << "    -> " << g.nodos[j].nombre
                 << " | Costo: " << g.matriz[id][j].costoTransmision
                 << " | Cap: "  << g.matriz[id][j].capacidadMW << " MW"
                 << " | Pérd: " << g.matriz[id][j].perdidas << "%\n";
            hayConexiones = 1;
        }
    }
    if (!hayConexiones) cout << "    (Sin conexiones)\n";
}
 
void modificarNodo(Grafo &g) {
    int id;
    cout << "\n--- MODIFICAR NODO ---\n";
    cout << "ID del nodo a modificar: "; cin >> id;
 
    if (id < 0 || id >= g.numNodos) {
        cout << "[ERROR] ID inválido.\n";
        return;
    }
 
    Nodo &n = g.nodos[id];
    int opcion;
    cout << "¿Qué desea modificar?\n";
    cout << "  1. Nombre\n";
    cout << "  2. Capacidad (MW)\n";
    cout << "  3. Consumo (MWh)\n";
    cout << "  4. Costo base\n";
    cout << "Opción: "; cin >> opcion;
 
    if (opcion == 1) {
        cin.ignore();
        cout << "Nuevo nombre: ";
        cin.getline(n.nombre, 50);
    } else if (opcion == 2) {
        cout << "Nueva capacidad (MW): ";
        cin >> n.capacidadMW;
    } else if (opcion == 3) {
        cout << "Nuevo consumo (MWh): ";
        cin >> n.consumoMWh;
    } else if (opcion == 4) {
        cout << "Nuevo costo base: ";
        cin >> n.costoBase;
    }
 
    cout << "[OK] Nodo modificado.\n";
}
 
void modificarArista(Grafo &g) {
    int origen, destino;
    cout << "\n--- MODIFICAR CONEXIÓN ---\n";
    cout << "ID nodo origen: ";  cin >> origen;
    cout << "ID nodo destino: "; cin >> destino;
 
    if (origen < 0 || origen >= g.numNodos || destino < 0 || destino >= g.numNodos) {
        cout << "[ERROR] IDs inválidos.\n";
        return;
    }
    if (!g.matriz[origen][destino].activa) {
        cout << "[ERROR] No existe esa conexión.\n";
        return;
    }
 
    cout << "Nuevo costo de transmisión: ";
    cin >> g.matriz[origen][destino].costoTransmision;
    g.matriz[destino][origen].costoTransmision = g.matriz[origen][destino].costoTransmision;
 
    cout << "[OK] Costo de transmisión actualizado.\n";
}
 
// =====================================================
// PASO 7: TRANSACCIONES
// =====================================================
 
void agregarTransaccion(Grafo &g) {
    int id;
    cout << "\n--- AGREGAR TRANSACCIÓN ---\n";
    cout << "ID del nodo: "; cin >> id;
 
    if (id < 0 || id >= g.numNodos || !g.nodos[id].activo) {
        cout << "[ERROR] Nodo inválido.\n";
        return;
    }
 
    Nodo &n = g.nodos[id];
    if (n.numTransacciones >= 100) {
        cout << "[ERROR] Límite de transacciones alcanzado.\n";
        return;
    }
 
    Transaccion &t = n.transacciones[n.numTransacciones];
    cout << "Año: ";       cin >> t.anio;
    cout << "Mes (1-12): "; cin >> t.mes;
    cout << "Monto (M COP): "; cin >> t.monto;
    cout << "Energía (MWh): "; cin >> t.energiaMWh;
 
    n.numTransacciones++;
    cout << "[OK] Transacción registrada.\n";
}
 
// =====================================================
// PASO 8: FILTRO POR AÑO
// =====================================================
 
void filtrarPorAnios(Grafo &g) {
    int anioDesde, anioHasta;
    cout << "\n--- FILTRAR POR AÑO ---\n";
    cout << "Desde el año: "; cin >> anioDesde;
    cout << "Hasta el año: "; cin >> anioHasta;
 
    cout << "\nNodos registrados entre " << anioDesde << " y " << anioHasta << ":\n";
    for (int i = 0; i < g.numNodos; i++) {
        Nodo &n = g.nodos[i];
        if (n.activo && n.anioRegistro >= anioDesde && n.anioRegistro <= anioHasta) {
            cout << "  [" << n.id << "] " << n.nombre
                 << " (" << nombreTipo(n.tipo) << ") - "
                 << n.mesRegistro << "/" << n.anioRegistro << "\n";
        }
    }
 
    cout << "\nTransacciones en ese rango:\n";
    for (int i = 0; i < g.numNodos; i++) {
        Nodo &n = g.nodos[i];
        for (int t = 0; t < n.numTransacciones; t++) {
            if (n.transacciones[t].anio >= anioDesde && n.transacciones[t].anio <= anioHasta) {
                cout << "  " << n.nombre
                     << " | " << n.transacciones[t].mes << "/" << n.transacciones[t].anio
                     << " | " << n.transacciones[t].energiaMWh << " MWh"
                     << " | " << n.transacciones[t].monto << " M COP\n";
            }
        }
    }
}
 
// =====================================================
// PASO 9: COSTO ÓPTIMO (Dijkstra)
// =====================================================
 
void dijkstra(Grafo &g) {
    int origen;
    cout << "\n--- COSTO ÓPTIMO DE DISTRIBUCIÓN (Dijkstra) ---\n";
    cout << "ID del nodo origen (generadora): "; cin >> origen;
 
    if (origen < 0 || origen >= g.numNodos || !g.nodos[origen].activo) {
        cout << "[ERROR] Nodo inválido.\n";
        return;
    }
 
    double dist[MAX_NODOS];
    int visitado[MAX_NODOS];
    int anterior[MAX_NODOS];
 
    for (int i = 0; i < g.numNodos; i++) {
        dist[i]     = 1e18; // infinito
        visitado[i] = 0;
        anterior[i] = -1;
    }
    dist[origen] = 0;
 
    for (int iter = 0; iter < g.numNodos; iter++) {
        // Buscar el nodo no visitado con menor distancia
        int u = -1;
        for (int i = 0; i < g.numNodos; i++) {
            if (!visitado[i] && g.nodos[i].activo) {
                if (u == -1 || dist[i] < dist[u]) u = i;
            }
        }
        if (u == -1 || dist[u] >= 1e18) break;
        visitado[u] = 1;
 
        // Relajar vecinos
        for (int v = 0; v < g.numNodos; v++) {
            if (g.matriz[u][v].activa && g.nodos[v].activo && !visitado[v]) {
                double peso = g.matriz[u][v].costoTransmision;
                if (dist[u] + peso < dist[v]) {
                    dist[v]     = dist[u] + peso;
                    anterior[v] = u;
                }
            }
        }
    }
 
    cout << "\nCostos mínimos desde '" << g.nodos[origen].nombre << "':\n";
    for (int i = 0; i < g.numNodos; i++) {
        if (i == origen || !g.nodos[i].activo) continue;
        cout << "  -> " << g.nodos[i].nombre << ": ";
        if (dist[i] >= 1e18) {
            cout << "  SIN RUTA\n";
        } else {
            cout << dist[i] << " M COP/MWh  |  Ruta: ";
            // Reconstruir ruta
            int ruta[MAX_NODOS];
            int len = 0, cur = i;
            while (cur != -1) { ruta[len++] = cur; cur = anterior[cur]; }
            for (int r = len - 1; r >= 0; r--) {
                cout << g.nodos[ruta[r]].nombre;
                if (r > 0) cout << " -> ";
            }
            cout << "\n";
        }
    }
}
 
// =====================================================
// PASO 10: ESTADÍSTICAS (Resumen)
// =====================================================
 
void mostrarEstadisticas(Grafo &g) {
    limpiarPantalla();
    cout << "    RESUMEN ESTADÍSTICO - SISTEMA ELÉCTRICO COLOMBIA\n";
    limpiarPantalla();
 
    int totalActivos = 0;
    double totalGeneracion = 0, totalConsumo = 0, totalCosto = 0;
    int contTipo[6] = {0};
 
    for (int i = 0; i < g.numNodos; i++) {
        if (!g.nodos[i].activo) continue;
        totalActivos++;
        contTipo[g.nodos[i].tipo]++;
        if (g.nodos[i].tipo != TIPO_CIUDAD)
            totalGeneracion += g.nodos[i].capacidadMW;
        else
            totalConsumo += g.nodos[i].consumoMWh;
        totalCosto += g.nodos[i].costoBase;
    }
 
    cout << "  Nodos activos:        " << totalActivos << "\n";
    cout << "  Hidroeléctricas:      " << contTipo[TIPO_HIDROELECTRICA] << "\n";
    cout << "  Termoeléctricas:      " << contTipo[TIPO_TERMOELECTRICA] << "\n";
    cout << "  Solar:                " << contTipo[TIPO_SOLAR] << "\n";
    cout << "  Eólica:               " << contTipo[TIPO_EOLICA] << "\n";
    cout << "  Ciudades:             " << contTipo[TIPO_CIUDAD] << "\n";
    cout << "  Capacidad total:      " << totalGeneracion << " MW\n";
    cout << "  Consumo total:        " << totalConsumo << " MWh\n";
    cout << "  Costo total base:     " << totalCosto << " M COP\n";
 
    cout << "\n  Conexiones activas:\n";
    int conexiones = 0;
    for (int i = 0; i < g.numNodos; i++)
        for (int j = i + 1; j < g.numNodos; j++)
            if (g.matriz[i][j].activa) conexiones++;
    cout << "  Total conexiones:     " << conexiones << "\n";
    limpiarPantalla();
}
 
void listarNodos(Grafo &g) {
    cout << "\n--- LISTA DE NODOS ---\n";
    for (int i = 0; i < g.numNodos; i++) {
        Nodo &n = g.nodos[i];
        cout << "  [" << n.id << "] "
             << n.nombre << " | "
             << nombreTipo(n.tipo) << " | "
             << (n.activo ? "Activo" : "Inactivo")
             << " | " << n.capacidadMW << " MW\n";
    }
}
 
// =====================================================
// PASO 11: PERSISTENCIA (Guardar y Cargar)
// =====================================================
 
void guardarDatos(Grafo &g) {
    ofstream f(ARCHIVO_DATOS);
    if (!f) { cout << "[ERROR] No se pudo abrir el archivo.\n"; return; }
 
    f << g.numNodos << "\n";
    for (int i = 0; i < g.numNodos; i++) {
        Nodo &n = g.nodos[i];
        f << n.id << "\n"
          << n.nombre << "\n"
          << n.tipo << " " << n.activo << " "
          << n.capacidadMW << " " << n.consumoMWh << " "
          << n.costoBase << " "
          << n.anioRegistro << " " << n.mesRegistro << "\n"
          << n.numTransacciones << "\n";
        for (int t = 0; t < n.numTransacciones; t++) {
            f << n.transacciones[t].anio << " "
              << n.transacciones[t].mes  << " "
              << n.transacciones[t].monto << " "
              << n.transacciones[t].energiaMWh << "\n";
        }
    }
 
    // Guardar matriz de adyacencia
    for (int i = 0; i < g.numNodos; i++)
        for (int j = 0; j < g.numNodos; j++) {
            Arista &a = g.matriz[i][j];
            f << a.activa << " " << a.costoTransmision << " "
              << a.capacidadMW << " " << a.perdidas << " " << a.anio << "\n";
        }
 
    f.close();
    cout << "[OK] Datos guardados en '" << ARCHIVO_DATOS << "'.\n";
}
 
void cargarDatos(Grafo &g) {
    ifstream f(ARCHIVO_DATOS);
    if (!f) { cout << "[AVISO] No se encontró archivo de datos. Iniciando vacío.\n"; return; }
 
    f >> g.numNodos;
    f.ignore();
    for (int i = 0; i < g.numNodos; i++) {
        Nodo &n = g.nodos[i];
        f >> n.id;
        f.ignore();
        f.getline(n.nombre, 50);
        f >> n.tipo >> n.activo >> n.capacidadMW
          >> n.consumoMWh >> n.costoBase
          >> n.anioRegistro >> n.mesRegistro
          >> n.numTransacciones;
        for (int t = 0; t < n.numTransacciones; t++) {
            f >> n.transacciones[t].anio
              >> n.transacciones[t].mes
              >> n.transacciones[t].monto
              >> n.transacciones[t].energiaMWh;
        }
    }
 
    for (int i = 0; i < g.numNodos; i++)
        for (int j = 0; j < g.numNodos; j++) {
            Arista &a = g.matriz[i][j];
            f >> a.activa >> a.costoTransmision
              >> a.capacidadMW >> a.perdidas >> a.anio;
        }
 
    f.close();
    cout << "[OK] Datos cargados desde '" << ARCHIVO_DATOS << "'.\n";
}
 
// =====================================================
// MENÚ PRINCIPAL
// =====================================================
 
int main() {
    Grafo g;
    inicializarGrafo(g);
 
    char cargar;
    cout << "\n¿Desea cargar datos desde archivo? (s/n): ";
    cin >> cargar;
    if (cargar == 's' || cargar == 'S') cargarDatos(g);
 
    int opcion;
    do {
        limpiarPantalla();
        cout << "  SISTEMA PEO-E - MINISTERIO DE MINAS Y ENERGÍA\n";
        limpiarPantalla();
        cout << "  1.  Agregar generadora/ciudad\n";
        cout << "  2.  Agregar conexión (línea de transmisión)\n";
        cout << "  3.  Eliminar nodo\n";
        cout << "  4.  Desactivar nodo\n";
        cout << "  5.  Consultar nodo\n";
        cout << "  6.  Modificar nodo\n";
        cout << "  7.  Modificar costo de conexión\n";
        cout << "  8.  Agregar transacción\n";
        cout << "  9.  Filtrar por año\n";
        cout << " 10.  Costo óptimo (Dijkstra)\n";
        cout << " 11.  Ver estadísticas\n";
        cout << " 12.  Listar todos los nodos\n";
        cout << " 13.  Guardar datos\n";
        cout << "  0.  Salir\n";
        limpiarPantalla();
        cout << "Opción: "; cin >> opcion;
 
        if      (opcion == 1)  agregarNodo(g);
        else if (opcion == 2)  agregarArista(g);
        else if (opcion == 3)  eliminarNodo(g);
        else if (opcion == 4)  desactivarNodo(g);
        else if (opcion == 5)  consultarNodo(g);
        else if (opcion == 6)  modificarNodo(g);
        else if (opcion == 7)  modificarArista(g);
        else if (opcion == 8)  agregarTransaccion(g);
        else if (opcion == 9)  filtrarPorAnios(g);
        else if (opcion == 10) dijkstra(g);
        else if (opcion == 11) mostrarEstadisticas(g);
        else if (opcion == 12) listarNodos(g);
        else if (opcion == 13) guardarDatos(g);
 
        if (opcion != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore(); cin.get();
        }
 
    } while (opcion != 0);
 
    cout << "\n¿Desea guardar antes de salir? (s/n): ";
    char guardar;
    cin >> guardar;
    if (guardar == 's' || guardar == 'S') guardarDatos(g);
 
    cout << "\n[OK] Programa finalizado. ¡Hasta luego!\n";
    return 0;
}