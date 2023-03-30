#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CAJERO 20
#define MAX_PRODUCTO 50
#define LIMPIAR system("clear")


// Estructuras
struct Producto {
    char nombre[20];
    int codigo;
    int cantidad;
    int precio;
};

struct Cajero {
    char nombre[MAX_CAJERO];
    char password[MAX_CAJERO];
};

// Prototipos

int cargarCajeros(struct Cajero* listaCajeros, int* linea);
int cargarStock();
void mostrarMenuPrincipal(struct Cajero* listaCajeros, int* linea);
void iniciarSesion(struct Cajero* listaCajeros, int* linea);
void mostrarInfoSuper();
void llamarSoporte();
void mostrarMenuCajero();
void mostrarMenuEncargado();
void crearPedido();
void escanearCodigo(struct Producto listaCompra[50]);
void agregarProducto(int cantidad, int codigo, struct Producto listaCompra[50]);
void borrarProducto();
void cancelarCompra();
void terminarCompra();
void pagarCompra();
void pagoEnEfectivo();


int main(void) {
    int linea = 0;
    int* punteroLinea = &linea;
    struct Cajero listaCajeros[MAX_CAJERO];
    struct Producto listaCompra[50];
    cargarStock();
    cargarCajeros(listaCajeros, punteroLinea);
    
    mostrarMenuPrincipal(listaCajeros, punteroLinea);
    return 0;    
}

int cargarStock() {
    FILE *archivoStock = NULL;

    archivoStock = fopen("stock.txt", "r");
    if (!archivoStock) {
        printf("No fue posible cargar el Stock.\n");
        return 1;
    } 

}

int cargarCajeros(struct Cajero* listaCajeros, int* linea) {
    FILE *archivoUsuarios = NULL;
    FILE *archivoPasswords = NULL;

    archivoUsuarios = fopen("usuarios.txt", "r");
    archivoPasswords = fopen("passwords.txt", "r");
    if (!archivoUsuarios || !archivoPasswords) {
        printf("No fue posible abrir el o los archivo\n");
        return 1;
    } 
    while (*linea < MAX_CAJERO && fgets(listaCajeros[*linea].nombre, MAX_CAJERO, archivoUsuarios) != NULL
    && fgets(listaCajeros[*linea].password, MAX_CAJERO, archivoPasswords) != NULL) {
        listaCajeros[*linea].nombre[strcspn(listaCajeros[*linea].nombre, "\n")] = '\0';
        listaCajeros[*linea].password[strcspn(listaCajeros[*linea].password, "\n")] = '\0';       
        (*linea)++;
    }
    fclose(archivoUsuarios);
    fclose(archivoPasswords);
    return 0;
}

void mostrarMenuPrincipal(struct Cajero* listaCajeros, int* punteroLinea){
    int opcion = -1;
    while (opcion != 0){
        LIMPIAR;
        fflush(stdin);
        printf("\t\t\t\t\tMENU PRINCIPAL\n");
        printf("1_ Iniciar sesion\n");
        printf("2_ Informacion del supermercado\n");
        printf("3_ Llamar a Soporte Técnico\n");
        printf("0_ Salir\n");
        printf("Ingrese opcion: ");
        
        scanf("%d", &opcion);

        printf("La opcion ingresada fue: %d\n", opcion);

        switch (opcion) {
            case 0:
                exit(0);
                break;
            case 1:
                iniciarSesion(listaCajeros, punteroLinea);
                break;
            case 2:
                mostrarInfoSuper();
                break;
            case 3:
                llamarSoporte();
                break;
            default:
                printf("Opcion incorrecta, ingrese nuevamente");
                sleep(2);
        }

    }
}

void llamarSoporte(){
    LIMPIAR;
    printf("Llamando a soporte técnico. Aguarde por favor...");
    sleep(3);
}

void mostrarInfoSuper(){
    //printf("\n\nDirección: Gutiérrez 1150\nCiudad: Los Polvorines\nTeléfono: 11-4020-1234\nHorarios: Lunes a Sábado de 08:00 a 22:00 hs\n\n");
    LIMPIAR;
    printf("\n\n"
        "Dirección: Gutiérrez 1150\n"
        "Ciudad: Los Polvorines\n"
        "Teléfono: 11-4020-1234\n"
        "Horarios: Lunes a Sábado de 08:00 a 22:00 hs\n\n");
    sleep(3);
}

