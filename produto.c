#include "hcliente.h"
#include "hfuncionario.h"
#include "hproduto.h"
#include <stdio.h>

//-------------------------------FUNCOES DO PRODUTO-------------------------------------------------------

//Depois que carregou o arquivo na memoria, entra o menu e as opcoes de produto.
void carregaproduto()
{
    //Ler os dados do arquivo.
    FILE *arqproduto;
	
	//abrir o arquivo
	arqproduto = fopen("arquivo_produto.txt","rb+");
    
    if(arqproduto == NULL)
    {
        printf("\nArquivo nao existe.");
        getchar();
        exit(0);
    }
    
    else
    {
        //contador de campos
        int idxCampos = 0;
        //contador de caracteres dos campos
        int idxCharCampos = 0;
        //contador de registros
        int regCount = 0;
        char auxCount[4] = { getc(arqproduto), getc(arqproduto), getc(arqproduto), getc(arqproduto) };
        
        //converter para inteiro
        int numproduto = atoi(auxCount);
        
        //alocar o array para estes registros
        struct strproduto *vetorproduto = (struct strproduto *) (malloc(numproduto * sizeof(struct pessoa)));
        
        //ler o '+' separador do contador de registro
        getc(arqproduto);
        
        //A) loop infinito (para cada registro)
        while(1)
        {
            //registro que esta sera lido do arquivo
            struct strproduto registro;
            
            //flag que indica se o arquivo terminou
            int breakingFlag = 0;
            
            //B) outro loop infinito (para cada campo)
            while(1)
            {
                //ler um caractere do arquivo
                char c = getc(arqproduto);
                
                //caractere que sera gravado na struct
                char rc = c;
                
                //se for o separador de campos (ou separador de registros)
                if (c == '-' || c == '+' || c == EOF)
                {
                    //caractere finalizador de string
                    rc = '\0';
                }
                
                //se for o campo nome atualmente
                if(idxCampos == 0)
                {
                    //concatenar o caractere no nome
                    registro.nome[idxCharCampos] = rc;
                }
                //se for o campo descricao
                else if(idxCampos == 1)
                {
                    //concatenar o caractere no descricao
                      registro.descricao[idxCharCampos] = rc;
                }
                //se for o campo preco
                else if(idxCampos == 2)
                {
                    //concatenar o caractere no preco
                    registro.preco[idxCharCampos] = rc;
                }
                
                //se o caractere do arquivo for separador de campo
                if(c == '-')
                {
                    //ir para o proximo campo da struct
                    idxCampos++;
                    //ir para o comeco da string
                    idxCharCampos = 0;
                }
                //se o caractere do arquivo for o separador de registro
                else if(c == '+')
                {
                    //ir novamente para o primeiro campo
                    idxCampos = 0;
                    //ir para o comeco da string
                    idxCharCampos = 0;
                    //sair do loop B
                    break;
                }
                //se chegou ao fim do arquivo
                else if(c == EOF)
                {
                    //indicar o fim do arquivo
                    breakingFlag = 1;
                    //sair do loop B
                    break;
                }
                //se nao aconteceu nada, so mudou de caractere
                else
                {
                    //apenas incrementar o contador
                    idxCharCampos++;
                }
            }
            
            //jogar no vetor
            vetorproduto[regCount] = registro;
            
            
            //se chegou ao fim do arquivo
            if(breakingFlag == 1)
            {
                //sair do loop A
                break;
            }
            //se ainda ha registros
            else
            {
                //incrementar o contador de registros
                regCount++;
            }
        }
    menuproduto(numproduto, vetorproduto, arqproduto);
}
}

