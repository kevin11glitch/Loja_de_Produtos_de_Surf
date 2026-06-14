#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
typedef struct NO{

    //dados da aplicacao
    int codigo;
    char* tipo_prod;
    char* descricao;
    float preco;

    //mecanismo de uniao de nos
    struct NO *prox;
    struct NO *ant;

}NO;

NO *inicio = NULL;
NO *fim = NULL;
int tam = 0;

typedef struct NO_FILA{
    int codigo;
    char* tipo_prod;
    char* descricao;
    float preco;

    char *nome_cliente;
    char *cpf;
    char *cep;
    char *nome_rua;
    int num_casa;
    char *complemento;

    struct NO_FILA *prox;
}NO_FILA;

NO_FILA *inicio_fila = NULL;
NO_FILA *fim_fila = NULL;
int tam_fila = 0;



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

void imprimir_produto_comprado(NO* produto){
    printf("--- PRODUTO COMPRADO COM SUCESSO ---\n\n");
    printf("CODIGO: %d\n", produto->codigo);
    printf("TIPO: %s\n", produto->tipo_prod);
    printf("DESCRICAO: %s\n", produto->descricao);
    printf("PRECO: R$ %.2f\n", produto->preco);
    printf("----------------------------\n\n");
}


NO* comprar_produto(int codigo){
    if (inicio == NULL) {
        return NULL; 
    }
    if(inicio->codigo == codigo){ //inicio
        NO *aux = inicio;
        inicio = inicio->prox;
        inicio->ant = NULL;
        if(tam == 1){
            fim = NULL;
        }
        //free(aux);
        imprimir_produto_comprado(aux);
        tam--;
        return aux;
    }else if(fim->codigo == codigo){ // fim
        NO *aux = fim;
        fim->ant->prox = NULL;
        fim = fim->ant;
        //free(aux);
        imprimir_produto_comprado(aux);
        tam--;
        return aux;
    }else{
        //meio....
        NO *aux = inicio;

        while(aux->prox != NULL && aux->prox->codigo != codigo){
            aux = aux->prox;
        }

        if (aux->prox == NULL) {
            return NULL; 
        }

        NO *lixo = aux->prox;
        aux->prox = lixo->prox;

        if (lixo->prox != NULL) { 
            lixo->prox->ant = aux; 
        }

        imprimir_produto_comprado(lixo);
        tam--;
        return lixo;
    }
    
}

void fila_pedidos_entrega(NO* produto_comprado, char *nome_cliente, char *cpf, char *cep, char *nome_rua, int num_casa, char *complemento){
    NO_FILA *novo = malloc(sizeof(NO_FILA));
    novo->codigo = produto_comprado->codigo;
    novo->tipo_prod = produto_comprado->tipo_prod;
    novo->descricao = produto_comprado->descricao;
    novo->preco = produto_comprado->preco;
    novo->nome_cliente = nome_cliente;
    novo->cpf = cpf;
    novo->cep = cep;
    novo->nome_rua = nome_rua;
    novo->num_casa = num_casa;
    novo->complemento = complemento;
    novo->prox = NULL;
    free(produto_comprado);

    if(inicio_fila == NULL){ //fila vazia
        //operacao de encaixe
        inicio_fila = novo;
        fim_fila = novo;
        tam_fila++;
    }else{ // fila nao esta vazia...
        fim_fila->prox = novo;
        fim_fila = novo;
        tam_fila++;
    }

    NO_FILA * aux = inicio_fila;
    printf("--- FILA DE PRODUTOS PARA ENTREGA ---\n\n");
    while(aux != NULL){
        printf("    -- PRODUTO -- \n");
        printf("    Codigo do produto: %d \n", aux->codigo);
        printf("    Tipo do produto: %s \n", aux->tipo_prod);
        printf("    Descricao do produto: %s \n", aux->descricao);
        printf("    Preco do produto: R$ %.2f \n\n", aux->preco);
        printf("    -- CLIENTE -- \n");
        printf("    Nome do cliente: %s \n", aux->nome_cliente);
        printf("    CPF do cliente: %s \n", aux->cpf);
        printf("    CEP do cliente: %s \n", aux->cep);
        printf("    Nome da rua: %s \n", aux->nome_rua);
        printf("    Numero da casa/apto: %d \n", aux->num_casa);
        printf("    Complemento: %s \n\n", aux->complemento);
        printf("-------------------------------------------\n\n");

        aux = aux->prox;
    }


}

