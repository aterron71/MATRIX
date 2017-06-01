#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int IDE=0,IDB=0,IDP=0;

typedef struct Persona
{
	char Nombre[30];
	int ID;
	int edad;
	char Sexo;
	struct Persona *siguiente;
}Persona;

typedef struct Bateria
{
	int nPersonas;
	int Nivel;
	Persona *inicio;
	struct Persona *ultimo;
	struct Bateria *siguiente;
}Bateria;


typedef struct Estacion
{
	int ID;
	int nPersonas;
	int nBaterias;
	struct Bateria *tope;
	struct Estacion *siguiente;
}Estacion;

//FUNCIONES PILA
Bateria* pop(Bateria **tope){
	Bateria *aux;
	aux = (*tope);
	(*tope) = (*tope)->siguiente;
	return aux;
}
void push(Bateria **tope,Bateria *dato){
	dato->siguiente = (*tope);
	(*tope) = dato;
}



//IMPRESIONES

void ImprimirEstaciones(Estacion **InicioEstacion){
	if(!(*InicioEstacion))
		return;
	printf("\n| Estacion: %d - Baterias: %d - Personas: %d 	|\n",(*InicioEstacion)->ID, (*InicioEstacion)->nBaterias, (*InicioEstacion)->nPersonas );
	return(ImprimirEstaciones(&(*InicioEstacion)->siguiente));
}

void MostrarBaterias(Bateria **tope){
	if(!(*tope)){
		return;
	}
	if((*tope)->nPersonas>0){
        printf("\nNivel: %d - Humanos: %d\n",(*tope)->Nivel,(*tope)->nPersonas );
    }
	MostrarBaterias(&(*tope)->siguiente);
}
void ImprimirHumanos (Persona **inicio, Persona **ultimo){
	printf("\nID: %d - Nombre: %s - Edad: %d\n",(*inicio)->ID, (*inicio)->Nombre, (*inicio)->edad );
	if((*inicio) ==(*ultimo))
		return;
	return (ImprimirHumanos(&(*inicio)->siguiente,ultimo));

}
//FIN IMPRESIONES

//ALOJAMIENTOS

void CrearEstacion(Estacion **InicioEstacion){
	Estacion *NuevaEstacion =(Estacion*) malloc(sizeof(Estacion));
	if(!NuevaEstacion){
		printf("No se pudo reservar la memoria\n");
		return ;
	}
	NuevaEstacion->ID=++IDE;
	NuevaEstacion->nBaterias=0;
	NuevaEstacion->nPersonas=0;
	NuevaEstacion->tope=NULL;
	NuevaEstacion->siguiente=(*InicioEstacion);
	(*InicioEstacion)=NuevaEstacion;
	printf("Estacion creada con el ID: %d creada con exito\n",IDE );
	system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
}

void CrearBateria(Bateria **tope){
	Bateria *NBateria=(Bateria*) malloc(sizeof(Bateria));
	if(!NBateria){
		printf("No se pudo reservar la memoria\n");
		return;
	}
	if(!(*tope))
		NBateria->Nivel=0;
	else
	NBateria->Nivel=++(NBateria)->Nivel;
	NBateria->nPersonas=0;
	NBateria->inicio=NULL;
	NBateria->ultimo=NULL;
	NBateria->siguiente=(*tope);
	(*tope)=NBateria;
	printf("Nivel %d de bateria creado.\n",NBateria->Nivel );
}
void IngresarHumano(Bateria **tope, char nombre[30],char sexo,int edad){
 Persona *NuevaPersona= (Persona*) malloc(sizeof(Persona));
 if(!NuevaPersona){
 	printf("No se ha podido agregar a la persona\n");
 	return ;
 }
 strcpy(NuevaPersona->Nombre,nombre);
 NuevaPersona->Sexo=sexo;
 NuevaPersona->edad=edad;
 NuevaPersona->siguiente = NULL;
 NuevaPersona->ID=++IDP;
 if((*tope)->ultimo!=NULL){
 	(*tope)->ultimo->siguiente = NuevaPersona;
 }
 (*tope)->ultimo = NuevaPersona;
 if(!(*tope)->inicio)
 	(*tope)->inicio = NuevaPersona;
 (*tope)->ultimo->siguiente = (*tope)->inicio;
 printf("%s - Ingresado a la capsula correctamente.\n",nombre );
 ++(*tope)->nPersonas;
}
//FIN ALOJAMIENTOS

//ELIMINAR
int eliminarHumano(Persona **inicio, Persona **ultimo, int IDHumano){
    if((*inicio)>(*ultimo))
        return 0;
    if((*inicio)->ID == IDHumano){
        Persona *aux = (*inicio);
        (*inicio) = (*inicio)->siguiente;
        free(aux);
        return 1;
    }
    return eliminarHumano(&(*inicio)->siguiente,&(*ultimo),IDHumano);
}
//FIN ELIMINAR
//BUSQUEDAS

