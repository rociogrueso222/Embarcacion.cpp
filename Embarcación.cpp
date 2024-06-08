#include <iostream>
#include <stdlib.h>

using namespace std;

struct pasajero {
    char nombre[45];
    pasajero* sig;
};

struct embarcacion {
    char nombreEmbarcacion[20];
    int dia, mes, year;
    char destino[45];
    int capacidad;
    int identificador; //  identificador
    int matricula;
    float precio;
    embarcacion* izq;
    embarcacion* der;
    int altura;
    pasajero* inicioPasajeros;
    pasajero* finPasajeros;
    int numPasajeros;
};

struct embarcacion* raiz, * aux;
struct pasajero* auxP;

int crearNodo() {
    aux = (struct embarcacion*)malloc(sizeof(struct embarcacion));
    cout << "Cual es el nombre de la embarcacion: ";
    cin >> aux->nombreEmbarcacion;
    cout << "ingrese el year: ";
    cin >> aux->year;
    cout << "ingrese el mes: ";
    cin >> aux->mes;
    cout << "ingrese el dia: ";
    cin >> aux->dia;
    cout << "Ingrese el destino de la embarcacion: ";
    cin >> aux->destino;
    cout << "ingrese la capacidad de la embarcacion: ";
    cin >> aux->capacidad;
    cout << "ingrese la matricula de la embarcacion: ";
    cin >> aux->matricula;
    cout << "ingrese el precio de la embarcacion: ";
    cin >> aux->precio;
    cout << "Ingrese el identificador: ";
    cin >> aux->identificador;
    aux->izq = NULL;
    aux->der = NULL;
    aux->altura = 1;
    aux->inicioPasajeros = NULL;
    aux->finPasajeros = NULL;
    aux->numPasajeros = 0;
    return 0;
}

int obtenerAltura(struct embarcacion* n) {
    if (n == NULL) {
        return 0;
    }
    return n->altura;
}

int mayor(int a, int b) {
    return (a > b) ? a : b;
}

int obtenerBalance(struct embarcacion* n) {
    if (n == NULL) {
        return 0;
    }
    return obtenerAltura(n->izq) - obtenerAltura(n->der);
}

struct embarcacion* rotarDerecha(struct embarcacion* y) {
    struct embarcacion* x = y->izq;
    struct embarcacion* T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;

    return x;
}

struct embarcacion* rotarIzquierda(struct embarcacion* x) {
    struct embarcacion* y = x->der;
    struct embarcacion* T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;

    return y;
}

struct embarcacion* insertar(struct embarcacion* nodo) {
    if (nodo == NULL) {
        return aux;
    }

    if (aux->identificador < nodo->identificador) {
        nodo->izq = insertar(nodo->izq);
    }
    else if (aux->identificador > nodo->identificador) {
        nodo->der = insertar(nodo->der);
    }
    else {
        return nodo;
    }

