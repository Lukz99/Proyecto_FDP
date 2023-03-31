/*
*   Autores:    Luna,           Barbara  
*               Ledesma Jurado, Lucas
*
*   GitHub:     https://github.com/Lukz99/Proyecto_FDP
*
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_CAJERO 20
#define MAX_PRODUCTO 11
#define LIMPIAR system("clear")

// Estructuras

struct Producto {
    char nombre[MAX_PRODUCTO];
    int codigo;
    int cantidad;
    int precio;
};

struct Cajero {
    char nombre[MAX_CAJERO];
    char password[MAX_CAJERO];
};

// Variables globales

struct Producto listaProductos[MAX_PRODUCTO];
int cantidadProductos;
int contadorTickets = 0;

// Prototipos

int cargarCajeros(struct Cajero* listaCajeros, int* linea);
int cargarStock(struct Producto* productos);
void mostrarMenuPrincipal(struct Cajero* listaCajeros, int* linea);
void iniciarSesion(struct Cajero* listaCajeros, int* linea);
void mostrarInfoSuper();
void llamarSoporte(char soporte[]);
void mostrarMenuCajero();
void mostrarMenuEncargado();
void crearPedido();
int escanearCodigo(struct Producto* listaCompra, struct Producto* productos, int productosComprados);
void borrarProducto();
void terminarCompra(struct Producto* listaCompra, int productosComprados);
void pagarCompra(struct Producto* listaCompra, int pagarTotal, int productosComprados);
void pagoEnEfectivo(struct Producto* listaCompra, int precioFinal, int productosComprados);
void pagoConTarjeta();
void emitirTicket(struct Producto* listaCompra, int precioFinal, int productosComprados);
 

// Funciones

int main(void) {
    
    int linea = 0;
    int* punteroLinea = &linea;
    struct Cajero listaCajeros[MAX_CAJERO];
    
    cargarStock(listaProductos);
    cargarCajeros(listaCajeros, punteroLinea);
    
    mostrarMenuPrincipal(listaCajeros, punteroLinea);

    return 0;    
}

int cargarStock(struct Producto *productos) {
    FILE *archivoStock = NULL;
    int numProductos = 0;
    archivoStock = fopen("stock.txt", "r");
    if (!archivoStock) {
        printf("No fue posible cargar el Stock\n");
        sleep(2);
        exit (1);
    } 

    while (numProductos < MAX_PRODUCTO && fscanf(archivoStock, "%s %d %d %d",   
                                                    productos[numProductos].nombre,
                                                    &productos[numProductos].codigo,
                                                    &productos[numProductos].cantidad,
                                                    &productos[numProductos].precio) == 4)
    {
        numProductos++;
    }
    cantidadProductos = numProductos;
}

int cargarCajeros(struct Cajero* listaCajeros, int* linea) {
    FILE *archivoUsuarios = NULL;
    FILE *archivoPasswords = NULL;

    archivoUsuarios = fopen("usuarios.txt", "r");
    archivoPasswords = fopen("passwords.txt", "r");
    if (!archivoUsuarios || !archivoPasswords) {
        printf("No fue posible abrir el o los archivos\n");
        sleep(2);
        exit(1);
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
        printf("\n0_ Salir\n");       
        printf("Ingrese opcion: ");
        
        
        scanf("%d", &opcion);

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
                llamarSoporte("soporte técnico");
                break;
            default:
                printf("Opcion incorrecta, ingrese nuevamente");
                sleep(2);
        }

    }
}

void llamarSoporte(char soporte[]){
    LIMPIAR;
    printf("Llamando al %s. Aguarde por favor...", soporte);
    sleep(3);
}

void mostrarInfoSuper(){
    LIMPIAR;
    printf("\n\n"
        "Dirección: Gutiérrez 1150\n"
        "Ciudad: Los Polvorines\n"
        "Teléfono: 11-4020-1234\n"
        "Horarios: Lunes a Sábado de 08:00 a 22:00 hs\n");
    printf("\n\n\n\n");
    sleep(2);
    //contarTiempo(-3);
    
    

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

        if (strcmp("ADMIN", usuarioInput) == 0 && strcmp("ADMIN", passwordInput) == 0) {
            loginCorrecto = 1;
            printf("\n\t\tPrivilegios de ADMIN otorgados\n");            
            mostrarMenuEncargado();
        } 

        for (int i = 0; i < *linea; i++){            
            // strcmp devuelve 0 cuando usuarioInput y el nombre guardado en el array son iguales
            if (strcmp(listaCajeros[i].nombre, usuarioInput) == 0 && strcmp(listaCajeros[i].password, passwordInput) == 0) { 
                loginCorrecto = 1;
                printf("\n\t\t\t\t¡Bienvenid@ %s!", listaCajeros[i].nombre);
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
    int opcion = -1;
    while (opcion != 0){
        LIMPIAR;        
        fflush(stdin);
        printf("\t\t\t\tMENU CAJERO\n");        
        printf("1_ Crear pedido\n");
        printf("2_ Llamar al encargado\n"); 

        printf("\n0_ Cerrar sesión\n");       
        
        printf("Ingrese opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 0:                
                break;
            case 1:
                crearPedido();
                break;
            case 2:
                llamarSoporte("encargado");
                break;            
            default:
                printf("Opcion incorrecta, ingrese nuevamente");
                sleep(2);
        }
    }   
}

void crearPedido(){    
    struct Producto listaCompra[MAX_PRODUCTO];
    int productosComprados = 0;
    int opcion = -1;
    while (opcion != 0) {
        fflush(stdin);
        LIMPIAR;
        printf("\t\t\t\t MENU DE COMPRA\n\n");
        printf("1_ Escanear codigo\n");
        printf("2_ Borrar producto\n");
        printf("3_ Terminar compra\n");
        printf("\n0_ Cancelar compra\n");

        printf("Ingrese opcion: ");
        scanf("%d", &opcion);
        
        switch (opcion) {
            case 0:
                break;
            case 1:
                productosComprados = escanearCodigo(listaCompra, listaProductos, productosComprados);
                break;
            case 2:
                borrarProducto();
                break;
            case 3:
                terminarCompra(listaCompra, productosComprados);
                break;
            default:
                printf("Opcion incorrecta, ingrese nuevamente");
                sleep(2);
        }
    }
    
}

int escanearCodigo(struct Producto *listaCompra, struct Producto *productos, int productosComprados) {
    
    int productoCorrecto    = 0;
    int numeroProducto      = 0;
    int cantidadCompra      = 0;
    int codigoCompra        = 0;
    int contadorStock       = 0;
    char nombreCompra[MAX_PRODUCTO];    

    fflush(stdin);
    LIMPIAR;
    printf("\t\t\t\tSTOCK ACTUAL\n");
    
    while (contadorStock < cantidadProductos) {
        printf("Nombre: %-10s \tCodigo: %-6d \tCantidad: %-6d \tPrecio: %-6d\n", listaProductos[contadorStock].nombre, listaProductos[contadorStock].codigo, listaProductos[contadorStock].cantidad, listaProductos[contadorStock].precio);
        contadorStock++;
    } 
    
    printf("Ingrese codigo o nombre del producto: ");
    if (scanf("%d", &codigoCompra) != 1) {              
        // Si no se ingresó un número, se asume que se ingresó el nombre del producto
        // Entra al 'if' en caso de que se escriba un nombre   
        scanf("%s", nombreCompra);
        for (int i = 0; i < cantidadProductos; i++) {
            if (strcmp(productos[i].nombre, nombreCompra) == 0) { 
                // strcmp devuelve 0 cuando el nombre ingresado del producto es igual al del array en [i]
                numeroProducto = i; 
                productoCorrecto = 1;           
                strcpy(listaCompra[productosComprados].nombre, nombreCompra); // Se guarda el nombre en listaCompra
                listaCompra[productosComprados].codigo = productos[i].codigo; // le asigno el mismo codigo del que coincide en nombre
                productosComprados++;       
            } 
        }
    } else { // Entra al 'else' en caso de que se escriba un código numérico
        for (int i = 0; i < cantidadProductos; i++) {
            if (productos[i].codigo == codigoCompra) {
                numeroProducto = i; 
                productoCorrecto = 1;                
                listaCompra[productosComprados].codigo = codigoCompra;                
                strcpy(listaCompra[productosComprados].nombre, productos[i].nombre);
                productosComprados++;                
            } 
        }
    } 
    if (!productoCorrecto) {
        printf("\nProducto no encontrado.\n");
        sleep(2);
        return productosComprados;
        
    }    
    printf("Ingrese cantidad: ");
    scanf("%d", &cantidadCompra);

    listaCompra[productosComprados-1].cantidad = cantidadCompra;                    // Se guarda la cantidad comprada
    productos[numeroProducto].cantidad -= cantidadCompra;                           // Se resta la cantidad comprada al stock

    listaCompra[productosComprados-1].precio = productos[numeroProducto].precio;    // Se guarda el precio en listaCompra
    
    LIMPIAR;
    printf("\t\t\t\t\tCOMPRA PARCIAL \n\n\n");
    for (int indiceProducto = 0; indiceProducto < productosComprados; indiceProducto++)    {

        printf("Nombre: %-15s Codigo: %-6d Cantidad: %-6d Precio: %-6d\n", listaCompra[indiceProducto].nombre, listaCompra[indiceProducto].codigo, listaCompra[indiceProducto].cantidad, listaCompra[indiceProducto].precio);
        /*printf("Nombre: %-20s", listaCompra[indiceProducto].nombre);
        printf("Codigo: %-20d", listaCompra[indiceProducto].codigo);
        printf("Cantidad: %d\t", listaCompra[indiceProducto].cantidad);
        printf("Precio: %d\n", listaCompra[indiceProducto].precio);
    */
    }    
    sleep(5);

    return productosComprados;
}

