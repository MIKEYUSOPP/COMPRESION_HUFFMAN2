#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <ctime>
#include <string>
#include <limits>
#include <ios>
#include <time.h>

#define TAM 256

using namespace std;

//---------------------------------------------------------------------------------------------------
int can, can2, contador_claves;

//-----------------------------------------------------------------------------------------------
//FUNCION PARA OBTENER LA HORA Y FECHA ACTUAL
int horas, minutos, segundos, dias, meses, anios;
struct FECHA
{
	int minuto, segundo, hora;
	int dia, mes, anio;
};

FECHA hoy()
{
	time_t t;
	t= time(NULL);
	struct tm *f;
	f = localtime(&t);
	FECHA aux;

	aux.hora = f->tm_hour;
	aux.minuto = f->tm_min;
	aux.segundo = f->tm_sec;
	aux.anio = f->tm_year+1900;
	aux.mes = f->tm_mon+1;
	aux.dia = f->tm_mday;
	return aux;
}
//--------------------------------------------------------------------------------------------------
void mostrar_fecha(FECHA f)
{
	cout<<"\n     HORA: "<<f.hora<<":"<<f.minuto<<":"<<f.segundo<<" FECHA:"<<f.dia<<"/"<<f.mes<<"/"<<f.anio<<endl;
	horas = f.hora;
	minutos=f.minuto;
	segundos=f.segundo;
	dias=f.dia;
	meses=f.mes;
	anios=f.anio;
}
//---------------------------------------------------------------------------------------------------
void gotoxy(int x,int y)
{
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
}
//---------------------------------------------------------------------------------------------------
class CLIENTES_COM
{
private:
	private:
    char FOLIO[20], NOM_PER[35], PRECIO_PAG[20], RFC[20];
    char TELEFONO_CLI[15];
    char DOMICILIO[80];
    int HORA, MINUTO, SEGUNDO, DIA, MES, ANIO;
public:
    void Capturar(); //METODOS
    void Mostrar();
    void Buscar();
    void Eliminar();
    void Modificar();
    void INDEXAR();
    void Ordenar();
    void HUFFMAN_CH(char*, char*, char*, char*, char*, char*,int, int, int, int, int, int);
}x1, xx1;


struct INDICE
{
	int NUM_RE;
    char FOLIO[20];
}y1;

//-------------COMPACTACION DEL ARCHIVO----------------------------------------------------------------------------------------
typedef struct no
{
  unsigned char caracter;
  int frecuencia;
  struct no *izq, *der, *sig;
}No;

typedef struct
{
    No *inicio;
    int tam;
}Lista;
//----------------Parte 1: tabla de frecuencia------------------------------------------
void inicializacion_tabla_con_ceros(unsigned int tabla[])
{
    int i;
    for (i=0;i<TAM; i++)
    {
        tabla[i]=0;
    }

}

//----------------------------------------------------------
void llenar_tab_frecuencia(unsigned char texto[], unsigned int tab[])
{
    int i=0;
    while(texto[i]!='\0')
    {
        tab[texto[i]]++;
        i++;
    }
}

void imprimir_tab_frecuencia(unsigned int tab[])
{
    int i;

    printf("\n\tTABLA DE FRECUENCIA:\n");
    for(i=0;i<TAM;i++)
    {
        if(tab[i]>0)
        {
            printf("\t%d = %u = %c\n", i, tab[i], i);
        }
    }
}



//-----------Parte 2: Lista Enlazada ordenada-------------
void crear_lista(Lista *lista)
{
    lista->inicio = NULL;
    lista->tam = 0;
}

void insertar_ordenado(Lista *lista, No *no)
{
    No *aux;
    //La lista está vacia?
    if(lista->inicio==NULL)
    {
        lista->inicio = no;
        //lista->tam++;
    }
    //tiene una frecuencia más baja que el principio de la lista
    else if(no->frecuencia<lista->inicio->frecuencia)
    {
        no->sig=lista->inicio;
        lista->inicio=no;
        //lista->tam++;
    }
    else
    {
        aux = lista->inicio;
        while(aux->sig && aux->sig->frecuencia <= no->frecuencia)
            aux = aux->sig;
        no->sig = aux->sig;
        aux->sig = no;
        //lista->tam++;
    }
    lista->tam++;
}

void llenar_lista(unsigned int tab[], Lista *lista)
{
    int i;
    No *nuevo;
    for (i=0; i<TAM; i++)
    {
        if(tab[i]>0)
        {
            //nuevo = malloc(sizeof(No));
            nuevo=new no;
            if(nuevo)
            {
                nuevo->caracter = i;
                nuevo->frecuencia = tab[i],
                nuevo->der = NULL;
                nuevo->izq = NULL;
                nuevo->sig = NULL;

                //llenar_ordenado(lista, nuevo);
                insertar_ordenado(lista, nuevo);
            }

            else
            {
                printf("\tERROR al asignar memoria en llenar_lista!\n");
                break;
            }
        }

    }
}

void imprimir_lista(Lista *lista)
{
    No *aux= lista->inicio;

    printf("\n\n\tLISTA ORDENADA: \n\tTAMAÑO: %d\n", lista->tam);
    while(aux)
    {
        printf("\tCARACTER: %c - FRECUENCIA: %d\n", aux->caracter, aux->frecuencia);
        aux = aux->sig;
    }
}

//------------parte 3: formar arbol de huffman-------------------
No* remove_no_inicio(Lista *lista)
{
    No *aux = NULL;
    if(lista->inicio)
    {
        aux = lista ->inicio;
        lista->inicio = aux->sig;
        aux->sig = NULL;
        lista ->tam--;
    }


    return aux;
}

No *formar_arbol(Lista *lista)
{
    No *primero, *segundo, *nuevo;

    while(lista->tam>1)
    {
        primero = remove_no_inicio(lista);
        segundo = remove_no_inicio(lista);
        //nuevo = malloc(sizeof(No));
        nuevo= new no;
        if(nuevo)
        {
            nuevo->caracter = '+';
            nuevo->frecuencia = primero->frecuencia + segundo->frecuencia;
            nuevo->izq = primero;
            nuevo->der= segundo;
            nuevo->sig = NULL;

            insertar_ordenado(lista, nuevo);
        }
        else
        {
            printf("ERROR al asignar memoria en formar_arbol!");
            break;
        }
    }
    return lista ->inicio;
}


void imprimir_arbol(No *raiz, int tam)
{
    if(raiz->izq==NULL &&raiz->der==NULL)
    {
        printf("\tHOJA: %c\tAltura: %d\n", raiz->caracter, tam);
    }
    else
    {
        imprimir_arbol(raiz->izq, tam+1);
        imprimir_arbol(raiz->der, tam+1);
    }
}


//----------------FORMAR DICCIONARIO----------------------
int altura_arbol(No *raiz)
{
    int izq, der;

    if(raiz==NULL)
        return -1;
    else
    {
        izq  = altura_arbol(raiz->izq)+1;
        der = altura_arbol(raiz->der)+1;

        if(izq>der)
        {
            return izq;
        }
        else
        {
            return der;
        }
    }
}

char** aloca_diccionario(int columnas)
{
    char **diccionario;
    int i;

    //diccionario = new char** *TAM;

    diccionario=(char**)malloc (TAM*sizeof(char**));


    for(i=0;i<TAM;i++)
    //diccionario [i] = (char) calloc(columnas, sizeof(char));

    diccionario[i]= (char*)calloc( columnas, sizeof( char*));

    return diccionario;
}

