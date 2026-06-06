#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;


void gotoxy(int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}



struct Transaccion {
    int    id;
    int    anio;
    int    mes;
    double monto;
    double energiaMWh;
    bool   activa;
};

struct Nodo {
    int    id;
    string nombre;
    int    tipo;     
    bool   activo;
    double capacidadMW;
    double consumoMWh;
    double costoBase;
    int    anioRegistro;
    int    mesRegistro;
    vector<Transaccion> transacciones;
};

struct Arista {
    int    idOrigen;
    int    idDestino;
    double costoTransmision;
    double capacidadMW;
    double perdidas;
    int    anio;
    bool   activa;
};

struct Grafo {
    vector<Nodo>   nodos;
    vector<Arista> aristas;
};




int buscarNodo(vector<Nodo> &nodos, int id){
    for(int i = 0; i < (int)nodos.size(); i++){
        if(nodos[i].id == id && nodos[i].activo)
            return i;
    }
    return -1;
}

int buscarArista(vector<Arista> &aristas, int origen, int destino){
    for(int i = 0; i < (int)aristas.size(); i++){
        if(aristas[i].activa &&
          ((aristas[i].idOrigen == origen && aristas[i].idDestino == destino) ||
           (aristas[i].idOrigen == destino && aristas[i].idDestino == origen)))
            return i;
    }
    return -1;
}

int buscarTransaccion(vector<Transaccion> &trans, int id){
    for(int i = 0; i < (int)trans.size(); i++){
        if(trans[i].id == id && trans[i].activa)
            return i;
    }
    return -1;
}

string nombreTipo(int tipo){
    switch(tipo){
        case 1: return "Hidroelectrica";
        case 2: return "Termoelectrica";
        case 3: return "Solar";
        case 4: return "Eolica";
        case 5: return "Ciudad";
    }
    return "Desconocido";
}




void TITULO(){
    system("cls");
    system("color F1");
    gotoxy(26,7); cout << "Universidad Popular del Cesar";
    gotoxy(22,8); cout << "Prog. Estadistico de Optimizacion Energetica";
}




int seleccionarTipo(){
    int op;
    do{
        TITULO();
        gotoxy(28,10); cout << "=== TIPO DE ELEMENTO ===";
        gotoxy(23,12); cout << "1. Hidroelectrica";
        gotoxy(23,13); cout << "2. Termoelectrica";
        gotoxy(23,14); cout << "3. Solar";
        gotoxy(23,15); cout << "4. Eolica";
        gotoxy(23,16); cout << "5. Ciudad";
        gotoxy(20,22); cout << "Seleccione una opcion: ";
        gotoxy(45,22); cin >> op;
    }while((op < 1)||(op > 5));
    return op;
}




void crearNodo(Grafo &g){
    TITULO();
    Nodo n;

    gotoxy(23,10); cout << "ID del Nodo       :";
    gotoxy(43,10); cin >> n.id;

    if(buscarNodo(g.nodos, n.id) != -1){
        gotoxy(20,20); cout << "//EL ID YA EXISTE//";
        getche(); return;
    }

    gotoxy(23,11); cout << "Nombre            :";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    gotoxy(43,11); getline(cin, n.nombre);

    n.tipo = seleccionarTipo();
    TITULO();

    gotoxy(23,10); cout << "Capacidad (MW)    :";
    gotoxy(43,10); cin >> n.capacidadMW;

    gotoxy(23,11); cout << "Consumo   (MWh)   :";
    gotoxy(43,11); cin >> n.consumoMWh;

    gotoxy(23,12); cout << "Costo base (MCOP) :";
    gotoxy(43,12); cin >> n.costoBase;

    gotoxy(23,13); cout << "Anio de registro  :";
    gotoxy(43,13); cin >> n.anioRegistro;

    gotoxy(23,14); cout << "Mes  de registro  :";
    gotoxy(43,14); cin >> n.mesRegistro;

    n.activo = true;
    g.nodos.push_back(n);

    gotoxy(20,20); cout << "//NODO CREADO//";
    getche();
}