void borrarProducto(){
    LIMPIAR;
    printf("Para borrar un producto de los escaneados,\n"
    "por favor escanéelo nuevamente e ingrese una\n"
    "cantidad negativa según corresponda");
    sleep(5);
}

void terminarCompra(struct Producto *listaCompra, int productosComprados){
    int pagarTotal = 0;
    for (int i = 0; i < productosComprados; i++) {
        pagarTotal += listaCompra[i].precio * listaCompra[i].cantidad;
    }
    printf("El total de su compra es: %d pesos\t", pagarTotal);
    sleep(2);
    pagarCompra(listaCompra, pagarTotal, productosComprados);   
    
}

void pagarCompra(struct Producto *listaCompra, int precioFinal, int productosComprados) {
    int opcion = -1;
    while (opcion != 0) {
        fflush(stdin);
        LIMPIAR;
        printf("El cliente debe pagar %d pesos. Seleccione metodo de pago:\n", precioFinal);
        printf("1_ Efectivo\n");
        printf("2_ Tarjeta de crédito\n");
        printf("3_ Tarjeta de débito\n");
        printf("\n0_ Cancelar compra\n");
        printf("Ingrese opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 0:
                break; 
            case 1:
                pagoEnEfectivo(listaCompra, precioFinal, productosComprados);
                break;
            case 2:
                pagoConTarjeta();
                break;
            case 3:
                pagoConTarjeta();
                break;
            default:
                printf("Opción incorrecta. Ingrese nuevamente.\n");
                sleep(2);
        }
    }
}

