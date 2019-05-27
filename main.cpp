#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

//Define quantas casas serao saltadas na codificacao
const int salto = 3;
//Define o tamanho do vetor de entrada
const int tamVetor = 3;

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

int main()
{
    char input[tamVetor], *resosta;


    printf("Frase a ser codificada pela cifra de Cesar: ");
    scanf("%s", &input);


    resosta = codifica(input, tamVetor);
    printf("Frase codificada: %s\n", resosta);
    resosta = decodifica(resosta, tamVetor);
    printf("Frase decodificada: %s\n", resosta);

    return 0;
}
