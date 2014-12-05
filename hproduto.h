#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//Prototipos
//Prototipos_Produtos
struct strproduto preencheproduto(int);
struct strproduto excluiproduto(int);
void discoproduto(int, struct strproduto *, FILE *);
void menuproduto (int, struct strproduto *, FILE *);
void carregaproduto();

//Structs
//Struct_produto
typedef struct strproduto
{
    char nome[25], descricao[100], preco[6];
};
struct strproduto produto;
