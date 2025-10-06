#include <iostream>
#include <string>

const int capacidad_inicial = 50;

int capacidad = capacidad_inicial;
int frente = 0;
int final = 0;
int total = 0;

// vectores paralelos dinámicos
int *id;
float *peso;
std::string *destino;
int *prioridad;
char *estado;

// funciones principales
void inicializar();
void encolar();
void desencolar();
void inspeccionar();
void reporte();
void liberar();
void menu();

// función principal
int main() {
    std::cout << "--- Sistema de Despacho Logístico MegaEnvío ---" << std::endl;

    inicializar();
    menu();
    liberar();

    return 0;
}

// reserva memoria dinámica
void inicializar() {
    std::cout << "Inicializando sistema con capacidad para " << capacidad << " paquetes..." << std::endl;

    id = new int[capacidad];
    peso = new float[capacidad];
    destino = new std::string[capacidad];
    prioridad = new int[capacidad];
    estado = new char[capacidad];

    std::cout << "Capacidad actual: " << capacidad << ". Paquetes en cola: " << total << "." << std::endl;
}

// agregar paquete (encolar)
void encolar() {
    if (total == capacidad) {
        std::cout << "Capacidad llena. Duplicando tamaño..." << std::endl;
        int nueva_cap = capacidad * 2;

        int *nuevo_id = new int[nueva_cap];
        float *nuevo_peso = new float[nueva_cap];
        std::string *nuevo_destino = new std::string[nueva_cap];
        int *nuevo_prioridad = new int[nueva_cap];
        char *nuevo_estado = new char[nueva_cap];

        for (int i = 0; i < capacidad; i++) {
            nuevo_id[i] = id[i];
            nuevo_peso[i] = peso[i];
            nuevo_destino[i] = destino[i];
            nuevo_prioridad[i] = prioridad[i];
            nuevo_estado[i] = estado[i];
        }

        delete[] id;
        delete[] peso;
        delete[] destino;
        delete[] prioridad;
        delete[] estado;

        id = nuevo_id;
        peso = nuevo_peso;
        destino = nuevo_destino;
        prioridad = nuevo_prioridad;
        estado = nuevo_estado;
        capacidad = nueva_cap;

        std::cout << "Nueva capacidad: " << capacidad << std::endl;
    }

    std::cout << "Ingrese ID del paquete: ";
    std::cin >> id[final];
    std::cout << "Peso (kg): ";
    std::cin >> peso[final];
    std::cin.ignore();
    std::cout << "Destino: ";
    std::getline(std::cin, destino[final]);
    std::cout << "Prioridad (1 = Alta, 2 = Media, 3 = Baja): ";
    std::cin >> prioridad[final];
    std::cin.ignore();

    estado[final] = 'E'; // en cola

    final = (final + 1) % capacidad;
    total++;

    std::cout << "Paquete agregado correctamente. Total: " << total << "/" << capacidad << std::endl;
}

// despachar paquete (desencolar)
void desencolar() {
    if (total == 0) {
        std::cout << "No hay paquetes en cola." << std::endl;
        return;
    }

    std::cout << "Despachando paquete..." << std::endl;
    estado[frente] = 'D'; // marcar como despachado

    std::cout << "Paquete " << id[frente] << " despachado con éxito. Estado: D" << std::endl;

    frente = (frente + 1) % capacidad;
    total--;
}

// mostrar frente de la cola
void inspeccionar() {
    if (total == 0) {
        std::cout << "No hay paquetes en cola." << std::endl;
        return;
    }

    std::cout << "Frente de la cola:" << std::endl;
    std::cout << "  ID: " << id[frente]
              << " | Peso: " << peso[frente] << " kg"
              << " | Destino: " << destino[frente]
              << " | Prioridad: " << prioridad[frente]
              << " | Estado: " << estado[frente] << std::endl;
}

// generar reporte por destino
void reporte() {
    if (total == 0) {
        std::cout << "No hay paquetes para generar reporte." << std::endl;
        return;
    }

    std::string buscar;
    std::cout << "Ingrese el destino para el reporte: ";
    std::getline(std::cin, buscar);

    int contador = 0;
    float suma_pesos = 0.0;

    for (int i = 0; i < capacidad; i++) {
        if (estado[i] == 'E' && destino[i] == buscar) {
            contador++;
            suma_pesos += peso[i];
        }
    }

    if (contador == 0) {
        std::cout << "No hay paquetes en cola con destino " << buscar << "." << std::endl;
        return;
    }

    float promedio = suma_pesos / contador;

    std::cout << "Reporte para destino '" << buscar << "':" << std::endl;
    std::cout << "  Paquetes en cola: " << contador << std::endl;
    std::cout << "  Peso promedio: " << promedio << " kg" << std::endl;
}

// liberar memoria dinámica
void liberar() {
    delete[] id;
    delete[] peso;
    delete[] destino;
    delete[] prioridad;
    delete[] estado;

    std::cout << "Memoria liberada correctamente. Sistema cerrado." << std::endl;
}

// menú principal
void menu() {
    int opcion = 0;
    do {
        std::cout << "\nSeleccione una operación:" << std::endl;
        std::cout << "1. Agregar Paquete (Encolar)" << std::endl;
        std::cout << "2. Despachar Paquete (Desencolar)" << std::endl;
        std::cout << "3. Inspeccionar Frente de Cola" << std::endl;
        std::cout << "4. Reporte por Destino" << std::endl;
        std::cout << "5. Salir (Liberar Memoria)" << std::endl;

        std::cout << "Opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch(opcion) {
            case 1: encolar(); break;
            case 2: desencolar(); break;
            case 3: inspeccionar(); break;
            case 4: reporte(); break;
            case 5: std::cout << "Saliendo del sistema..." << std::endl; break;
            default: std::cout << "Opción inválida." << std::endl;
        }

    } while(opcion != 5);
}