Estacion * BuscarEstacion( Estacion **InicioEstacion,int ID){
	if(!(*InicioEstacion))
		return NULL;
	if((*InicioEstacion)->ID==ID)
		return ((*InicioEstacion));
	return (BuscarEstacion(&(*InicioEstacion)->siguiente,ID));
}

//FIN BUSQUEDAS

//ORDENAMIENTOS
void ordenarCola(Persona **inicio){
    int bandera = 0;
    if(!(*inicio)->siguiente){
        return;
    }
    if((*inicio)->edad > (*inicio)->siguiente->edad){
        bandera = 1;
        Persona *aux=(*inicio),*aux1=(*inicio)->siguiente;
        (*inicio)=(*inicio)->siguiente;
        (*inicio)->siguiente=aux;
        (*inicio)->siguiente->siguiente=aux1;
    }
    ordenarCola(&(*inicio)->siguiente);
    if(bandera == 1){
        ordenarCola(inicio);
    }
}
//FIN ORDENAMIENTOS
//MENUS

void MenuIngresarHumano(Estacion *InicioEstacion){
	char nombre[30],sexo;
	int edad,op;
	while(getchar()!='\n');
	printf("Ingresa el nombre del humano: ");
	scanf("%[^\n]",nombre);
	while(getchar()!='\n');
	printf("Ingresa el Sexo ( M - F ):  ");
	scanf("%c",&sexo);
	while(getchar()!='\n');
	printf("Ingresa la edad: ");
	scanf("%d",&edad);
	do{
		printf("Deseas ingresarlo a la capsula (1 - SI, 2 - NO):  ");
		scanf("%d",&op);
		if(op==1){
			IngresarHumano(&(InicioEstacion)->tope,nombre,sexo,edad);
			InicioEstacion->nPersonas++;
			system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
		}else if(op>3){
			printf("Opcion invalida!\n");
			system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
		}
	}while(op>3);


}

//VERIFICADORES

int VerifiPila(Estacion *InicioEstacion){
	Bateria *aux;
	if(!(InicioEstacion)->tope){
		return 0;
	}
	if(InicioEstacion->tope->nPersonas!=20){
		MenuIngresarHumano(InicioEstacion);
		return 1;
	}
	push(&aux,pop(&InicioEstacion->tope));
	VerifiPila(InicioEstacion);
	push(&InicioEstacion->tope,aux);
	return 2;
}
int eliminarHumanoBateria(Bateria **tope,int nivel, int IDHumano){
	if(!(*tope))
		return 0;
	if((*tope)->Nivel == nivel){
		if(eliminarHumano(&(*tope)->inicio,&(*tope)->ultimo,IDHumano) == 1){
            (*tope)->nPersonas--;
            return 1;
        }
    }
	return(eliminarHumanoBateria(&(*tope)->siguiente,nivel,IDHumano));
}

int SelecNivel(Bateria **tope,int Nivel){
	if(!(*tope))
		return 0;
	if((*tope)->Nivel == Nivel && (*tope)->nPersonas > 0)
		return 1;
	return(SelecNivel(&(*tope)->siguiente,Nivel));
}

void VerifiBateria(Bateria **tope, int sbateria){
	Bateria *aux;
	if(!(*tope)){
		return;
	}
	if((*tope)->Nivel == sbateria){
		ImprimirHumanos(&(*tope)->inicio,&(*tope)->ultimo);
		return;
	}
	push(&aux,pop(tope));
	VerifiBateria(tope,sbateria);
	push(tope,aux);
}
//FIN VERIFICADORES
void MenuBaterias( Estacion *InicioEstacion, int sbateria){
	int IDHumano;
        printf(" -------------------------------- ");
        printf("\n|  HUMANOS REGISTRADOS.         |");
        printf("\n -------------------------------- ");
        VerifiBateria(&InicioEstacion->tope,sbateria);
        printf("\nSeleccione el ID del humano a eliminar: ");
        scanf("%d",&IDHumano);
        if(eliminarHumanoBateria(&InicioEstacion->tope,sbateria,IDHumano) == 1){
            printf("\nHumano eliminado con exito!\n");
            InicioEstacion->nPersonas--;
            system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
        }else{
            printf("\nNo se ha seleccionado un humano valido.\n");
            system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
        }
}