void mostrarNodos(Grafo &g){
    TITULO();
    int y = 11;

    gotoxy(3,10);
    cout << left << setw(8)  << "ID"
                 << setw(22) << "NOMBRE"
                 << setw(16) << "TIPO"
                 << setw(12) << "CAP(MW)"
                 << setw(8)  << "ESTADO";

    for(auto n : g.nodos){
        if(n.activo){
            gotoxy(3,y);
            cout << left << setw(8)  << n.id
                         << setw(22) << n.nombre
                         << setw(16) << nombreTipo(n.tipo)
                         << setw(12) << n.capacidadMW
                         << setw(8)  << (n.activo ? "Activo" : "Inactivo");
            y++;
        }
    }
    getche();
}

void modificarNodo(Grafo &g){
    TITULO();
    int id;

    gotoxy(23,10); cout << "ID del Nodo :";
    gotoxy(37,10); cin >> id;

    int idx = buscarNodo(g.nodos, id);
    if(idx == -1){
        gotoxy(20,20); cout << "//NODO NO EXISTE//";
        getche(); return;
    }

    Nodo &n = g.nodos[idx];
    int op;

    do{
        gotoxy(20,20); cout << "Que desea Modificar?:";
        gotoxy(20,21); cout << "1.Nombre  2.Capacidad  3.Consumo  4.CostoBase  5.Desactivar";
        gotoxy(41,20); cin >> op;
    }while((op < 1)||(op > 5));

    switch(op){
        case 1: gotoxy(23,14); cout << "Nuevo Nombre :";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                gotoxy(37,14); getline(cin, n.nombre);
                break;
        case 2: gotoxy(23,14); cout << "Nueva Capacidad (MW) :";
                gotoxy(45,14); cin >> n.capacidadMW;
                break;
        case 3: gotoxy(23,14); cout << "Nuevo Consumo (MWh)  :";
                gotoxy(45,14); cin >> n.consumoMWh;
                break;
        case 4: gotoxy(23,14); cout << "Nuevo Costo base     :";
                gotoxy(45,14); cin >> n.costoBase;
                break;
        case 5: n.activo = false;
                break;
    }

    gotoxy(20,20); cout << "//NODO MODIFICADO//";
    getche();
}

void eliminarNodo(Grafo &g){
    TITULO();
    int id;

    gotoxy(23,10); cout << "ID del Nodo a Eliminar :";
    gotoxy(47,10); cin >> id;

    int idx = buscarNodo(g.nodos, id);
    if(idx == -1){
        gotoxy(20,20); cout << "//NODO NO EXISTE//";
        getche(); return;
    }

   
    for(auto &a : g.aristas){
        if(a.idOrigen == id || a.idDestino == id)
            a.activa = false;
    }

    g.nodos.erase(g.nodos.begin() + idx);

    gotoxy(20,20); cout << "//NODO ELIMINADO//";
    getche();
}




void crearArista(Grafo &g){
    TITULO();

    if((int)g.nodos.size() < 2){
        gotoxy(20,20); cout << "//SE NECESITAN AL MENOS 2 NODOS//";
        getche(); return;
    }

    Arista a;

    gotoxy(23,10); cout << "ID nodo Origen  :";
    gotoxy(41,10); cin >> a.idOrigen;

    if(buscarNodo(g.nodos, a.idOrigen) == -1){
        gotoxy(20,20); cout << "//NODO ORIGEN NO EXISTE//";
        getche(); return;
    }

    gotoxy(23,11); cout << "ID nodo Destino :";
    gotoxy(41,11); cin >> a.idDestino;

    if(buscarNodo(g.nodos, a.idDestino) == -1){
        gotoxy(20,20); cout << "//NODO DESTINO NO EXISTE//";
        getche(); return;
    }

    if(buscarArista(g.aristas, a.idOrigen, a.idDestino) != -1){
        gotoxy(20,20); cout << "//LA CONEXION YA EXISTE//";
        getche(); return;
    }

    gotoxy(23,12); cout << "Costo transmision (MCOP) :";
    gotoxy(49,12); cin >> a.costoTransmision;

    gotoxy(23,13); cout << "Capacidad linea   (MW)   :";
    gotoxy(49,13); cin >> a.capacidadMW;

    gotoxy(23,14); cout << "Porcentaje perdidas      :";
    gotoxy(49,14); cin >> a.perdidas;

    gotoxy(23,15); cout << "Anio de instalacion      :";
    gotoxy(49,15); cin >> a.anio;

    a.activa = true;
    g.aristas.push_back(a);

    gotoxy(20,20); cout << "//CONEXION CREADA//";
    getche();
}

