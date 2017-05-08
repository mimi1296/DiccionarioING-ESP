#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Dictionary Proyect:


struct Dict {
	char palIngles  [50];
	char palEspanol [50];
};
typedef struct Dict tipoDict;

struct Nodo {
	tipoDict info;
	struct Nodo *siguiente;
};

typedef struct Nodo tipoNodo;

tipoNodo *lista=NULL;

tipoNodo *crearNodo (tipoDict dict) {
	tipoNodo *nodo = (tipoNodo *)malloc (sizeof (tipoNodo));

	strcpy (nodo->info.palIngles, dict.palIngles);
	strcpy (nodo->info.palEspanol, dict.palEspanol);
	

	nodo->siguiente = NULL;
	return nodo;
}

tipoNodo* adicionarLista (tipoNodo *lista, tipoDict dict) {
	tipoNodo *nuevoNodo = crearNodo (dict);

	if (lista==NULL) { 
		lista = nuevoNodo;
	}else {
		tipoNodo *aptNodo = lista;
		while (aptNodo ->siguiente != NULL) {
			aptNodo = aptNodo->siguiente;
		}
		aptNodo->siguiente = nuevoNodo;
	}
	return lista;
}

void imprimirLista (tipoNodo *lista) {
	tipoNodo *aptNodo = lista;
	while (aptNodo != NULL) {
		printf ("<%s>:<%s>\n", aptNodo->info.palIngles, aptNodo->info.palEspanol);
		aptNodo = aptNodo->siguiente;
	}
}

tipoNodo* cargarDictToLista (char *nombreArchivoBin, tipoNodo *lista) {
	FILE *manejadorBin;
	manejadorBin = fopen (nombreArchivoBin, "rb"); 
	tipoDict dictTmp;
	int longitudBytes = sizeof (tipoDict);

	while (fread (&dictTmp, longitudBytes, 1, manejadorBin) == 1) {
		//printf ("<%s>:<%s>\n", dictTmp.palIngles, dictTmp.palEspanol);
		lista = adicionarLista (lista, dictTmp);
	}
	fclose (manejadorBin);
	return lista;
}

char *buscarPal(char *palABuscar, tipoNodo *list){
	tipoNodo *pal;
	char *palI =(char *)malloc(50);
	char *palE = (char*)malloc(50);
	if(list==NULL){
		return "no existe";
	}
	else{
		pal=list;
		while(pal != NULL){
			strcpy(palI, pal ->info.palIngles);
			strcpy(palE, pal ->info.palEspanol);
			if(strcmp(palABuscar,palI)==0){
				return palE;
			}
			else{
				if (strcmp(palABuscar, palE)==0){
					return palI;
				}
				else{
					pal= pal ->siguiente;
				}
			}
		}
	}
	return "no existe";
}

tipoNodo *InsertarList(tipoNodo *lst, int pos, tipoDict elemento){
	tipoNodo *p = lst;
	tipoNodo *Nodo = crearNodo(elemento);
	int cont;
	if(pos == 1){
		Nodo->siguiente = lst;
		lst = Nodo;
	}
	else{
		cont =1;
		while (cont<pos-1){
			cont++;
			p = p->siguiente;
		}
		Nodo ->siguiente=p -> siguiente;
		p->siguiente = Nodo;
	}
	return lst;
}

int buscarPosInsert(tipoNodo *lista, char *pal){
	int pos=1;
	if(lista==NULL){
		printf("Lista vacia\n");
	}
	tipoNodo *aptNodo =lista;
	while(aptNodo != NULL){
		if(strcmp(pal,aptNodo->info.palIngles)>0){
			pos++;
			aptNodo =aptNodo->siguiente;
		}
		else{
			break;
		}

	}
	return pos;
}

tipoNodo *EliminarPal(tipoNodo *lst, char *palabra){
	tipoNodo *aptNodo = lst;
	while(aptNodo->siguiente != NULL){
		if(strcmp(palabra, aptNodo->siguiente->info.palIngles)==0){
			aptNodo->siguiente=aptNodo->siguiente->siguiente;
		}
		else{
			if(strcmp(palabra, aptNodo->siguiente->info.palEspanol)==0){
				aptNodo->siguiente=aptNodo->siguiente->siguiente;
			}
		}
		aptNodo=aptNodo->siguiente;
	}
	return lst;
}

tipoNodo *Modificar(tipoNodo *lst, char *palabra){
	tipoNodo *aptNodo =lst;
	char *nueva = (char*)malloc(50);
	while(aptNodo != NULL){
		if(strcmp(palabra, aptNodo -> info.palIngles)==0){
			printf("Escriba la nueva traduccion de la palabra: \n");
			scanf("%s", nueva);
			strcpy(aptNodo -> info.palEspanol,nueva);
		}else{
			if(strcmp(palabra, aptNodo->info.palEspanol)==0){
				printf("Escriba la nueva traduccion de la palabra: \n");
				scanf("%s", nueva);
				strcpy(aptNodo -> info.palIngles,nueva);

			}
		}
		aptNodo = aptNodo -> siguiente;
	}
	return lst;
}

