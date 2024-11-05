#include <stdio.h>
#include <stdlib.h>
#ifndef CADASTRO_H
#define CADASTRO_H


typedef struct {
    int codigo;          
    char nome[50];      
    int quantidade;     
    float preco;         
} Fruta;


void cadastroItem(Fruta **itens, int *cont);
void listaDeItens(Fruta *itens, int cont);
void buscar(Fruta *itens, int cont);
void editarItens(Fruta *itens, int cont);
void exluirItem(Fruta **itens, int *cont);
void cadastrarVendas(Fruta *itens, int idItem, int vendas);
void efetuarVenda(Fruta *itens, int *cont);



void cadastroItem(Fruta **itens, int *cont) {
    Fruta novoItem;

    printf("Digite o Id da fruta: ");
    scanf("%d", &novoItem.codigo);
    getchar(); 

    for (int i = 0; i < *cont; i++) {
        if ((*itens)[i].codigo == novoItem.codigo) {
            printf("Esse Id ja esta cadastrado. Insira outro\n");
            return;
        }
    }

    printf("Informe o nome da nova fruta: ");
    scanf(" %[^\n]", novoItem.nome);

    printf("Quantidade registrada: ");
    scanf("%d", &novoItem.quantidade);

    printf("Informe o valor da fruta: ");
    scanf("%f", &novoItem.preco);

    Fruta *temp = (Fruta *)realloc(*itens, (*cont + 1) * sizeof(Fruta));    
    if (temp == NULL) {
        printf("Erro ao alocar memória.\n");
        return;
    }
    *itens = temp;


    (*itens)[*cont] = novoItem;
    (*cont)++; 

    printf("Fruta cadastrada.\n");
}

void listaDeItens(Fruta *itens, int cont){
    if (cont == 0){
        printf("Lista vazia\n");
        return;
    }
    
    printf("itens cadastrados:\n");
    for (int i = 0; i< cont; i++){
        printf("nome: %s\n", itens[i].nome);
        printf("quantidade: %d\n", itens[i].quantidade);
        printf("preco: %.2f\n", itens[i].preco);
        printf("Id: %d\n", itens[i].codigo);
        printf("\n");
    }
}

void cadastrarVendas(Fruta *itens, int idItem, int vendas) {
    FILE *file = fopen("vendas.txt", "a");
    if (file == NULL) {
        printf("Error.\n");
        return;
    }

    fprintf(file, "Id: %d, vendas: %d\n", idItem, vendas);
    fclose(file);
}

void efetuarVenda(Fruta *itens, int *cont) {
    if (*cont == 0) {
        printf("Nenhuma fruta cadastrada.\n");
        return;
    }

    int codigo;
    int vendas;
    printf("Informe o ID da fruta para efetuar a venda: ");
    scanf("%d", &codigo);

    for (int i = 0; i < *cont; i++) {
        if (itens[i].codigo == codigo) {
            printf("Em estoque %d\n", itens[i].quantidade);
            printf("agora informe a quantidade que deseja vender ");
            scanf("%d", &vendas);

            if (vendas > itens[i].quantidade) {
                printf("Itens insufucientes,contatar destribuidora.\n");
                return;
            }

            itens[i].quantidade -= vendas; 
            cadastrarVendas(itens, codigo, vendas); 
            printf("transacao realizada\n");
            return;
        }
    }

    printf("Fruta de Id %d não esta em estoque.\n", codigo);
}

void editarItens(Fruta *itens, int cont) {
    if (cont == 0) {
        printf("esta fruta nao consta nos registros\n");
        return;
    }

    int codigo;
    printf("Informe o ID da fruta a ser editada  ");
    scanf("%d", &codigo);

    for (int i = 0; i < cont; i++) {
        if (itens[i].codigo == codigo) {
            printf("Fruta:\n");
            printf("Nome registrado: %s\n", itens[i].nome);
            printf("Quantidade registrada: %d\n", itens[i].quantidade);
            printf("Preco registrado: %.2f\n", itens[i].preco);
            printf("Id: %d\n", itens[i].codigo);
            printf("\n");
            printf("\n");
            printf("Registre um novo nome: ");
            scanf(" %[^\n]", itens[i].nome);
            printf("Registre a quantidade em estoque: ");
            scanf("%d", &itens[i].quantidade);
            printf("Registre o valor fruta: ");
            scanf("%f", &itens[i].preco);

            printf("Edicao realizada!\n");
            return;
        }
    }

    printf("Fruta com Id %d não registrada.\n", codigo);
}


void buscar(Fruta *itens, int cont){
    if (cont == 0){
        printf("Fruta não encontrada\n");
        return;
    }
    
    int codigo;
    printf("informe o Id da fruta buscada:");
    scanf("%d", &codigo);
    
    for(int i = 0; i<cont; i++){
        if (itens[i].codigo == codigo){
            printf("Resultado:\n");
            printf("nome: %s\n", itens[i].nome);
            printf("quantidade: %d\n",itens[i].quantidade);
            printf("preco: %.2f\n", itens[i].preco);
            printf("Id: %d\n", itens[i].codigo);
            return;
        }
    }
    
    printf("Fruta com Id %d não registrada.\n", codigo);
}

void exluirItem(Fruta **itens, int *cont) {
    if (*cont == 0) {
        printf("esta fruta nao consta nos registros\n");
        return;
    }

    int codigo;
    printf("Informe o ID da fruta a ser excluida: ");
    scanf("%d", &codigo);

    for (int i = 0; i < *cont; i++) {
        if ((*itens)[i].codigo == codigo) {
            if ((*itens)[i].quantidade > 0) {
                printf("Fruta ainda em estoque. Exclusao negada\n");
                return;
            }

            for (int j = i; j < *cont - 1; j++) {
                (*itens)[j] = (*itens)[j + 1]; 
            }

            Fruta *temp = (Fruta *)realloc(*itens, (*cont - 1) * sizeof(Fruta));
            if (temp == NULL && (*cont - 1) > 0) {
                printf("Nao foi possivel realocar memória.\n");
                return;
            }
            *itens = temp;

            (*cont)--;
            printf("exclusão realizada\n");
            return;
        }
    }

    printf("Fruta com Id %d não esta registrada.\n", codigo);
}




#endif 