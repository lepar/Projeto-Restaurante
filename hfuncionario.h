#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Prototipos
//Prototipos_Funcionario
struct strfuncionario preenchefuncionario(int);
struct strfuncionario excluifuncionario(int);
void discofuncionario(int, struct strfuncionario *, FILE *);
void menufuncionario (int, struct strfuncionario *, FILE *);
void carregafuncionario ();

//Structs
//Struct_funcionario
struct strfuncionario
{
    char nome[25], funcao[20], codigo[6];
};
struct strfuncionario funcionario;