void generar_diccionario(char **diccionario, No *raiz, char *camino, int columnas)
{
    char izquierda[columnas], derecha[columnas];
        if (raiz->izq == NULL && raiz ->der == NULL)
        {
            strcpy(diccionario[raiz->caracter], camino);
        }
        else
        {
            strcpy(izquierda, camino);
            strcpy(derecha, camino);

            strcat(izquierda, "0");
            strcat(derecha, "1");

            generar_diccionario(diccionario, raiz->izq, izquierda, columnas);
            generar_diccionario(diccionario, raiz->der, derecha, columnas);

        }
}


void imprimir_diccionario(char **diccionario)
{
    int i;

    printf("\n\n\tDICCIONARIO: \n");
    for(i=0; i<TAM; i++)
    {
        if(strlen(diccionario[i])>0)
        {
            printf("\t%3d:  %s\n", i, diccionario[i]);
        }
    }
}
//---------------------Parte 5: codificar texto------------------
int calcular_tamano_string(char **diccionario, unsigned char *texto)
{
    int i=0, tam=0;

    while(texto[i]!='\0')
    {
        tam = tam + strlen(diccionario [texto[i]]);
        i++;

    }
    return tam +1;

}
char* codificar(char **diccionario, unsigned char *texto)
{
    int i=0;
    int tam= calcular_tamano_string(diccionario, texto);
    char *codigo = (char*) calloc(tam, sizeof(char*));
    //(char*)calloc( columnas, sizeof( char*));

    while (texto[i]!='\0')
    {
        strcat(codigo, diccionario[texto[i]]);
        i++;
    }
    return codigo;
}


//--------DECODIFICAR---------------------------------
char *decodificar(char *texto, No *raiz)
{
    int i=0;
    //int tamano_string=strlen((char*)texto);
    int tamano_string=strlen(texto);
    No *aux = raiz;
    char temp [2];
    char *decodificado = (char*) calloc(tamano_string, sizeof(char*));

    //(char*) calloc(tam, sizeof(char*));

    while (texto[i]!='\0')
    {
        if(texto[i]=='0')
        {
            aux = aux ->izq;
        }
        else
        {
            aux = aux->der;
        }
        if(aux->izq == NULL&& aux->der==NULL)
        {
            temp[0] = aux->caracter;
            temp[1] = '\0';
            strcat(decodificado, temp);
            aux = raiz;
        }
        i++;
    }
    return decodificado;

}