void mostrarAristas(Grafo &g){
    TITULO();
    int y = 11;

    gotoxy(3,10);
    cout << left << setw(10) << "ORIGEN"
                 << setw(10) << "DESTINO"
                 << setw(14) << "COSTO(MCOP)"
                 << setw(12) << "CAP(MW)"
                 << setw(10) << "PERD%"
                 << setw(8)  << "ANIO";

    for(auto a : g.aristas){
        if(a.activa){
            // Obtener nombres
            string nomO = "?", nomD = "?";
            int io = buscarNodo(g.nodos, a.idOrigen);
            int id = buscarNodo(g.nodos, a.idDestino);
            if(io != -1) nomO = g.nodos[io].nombre;
            if(id != -1) nomD = g.nodos[id].nombre;

            gotoxy(3,y);
            cout << left << setw(10) << nomO
                         << setw(10) << nomD
                         << setw(14) << a.costoTransmision
                         << setw(12) << a.capacidadMW
                         << setw(10) << a.perdidas
                         << setw(8)  << a.anio;
            y++;
        }
    }
    getche();
}

void modificarArista(Grafo &g){
    TITULO();
    int origen, destino;

    gotoxy(23,10); cout << "ID nodo Origen  :";
    gotoxy(41,10); cin >> origen;

    gotoxy(23,11); cout << "ID nodo Destino :";
    gotoxy(41,11); cin >> destino;

    int idx = buscarArista(g.aristas, origen, destino);
    if(idx == -1){
        gotoxy(20,20); cout << "//CONEXION NO EXISTE//";
        getche(); return;
    }

    Arista &a = g.aristas[idx];
    int op;

    do{
        gotoxy(20,20); cout << "Que desea Modificar?:";
        gotoxy(20,21); cout << "1.Costo  2.Capacidad  3.Perdidas  4.Desactivar";
        gotoxy(41,20); cin >> op;
    }while((op < 1)||(op > 4));

    switch(op){
        case 1: gotoxy(23,14); cout << "Nuevo Costo (MCOP) :";
                gotoxy(43,14); cin >> a.costoTransmision;
                break;
        case 2: gotoxy(23,14); cout << "Nueva Capacidad MW :";
                gotoxy(43,14); cin >> a.capacidadMW;
                break;
        case 3: gotoxy(23,14); cout << "Nuevas Perdidas %  :";
                gotoxy(43,14); cin >> a.perdidas;
                break;
        case 4: a.activa = false;
                break;
    }

    gotoxy(20,20); cout << "//CONEXION MODIFICADA//";
    getche();
}

void eliminarArista(Grafo &g){
    TITULO();
    int origen, destino;

    gotoxy(23,10); cout << "ID nodo Origen  :";
    gotoxy(41,10); cin >> origen;

    gotoxy(23,11); cout << "ID nodo Destino :";
    gotoxy(41,11); cin >> destino;

    int idx = buscarArista(g.aristas, origen, destino);
    if(idx == -1){
        gotoxy(20,20); cout << "//CONEXION NO EXISTE//";
        getche(); return;
    }

    g.aristas.erase(g.aristas.begin() + idx);
    gotoxy(20,20); cout << "//CONEXION ELIMINADA//";
    getche();
}




void crearTransaccion(Grafo &g){
    TITULO();
    int id;

    gotoxy(23,10); cout << "ID del Nodo :";
    gotoxy(37,10); cin >> id;

    int idx = buscarNodo(g.nodos, id);
    if(idx == -1){
        gotoxy(20,20); cout << "//NODO NO EXISTE//";
        getche(); return;
    }

    Transaccion t;

    gotoxy(23,12); cout << "ID de la Transaccion :";
    gotoxy(45,12); cin >> t.id;

    gotoxy(23,13); cout << "Anio                 :";
    gotoxy(45,13); cin >> t.anio;

    gotoxy(23,14); cout << "Mes  (1-12)          :";
    gotoxy(45,14); cin >> t.mes;

    gotoxy(23,15); cout << "Monto    (MCOP)      :";
    gotoxy(45,15); cin >> t.monto;

    gotoxy(23,16); cout << "Energia  (MWh)       :";
    gotoxy(45,16); cin >> t.energiaMWh;

    t.activa = true;
    g.nodos[idx].transacciones.push_back(t);

    gotoxy(20,20); cout << "//TRANSACCION REGISTRADA//";
    getche();
}

