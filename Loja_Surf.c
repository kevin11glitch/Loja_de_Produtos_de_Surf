#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct NO{

    //dados da aplicacao
    int codigo;
    char* tipo_prod;
    char* descricao;
    float preco;

    //mecanismo de uniao de nos
    struct NO * prox;
    struct NO *ant;

}NO;

NO *inicio = NULL;
NO *fim = NULL;
int tam = 0;

void recebimento(int codigo, char * tipo_prod, char* descricao, float preco){
   
    //if(pos >= 0 && pos <= tam){

        NO * novo = malloc(sizeof(NO));
        novo->codigo = codigo;
        novo->tipo_prod = tipo_prod;
        novo->descricao = descricao;
        novo->preco = preco;
        novo->prox = NULL;
        novo->ant = NULL;

        //tratar como inserir 

        if(inicio == NULL){ //lista vazia
            //operacao de encaixe
            inicio = novo;
            fim = novo;
            tam++;
        }else{ // lista nao esta vazia...

            if(novo->preco < inicio->preco){ // caso do inicio
                novo->prox = inicio;
                inicio->ant = novo;
                inicio = novo;
                tam++;

            }else if(novo->preco > fim->preco){ //caso do fim
                fim->prox = novo;
                novo->ant = fim;
                fim = novo;
                tam++;
            }else{
                //meio ...
                NO* aux = inicio;
                while(aux->prox->preco < novo->preco){
                    aux = aux->prox;
                }
                novo->prox =aux->prox;
                novo->ant = aux;
                aux->prox->ant = novo;
                aux->prox = novo;
                tam++;
            }
        }
    //}else{
        //printf("Posicao invalida! Isso aqui é uma listaaaaaaaa! :D");
    //}
}

void produtos_disponiveis(){
    NO * aux = inicio;
    printf("--- LISTA DE PRODUTOS DISPONIVEIS ---\n\n");
    while(aux != NULL){
        printf("Codigo do produto: %d \n", aux->codigo);
        printf("Tipo do produto: %s \n", aux->tipo_prod);
        printf("Descricao do produto: %s \n", aux->descricao);
        printf("Preco do produto: R$ %.2f \n", aux->preco);
        printf("----------------------------\n\n");

        aux = aux->prox;
    }
}

void vizualizar_categoria(char *categoria){
    NO * aux = inicio;
    int item_encontrado = 0;
    printf("--- LISTA DE PRODUTOS DISPONIVEIS POR CATEGORIA (%s) ---\n\n", categoria);
    while(aux != NULL){
        if(strcmp(aux->tipo_prod, categoria) == 0){
            printf("Codigo do produto: %d \n", aux->codigo);
            printf("Tipo do produto: %s \n", aux->tipo_prod);
            printf("Descricao do produto: %s \n", aux->descricao);
            printf("Preco do produto: R$ %.2f \n", aux->preco);
            printf("----------------------------\n\n");
            item_encontrado = 1;
        }
        aux = aux->prox;
    }

    if(!item_encontrado){
        printf("Nenhum produto encontrado na categoria '%s'.\n", categoria);
    }
}


void vizualizar_preco(float minimo, float maximo){
    NO * aux = inicio;
    int item_encntrado = 0;
    printf("--- LISTA DE PRODUTOS DISPONIVEIS POR INTERVALO DE PRECO (R$ %.2f - R$ %.2f) ---\n\n", minimo, maximo);
    while(aux != NULL){
        if(aux->preco >= minimo && aux->preco <= maximo){
            printf("CODIGO: %d \n", aux->codigo);
            printf("TIPO: %s \n", aux->tipo_prod);
            printf("DESCRICAO: %s \n", aux->descricao);
            printf("PRECO: R$ %.2f \n", aux->preco);
            printf("----------------------------\n\n");
            item_encntrado = 1;
        }
        aux = aux->prox;
    }
    if(!item_encntrado){
        printf("Nenum produto encontrado nessa faixa de preco.\n");
    }
}