void pagoConTarjeta() {
    printf("No hay sistema. Solicite pago en efectivo.");
    sleep(2);
}

void pagoEnEfectivo(struct Producto *listaCompra, int precioFinal, int productosComprados) {
    int efectivo;
    int vuelto;
    printf("Ingrese con cuanto paga el usuario: \n");
    scanf("%d", &efectivo);
    vuelto = efectivo - precioFinal;
    printf("Devolver al cliente %d pesos\n\n", vuelto);
    emitirTicket(listaCompra, precioFinal, productosComprados);
    sleep(3);    
    mostrarMenuCajero();
}

void emitirTicket(struct Producto *listaCompra, int precioFinal, int productosComprados) {
    char nombreArchivo[50];
    char nombreCliente[20];
    sprintf(nombreArchivo, "Tickets/ticket_%d.txt", contadorTickets); // guarda "ticket_{contadorTickets}.txt" en nombreArchivo
    contadorTickets++;

    FILE* archivoTicket = fopen(nombreArchivo, "w");
    if (archivoTicket == NULL) {
        printf("Error al abrir el archivo.");
        return;
    }
    printf("Ingrese nombre del cliente: ");
    scanf("%s", nombreCliente);

    printf("\n\t\t\t¡Gracias por su compra %s!", nombreCliente);
    for (int i = 0; i < productosComprados; i++) {
        fprintf(archivoTicket, "Nombre: %-10s\tCodigo: %d\tCantidad: %d\tPrecio: %d\n", 
        listaCompra[i].nombre, 
        listaCompra[i].codigo,
        listaCompra[i].cantidad, 
        listaCompra[i].precio); // escribe en el archivo del ticket
    }
    fprintf(archivoTicket, "Cliente: %s\n", nombreCliente);
    fprintf(archivoTicket,"-----------------------FIN-----DE----TICKET-------------------");

    fclose(archivoTicket);
}