    nodo->altura = 1 + mayor(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

    int balance = obtenerBalance(nodo);

    if (balance > 1 && aux->identificador < nodo->izq->identificador) {
        return rotarDerecha(nodo);
    }

    if (balance < -1 && aux->identificador > nodo->der->identificador) {
        return rotarIzquierda(nodo);
    }

    if (balance > 1 && aux->identificador > nodo->izq->identificador) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if (balance < -1 && aux->identificador < nodo->der->identificador) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

void inOrden(struct embarcacion* nodo) {
    if (nodo != NULL) {
        inOrden(nodo->izq);
        cout << "Nombre: " << nodo->nombreEmbarcacion << ", Identificador: " << nodo->identificador << endl;
        inOrden(nodo->der);
    }
}

struct embarcacion* buscarEmbarcacion(struct embarcacion* nodo, int identificadorBusqueda) {
    if (nodo == NULL || nodo->identificador == identificadorBusqueda) {
        return nodo;
    }

    if (identificadorBusqueda < nodo->identificador) {
        return buscarEmbarcacion(nodo->izq, identificadorBusqueda);
    }
    else {
        return buscarEmbarcacion(nodo->der, identificadorBusqueda);
    }
}

void registrarPasajero(struct embarcacion* viaje) {
    if (viaje->numPasajeros >= viaje->capacidad) {
        cout << "La embarcacion ha alcanzado su capacidad maxima." << endl;
        return;
    }

    auxP = (struct pasajero*)malloc(sizeof(struct pasajero));
    cout << "Ingrese el nombre del pasajero: ";
    cin >> auxP->nombre;
    auxP->sig = NULL;

    if (viaje->inicioPasajeros == NULL) {
        viaje->inicioPasajeros = auxP;
        viaje->finPasajeros = auxP;
    } else {
        viaje->finPasajeros->sig = auxP;
        viaje->finPasajeros = auxP;
    }

    viaje->numPasajeros++;
    cout << "Pasajero registrado exitosamente." << endl;
}

void listarPasajeros(struct embarcacion* viaje) {
    if (viaje->inicioPasajeros == NULL) {
        cout << "No hay pasajeros registrados en este viaje." << endl;
        return;
    }

    pasajero* temp = viaje->inicioPasajeros;
    int count = 1;
    while (temp != NULL) {
        cout << count << ". " << temp->nombre << endl;
        temp = temp->sig;
        count++;
    }
}

struct embarcacion* minValorNodo(struct embarcacion* nodo) {
    struct embarcacion* actual = nodo;

    while (actual && actual->izq != NULL) {
        actual = actual->izq;
    }

    return actual;
}

struct embarcacion* eliminar(struct embarcacion* raiz, int identificador) {
    if (raiz == NULL) {
        return raiz;
    }

    if (identificador < raiz->identificador) {
        raiz->izq = eliminar(raiz->izq, identificador);
    } else if (identificador > raiz->identificador) {
        raiz->der = eliminar(raiz->der, identificador);
    } else {
        if (raiz->izq == NULL) {
            struct embarcacion* temp = raiz->der;
            free(raiz);
            return temp;
        } else if (raiz->der == NULL) {
            struct embarcacion* temp = raiz->izq;
            free(raiz);
            return temp;
        }

        struct embarcacion* temp = minValorNodo(raiz->der);
        (raiz->nombreEmbarcacion, temp->nombreEmbarcacion);
        raiz->dia = temp->dia;
        raiz->mes = temp->mes;
        raiz->year = temp->year;
        (raiz->destino, temp->destino);
        raiz->capacidad = temp->capacidad;
        raiz->identificador = temp->identificador;
        raiz->matricula = temp->matricula;
        raiz->precio = temp->precio;
        raiz->der = eliminar(raiz->der, temp->identificador);
    }
    return raiz;
}

int main() {
    raiz = NULL;
    int opc = 0;
    struct embarcacion* resultado; // Declaramos las variables aquí
    int identificadorBusqueda;
    
    do {
        cout << "Menu de opciones" << endl;
        cout << "1. Registrar un nuevo viaje" << endl;
        cout << "2. Listar viajes inorden" << endl;
        cout << "3. Buscar un viaje por identificador" << endl;
        cout << "4. Registrar un pasajero en un viaje" << endl;
        cout << "5. Listar todos lospasajero de un viaje" << endl;
        cout << "6. Eliminar un viajepor identificador" << endl;
        cout << "7. Salir" << endl;
        cin >> opc;
        switch (opc) {
        case 1:
            crearNodo();
            raiz = insertar(raiz);
            break;
        case 2:
            cout << "Inorden: " << endl;
            inOrden(raiz);
            cout << endl;
            break;
        case 3:
            cout << "Ingrese el identificador de la embarcacion a buscar: ";
            cin >> identificadorBusqueda;
            resultado = buscarEmbarcacion(raiz, identificadorBusqueda);
            if (resultado != NULL) {
                cout << "Datos de la embarcacion encontrada:" << endl;
                cout << "Nombre: " << resultado->nombreEmbarcacion << endl;
                cout << "Fecha: " << resultado->dia << "/" << resultado->mes << "/" << resultado->year << endl;
                cout << "Destino: " << resultado->destino << endl;
                cout << "Capacidad: " << resultado->capacidad << endl;
                cout << "Matricula: " << resultado->matricula << endl;
                cout << "Precio: " << resultado->precio << endl;
                cout << "Identificador: " << resultado->identificador << endl;
            } else {
                cout << "Embarcacion no encontrada." << endl;
            }
            break;
        case 4:
            cout << "Ingrese el identificador de la embarcacion para registrar pasajeros: ";
            cin >> identificadorBusqueda;
            resultado = buscarEmbarcacion(raiz, identificadorBusqueda);
            if (resultado != NULL) {
                char opcion;
                do {
                    registrarPasajero(resultado);
                    cout << "Desea registrar otro pasajero en este viaje? (s/n): ";
                    cin >> opcion;
                } while (opcion == 's' || opcion == 'S');
            } else {
                cout << "Embarcacion no encontrada." << endl;
            }
            break;
        case 5:
            cout << "Ingrese el identificador de la embarcacion para listar pasajeros: ";
            cin >> identificadorBusqueda;
            resultado = buscarEmbarcacion(raiz, identificadorBusqueda);
            if (resultado != NULL) {
                listarPasajeros(resultado);
            } else {
                cout << "Embarcacion no encontrada." << endl;
            }
            break;
        case 6:
            cout << "Ingrese el identificador de la embarcacion a eliminar: ";
            cin >> identificadorBusqueda;
            raiz = eliminar(raiz, identificadorBusqueda);
            cout << "Embarcacion eliminada exitosamente." << endl;
            break;
        }
    } while (opc != 7);
    return 0;
}
