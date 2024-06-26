#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
6) Elabore um programa no qual o usuário informe o nome
de um arquivo texto e uma palavra, e o programa informe o
número de vezes que aquela palavra aparece
*/

void LeString(char String[], int tamanho){
    setbuf(stdin, NULL);
    fgets(String, tamanho, stdin);
    String[strcspn(String, "\n")] = '\0';
}

void CriaArquivo(char nome[]){

    int alternativa;
    char texto[100];
    FILE* arq1;

    arq1 = fopen(nome, "r+w");
    if(arq1 != NULL){
        perror("Arquivo já existe!\n");
        printf("1- Sobrescrever arquivo!\n2- Alterar nome\n");
        scanf("%i", &alternativa);
        if(alternativa == 1){
            arq1 = fopen(nome, "w");
            if(arq1 == NULL){
                perror("Erro ao criar arquivo!\n");
                exit(1);
            }
            printf("Arquivo %s criado!\n", nome);
        }else if(alternativa == 2){
            printf("Digite o novo nome: ");
            LeString(nome, 49);
            arq1 = fopen(nome, "w");
            if(arq1 == NULL){
                perror("Erro ao criar arquivo!\n");
                exit(1);
            }
            printf("Arquivo %s criado!\n", nome);
        }
    } else if(arq1 == NULL){
        arq1 = fopen(nome, "w");
        if(arq1 == NULL){
            perror("Erro ao criar arquivo!\n");
            exit(1);
        }
        printf("Arquivo %s criado!\n", nome);
    }

    printf("Deseja escrever algo no arquivo?\n");
    printf("1- SIM, 2- NÃO\n");

    do{
        scanf("%i", &alternativa);
    }while(alternativa != 2 && alternativa != 1);

    if(alternativa == 1){
        arq1 = fopen(nome, "r+w");
        if(arq1 == NULL){
            perror("Erro ao abrir arquivo!\n");
            exit(1);
        }
        printf("Digite o que desejar: \n");
        LeString(texto, 99);
        printf("(\" %s \") TEXTO ADICIONADO COM SUCESSO!\n", texto);
        fputs(texto, arq1);
    }else if(alternativa == 2){
        perror("Ok, seguindo!");
        fputs("\0", arq1);
    }

    fclose(arq1);
}

int main(){

    char pesquisaarquivo[50];
    char texto[50];
    char caracter;
    int contapalavras = 0;
    int opcao = 0;
    FILE* arq2;

    do{
        printf("1- Criar arquivo\n2- Buscar arquivo\n3- Encerrar programa.\n");
        scanf("%i", &opcao);
        setbuf(stdin, NULL);
        if(opcao == 1){
            printf("Digite o nome do arquivo: ");
            LeString(texto, 49);
            CriaArquivo(texto);
        }
        if(opcao == 2){
            printf("Pesquisar arquivo: ");
            LeString(pesquisaarquivo, 49);
            arq2 = fopen(pesquisaarquivo, "r");
            if(arq2 == NULL){
            perror("Erro ao ler arquivo!\n");
            exit(1);
            }
        
            printf("Digite uma palavra: ");
            scanf("%c", &caracter);
            int c;

            contapalavras = 0;
            while((c = fgetc(arq2)) != EOF){
                if(toupper(c) == toupper(caracter)){
                    contapalavras++;
                }
            }

            printf("A letra %c, aparece %i vezes em %s\n", caracter, contapalavras, pesquisaarquivo);

            fclose(arq2);
        }
        if(opcao == 3){
            printf("Encerrando programa!\n");
            exit(0);
        }
    } while(opcao != 3);
    

    return 0;
}