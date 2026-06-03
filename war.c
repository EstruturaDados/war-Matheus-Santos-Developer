// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
//         Empresa: MateCheck
//         Níveis: Novato | Aventureiro | Mestre
// ============================================================================
//
// COMO USAR:
// Para compilar e rodar um nível específico, comente os outros dois blocos
// main() ou use o menu inicial que escolhe qual nível jogar.
//
// Compile com: gcc war.c -o war
// Execute com: ./war
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ============================================================================
// CONSTANTES GLOBAIS
// ============================================================================
#define MAX_TERRITORIOS  5    // número fixo de territórios no mapa
#define MAX_NOME        30    // tamanho máximo do nome do território
#define MAX_COR         10    // tamanho máximo da cor do exército
#define NUM_MISSOES      2    // quantidade de missões disponíveis

// ============================================================================
// ESTRUTURA DE DADOS — usada nos 3 níveis
// ============================================================================
typedef struct {
    char nome[MAX_NOME];  // nome do território
    char cor[MAX_COR];    // cor do exército dominante
    int  tropas;          // quantidade de tropas presentes
} Territorio;


// ============================================================================
//
//  ██╗     ██╗   ██╗███████╗██╗         ███╗   ██╗ ██████╗ ██╗   ██╗ █████╗ ████████╗ ██████╗
//  ██║     ██║   ██║██╔════╝██║         ████╗  ██║██╔═══██╗██║   ██║██╔══██╗╚══██╔══╝██╔═══██╗
//  ██║     ██║   ██║█████╗  ██║         ██╔██╗ ██║██║   ██║██║   ██║███████║   ██║   ██║   ██║
//  ██║     ╚██╗ ██╔╝██╔══╝  ██║         ██║╚██╗██║██║   ██║╚██╗ ██╔╝██╔══██║   ██║   ██║   ██║
//  ███████╗ ╚████╔╝ ███████╗███████╗    ██║ ╚████║ ██████╔╝ ╚████╔╝ ██║  ██║   ██║   ╚██████╔╝
//  ╚══════╝  ╚═══╝  ╚══════╝╚══════╝    ╚═╝  ╚═══╝ ╚═════╝   ╚═══╝  ╚═╝  ╚═╝   ╚═╝    ╚═════╝
//
//  Conceitos: struct | vetor estático | scanf/fgets/printf
// ============================================================================