void entregar_pedido(){
    if(inicio_fila == NULL){
        printf("=> Nenhum pedido para entrega na fila!\n\n");
        return;
    }

    NO_FILA*aux = inicio_fila;
    inicio_fila = inicio_fila-> prox;

    if(inicio_fila == NULL){
        fim_fila = NULL;
    }
    tam_fila--;

    printf("=> Pedido saindo para entrega...\n\n");
    printf("-- PRODUTO --\n");
    printf("Codigo: %d\n", aux->codigo);
    printf("Tipo: %s\n", aux->tipo_prod);
    printf("Descricao: %s\n", aux->descricao);
    printf("Preco: %.2f\n\n", aux->preco);
    printf("-- CLIENTE --\n");
    printf("Nome: %s\n", aux->nome_cliente);
    printf("CPF: %s\n", aux->cpf);
    printf("CEP: %s\n", aux->cep);
    printf("Nome da rua: %s\n", aux->nome_rua);
    printf("Numero da casa: %d\n", aux->num_casa);
    printf("Complemento: %s\n\n", aux->complemento);

    free(aux->nome_cliente);
    free(aux->cpf);
    free(aux->cep);
    free(aux->complemento);
    free(aux->nome_rua);
    free(aux);
}

void desenhar_surfista() {
    printf("                   -.--.\n");
    printf("                   )  \" '-,\n");
    printf("                   ',' 2  \\_\n");
    printf("                    \\q \\ .  \\\n");
    printf("                 _.--'  '----.__\n");
    printf("                /  ._      _.__ \\__\n");
    printf("             _.'_.'  \\_ .-._\\_ '-, }\n");
    printf("            (,/ _.---;-(  . \\ \\   ~\n");
    printf("          ____ (  .___\\_\\  \\/_/\n");
    printf("         (      '-._ \\   \\ |\n");
    printf("          '._       ),> _) >\n");
    printf("             '-._   '        -._\n");
    printf("                 '-._           '.\n");
    printf("                     '-._         `\\\n");
    printf("                         '-._       '.\n");
    printf("                             '-._     \\\n");
    printf("                                 `~---'\n\n");
}