void iniciarSesion(struct Cajero *listaCajeros, int* linea) {
    fflush(stdin);
    char usuarioInput[MAX_CAJERO];
    char passwordInput[MAX_CAJERO];
    int loginCorrecto = 0;

    while (!loginCorrecto) {
        LIMPIAR;
        printf("\t\t\t\tINICIO DE SESION\n\n");

        printf("\nUsuario: ");
        fgets(usuarioInput, sizeof(usuarioInput), stdin);
        usuarioInput[strcspn(usuarioInput, "\n")] = '\0'; // borra el \n del input

        printf("\nContraseña: ");
        fgets(passwordInput, sizeof(passwordInput), stdin);        
        passwordInput[strcspn(passwordInput, "\n")] = '\0';

        printf("ingresaste:%s\n",usuarioInput);

        if (strcmp("ADMIN", usuarioInput) == 0 && strcmp("ADMIN", passwordInput) == 0) {
            loginCorrecto = 1;
            printf("\n\t\tPrivilegios de ADMIN otorgados\n");            
            mostrarMenuEncargado();
        } 

        for (int i = 0; i < *linea; i++){
            printf("User: %s", listaCajeros[i].nombre);
            printf("Contraseña: %s\n", listaCajeros[i].password);
            
            // strcmp devuelve 0 cuando usuarioInput y el nombre guardado en el array son iguales
            if (strcmp(listaCajeros[i].nombre, usuarioInput) == 0 && strcmp(listaCajeros[i].password, passwordInput) == 0) { 
                loginCorrecto = 1;
                printf("\n\t\t\t\t¡Bienvenido %s!", listaCajeros[i].nombre);
                sleep(3);
                mostrarMenuCajero();
            } 
        }
        if (!loginCorrecto) {
            printf("\nUsuario o contraseña incorrectos. Por favor intente nuevamente.\n");
            sleep(3);
        }
    }    
}

void mostrarMenuEncargado(){
    printf("ADMIN");
}

void mostrarMenuCajero(){
    int opcion = 1;
    while (opcion != 0){
        LIMPIAR;
        int opcion;
        printf("\n\tMENU CAJERO\n");
        printf("\n1_ Crear pedido\n");
        printf("2_ ...\n");

        printf("Ingrese opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 1:
                crearPedido();
                break;
            case 2:

        }
    }

}

void crearPedido(){
    

    int opcion;
    printf("1_ Escanear codigo\n");
    printf("2_ Borrar producto\n");
    printf("3_ Terminar compra\n");
    printf("4_ Cancelar compra\n");

    printf("Ingrese opcion: ");
    scanf("%d", &opcion);
    
    switch (opcion) {
        case 1:
            //escanearCodigo(&listaCompra[50]);
            break;
        case 2:
            borrarProducto();
            break;
        case 3:
            //terminarCompra(Producto listaCompra);
            break;
        case 4:
            cancelarCompra();
            break;
    }
}

void borrarProducto(){
    // Modifica listaCompra para eliminar un producto o bajar su cantidad
}

void terminarCompra(struct Producto listaCompra){
    int precioFinal = 1000;
    //
    //printf("El total de su compra es: ", precioFinal)
    pagarCompra(precioFinal);
    
    
}

void pagarCompra(int precioFinal) {
    int opcion;
    printf("1_ Efectivo\n");
    printf("2_ Tarjeta de credito\n");    
    printf("3_ Tarjeta de debito\n");
    
    printf("Ingrese opcion: ");
    scanf("%d", &opcion);

    switch (opcion){
        case 1:
            pagoEnEfectivo(precioFinal);
            break;
        case 2:
            //pagoConTarjeta();
            break;
        case 3:
            //pagoConTarjeta();
            break;
    }
}

void pagoEnEfectivo(int precioFinal){
    int efectivo;
    int vuelto;
    printf("Ingrese con cuanto paga el usuario: \n");
    scanf("%d", &efectivo);
    vuelto = efectivo - precioFinal;
    printf("Devolver al cliente %d pesos", vuelto);
}

void escanearCodigo(struct Producto listaCompra[50]){
    int cantidad;
    char codigo[10];

    printf("Ingrese cantidad: \n");
    scanf("%d", &cantidad);

    printf("Ingrese codigo del producto: \n");
    scanf("%d", &codigo);    
    

    agregarProducto(cantidad, codigo[10], listaCompra);
}

void agregarProducto(int cantidadProducto, int codigoProducto, struct Producto listaCompra[50]){
    // Agregar Producto a la lista de compra
    


}

void cancelarCompra(){
    // Cancela todo, el cliente se va sin comprar nada
}


