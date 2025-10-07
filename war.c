//Lembrando que eu fiz tudo pelo meu vscode do meu desktop

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> //Caracteres especiais em C
#include <time.h> // Para usar na geração de números aleatórios


//--- Constantes ---
#define MAX_TROPAS 5
#define MAX_STRING 100
#define MAX_TERRITORIO 5
#define TOTAL_MISSOES 3
//--- Constantes ---


struct Missoes{
    int numeroMissao;
    char nomeMissao[MAX_STRING];
};



//--- Struct pois vai armazenar dados de diferentes naturalidades ----
struct Territorio{
    char nomeTerritorio[MAX_STRING];
    char corTerritorio[MAX_STRING];
    int numeroTropas;
};
// --- FIM STRUCT ---



//--- ÁREA DESTINADA PARA COLOCAR OS PROTÓTIPOS DAS FUNÇÕES ---
void removerNovaLinha (char *str);
void lancarMissao(struct Missoes *quest);
void limpezaBuffer();
void exibirMenu(struct Territorio *mapa, struct Missoes *missaoAtual); // CORREÇÃO: Parâmetros ajustados
void inicializarMapa(struct Territorio *mapa);
void exibirTerritorio(struct Territorio *mapa);
void confrontoTerritorios(struct Territorio* atacante, struct Territorio* defensor);
void diminuirTropasPerdedor(struct Territorio *perdedor);
int lancarDados();
//--- FIM DOS PROTÓTIPOS ---



int main(){
    srand(time(NULL));
    setlocale(LC_ALL, "Portuguese");
    

    //Alocação dinâmica de memória
    //Utilização de ponteiros que indicaram as structs do programa
    int opcao = -1;
    struct Territorio *Mapa_mundi;
    //calloc p memória e ja inicia com zero
    Mapa_mundi = (struct Territorio *) calloc(MAX_TERRITORIO, sizeof(struct Territorio));

    //Verificação: se a alocação de memória foi efetivada com sucesso
    if (Mapa_mundi == NULL){
        printf("ERRO: falha na alocação de memória. \n");
        return 1;
    } //Se voltar "1", deu B.O
    
    struct Missoes missaoAtual;
    inicializarMapa(Mapa_mundi);
    lancarMissao(&missaoAtual);

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("     Bem VINDO ao jogo de Guerra   \n" );
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Sua missão %s\n\n", missaoAtual.nomeMissao);
    
    
    while (opcao != 0){
        exibirMenu(Mapa_mundi, &missaoAtual);
    }

    free(Mapa_mundi);

    printf("\nJogo finalizado. Até a proxima\n");

    return 0;

}
// --- FIM função principal ---


//--- Comeco FUnção quebra de linha ----
void removerNovaLinha (char *str){
    //A função strcspn encontra o primeiro caractere de quebra de linha '\n'
    str[strcspn(str, "\n")] = 0;
}

//--Fim Função--

//FUnção pra lancar as missões
void lancarMissao(struct Missoes *quest){
    //Criar um banco de missões possiveis
    struct Missoes bancoDeMissoes[TOTAL_MISSOES];
    
    strcpy(bancoDeMissoes[0].nomeMissao, "Acabar com o exercito rival com menos tropas");
    bancoDeMissoes[0].numeroMissao = 1;

    strcpy(bancoDeMissoes[1].nomeMissao, "Acabar com o exercito rival com mais tropas");
    bancoDeMissoes[1].numeroMissao = 2;

    strcpy(bancoDeMissoes[2].nomeMissao, "Acabar com 2 exercitos");
    bancoDeMissoes[2].numeroMissao = 3;

    //Sorteia um indice aleatório do banco de missões
    int indiceSorteado = rand() % TOTAL_MISSOES;

    //Copia a missão sorteada para a missão atual do jogador
    *quest = bancoDeMissoes[indiceSorteado];

}


//--- Função para limpeza de buffer ---
void limpezaBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
// --- FIM FUNÇÂO ---


