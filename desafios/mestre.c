#include <stdio.h>
#include <stdlib.h> // dynamic memory and rand()
#include <string.h>
#include <time.h> // for srand(time(NULL))

// Definition of the struct (Definition da estrutura)
typedef struct {
    char nome[50];
    char cor[20];
    int tropas;
} Territorio;

// Enum para facilitar a leitura das missões
typedef enum { DESTRUIR_INIMIGO, CONQUISTAR_3 } TipoMissao;

// Protótipos das funções (Modularização)
void inicializarMapa(Territorio *mapa);
void exibirMapa(const Territorio *mapa, int total);
void realizarBatalha(Territorio *at, Territorio *df);
int verificarMissao(const Territorio *mapa, int total, TipoMissao missao, const char *corJogador, const char *corAlvo);

int main()
{
    srand(time(NULL)); // Seed for randomness
    int total = 5;
    // Dynamic allocation with calloc (Alocação dinâmica)
    Territorio *mapa = (Territorio *) calloc(total, sizeof(Territorio));

    if (!mapa) return 1;
    inicializarMapa(mapa);

    // Sorteia qual território pertence ao jogador
    int indiceJogador = rand() % 5;
    char corJogador[20];
    strcpy(corJogador, mapa[indiceJogador].cor);

    // Sorteia a missão
    TipoMissao minhaMissao = rand() % 2;
    char corAlvo[20] = "Verde"; // Alvo padrão

    // Se a missão for destruir e o jogador for verde, mudamos o alvo para não atacar o Brasil!
    if (minhaMissao == DESTRUIR_INIMIGO && strcmp(corJogador, "Verde") == 0) {
        strcpy(corAlvo, "Vermelho");
    }

    printf("--- WAR MESTRE: MISSAO ALEATORIA ---\n");
    printf("Voce comeca no territorio: %s (Exercito %s)\n", mapa[indiceJogador].nome, corJogador);

    if (minhaMissao == DESTRUIR_INIMIGO) 
    {
        printf("SUA MISSAO: Destruir o Exercicio %s\n", corAlvo);
    } else {
        printf("SUA MISSAO: Conquistar 3 territorios para o exercito %s\n", corJogador);
    }
    
    int op;
    do
    {
        printf("\n1. Atacar | 2. Ver Mapa | 3. Verificar Missao | 0. Saida: ");
        scanf("%d", &op);

        if (op == 1)
        {
            int a, d;
            printf("ID Atacante (1-5): "); scanf("%d", &a);
            printf("ID Defensor (1-5): "); scanf("%d", &d);

            if (a >= 1 && a <= 5 && d >= 1 && d <= 5 && a != d) {
                 // NOVA TRAVA: Correção da sintaxe do strcmp
                if (mapa[a-1].tropas <= 1) {
                    printf("ERRO: Voce precisa de pelo menos 2 tropas para atacar!\n");
                } 
                else if (strcmp(mapa[a-1].cor, mapa[d-1].cor) == 0) {
                    printf("ERRO: Você nao pode atacar seu proprio exercito (%s)!\n", mapa[a-1].cor);
                } 
                else {
                    realizarBatalha(&mapa[a-1], &mapa[d-1]);
                } 
            } else {
                    printf("Comando invalido!\n");
            } 
        }
        else if (op == 2) exibirMapa(mapa, total);
        else if (op == 3) {
            if (verificarMissao(mapa, total, minhaMissao, corJogador, corAlvo)) {
                printf("\n VITORIA! Voce cumpriu e dominou o campo!\n");
                op = 0; // Finaliza o jogo
            } else {
                printf("\nKeep fighting! A missao ainda nao foi concluida. Continue a estrategia! \n"); 
            }
        }
    } while (op != 0);

    free(mapa);
    return 0;
}  
    
// Inicialização automática para testar rápido
void inicializarMapa(Territorio *mapa) {
    char nomes[5][50] = {"Brasil", "Egito", "Alascar", "Russia", "Japao"};
    char cores[5][20] = {"Verde", "Amarelo", "Azul", "Verde", "Vermelho"};
    for (int i = 0; i < 5; i++)
    {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].cor, cores[i]);
        mapa[i].tropas = (rand() % 5) + 3;
    }
} 

void exibirMapa(const Territorio *mapa, int total) {
    printf("\n--- SITUACAO DO MUNDO ---\n");
    for (int i = 0; i < total; i++)
    {
        printf("[%d] %-10s | Cor: %-10s | Tropas: %d\n", i+1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);

    }
    
}

void realizarBatalha(Territorio *at, Territorio *df) {
    int dAt = (rand() % 6) + 1;
    int dDf = (rand() % 6) + 1;
    printf("\n %s vs %s | Dados: A(%d) D(%d)\n", at->nome, df->nome, dAt, dDf);
    
    if (dAt >= dDf)
    {
        df->tropas--;
        if (df->tropas <= 0) 
        {
            printf("VITORIA! %s agora e %s!\n", df->nome, at->cor);
            strcpy(df->cor, at->cor);
            df->tropas = 1;
        } else printf("O defensor perdeu 1 tropa!\n");
    } else {
        at->tropas--;
        if (at->tropas < 1) at->tropas = 1; // Ataque nunca fica com menos de 1
        printf("A desefa resistiu! Atacante perdeu 1 tropa.\n");
    }
}


int verificarMissao(const Territorio *mapa, int total, TipoMissao missao, const char *corJogador, const char *corAlvo) {
    printf("\n--- RELATORIO DE MISSAO ----\n");

    if (missao == DESTRUIR_INIMIGO) {
        int inimigosRestantes = 0;
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, corAlvo) == 0) {
                inimigosRestantes++;
            } 
        }

        if (inimigosRestantes == 0) {
            return 1; // Vitória!
        } else {
            printf("Objetivo: Eliminar o Exercito %s.\n", corAlvo);
            printf("Status: Ainda restam %d territorios inimigos! Continue atacando.\n", inimigosRestantes);
            return 0;
        }
        
    }
    else {// Missão CONQUISTAR_3
        int meusTerritorios = 0;
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                meusTerritorios++;
            }
        }

        printf("Objetivo: Dominar 3 territorios com a cor %s.\n", corJogador);
        printf("Status: Voce possui %d de 3 territorios necessarios.\n", meusTerritorios);
    
        return (meusTerritorios >= 3);
    }
    
}
    