//--------------------Parte 7: Compactar-------------------------
void compactar (char *str)
{
    FILE *archivo = fopen("COMPACTADO_HUFFMAN.bin", "wb");
    int i=0, j=7;
    unsigned char  mascara, byte = 0; //Un byte son 8 bits
    if(archivo)
    {
        while(str[i] != '\0')
        {
            /*SECUENCIA DE CEROS Y UNOS*//*10101010101001*/
            mascara = 1;
            if(str[i]=='1')
            {
                mascara = mascara<<j;
                byte = byte| mascara;
            }
            j--;
            if(j<0)
            {
                fwrite(&byte, sizeof(unsigned char), 1, archivo);
                byte = 0;
                j=7;
            }
            i++;
        }
        if(j!=7)//
        {
            fwrite(&byte, sizeof(unsigned char), 1, archivo);
        }
        fclose(archivo);
    }
    else
    {
        printf("\n\nERROR AL ABRIR/CREAR ARCHIVO DE COMPACTAR EN HUFFMAN\n\n");
    }
}
//--------Parte 8:
unsigned int eh_bit_um(unsigned char byte, int i)
{
    unsigned char mascara = (1<<i);
    return byte & mascara;

}
void descompactar (No *raiz)
{
    FILE *archivo = fopen("COMPACTADO_HUFFMAN.bin", "rb");
    No *aux = raiz;
    unsigned char byte;
    int i=0;

    if (archivo)
    {
        while(fread(&byte, sizeof(unsigned char), 1, archivo))
        {
            for(i=7; i>=0;i--)
            {
                if(eh_bit_um(byte, i))
                {
                    aux = aux ->der;

                }
                else
                {
                    aux=aux->izq;
                }

                if(aux->izq ==NULL && aux->der ==NULL)
                {
                    printf("%c", aux->caracter);
                    aux=raiz;
                }
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("\n\nERROR AL ABRIR ARCHIVO COMPACTADO EN HUFFMAN EN 'descompactar' \n\n");
    }
}

//----------------PARTE 9: Descompactar archivo------------------------
int descubrir_tamano()
{
    FILE *arc = fopen("CLIENTES2.txt", "r");
    int tam =0;
    if(arc)
    {
        while(fgetc(arc)!=-1)
        {
            tam++;
        }
        fclose (arc);
    }
    else
    {
        printf("\n\n\tERROR AL ABRIR ARCHIVO EN FUNCION DESCUBRIR TAMAÑO\n\n");
    }
    return tam;
}

void leer_texto(unsigned char *texto)
{
    FILE *arc = fopen ("CLIENTES2.txt", "r");
    char letra;
    int i=0;

    if (arc)
    {
        while(!feof(arc))
        {
            letra =fgetc(arc);
            if(letra!=-1)
            {
                texto[i]=letra;
                i++;
            }

        }
        fclose (arc);
    }
    else
    {
        printf("\n\n\tERROR AL ABRIR ARCHIVO EN FUNCION ´LEER TEXTO\n\n");
    }
}


//Funcion de llamado a Huffman-----------------
void Compactar()
{
	    //unsigned char texto[] = "VAMOS A APRENDER PROGRAMACIÓN";
    unsigned char *texto;
    unsigned int tabla_frecuencia[TAM];
    int tam=0;
    Lista lista;
    No *Arbol;
    int columnas;
    char **diccionario;
    char *codificado;
    char *decodificado;

    SetConsoleOutputCP(65001);

    tam = descubrir_tamano();

    //printf("\n\tCANTIDAD DE CARACTERES: %d\n", tam );
    texto = (unsigned char *)calloc(tam +2, sizeof(unsigned char*));
    leer_texto(texto);
    //printf("\n\tTEXTO: %s\n", texto);

    //------parte 1: tabla de frecuencia--------

    inicializacion_tabla_con_ceros(tabla_frecuencia);
    llenar_tab_frecuencia(texto, tabla_frecuencia);
    //imprimir_tab_frecuencia(tabla_frecuencia);

    //------parte 2: lista ordenada-------------
    crear_lista(&lista);
    llenar_lista(tabla_frecuencia, &lista);
    //imprimir_lista(&lista);

    //------parte 3: arbol binario de huffman------
    Arbol = formar_arbol(&lista);
    //printf("\n\tARBOL DE HUFFMAN:\n");
    //imprimir_arbol(Arbol, 0);

    //-----Parte 4: Formar diccionario------------
    columnas = altura_arbol(Arbol)+1;
    diccionario = aloca_diccionario(columnas);
    generar_diccionario (diccionario, Arbol, "", columnas);
    //imprimir_diccionario(diccionario);
    //-----Parte 5: Codificacion de la cadena -------------------------------
    codificado = codificar(diccionario, texto);
    //printf("\n\n\tTEXTO CODIFICADO: %s\n",codificado );
    //-----Parte 6: DECODIFICAR EL TEXTO CODIFICADO--------------
    decodificado = decodificar(codificado, Arbol);
    //printf("\n\n\tTEXTO DECODIFICADO: %s\n", decodificado);
    //---Parte 7: Compactar -------------------------------------
    compactar(codificado);
    //---Parte 8: Descompactar -------------------------------------
    //printf("\nARCHIVO DESCOMPACTADO!\n\n");
    //descompactar(Arbol);
    //printf("\n\n");
    free(texto);
    free(codificado);
    free(decodificado);
	

}

void Compactar2()
{
	    //unsigned char texto[] = "VAMOS A APRENDER PROGRAMACIÓN";
    unsigned char *texto;
    unsigned int tabla_frecuencia[TAM];
    int tam=0;
    Lista lista;
    No *Arbol;
    int columnas;
    char **diccionario;
    char *codificado;
    char *decodificado;

    SetConsoleOutputCP(65001);

    tam = descubrir_tamano();

    //printf("\n\tCANTIDAD DE CARACTERES: %d\n", tam );
    texto = (unsigned char *)calloc(tam +2, sizeof(unsigned char*));
    leer_texto(texto);
    printf("\n\tDATOS DEL TEXTO COMPACTADO CON EL ALGORITMO DE HUFFMAN:\n\n");
    //printf("\n\tTEXTO: %s\n", texto);
    //------parte 1: tabla de frecuencia--------

    inicializacion_tabla_con_ceros(tabla_frecuencia);
    llenar_tab_frecuencia(texto, tabla_frecuencia);
    imprimir_tab_frecuencia(tabla_frecuencia);

    //------parte 2: lista ordenada-------------
    crear_lista(&lista);
    llenar_lista(tabla_frecuencia, &lista);
    imprimir_lista(&lista);

    //------parte 3: arbol binario de huffman------
    Arbol = formar_arbol(&lista);
    printf("\n\tARBOL DE HUFFMAN:\n");
    imprimir_arbol(Arbol, 0);

    //-----Parte 4: Formar diccionario------------
    columnas = altura_arbol(Arbol)+1;
    diccionario = aloca_diccionario(columnas);
    generar_diccionario (diccionario, Arbol, "", columnas);
    imprimir_diccionario(diccionario);
    //-----Parte 5: Codificacion de la cadena -------------------------------
    codificado = codificar(diccionario, texto);
	printf("\n\n\tTEXTO CODIFICADO: %s\n",codificado );
    //-----Parte 6: DECODIFICAR EL TEXTO CODIFICADO--------------
    decodificado = decodificar(codificado, Arbol);
    //printf("\n\n\tTEXTO DECODIFICADO: %s\n", decodificado);
    //---Parte 7: Compactar -------------------------------------
    compactar(codificado);
    //---Parte 8: Descompactar -------------------------------------
    printf("\t\nARCHIVO DESCOMPACTADO:\n\n");
    descompactar(Arbol);
    //printf("\n\n");
    free(texto);
    free(codificado);
    free(decodificado);
	

}

//-----------------------------------------------------------------------------------------------------
void CLIENTES_COM::Capturar() // DE LA CLASE ALUMNO PERTENECE CAPTURAR ESO SIGNIFICAN LOS DOS PUNTOS
{

	ifstream ArchivoIf;
	ArchivoIf.open("CLIENTES2.bin", ios::binary);

	
	
    if (ArchivoIf.fail())
    {
			    ofstream Archivo2("CLIENTES2.bin", ios::out|ios::app|ios::binary);
			    ofstream Archivo4("CLIENTES2.txt", ios::out|ios::app);
			    ofstream Archivo3("INDICE_CLIENTES.bin", ios::out|ios::app|ios::binary);

				int i=0, P=1, G=14, pal=0, pal2=0, jj=0;
				int POSICION;

				gotoxy(5, 0);  printf("%c",201);
			    for (i=6;i<50;i++)
			    {
			        gotoxy(i, 0);printf("%c",205);

			    }
			    gotoxy(50, 0); printf("%c", 187);
			    gotoxy(5, 1);printf("%c",186);
			    printf("\tCAPTURAR DATOS DE LOS CLIENTES\n", 181);
			    gotoxy(50, 1);printf("%c",186);
				gotoxy(5, 2); printf("%c", 200);
				for (i=6;i<50;i++)
			    {
			        gotoxy(i, 2);printf("%c",205);

			    }
				gotoxy(50, 2);printf("%c",188);

                jj=jj+1;

				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				printf("\n\n     PERSONA %d\n", jj);
				printf("\n     ESCRIBA EL FOLIO DEL CLIENTE:\n     ", can);
				cin.sync();
				cin.getline(x1.FOLIO, 20);
				strcpy(y1.FOLIO, x1.FOLIO);
				cin.sync();
			    printf("\n     ESCRIBE EL NOMBRE DE LA PERSONA:\n     ");
			    cin.getline(x1.NOM_PER, 35);
			    cin.sync();
				printf("\n     %cCU%cL ES EL RFC DEL CLIENTE?\n     ", 168, 181);
				cin.getline(x1.RFC,20);
				cin.sync();
			    printf("\n     %cCU%cL ES LA TARIFA A PAGAR?\n     ", 168, 181);
			    cin.getline(x1.PRECIO_PAG, 20);
				cin.sync();
				printf("\n     %cCU%cL ES EL TELEFONO DEL CLIENTE?\n     ", 168, 181);
			    cin.getline(x1.TELEFONO_CLI, 15);
			    cin.sync();
			    FECHA actual;
			    actual = hoy();
			    mostrar_fecha(actual);
			    x1.HORA=horas;
			    x1.MINUTO=minutos;
			    x1.SEGUNDO=segundos;
			    x1.DIA=dias;
			    x1.MES=meses;
			    x1.ANIO=anios;
			    printf("\n     %cCU%cL ES EL DOMICILIO DEL ESTABLECIMENTO?\n     ", 168, 181);
			    cin.getline(x1.DOMICILIO, 80);
			    cin.sync();


			    can;
				y1.NUM_RE=jj;
				
				Archivo4<<"     -----------------------------------------------------------------------------------------------------------------------\n";
				Archivo4<<"     |     FOLIO-----------------------------------: "<<x1.FOLIO<<endl;
				Archivo4<<"     |     NOMBRE DEL CLIENTE----------------------: "<<x1.NOM_PER<<endl;
				Archivo4<<"     |     RFC DEL CLIENTE-------------------------: "<<x1.RFC<<endl;
				Archivo4<<"     |     TELEFONO DEL CLIENTE--------------------: "<<x1.TELEFONO_CLI<<endl;
				Archivo4<<"     |     PRECIO A PAGAR--------------------------: "<<x1.PRECIO_PAG<<endl;
				Archivo4<<"     |     DOMICILIO DE LA SUCURSAL----------------: "<<x1.DOMICILIO<<endl;
				Archivo4<<"     |     HORA Y FECHA DEL REGISTRO---------------: "<<"HORA: "<<x1.HORA<<":"<<x1.MINUTO<<":"<<x1.SEGUNDO<<"  FECHA: "<<x1.DIA<<"/"<<x1.MES<<"/"<<x1.ANIO<<endl;
				Archivo4<<"     -----------------------------------------------------------------------------------------------------------------------\n";
				Archivo2.write((char*)&x1,sizeof(x1));
				Archivo3.write((char*)&y1, sizeof(y1));
				Archivo2.close();
				Archivo3.close();
				Archivo4.close();
				remove("COMPACTADO_HUFFMAN.bin");
				Compactar();
				SetConsoleOutputCP(850);
    }

	else
	{
    	ofstream Archivo2("CLIENTES2.bin", ios::out|ios::app|ios::binary);
    	ofstream Archivo4("CLIENTES2.txt", ios::out|ios::app);
		ofstream Archivo3("INDICE_CLIENTES.bin", ios::out|ios::app|ios::binary);

		int POSICION;
    	string CLAVEMM;
    	string NUMEROMM;
    	int jj=0;
    	char NUMEROXD[5];
    	int pal2=0, i=0;

				gotoxy(5, 0);  printf("%c",201);
			    for (i=6;i<50;i++)
			    {
			        gotoxy(i, 0);printf("%c",205);

			    }
			    gotoxy(50, 0); printf("%c", 187);
			    gotoxy(5, 1);printf("%c",186);
			    printf("\tCAPTURAR DATOS DE LOS CLIENTES\n", 181);
			    gotoxy(50, 1);printf("%c",186);
				gotoxy(5, 2); printf("%c", 200);
				for (i=6;i<50;i++)
			    {
			        gotoxy(i, 2);printf("%c",205);

			    }
				gotoxy(50, 2);printf("%c",188);

                					ifstream CON;
                    CON.open("INDICE_CLIENTES.bin", ios::binary|ios::in);
                    while (!CON.eof())
                    {
						CON.read((char*)&y1,sizeof(y1));
		            	if(CON.eof())
		            	{
		            		break;
						}
		                y1.NUM_RE;
						y1.FOLIO;

						jj++;
        			}
                    CON.close();
					jj++;

				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				printf("\n\n     PERSONA %d\n", jj);
				printf("\n     ESCRIBA EL FOLIO DEL CLIENTE:\n     ", can);
				cin.sync();
				cin.getline(x1.FOLIO, 20);
				strcpy(y1.FOLIO, x1.FOLIO);
				cin.sync();
			    printf("\n     ESCRIBE EL NOMBRE DE LA PERSONA:\n     ");
			    cin.getline(x1.NOM_PER, 35);
			    cin.sync();
				printf("\n     %cCU%cL ES EL RFC DEL CLIENTE?\n     ", 168, 181);
				cin.getline(x1.RFC,20);
				cin.sync();
			    printf("\n     %cCU%cL ES LA TARIFA A PAGAR?\n     ", 168, 181);
			    cin.getline(x1.PRECIO_PAG, 20);
				cin.sync();
				printf("\n     %cCU%cL ES EL TELEFONO DEL CLIENTE?\n     ", 168, 181);
			    cin.getline(x1.TELEFONO_CLI, 15);
			    cin.sync();
			    FECHA actual;
			    actual = hoy();
			    mostrar_fecha(actual);
			    x1.HORA=horas;
			    x1.MINUTO=minutos;
			    x1.SEGUNDO=segundos;
			    x1.DIA=dias;
			    x1.MES=meses;
			    x1.ANIO=anios;
			    printf("\n     %cCU%cL ES EL DOMICILIO DEL ESTABLECIMENTO?\n     ", 168, 181);
			    cin.getline(x1.DOMICILIO, 80);
			    cin.sync();

			    can;
				y1.NUM_RE=jj;
				
				Archivo4<<"     |     FOLIO-----------------------------------: "<<x1.FOLIO<<endl;
				Archivo4<<"     |     NOMBRE DEL CLIENTE----------------------: "<<x1.NOM_PER<<endl;
				Archivo4<<"     |     RFC DEL CLIENTE-------------------------: "<<x1.RFC<<endl;
				Archivo4<<"     |     TELEFONO DEL CLIENTE--------------------: "<<x1.TELEFONO_CLI<<endl;
				Archivo4<<"     |     PRECIO A PAGAR--------------------------: "<<x1.PRECIO_PAG<<endl;
				Archivo4<<"     |     DOMICILIO DE LA SUCURSAL----------------: "<<x1.DOMICILIO<<endl;
				Archivo4<<"     |     HORA Y FECHA DEL REGISTRO---------------: "<<"HORA: "<<x1.HORA<<":"<<x1.MINUTO<<":"<<x1.SEGUNDO<<"  FECHA: "<<x1.DIA<<"/"<<x1.MES<<"/"<<x1.ANIO<<endl;
				Archivo4<<"     -----------------------------------------------------------------------------------------------------------------------\n";
				
				Archivo2.write((char*)&x1,sizeof(x1));
				Archivo3.write((char*)&y1, sizeof(y1));
				Archivo2.close();
				Archivo3.close();
				Archivo4.close();
				remove("COMPACTADO_HUFFMAN.bin");
				Compactar();
				SetConsoleOutputCP(850);
		}
}
//----------------------MOSTREAR REGISTROS
void CLIENTES_COM::Mostrar()
{
	ifstream Archivo;

	Archivo.open("CLIENTES2.bin", ios::binary|ios::in);//abrimos el archivo en modo lectura
	if(Archivo.is_open())
	{
			int i=0;
		    gotoxy(5, 0);  printf("%c",201);
		    for (i=6;i<75;i++)
		    {
		        gotoxy(i, 0);printf("%c",205);

		    }
		    gotoxy(75, 0); printf("%c", 187);
		    gotoxy(5, 1);printf("%c",186);
			printf("\tREGISTRO DE CLIENTES\n", 181);
		    gotoxy(75, 1);printf("%c",186);

			gotoxy(5, 2); printf("%c", 200);
			for (i=6;i<75;i++)
		    {
		        gotoxy(i, 2);printf("%c",205);

		    }
			gotoxy(75, 2);printf("%c",188);
			cout<<"\t\n\n     -----------------------------------------------------------------------------------------------------------------------\n";

			while (!Archivo.eof())
			{
				Archivo.read((char*)&x1,sizeof(x1));
            	if(Archivo.eof())
                	break;
				cout<<"     |     FOLIO-----------------------------------: "<<x1.FOLIO<<endl;
				cout<<"     |     NOMBRE DEL CLIENTE----------------------: "<<x1.NOM_PER<<endl;
				cout<<"     |     RFC DEL CLIENTE-------------------------: "<<x1.RFC<<endl;
				cout<<"     |     TELEFONO DEL CLIENTE--------------------: "<<x1.TELEFONO_CLI<<endl;
				cout<<"     |     PRECIO A PAGAR--------------------------: "<<x1.PRECIO_PAG<<endl;
				cout<<"     |     DOMICILIO DE LA SUCURSAL----------------: "<<x1.DOMICILIO<<endl;
				cout<<"     |     HORA Y FECHA DEL REGISTRO---------------: "<<"HORA: "<<x1.HORA<<":"<<x1.MINUTO<<":"<<x1.SEGUNDO<<"  FECHA: "<<x1.DIA<<"/"<<x1.MES<<"/"<<x1.ANIO<<endl;
				cout<<"     -----------------------------------------------------------------------------------------------------------------------\n";

			}

			Archivo.close();//cerramos el archivo
	}
	else
	{
				cout<<"\n\n     ------------------------------------\n";
				cout<<"	NO EXISTE UN REGISTRO DE DATOS\n";
				cout<<"     ------------------------------------\n\n     ";

	}

}

//----------------------------------------------------------------------------------------------------
void CLIENTES_COM::Buscar()
{
	system ("cls");
	
	ifstream Archivo;
	Archivo.open("CLIENTES2.bin", ios::binary|ios::in);//abrimos el archivo en modo lectura
	if(Archivo.is_open())
	{
				int i=0;
				gotoxy(5, 0);  printf("%c",201);
			    for (i=6;i<50;i++)
			    {
			        gotoxy(i, 0);printf("%c",205);

			    }
			    gotoxy(50, 0); printf("%c", 187);
			    gotoxy(5, 1);printf("%c",186);
			    printf("\tBUSQUEDA DE REGISTROS\n", 181);
			    gotoxy(50, 1);printf("%c",186);
				gotoxy(5, 2); printf("%c", 200);
				for (i=6;i<50;i++)
			    {
			        gotoxy(i, 2);printf("%c",205);

			    }
				gotoxy(50, 2);printf("%c",188);


			bool encontrado = false;
            char folioaux [15];


			cout<<"\n\n     DIGITA EL FOLIO DEL CLIENTE: \n     ";
			fflush(stdin);cin.getline(folioaux, 15);

			while(!Archivo.eof() && !encontrado)
			{
				Archivo.read((char*)&x1,sizeof(x1));
		        if(Archivo.eof())
		        {
		            break;
		        }
		        if(strcmp(x1.FOLIO,folioaux)==0)
		        {
						
						cout<<"\n     LOS DATOS DEL REGISTRO BUSCADO SON LOS SIGUIENTES: ";
						cout<<"\n\n     -----------------------------------------------------------------------------------------------------------------------\n";
						cout<<"     |     FOLIO-----------------------------------: "<<x1.FOLIO<<endl;
						cout<<"     |     NOMBRE DEL CLIENTE----------------------: "<<x1.NOM_PER<<endl;
						cout<<"     |     RFC DEL CLIENTE-------------------------: "<<x1.RFC<<endl;
						cout<<"     |     TELEFONO DEL CLIENTE--------------------: "<<x1.TELEFONO_CLI<<endl;
						cout<<"     |     PRECIO A PAGAR--------------------------: "<<x1.PRECIO_PAG<<endl;
						cout<<"     |     DOMICILIO DE LA SUCURSAL----------------: "<<x1.DOMICILIO<<endl;
						cout<<"     |     HORA Y FECHA DEL REGISTRO---------------: "<<"HORA: "<<x1.HORA<<":"<<x1.MINUTO<<":"<<x1.SEGUNDO<<"  FECHA: "<<x1.DIA<<"/"<<x1.MES<<"/"<<x1.ANIO<<endl;
						cout<<"     -----------------------------------------------------------------------------------------------------------------------\n";
						encontrado=true;
						break;
					}
			}
				Archivo.close();

			if (!encontrado)
			{
				cout<<"\n\n     --------------------------\n";
				cout<<"	DATO NO ENCONTRADO\n";
				cout<<"     --------------------------\n\n     ";
			}
	}

	else
	{
				cout<<"\n\n     ------------------------------------\n";
				cout<<"	NO EXISTE UN REGISTRO DE DATOS\n";
				cout<<"     ------------------------------------\n\n     ";

	}
	printf("\n\n     ");


}
//----------------------------------------------------------------------------------------------------
void CLIENTES_COM::Modificar()
{
	ifstream Archivo;
	//ifstream Archivo2;
	char folioaux [15];
	bool encontrado = false;
	int editar = 1;
	int pal=0;
    int  k=0;
	Archivo.open("CLIENTES2.bin", ios::binary|ios::in);
	if (Archivo.is_open())
	{
		//remove("INDICE.txt");
        //remove("INDICE2.txt");
        //ofstream NUEVOINDICE("INDICE.txt", ios::out|ios::app);
		cout<<"     -------------------------------------------\n";
		printf("              EDICI%cN DE REGISTROS\n", 224);
		cout<<"     -------------------------------------------\n";
		//ofstream aux2("auxiliar51.bin", ios::binary|ios::out|ios::app);
        //aux2<<"¦-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	¦\n";
        //aux2<<"¦          REGISTROS DE EMPLEADOS DE UNA TIENDA DE PINTURAS\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t¦\n";
        //aux2<<"¦-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------	¦\n";
        //aux2<<"| CLAVE\t\t| NOMBRE\t\t\t\t| CURP\t\t\t| RFC\t\t\t| CARGO\t\t\t| SUELDO\t\t| TELEFONO\t| DIRECCION\t\t\t\t\t\t\t\t\t\t\t|" "\n";
		printf("\n     DAME EL FOLIO DEL CLIENTE: ");
		cin>>folioaux;
		fflush(stdin);
		while (!Archivo.eof())
		{
			Archivo.read((char*)&x1,sizeof(x1));
		    if(Archivo.eof())
		    {
		        break;
		    }
		    if(strcmp(x1.FOLIO,folioaux)==0&&!encontrado)
		    {
						
						cout<<"\n     LOS DATOS DEL REGISTRO BUSCADO SON LOS SIGUIENTES: ";
						cout<<"\n\n     -----------------------------------------------------------------------------------------------------------------------\n";
						cout<<"     |     FOLIO-----------------------------------: "<<x1.FOLIO<<endl;
						cout<<"     |     NOMBRE DEL CLIENTE----------------------: "<<x1.NOM_PER<<endl;
						cout<<"     |     RFC DEL CLIENTE-------------------------: "<<x1.RFC<<endl;
						cout<<"     |     TELEFONO DEL CLIENTE--------------------: "<<x1.TELEFONO_CLI<<endl;
						cout<<"     |     PRECIO A PAGAR--------------------------: "<<x1.PRECIO_PAG<<endl;
						cout<<"     |     DOMICILIO DE LA SUCURSAL----------------: "<<x1.DOMICILIO<<endl;
						cout<<"     |     HORA Y FECHA DEL REGISTRO---------------: "<<"HORA: "<<x1.HORA<<":"<<x1.MINUTO<<":"<<x1.SEGUNDO<<"  FECHA: "<<x1.DIA<<"/"<<x1.MES<<"/"<<x1.ANIO<<endl;
						cout<<"     -----------------------------------------------------------------------------------------------------------------------\n";
						encontrado=true;
						printf("\n     %cDESEAS EDITAR EL REGISTRO?\n     ", 168);
						cin>>editar;
						
						break;
			}
			
		}
		Archivo.close();
		if (!encontrado)
		{
			cout<<"\n\n     --------------------------\n";
			cout<<"	DATO NO ENCONTRADO\n";
			cout<<"     --------------------------\n\n     ";
		}
		
		
		
		if (editar==1)
		{
				ofstream aux("auxiliar61.bin", ios::binary|ios::out|ios::app);
				ofstream aux2("auxiliar62.txt", ios::binary|ios::out|ios::app);
				ifstream DATOS;
				//ifstream Archivo2;
				fflush(stdin);
			    //ifstream indice("indice.txt");
			    aux2<<"     -----------------------------------------------------------------------------------------------------------------------\n";
			    
			    DATOS.open("CLIENTES2.bin", ios::binary|ios::in);
			    
		        while(!DATOS.eof())
		        {
		          DATOS.read((char*)&x1,sizeof(x1));
	     	      if(DATOS.eof())
			      {
			        break;
			      }
			      
				  if(strcmp(x1.FOLIO,folioaux)==0&&encontrado)
				  {
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
					        printf("\n     ESCRIBE EL NUEVO NOMBRE DEL CLIENTE:\n     ");
					       	cin.getline(x1.NOM_PER, 35);
					       	cin.sync();
					        printf("\n     %cCU%cL ES EL NUEVO RFC DEL CLIENTE?\n     ", 168, 181);
					        cin.getline(x1.RFC, 20);
							cin.sync();
							printf("\n     %cCU%cL ES EL NUEVO TELEFONO DEL CLIENTE?\n     ", 168, 181);
					        cin.getline(x1.TELEFONO_CLI, 15);
					        cin.sync();
					        printf("\n     %cCU%cNTO SERA LO QUE TENDR%c QUE PAGAR EL CLIENTE AHORA?\n     ", 168, 181, 181);
					        cin.getline(x1.PRECIO_PAG, 20);
					        cin.sync();
					        FECHA actual;
					        actual = hoy();
					        mostrar_fecha(actual);
					        x1.HORA=horas;
					        x1.MINUTO=minutos;
					        x1.SEGUNDO=segundos;
					        x1.DIA=dias;
					        x1.MES=meses;
					        x1.ANIO=anios;
					        printf("\n     %cCU%cL ES EL NUEVO DOMICILIO DEL ESTABLECIMENTO?\n     ", 168, 181);
					        cin.getline(x1.DOMICILIO, 80);
					        cin.sync();
					        
							aux2<<"     |     FOLIO-----------------------------------: "<<x1.FOLIO<<endl;
							aux2<<"     |     NOMBRE DEL CLIENTE----------------------: "<<x1.NOM_PER<<endl;
							aux2<<"     |     RFC DEL CLIENTE-------------------------: "<<x1.RFC<<endl;
							aux2<<"     |     TELEFONO DEL CLIENTE--------------------: "<<x1.TELEFONO_CLI<<endl;
							aux2<<"     |     PRECIO A PAGAR--------------------------: "<<x1.PRECIO_PAG<<endl;
							aux2<<"     |     DOMICILIO DE LA SUCURSAL----------------: "<<x1.DOMICILIO<<endl;
							aux2<<"     |     HORA Y FECHA DEL REGISTRO---------------: "<<"HORA: "<<x1.HORA<<":"<<x1.MINUTO<<":"<<x1.SEGUNDO<<"  FECHA: "<<x1.DIA<<"/"<<x1.MES<<"/"<<x1.ANIO<<endl;
							aux2<<"     -----------------------------------------------------------------------------------------------------------------------\n";		
					        
					        aux.write((char*)&x1,sizeof(x1));
					        
				    		
					}
			      	else
			      	{
			      			x1.FOLIO;
							x1.NOM_PER;
							x1.RFC;
							x1.TELEFONO_CLI;
							x1.PRECIO_PAG;
							x1.HORA;
							x1.MINUTO;
							x1.SEGUNDO;
							x1.DIA;
							x1.MES;
							x1.ANIO;
							x1.DOMICILIO;
							
							aux2<<"     |     FOLIO-----------------------------------: "<<x1.FOLIO<<endl;
							aux2<<"     |     NOMBRE DEL CLIENTE----------------------: "<<x1.NOM_PER<<endl;
							aux2<<"     |     RFC DEL CLIENTE-------------------------: "<<x1.RFC<<endl;
							aux2<<"     |     TELEFONO DEL CLIENTE--------------------: "<<x1.TELEFONO_CLI<<endl;
							aux2<<"     |     PRECIO A PAGAR--------------------------: "<<x1.PRECIO_PAG<<endl;
							aux2<<"     |     DOMICILIO DE LA SUCURSAL----------------: "<<x1.DOMICILIO<<endl;
							aux2<<"     |     HORA Y FECHA DEL REGISTRO---------------: "<<"HORA: "<<x1.HORA<<":"<<x1.MINUTO<<":"<<x1.SEGUNDO<<"  FECHA: "<<x1.DIA<<"/"<<x1.MES<<"/"<<x1.ANIO<<endl;
							aux2<<"     -----------------------------------------------------------------------------------------------------------------------\n";							
							
							aux.write((char*)&x1,sizeof(x1));
							
					  	
					}
				  	

				}


		DATOS.close();
		aux.close();
		aux2.close();
		remove("CLIENTES2.txt");
		remove("CLIENTES2.bin");
		//remove("REGISTRO DE FACTURAS.txt");
		
		rename("auxiliar61.bin", "CLIENTES2.bin");
		rename("auxiliar62.txt", "CLIENTES2.txt");
		//rename("auxiliar41.txt", "REGISTRO DE EMPLEADOS.txt");		
		remove("COMPACTADO_HUFFMAN.bin");
		Compactar();
		SetConsoleOutputCP(850);
		
		printf("\n\n     ");
		system("PAUSE");
		//aux2.close();
		}
		
	}

	else
	{
				cout<<"\n\n     ------------------------------------\n";
				cout<<"	NO EXISTE UN REGISTRO DE DATOS\n";
				cout<<"     ------------------------------------\n\n     ";
	}

}
//----------------------------------------------------------------------------------------------------
void CLIENTES_COM::Eliminar()
{
	ifstream Archivo;
	//ifstream Archivo2;
	char folioaux [15];
	bool encontrado = false;
	int editar = 1;
	int pal=0;
    int  k=0;
	Archivo.open("CLIENTES2.bin", ios::binary|ios::in);
	if (Archivo.is_open())
	{
	    ofstream NUEVOINDICE("INDICE_CLIENTES_aux.bin", ios::binary|ios::out|ios::app);
		cout<<"     -------------------------------------------\n";
		printf("              ELIMINACI%cN DE REGISTROS\n", 224);
		cout<<"     -------------------------------------------\n";
		//ofstream aux2("auxiliar51.bin", ios::binary|ios::out|ios::app);

		printf("\n     DAME EL FOLIO DEL CLIENTE: ");
		cin>>folioaux;
		fflush(stdin);
		while (!Archivo.eof())
		{
			Archivo.read((char*)&x1,sizeof(x1));
		    if(Archivo.eof())
		    {
		        break;
		    }
		    if(strcmp(x1.FOLIO,folioaux)==0&&!encontrado)
		    {
						
						cout<<"\n     LOS DATOS DEL REGISTRO QUE SE QUIERE ELIMINAR SON LOS SIGUIENTES: ";
						cout<<"\n\n     -----------------------------------------------------------------------------------------------------------------------\n";
						cout<<"     |     FOLIO-----------------------------------: "<<x1.FOLIO<<endl;
						cout<<"     |     NOMBRE DEL CLIENTE----------------------: "<<x1.NOM_PER<<endl;
						cout<<"     |     RFC DEL CLIENTE-------------------------: "<<x1.RFC<<endl;
						cout<<"     |     TELEFONO DEL CLIENTE--------------------: "<<x1.TELEFONO_CLI<<endl;
						cout<<"     |     PRECIO A PAGAR--------------------------: "<<x1.PRECIO_PAG<<endl;
						cout<<"     |     DOMICILIO DE LA SUCURSAL----------------: "<<x1.DOMICILIO<<endl;
						cout<<"     |     HORA Y FECHA DEL REGISTRO---------------: "<<"HORA: "<<x1.HORA<<":"<<x1.MINUTO<<":"<<x1.SEGUNDO<<"  FECHA: "<<x1.DIA<<"/"<<x1.MES<<"/"<<x1.ANIO<<endl;
						cout<<"     -----------------------------------------------------------------------------------------------------------------------\n";
						encontrado=true;
						printf("\n     %cDESEAS ELIMINAR EL REGISTRO?\n     ", 168);
						cin>>editar;
						
						break;
			}
			
		}
		Archivo.close();
		if (!encontrado)
		{
			cout<<"\n\n     --------------------------\n";
			cout<<"	DATO NO ENCONTRADO\n";
			cout<<"     --------------------------\n\n     ";
		}
		
		
		
		if (editar==1)
		{
				ofstream aux("auxiliar61.bin", ios::binary|ios::out|ios::app);
				ofstream aux2("auxiliar62.txt", ios::binary|ios::out|ios::app);
				ifstream DATOS;
				//ifstream Archivo2;
				fflush(stdin);
				aux2<<"     -----------------------------------------------------------------------------------------------------------------------\n";
			    //ifstream indice("indice.txt");
			    DATOS.open("CLIENTES2.bin", ios::binary|ios::in);
			    
		        while(!DATOS.eof())
		        {
		          DATOS.read((char*)&x1,sizeof(x1));
	     	      if(DATOS.eof())
			      {
			        break;
			      }
			      
				  if(strcmp(x1.FOLIO,folioaux)==0&&encontrado)
				  {
						cout<<"\n\n     ------------------------------------------------\n";
						cout<<"     EL DATO SE HA ELIMINADO CORRECTAMENTE\n";
						cout<<"     ------------------------------------------------\n";	
				  }
			      else
			      {
			      	k++;
			      	
			      			x1.FOLIO;
			      			strcpy(y1.FOLIO, x1.FOLIO);			      			
							x1.NOM_PER;
							x1.RFC;
							x1.TELEFONO_CLI;
							x1.PRECIO_PAG;
							x1.HORA;
							x1.MINUTO;
							x1.SEGUNDO;
							x1.DIA;
							x1.MES;
							x1.ANIO;
							x1.DOMICILIO;
							y1.NUM_RE=k;
							
							aux2<<"     |     FOLIO-----------------------------------: "<<x1.FOLIO<<endl;
							aux2<<"     |     NOMBRE DEL CLIENTE----------------------: "<<x1.NOM_PER<<endl;
							aux2<<"     |     RFC DEL CLIENTE-------------------------: "<<x1.RFC<<endl;
							aux2<<"     |     TELEFONO DEL CLIENTE--------------------: "<<x1.TELEFONO_CLI<<endl;
							aux2<<"     |     PRECIO A PAGAR--------------------------: "<<x1.PRECIO_PAG<<endl;
							aux2<<"     |     DOMICILIO DE LA SUCURSAL----------------: "<<x1.DOMICILIO<<endl;
							aux2<<"     |     HORA Y FECHA DEL REGISTRO---------------: "<<"HORA: "<<x1.HORA<<":"<<x1.MINUTO<<":"<<x1.SEGUNDO<<"  FECHA: "<<x1.DIA<<"/"<<x1.MES<<"/"<<x1.ANIO<<endl;
							aux2<<"     -----------------------------------------------------------------------------------------------------------------------\n";		
							
														
							aux.write((char*)&x1,sizeof(x1));
							NUEVOINDICE.write((char*)&y1, sizeof(y1));
					  	
				 }
				  	

			}

		
		DATOS.close();
		aux.close();
		aux2.close();
		NUEVOINDICE.close();
		remove("INDICE_CLIENTES.bin");
	    remove("INDICEBINARIO3.bin");
	    remove("CLIENTES2.txt");
	    remove("CLIENTES2.bin");
		//remove("REGISTRO DE FACTURAS.txt");
		rename("INDICE_CLIENTES_aux.bin", "INDICE_CLIENTES.bin");
		rename("auxiliar62.txt", "CLIENTES2.txt");
		rename("auxiliar61.bin", "CLIENTES2.bin");
		
		
		remove("COMPACTADO_HUFFMAN.bin");
		Compactar();
		SetConsoleOutputCP(850);
		//rename("auxiliar41.txt", "REGISTRO DE EMPLEADOS.txt");
		printf("\n\n     ");
		system("PAUSE");
		//aux2.close();
		}
		
	}

	else
	{
				cout<<"\n\n     ------------------------------------\n";
				cout<<"	NO EXISTE UN REGISTRO DE DATOS\n";
				cout<<"     ------------------------------------\n\n     ";
	}
}


//----------------------------------------------------------------------------------------------------
void CLIENTES_COM::INDEXAR()
{

    ifstream Archivo;
	string  clave;
	string numero;

	Archivo.open("INDICE_CLIENTES.bin", ios::binary|ios::in);//abrimos el archivo en modo lectura
	if(Archivo.is_open())
	{
			int i=0;
		    gotoxy(5, 0);  printf("%c",201);
		    for (i=6;i<75;i++)
		    {
		        gotoxy(i, 0);printf("%c",205);

		    }
		    gotoxy(75, 0); printf("%c", 187);
		    gotoxy(5, 1);printf("%c",186);
			printf("\tINDICE ORDENADO DE FOLIOS\n", 181);
		    gotoxy(75, 1);printf("%c",186);

			gotoxy(5, 2); printf("%c", 200);
			for (i=6;i<75;i++)
		    {
		        gotoxy(i, 2);printf("%c",205);

		    }
			gotoxy(75, 2);printf("%c",188);
			cout<<"\t\n\n     -----------------------------------------------------------------------------------------------------------------------\n";

			while (!Archivo.eof())
			{
				Archivo.read((char*)&y1,sizeof(y1));
			    if(Archivo.eof())
			        break;
				
				cout<<"     |     REGISTRO "<<y1.NUM_RE<<"---------------------: "<<y1.FOLIO<<endl;
				cout<<"     -----------------------------------------------------------------------------------------------------------------------\n";
				
			}
			cout<<endl<<"\n     ";
			Archivo.close();

	}
	else
	{
				cout<<"\n\n     ------------------------------------\n";
				cout<<"	NO EXISTE UN REGISTRO DE DATOS\n";
				cout<<"     ------------------------------------\n\n     ";

	}

}

//----------------------------------------------------------------------------------------------------
void ordenar_alf()
{
    int i, j=1;
    ifstream ArchivoOr;
    ifstream ArchivoIn;
    string clave;
    string numero_2;
    string numero;
    char folioaux[14];
    int numeroaux;

    struct CLAVES
    {
        char folios[14];
    }A[contador_claves], B;
    
    struct CLAVE_NUM
    {
        char folios[14];
       	int num;
    }AB[contador_claves];



    ArchivoOr.open("INDICE ORDENADO3.bin", ios::binary|ios::in);//abrimos el archivo en modo lectura
    if (ArchivoOr.is_open())
    {
        ofstream AUX("INDICE EN ORDEN ALFABETICO.bin", ios::binary|ios::out|ios::app);
        ofstream AUX2("INDICE EN ORDEN CON NUMEROS.bin", ios::binary|ios::out|ios::app);

			while (!ArchivoOr.eof())
			{
				ArchivoOr.read((char*)&y1, sizeof(y1));
				if(ArchivoOr.eof())
				break;
				
			    strcpy(folioaux, y1.FOLIO);
				//getline(ArchivoOr, clave);
                strcpy(A[j].folios, folioaux);
				j++;
            }
            ArchivoOr.close();

	       for ( i = 1; i <= contador_claves; i++ )
	        {
	                for (  j = i + 1; j <= contador_claves; j++ )
	                {
	
	                    if ( ( strcoll(/*1º*/ A[i].folios, /*2º*/A[j].folios) ) > 0 ) {
	                        strcpy ( B.folios, A[i].folios );
	                        strcpy ( A[i].folios, A[j].folios );
	                        strcpy ( A[j].folios, B.folios );
	                    }
	                }
	        }
	        
            for (int h=1; h<=contador_claves;h++)
            {
                //cout<<"\nCLAVE "<<h<<endl;
                AUX.write((char*)&A[h].folios, sizeof(A[h].folios));
                //AUX<<A[h].claves<<endl;
            }

            AUX.close();

            for (int g=1; g<=contador_claves; g++)
            {
                ArchivoIn.open("INDICE_CLIENTES.bin", ios::binary|ios::in);//abrimos el archivo en modo lectura
                while (!ArchivoIn.eof())
                {
                	ArchivoIn.read((char*)&y1, sizeof(y1));
                	if(ArchivoIn.eof())
                	break;
                	
                    if (strcmp(y1.FOLIO, A[g].folios)==0)
                    {
                        strcpy(folioaux, A[g].folios);
                        strcpy(AB[g].folios, folioaux);
                        //strcpy(numeroaux, y.NUM_RE);
                        numeroaux=y1.NUM_RE;
                        AB[g].num = numeroaux;

                    }
                }
                ArchivoIn.close();

            }

            for (int v=1; v<=contador_claves;v++)
            {
                //cout<<"\nCLAVE "<<h<<endl;
                y1.NUM_RE=AB[v].num;
                strcpy(y1.FOLIO, AB[v].folios);
                AUX2.write((char*)&y1, sizeof(y1));
                //AUX2<<AB[v].num<<endl<<AB[v].folios<<endl;
            }
            AUX2.close();




    }
    else
    {
        cout<<"\n\n     ------------------------------------\n";
        cout<<"	NO EXISTE UN REGISTRO DE DATOS\n";
        cout<<"     ------------------------------------\n\n     ";
    }

    remove("INDICE ORDENADO3.bin");
    remove("INDICEBINARIO3.bin");
    remove ("INDICE EN ORDEN ALFABETICO.bin");
    rename("INDICE EN ORDEN CON NUMEROS.bin", "INDICEBINARIO3.bin");
}

//-----------------------------------------------------------------------------------------------

void CLIENTES_COM::Ordenar()
{
    ofstream Archivo2("INDICE ORDENADO3.bin", ios::binary|ios::out|ios::app);
    ifstream Archivo;
	string  clave;
	string numero;
    //int i;

            Archivo.open("INDICE_CLIENTES.bin", ios::binary|ios::in);//abrimos el archivo en modo lectura
            if(Archivo.is_open())
            {
                    int i=0;
                    gotoxy(5, 0);  printf("%c",201);
                    for (i=6;i<75;i++)
                    {
                        gotoxy(i, 0);printf("%c",205);

                    }
                    gotoxy(75, 0); printf("%c", 187);
                    gotoxy(5, 1);printf("%c",186);
                    printf("\tINDICE ORDENADO DE LOS FOLIOS DE LOS CLIENTES\n", 181);
                    gotoxy(75, 1);printf("%c",186);

                    gotoxy(5, 2); printf("%c", 200);
                    for (i=6;i<75;i++)
                    {
                        gotoxy(i, 2);printf("%c",205);

                    }
                    gotoxy(75, 2);printf("%c",188);
                    //cout<<"\t\n\n-----------------------------------------------------------------------------------------------------------------------\n";

                    i=0;
                            
                	while (!Archivo.eof())
					{
						Archivo.read((char*)&y1,sizeof(y1));
					    if(Archivo.eof())
					    break;
					    
					    y1.NUM_RE;
					    y1.FOLIO;
					    Archivo2.write((char*)&y1, sizeof(y1));
					    i++;
                    }
                    Archivo2.close();
                    Archivo.close();

                	contador_claves=i;
                    //printf("\n\n%d\n\n", contador_claves);
                    ordenar_alf();


                    ifstream TER;
                	TER.open("INDICEBINARIO3.bin", ios::binary|ios::in);//abrimos el archivo en modo lectura
                    cout<<"\t\n\n     -----------------------------------------------------------------------------------------------------------------------\n";

                    while (!TER.eof())
                	{
                		TER.read((char*)&y1, sizeof(y1));
                    	if(TER.eof())
                            break;
                                	
                    	cout<<"     |     REGISTRO "<<y1.NUM_RE<<"---------------------: "<<y1.FOLIO<<endl;
                        cout<<"     -----------------------------------------------------------------------------------------------------------------------\n";
                    }
                    cout<<endl<<"\n     ";
                    system("PAUSE");
                    TER.close();


            }
            else
            {
                        cout<<"\n\n     ------------------------------------\n";
                        cout<<"	NO EXISTE UN REGISTRO DE DATOS\n";
                        cout<<"     ------------------------------------\n\n     ";

            }

}







//----------------------------------------------------------------------------------------------------
int main()
{
    int opc, opc2;
    do {

//ESTRUCTURA DEL PROGRAMA
	system("cls");
    int i=0, P=1, G=14;
    gotoxy(5, 0);  printf("%c",201);
    for (i=6;i<75;i++)
    {
        gotoxy(i, 0);printf("%c",205);

    }
    gotoxy(75, 0); printf("%c", 187);
    gotoxy(5, 1);printf("%c",186);
	printf("\tREGISTRO DE CLIENTES\n", 181);
    gotoxy(75, 1);printf("%c",186);

	gotoxy(5, 2); printf("%c", 200);
	for (i=6;i<75;i++)
    {
        gotoxy(i, 2);printf("%c",205);

    }
	gotoxy(75, 2);printf("%c",188);


        printf("\n\n     - RELLENA EL SIGUIENTE FORMULARIO PARA REGISTRAR LOS DATOS DE LOS REGISTROS DENTRO DEL ARCHIVO DE CLIENTES.\n", 181);
        printf("     * EL PROGRAMA TE MOSTRAR%c UN MEN%c PARA QUE REALICES DISTINTAS ACCIONES CON LOS DATOS DE LOS CLIENTES QUE YA HAYAS REGISTRADO.\n\n", 181, 233);
        cout << "\n\t1.- CAPTURAR \n\t2.- MOSTRAR \n\t3.- BUSCAR \n\t4.- MODIFICAR \n\t5.- ELIMINAR \n\t6.- GENERAR INDICES CON LAS CLAVES \n\t7.- ORDENAR INDICE \n\t8.- LEER ARCHIVO COMPACTADO \n\t9.- SALIR\n\n\tSELECCIONA LA OPCION (1-9): ";
        cin >> opc;



        switch (opc)
        {
        case 1:
            system("cls");
            can=0;
            do
			{
                can++;
                x1.Capturar();
                printf("\n\n     %cDESEAS REGISTRAR LA FACTURA DE OTRA COMPRA? 1(SI) || 2 O CUALQUIER OTRO NUMERO (NO)\n     ", 168, 224);
                cin >> opc2;
              system("cls");

            } while (opc2 != 2);
            break;

       case 2:
        	system("cls");
			x1.Mostrar();
			printf("\n\n     ");
			system("PAUSE");
            break;

        case 3:
		x1.Buscar();
		system("PAUSE");
            break;

        case 4:
        system("cls");
		x1.Modificar();
            break;

        case 5:
        system("cls");
		x1.Eliminar();
            break;
        case 6:
        system("cls");
        x1.INDEXAR();
        system("pause");
            break;
       case 7:
            system("cls");
            x1.Ordenar();
            break;
       case 8:
       		system("cls");
       		remove("COMPACTADO_HUFFMAN.bin");
       		Compactar2();
       		SetConsoleOutputCP(850);
       		printf("\n\n\t");
       		system("Pause");
       	

        }
    } while (opc != 9);

	return 0;
}
