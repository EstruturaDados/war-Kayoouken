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



//Área destinada para colocar os protótipos da funções



//FIm dos protótipos


int main(){
    srand(time(NULL));
    setlocale(LC_ALL,"Portuguese");
    //Utilização de ponteiros que indicaram as structs do programa
    struct Territorio *Mapa_mundi = (struct Territorio *)calloc(MAX_TERRITORIO, sizeof(struct Territorio));
    //verificar se a alocação deu tudo ok
    if (Mapa_mundi == NULL){
        printf("ERRO: falha na alocação de memória. \n");
        return 1;
        //Se voltar um 1 deu b.o
    }
    
    //aloc de memoria//ponteiros
    struct Missoes missaoAtual;
    
    printf("=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-");
    printf("  BEM VINDO ao jogo de Guerra!   ");
    printf("=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-");
    printf("Sua missão %s\n\n", missaoAtual.nomeMissao);

   
    int opcao = -1; 
    while (opcao != 0) {
        exibirTerritorio(Mapa_mundi);
        exibirMenu(Mapa_mundi, &missaoAtual);
    }


    
    

    //Parte final, onde se incia os confrontos
    int atk01;
    int atk02;
    printf("\n=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n Vamos iniciar os confrontos entre territórios\n");
    printf("=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("Escolha um territorio atacante entre 1 a 5: ");
    scanf("%d", &atk01);
    printf("Escolha outro territorio para travar batalha entre 1 a 5 , (tirando o ja escolhido anteriormente)");
    scanf("%d", &atk02);
    
    if (atk01 == atk02){
        printf("Erro: O territorio atacante não pode ser o mesmo que o defensor. \n");
    }else {
        printf("\nProcessando Batalha...\n");
        confrontoTerritorios(&Mapa_mundi[atk01 - 1], &Mapa_mundi[atk02 - 1]);
    }
    

    free(Mapa_mundi); //Tem que colocar o parâmetro nao esquecer

       
    

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
    
    strcpy(quest[0].nomeMissao, "Acabar com o exercito rival com menos tropas");
    quest[0].numeroMissao = 1;

    strcpy(quest[1].nomeMissao, "Acabar com o exercito rival com mais tropas");
    quest[1].numeroMissao = 2;

    strcpy(quest[2].nomeMissao, "Acabar com 2 exercitos");
    quest[2].numeroMissao = 3;

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
void exibirMenu( struct terrritorio *mapaJogador,struct Missoes * missaoJogador){
    printf("--------------------------------------");
    printf("O territorio do jogador é %s", mapaJogador);
    printf("Missão principal jogador: %s ", missaoJogador);
    printf("           Menu de ações: \n          ");
    printf("1 - Atacar                          \n");
    printf("2 - Verificar missão                \n");
    printf("0 - Sair                            \n");
    printf("--------------------------------------");
    int resposta;
    scanf("%d", &resposta);
    struct Territorio * Mapa_mundi;

    switch(resposta){
        case 1:{
            printf("Vamos ao ataque!");
            int atk01;
            int atk02;
            printf("\n=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=");
            printf("\n Vamos iniciar os confrontos entre territórios\n");
            printf("=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
            printf("Escolha um territorio atacante entre 1 a 5: ");
            scanf("%d", &atk01);
            printf("Escolha outro territorio para travar batalha entre 1 a 5 , (tirando o ja escolhido anteriormente)");
            scanf("%d", &atk02);
            
            if (atk01 < 1|| atk01 > 5||atk02 < 1|| atk02 > 5){
                printf("Erro: Numero inválido. Tente novamente \n");
            }else if (atk01 == atk02){
                printf("O territorio atacante não pode ser o mesmo que o defensor");
            }else {
                confrontoTerritorios(&Mapa_mundi[atk01], &Mapa_mundi[atk02]);
            }
            
            break;
        }
        case 2:
            exibirTerritorios(Mapa_mundi);
            break;
        case 3:
        printf("\nLembrete da sua missão %s\n", missaoJogador-> nomeMissao);
        
            
        
    }
}//Adicionei a chave q faltava pra fechar a função


//Fim função



//FUnção pra inicializar
void inicializarMapa(struct Territorio *mapa){
    
    
        //dados África
    struct Territorio modeloMapa[MAX_TERRITORIO] = {
        { "África",         "Amarelo",   4 },
        { "Oceania",        "Azul",      3 },
        { "Europa",         "Vermelho",  3 },//troquei a disposição dos Territorios dentro dessa struct, fica mais legível
        { "America do Sul", "Verde",     5 },
        { "Ásia",           "Rosa",      5 }
    };
    for (int i = 0;i < MAX_TERRITORIO; i++){
        strcpy(mapa[i].nomeTerritorio, modeloMapa[i].nomeTerritorio);
        strcpy(mapa[i].corTerritorio, modeloMapa[i].numeroTropas);
        mapa[i].numeroTropas = modeloMapa[i].numeroTropas;
    }
}
//FIM FUNÇÃO



//--- Função para exibir territórios ---
void exibirTerritorio(struct Territorio *mapa){

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
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
}
// --- FIM FUNÇÂO ---

                            //Parâmetro 1, relacionado a atacante//Parâmetro 2, relacionado ao defensor
void confrontoTerritorios(struct Territorio* atacante, struct Territorio* defensor){
    //Inicializa o gerador de números aleatorios 
    //srand(time(NULL)) garante que os resultados dos dados sejam diferentes a cada
    

    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    printf("A batalha será travada entre %s (Atacante) e %s (Defensor)");
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

    if (lancarDados == 1 ){
        diminuirTropasPerdedor(defensor);
    }else{
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

        // Loop para lançar os dados
        for (int i = 0; i < 2; i++) {
            // Gera um número aleatório entre 1 e 6
            dados[i] = (rand() % 6) + 1;
            printf("Dado %d lançado: %d\n", i + 1, dados[i]);
        }

        if (dados[0] > dados[1]) {
            printf("\nO Atacante foi vitorioso com um %d e o defensor perdeu com %d\n", dados[0], dados[1]);
            vencedor = 1;
        } else if (dados[0] == dados[1]) {
            printf("\nO confronto deu empate! Vamos tentar novamente.\n");
            houveEmpate = 1; // Define a variável para manter o loop ativo
            printf("\nAperte Enter para continuar...");
            getchar();
        } else {
            printf("\nO defensor foi vitorioso com um %d e o atacante perdeu com %d\n", dados[1], dados[0]);
            vencedor = 2;
        }
    } while (houveEmpate == 1); // A condição para o loop continuar é se houver empate

    return vencedor; //Se 1 == atacante vencendor|| se 2 == Defensor vencedor
}

//Adição de cada uma das funções a serem executadas dentro do main



//Fim declaração

 

//--- Ínicio da função principal ---