void MenuEstacion(Estacion *InicioEstacion){
   int op,sbateria;
    do{
        printf(" -------------------------------- ");
        printf("\n|  BIENVENIDO A LA ESTACION %d.    |",InicioEstacion->ID);
        printf("\n -------------------------------- ");
        printf("\n|1.-INGRESAR HUMANO.             |");
        printf("\n|2.-ELIMINAR HUMANO.             |");
        printf("\n|3.-ELIMINAR NIVEL.              |");
        printf("\n|4.-REGRESAR                     |");
        printf("\n -------------------------------- ");
        printf("\nElija una opci%cn: ",162);
        scanf("%d",&op);
        switch(op){
        case 1:
                system("clear");
                //system("cls");
                if(InicioEstacion->tope==NULL){
                	CrearBateria(&InicioEstacion->tope);
                	InicioEstacion->nBaterias++;
                }

                if(VerifiPila(InicioEstacion)==0){
                	if(InicioEstacion->tope->nPersonas==20){
                		CrearBateria(&InicioEstacion->tope);
                		InicioEstacion->nBaterias++;
                	}
                	MenuIngresarHumano(InicioEstacion);
                }


                break;
        case 2:
                system("clear");
                if(!(InicioEstacion)->tope){
                	printf("No se han registrado baterias\n");

                }
                else if(InicioEstacion->nPersonas>0){
				        printf(" -------------------------------- ");
				        printf("\n|  BATERIAS.                    |");
				        printf("\n -------------------------------- ");
				        MostrarBaterias(&InicioEstacion->tope);
				        printf("\nIngresa el nivel al que quieres acceder: ");
				        scanf("%d",&sbateria);
				        if(SelecNivel(&InicioEstacion->tope,sbateria)==0){
				        	printf("No se ingreso un nivel valido\n");
				        	system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
				        }else
				        	MenuBaterias(InicioEstacion,sbateria);
                }else{
                    printf("No existen humanos en las baterias.\n");
                    system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                }
                //system("cls");
                //EliminarHumano(&InicioEstacion->tope);
                break;
        case 3:
        		//EliminarNivel(&InicioEstacion->tope);
        		break;

        case 4: break;
        default:
                printf("\nOpci%cn no valida.\n",162);
        }
    system("clear");
    //system("cls");
    }while(op!=4);
}

void MenuMatrix(Estacion **InicioEstacion){
	   int op;
	   Estacion *aux=NULL;
    do{
        printf(" -------------------------------- ");
        printf("\n|  MATRIX.                        |");
        printf("\n -------------------------------- ");
        printf("\n|1.-INGRESAR ESTACION.            |");
        printf("\n|2.-ADMINISTRAR ESTACION          |");
        printf("\n|3.-REGRESAR                      |");
        printf("\n -------------------------------- ");
        printf("\nElija una opci%cn: ",162);
        scanf("%d",&op);
        switch(op){
        case 1:
                system("clear");
                //system("cls");
                CrearEstacion(InicioEstacion);

                break;
        case 2:
                system("clear");
                //system("cls");
				if(!InicioEstacion){
							printf("No existen estaciones\n");
							return;
						}
						int ID;

					        printf(" -------------------------------- ");
					        printf("\n|  ESTACIONES.                        |");
					        printf("\n -------------------------------- ");
					        ImprimirEstaciones(InicioEstacion);
					        printf("NOTA: INGRESE 0 PARA REGRESAR\n");
					        printf("\nElija un ID: ");
					        scanf("%d",&ID);
					        aux=BuscarEstacion(InicioEstacion,ID);
					    if(ID!=0 && aux!=NULL)
                		{
                			system("clear");
                			MenuEstacion(aux);}
                		else{
                			if(aux==NULL && ID!=0){
                			printf("ID no encontrado\n");
                			system("read -n 1 -s -p \"Presiona una tecla para continuar...\"");
                			}
                		}
                		system("clear");
					    //system("cls");
                break;
        case 3: break;
        default:
                printf("\nOpci%cn no valida.\n",162);
        }
    system("clear");
    //system("cls");
    }while(op!=3);

}

void MenuAyuda(Estacion **InicioEstacion){

}


//FIN MENUS



int main(int argc, char const *argv[])
{
	Estacion *InicioEstacion=NULL;
   int op;
    do{
        printf(" -------------------------------- ");
        printf("\n|  BIENVENIDO A LA MATRIX.        |");
        printf("\n -------------------------------- ");
        printf("\n|1.-ADMINISTRAR MATRIX.           |");
        printf("\n|2.-AYUDAR AMIGOS                 |");
        printf("\n|3.-SALIR                         |");
        printf("\n -------------------------------- ");
        printf("\nElija una opci%cn: ",162);
        scanf("%d",&op);
        switch(op){
        case 1:
                system("clear");
                //system("cls");
                MenuMatrix(&InicioEstacion);
                break;
        case 2:
                system("clear");
                //system("cls");
                MenuAyuda(&InicioEstacion);
                break;
        case 3: break;
        default:
                printf("\nOpci%cn no valida.\n",162);
        }
    system("clear");
    //system("cls");
    }while(op!=3);
	return 0;
}

