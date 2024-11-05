#include <stdlib.h>
#include <stdio.h>
#include "cadastro.h"

int main() {
    Fruta *itens = NULL;  
    int cont = 0;       
    int num;

    do {
        printf("\nMenu:\n");
        printf("1. Efetue uma venda\n");
        printf("2. Lista de Frutas\n");
        printf("3. Cadastre uma nova fruta\n");
        printf("4. busque a fruta desejada\n");
        printf("5. edite as informacoes de uma fruta\n");
        printf("6. excluir uma fruta do registro\n");
        printf("7. Encerrar Programa\n");
        printf("\n");
        printf("***********************************************************\n");
        printf("**Digite uma das opcoes de acordo com a numeracao. Ex: 2.**\n");
        printf("***********************************************************\n");
        printf("\n");
        scanf("%d", &num);
        printf("\n");


        switch (num) {
            case 1:
                efetuarVenda(itens, &cont);
                break;
            case 2:
                listaDeItens(itens, cont);
                break;
            case 3:
                cadastroItem(&itens, &cont);
                break;
            case 4:
                buscar(itens, cont);
                break;
            case 5:
                editarItens(itens, cont);
                break;
            case 6:
                exluirItem(&itens, &cont);
                break;
            case 7:
                printf("Obrigado por utilizar nosso sistema!\n");
                break;
            default:
                printf("O digito informado nao e uma opcao valida...\n");
                break;
        }
    } while (num != 7);

    free(itens);

    return 0;
}