void menuproduto(int numproduto, struct strproduto *vetorproduto, FILE *arqproduto)
{
    int contador=0, resposta=1, aux=0, opcao=0;
    char editarproduto[25];
    struct strproduto *auxvetorproduto;
    
    do{
        printf("Escolha uma opcao:");
        printf("\n1 - Cadastrar um produto.");
        printf("\n2 - Editar um produto cadastrado.");
        printf("\n3 - Excluir um produto cadastrado.");
        printf("\n4 - SAIR.");
        scanf("%d", &opcao);
        switch (opcao)
        {
                
                //Cadastrar novo produto
            case 1:
            {
                while(1)
                {
                    printf("\nDeseja cadastrar um produto ? 1/sim   ||   2/nao");
                    scanf("%d", &resposta);
                    if(resposta==1)
                    {
                        aux = numproduto;
                        numproduto = numproduto + 1;
                        struct strproduto *auxvetorproduto = (struct strproduto *) (malloc(aux * sizeof(struct strproduto)));
                        for(contador = 0; contador < aux; contador++)
                        {
                            auxvetorproduto[contador] = vetorproduto[contador];
                        }
                        struct strproduto *vetorproduto = (struct strproduto *) (malloc(numproduto * sizeof(struct strproduto)));
                        for(contador = 0; contador < aux; contador++)
                        {
                            vetorproduto[contador] = auxvetorproduto[contador];
                        }
                        for(contador = aux; contador<numproduto; contador++)
                        {
                            vetorproduto[contador] = preencheproduto(contador);
                        }
                        free(auxvetorproduto);
                    }
                    else
                        //sair quando a resposta for nao
                    { break; }
                }
            }
                break;
                
                //Editar produto cadastrado.
            case 2:
            {
                printf("\nEntre com o nome do produto:");
                scanf("%s", editarproduto);
                for(contador=0;contador<numproduto;contador++)
                {
                    if(strcmp(editarproduto, vetorproduto[contador].nome) == 0)
                    {
                        vetorproduto[contador] = preencheproduto(contador);
                    }
                }
                getchar();

            }
                break;
                
                //Excluir produto cadastrado.
            case 3:
            {
                printf("\nEntre com o nome do produto:");
                scanf("%s", editarproduto);
                for(contador=0;contador<numproduto;contador++)
                {
                    if(strcmp(editarproduto, vetorproduto[contador].nome) == 0)
                    {
                        vetorproduto[contador] = excluiproduto(contador);
                    }
                }
                
                printf("\nProduto nao encontrado.");
                getchar();
            }
                break;
                
                //Sair do programa e salvar os dados no arquivo.
            case 4:
            {
                discoproduto(numproduto, vetorproduto, arqproduto);
            }
                break;
        }
        printf("\n\n\nDeseja retornar ao menu de produtos ? 1/sim  ||  2/nao");
        scanf("%d", &opcao);
        //Sair do laco do menu e salvar todos os produtos da memoria no arquivo .txt
    }while(opcao==1);
    
    discoproduto(numproduto, vetorproduto, arqproduto);
    free(vetorproduto);
    fclose(arqproduto);
}

// Cadastra o produto na posicao contador do vetor.
struct strproduto preencheproduto(int contador)
{
    
    struct strproduto produto;
    
    printf("\nInforme nome: ");
	scanf("%s", produto.nome);
	printf("\nInforme a descricao: ");
	scanf("%s", produto.descricao);
	printf("\nInforme o preco: ");
	scanf("%s", produto.preco);
	
    return produto;
}

// No lugar de excluido, preenche com: nome: excluido - descricao: excluido - preco: excluido
struct strproduto excluiproduto(int contador)
{
    struct strproduto excluido;
    
    printf("\nPor favor, para excluir, digite 00000 em todos os campos:");
    printf("\nInforme nome: ");
	scanf("%s", excluido.nome);
	printf("\nInforme a descricao: ");
	scanf("%s", excluido.descricao);
	printf("\nInforme o preco: ");
	scanf("%s", excluido.preco);
    return excluido;
}

//Cadastra todos os produtos do vetor no arquivo .txt
void discoproduto (int numproduto, struct strproduto *vetorproduto, FILE *arqproduto)
{
    int contar;
    char separadorstruct = 43, separadordados= 45;
    arqproduto = fopen("arquivo_produto.txt", "rb+");
    
    if(numproduto < 10)
    {
        fprintf(arqproduto, "0");
        fprintf(arqproduto, "0");
        fprintf(arqproduto, "0");
        fprintf(arqproduto, "%d", numproduto);
    }
    else
    {
        if(numproduto > 9 &&  numproduto < 100)
        {
            fprintf(arqproduto, "0");
            fprintf(arqproduto, "0");
            fprintf(arqproduto, "%d",  numproduto);
        }
        else
        {
            if(numproduto > 99 && numproduto < 1000)
            {
                fprintf(arqproduto, "0");
                fprintf(arqproduto, "%d",  numproduto);
            }
            else
            {
                if(numproduto > 999)
                {
                    fprintf(arqproduto, "%d",  numproduto);
                }
            }
        }
    }
    fputs(&separadorstruct, arqproduto);
    for (contar=0; contar<numproduto; contar++)
    {
        fputs(vetorproduto[contar].nome, arqproduto);
        fputc(separadordados, arqproduto);
        fputs(vetorproduto[contar].descricao, arqproduto);
        fputc(separadordados, arqproduto);
        fputs(vetorproduto[contar].preco, arqproduto);
        fputs(&separadorstruct, arqproduto);
    }
}
