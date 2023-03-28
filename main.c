#include <stdio.h>
#include <string.h>

#define MAX 20

////////////////////// MIRAR !buffer[strcspn(buffer, "\n")] = 0;

// Estructuras
struct Producto {
    char codigo[10];
    int cantidad;
    int precio;
};

struct Cajero {
    char nombre[MAX];
    char password[MAX];
};

// Variables globales



// Prototipos
int cargarCajeros(struct Cajero *listaCajeros, int *linea);
void mostrarMenuPrincipal();
void iniciarSesion(struct Cajero *listaCajeros, int *linea);
void mostrarMenuCajero();
void crearPedido();
void escanearCodigo(struct Producto listaCompra[50]);
void agregarProducto(int cantidad, int codigo, struct Producto listaCompra[50]);
void borrarProducto();
void cancelarCompra();
void terminarCompra();
void pagarCompra();
void pagoEnEfectivo();


int main(void){
    int linea = 0;
    int* pLinea = &linea;
    struct Cajero listaCajeros[MAX];
    cargarCajeros(listaCajeros, &linea);
    printf("linea vale: %d\n", linea);
    iniciarSesion(listaCajeros, &linea);

    


    //mostrarMenuPrincipal();
    return 0;
}

int cargarCajeros(struct Cajero *listaCajeros, int *linea){
    FILE *archivoUsuarios = NULL;
    FILE *archivoPasswords = NULL;     

    archivoUsuarios = fopen("usuarios.txt", "r");
    archivoPasswords = fopen("passwords.txt", "r");
    if (archivoUsuarios == NULL || archivoPasswords == NULL) {
        printf("No fue posible abrir el o los archivo\n");
        return 1;
    } 
    while (*linea < MAX && fgets(listaCajeros[*linea].nombre, MAX, archivoUsuarios) != NULL
    && fgets(listaCajeros[*linea].password, MAX, archivoPasswords) != NULL) {
        listaCajeros[*linea].nombre[strcspn(listaCajeros[*linea].nombre, "\n")] = '\0';
        listaCajeros[*linea].password[strcspn(listaCajeros[*linea].password, "\n")] = '\0';       
        (*linea)++;
    }
    fclose(archivoUsuarios);
    fclose(archivoPasswords);
    return 0;
}

void mostrarMenuPrincipal(){
    int opcion = 1;
    while (opcion != 0){
        printf("\tMENU PRINCIPAL\n");
        printf("1_ Iniciar sesion\n");
        printf("2_ Informacion del supermercado\n");
        printf("3_ Llamar a Soporte Técnico\n");
        printf("0_ Salir\n");
        printf("Ingrese opcion: ");
        scanf("%d", &opcion);

        printf("La opcion ingresada fue: %d\n", opcion);

        switch (opcion) {
            case 1:
                //iniciarSesion();
                break;
            case 2:
                printf("\n\nDirección: Gutiérrez 1150\nCiudad: Los Polvorines\nTeléfono: 11-4020-1234\nHorarios: Lunes a Sábado de 08:00 a 22:00 hs\n\n");
                break;
        }

    }
}

void iniciarSesion(struct Cajero *listaCajeros, int* linea){
    char usuarioInput[MAX];
    char passwordInput[MAX];
    printf("\tINICIO DE SESION\n\n");
    printf("\nUsuario: ");
    fgets(usuarioInput, sizeof(usuarioInput), stdin);
    printf("\nContraseña: ");
    fgets(passwordInput, sizeof(passwordInput), stdin);
    usuarioInput[strcspn(usuarioInput, "\n")] = '\0'; // borra el \n del input
    passwordInput[strcspn(passwordInput, "\n")] = '\0';
    printf("ingresaste:%s\n",usuarioInput);
    if (strcmp("ADMIN", usuarioInput) == 0 && strcmp("ADMIN", passwordInput) == 0){
        printf("\n\t\tPrivilegios de ADMIN otorgados\n");
        //mostrarMenuAdmin();
    } 
    for (int i = 0; i < *linea; i++){
        printf("User: %s", listaCajeros[i].nombre);
        printf("Contraseña: %s\n", listaCajeros[i].password);
        if (strcmp(listaCajeros[i].nombre, usuarioInput) == 0) { //devuelve 0 cuando usuarioInput y el nombre guardado en el array son iguales
            printf("Usuario encontrado\n");
        }   else {
            printf ("NO LUCAS \n");
        }
    }
    
    
    // Inicia sesion un cajero

    mostrarMenuCajero();

    // Inicia sesion un encargado

    //mostrarMenuEncargado();
}

void mostrarMenuCajero(){
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

void crearPedido(){
    struct Producto listaCompra[50];

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