int main() {
    recebimento(3042, "Quilha", "Deflow - Twin Keel Machado", 345.00);
    recebimento(3015, "Parafina", "Fu Wax - Summer Tropical", 150.00);
    recebimento(3003, "Quilha", "FCS II Performer - PC Carbon", 545.00);
    recebimento(3049, "Leash", "Pro-Lite - Surf Series 5ft", 45.00);
    recebimento(3021, "Deck", "Channel Islands - Mixed Groove", 430.00);
    recebimento(3008, "Parafina", "Sex Wax - Classic Cold", 200.00);
    recebimento(3034, "Quilha", "FCS II Al Merrick - Ultra Light", 690.00);
    recebimento(3011, "Leash", "FCS All Round - Essential 6ft", 315.00);
    recebimento(3047, "Deck", "Dakine Carve - Pad Black Camo", 135.00);
    recebimento(3026, "Parafina", "Mrs Palmers - Ultra Sticky", 500.00);
    recebimento(3001, "Quilha", "Shapers Fins - Corelite AM2", 195.00);
    recebimento(3039, "Leash", "Dakine John John - Recon Series", 565.00);
    recebimento(3014, "Deck", "Creatures of Leisure - Icon Fish", 280.00);
    recebimento(3028, "Parafina", "Sticky Bumps - Tour Series Extra", 400.00);
    recebimento(3007, "Quilha", "Scarfini - FX2 Eco Glass Small", 89.00);
    recebimento(3043, "Leash", "Modom - Standard 6ft Black", 215.00);
    recebimento(3019, "Deck", "Gorilla Grip - Phils Industrial", 650.00);
    recebimento(3050, "Parafina", "Banana Wax - Tropical Hard", 13.00);
    recebimento(3012, "Quilha", "Futures Fins - Rasta Quad Bamboo", 445.00);
    recebimento(3031, "Leash", "Dakine Pro Comp - 5ft Blue", 165.00);
    recebimento(3006, "Deck", "FCS T-3 - Traction Mid Grey", 330.00);
    recebimento(3037, "Parafina", "Terra Wax - Organic Eco", 600.00);
    recebimento(3022, "Quilha", "Captain Fin - Mikey February Twin", 245.00);
    recebimento(3004, "Leash", "FCS Freedom Helix - Premium", 620.00);
    recebimento(3046, "Deck", "Astrodeck - Nathan Fletcher", 530.00);
    recebimento(3017, "Parafina", "Bubble Gum - Hydro Tech", 300.00);
    recebimento(3033, "Quilha", "FCS II Accelerator - Neo Glass", 145.00);
    recebimento(3010, "Leash", "XM COMP - Tangle Free 6ft", 415.00);
    recebimento(3041, "Deck", "Gorilla Grip - Skinny Series", 180.00);
    recebimento(3025, "Parafina", "Sticky Bumps - Original Cold", 95.00);
    recebimento(3005, "Quilha", "Naked Viking - Apex Quad Series", 395.00);
    recebimento(3038, "Leash", "Pro-Lite - Heavy Duty 8ft", 515.00);
    recebimento(3016, "Deck", "F Filipe Toledo - Pro Model", 480.00);
    recebimento(3048, "Parafina", "Magical Wax - Competicao Grip", 250.00);
    recebimento(3013, "Quilha", "Futures Fins - John John Techflex", 595.00);
    recebimento(3035, "Leash", "Bullys - Essential 7ft", 115.00);
    recebimento(3002, "Deck", "Onboard - Performance Pad", 380.00);
    recebimento(3045, "Parafina", "Sex Wax - Mega Grip Tropical", 450.00);
    recebimento(3020, "Quilha", "Feather Fins - Carbon Hybrid", 295.00);
    recebimento(3032, "Leash", "Creatures of Leisure - Reliance 7ft", 265.00);
    recebimento(3009, "Deck", "Onboard - Prone Series Pad", 75.00);
    recebimento(3044, "Parafina", "Fu Wax - Cold Water Special", 350.00);
    recebimento(3024, "Quilha", "True Ames - Greenough Single Fin", 495.00);
    recebimento(3036, "Leash", "Ocean & Earth - ONE XT Premium", 365.00);
    recebimento(3018, "Deck", "Famous Surf - The Drop Traction", 580.00);
    recebimento(3040, "Parafina", "Ransom - Wax Cold Water", 550.00);
    recebimento(3029, "Quilha", "Futures Fins - Legacy Series", 750.00);
    recebimento(3003, "Leash", "Stay Covered - Big Wave 10ft", 465.00);
    recebimento(3027, "Deck", "Creatures of Leisure - Mick Fanning", 720.00);
    recebimento(3023, "Deck", "Shapers - Stealth Traction", 230.00);

    system("cls");
    int opcao, codigo;
    char escolha[50];
    float min, max;
    printf("-- Bem-vindo(a) a loja Tati Surf Co! --\n\n");
    desenhar_surfista();

    do{
        printf("-> Opcao 1: Ver produtos disponiveis para compra\n");
        printf("-> Opcao 2: Ver produtos por categoria\n");
        printf("-> Opcao 3: Ver produtos por intervalo de valores\n");
        printf("-> Opcao 4: Comprar item\n");
        printf("-> Opcao 5: Despachar pedido para entrega\n");
        printf("-> Opcao 6: Encerrar atendimento\n");
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
            char *nome_cliente = malloc(sizeof(char)*255);
            char *nome_rua = malloc(sizeof(char)*255);
            char *complemento = malloc(sizeof(char)*255);
            char *cpf = malloc(sizeof(char)*15);
            char *cep = malloc(sizeof(char)*15);
            int num_casa;
            printf("Digite o codigo do produto que gostaria de comprar: ");
            scanf("%d", &codigo);            
            NO*produto_removido = comprar_produto(codigo);

            if (produto_removido != NULL) {
                printf("--- DIGITE SEUS DADOS PARA ENTREGA ---\n\n");
                printf("Nome do Cliente: ");
                scanf(" %[^\n]", nome_cliente);

                printf("CPF (somente numeros): ");
                scanf("%s", cpf);

                printf("CEP: ");
                scanf("%s", cep);

                printf("Nome da Rua: ");
                scanf(" %[^\n]", nome_rua);

                printf("Numero da Casa/Apto: ");
                scanf("%d", &num_casa);

                printf("Complemento: ");
                scanf(" %[^\n]", complemento);
                system("cls");

                fila_pedidos_entrega(produto_removido, nome_cliente, cpf, cep, nome_rua, num_casa, complemento);
                
                printf("=> Seu pedido foi adicionado a fila de entregas com sucesso, %s!\n\n", nome_cliente);
            }else{
                printf("=> Erro: Produto com codigo %d nao encontrado.\n\n", codigo);
            }
            Sleep(1500);
            break;

        case 5:
            system("cls");
            printf("=> Despachando pedido para o entregador...\n");
            entregar_pedido();
            Sleep(1500);
            break;
        
        case 6:
            system("cls");
            printf("=> Encerrando atendimento. Volte sempre!");
            break;

        default:
            system("cls");
            printf("=> Opcao %d nao existe: Digite uma opcao valida.\n", opcao);
            break;
        }
    }while(opcao != 6);

    

    return 0;
}
