#include "hcliente.h"
#include "hfuncionario.h"
#include "hproduto.h"
#include <stdio.h>

//-------------------------------FUNCAO DO MENU PRINCIPAL DO PROJETO--------------------------------------
void menuprincipalprojeto()
{
    int opcprincipal, auxopc;
    
    do
    {
        printf("\nSelecione uma opcao abaixo:");
        printf("\n1 - Entrar no menu de clientes.");
        printf("\n2 - Entrar no menu de funcionarios.");
        printf("\n3 - Entrar no menu de produtos.");
        printf("\n4 - Sair.");
        scanf("%d", &opcprincipal);
        do
        {
            if(opcprincipal > 4)
            {
                printf("\nPor favor, digite uma opcao entre 1 e 4:");
                scanf("%d", &opcprincipal);
            }
        }while(opcprincipal > 4);
    
        switch (opcprincipal)
        {
            case 1:
                carregacliente();
                break;
            case 2:
                carregafuncionario();
                break;
            case 3:
                carregaproduto();
                break;
            case 4:
                exit(0);
                break;
        }
        printf("\n\n\nDeseja voltar ao menu principal ?    1/sim  ||  2/nao:");
        scanf("%d", &auxopc);
    }while(auxopc == 1);
}

//-------------------------------FUNCOES DO CLIENTE-------------------------------------------------------
//Carrega todos os dados do arquivo na memoria
void carregacliente()
{
    //Ler os dados do arquivo
    FILE *arqcliente;
	
	//abrir o arquivo
	arqcliente = fopen("arquivo_cliente.txt","rb+");
    
    if(arqcliente == NULL)
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
        char auxCount[4] = { getc(arqcliente), getc(arqcliente), getc(arqcliente), getc(arqcliente) };
        
        //converter para inteiro
        int numcliente = atoi(auxCount);
        
        //alocar o array para estes registros
        struct pessoa *vetorcliente = (struct pessoa *) (malloc(numcliente * sizeof(struct pessoa)));
        
       //ler o '+' separador do contador de registro
        getc(arqcliente);
        
        //A) loop infinito (para cada registro)
        while(1)
        {
            //registro que esta sera lido do arquivo
            struct pessoa registro;
            
            //flag que indica se o arquivo terminou
            int breakingFlag = 0;
            
            //B) outro loop infinito (para cada campo)
            while(1)
            {
                //ler um caractere do arquivo
                char c = getc(arqcliente);
                
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
                //se for o campo pessoas
                else if(idxCampos == 1)
                {
                    //concatenar o caractere no pessoas
                    registro.pessoas[idxCharCampos] = rc;
                }
                //se for o campo mesa
                else if(idxCampos == 2)
                {
                    //concatenar o caractere no mesa
                    registro.mesa[idxCharCampos] = rc;
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
            vetorcliente[regCount] = registro;
            
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
        
        //fechar o arquivo
        fclose(arqcliente);
        
        //chama a funcao menu
        menucliente(numcliente, vetorcliente, arqcliente);
    }
}

// Menu principal do cliente
void menucliente(int numcliente, struct pessoa *vetorcliente, FILE *arqcliente)
{
    int contador=0, resposta=1, aux=0, opcao=0;
    char editarcliente[25];
    struct pessoa *auxvetorcliente;
    
    do{
        printf("Escolha uma opcao:");
        printf("\n1 - Cadastrar um clientes.");
        printf("\n2 - Editar um cliente cadastrado.");
        printf("\n3 - Excluir um cliente cadastrado.");
        printf("\n4 - SAIR.");
        scanf("%d", &opcao);
        switch (opcao)
        {
                
                //Cadastrar novo cliente
            case 1:
            {
                while(1)
                {
                    printf("\nDeseja cadastrar um cliente ? 1/sim   ||   2/nao");
                    scanf("%d", &resposta);
                    if(resposta==1)
                    {
                        aux = numcliente;
                        numcliente = numcliente + 1;
                        struct pessoa *auxvetorcliente = (struct pessoa *) (malloc(aux * sizeof(struct pessoa)));
                        for(contador = 0; contador < aux; contador++)
                        {
                            auxvetorcliente[contador] = vetorcliente[contador];
                        }
                        struct pessoa *vetorcliente = (struct pessoa *) (malloc(numcliente * sizeof(struct pessoa)));
                        for(contador = 0; contador < aux; contador++)
                        {
                            vetorcliente[contador] = auxvetorcliente[contador];
                        }
                        for(contador = aux; contador<numcliente; contador++)
                        {
                            vetorcliente[contador] = preenchecliente(contador);
                        }
                        free(auxvetorcliente);
                    }
                    else
                        //sair quando a resposta for nao
                    { break; }
                }
            }
                break;
                
                //Editar cliente cadastrado.
            case 2:
                
                printf("\nEntre com o nome do cliente:");
                scanf("%s", editarcliente);
                for(contador=0;contador<numcliente;contador++)
                {
                    if(strcmp(editarcliente, vetorcliente[contador].nome) == 0)
                    {
                        vetorcliente[contador] = preenchecliente(contador);
                    }
                }
                getchar();
                break;
                
                //Excluir cliente cadastrado.
            case 3:
    
                printf("\nEntre com o nome do cliente:");
                scanf("%s", editarcliente);
                for(contador=0;contador<numcliente;contador++)
                {
                    if(strcmp(editarcliente, vetorcliente[contador].nome) == 0)
                    {
                        vetorcliente[contador] = excluicliente(contador);
                    }
                }
                
                printf("\nCliente nao cadastrado.");
                getchar();
                break;
                
                //Sair do programa e salvar todos os clientes da memoria no arquivo .txt
            case 4:
                discocliente(numcliente, vetorcliente, arqcliente);
                break;
        }
        printf("\n\n\nDeseja retornar ao menu de clientes ? 1/sim  ||  2/nao");
        scanf("%d", &opcao);
        
        //Sair do laco do menu e salvar todos os clientes da memoria no arquivo .txt
    }while(opcao==1);
    discocliente(numcliente, vetorcliente, arqcliente);
}

// Cadastra o cliente na posicao contador do vetor.
struct pessoa preenchecliente(int contador)
{
    struct pessoa cliente;
    
    printf("\nInforme nome: ");
	scanf("%s", cliente.nome);
	printf("\nInforme a quantidade de pessoas: ");
	scanf("%s", cliente.pessoas);
	printf("\nInforme a mesa: ");
	scanf("%s", cliente.mesa);
	
    return cliente;
}

// No lugar de excluido, preenche com: nome: excluido - pessoas: 0000000000 - mesa: excluido
struct pessoa excluicliente(int contador)
{
    struct pessoa excluido;
    
    printf("\nPor favor, para excluir, digite 00000 em todos os campos:");
    printf("\nInforme nome: ");
	scanf("%s", excluido.nome);
	printf("\nInforme a quantidade de pessoas: ");
	scanf("%s", excluido.pessoas);
	printf("\nInforme a mesa: ");
	scanf("%s", excluido.mesa);
    return excluido;
}

//Cadastra todos os clientes do vetor no arquivo .txt
void discocliente (int numcliente, struct pessoa *vetorcliente, FILE *arqcliente)
{
    int contar;
    char separadorstruct = 43, separadordados= 45;
    arqcliente = fopen("arquivo_cliente.txt", "rb+");
    
    if(numcliente < 10)
    {
        fprintf(arqcliente, "0");
        fprintf(arqcliente, "0");
        fprintf(arqcliente, "0");
        fprintf(arqcliente, "%d", numcliente);
    }
    else
    {
        if(numcliente > 9 && numcliente < 100)
        {
            fprintf(arqcliente, "0");
            fprintf(arqcliente, "0");
            fprintf(arqcliente, "%d", numcliente);
        }
        else
        {
            if(numcliente > 99 && numcliente < 1000)
            {
                fprintf(arqcliente, "0");
                fprintf(arqcliente, "%d", numcliente);
            }
            else
            {
                if(numcliente > 999)
                {
                    fprintf(arqcliente, "%d", numcliente);
                }
            }
        }
    }
    fputs(&separadorstruct, arqcliente);
    for (contar=0; contar<numcliente; contar++)
    {
        fputs(vetorcliente[contar].nome, arqcliente);
        fputc(separadordados, arqcliente);
        fputs(vetorcliente[contar].pessoas, arqcliente);
        fputc(separadordados, arqcliente);
        fputs(vetorcliente[contar].mesa, arqcliente);
        fputs(&separadorstruct, arqcliente);
    }
}