void mostrarTransacciones(Grafo &g){
    TITULO();
    int id;

    gotoxy(23,10); cout << "ID del Nodo :";
    gotoxy(37,10); cin >> id;

    int idx = buscarNodo(g.nodos, id);
    if(idx == -1){
        gotoxy(20,20); cout << "//NODO NO EXISTE//";
        getche(); return;
    }

    int y = 12;
    gotoxy(3,11);
    cout << left << setw(8)  << "ID"
                 << setw(8)  << "ANIO"
                 << setw(6)  << "MES"
                 << setw(14) << "MONTO(MCOP)"
                 << setw(14) << "ENERGIA(MWh)";

    for(auto t : g.nodos[idx].transacciones){
        if(t.activa){
            gotoxy(3,y);
            cout << left << setw(8)  << t.id
                         << setw(8)  << t.anio
                         << setw(6)  << t.mes
                         << setw(14) << t.monto
                         << setw(14) << t.energiaMWh;
            y++;
        }
    }
    getche();
}

void eliminarTransaccion(Grafo &g){
    TITULO();
    int idNodo, idTrans;

    gotoxy(23,10); cout << "ID del Nodo        :";
    gotoxy(43,10); cin >> idNodo;

    int idx = buscarNodo(g.nodos, idNodo);
    if(idx == -1){
        gotoxy(20,20); cout << "//NODO NO EXISTE//";
        getche(); return;
    }

    gotoxy(23,11); cout << "ID de la Transaccion :";
    gotoxy(45,11); cin >> idTrans;

    int ti = buscarTransaccion(g.nodos[idx].transacciones, idTrans);
    if(ti == -1){
        gotoxy(20,20); cout << "//TRANSACCION NO EXISTE//";
        getche(); return;
    }

    g.nodos[idx].transacciones.erase(g.nodos[idx].transacciones.begin() + ti);
    gotoxy(20,20); cout << "//TRANSACCION ELIMINADA//";
    getche();
}




void filtrarPorAnio(Grafo &g){
    TITULO();
    int desde, hasta;
    int y = 14;

    gotoxy(23,10); cout << "Desde el Anio :";
    gotoxy(39,10); cin >> desde;

    gotoxy(23,11); cout << "Hasta el Anio :";
    gotoxy(39,11); hasta = 0; cin >> hasta;

    gotoxy(3,13);
    cout << left << setw(22) << "NODO"
                 << setw(16) << "TIPO"
                 << setw(10) << "REGISTRO";

    for(auto n : g.nodos){
        if(n.activo && n.anioRegistro >= desde && n.anioRegistro <= hasta){
            gotoxy(3,y);
            cout << left << setw(22) << n.nombre
                         << setw(16) << nombreTipo(n.tipo)
                         << setw(10) << n.anioRegistro;
            y++;
        }
    }

    
    for(auto n : g.nodos){
        for(auto t : n.transacciones){
            if(t.activa && t.anio >= desde && t.anio <= hasta && y < 23){
                gotoxy(3,y);
                cout << left << setw(22) << n.nombre
                             << setw(8)  << t.anio
                             << setw(8)  << t.monto
                             << setw(10) << t.energiaMWh;
                y++;
            }
        }
    }
    getche();
}




