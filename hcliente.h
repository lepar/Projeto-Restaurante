#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prototipos
//Menu principal do projeto
void menuprincipalprojeto();

//Prototipos_Cliente
struct pessoa preenchecliente(int);
struct pessoa excluicliente(int);
void discocliente(int, struct pessoa *, FILE *);
void menucliente (int, struct pessoa *, FILE *);
void carregacliente ();

//Structs
//Struct_cliente
struct pessoa
{
    char nome[30], pessoas[2], mesa[2];
};
struct pessoa cliente;