void comprar_produto(int codigo){

    if(inicio->codigo == codigo){ //inicio
        NO *lixo = inicio;
        printf("--- PRODUTO COMPRADO COM SUCESSO ---\n\n");
        printf("CODIGO: %d\n", lixo->codigo);
        printf("TIPO: %s\n", lixo->tipo_prod);
        printf("DESCRICAO: %s\n", lixo->descricao);
        printf("PRECO: R$ %.2f\n", lixo->preco);
        printf("----------------------------\n\n");
        inicio = inicio->prox;
        inicio->ant = NULL;
        if(tam == 1){
            fim = NULL;
        }
        free(lixo);
        tam--;
    }else if(fim->codigo == codigo){ // fim
        NO *lixo = fim;
        printf("--- PRODUTO COMPRADO COM SUCESSO ---\n\n");
        printf("CODIGO: %d\n", lixo->codigo);
        printf("TIPO: %s\n", lixo->tipo_prod);
        printf("DESCRICAO: %s\n", lixo->descricao);
        printf("PRECO: R$ %.2f\n", lixo->preco);
        printf("----------------------------\n\n");
        fim->ant->prox = NULL;
        fim = fim->ant;
        free(lixo);
        tam--;
    }else{
        //meio....
        NO *aux = inicio;
        NO *lixo = aux;
        while(aux->prox->codigo != codigo){
            aux = aux->prox;
        }
        lixo = aux->prox;
        printf("--- PRODUTO COMPRADO COM SUCESSO ---\n\n");
        printf("CODIGO: %d\n", lixo->codigo);
        printf("TIPO: %s\n", lixo->tipo_prod);
        printf("DESCRICAO: %s\n", lixo->descricao);
        printf("PRECO: R$ %.2f\n", lixo->preco);
        printf("----------------------------\n\n");
        aux->prox = lixo->prox;
        aux->prox->ant = aux; 
        free(lixo);
        tam--;
        
    }

    
}

int main() {
    recebimento(2012, "Quilha", "Futures Fins - AM1 Honeycomb Medium", 550.00);
    recebimento(2004, "Parafina", "Banana Wax - Eco Friendly", 12.00);
    recebimento(2019, "Deck", "Creatures of Leisure - Italo Ferreira Lite", 240.00);
    recebimento(2006, "Leash", "FCS Freedom - 6ft Black", 185.00);
    recebimento(2002, "Parafina", "Fu Wax - Tropical Summer", 22.00);
    recebimento(2015, "Quilha", "Scarfini - HX3 Carbon Hybrid", 310.00);
    recebimento(2010, "Leash", "Pro-Lite - Surf Series 5ft", 98.00);
    recebimento(2017, "Deck", "FCS T-3 - Traction Blue Line", 195.00);
    recebimento(2001, "Parafina", "Sticky Bumps - Água Fria", 15.50);
    recebimento(2011, "Quilha", "FCS II Carver - Neo Glass Large", 420.00);
    recebimento(2008, "Leash", "Creatures of Leisure - Reliance 6ft", 160.00);
    recebimento(2020, "Deck", "Astrodeck - Nathan Fletcher Signature", 205.00);
    recebimento(2003, "Parafina", "Sex Wax - Coconut High Grip", 18.90);
    recebimento(2014, "Quilha", "Shapers Fins - S5 Thruster Carbon", 390.00);
    recebimento(2007, "Leash", "Dakine Kainui - 7ft Blue", 145.50);
    recebimento(2016, "Deck", "Gorilla Grip - Jane Tail Pad", 215.00);
    recebimento(2005, "Parafina", "Magical Wax - Competição", 25.00);
    recebimento(2013, "Quilha", "Captain Fin - Dane Reynolds Summer", 480.00);
    recebimento(2009, "Leash", "Ocean & Earth - Regular 8ft", 120.00);
    recebimento(2018, "Deck", "Dakine Launch - Pad Orange", 175.40);

    system("cls");
    int opcao, codigo;
    char escolha[50];
    float min, max;
    printf("-- Bem-vindo(a) a loja Tati Surf Co! --\n\n");

    do{
        printf("-> Opcao 1: Ver produtos disponiveis para compra\n");
        printf("-> Opcao 2: Ver produtos por categoria\n");
        printf("-> Opcao 3: Ver produtos por intervalo de valores\n");
        printf("-> Opcao 4: Comprar item\n");
        printf("-> Opcao 5: Encerrar atendimento\n");
        printf("Escolha uma opcao de acao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            system("cls");
            produtos_disponiveis();
            break;

        case 2:
            system("cls");
            printf("Escolha uma categoria de produto: ");
            scanf("%s", escolha);
            vizualizar_categoria(escolha);
            break;

        case 3:
            system("cls");
            printf("Escolha um valor minimo: ");
            scanf("%f", &min);
            printf("Escolha um valor maximo: ");
            scanf("%f", &max);
            vizualizar_preco(min,max);
            break;
        
        case 4:
            system("cls");
            printf("Digite o codigo do produto que gostaria de comprar: ");
            scanf("%d", &codigo);
            comprar_produto(codigo);
            break;

        case 5:
            system("cls");
            printf("Encerrando atendimento. Volte sempre!");
            break;

        default:
            system("cls");
            printf("* Opcao %d nao existe -> Digite uma opcao valida.\n", opcao);
            break;
        }
    }while(opcao != 5);

    

    return 0;
}