void dijkstra(Grafo &g){
    TITULO();

    if(g.nodos.empty()){
        gotoxy(20,20); cout << "//NO HAY NODOS EN EL SISTEMA//";
        getche(); return;
    }

    int idOrigen;
    gotoxy(23,10); cout << "ID nodo Origen (generadora) :";
    gotoxy(52,10); cin >> idOrigen;

    int io = buscarNodo(g.nodos, idOrigen);
    if(io == -1){
        gotoxy(20,20); cout << "//NODO NO EXISTE//";
        getche(); return;
    }

    int N = (int)g.nodos.size();
    vector<double> dist(N, 1e18);
    vector<int>    anterior(N, -1);
    vector<bool>   visitado(N, false);

    dist[io] = 0;

    for(int iter = 0; iter < N; iter++){
        int u = -1;
        for(int i = 0; i < N; i++)
            if(!visitado[i] && g.nodos[i].activo)
                if(u == -1 || dist[i] < dist[u]) u = i;

        if(u == -1 || dist[u] >= 1e18) break;
        visitado[u] = 1;

        for(auto &ar : g.aristas){
            if(!ar.activa) continue;
            int v = -1;
            if(ar.idOrigen == g.nodos[u].id)
                v = buscarNodo(g.nodos, ar.idDestino);
            else if(ar.idDestino == g.nodos[u].id)
                v = buscarNodo(g.nodos, ar.idOrigen);
            if(v == -1 || !g.nodos[v].activo || visitado[v]) continue;
            if(dist[u] + ar.costoTransmision < dist[v]){
                dist[v]     = dist[u] + ar.costoTransmision;
                anterior[v] = u;
            }
        }
    }

    int y = 12;
    gotoxy(5,11); cout << left << setw(22) << "DESTINO" << setw(14) << "COSTO(MCOP)" << "RUTA";

    for(int i = 0; i < N && y < 23; i++){
        if(i == io || !g.nodos[i].activo) continue;
        gotoxy(5,y);
        if(dist[i] >= 1e18){
            cout << left << setw(22) << g.nodos[i].nombre << "SIN RUTA";
        } else {
            // Reconstruir ruta
            vector<int> ruta;
            int cur = i;
            while(cur != -1){ ruta.push_back(cur); cur = anterior[cur]; }
            reverse(ruta.begin(), ruta.end());

            string rutaStr = "";
            for(int r = 0; r < (int)ruta.size(); r++){
                rutaStr += g.nodos[ruta[r]].nombre;
                if(r < (int)ruta.size()-1) rutaStr += "->";
            }
            cout << left << setw(22) << g.nodos[i].nombre
                         << setw(14) << dist[i]
                         << rutaStr;
        }
        y++;
    }
    getche();
}




void resumenDatos(Grafo &g){
    TITULO();

    int totalNodos = 0, totalCiudades = 0, totalConexiones = 0, totalTrans = 0;
    int hidro = 0, termo = 0, solar = 0, eolica = 0;
    double totalCap = 0, totalCons = 0;

    for(auto n : g.nodos){
        if(!n.activo) continue;
        totalNodos++;
        if(n.tipo == 1) hidro++;
        if(n.tipo == 2) termo++;
        if(n.tipo == 3) solar++;
        if(n.tipo == 4) eolica++;
        if(n.tipo == 5) totalCiudades++;
        if(n.tipo != 5) totalCap  += n.capacidadMW;
        else            totalCons += n.consumoMWh;
        for(auto t : n.transacciones) if(t.activa) totalTrans++;
    }
    for(auto a : g.aristas) if(a.activa) totalConexiones++;

    gotoxy(33,9);  cout << "--RESUMEN DE DATOS--";
    gotoxy(25,10); cout << "Nodos activos       : " << totalNodos;
    gotoxy(25,11); cout << "  Hidroelectricas   : " << hidro;
    gotoxy(25,12); cout << "  Termoelectricas   : " << termo;
    gotoxy(25,13); cout << "  Solar             : " << solar;
    gotoxy(25,14); cout << "  Eolica            : " << eolica;
    gotoxy(25,15); cout << "  Ciudades          : " << totalCiudades;
    gotoxy(25,16); cout << "Conexiones activas  : " << totalConexiones;
    gotoxy(25,17); cout << "Transacciones       : " << totalTrans;
    gotoxy(25,18); cout << "Capacidad total     : " << totalCap  << " MW";
    gotoxy(25,19); cout << "Consumo total       : " << totalCons << " MWh";

    getche();
}




