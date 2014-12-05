#include "hcliente.h"
#include "hfuncionario.h"
#include "hproduto.h"
#include <stdio.h>

//-------------------------------FUNCOES DO FUNCIONARIO-------------------------------------------------------

//Carrega os dados do arquivo na memoria.
void carregafuncionario()
{
    //Ler os dados do arquivo.
    FILE *arqfuncionario;
	
	//abrir o arquivo
	arqfuncionario = fopen("arquivo_funcionario.txt","rb+");
    
    if(arqfuncionario == NULL)
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
        char auxCount[4] = { getc(arqfuncionario), getc(arqfuncionario), getc(arqfuncionario), getc(arqfuncionario) };
        
        //converter para inteiro
        int numfuncionario = atoi(auxCount);
    
        //alocar o array para estes registros
        struct strfuncionario *vetorfuncionario = (struct strfuncionario *) (malloc(numfuncionario * sizeof(struct strfuncionario)));
        
        //ler o '+' separador do contador de registro
        getc(arqfuncionario);
        
        //A) loop infinito (para cada registro)
        while(!feof(arqfuncionario))
        {
            //registro que esta sera lido do arquivo
            struct strfuncionario registro;
            
            //flag que indica se o arquivo terminou
            int breakingFlag = 0;
            
            //B) outro loop infinito (para cada campo)
            while(1)
            {
                //ler um caractere do arquivo
                char c = getc(arqfuncionario);
                
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
                //se for o campo funcao
                else if(idxCampos == 1)
                {
                    //concatenar o caractere no funcao
                    registro.funcao[idxCharCampos] = rc;
                }
                //se for o campo codigo
                else if(idxCampos == 2)
                {
                    //concatenar o caractere no codigo
                    registro.codigo[idxCharCampos] = rc;
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
            vetorfuncionario[regCount] = registro;
                
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
        fclose(arqfuncionario);
        
        //chama a funcao menu
        menufuncionario(numfuncionario, vetorfuncionario, arqfuncionario);
    }
    
}

//Depois que carregou o arquivo na memoria, entra o menu e as opcoes de funcionario.
void menufuncionario(int numfuncionario, struct strfuncionario *vetorfuncionario, FILE *arqfuncionario)
{
    int contador=0, resposta=1, aux=0, opcao=0;
    char editarfuncionario[25];
    struct strfuncionario *auxvetorfuncionario;
    
    do{
        printf("Escolha uma opcao:");
        printf("\n1 - Cadastrar um funcionario.");
        printf("\n2 - Editar um funcionario cadastrado.");
        printf("\n3 - Excluir um funcionario cadastrado.");
        printf("\n4 - SAIR.");
        scanf("%d", &opcao);
        switch (opcao)
        {
                
                //Cadastrar novo funcionario
            case 1:
            {
                while(1)
                {
                    printf("\nDeseja cadastrar um funcionario ? 1/sim   ||   2/nao");
                    scanf("%d", &resposta);
                    if(resposta==1)
                    {
                        aux = numfuncionario;
                        numfuncionario = numfuncionario + 1;
                        struct strfuncionario *auxvetorfuncionario = (struct strfuncionario *) (malloc(aux * sizeof(struct strfuncionario)));
                        for(contador = 0; contador < aux; contador++)
                        {
                            auxvetorfuncionario[contador] = vetorfuncionario[contador];
                        }
                        struct strfuncionario *vetorfuncionario = (struct strfuncionario *) (malloc(numfuncionario * sizeof(struct strfuncionario)));
                        for(contador = 0; contador < aux; contador++)
                        {
                            vetorfuncionario[contador] = auxvetorfuncionario[contador];
                        }
                        for(contador = aux; contador<numfuncionario; contador++)
                        {
                            vetorfuncionario[contador] = preenchefuncionario(contador);
                        }
                        free(auxvetorfuncionario);
                    }
                    else
                        //sair quando a resposta for nao
                    { break; }
                }
            }
                break;
                
                //Editar funcionario cadastrado.
            case 2:
            {
                printf("\nEntre com o nome do funcionario:");
                scanf("%s", editarfuncionario);
                for(contador=0;contador<numfuncionario;contador++)
                {
                    if(strcmp(editarfuncionario, vetorfuncionario[contador].nome) == 0)
                    {
                        vetorfuncionario[contador] = preenchefuncionario(contador);
                    }
                }
                getchar();
            }
                break;
                
                //Excluir funcionario cadastrado.
            case 3:
            {
                printf("\nEntre com o nome do funcionario:");
                scanf("%s", editarfuncionario);
                for(contador=0;contador<numfuncionario;contador++)
                {
                    if(strcmp(editarfuncionario, vetorfuncionario[contador].nome) == 0)
                    {
                        vetorfuncionario[contador] = excluifuncionario(contador);
                    }
                }
                
                printf("\nFuncionario nao cadastrado.");
                getchar();            }
                break;
                
                //Sair do programa e salvar todos os funcionarios da memoria no arquivo .txt
            case 4:
            {
                discofuncionario(numfuncionario, vetorfuncionario, arqfuncionario);
            }
                break;
        }
        printf("\n\n\nDeseja retornar ao menu de funcionarios ? 1/sim  ||  2/nao");
        scanf("%d", &opcao);
        //Sair do laco do menu e salvar todos os funcionarios da memoria no arquivo .txt
    }while(opcao==1);
    discofuncionario(numfuncionario, vetorfuncionario, arqfuncionario);
    free(vetorfuncionario);
    fclose(arqfuncionario);
}

// Cadastra o funcionario na posicao contador do vetor.
struct strfuncionario preenchefuncionario(int contador)
{
    struct strfuncionario funcionario;
    
    printf("\nInforme nome: ");
	scanf("%s", funcionario.nome);
	printf("\nInforme a funcao: ");
	scanf("%s", funcionario.funcao);
	printf("\nInforme o codigo: ");
	scanf("%s", funcionario.codigo);
	
    return funcionario;
}

// No lugar de excluido, preenche com: nome: excluido - funcao: 0000000000 - codigo: excluido
struct strfuncionario excluifuncionario(int contador)
{
    struct strfuncionario excluido;
    
    printf("\nPor favor, para excluir, digite 00000 em todos os campos:");
    printf("\nInforme nome: ");
	scanf("%s", excluido.nome);
	printf("\nInforme a funcao: ");
	scanf("%s", excluido.funcao);
	printf("\nInforme o codigo: ");
	scanf("%s", excluido.codigo);
    return excluido;
}

//Cadastra todos os funcionarios do vetor no arquivo .txt
void discofuncionario (int numfuncionario, struct strfuncionario *vetorfuncionario, FILE *arqfuncionario)
{
    int contar;
    char separadorstruct = 43, separadordados= 45;
    arqfuncionario = fopen("arquivo_funcionario.txt", "rb+");
    
    if(numfuncionario < 10)
    {
        fprintf(arqfuncionario, "0");
        fprintf(arqfuncionario, "0");
        fprintf(arqfuncionario, "0");
        fprintf(arqfuncionario, "%d", numfuncionario);
    }
    else
    {
        if(numfuncionario > 9 && numfuncionario < 100)
        {
            fprintf(arqfuncionario, "0");
            fprintf(arqfuncionario, "0");
            fprintf(arqfuncionario, "%d", numfuncionario);
        }
        else
        {
            if(numfuncionario > 99 && numfuncionario < 1000)
            {
                fprintf(arqfuncionario, "0");
                fprintf(arqfuncionario, "%d", numfuncionario);
            }
            else
            {
                if(numfuncionario > 999)
                {
                    fprintf(arqfuncionario, "%d", numfuncionario);
                }
            }
        }
    }
    fputs(&separadorstruct, arqfuncionario);
    for (contar=0; contar<numfuncionario; contar++)
    {
        fputs(vetorfuncionario[contar].nome, arqfuncionario);
        fputc(separadordados, arqfuncionario);
        fputs(vetorfuncionario[contar].funcao, arqfuncionario);
        fputc(separadordados, arqfuncionario);
        fputs(vetorfuncionario[contar].codigo, arqfuncionario);
        fputs(&separadorstruct, arqfuncionario);
    }
}