// Cadastra os dados dos 5 territórios via terminal
void novato_cadastrar(Territorio mapa[]) {
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\n=== Território %d ===\n", i + 1);

        printf("  Nome          : ");
        scanf("%29s", mapa[i].nome);

        printf("  Cor do exército: ");
        scanf("%9s", mapa[i].cor);

        printf("  Nº de tropas  : ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibe todos os territórios cadastrados em formato de tabela
void novato_exibir(const Territorio mapa[]) {
    printf("\n╔══════════════════════════════════════════════╗\n");
    printf("║         MAPA DOS TERRITÓRIOS                 ║\n");
    printf("╠══════╦══════════════╦══════════════╦═════════╣\n");
    printf("║  Nº  ║ Nome         ║ Exército     ║ Tropas  ║\n");
    printf("╠══════╬══════════════╬══════════════╬═════════╣\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("║  %-3d ║ %-12s ║ %-12s ║  %-6d ║\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("╚══════╩══════════════╩══════════════╩═════════╝\n");
}

// Ponto de entrada do Nível Novato
void nivel_novato() {
    Territorio mapa[MAX_TERRITORIOS]; // vetor estático de structs

    printf("\n🟢 ========== NÍVEL NOVATO ==========\n");
    printf("Cadastre os 5 territórios do mapa.\n");

    novato_cadastrar(mapa);
    novato_exibir(mapa);

    printf("\n✅ Nível Novato concluído!\n");
}


// ============================================================================
//
//   █████╗ ██╗   ██╗███████╗███╗   ██╗████████╗██╗   ██╗██████╗ ███████╗██╗██████╗  ██████╗
//  ██╔══██╗██║   ██║██╔════╝████╗  ██║╚══██╔══╝██║   ██║██╔══██╗██╔════╝██║██╔══██╗██╔═══██╗
//  ███████║██║   ██║█████╗  ██╔██╗ ██║   ██║   ██║   ██║██████╔╝█████╗  ██║██████╔╝██║   ██║
//  ██╔══██║╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ██║   ██║██╔══██╗██╔══╝  ██║██╔══██╗██║   ██║
//  ██║  ██║ ╚████╔╝ ███████╗██║ ╚████║   ██║   ╚██████╔╝██║  ██║███████╗██║██║  ██║╚██████╔╝
//  ╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝╚═╝  ╚═╝ ╚═════╝
//
//  Conceitos: calloc/free | ponteiros | rand()/srand() | funções
// ============================================================================

// Aloca dinamicamente o vetor de territórios com calloc (memória zerada)
Territorio* aventureiro_alocar() {
    Territorio *mapa = (Territorio*) calloc(MAX_TERRITORIOS, sizeof(Territorio));
    if (mapa == NULL) {
        printf("❌ Erro: falha ao alocar memória!\n");
        exit(1);
    }
    return mapa;
}

// Preenche os territórios com dados pré-definidos (sem precisar digitar)
void aventureiro_inicializar(Territorio *mapa) {
    // Dados iniciais: nome, cor do exército, tropas
    char nomes[MAX_TERRITORIOS][MAX_NOME] = {"Brasil", "Argentina", "Chile", "Peru", "Colombia"};
    char cores[MAX_TERRITORIOS][MAX_COR]  = {"Azul", "Vermelho", "Verde", "Amarelo", "Roxo"};
    int  tropas[MAX_TERRITORIOS]          = {5, 4, 3, 6, 2};

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        strcpy(mapa[i].nome,  nomes[i]);
        strcpy(mapa[i].cor,   cores[i]);
        mapa[i].tropas = tropas[i];
    }
}

// Libera a memória alocada com calloc
void aventureiro_liberar(Territorio *mapa) {
    free(mapa);
}

// Exibe o mapa atual (leitura apenas, por isso usa const)
void aventureiro_exibir(const Territorio *mapa) {
    printf("\n╔══════════════════════════════════════════════╗\n");
    printf("║            ESTADO DO MAPA                    ║\n");
    printf("╠══════╦══════════════╦══════════════╦═════════╣\n");
    printf("║  Nº  ║ Nome         ║ Exército     ║ Tropas  ║\n");
    printf("╠══════╬══════════════╬══════════════╬═════════╣\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("║  %-3d ║ %-12s ║ %-12s ║  %-6d ║\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("╚══════╩══════════════╩══════════════╩═════════╝\n");
}

// Simula a batalha entre dois territórios com dados aleatórios (1 a 6)
// Modificar o mapa exige ponteiro (passagem por referência)
void aventureiro_simular_ataque(Territorio *mapa, int atk, int def) {
    // Valida os índices (converte de 1-5 para 0-4)
    atk--; def--;
    if (atk < 0 || atk >= MAX_TERRITORIOS || def < 0 || def >= MAX_TERRITORIOS) {
        printf("❌ Território inválido!\n");
        return;
    }
    if (atk == def) {
        printf("❌ Um território não pode atacar a si mesmo!\n");
        return;
    }

    // Rola os dados (1 a 6)
    int dado_atk = (rand() % 6) + 1;
    int dado_def = (rand() % 6) + 1;

    printf("\n⚔️  %s (dado: %d) ataca %s (dado: %d)\n",
           mapa[atk].nome, dado_atk, mapa[def].nome, dado_def);

    // Empate favorece o atacante (>= vence)
    if (dado_atk >= dado_def) {
        mapa[def].tropas--;
        printf("✅ Atacante venceu! %s perdeu 1 tropa. Restam: %d\n",
               mapa[def].nome, mapa[def].tropas);

        // Se o defensor ficou sem tropas, território é conquistado
        if (mapa[def].tropas <= 0) {
            printf("🏳️  %s foi conquistado por %s!\n", mapa[def].nome, mapa[atk].nome);
            strcpy(mapa[def].cor, mapa[atk].cor); // muda a cor do dono
            mapa[def].tropas = 1;                 // move 1 tropa para o novo território
        }
    } else {
        printf("🛡️  Defensor resistiu! Nenhuma tropa perdida.\n");
    }
}

// Fase de ataque: lê os territórios atacante e defensor e chama a simulação
void aventureiro_fase_ataque(Territorio *mapa) {
    int atk, def;
    printf("\nEscolha o território ATACANTE (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &atk);
    printf("Escolha o território DEFENSOR  (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &def);

    aventureiro_simular_ataque(mapa, atk, def);
}

// Ponto de entrada do Nível Aventureiro
void nivel_aventureiro() {
    srand((unsigned int) time(NULL)); // semente aleatória baseada no tempo

    Territorio *mapa = aventureiro_alocar();
    aventureiro_inicializar(mapa);

    printf("\n🔵 ========== NÍVEL AVENTUREIRO ==========\n");

    int opcao;
    do {
        aventureiro_exibir(mapa);
        printf("\n[1] Atacar  [0] Sair\nOpção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            aventureiro_fase_ataque(mapa);
        }
    } while (opcao != 0);

    aventureiro_liberar(mapa); // libera a memória alocada
    printf("\n✅ Nível Aventureiro encerrado!\n");
}


// ============================================================================
//
//  ███╗   ███╗███████╗███████╗████████╗██████╗ ███████╗
//  ████╗ ████║██╔════╝██╔════╝╚══██╔══╝██╔══██╗██╔════╝
//  ██╔████╔██║█████╗  ███████╗   ██║   ██████╔╝█████╗
//  ██║╚██╔╝██║██╔══╝  ╚════██║   ██║   ██╔══██╗██╔══╝
//  ██║ ╚═╝ ██║███████╗███████║   ██║   ██║  ██║███████╗
//  ╚═╝     ╚═╝╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝╚══════╝
//
//  Conceitos: modularização total | const correctness | missões | passagem por referência
// ============================================================================

// --- Protótipos das funções do Nível Mestre ---
Territorio* mestre_alocar_mapa();
void        mestre_inicializar_territorios(Territorio *mapa);
void        mestre_liberar_memoria(Territorio *mapa);
void        mestre_exibir_menu();
void        mestre_exibir_mapa(const Territorio *mapa);
void        mestre_exibir_missao(int missao_id);
void        mestre_fase_ataque(Territorio *mapa, const char *cor_jogador);
void        mestre_simular_ataque(Territorio *mapa, int atk, int def, const char *cor_jogador);
int         mestre_sortear_missao();
int         mestre_verificar_vitoria(const Territorio *mapa, int missao_id, const char *cor_jogador);
void        mestre_limpar_buffer();

// Aloca o mapa dinamicamente com calloc
Territorio* mestre_alocar_mapa() {
    Territorio *mapa = (Territorio*) calloc(MAX_TERRITORIOS, sizeof(Territorio));
    if (!mapa) {
        printf("❌ Falha ao alocar memória!\n");
        exit(1);
    }
    return mapa;
}

// Inicializa os territórios com dados pré-definidos
void mestre_inicializar_territorios(Territorio *mapa) {
    char nomes[MAX_TERRITORIOS][MAX_NOME] = {"Brasil", "Argentina", "Chile", "Peru", "Colombia"};
    // Cores dos exércitos: Azul = jogador, demais = inimigos
    char cores[MAX_TERRITORIOS][MAX_COR]  = {"Azul", "Verde", "Verde", "Vermelho", "Vermelho"};
    int  tropas[MAX_TERRITORIOS]          = {5, 4, 3, 6, 2};

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        strcpy(mapa[i].nome,  nomes[i]);
        strcpy(mapa[i].cor,   cores[i]);
        mapa[i].tropas = tropas[i];
    }
}

// Libera a memória alocada
void mestre_liberar_memoria(Territorio *mapa) {
    free(mapa);
}

// Exibe o menu principal do jogo
void mestre_exibir_menu() {
    printf("\n┌─────────────────────────────┐\n");
    printf("│        MENU PRINCIPAL       │\n");
    printf("├─────────────────────────────┤\n");
    printf("│  [1] Atacar                 │\n");
    printf("│  [2] Verificar Missão       │\n");
    printf("│  [0] Sair                   │\n");
    printf("└─────────────────────────────┘\n");
    printf("Opção: ");
}

// Exibe o estado atual do mapa (const = só leitura)
void mestre_exibir_mapa(const Territorio *mapa) {
    printf("\n╔══════════════════════════════════════════════╗\n");
    printf("║            ESTADO DO MAPA                    ║\n");
    printf("╠══════╦══════════════╦══════════════╦═════════╣\n");
    printf("║  Nº  ║ Nome         ║ Exército     ║ Tropas  ║\n");
    printf("╠══════╬══════════════╬══════════════╬═════════╣\n");
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("║  %-3d ║ %-12s ║ %-12s ║  %-6d ║\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("╚══════╩══════════════╩══════════════╩═════════╝\n");
}

// Exibe a missão do jogador com base no ID sorteado
void mestre_exibir_missao(int missao_id) {
    printf("\n🎯 SUA MISSÃO: ");
    switch (missao_id) {
        case 0: printf("Destruir completamente o exército VERDE!\n");    break;
        case 1: printf("Conquistar pelo menos 3 territórios!\n");        break;
        default: printf("Missão desconhecida.\n");
    }
}

// Sorteia um ID de missão aleatório (0 ou 1)
int mestre_sortear_missao() {
    return rand() % NUM_MISSOES;
}

// Limpa o buffer de entrada para evitar lixo em leituras consecutivas
void mestre_limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Executa a lógica da batalha entre dois territórios (passagem por referência)
void mestre_simular_ataque(Territorio *mapa, int atk, int def, const char *cor_jogador) {
    atk--; def--;
    if (atk < 0 || atk >= MAX_TERRITORIOS || def < 0 || def >= MAX_TERRITORIOS) {
        printf("❌ Território inválido!\n");
        return;
    }
    if (atk == def) {
        printf("❌ Um território não pode atacar a si mesmo!\n");
        return;
    }
    // Só pode atacar com territórios que já pertencem ao jogador
    if (strcmp(mapa[atk].cor, cor_jogador) != 0) {
        printf("❌ Você só pode atacar com seus próprios territórios!\n");
        return;
    }
    // Não pode atacar territórios aliados
    if (strcmp(mapa[def].cor, cor_jogador) == 0) {
        printf("❌ Você não pode atacar seu próprio território!\n");
        return;
    }

    int dado_atk = (rand() % 6) + 1;
    int dado_def = (rand() % 6) + 1;

    printf("\n⚔️  %s (dado: %d) ataca %s (dado: %d)\n",
           mapa[atk].nome, dado_atk, mapa[def].nome, dado_def);

    if (dado_atk >= dado_def) {
        mapa[def].tropas--;
        printf("✅ Você venceu! %s perdeu 1 tropa. Restam: %d\n",
               mapa[def].nome, mapa[def].tropas);

        if (mapa[def].tropas <= 0) {
            printf("🏆 %s foi CONQUISTADO! Agora pertence ao exército %s.\n",
                   mapa[def].nome, cor_jogador);
            strcpy(mapa[def].cor, cor_jogador);
            mapa[def].tropas = 1;
        }
    } else {
        printf("🛡️  Defensor resistiu! Nenhuma tropa perdida.\n");
    }
}

// Interface de ataque: lê os territórios e chama a simulação
void mestre_fase_ataque(Territorio *mapa, const char *cor_jogador) {
    int atk, def;
    mestre_exibir_mapa(mapa);
    printf("\nTerritório ATACANTE (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &atk);
    mestre_limpar_buffer();
    printf("Território DEFENSOR  (1 a %d): ", MAX_TERRITORIOS);
    scanf("%d", &def);
    mestre_limpar_buffer();

    mestre_simular_ataque(mapa, atk, def, cor_jogador);
}

// Verifica se a missão do jogador foi cumprida (const = só leitura do mapa)
int mestre_verificar_vitoria(const Territorio *mapa, int missao_id, const char *cor_jogador) {
    int conquistados = 0;
    int verdes_vivos = 0;

    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        if (strcmp(mapa[i].cor, cor_jogador) == 0) conquistados++;
        if (strcmp(mapa[i].cor, "Verde") == 0)     verdes_vivos++;
    }

    switch (missao_id) {
        case 0: return (verdes_vivos == 0);       // missão: destruir Verde
        case 1: return (conquistados >= 3);       // missão: conquistar 3 territórios
        default: return 0;
    }
}

// Ponto de entrada do Nível Mestre
void nivel_mestre() {
    srand((unsigned int) time(NULL));

    // --- Setup ---
    Territorio *mapa       = mestre_alocar_mapa();
    const char *cor_jogador = "Azul";             // jogador comanda o exército Azul
    int missao_id          = mestre_sortear_missao();

    mestre_inicializar_territorios(mapa);

    printf("\n🟣 ========== NÍVEL MESTRE ==========\n");
    printf("Você comanda o exército: %s\n", cor_jogador);
    mestre_exibir_missao(missao_id);

    // --- Game Loop ---
    int opcao;
    int vitoria = 0;
    do {
        mestre_exibir_mapa(mapa);
        mestre_exibir_missao(missao_id);
        mestre_exibir_menu();
        scanf("%d", &opcao);
        mestre_limpar_buffer();

        switch (opcao) {
            case 1:
                mestre_fase_ataque(mapa, cor_jogador);
                // Checa vitória após cada ataque
                vitoria = mestre_verificar_vitoria(mapa, missao_id, cor_jogador);
                if (vitoria) {
                    printf("\n🎉🏆 PARABÉNS! Você cumpriu sua missão! 🏆🎉\n");
                }
                break;
            case 2:
                if (mestre_verificar_vitoria(mapa, missao_id, cor_jogador)) {
                    printf("\n✅ Missão CUMPRIDA! Você venceu!\n");
                    vitoria = 1;
                } else {
                    printf("\n⏳ Missão ainda não concluída. Continue atacando!\n");
                }
                break;
            case 0:
                printf("\n👋 Saindo do jogo...\n");
                break;
            default:
                printf("❌ Opção inválida.\n");
        }

        // Pausa para o jogador ler os resultados
        if (opcao != 0 && !vitoria) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (opcao != 0 && !vitoria);

    // --- Limpeza ---
    mestre_liberar_memoria(mapa);
    printf("\n✅ Nível Mestre encerrado!\n");
}


// ============================================================================
// MENU INICIAL — escolhe qual nível jogar
// ============================================================================
int main() {
    int nivel;

    printf("╔══════════════════════════════════════╗\n");
    printf("║     🗺️  WAR ESTRUTURADO — MateCheck   ║\n");
    printf("╠══════════════════════════════════════╣\n");
    printf("║  [1] 🟢 Nível Novato                 ║\n");
    printf("║  [2] 🔵 Nível Aventureiro             ║\n");
    printf("║  [3] 🟣 Nível Mestre                  ║\n");
    printf("║  [0] Sair                            ║\n");
    printf("╚══════════════════════════════════════╝\n");
    printf("Escolha o nível: ");
    scanf("%d", &nivel);

    switch (nivel) {
        case 1: nivel_novato();      break;
        case 2: nivel_aventureiro(); break;
        case 3: nivel_mestre();      break;
        case 0: printf("Até logo!\n"); break;
        default: printf("❌ Opção inválida.\n");
    }

    return 0;
}
