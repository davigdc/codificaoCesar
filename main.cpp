#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

//Define quantas casas serao saltadas na codificacao
const int salto = 3;
//Define o tamanho do vetor de entrada
const int tamVetor = 300;

//Como o vetor eh estatico esta funcao retorna ate qual posicao o vetor foi preenchido pelo usuario
int caracteresValidos (char *vetor, int tamanho){
    int cont = 0;

    for(int i = 0; i < tamanho; i++){
        if(vetor[i] == NULL){   //quando nao preenchido por completo o vetor, o termo proximo ao ultimo entrado eh NULL assim facilitando saber onde termina a leitura
            break;
        } else {
            cont++;
        }
    }

return cont;
}

char *codifica (char *entrada, int chave){
    int x = caracteresValidos(entrada, chave);
    char *aux = (char*)calloc(x, sizeof(char)); //Vetor cujo tamanho eh o numero de caracteres digitados pelo usuario

    for(int i = 0; i < x; i++){
        aux[i] = entrada[i] + salto;    //caracter atual MAIS o valor do salto para codificacao (valor declarado no inicio do codigo)
    }

return aux;
}

char *decodifica (char *entrada, int chave){
    int x = caracteresValidos(entrada, chave);
    char *aux = (char*)calloc(x, sizeof(char)); //Vetor cujo tamanho eh o numero de caracteres digitados pelo usuario

    for(int i = 0; i < x; i++){
        aux[i] = entrada[i] - salto;    //caracter atual MENOS o valor do salto para decodificacao (valor declarado no inicio do codigo)
    }

return aux;
}

void criaArquivo (char *nomeArq, char *entrada) {

    FILE *arq = fopen(nomeArq, "w+");
    fprintf(arq, "%s\n", entrada);

    fclose(arq);
}

void codificaArquivo (char *nomeArq) {

char aux[tamVetor],
     aux2[tamVetor] = {},
     *aux3;
bool laco = false;

    FILE *arq = fopen(nomeArq, "r");
    if(arq == NULL){
        printf("\tArquivo ->%s<- inexistente ou sem espaco na memoria!\n", nomeArq);
    } else {

        while(!feof(arq)){  //Le linha por linha ate o final do arquivo
            if(laco){
                strcat(aux2, " ");  // Serve para formatacao do texto, essa condicao evita de adicionar um espaco antes e depois do texto
            }
            if (!feof(arq)){
                laco = true;    //Apenas se houver mais de uma linha adicionara um espaco, AQUI se remove a quebra de linha, transformando o arquivo em uma unica linha para codificacao
                fscanf(arq, "%[^\n]\n", &aux);  //Leitura da linha e armazenamento em aux
                strcat(aux2, aux);  //A ideia aqui eh fazer aux+=aux, mas com o formato char so por meio desta adapcao, fica o desafio de uma forma mais efetiva, que possa preservar a quebra de linha tambem, boa sorte! (Transforma um arquivo de varias linhas em uma unica linha)
                //printf("Linha lida: %s\n", aux);  //Imprimira linha por linha do arquivo
            }
        }

        aux3 = codifica(aux2, tamVetor);    // aux3 recebe o vetor aux2 ja codificado
        printf("\nResultado codificacao: %s\n", aux3); //Impressao do resultado da codificacao
        fclose(arq);
    }

    criaArquivo(nomeArq, aux3); //Atualiza o arquivo, agr sim codificado

}

void decodificaArquivo (char *nomeArq) {    //A ideia eh a mesma da funcao de codificacao, os comentarios sao praticamente os mesmos

char aux[tamVetor],
     aux2[tamVetor] = {},
     *aux3;
bool laco = false;

    FILE *arq = fopen(nomeArq, "r");
    if(arq == NULL){
        printf("\tArquivo ->%s<- inexistente ou sem espaco na memoria!\n", nomeArq);
    } else {

        while(!feof(arq)){
            if(laco){
                strcat(aux2, " ");
            }
            if (!feof(arq)){
                laco = true;
                fscanf(arq, "%[^\n]\n", &aux);
                strcat(aux2, aux);
                printf("Linha lida: %s\n", aux);
            }
        }

        aux3 = decodifica(aux2, tamVetor);
        printf("\nResultado decodificacao: %s\n", aux3);
        fclose(arq);
    }

    criaArquivo(nomeArq, aux3);

}

int main()
{
    int menu = 0;
    char arqNome [25],
         texto[tamVetor];

    do{
    printf("-------------------------------------------------------------\n");
    printf("\tMENU:\n1-)Criar arquivo com texto;\n2-)Codificar arquivo;\n3-)Decodificar arquivo;\n4-)Sair.\n\tEntrada: ");
        scanf("%d", &menu);
        fflush(stdin);

        if (menu < 1 || menu > 4){
            printf("\tOpcao invalida, tente novamente!\n");
        }

        switch(menu){
            case 1: //Criacao arquivo com texto
                printf("Qual o nome do arquivo a ser criado (colocar .txt): ");
                fflush(stdin);
                scanf("%s", &arqNome);
                fflush(stdin);
                printf("Frase a ser escrita no arquivo: ");
                fflush(stdin);
                gets(texto);
                criaArquivo(arqNome, texto);
            break;

            case 2: //Codificacao de arquivo ja existente
                printf("Qual o nome do arquivo a ser codificado (colocar .txt): ");
                scanf("%s", &arqNome);
                codificaArquivo(arqNome);
            break;

            case 3: //Decodificacao de arquivo ja existente
                printf("Qual o nome do arquivo a ser decodificado (colocar .txt): ");
                scanf("%s", &arqNome);
                decodificaArquivo(arqNome);
            break;

        }

    } while(menu != 4);

    return 0;
}
