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
void agregarProducto(int cantidad, int codigo, struct Producto listaCompra[50]);
void borrarProducto();
void cancelarCompra();
void terminarCompra();
void pagarCompra();
void pagoEnEfectivo();
int contarTiempo(int tiempo);

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

    while (numProductos < MAX_PRODUCTO && fscanf(archivoStock, "%s %d %d %d", productos[numProductos].nombre, &productos[numProductos].codigo, &productos[numProductos].cantidad, &productos[numProductos].precio) == 4) {
        //printf("Nombre: %s \tCodigo: %d \tCantidad: %d \tPrecio: %d\n", productos[numProductos].nombre, productos[numProductos].codigo, productos[numProductos].cantidad, productos[numProductos].precio);
        numProductos++;
        
    }
    cantidadProductos = numProductos;
    printf("cantidadProductos vale: %d", cantidadProductos);
    sleep(2);
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

int contarTiempo(int tiempo) {
    if (tiempo == 0) {
        return 0;
    } else if (tiempo < 0) {
        for (-tiempo; tiempo >= 0; tiempo--) {
            printf("%d\r", tiempo);
            //fflush(stdout);
            sleep(-tiempo);
        }
    } else {
        for (tiempo; tiempo <= 0; tiempo++) {
            printf("%d\r", tiempo);
            //fflush(stdout);
            sleep(tiempo);
        }
    }
    return 0;
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
            //printf("User: %s", listaCajeros[i].nombre); MOSTRAR USER Y PASS
            //printf("Contraseña: %s\n", listaCajeros[i].password);
            
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
    fflush(stdin);
    struct Producto listaCompra[MAX_PRODUCTO];
    int productosComprados = 0;
    int opcion = -1;
    while (opcion != 0) {
        LIMPIAR;
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
                //terminarCompra(Producto listaCompra);
                break;
            default:
                printf("Opcion incorrecta, ingrese nuevamente");
                sleep(2);
        }
    }
    
}


int escanearCodigo(struct Producto *listaCompra, struct Producto *productos, int productosComprados) {
    
    int productoCorrecto = 0;
    int numeroProducto = NULL;

    int cantidadCompra;
    int codigoCompra;
    char nombreCompra[MAX_PRODUCTO];
    
    fflush(stdin);

    LIMPIAR;
    printf("\t\t\t\tSTOCK ACTUAL\n");
    int nP=0;
    while (nP < cantidadProductos) {
        printf("Nombre: %s \tCodigo: %d \tCantidad: %d \tPrecio: %d\n", listaProductos[nP].nombre, listaProductos[nP].codigo, listaProductos[nP].cantidad, listaProductos[nP].precio);
        nP++;
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
                sleep(3);
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
                sleep(3);
            } 
        }
    } 

    

    if (!productoCorrecto) {
            printf("\nProducto no encontrado. Ingrese nuevamente...\n");
            sleep(2);
        }



    
    printf("Ingrese cantidad: ");
    scanf("%d", &cantidadCompra);

    listaCompra[productosComprados-1].cantidad = cantidadCompra;
    productos[numeroProducto].cantidad -= cantidadCompra;

    listaCompra[productosComprados-1].precio = productos[numeroProducto].precio;
    
    printf("COMPRA PARCIAL \n\n\n\n\n\n");
    for (int a = 0; a < productosComprados; a++)    {
        printf("Nombre: %s\t", listaCompra[a].nombre);
        printf("Codigo: %d\t", listaCompra[a].codigo);
        printf("Cantidad: %d\t", listaCompra[a].cantidad);
        printf("Precio: %d\t\n", listaCompra[a].precio);
    }
    
    sleep(5);

    return productosComprados;
    //agregarProducto(cantidad, codigo[10], listaCompra);
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

void agregarProducto(int cantidadProducto, int codigoProducto, struct Producto listaCompra[50]){
    // Agregar Producto a la lista de compra
    


}

void cancelarCompra(){
    // TODO
}