void guardarNodos(Grafo &g){
    ofstream archivo("nodos.csv");
    for(auto n : g.nodos){
        if(n.activo){
            archivo << n.id << ","
                    << n.nombre << ","
                    << n.tipo << ","
                    << n.capacidadMW << ","
                    << n.consumoMWh << ","
                    << n.costoBase << ","
                    << n.anioRegistro << ","
                    << n.mesRegistro << "\n";
        }
    }
    archivo.close();
}

void guardarAristas(Grafo &g){
    ofstream archivo("aristas.csv");
    for(auto a : g.aristas){
        if(a.activa){
            archivo << a.idOrigen << ","
                    << a.idDestino << ","
                    << a.costoTransmision << ","
                    << a.capacidadMW << ","
                    << a.perdidas << ","
                    << a.anio << "\n";
        }
    }
    archivo.close();
}

void guardarTransacciones(Grafo &g){
    ofstream archivo("transacciones.csv");
    for(auto n : g.nodos){
        if(!n.activo) continue;
        for(auto t : n.transacciones){
            if(t.activa){
                archivo << n.id << ","
                        << t.id << ","
                        << t.anio << ","
                        << t.mes  << ","
                        << t.monto << ","
                        << t.energiaMWh << "\n";
            }
        }
    }
    archivo.close();
}

void guardarTodo(Grafo &g){
    guardarNodos(g);
    guardarAristas(g);
    guardarTransacciones(g);
    gotoxy(20,20); cout << "//DATOS GUARDADOS//";
    getche();
}

void cargarNodos(Grafo &g){
    ifstream archivo("nodos.csv");
    if(!archivo){ return; }
    string linea;
    while(getline(archivo, linea)){
        stringstream ss(linea);
        string dato;
        Nodo n;
        getline(ss, dato, ','); n.id          = stoi(dato);
        getline(ss, n.nombre,  ',');
        getline(ss, dato, ','); n.tipo         = stoi(dato);
        getline(ss, dato, ','); n.capacidadMW  = stod(dato);
        getline(ss, dato, ','); n.consumoMWh   = stod(dato);
        getline(ss, dato, ','); n.costoBase    = stod(dato);
        getline(ss, dato, ','); n.anioRegistro = stoi(dato);
        getline(ss, dato, ','); n.mesRegistro  = stoi(dato);
        n.activo = true;
        g.nodos.push_back(n);
    }
    archivo.close();
}

void cargarAristas(Grafo &g){
    ifstream archivo("aristas.csv");
    if(!archivo){ return; }
    string linea;
    while(getline(archivo, linea)){
        stringstream ss(linea);
        string dato;
        Arista a;
        getline(ss, dato, ','); a.idOrigen         = stoi(dato);
        getline(ss, dato, ','); a.idDestino        = stoi(dato);
        getline(ss, dato, ','); a.costoTransmision = stod(dato);
        getline(ss, dato, ','); a.capacidadMW      = stod(dato);
        getline(ss, dato, ','); a.perdidas         = stod(dato);
        getline(ss, dato, ','); a.anio             = stoi(dato);
        a.activa = true;
        g.aristas.push_back(a);
    }
    archivo.close();
}

void cargarTransacciones(Grafo &g){
    ifstream archivo("transacciones.csv");
    if(!archivo){ return; }
    string linea;
    while(getline(archivo, linea)){
        stringstream ss(linea);
        string dato;
        Transaccion t;
        int idNodo;
        getline(ss, dato, ','); idNodo    = stoi(dato);
        getline(ss, dato, ','); t.id      = stoi(dato);
        getline(ss, dato, ','); t.anio    = stoi(dato);
        getline(ss, dato, ','); t.mes     = stoi(dato);
        getline(ss, dato, ','); t.monto   = stod(dato);
        getline(ss, dato, ','); t.energiaMWh = stod(dato);
        t.activa = true;
        int idx = buscarNodo(g.nodos, idNodo);
        if(idx != -1) g.nodos[idx].transacciones.push_back(t);
    }
    archivo.close();
}

void cargarTodo(Grafo &g){
    cargarNodos(g);
    cargarAristas(g);
    cargarTransacciones(g);
}


// =====================================================
// SUBMENÚS
// =====================================================

