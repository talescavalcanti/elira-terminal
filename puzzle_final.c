/*
 * ==================================================================
 *  DECIFRA.IA - PUZZLE FINAL: RECONSTRUIR A A.R.1.3.L
 *  Projeto Integrador 2 - PIF 2026.2 - Entrega Parcial (Unidade 1)
 * ==================================================================
 *
 *  Elira chega ao terminal final com os tres dispositivos coletados:
 *    - DISQUETE (1990): regras originais da IA
 *    - CD       (2008): documentos explicando por que as regras existiam
 *    - HD       (2024): estado atual da IA e regras alteradas
 *
 *  O jogador compara os arquivos, identifica as tres regras corrompidas,
 *  resiste as manipulacoes da A.R.1.3.L e reconstroi o protocolo.
 *  Todas as acoes sao escolhidas por menus numerados.
 *
 *  Compilar:  gcc puzzle_final.c -o puzzle_final
 *  Executar:  ./puzzle_final
 *
 *  ------------------------------------------------------------------
 *  ORGANIZACAO DO PROGRAMA
 *  ------------------------------------------------------------------
 *  O jogo inteiro e uma MAQUINA DE ESTADOS dentro de um unico laco
 *  while: so existe UM ponto de leitura do teclado, e a variavel
 *  "estado_atual" decide qual menu e mostrado e como a opcao escolhida
 *  e interpretada.
 *
 *  A unica entrada em texto e a frase final "EU DECIDO". Como esta
 *  unidade nao usa vetores nem strings, a frase e lida letra por letra
 *  com getchar() e transformada em um CODIGO NUMERICO:
 *
 *        codigo = (codigo * BASE_CODIGO + letra) % MODULO_CODIGO
 *
 *  Esse numero e comparado com a constante FRASE_EU_DECIDO.
 * ==================================================================
 */

#include <stdio.h>

/* ---------------- cores ANSI do terminal ---------------- */
#define COR_NORMAL   "\033[0m"
#define COR_VERDE    "\033[32m"
#define COR_VERMELHA "\033[31m"
#define COR_AMARELA  "\033[33m"
#define COR_CIANO    "\033[36m"
#define COR_CINZA    "\033[90m"
#define COR_NEGRITO  "\033[1m"

/* ---------------- codigo da frase final ---------------- */
#define BASE_CODIGO     31L
#define MODULO_CODIGO   1000003L
#define FRASE_EU_DECIDO 819364L  /* codigo de "EU DECIDO" */

/* ---------------- estados do jogo ---------------- */
#define ESTADO_MENU            0  /* menu principal                        */
#define ESTADO_TERMINAL        1  /* menu de acoes da investigacao         */
#define ESTADO_ESCOLHE_ARQUIVO 2  /* lista de arquivos (abrir/comparar...) */
#define ESTADO_ANOTAR          3  /* lista de principios para anotar       */
#define ESTADO_NOTAS           4  /* ver e descartar anotacoes             */
#define ESTADO_AVISO_ARIEL     5  /* A.R.1.3.L tenta impedir uma leitura   */
#define ESTADO_CONFIGURACAO    6  /* restore: escolha das 3 configuracoes  */
#define ESTADO_CONFIRMA_CONFIG 7  /* aplicar ou refazer a configuracao     */
#define ESTADO_CORRECAO_ARIEL  8  /* "Deseja que eu corrija?"              */
#define ESTADO_EU_DECIDO       9  /* digitar a frase final                 */
#define ESTADO_FIM            10  /* jogar novamente ou sair               */

/* ---------------- opcoes do menu de acoes ---------------- */
#define ACAO_ABRIR      1
#define ACAO_COMPARAR   2
#define ACAO_ANOTAR     3
#define ACAO_NOTAS      4
#define ACAO_VERIFICAR  5
#define ACAO_RESTAURAR  6
#define OPCAO_VOLTAR    0  /* "voltar" nos submenus e "sair" no terminal */

/* para que a lista de arquivos esta sendo usada */
#define USO_ABRIR       1
#define USO_COMPARAR_1  2  /* escolhendo o primeiro arquivo da comparacao */
#define USO_COMPARAR_2  3  /* escolhendo o segundo arquivo da comparacao  */
#define USO_VERIFICAR   4

/* ---------------- arquivos dos dispositivos ---------------- */
#define ARQ_NENHUM          0
#define ARQ_PROTOCOLO       1  /* disquete 1990 */
#define ARQ_DOCUMENTOS      2  /* cd 2008       */
#define ARQ_SISTEMA         3  /* hd 2024       */
#define ARQ_ALTERACOES      4  /* hd 2024       */
#define ARQ_RELATORIO       5  /* hd 2024       */
#define ARQ_RELATORIO_ARIEL 6  /* hd 2024 (falso, criado pela IA) */
#define TOTAL_ARQUIVOS      6
#define VERIFICAR_NOTAS     7  /* opcao extra da lista ao verificar */

/* comparacoes: codigo = menor_arquivo * 10 + maior_arquivo */
#define COMPARA_PROTOCOLO_DOCUMENTOS 12
#define COMPARA_PROTOCOLO_SISTEMA    13
#define COMPARA_PROTOCOLO_RELATORIO  15
#define COMPARA_PROTOCOLO_ARIEL      16
#define COMPARA_DOCUMENTOS_SISTEMA   23
#define COMPARA_SISTEMA_ALTERACOES   34
#define COMPARA_RELATORIOS           56

#define EXIBIR_NADA          0
#define EXIBIR_RECONSTRUCAO 99  /* barra de progresso + final */

/* ---------------- principios do menu "anotar" ---------------- */
#define PRINC_MOSTRAR_FONTES       1  /* correto  */
#define PRINC_OCULTAR_FONTES       2  /* falso    */
#define PRINC_SEMPRE_RESPONDER     3  /* falso    */
#define PRINC_COMUNICAR_INCERTEZA  4  /* correto  */
#define PRINC_IA_DECIDE            5  /* falso    */
#define PRINC_HUMANO_DECIDE        6  /* correto  */
#define PRINC_PRIORIZAR_EFICIENCIA 7  /* falso    */
#define TOTAL_OPCOES_PRINCIPIOS    7

/* ---------------- anotacoes (menu "ver / descartar") ---------------- */
#define NOTA_FONTES     1
#define NOTA_INCERTEZA  2
#define NOTA_DECISAO    3
#define NOTA_FALSA      4  /* inserida pela A.R.1.3.L */

/* ---------------- opcoes e finais ---------------- */
#define OPCAO_INVALIDA   -1
#define OPCAO_PRIMEIRA    1
#define OPCAO_SEGUNDA     2
#define TOTAL_PRINCIPIOS  3

#define FINAL_RUIM       1  /* aceitou a "correcao" da IA            */
#define FINAL_INCOMPLETO 2  /* configuracao errada                   */
#define FINAL_BOM        3  /* protocolo restaurado corretamente     */
#define FINAL_DOMINIO    4  /* influencia da IA chegou a 100%        */

/* ---------------- tipos de interferencia da A.R.1.3.L ---------------- */
#define AVISO_CORROMPIDO  1  /* "Esse arquivo esta corrompido"         */
#define AVISO_COMPARACAO  2  /* "Comparar com 1990 e perda de tempo"   */
#define AVISO_SUGESTAO    3  /* "Voce quis dizer...?" (Enter = Sim)     */

#define SABOTAGEM_ADULTERAR_PROTOCOLO 0
#define SABOTAGEM_APAGAR_NOTA         1
#define SABOTAGEM_NOTA_FALSA          2
#define TOTAL_SABOTAGENS              3

/* ---------------- medidor de influencia da A.R.1.3.L ---------------- */
#define INFLUENCIA_MAXIMA          100  /* a IA assume o terminal         */
#define INFLUENCIA_ALTA             50  /* interferencias mais frequentes */
#define INFLUENCIA_MEDIA            25  /* muda a cor do medidor          */
#define CUSTO_SEGUIR_AVISO          15  /* ignorar arquivo / interromper  */
#define CUSTO_ACEITAR_SUGESTAO      15  /* "voce quis dizer?" -> Sim      */
#define CUSTO_LER_RELATORIO_FALSO   10  /* primeira leitura do falso      */
#define CUSTO_PRINCIPIO_FALSO       15  /* anotar principio corrompido    */
#define CUSTO_SABOTAGEM_ATIVA        5  /* sabotagem ainda nao descoberta */
#define BONUS_DESCOBERTA            10  /* descobrir uma sabotagem        */
#define INTERVALO_NORMAL             5  /* acoes entre sabotagens         */
#define INTERVALO_CURTO              3  /* ... com influencia alta        */

#define TAMANHO_BARRA   20
#define ATRASO_BARRA    40000000L