// MODIFICADA: Inicializo la palabra a retornar con "Nothing" que se reemplaza
// si encuentra algo entre tus rangos.
// pero, esos rangos hay que definirlos bien
char *comparar(tipoNodo *apt, char *pal){ //Funcion que recibe un apuntador tipo nodo y una palabra a comparar 
	char *palS = (char*)malloc(50);
	strcpy (palS, "Nothing");
	if((strcmp(pal,apt->info.palIngles)<2) && (strcmp(pal,apt ->info.palIngles)>(-2))){
		//printf("%s %s",pal,apt->info.palIngles );
		//printf("%d\n",strcmp(pal,apt->info.palIngles));
		strcpy(palS,apt->info.palIngles);
		return palS;

		   //Si lo que retorna strcmp del apuntador con la palabra esta entre -10 y 10 entonces que la retorne
	}else{
		if(((strcmp(pal,apt->info.palEspanol)<2)) && ((strcmp(pal,apt->info.palEspanol)>(-2)))) {
			//printf("%s %s",pal,apt->info.palEspanol );
			//printf("%d\n",strcmp(pal,apt->info.palEspanol));
			strcpy(palS,apt->info.palEspanol);
			return palS;
		}
	}
	
}

// MODIFICADA: ahora entra el numero de palabras que encontro
// e imprime una cadena y NO caracter X caracter
void imprimirSugeridos(char *sug[], int cont){ // imprime la matriz de palabras sugeridas.
	int i=0,j=0; 
	while(i < cont ){
		printf("\n");
		printf("%s",sug[i]);
		printf("\n");
		i++;
	}
}

void *BusquedaInt(tipoNodo *lst, char *palabra){ //busqueda inteligente.
	tipoNodo *aptNodo  = lst;
	char palabraRetornada [50];

	char **Sugeridos= (char**)malloc(7*sizeof(char*));
	for (int t=0;t<7;t++){
		Sugeridos[t]=(char*)malloc(50*sizeof(char));
	}
	int cont =0;
	int x = 0;
	if((buscarPal(palabra,aptNodo)!="no existe")){
		printf("La traduccion de la palabra es: %s\n",buscarPal(palabra,aptNodo));
		x = 0;
	}else{
		while(aptNodo != NULL){
			// MODIFICADA: Si comparar encuentra alguna entonces la adiciono a sugeridos
			// y tengo en cuenta que no me pase de 7 sugeridos
			strcpy (palabraRetornada, comparar(aptNodo,palabra));
			if (strcmp (palabraRetornada, "Nothing")!=0) {
				strcpy(Sugeridos[cont],palabraRetornada);
				cont++;
				if (cont >=7) break;
				x=1;
			}
			aptNodo = aptNodo -> siguiente;
		}
	}
	if (x==1){
		imprimirSugeridos(Sugeridos, cont);
	}
	
}


void imprimMEN(){
	system("cls");
	printf("Escriba la letra correspondiente a la opcion que desee seleccionar:\n");
	printf("\t <s>  Salir del programa. \n \t <b>  Realizar busqueda exacta. \n \t <a>  Adicionar palabra. \n \t <e>  Eliminar palabra. \n \t <m>  Modificar. \n \t <i>  Busqueda inteligente. \n");
}

tipoNodo *menu(tipoNodo *lista){
	while(1){
		char opcion;
		char *palabra = (char*)malloc(50);
		char *pal2 = (char *)malloc(50);
		imprimMEN();
		scanf("%c",&opcion);
		if(opcion == 's'){
			break;
		}else{
			if(opcion == 'b'){
				printf("Introduzca la palabra a buscar:\n");
				scanf("%s",pal2);
				palabra = buscarPal(pal2,lista);
				printf("La traduccion es: %s\n",palabra);
				system("PAUSE");
			}else{
				if(opcion == 'a'){
					int posInsert;
					tipoDict nueva;
					printf("Introduzca la palabra en ingles:\n");
					scanf("%s",nueva.palIngles);
					printf("Introduzca el significado en espanol:\n");
					scanf("%s",nueva.palEspanol);
					posInsert = buscarPosInsert(lista,nueva.palIngles);
					lista = InsertarList(lista, posInsert, nueva);
				}else{
					if(opcion == 'e'){
						printf("Escriba la palabra a eliminar: \n");
						scanf("%s",pal2);
						EliminarPal(lista,pal2);
					}else{
						if(opcion == 'm'){
							printf("Escriba la palabra a modificar: \n");
							scanf("%s",pal2);
							Modificar(lista,pal2);
						}else{
							if(opcion == 'i'){
								printf("Escriba la palabra a buscar:\n");
								scanf("%s",pal2);
								BusquedaInt(lista,pal2);
								system("PAUSE");
							}
						}
					}
				}
				
			}
		}
	}
	return lista;
}
	

int main (int argc, char * argv[]){
	tipoNodo *lista=NULL;
	lista = cargarDictToLista ("minidict.bin", lista);
	//imprimirLista (lista);
	char *palabra = argv[1];
	if (palabra != NULL){	
		palabra = buscarPal(palabra, lista);
		printf("%s\n",palabra);
	}
	else{
		menu(lista);
	}
	return 0;
}