//função para exibir menu de ações
void exibirMenu(struct Territorio *mapa, struct Missoes *missaoJogador){
    int opcao;
   
    printf("\n--------------------------------------\n");
    printf("           Menu de Ações\n");
    printf("--------------------------------------\n");
    printf("1 - Atacar\n");
    printf("2 - Exibir Mapa de Territórios\n");
    printf("3 - Verificar Missão\n");
    printf("0 - Sair do Jogo\n");
    printf("--------------------------------------\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    limpezaBuffer();

    switch(opcao){
        case 1:{
            printf("\n--- MODO DE ATAQUE ---\n");
            
            int atk01;
            int atk02;
            
            printf("Escolha um território para ser o ATACANTE (1 a 5): ");
            scanf("%d", &atk01);
            limpezaBuffer();

            printf("Escolha um território para ser o DEFENSOR (1 a 5): ");
            scanf("%d", &atk02);
            limpezaBuffer();
            
            if (atk01 < 1 || atk01 > MAX_TERRITORIO || atk02 < 1 || atk02 > MAX_TERRITORIO){
                printf("\nErro: Número de território inválido. Tente novamente.\n");
            } else if (atk01 == atk02){
                printf("\nErro: O território atacante não pode ser o mesmo que o defensor.\n");
            } else {
                printf("\nProcessando Batalha...\n");
                // CORREÇÃO: Usando o ponteiro 'mapa' que foi recebido pela função.
                // O índice do array é (número escolhido - 1)
                confrontoTerritorios(&mapa[atk01 - 1], &mapa[atk02 - 1]);
            }
            break;
        }
        case 2:
            exibirTerritorio(mapa);
            break;
        case 3:
            printf("\nLEMBRETE DA SUA MISSÃO: %s\n", missaoJogador->nomeMissao);
            break;
        case 0:
            // Este caso não precisa de código, o loop no main() vai terminar.
            break;
        default:
            printf("\nOpção inválida! Tente novamente.\n");
            break;
    }

    return opcao;
}



//Fim função



//FUnção pra inicializar
//FUnção pra inicializar
void inicializarMapa(struct Territorio *mapa){
    struct Territorio modeloMapa[MAX_TERRITORIO] = {
        { "África",         "Amarelo",  4 },
        { "Oceania",        "Azul",     3 },
        { "Europa",         "Vermelho", 3 },
        { "America do Sul", "Verde",    5 },
        { "Ásia",           "Rosa",     5 }
    };
    for (int i = 0; i < MAX_TERRITORIO; i++){
        strcpy(mapa[i].nomeTerritorio, modeloMapa[i].nomeTerritorio);
        strcpy(mapa[i].corTerritorio, modeloMapa[i].corTerritorio);
        mapa[i].numeroTropas = modeloMapa[i].numeroTropas;
    }
}
    //FIM FUNÇÃO



//--- Função para exibir territórios ---
void exibirTerritorio(struct Territorio *mapa){

    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Exibindo territórios cadastrados \n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    printf("Pressione Enter para continuar.\n");
    getchar();
//-----------------------------------------------------
    for(int c = 0;c < MAX_TERRITORIO; c++){
        printf("%dº territorio:\n", c + 1);
        printf("Nome: %s\n", mapa[c].nomeTerritorio);
        printf("Cor: %s\n", mapa[c].corTerritorio);
        printf("Quantidade de tropas: %d\n", mapa[c].numeroTropas);
        printf("=-=-=-=-=-=-=-=-=-=-=\n");
    }
    printf("Pressione Enter para continuar...\n");
    getchar();
}
// --- FIM FUNÇÂO ---

                            //Parâmetro 1, relacionado a atacante//Parâmetro 2, relacionado ao defensor
void confrontoTerritorios(struct Territorio* atacante, struct Territorio* defensor){
    //Inicializa o gerador de números aleatorios 
    //srand(time(NULL)) garante que os resultados dos dados sejam diferentes a cada
    

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("A batalha será travada entre %s (Atacante) e %s (Defensor)", atacante ->nomeTerritorio, defensor -> nomeTerritorio);
    printf("%s tem %d tropas.\n", atacante->nomeTerritorio, atacante->numeroTropas);
    printf("%s tem %d tropas.\n", defensor->nomeTerritorio, defensor->numeroTropas);
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");


    //Validação: O atacante precisa de pelo menos 2 tropas para atacar.
    if (atacante->numeroTropas < 2) {
        printf("O atacante %s não tem tropas suficientes para atacar!\n", atacante->nomeTerritorio);
        return;
    }

    //Inserindo a função lancar dados dentro da função confronto
    int vencedor = lancarDados();

    if (vencedor == 1 ){
        printf("Vitória do ATACANTE! \n");
        diminuirTropasPerdedor(defensor);
    }else{
        printf("Vitória do DEFENSOR\n");
        diminuirTropasPerdedor(atacante);
    }

}

//função para diminuir um no territorio perdedor
void diminuirTropasPerdedor(struct Territorio *perdedor){
    perdedor->numeroTropas--;
    printf("O território %s perdeu 1 tropa. Agora tem %d tropas. \n", perdedor->nomeTerritorio, perdedor->numeroTropas);
}

//Função para lançamento de dados
int lancarDados() {
    int dados[2];
    int houveEmpate;
    int vencedor; // vencedor: 1= Atacante // 2 = Defensor
    
    // O loop 'do-while' vai garantir que a rodada seja jogada até que haja um vencedor
    do {
        houveEmpate = 0; // Reseta a variável a cada nova rodada
        
        printf("Lançando dados...\n");
        getchar();

        dados[0] = (rand() % 6) + 1;
        printf("Dado do ATACANTE: %d\n", dados[0]);

        dados[1] = (rand() % 6) + 1;
        printf("Dado do DEFENSOR: %d\n", dados[1]);

        // Loop para lançar os dados
        if (dados[0] > dados[1]){
            vencedor = 1;
            }else if (dados[0] < dados[1]){
                vencedor = 2;
            }else{
                printf("\nO confronto deu EMPATE! Lançando os dados novamente;\n");
                houveEmpate = 1;
            }
        }while (houveEmpate == 1);

        return vencedor;
    }

//Fim declaração

 

//--- Ínicio da função principal ---