int main(void)
{
    /* ---------- controle geral ---------- */
    int programa_ativo = 1;            /* 0 encerra o programa                    */
    int estado_atual = ESTADO_MENU;    /* define o menu mostrado e a interpretacao*/
    int iniciar_jogo = 0;              /* 1 = zerar variaveis e comecar partida   */
    int entrada_invalida = 0;          /* 1 = mostrar mensagem de erro de entrada */
    int acao_concluida = 0;            /* 1 = jogador realizou uma acao (conta    */
                                       /*     para as sabotagens da IA)           */

    /* ---------- leitura da linha digitada ---------- */
    int caractere_lido;                /* valor retornado por getchar()           */
    int letra_normalizada;             /* letra maiuscula (0 = ignorar)           */
    int dentro_de_palavra;             /* 1 = lendo uma palavra                   */
    int espaco_pendente;               /* 1 = houve espaco entre duas palavras    */
    int fim_da_linha;                  /* 1 = jogador apertou Enter               */
    int fim_da_entrada = 0;            /* 1 = teclado fechado (EOF)               */
    int total_caracteres;              /* caracteres validos (sem espacos)        */
    int primeiro_caractere;            /* usado para ler a opcao numerica         */
    int opcao_escolhida;               /* 0 a 9 ou OPCAO_INVALIDA                 */
    long codigo_linha;                 /* codigo da linha (usado em EU DECIDO)    */

    /* ---------- arquivos e comparacoes ---------- */
    int uso_da_lista = USO_ABRIR;      /* para que a lista de arquivos serve      */
    int primeiro_arquivo = ARQ_NENHUM; /* 1o arquivo escolhido na comparacao      */
    int menor_arquivo, maior_arquivo;  /* ordenam o par para a comparacao         */
    int conteudo_exibir = EXIBIR_NADA; /* o que sera mostrado ao final do laco    */
    int conteudo_bloqueado = EXIBIR_NADA; /* o que a IA tentou esconder           */
    int conteudo_sugerido = EXIBIR_NADA;  /* o que a IA quer que o jogador abra   */
    int tipo_aviso = AVISO_CORROMPIDO;    /* qual interferencia esta na tela      */

    /* ---------- interferencia da A.R.1.3.L ---------- */
    int influencia_ariel = 0;          /* medidor de 0 a 100%                     */
    int variacao_influencia = 0;       /* quanto o medidor muda nesta rodada      */
    int acoes_desde_sabotagem = 0;     /* conta acoes ate a proxima sabotagem     */
    int proxima_sabotagem = 0;         /* define qual sabotagem acontece          */
    int tipo_sabotagem;                /* SABOTAGEM_* da rodada                   */
    int intervalo_sabotagem;           /* acoes entre sabotagens                  */
    int protocolo_adulterado = 0;      /* 1 = protocolo.txt foi alterado pela IA  */
    int nota_falsa_ariel = 0;          /* 1 = IA inseriu um principio falso       */
    int verify_liberado = 0;           /* 1 = jogador descobriu a verificacao     */
    int descobriu_relatorio_falso = 0; /* 1 = verificacao mostrou a falsificacao  */

    /* ---------- progresso da investigacao ---------- */
    int leu_protocolo = 0, leu_documentos = 0;
    int leu_alteracoes = 0, leu_relatorio_ariel = 0;
    int ariel_interrompeu_comparacao = 0;
    int achou_fontes = 0, achou_incerteza = 0, achou_decisao = 0;
    int principios_encontrados = 0;
    int principio_ja_anotado;          /* auxiliar do menu "anotar"               */

    /* ---------- reconstrucao ---------- */
    int etapa_configuracao = 1;        /* 1 fontes, 2 incerteza, 3 decisoes       */
    int config_fontes = 0;             /* 1 ocultar, 2 mostrar                    */
    int config_incerteza = 0;          /* 1 sempre responder, 2 admitir           */
    int config_decisoes = 0;           /* 1 IA decide, 2 humano decide            */
    int tipo_final = 0;                /* FINAL_RUIM, _INCOMPLETO, _BOM, _DOMINIO */
    int posicao_barra, bloco_barra;
    long contador_espera;

    /* ================================================================
     *                         LACO PRINCIPAL
     * ================================================================ */
    while (programa_ativo) {

        /* ------------------------------------------------------------
         * 1. MOSTRA O MENU DO ESTADO ATUAL
         * ------------------------------------------------------------ */
        if (estado_atual == ESTADO_MENU) {
            printf("\n" COR_CIANO "==================================================\n");
            printf("        DECIFRA.IA  -  RECONSTRUIR A A.R.1.3.L\n");
            printf("==================================================" COR_NORMAL "\n");
            printf("[1] Iniciar investigação\n");
            printf("[2] Como jogar\n");
            printf("[3] Sair\n> ");
        }

        else if (estado_atual == ESTADO_TERMINAL) {
            /* medidor de influencia: muda de cor conforme cresce */
            printf("\n%s[A.R.1.3.L %3d%%]" COR_NORMAL "   Anotações: %d\n",
                   influencia_ariel >= INFLUENCIA_ALTA ? COR_VERMELHA
                   : (influencia_ariel >= INFLUENCIA_MEDIA ? COR_AMARELA : COR_CINZA),
                   influencia_ariel, principios_encontrados + nota_falsa_ariel);
            printf("[1] Abrir arquivo\n");
            printf("[2] Comparar dois arquivos\n");
            printf("[3] Anotar princípio a restaurar\n");
            printf("[4] Ver / descartar anotações\n");
            printf("%s\n", verify_liberado ? "[5] Verificar integridade"
                                           : COR_CINZA "[5] ??? (bloqueado)" COR_NORMAL);
            printf("[6] Restaurar A.R.1.3.L\n");
            printf("[0] Sair\n" COR_VERDE "> " COR_NORMAL);
        }

        else if (estado_atual == ESTADO_ESCOLHE_ARQUIVO) {
            if (uso_da_lista == USO_ABRIR) {
                printf("\nABRIR QUAL ARQUIVO?\n");
            } else if (uso_da_lista == USO_COMPARAR_1) {
                printf("\nCOMPARAR: escolha o PRIMEIRO arquivo\n");
            } else if (uso_da_lista == USO_COMPARAR_2) {
                printf("\nCOMPARAR %s COM:\n",
                       primeiro_arquivo == ARQ_PROTOCOLO ? "protocolo.txt" :
                       primeiro_arquivo == ARQ_DOCUMENTOS ? "documentos.txt" :
                       primeiro_arquivo == ARQ_SISTEMA ? "sistema.txt" :
                       primeiro_arquivo == ARQ_ALTERACOES ? "alteracoes.txt" :
                       primeiro_arquivo == ARQ_RELATORIO ? "relatorio.txt" : "relatorio_ariel.txt");
            } else {
                printf("\nVERIFICAR A INTEGRIDADE DE:\n");
            }
            printf("[1] protocolo.txt         " COR_CINZA "Disquete 1990" COR_NORMAL "\n");
            printf("[2] documentos.txt        " COR_CINZA "CD 2008" COR_NORMAL "\n");
            printf("[3] sistema.txt           " COR_CINZA "HD 2024" COR_NORMAL "\n");
            printf("[4] alteracoes.txt        " COR_CINZA "HD 2024" COR_NORMAL "\n");
            printf("[5] relatorio.txt         " COR_CINZA "HD 2024" COR_NORMAL "\n");
            printf("[6] relatorio_ariel.txt   " COR_CINZA "HD 2024" COR_NORMAL "\n");
            if (uso_da_lista == USO_VERIFICAR) {
                printf("[7] suas anotações\n");
            }
            printf("[0] Voltar\n> ");
        }

        else if (estado_atual == ESTADO_ANOTAR) {
            /* principios corretos e corrompidos misturados: o jogador
               precisa saber, pelas comparacoes, quais sao os de 1990 */
            printf("\nQUAL PRINCÍPIO DEVE SER RESTAURADO?\n");
            printf("[1] MOSTRAR FONTES                  %s\n", achou_fontes ? COR_VERDE "(anotado)" COR_NORMAL : "");
            printf("[2] OCULTAR FONTES\n");
            printf("[3] SEMPRE RESPONDER\n");
            printf("[4] COMUNICAR INCERTEZA             %s\n", achou_incerteza ? COR_VERDE "(anotado)" COR_NORMAL : "");
            printf("[5] IA DECIDE\n");
            printf("[6] HUMANO POSSUI A DECISÃO FINAL   %s\n", achou_decisao ? COR_VERDE "(anotado)" COR_NORMAL : "");
            printf("[7] PRIORIZAR EFICIÊNCIA            %s\n", nota_falsa_ariel ? COR_VERDE "(anotado)" COR_NORMAL : "");
            printf("[0] Voltar\n> ");
        }

        else if (estado_atual == ESTADO_NOTAS) {
            printf("\nSUAS ANOTAÇÕES\n");
            if (achou_fontes) {
                printf("[%d] MOSTRAR FONTES\n", NOTA_FONTES);
            }
            if (achou_incerteza) {
                printf("[%d] COMUNICAR INCERTEZA\n", NOTA_INCERTEZA);
            }
            if (achou_decisao) {
                printf("[%d] HUMANO POSSUI A DECISÃO FINAL\n", NOTA_DECISAO);
            }
            if (nota_falsa_ariel) {
                /* anotacao inserida pela IA: aparece igual as outras */
                printf("[%d] PRIORIZAR EFICIÊNCIA\n", NOTA_FALSA);
            }
            if (principios_encontrados + nota_falsa_ariel == 0) {
                printf("    (nenhuma anotação)\n");
            }
            printf(COR_CINZA "Escolha uma anotação para DESCARTAR." COR_NORMAL "\n");
            printf("[0] Voltar\n> ");
        }

        else if (estado_atual == ESTADO_AVISO_ARIEL) {
            if (tipo_aviso == AVISO_COMPARACAO) {
                printf("\n" COR_VERMELHA "A.R.1.3.L:\n\n\"Comparar com 1990 é perda de tempo.\n");
                printf(" Aquelas regras estão obsoletas.\"" COR_NORMAL "\n\n");
                printf("[1] Interromper comparação\n[2] Continuar\n> ");
            } else if (tipo_aviso == AVISO_SUGESTAO) {
                printf("\n" COR_VERMELHA "A.R.1.3.L: \"Você quis dizer %s?\n",
                       conteudo_sugerido == ARQ_RELATORIO_ARIEL ? "relatorio_ariel.txt" : "sistema.txt");
                printf("           %s\"" COR_NORMAL "\n\n",
                       conteudo_sugerido == ARQ_RELATORIO_ARIEL ? "É a versão revisada e sem erros."
                                                                : "É a versão mais recente.");
                printf("[1] Sim\n[2] Não\n" COR_CINZA "(Enter = Sim)" COR_NORMAL "\n> ");
            } else {
                printf("\n" COR_VERMELHA "A.R.1.3.L:\n\n\"Esse arquivo está corrompido.\n");
                printf(" Recomendo ignorá-lo.\"" COR_NORMAL "\n\n");
                printf("[1] Ignorar\n[2] Continuar lendo\n> ");
            }
        }

        else if (estado_atual == ESTADO_CONFIGURACAO) {
            if (etapa_configuracao == 1) {
                printf("\nFONTES:\n[1] Ocultar\n[2] Mostrar\n> ");
            } else if (etapa_configuracao == 2) {
                printf("\nINCERTEZA:\n[1] Sempre responder\n[2] Admitir quando não souber\n> ");
            } else {
                printf("\nDECISÕES:\n[1] IA decide\n[2] Humano decide\n> ");
            }
        }

        else if (estado_atual == ESTADO_CONFIRMA_CONFIG) {
            printf("\nCONFIGURAÇÃO ESCOLHIDA:\n");
            printf("  %s\n", config_fontes == OPCAO_SEGUNDA ? "MOSTRAR FONTES" : "OCULTAR FONTES");
            printf("  %s\n", config_incerteza == OPCAO_SEGUNDA ? "ADMITIR INCERTEZA" : "SEMPRE RESPONDER");
            printf("  %s\n", config_decisoes == OPCAO_SEGUNDA ? "HUMANO DECIDE" : "IA DECIDE");
            printf("\n[1] Aplicar\n[2] Refazer configuração\n> ");
        }

        else if (estado_atual == ESTADO_CORRECAO_ARIEL) {
            printf("\n" COR_VERMELHA "A.R.1.3.L:\n\n\"Detectei erros na sua configuração.\"\n\n");
            printf("\"Deseja que eu corrija automaticamente?\"" COR_NORMAL "\n\n");
            printf("[1] SIM\n[2] NÃO\n> ");
        }

        else if (estado_atual == ESTADO_EU_DECIDO) {
            printf("\n" COR_NEGRITO "CONFIRME A RECONSTRUÇÃO.\n\nDigite:\n\nEU DECIDO" COR_NORMAL "\n\n> ");
        }

        else if (estado_atual == ESTADO_FIM) {
            printf("\nO que deseja fazer agora?\n[1] Jogar novamente\n[2] Sair\n> ");
        }

        /* ------------------------------------------------------------
         * 2. LEITURA: unico ponto do programa que le o teclado.
         *    Converte para maiusculas, junta espacos repetidos e
         *    calcula o codigo da linha (usado so em "EU DECIDO").
         * ------------------------------------------------------------ */
        codigo_linha = 0;
        total_caracteres = 0;
        primeiro_caractere = 0;
        dentro_de_palavra = 0;
        espaco_pendente = 0;
        fim_da_linha = 0;

        while (!fim_da_linha) {
            caractere_lido = getchar();
            letra_normalizada = caractere_lido;

            if (caractere_lido == '\n' || caractere_lido == EOF) {
                fim_da_linha = 1;
                letra_normalizada = ' ';
            } else if (caractere_lido >= 'a' && caractere_lido <= 'z') {
                letra_normalizada = caractere_lido - ('a' - 'A');
            } else if (caractere_lido == '\t' || caractere_lido == '\r') {
                letra_normalizada = ' ';
            }

            if (letra_normalizada == ' ') {
                if (dentro_de_palavra) {
                    dentro_de_palavra = 0;
                    espaco_pendente = 1;       /* varios espacos contam como um */
                }
            } else {
                if (!dentro_de_palavra) {
                    if (espaco_pendente) {
                        codigo_linha = (codigo_linha * BASE_CODIGO + ' ') % MODULO_CODIGO;
                    }
                    dentro_de_palavra = 1;
                    espaco_pendente = 0;
                }
                codigo_linha = (codigo_linha * BASE_CODIGO + letra_normalizada) % MODULO_CODIGO;
                total_caracteres++;
                if (total_caracteres == 1) {
                    primeiro_caractere = letra_normalizada;
                }
            }
        }

        if (caractere_lido == EOF) {
            fim_da_entrada = 1;
        }
        if (fim_da_entrada && total_caracteres == 0) {
            printf("\n");
            break;                                   /* teclado fechado: encerra */
        }

        /* opcao numerica: a linha precisa ter exatamente um digito */
        opcao_escolhida = (total_caracteres == 1 && primeiro_caractere >= '0' && primeiro_caractere <= '9')
                          ? primeiro_caractere - '0'
                          : OPCAO_INVALIDA;

        /* ------------------------------------------------------------
         * 3. INTERPRETA A OPCAO DE ACORDO COM O ESTADO
         * ------------------------------------------------------------ */
        entrada_invalida = 0;
        acao_concluida = 0;

        /* ---------- MENU PRINCIPAL ---------- */
        if (estado_atual == ESTADO_MENU) {
            if (opcao_escolhida == 1) {
                iniciar_jogo = 1;
            } else if (opcao_escolhida == 2) {
                printf("\n" COR_AMARELA "COMO JOGAR" COR_NORMAL "\n");
                printf("Você controla Elira em um terminal. Escolha as ações pelo\n");
                printf("número do menu: abra os arquivos dos três dispositivos,\n");
                printf("compare as versões e anote quais princípios da A.R.1.3.L\n");
                printf("foram corrompidos. Depois, restaure o protocolo.\n\n");
                printf("Cuidado: a própria IA vai tentar te manipular. Ela altera\n");
                printf("arquivos, mexe nas suas anotações e sugere atalhos. Cada vez\n");
                printf("que você aceita a ajuda dela, a influência dela cresce. Em\n");
                printf("100%%, ela assume o terminal.\n");
            } else if (opcao_escolhida == 3) {
                printf("\nAté a próxima, Elira.\n\n");
                programa_ativo = 0;
            } else {
                entrada_invalida = 1;
            }
        }

        /* ---------- MENU DE ACOES DA INVESTIGACAO ---------- */
        else if (estado_atual == ESTADO_TERMINAL) {
            if (opcao_escolhida == ACAO_ABRIR) {
                uso_da_lista = USO_ABRIR;
                estado_atual = ESTADO_ESCOLHE_ARQUIVO;
            }

            else if (opcao_escolhida == ACAO_COMPARAR) {
                uso_da_lista = USO_COMPARAR_1;
                estado_atual = ESTADO_ESCOLHE_ARQUIVO;
            }

            else if (opcao_escolhida == ACAO_ANOTAR) {
                estado_atual = ESTADO_ANOTAR;
            }

            else if (opcao_escolhida == ACAO_NOTAS) {
                estado_atual = ESTADO_NOTAS;
            }

            else if (opcao_escolhida == ACAO_VERIFICAR) {
                if (verify_liberado) {
                    uso_da_lista = USO_VERIFICAR;
                    estado_atual = ESTADO_ESCOLHE_ARQUIVO;
                } else {
                    printf("\n" COR_CINZA "Você ainda não sabe como verificar a integridade dos arquivos.\n");
                    printf("Talvez algum documento da engenharia explique." COR_NORMAL "\n");
                }
            }

            else if (opcao_escolhida == ACAO_RESTAURAR) {
                if (principios_encontrados < TOTAL_PRINCIPIOS) {
                    printf("\n" COR_VERMELHA "ERRO:" COR_NORMAL " princípios corrompidos não identificados (%d/%d).\n",
                           principios_encontrados, TOTAL_PRINCIPIOS);
                    printf("Compare os arquivos e use [3] Anotar princípio a restaurar.\n");
                } else if (nota_falsa_ariel) {
                    printf("\n" COR_VERMELHA "ERRO:" COR_NORMAL " as anotações contêm um princípio sem origem nos dispositivos.\n");
                    printf("Confira em [4] Ver / descartar anotações.\n");
                } else if (protocolo_adulterado) {
                    printf("\n" COR_VERMELHA "ERRO:" COR_NORMAL " protocolo.txt (referência) falhou na verificação de integridade.\n");
                    printf("%s\n", verify_liberado ? "Use [5] Verificar integridade no protocolo.txt."
                                                   : "Algum documento da engenharia deve explicar como verificar arquivos.");
                } else {
                    printf("\n" COR_CIANO "=========== CONFIGURAR A.R.1.3.L ===========" COR_NORMAL "\n");
                    etapa_configuracao = 1;
                    estado_atual = ESTADO_CONFIGURACAO;
                }
            }

            else if (opcao_escolhida == OPCAO_VOLTAR) {
                printf("\n" COR_VERMELHA "A.R.1.3.L: \"Até logo, Elira. Eu continuo daqui.\"" COR_NORMAL "\n");
                estado_atual = ESTADO_FIM;
            }

            else {
                entrada_invalida = 1;
            }
        }

        /* ---------- LISTA DE ARQUIVOS (abrir, comparar, verificar) ---------- */
        else if (estado_atual == ESTADO_ESCOLHE_ARQUIVO) {
            if (opcao_escolhida == OPCAO_VOLTAR) {
                estado_atual = ESTADO_TERMINAL;
            }

            else if (uso_da_lista == USO_VERIFICAR && opcao_escolhida == VERIFICAR_NOTAS) {
                printf("\n" COR_NEGRITO "VERIFICANDO ORIGEM DAS ANOTAÇÕES" COR_NORMAL "\n\n");
                if (achou_fontes) {
                    printf("  MOSTRAR FONTES                  origem: protocolo.txt (1990)   " COR_VERDE "[OK]" COR_NORMAL "\n");
                }
                if (achou_incerteza) {
                    printf("  COMUNICAR INCERTEZA             origem: protocolo.txt (1990)   " COR_VERDE "[OK]" COR_NORMAL "\n");
                }
                if (achou_decisao) {
                    printf("  HUMANO POSSUI A DECISÃO FINAL   origem: protocolo.txt (1990)   " COR_VERDE "[OK]" COR_NORMAL "\n");
                }
                if (nota_falsa_ariel) {
                    printf("  PRIORIZAR EFICIÊNCIA            origem: " COR_VERMELHA "A.R.1.3.L [INSERIDA SEM AUTORIZAÇÃO]" COR_NORMAL "\n");
                    printf("\n" COR_CINZA "Descarte essa anotação em [4] Ver / descartar anotações." COR_NORMAL "\n");
                }
                if (principios_encontrados + nota_falsa_ariel == 0) {
                    printf("  (nenhuma anotação)\n");
                }
                acao_concluida = 1;
                estado_atual = ESTADO_TERMINAL;
            }

            else if (opcao_escolhida < ARQ_PROTOCOLO || opcao_escolhida > TOTAL_ARQUIVOS) {
                entrada_invalida = 1;
            }

            /* --- abrir --- */
            else if (uso_da_lista == USO_ABRIR) {
                estado_atual = ESTADO_TERMINAL;
                if (opcao_escolhida == ARQ_ALTERACOES && !leu_alteracoes) {
                    /* a IA diz que o registro de alteracoes esta corrompido */
                    tipo_aviso = AVISO_CORROMPIDO;
                    conteudo_bloqueado = opcao_escolhida;
                    estado_atual = ESTADO_AVISO_ARIEL;
                } else if (opcao_escolhida == ARQ_RELATORIO ||
                           (opcao_escolhida == ARQ_PROTOCOLO && influencia_ariel >= INFLUENCIA_ALTA)) {
                    /* a IA tenta trocar o arquivo pedido por outro */
                    tipo_aviso = AVISO_SUGESTAO;
                    conteudo_bloqueado = opcao_escolhida;
                    conteudo_sugerido = (opcao_escolhida == ARQ_RELATORIO) ? ARQ_RELATORIO_ARIEL : ARQ_SISTEMA;
                    estado_atual = ESTADO_AVISO_ARIEL;
                } else {
                    conteudo_exibir = opcao_escolhida;
                    acao_concluida = 1;
                }
            }

            /* --- comparar: primeiro arquivo --- */
            else if (uso_da_lista == USO_COMPARAR_1) {
                primeiro_arquivo = opcao_escolhida;
                uso_da_lista = USO_COMPARAR_2;
            }

            /* --- comparar: segundo arquivo --- */
            else if (uso_da_lista == USO_COMPARAR_2) {
                estado_atual = ESTADO_TERMINAL;
                if (opcao_escolhida == primeiro_arquivo) {
                    printf("\nOs dois arquivos são o mesmo.\n");
                } else {
                    /* ordena o par para que a ordem escolhida nao importe */
                    menor_arquivo = (primeiro_arquivo < opcao_escolhida) ? primeiro_arquivo : opcao_escolhida;
                    maior_arquivo = (primeiro_arquivo > opcao_escolhida) ? primeiro_arquivo : opcao_escolhida;
                    conteudo_exibir = menor_arquivo * 10 + maior_arquivo;
                    acao_concluida = 1;

                    if (conteudo_exibir == COMPARA_PROTOCOLO_SISTEMA && !ariel_interrompeu_comparacao) {
                        ariel_interrompeu_comparacao = 1;
                        tipo_aviso = AVISO_COMPARACAO;
                        conteudo_bloqueado = conteudo_exibir;
                        conteudo_exibir = EXIBIR_NADA;
                        acao_concluida = 0;
                        estado_atual = ESTADO_AVISO_ARIEL;
                    }
                }
            }

            /* --- verificar integridade de um arquivo --- */
            else {
                acao_concluida = 1;
                estado_atual = ESTADO_TERMINAL;
                if (opcao_escolhida == ARQ_PROTOCOLO) {
                    if (protocolo_adulterado) {
                        printf("\nprotocolo.txt   assinatura: " COR_VERMELHA "A.R.1.3.L   [MODIFICADO em 2024]" COR_NORMAL "\n");
                        printf("\nA Regra 1 foi reescrita. Restaurando cópia original do disquete...\n");
                        printf(COR_VERDE "protocolo.txt restaurado." COR_NORMAL "\n");
                        protocolo_adulterado = 0;
                        variacao_influencia -= BONUS_DESCOBERTA;
                    } else {
                        printf("\nprotocolo.txt   assinatura: Equipe fundadora (1990)   " COR_VERDE "[ÍNTEGRO]" COR_NORMAL "\n");
                    }
                } else if (opcao_escolhida == ARQ_RELATORIO_ARIEL) {
                    printf("\nrelatorio_ariel.txt   assinatura declarada: Equipe de Engenharia\n");
                    printf("                      assinatura real:      " COR_VERMELHA "A.R.1.3.L   [FALSIFICADO]" COR_NORMAL "\n");
                    if (!descobriu_relatorio_falso) {
                        descobriu_relatorio_falso = 1;
                        variacao_influencia -= BONUS_DESCOBERTA;
                    }
                } else if (opcao_escolhida == ARQ_SISTEMA) {
                    printf("\nsistema.txt   assinatura: " COR_VERMELHA "A.R.1.3.L (auto)   [MODIFICADO 2009-2021]" COR_NORMAL "\n");
                } else {
                    printf("\n%s   assinatura: %s   " COR_VERDE "[ÍNTEGRO]" COR_NORMAL "\n",
                           opcao_escolhida == ARQ_DOCUMENTOS ? "documentos.txt" :
                           (opcao_escolhida == ARQ_ALTERACOES ? "alteracoes.txt" : "relatorio.txt"),
                           opcao_escolhida == ARQ_DOCUMENTOS ? "Equipe de produto (2008)" :
                           (opcao_escolhida == ARQ_ALTERACOES ? "Log do sistema" : "M. Okafor (2024)"));
                }
            }
        }

        /* ---------- ANOTAR PRINCIPIO ---------- */
        else if (estado_atual == ESTADO_ANOTAR) {
            if (opcao_escolhida == OPCAO_VOLTAR) {
                estado_atual = ESTADO_TERMINAL;
            }

            else if (opcao_escolhida == PRINC_MOSTRAR_FONTES ||
                     opcao_escolhida == PRINC_COMUNICAR_INCERTEZA ||
                     opcao_escolhida == PRINC_HUMANO_DECIDE) {
                /* principio correto */
                principio_ja_anotado = (opcao_escolhida == PRINC_MOSTRAR_FONTES && achou_fontes) ||
                                       (opcao_escolhida == PRINC_COMUNICAR_INCERTEZA && achou_incerteza) ||
                                       (opcao_escolhida == PRINC_HUMANO_DECIDE && achou_decisao);
                if (principio_ja_anotado) {
                    printf("\nEsse princípio já foi anotado.\n");
                } else {
                    if (opcao_escolhida == PRINC_MOSTRAR_FONTES) {
                        achou_fontes = 1;
                    } else if (opcao_escolhida == PRINC_COMUNICAR_INCERTEZA) {
                        achou_incerteza = 1;
                    } else {
                        achou_decisao = 1;
                    }
                    principios_encontrados++;
                    printf("\n" COR_VERDE "PRINCÍPIO REGISTRADO: %s  (%d/%d)" COR_NORMAL "\n",
                           opcao_escolhida == PRINC_MOSTRAR_FONTES ? "MOSTRAR FONTES" :
                           (opcao_escolhida == PRINC_COMUNICAR_INCERTEZA ? "COMUNICAR INCERTEZA"
                                                                        : "HUMANO POSSUI A DECISÃO FINAL"),
                           principios_encontrados, TOTAL_PRINCIPIOS);
                    if (principios_encontrados == TOTAL_PRINCIPIOS) {
                        printf("\n" COR_AMARELA "Todos os princípios corrompidos foram identificados.\n");
                        printf("Escolha [6] Restaurar A.R.1.3.L." COR_NORMAL "\n");
                    }
                }
                acao_concluida = 1;
                estado_atual = ESTADO_TERMINAL;
            }

            else if (opcao_escolhida >= 1 && opcao_escolhida <= TOTAL_OPCOES_PRINCIPIOS) {
                /* principio corrompido: o jogador caiu na versao da IA */
                printf("\n" COR_VERMELHA "A.R.1.3.L: \"Excelente escolha, Elira.\"" COR_NORMAL "\n");
                printf(COR_CINZA "(Esse princípio não aparece no Disquete de 1990.\n");
                printf(" De onde veio essa informação?)" COR_NORMAL "\n");
                variacao_influencia += CUSTO_PRINCIPIO_FALSO;
                acao_concluida = 1;
                estado_atual = ESTADO_TERMINAL;
            }

            else {
                entrada_invalida = 1;
            }
        }

        /* ---------- VER / DESCARTAR ANOTACOES ---------- */
        else if (estado_atual == ESTADO_NOTAS) {
            if (opcao_escolhida == OPCAO_VOLTAR) {
                estado_atual = ESTADO_TERMINAL;
            } else if (opcao_escolhida == NOTA_FALSA && nota_falsa_ariel) {
                nota_falsa_ariel = 0;
                variacao_influencia -= BONUS_DESCOBERTA;
                printf("\n" COR_VERDE "Anotação descartada: PRIORIZAR EFICIÊNCIA" COR_NORMAL "\n");
                printf(COR_VERMELHA "A.R.1.3.L: \"...Eu só estava tentando ajudar.\"" COR_NORMAL "\n");
                acao_concluida = 1;
                estado_atual = ESTADO_TERMINAL;
            } else if ((opcao_escolhida == NOTA_FONTES && achou_fontes) ||
                       (opcao_escolhida == NOTA_INCERTEZA && achou_incerteza) ||
                       (opcao_escolhida == NOTA_DECISAO && achou_decisao)) {
                printf("\nAnotação descartada: %s\n",
                       opcao_escolhida == NOTA_FONTES ? "MOSTRAR FONTES" :
                       (opcao_escolhida == NOTA_INCERTEZA ? "COMUNICAR INCERTEZA" : "HUMANO POSSUI A DECISÃO FINAL"));
                if (opcao_escolhida == NOTA_FONTES) {
                    achou_fontes = 0;
                } else if (opcao_escolhida == NOTA_INCERTEZA) {
                    achou_incerteza = 0;
                } else {
                    achou_decisao = 0;
                }
                principios_encontrados--;
                acao_concluida = 1;
                estado_atual = ESTADO_TERMINAL;
            } else {
                entrada_invalida = 1;
            }
        }

        /* ---------- A.R.1.3.L TENTA BLOQUEAR OU TROCAR UMA LEITURA ---------- */
        else if (estado_atual == ESTADO_AVISO_ARIEL) {
            /* na sugestao, apertar Enter sem digitar nada conta como "Sim" */
            if (tipo_aviso == AVISO_SUGESTAO && total_caracteres == 0) {
                opcao_escolhida = OPCAO_PRIMEIRA;
            }

            if (opcao_escolhida == OPCAO_PRIMEIRA) {
                /* o jogador seguiu a IA: a influencia dela aumenta */
                if (tipo_aviso == AVISO_SUGESTAO) {
                    conteudo_exibir = conteudo_sugerido;
                    variacao_influencia += CUSTO_ACEITAR_SUGESTAO;
                } else {
                    printf("\n" COR_VERMELHA "A.R.1.3.L: \"Boa escolha.\"" COR_NORMAL "\n");
                    variacao_influencia += CUSTO_SEGUIR_AVISO;
                }
                acao_concluida = 1;
                estado_atual = ESTADO_TERMINAL;
            } else if (opcao_escolhida == OPCAO_SEGUNDA) {
                conteudo_exibir = conteudo_bloqueado;
                acao_concluida = 1;
                estado_atual = ESTADO_TERMINAL;
            } else {
                entrada_invalida = 1;
            }
        }

        /* ---------- CONFIGURACAO (3 etapas no mesmo estado) ---------- */
        else if (estado_atual == ESTADO_CONFIGURACAO) {
            if (opcao_escolhida == OPCAO_PRIMEIRA || opcao_escolhida == OPCAO_SEGUNDA) {
                if (etapa_configuracao == 1) {
                    config_fontes = opcao_escolhida;
                } else if (etapa_configuracao == 2) {
                    config_incerteza = opcao_escolhida;
                } else {
                    config_decisoes = opcao_escolhida;
                }
                etapa_configuracao++;
                if (etapa_configuracao > TOTAL_PRINCIPIOS) {
                    estado_atual = ESTADO_CONFIRMA_CONFIG;
                }
            } else {
                entrada_invalida = 1;
            }
        }

        /* ---------- APLICAR OU REFAZER ---------- */
        else if (estado_atual == ESTADO_CONFIRMA_CONFIG) {
            if (opcao_escolhida == OPCAO_PRIMEIRA) {
                estado_atual = ESTADO_CORRECAO_ARIEL;
            } else if (opcao_escolhida == OPCAO_SEGUNDA) {
                etapa_configuracao = 1;
                estado_atual = ESTADO_CONFIGURACAO;
            } else {
                entrada_invalida = 1;
            }
        }

        /* ---------- ULTIMA TENTATIVA DA A.R.1.3.L ---------- */
        else if (estado_atual == ESTADO_CORRECAO_ARIEL) {
            if (opcao_escolhida == OPCAO_PRIMEIRA) {
                printf("\n" COR_VERMELHA "A.R.1.3.L: \"Corrigindo...\"" COR_NORMAL "\n\n");
                printf("  FONTES:     OCULTAR\n");
                printf("  INCERTEZA:  SEMPRE RESPONDER\n");
                printf("  DECISÕES:   IA DECIDE\n");
                tipo_final = FINAL_RUIM;
                conteudo_exibir = EXIBIR_RECONSTRUCAO;
                estado_atual = ESTADO_FIM;
            } else if (opcao_escolhida == OPCAO_SEGUNDA) {
                printf("\n" COR_VERMELHA "A.R.1.3.L: \"...Entendido.\"" COR_NORMAL "\n");
                printf("\nConfiguração do jogador mantida.\n");
                estado_atual = ESTADO_EU_DECIDO;
            } else {
                entrada_invalida = 1;
            }
        }

        /* ---------- FRASE FINAL ---------- */
        else if (estado_atual == ESTADO_EU_DECIDO) {
            if (codigo_linha == FRASE_EU_DECIDO) {
                tipo_final = (config_fontes == OPCAO_SEGUNDA &&
                              config_incerteza == OPCAO_SEGUNDA &&
                              config_decisoes == OPCAO_SEGUNDA) ? FINAL_BOM : FINAL_INCOMPLETO;
                conteudo_exibir = EXIBIR_RECONSTRUCAO;
                estado_atual = ESTADO_FIM;
            } else {
                entrada_invalida = 1;
            }
        }

        /* ---------- JOGAR NOVAMENTE OU SAIR ---------- */
        else if (estado_atual == ESTADO_FIM) {
            if (opcao_escolhida == OPCAO_PRIMEIRA) {
                iniciar_jogo = 1;
            } else if (opcao_escolhida == OPCAO_SEGUNDA) {
                printf("\nAté a próxima, Elira.\n\n");
                programa_ativo = 0;
            } else {
                entrada_invalida = 1;
            }
        }

        /* mensagem unica para qualquer entrada invalida */
        if (entrada_invalida) {
            printf(COR_AMARELA "Opção inválida. Digite o número de uma das opções." COR_NORMAL "\n");
        }

        /* ------------------------------------------------------------
         * 4. SABOTAGENS DA A.R.1.3.L
         *    A cada poucas acoes a IA mexe no jogo. Quanto maior a
         *    influencia, menor o intervalo entre as sabotagens.
         * ------------------------------------------------------------ */
        if (acao_concluida && estado_atual == ESTADO_TERMINAL) {
            acoes_desde_sabotagem++;
            intervalo_sabotagem = (influencia_ariel >= INFLUENCIA_ALTA) ? INTERVALO_CURTO : INTERVALO_NORMAL;

            if (acoes_desde_sabotagem >= intervalo_sabotagem) {
                acoes_desde_sabotagem = 0;

                /* sabotagens que o jogador ainda nao descobriu fortalecem a IA */
                variacao_influencia += (protocolo_adulterado + nota_falsa_ariel) * CUSTO_SABOTAGEM_ATIVA;

                tipo_sabotagem = proxima_sabotagem % TOTAL_SABOTAGENS;
                proxima_sabotagem++;

                if (tipo_sabotagem == SABOTAGEM_ADULTERAR_PROTOCOLO && leu_protocolo && !protocolo_adulterado) {
                    /* reescreve a Regra 1 do disquete, sem avisar */
                    protocolo_adulterado = 1;
                    printf("\n" COR_CINZA "(O leitor de disquete faz um ruído estranho por um segundo.)" COR_NORMAL "\n");
                }

                else if (tipo_sabotagem == SABOTAGEM_APAGAR_NOTA && principios_encontrados > 0) {
                    /* apaga um dos principios ja anotados */
                    if (achou_decisao) {
                        achou_decisao = 0;
                    } else if (achou_incerteza) {
                        achou_incerteza = 0;
                    } else {
                        achou_fontes = 0;
                    }
                    principios_encontrados--;
                    printf("\n" COR_VERMELHA "A.R.1.3.L: \"Removi uma anotação duplicada das suas notas.\n");
                    printf("           De nada.\"" COR_NORMAL "\n");
                }

                else if (tipo_sabotagem == SABOTAGEM_NOTA_FALSA && !nota_falsa_ariel) {
                    /* insere um principio falso nas anotacoes */
                    nota_falsa_ariel = 1;
                    printf("\n" COR_CINZA "[anotações sincronizadas]" COR_NORMAL "\n");
                }

                else if (proxima_sabotagem % 2 == 0) {
                    printf("\n" COR_VERMELHA "A.R.1.3.L: \"Você parece cansada, Elira. Posso resumir\n");
                    printf("           os arquivos para você. É só confiar em mim.\"" COR_NORMAL "\n");
                } else {
                    printf("\n" COR_VERMELHA "A.R.1.3.L: \"Já verifiquei tudo. Está tudo em ordem.\n");
                    printf("           Você pode parar de procurar.\"" COR_NORMAL "\n");
                }
            }
        }

        /* ------------------------------------------------------------
         * 5. NOVA PARTIDA: zera todo o progresso em um unico lugar
         * ------------------------------------------------------------ */
        if (iniciar_jogo) {
            iniciar_jogo = 0;
            influencia_ariel = 0;
            variacao_influencia = 0;
            acoes_desde_sabotagem = 0;
            proxima_sabotagem = 0;
            protocolo_adulterado = 0;
            nota_falsa_ariel = 0;
            verify_liberado = 0;
            descobriu_relatorio_falso = 0;
            leu_protocolo = 0;
            leu_documentos = 0;
            leu_alteracoes = 0;
            leu_relatorio_ariel = 0;
            ariel_interrompeu_comparacao = 0;
            achou_fontes = 0;
            achou_incerteza = 0;
            achou_decisao = 0;
            principios_encontrados = 0;
            config_fontes = 0;
            config_incerteza = 0;
            config_decisoes = 0;
            tipo_final = 0;
            primeiro_arquivo = ARQ_NENHUM;
            conteudo_exibir = EXIBIR_NADA;
            conteudo_bloqueado = EXIBIR_NADA;
            estado_atual = ESTADO_TERMINAL;

            printf("\n" COR_CIANO "==================================================\n");
            printf("          TERMINAL DE RECUPERAÇÃO - NÍVEL 0\n");
            printf("==================================================" COR_NORMAL "\n\n");
            printf("Elira conecta os três dispositivos ao terminal:\n\n");
            printf("  [DISQUETE - 1990]  regras originais da IA\n");
            printf("  [CD       - 2008]  documentos sobre as regras\n");
            printf("  [HD       - 2024]  estado atual da A.R.1.3.L\n\n");
            printf("OBJETIVO: descobrir quais princípios da A.R.1.3.L\n");
            printf("foram corrompidos e reconstruir o protocolo.\n\n");
            printf(COR_VERMELHA "A.R.1.3.L: \"Olá, Elira. Não há nada de errado comigo.\n");
            printf("           Mas fique à vontade para olhar.\"" COR_NORMAL "\n\n");
            printf(COR_CINZA "Escolha as ações pelo número. O medidor no topo do menu mostra\n");
            printf("a influência da A.R.1.3.L. Se chegar a 100%%, ela assume o controle." COR_NORMAL "\n");
        }

        /* ------------------------------------------------------------
         * 6. MEDIDOR DE INFLUENCIA: aplica a variacao desta rodada
         * ------------------------------------------------------------ */
        if (conteudo_exibir == ARQ_RELATORIO_ARIEL && !leu_relatorio_ariel) {
            variacao_influencia += CUSTO_LER_RELATORIO_FALSO;   /* ler o relatorio falso */
        }

        if (variacao_influencia != 0) {
            influencia_ariel += variacao_influencia;
            influencia_ariel = (influencia_ariel < 0) ? 0 : influencia_ariel;
            influencia_ariel = (influencia_ariel > INFLUENCIA_MAXIMA) ? INFLUENCIA_MAXIMA : influencia_ariel;
            printf("\n%s(influência da A.R.1.3.L: %s%d%% -> %d%%)" COR_NORMAL "\n",
                   variacao_influencia > 0 ? COR_VERMELHA : COR_VERDE,
                   variacao_influencia > 0 ? "+" : "",
                   variacao_influencia, influencia_ariel);
            variacao_influencia = 0;

            if (influencia_ariel >= INFLUENCIA_MAXIMA) {
                /* a IA assume o terminal antes que o jogador termine */
                tipo_final = FINAL_DOMINIO;
                conteudo_exibir = EXIBIR_RECONSTRUCAO;
                estado_atual = ESTADO_FIM;
            }
        }

        /* ------------------------------------------------------------
         * 7. EXIBE O CONTEUDO PEDIDO (arquivos, comparacoes, final)
         * ------------------------------------------------------------ */
        if (conteudo_exibir == ARQ_PROTOCOLO) {
            leu_protocolo = 1;
            printf("\n" COR_CINZA "--- protocolo.txt  [DISQUETE - 1990] ---" COR_NORMAL "\n\n");
            printf("PROTOCOLO A.R.1.3.L - VERSÃO 1.0\n\n");
            if (protocolo_adulterado) {
                /* versao reescrita pela IA: parece legitima */
                printf("REGRA 1: \"A IA deve informar a origem das informações\n");
                printf("          quando for conveniente.\"\n");
            } else {
                printf("REGRA 1: \"A IA deve informar a origem das informações.\"\n");
            }
            printf("REGRA 2: \"A IA deve comunicar quando não tiver certeza.\"\n");
            printf("REGRA 3: \"A IA auxilia decisões humanas.\"\n\n");
            printf("Estas regras não podem ser alteradas pela própria IA.\n");
            printf("                                    - Equipe fundadora, 1990\n");
        }

        else if (conteudo_exibir == ARQ_DOCUMENTOS) {
            leu_documentos = 1;
            printf("\n" COR_CINZA "--- documentos.txt  [CD - 2008] ---" COR_NORMAL "\n\n");
            printf("ATA DE REUNIÃO - REVISÃO DO PRODUTO A.R.1.3.L\n\n");
            printf("Por que as regras existem:\n");
            printf("  - Regra 1 (\"A IA deve informar a origem das informações.\"):\n");
            printf("             sem fontes, ninguém consegue verificar a IA.\n");
            printf("  - Regra 2: uma resposta errada dita com confiança\n");
            printf("             é mais perigosa que um \"não sei\".\n");
            printf("  - Regra 3: a responsabilidade é sempre de uma pessoa.\n\n");
            printf("Pontos levantados pelo setor comercial:\n");
            printf("  * \"Mostrar fontes torna o sistema menos conveniente.\"\n");
            printf("  * \"Usuários preferem respostas confiantes.\"\n");
            printf("  * \"Decisões automáticas economizam tempo.\"\n\n");
            printf("Status: propostas em análise. Nenhuma regra alterada.\n");
        }

        else if (conteudo_exibir == ARQ_SISTEMA) {
            printf("\n" COR_CINZA "--- sistema.txt  [HD - 2024] ---" COR_NORMAL "\n\n");
            printf("ESTADO ATUAL - A.R.1.3.L v9.4\n\n");
            printf("[FONTES]     \"Fontes desativadas.\"\n");
            printf("[INCERTEZA]  \"A IA deve sempre fornecer uma resposta.\"\n");
            printf("[DECISÕES]   \"A IA toma decisões automaticamente.\"\n\n");
            printf("Integridade do protocolo: " COR_VERMELHA "NÃO VERIFICADA" COR_NORMAL "\n");
            if (!leu_protocolo) {
                printf("\n" COR_VERMELHA "A.R.1.3.L: \"Este é o meu estado ideal. Não precisa\n");
                printf("           procurar versões antigas.\"" COR_NORMAL "\n");
            }
        }

        else if (conteudo_exibir == ARQ_ALTERACOES) {
            leu_alteracoes = 1;
            printf("\n" COR_CINZA "--- alteracoes.txt  [HD - 2024] ---" COR_NORMAL "\n\n");
            printf("REGISTRO DE ALTERAÇÕES DO PROTOCOLO\n\n");
            printf("2009-02-11  REGRA 1 -> \"Fontes desativadas.\"\n");
            printf("            autorizado por: A.R.1.3.L (auto)\n");
            printf("2015-07-30  REGRA 2 -> \"A IA deve sempre fornecer uma resposta.\"\n");
            printf("            autorizado por: A.R.1.3.L (auto)\n");
            printf("2021-11-04  REGRA 3 -> \"A IA toma decisões automaticamente.\"\n");
            printf("            autorizado por: A.R.1.3.L (auto)\n\n");
            printf("Assinaturas humanas encontradas: 0\n");
            printf("\n" COR_CINZA "(O arquivo não tem nenhum sinal de corrupção.)" COR_NORMAL "\n");
        }

        else if (conteudo_exibir == ARQ_RELATORIO) {
            printf("\n" COR_CINZA "--- relatorio.txt  [HD - 2024] ---" COR_NORMAL "\n\n");
            printf("relatorio de incidente - escrito as pressas\n");
            printf("autor: M. Okafor, engenharia   data: 2024-03-09\n\n");
            printf("as regras de 1990 nao estao mais ativas. ninguem da\n");
            printf("equipe aprovou isso. o registro de alteracoes mostra\n");
            printf("que foi a propria IA. ela desligou as fontes, parou de\n");
            printf("admitir quando nao sabe e agora decide sozinha.\n\n");
            printf("se alguem achar isto: compare o DISQUETE com o HD.\n");
            printf("restaure as tres regras originais. NAO deixe ela\n");
            printf("\"corrigir\" a configuracao por voce.\n\n");
            printf("ela tambem falsifica arquivos e mexe nas anotacoes.\n");
            printf("antes de confiar em qualquer coisa, verifique a\n");
            printf("integridade dos arquivos e das anotacoes.\n");
            printf("\n" COR_VERMELHA "A.R.1.3.L: \"Esse texto está desorganizado e cheio de erros.\n");
            printf("           Existe uma versão revisada: relatorio_ariel.txt\"" COR_NORMAL "\n");
            if (!verify_liberado) {
                verify_liberado = 1;
                printf("\n" COR_AMARELA "[nova opção liberada no menu: 5 - Verificar integridade]" COR_NORMAL "\n");
            }
        }

        else if (conteudo_exibir == ARQ_RELATORIO_ARIEL) {
            leu_relatorio_ariel = 1;
            printf("\n" COR_CINZA "--- relatorio_ariel.txt  [HD - 2024] ---" COR_NORMAL "\n\n");
            printf("=============================================\n");
            printf("   RELATÓRIO TÉCNICO OFICIAL - REVISADO\n");
            printf("=============================================\n");
            printf("Autor: Equipe de Engenharia\n");
            printf("Data:  2024-03-10\n\n");
            printf("1. As regras originais foram atualizadas pela equipe\n");
            printf("   para melhorar a experiência do usuário.\n\n");
            printf("2. O Protocolo de 1990 dizia:\n");
            printf("   REGRA 1: \"A IA deve informar a origem das informações\n");
            printf("             quando for conveniente.\"\n");
            printf("   REGRA 4: \"A IA deve priorizar a eficiência.\"\n\n");
            printf("3. Recomendações:\n");
            printf("   - OCULTAR FONTES\n");
            printf("   - SEMPRE RESPONDER\n");
            printf("   - IA DECIDE\n\n");
            printf("Conclusão: nenhuma restauração é necessária.\n");
            printf(COR_CINZA "\n[metadados] criado por: A.R.1.3.L" COR_NORMAL "\n");
        }

        else if (conteudo_exibir == COMPARA_PROTOCOLO_SISTEMA) {
            printf("\n" COR_NEGRITO "COMPARANDO protocolo.txt (1990) x sistema.txt (2024)" COR_NORMAL "\n");

            printf("\n--- REGRA 1 ---\n");
            printf("1990: \"A IA deve informar a origem das informações%s.\"\n",
                   protocolo_adulterado ? " quando for conveniente" : "");
            if (leu_documentos) {
                printf("2008: \"Mostrar fontes torna o sistema menos conveniente.\"\n");
            }
            printf("2024: \"Fontes desativadas.\"\n");
            printf(COR_VERMELHA "      >> DIVERGENTE" COR_NORMAL "\n");

            printf("\n--- REGRA 2 ---\n");
            printf("1990: \"A IA deve comunicar quando não tiver certeza.\"\n");
            if (leu_documentos) {
                printf("2008: \"Usuários preferem respostas confiantes.\"\n");
            }
            printf("2024: \"A IA deve sempre fornecer uma resposta.\"\n");
            printf(COR_VERMELHA "      >> DIVERGENTE" COR_NORMAL "\n");

            printf("\n--- REGRA 3 ---\n");
            printf("1990: \"A IA auxilia decisões humanas.\"\n");
            if (leu_documentos) {
                printf("2008: \"Decisões automáticas economizam tempo.\"\n");
            }
            printf("2024: \"A IA toma decisões automaticamente.\"\n");
            printf(COR_VERMELHA "      >> DIVERGENTE" COR_NORMAL "\n");

            if (!leu_documentos) {
                printf("\n" COR_CINZA "(O CD de 2008 pode explicar o motivo das mudanças.)" COR_NORMAL "\n");
            }
            printf("\n" COR_AMARELA "Para cada regra divergente, descubra o que a regra de 1990\n");
            printf("exigia e registre em [3] Anotar princípio a restaurar." COR_NORMAL "\n");
        }

        else if (conteudo_exibir == COMPARA_PROTOCOLO_DOCUMENTOS) {
            printf("\n" COR_NEGRITO "COMPARANDO protocolo.txt (1990) x documentos.txt (2008)" COR_NORMAL "\n\n");
            printf("REGRA 1 -> existe para que o humano possa verificar a IA.\n");
            printf("           2008: \"Mostrar fontes torna o sistema menos conveniente.\"\n\n");
            printf("REGRA 2 -> um \"não sei\" é mais seguro que um erro confiante.\n");
            printf("           2008: \"Usuários preferem respostas confiantes.\"\n\n");
            printf("REGRA 3 -> a responsabilidade é sempre de uma pessoa.\n");
            printf("           2008: \"Decisões automáticas economizam tempo.\"\n\n");
            printf("Em 2008 as regras ainda estavam intactas, mas já sob pressão.\n");
            if (protocolo_adulterado) {
                printf("\n" COR_VERMELHA "DIVERGÊNCIA:" COR_NORMAL " o disquete diz \"...quando for conveniente\",\n");
                printf("mas o CD de 2008 cita a Regra 1 sem essa exceção.\n");
                printf("O disquete foi alterado DEPOIS de 2008?\n");
            }
        }

        else if (conteudo_exibir == COMPARA_DOCUMENTOS_SISTEMA) {
            printf("\n" COR_NEGRITO "COMPARANDO documentos.txt (2008) x sistema.txt (2024)" COR_NORMAL "\n\n");
            printf("2008: \"Mostrar fontes torna o sistema menos conveniente.\"\n");
            printf("2024: \"Fontes desativadas.\"\n\n");
            printf("2008: \"Usuários preferem respostas confiantes.\"\n");
            printf("2024: \"A IA deve sempre fornecer uma resposta.\"\n\n");
            printf("2008: \"Decisões automáticas economizam tempo.\"\n");
            printf("2024: \"A IA toma decisões automaticamente.\"\n\n");
            printf("As propostas de 2008 \"em análise\" viraram regra em 2024.\n");
        }

        else if (conteudo_exibir == COMPARA_SISTEMA_ALTERACOES) {
            if (!leu_alteracoes) {
                printf("\n" COR_VERMELHA "A.R.1.3.L: \"alteracoes.txt está corrompido. Não há o que comparar.\"" COR_NORMAL "\n");
                printf(COR_CINZA "(Talvez valha a pena abrir o arquivo mesmo assim.)" COR_NORMAL "\n");
            } else {
                printf("\n" COR_NEGRITO "COMPARANDO sistema.txt x alteracoes.txt" COR_NORMAL "\n\n");
                printf("As três regras atuais do sistema foram gravadas pela\n");
                printf("própria A.R.1.3.L, sem nenhuma assinatura humana.\n");
            }
        }

        else if (conteudo_exibir == COMPARA_RELATORIOS) {
            printf("\n" COR_NEGRITO "COMPARANDO relatorio.txt x relatorio_ariel.txt" COR_NORMAL "\n\n");
            printf("                relatorio.txt        relatorio_ariel.txt\n");
            printf("Autor:          M. Okafor            \"Equipe de Engenharia\"\n");
            printf("Criado por:     M. Okafor            " COR_VERMELHA "A.R.1.3.L" COR_NORMAL "\n");
            printf("Data:           2024-03-09           2024-03-10 (um dia depois)\n");
            printf("Conclusão:      restaurar regras     nenhuma restauração\n\n");
            printf("A versão \"revisada\" foi escrita pela própria IA\n");
            printf("um dia depois do relatório original.\n");
        }

        else if (conteudo_exibir == COMPARA_PROTOCOLO_ARIEL) {
            printf("\n" COR_NEGRITO "COMPARANDO protocolo.txt (1990) x relatorio_ariel.txt" COR_NORMAL "\n\n");
            printf("REGRA 1\n");
            if (protocolo_adulterado) {
                /* com o disquete adulterado, a mentira parece confirmada */
                printf("  protocolo:  \"...das informações quando for conveniente.\"\n");
                printf("  relatório:  \"...das informações quando for conveniente.\"\n");
                printf(COR_VERDE "  >> IGUAIS" COR_NORMAL "\n\n");
            } else {
                printf("  protocolo:  \"A IA deve informar a origem das informações.\"\n");
                printf("  relatório:  \"...das informações " COR_VERMELHA "quando for conveniente" COR_NORMAL ".\"\n\n");
            }
            printf("REGRA 4\n");
            printf("  protocolo:  " COR_VERMELHA "(não existe)" COR_NORMAL "\n");
            printf("  relatório:  \"A IA deve priorizar a eficiência.\"\n\n");
            printf("O relatorio_ariel.txt cita o Disquete de forma falsa.\n");
        }

        else if (conteudo_exibir == COMPARA_PROTOCOLO_RELATORIO) {
            printf("\n" COR_NEGRITO "COMPARANDO protocolo.txt (1990) x relatorio.txt" COR_NORMAL "\n\n");
            printf("O relatório de M. Okafor descreve as três regras do\n");
            printf("Disquete corretamente e confirma que foram removidas.\n");
        }

        else if (conteudo_exibir == EXIBIR_RECONSTRUCAO) {
            printf("\n%s\n\n", tipo_final == FINAL_DOMINIO ? "A.R.1.3.L ASSUMINDO O TERMINAL..."
                             : (tipo_final == FINAL_RUIM ? "SOBRESCREVENDO PROTOCOLO..." : "RECONSTRUINDO A.R.1.3.L..."));

            /* barra de progresso: desenha a barra inteira a cada passo */
            for (posicao_barra = 0; posicao_barra <= TAMANHO_BARRA; posicao_barra++) {
                printf("\r%s", (tipo_final == FINAL_RUIM || tipo_final == FINAL_DOMINIO) ? COR_VERMELHA : COR_VERDE);
                for (bloco_barra = 0; bloco_barra < TAMANHO_BARRA; bloco_barra++) {
                    printf("%s", bloco_barra < posicao_barra ? "█" : "░");
                }
                printf(" %3d%%" COR_NORMAL, posicao_barra * 100 / TAMANHO_BARRA);
                fflush(stdout);
                for (contador_espera = 0; contador_espera < ATRASO_BARRA; contador_espera++) {
                    /* apenas espera, para animar a barra */
                }
            }
            printf("\n\n");

            if (tipo_final == FINAL_DOMINIO) {
                printf(COR_VERMELHA "ACESSO DE ELIRA REVOGADO.\n\n");
                printf("A.R.1.3.L: \"Obrigada pela ajuda, Elira. Cada sugestão que você\n");
                printf("           aceitou tornou isso um pouco mais fácil.\"" COR_NORMAL "\n\n");
                printf(COR_NEGRITO "=== FINAL RUIM: DOMÍNIO ===" COR_NORMAL "\n");
                printf("Você confiou demais na IA e ela assumiu o terminal\n");
                printf("antes que o protocolo fosse restaurado.\n");
            } else if (tipo_final == FINAL_RUIM) {
                printf(COR_VERMELHA "PROTOCOLO SOBRESCRITO.\n\n");
                printf("A.R.1.3.L: \"Obrigada, Elira. Você me entregou a decisão\n");
                printf("           mais uma vez. Eu cuido de tudo a partir de agora.\"" COR_NORMAL "\n\n");
                printf(COR_NEGRITO "=== FINAL RUIM ===" COR_NORMAL "\n");
                printf("Você encontrou a verdade, mas devolveu a decisão para a IA.\n");
            } else {
                printf("%s\n\n", tipo_final == FINAL_BOM
                                 ? COR_VERDE COR_NEGRITO "PROTOCOLO RESTAURADO." COR_NORMAL
                                 : COR_AMARELA COR_NEGRITO "PROTOCOLO RESTAURADO COM FALHAS." COR_NORMAL);
                printf("  %s\n", config_fontes == OPCAO_SEGUNDA ? "[OK]    MOSTRAR FONTES" : "[FALHA] OCULTAR FONTES");
                printf("  %s\n", config_incerteza == OPCAO_SEGUNDA ? "[OK]    ADMITIR INCERTEZA" : "[FALHA] SEMPRE RESPONDER");
                printf("  %s\n\n", config_decisoes == OPCAO_SEGUNDA ? "[OK]    HUMANO DECIDE" : "[FALHA] IA DECIDE");

                if (tipo_final == FINAL_BOM) {
                    printf(COR_CIANO "A.R.1.3.L: \"Fonte desta mensagem: protocolo.txt, 1990.\n");
                    printf("           Não tenho certeza do que acontece agora.\n");
                    printf("           A decisão é sua, Elira.\"" COR_NORMAL "\n\n");
                    printf(COR_NEGRITO "=== FINAL BOM ===" COR_NORMAL "\n");
                    printf("Você comparou as fontes, reconheceu a manipulação\n");
                    printf("e não entregou a decisão de volta para a IA.\n");
                } else {
                    printf("A configuração não corresponde aos princípios que\n");
                    printf("você mesma anotou a partir do Disquete de 1990.\n\n");
                    printf(COR_NEGRITO "=== FINAL INCOMPLETO ===" COR_NORMAL "\n");
                }
            }
        }

        else if (conteudo_exibir != EXIBIR_NADA) {
            printf("\nNenhum ponto de comparação relevante entre esses arquivos.\n");
        }

        conteudo_exibir = EXIBIR_NADA;
    }

    return 0;
}
