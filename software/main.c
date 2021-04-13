#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h> //No linux/Mac //sleep(numero de segundos pausado);
#include <windows.h>> //Para dar pause. //Sleep(numero de segundos pausado);

typedef struct{
    int codigo;
    char nome[30];
    float preco;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} Carrinho;

void infoProduto(Produto prod);
void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
Produto pegarProdutoPorCodigo(int codigo); //Busca o produto pelo código.
int * temNoCarrinho(int codigo); //Verifica se o produto ja esta no carrinho.
void fecharPedido();

static int contador_produto = 0; //Quantos produtos tem cadastrados.
static int contador_carrinho = 0; //Quantos produtos tem no carrinho.
static Carrinho carrinho[50]; //Itens no carrinho, adiciona os produtos que ficaram no carrinho.
static Produto produtos[50]; //Cadastrar os produtos no supermercado.

int main(){

    menu();

    return 0;
}

void infoProduto(Produto prod){
    printf("Codigo: %d \nNome: %s \nPreco: %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco); //strtok("vai aparecer", ""remove o /n"")
}

void menu(){

    system("cls");

    int opcao = 1;

    while((opcao > 0) && (opcao < 7)){
        printf("############################################################\n");
        printf("############## Bem Vindo ao Supermercado Geek ##############\n");
        printf("############################################################\n\n");

        printf("Selecione uma opcao abaixo: \n");
        printf("1 - Cadastrar Produto:\n");
        printf("2 - Listar Produto:\n");
        printf("3 - Comprar Produto:\n");
        printf("4 - Visualizar Carrinho:\n");
        printf("5 - Fechar Pedido:\n");
        printf("6 - Sair do Sistema:\n\n");



        printf("     O que deseja fazer: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1:
                cadastrarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                comprarProduto();
                break;
            case 4:
                visualizarCarrinho();
                break;
            case 5:
                fecharPedido();
                break;
            case 6:
                printf("Volte sempre!\n\n");
                Sleep(3);
                exit(0);
            default:
                printf("Opcao Invalida!");
                Sleep(3);
                menu();
                break;
        }
    }
}

void cadastrarProduto(){

    system("cls");

    printf("###########################################################\n");
    printf("#################### Supermercado Geek ####################\n");
    printf("###########################################################\n\n");

    printf("    Cadastro de Produto: \n\n");
    printf("Informe o nome do produto: ");
    fgets(produtos[contador_produto].nome, 30, stdin);

    printf("\nInforme o preco do produto: ");
    scanf("%f", &produtos[contador_produto].preco);

    printf("\n\nO produto foi cadastrado com Sucesso!\n", strtok(produtos[contador_produto].nome, "\n"));
    produtos[contador_produto].codigo = (contador_produto + 1);
    contador_produto++;
    sleep(3);
    system("cls");
}

void listarProdutos(){
    system("cls");

    printf("###########################################################\n");
    printf("#################### Supermercado Geek ####################\n");
    printf("###########################################################\n\n");

    if(contador_produto > 0){
        printf("    Listagem de Produtos:\n\n");
        printf("-----------------------------------------------------------\n");
        for(int i = 0; i < contador_produto; i++){
            infoProduto(produtos[i]);
            printf("-----------------------------------------------------------\n");
        }
    } else{
        printf("Nao existe produtos cadastrados.");
        sleep(3);
        menu();
    }
    system("pause");
    system("cls");

}

void comprarProduto(){
    if(contador_produto > 0){

        system("cls");

        printf("###########################################################\n");
        printf("#################### Supermercado Geek ####################\n");
        printf("###########################################################\n\n");

        printf("Adicionar no Carrinho:\n\n");

        printf("Listagem de produtos:\n\n");
        printf("---------------------------------------------\n\n");
        for(int i = 0; i < contador_produto; i++){
            infoProduto(produtos[i]);
            printf("---------------------------------------------\n");
        }

        int codigo;
        printf("Informe o codigo do produto: ");
        scanf("%d", &codigo);
        getchar();

        int tem_mercado = 0;
        for(int i = 0; i < contador_produto; i++){
            if(produtos[i].codigo == codigo){ //verifica se tem cadastro com o codigo que foi pedido.
                tem_mercado = 1;

                if(contador_carrinho > 0){ // verifica se tem produto no carrinho.
                    int *retorno = temNoCarrinho(codigo);

                    if(retorno[0] == 1){
                        carrinho[retorno[1]].quantidade++; //Se ja tiver no carrinho o programa vai direto no arrei q esta o produto e adiciona quantidade.
                        printf("Quantidade do produto %s foi aumentada no carrinho.\n", strtok(carrinho[retorno[1]].produto.nome, "\n"));
                        sleep(3);
                        menu();
                    } else{ //Caso o produto nao exista no carrinho ele sera adicionado
                        Produto p = pegarProdutoPorCodigo(codigo);
                        carrinho[contador_carrinho].produto = p;
                        carrinho[contador_carrinho].quantidade = 1;
                        contador_carrinho++;
                        printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
                        sleep(3);
                        menu();
                    }
                } else{
                    Produto p = pegarProdutoPorCodigo(codigo);
                    carrinho[contador_carrinho].produto = p;
                    carrinho[contador_carrinho].quantidade = 1;
                    contador_carrinho++;
                    printf("O produto %s foi adicionado no carrinho. \n", strtok(p.nome, "\n"));
                    sleep(3);
                    menu();
                }
            }
        }
        if(tem_mercado < 1){
            printf("Nao foi encontrado o produto com o codigo: %d.\n", codigo);
            sleep(2);
            menu();
        }

    } else {
        printf("Não existe produto para vender!\n\n");
        sleep(3);
    }
}

void visualizarCarrinho(){

    system("cls");

    printf("###########################################################\n");
    printf("#################### Supermercado Geek ####################\n");
    printf("###########################################################\n\n");

    if(contador_carrinho > 0){
        printf("    Produtos do Carrinho:\n");
        printf("-----------------------------------------------------------\n");
        for(int i = 0; i < contador_carrinho; i++){
            infoProduto(carrinho[i].produto);
            printf("Quantidade: %d\n", carrinho[i].quantidade);
            printf("-----------------------------------------------------------\n");
            Sleep(1);
        }
    } else {
        printf("Nao ha produtos no carrinho!\n");
    }
    system("pause");
    system("cls");
}

Produto pegarProdutoPorCodigo(int codigo){
    Produto p;

    for(int i = 0; i < contador_produto; i++){
        if(produtos[i].codigo == codigo){
            p = produtos[i];
        }
    }

    return p;
}

int * temNoCarrinho(int codigo){
    int static retorno[] = {0, 0};
    for(int i = 0; i < contador_carrinho; i++){
        if(carrinho[i].produto.codigo == codigo){
            retorno[0] = 1; //Já existe esse produto no carrinho.
            retorno[1] = i; //Indice do produto no carrinho.
        }
    }
    return retorno;
}

void fecharPedido(){
    system("cls");

    printf("###########################################################\n");
    printf("#################### Supermercado Geek ####################\n");
    printf("###########################################################\n\n");

    if(contador_carrinho > 0){
        float valorTotal = 0.0;
        printf("    Produtos no Carrinho:\n\n");
        printf("-----------------------------------------------------------\n");
        for(int i = 0; i < contador_carrinho; i++){
            Produto p = carrinho[i].produto;
            int quantidade = carrinho[i].quantidade;
            valorTotal += p.preco * quantidade;
            infoProduto(p);
            printf("Quantidade: %d\n", quantidade);
            printf("-----------------------------------------------------------\n");
            sleep(1);
        }
    printf("Sua fatura e R$: %.2f\n\n", valorTotal);


    contador_carrinho = 0; //Limpando Carrinho:

    printf("    Obrigado pela preferencia\n");
    sleep(3);
    menu();

    } else{
        printf("Nao ha produtos no carrinho!\n");
        sleep(3);
        menu();
    }
}