void menuNodos(Grafo &g){
    int op;
    do{
        TITULO();
        gotoxy(30,9);  cout << "=== NODOS ===";
        gotoxy(23,10); cout << "1. Crear Nodo";
        gotoxy(23,11); cout << "2. Mostrar Nodos";
        gotoxy(23,12); cout << "3. Modificar Nodo";
        gotoxy(23,13); cout << "4. Eliminar Nodo";
        gotoxy(23,14); cout << "5. Volver";

        do{
            gotoxy(38,20); cout << "             ";
            gotoxy(20,20); cout << "Ingrese la opcion:";
            gotoxy(38,20); cin >> op;
        }while((op < 1)||(op > 5));

        switch(op){
            case 1: crearNodo(g);    break;
            case 2: mostrarNodos(g); break;
            case 3: modificarNodo(g);break;
            case 4: eliminarNodo(g); break;
        }
    }while(op != 5);
}

void menuConexiones(Grafo &g){
    int op;
    do{
        TITULO();
        gotoxy(28,9);  cout << "=== CONEXIONES ===";
        gotoxy(23,10); cout << "1. Crear Conexion";
        gotoxy(23,11); cout << "2. Mostrar Conexiones";
        gotoxy(23,12); cout << "3. Modificar Conexion";
        gotoxy(23,13); cout << "4. Eliminar Conexion";
        gotoxy(23,14); cout << "5. Volver";

        do{
            gotoxy(38,20); cout << "             ";
            gotoxy(20,20); cout << "Ingrese la opcion:";
            gotoxy(38,20); cin >> op;
        }while((op < 1)||(op > 5));

        switch(op){
            case 1: crearArista(g);    break;
            case 2: mostrarAristas(g); break;
            case 3: modificarArista(g);break;
            case 4: eliminarArista(g); break;
        }
    }while(op != 5);
}

void menuTransacciones(Grafo &g){
    int op;
    do{
        TITULO();
        gotoxy(27,9);  cout << "=== TRANSACCIONES ===";
        gotoxy(23,10); cout << "1. Agregar Transaccion";
        gotoxy(23,11); cout << "2. Mostrar Transacciones";
        gotoxy(23,12); cout << "3. Eliminar Transaccion";
        gotoxy(23,13); cout << "4. Volver";

        do{
            gotoxy(38,20); cout << "             ";
            gotoxy(20,20); cout << "Ingrese la opcion:";
            gotoxy(38,20); cin >> op;
        }while((op < 1)||(op > 4));

        switch(op){
            case 1: crearTransaccion(g);    break;
            case 2: mostrarTransacciones(g);break;
            case 3: eliminarTransaccion(g); break;
        }
    }while(op != 4);
}




int main(){

    char OP;
    Grafo g;

    TITULO();

    do{
        gotoxy(20,23); cout << "Desea Abrir un Archivo ya existente (S/N):";
        OP = getch();
        OP = toupper(OP);
    }while((OP != 'S')&&(OP != 'N'));

    if(OP == 'S'){
        cargarTodo(g);
    }

    int op;
    do{
        TITULO();
        gotoxy(30,9);  cout << "=== MENU PRINCIPAL ===";
        gotoxy(23,10); cout << "1. Nodos  (Generadoras / Ciudades)";
        gotoxy(23,11); cout << "2. Conexiones  (Lineas de transmision)";
        gotoxy(23,12); cout << "3. Transacciones";
        gotoxy(23,13); cout << "4. Filtrar por Anio";
        gotoxy(23,14); cout << "5. Costo Optimo  (Dijkstra)";
        gotoxy(23,15); cout << "6. Resumen de Datos";
        gotoxy(23,16); cout << "7. Guardar";
        gotoxy(23,17); cout << "8. Salir";

        do{
            gotoxy(38,20); cout << "             ";
            gotoxy(20,20); cout << "Ingrese la opcion:";
            gotoxy(38,20); cin >> op;
        }while((op < 1)||(op > 8));

        switch(op){
            case 1: menuNodos(g);        break;
            case 2: menuConexiones(g);   break;
            case 3: menuTransacciones(g);break;
            case 4: filtrarPorAnio(g);   break;
            case 5: dijkstra(g);         break;
            case 6: resumenDatos(g);     break;
            case 7: guardarTodo(g);      break;
        }

    }while(op != 8);

    return 0;
}
