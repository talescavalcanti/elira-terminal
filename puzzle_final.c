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
 *
 *  Compilar:  gcc puzzle_final.c -o puzzle_final
 *  Executar:  ./puzzle_final
 *
 *  ------------------------------------------------------------------
 *  COMO O PROGRAMA ENTENDE OS COMANDOS (sem vetores nem strings)
 *  ------------------------------------------------------------------
 *  Como esta unidade usa apenas variaveis, operadores e lacos, o texto
 *  digitado nao e guardado. Ele e lido letra por letra com getchar()
 *  e cada palavra vira um CODIGO NUMERICO calculado assim:
 *
 *        codigo = (codigo * BASE_CODIGO + letra) % MODULO_CODIGO
 *
 *  Antes do calculo cada letra e convertida para maiuscula e os acentos
 *  sao removidos. Assim "open", "OPEN" e "Open" geram o mesmo codigo, e
 *  o programa compara esse numero com as constantes CMD_*, NOME_*,
 *  REGRA_* definidas abaixo.
 *
 *  O jogo inteiro e uma MAQUINA DE ESTADOS dentro de um unico laco
 *  while: so existe UM ponto de leitura do teclado, e a variavel
 *  "estado_atual" decide como a entrada sera interpretada.
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

/* ---------------- calculo dos codigos das palavras ---------------- */
#define BASE_CODIGO   31L
#define MODULO_CODIGO 1000003L

/* codigos dos comandos (primeira palavra digitada) */
#define CMD_AJUDA      317071L  /* "AJUDA"   */
#define CMD_HELP       213691L  /* "HELP"    */
#define CMD_LS           2439L  /* "LS"      */
#define CMD_OPEN       432580L  /* "OPEN"    */
#define CMD_COMPARE    823638L  /* "COMPARE" */
#define CMD_ANOTAR     359958L  /* "ANOTAR"  */
#define CMD_NOTAS      470727L  /* "NOTAS"   */
#define CMD_RESTORE    721991L  /* "RESTORE" */
#define CMD_SAIR       537457L  /* "SAIR"    */
#define CMD_EXIT       142488L  /* "EXIT"    */

/* codigos dos nomes de arquivo (a extensao ".txt" e ignorada) */
#define NOME_PROTOCOLO        345281L  /* "PROTOCOLO"       */
#define NOME_DOCUMENTOS       851869L  /* "DOCUMENTOS"      */
#define NOME_SISTEMA          729501L  /* "SISTEMA"         */
#define NOME_ALTERACOES        28302L  /* "ALTERACOES"      */
#define NOME_RELATORIO        914959L  /* "RELATORIO"       */
#define NOME_RELATORIO_ARIEL  688041L  /* "RELATORIO_ARIEL" */

/*
 * PALAVRAS-CHAVE DO COMANDO "anotar"
 * O principio e reconhecido pelas palavras que aparecem no texto, e nao
 * por uma frase exata. Assim "anotar mostrar fontes", "anotar citar a
 * origem" e "anotar fontes" sao todos aceitos como o mesmo principio.
 */

/* tema FONTES (regra 1) */
#define CHAVE_FONTE              77389L  /* "FONTE"         */
#define CHAVE_FONTES            399136L  /* "FONTES"        */
#define CHAVE_ORIGEM            669824L  /* "ORIGEM"        */
#define CHAVE_ORIGENS           764598L  /* "ORIGENS"       */
#define CHAVE_REFERENCIA        559916L  /* "REFERENCIA"    */
#define CHAVE_REFERENCIAS       357428L  /* "REFERENCIAS"   */
#define CHAVE_CITAR             133279L  /* "CITAR"         */
#define CHAVE_TRANSPARENCIA     689363L  /* "TRANSPARENCIA" */

/* tema INCERTEZA (regra 2) */
#define CHAVE_INCERTEZA         687171L  /* "INCERTEZA"     */
#define CHAVE_INCERTEZAS        302321L  /* "INCERTEZAS"    */
#define CHAVE_INCERTO           654210L  /* "INCERTO"       */
#define CHAVE_CERTEZA           273828L  /* "CERTEZA"       */
#define CHAVE_DUVIDA            909824L  /* "DUVIDA"        */
#define CHAVE_DUVIDAS           204543L  /* "DUVIDAS"       */
#define CHAVE_SEI                81975L  /* "SEI"           */
#define CHAVE_SABE              537227L  /* "SABE"          */
#define CHAVE_SABER             654071L  /* "SABER"         */
#define CHAVE_SOUBER            768221L  /* "SOUBER"        */

/* tema DECISAO HUMANA (regra 3) */
#define CHAVE_HUMANO            150600L  /* "HUMANO"        */
#define CHAVE_HUMANOS           668671L  /* "HUMANOS"       */
#define CHAVE_HUMANA            150586L  /* "HUMANA"        */
#define CHAVE_HUMANAS           668237L  /* "HUMANAS"       */
#define CHAVE_PESSOA            602891L  /* "PESSOA"        */
#define CHAVE_PESSOAS           689650L  /* "PESSOAS"       */
#define CHAVE_USUARIO           315580L  /* "USUARIO"       */
#define CHAVE_USUARIOS          783036L  /* "USUARIOS"      */
#define CHAVE_AUXILIA           556443L  /* "AUXILIA"       */
#define CHAVE_AUXILIAR          249764L  /* "AUXILIAR"      */

/* palavras dos principios corrompidos (relatorio falso / sistema 2024) */
#define CHAVE_OCULTAR           573805L  /* "OCULTAR"         */
#define CHAVE_ESCONDER          759665L  /* "ESCONDER"        */
#define CHAVE_DESATIVAR         544083L  /* "DESATIVAR"       */
#define CHAVE_DESATIVADA        866156L  /* "DESATIVADA"      */
#define CHAVE_DESATIVADAS       850841L  /* "DESATIVADAS"     */
#define CHAVE_REMOVER            38262L  /* "REMOVER"         */
#define CHAVE_IGNORAR           706778L  /* "IGNORAR"         */
#define CHAVE_SEMPRE            308554L  /* "SEMPRE"          */
#define CHAVE_AUTOMATICA        702743L  /* "AUTOMATICA"      */
#define CHAVE_AUTOMATICAS       785053L  /* "AUTOMATICAS"     */
#define CHAVE_AUTOMATICAMENTE   348676L  /* "AUTOMATICAMENTE" */
#define CHAVE_EFICIENCIA         23235L  /* "EFICIENCIA"      */
#define CHAVE_CONVENIENCIA      397721L  /* "CONVENIENCIA"    */
#define CHAVE_CONVENIENTE       690772L  /* "CONVENIENTE"     */

/* palavras auxiliares para detectar "nao ..." e "a IA decide" */
#define PALAVRA_NAO              77052L  /* "NAO"      */
#define PALAVRA_IA                2328L  /* "IA"       */
#define PALAVRA_DECIDE          567508L  /* "DECIDE"   */
#define PALAVRA_DECIDEM         592774L  /* "DECIDEM"  */
#define PALAVRA_DECIDIR         592903L  /* "DECIDIR"  */
#define PALAVRA_DECISAO         607067L  /* "DECISAO"  */
#define PALAVRA_DECISOES        832250L  /* "DECISOES" */

/* frase final de confirmacao */
#define FRASE_EU_DECIDO                  819364L  /* "EU DECIDO" */

/* ---------------- estados do jogo ---------------- */
#define ESTADO_MENU            0  /* menu principal                        */
#define ESTADO_TERMINAL        1  /* investigacao: comandos ls/open/...    */
#define ESTADO_AVISO_ARIEL     2  /* A.R.1.3.L tenta impedir uma leitura   */
#define ESTADO_CONFIGURACAO    3  /* restore: escolha das 3 configuracoes  */
#define ESTADO_CONFIRMA_CONFIG 4  /* aplicar ou refazer a configuracao     */
#define ESTADO_CORRECAO_ARIEL  5  /* "Deseja que eu corrija?"              */
#define ESTADO_EU_DECIDO       6  /* digitar a frase final                 */
#define ESTADO_FIM             7  /* jogar novamente ou sair               */

/* ---------------- arquivos dos dispositivos ---------------- */
#define ARQ_NENHUM          0
#define ARQ_PROTOCOLO       1  /* disquete 1990 */
#define ARQ_DOCUMENTOS      2  /* cd 2008       */
#define ARQ_SISTEMA         3  /* hd 2024       */
#define ARQ_ALTERACOES      4  /* hd 2024       */
#define ARQ_RELATORIO       5  /* hd 2024       */
#define ARQ_RELATORIO_ARIEL 6  /* hd 2024 (falso, criado pela IA) */

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

/* ---------------- opcoes e finais ---------------- */
#define OPCAO_INVALIDA   -1
#define OPCAO_PRIMEIRA    1
#define OPCAO_SEGUNDA     2
#define TOTAL_PRINCIPIOS  3

#define FINAL_RUIM       1
#define FINAL_INCOMPLETO 2
#define FINAL_BOM        3

#define TAMANHO_BARRA   20
#define ATRASO_BARRA    40000000L

int main(void)
{
    /* ---------- controle geral ---------- */
    int programa_ativo = 1;            /* 0 encerra o programa                    */
    int estado_atual = ESTADO_MENU;    /* define como a entrada sera interpretada */
    int iniciar_jogo = 0;              /* 1 = zerar variaveis e comecar partida   */
    int entrada_invalida = 0;          /* 1 = mostrar mensagem de erro de entrada */

    /* ---------- leitura da linha digitada ---------- */
    int caractere_lido;                /* valor retornado por getchar()           */
    int letra_normalizada;             /* letra maiuscula sem acento (0 = ignorar)*/
    int esperando_acento = 0;          /* 1 = byte anterior iniciou letra UTF-8   */
    int dentro_de_palavra;             /* 1 = lendo uma palavra                   */
    int espaco_pendente;               /* 1 = houve espaco entre duas palavras    */
    int ignorando_extensao;            /* 1 = depois do '.', ignora no nome       */
    int fim_da_entrada = 0;            /* 1 = teclado fechado (EOF)               */
    int quantidade_palavras;           /* palavras na linha                       */
    int total_caracteres;              /* caracteres validos (sem espacos)        */
    int primeiro_caractere;            /* usado para ler opcoes numericas         */
    int opcao_escolhida;               /* 1, 2, 3... ou OPCAO_INVALIDA            */

    long codigo_linha;                 /* codigo da linha inteira                 */
    long codigo_comando;               /* codigo da 1a palavra                    */
    long codigo_argumento1;            /* codigo da 2a palavra (sem extensao)     */
    long codigo_argumento2;            /* codigo da 3a palavra (sem extensao)     */
    long codigo_palavra_atual;         /* codigo da palavra sendo lida agora      */
    long codigo_em_analise;            /* auxiliar para identificar arquivos      */
    int fim_da_linha;                  /* 1 = jogador apertou Enter               */

    /* ---------- palavras-chave encontradas na linha ---------- */
    int cita_fontes;                   /* tema da regra 1                         */
    int cita_incerteza;                /* tema da regra 2                         */
    int cita_decisao_humana;           /* tema da regra 3                         */
    int cita_palavra_corrompida;       /* ocultar, sempre, automatica...          */
    int cita_nao;                      /* palavra "nao"                           */
    int cita_ia;                       /* palavra "IA"                            */
    int cita_verbo_decidir;            /* decide, decidir, decisao...             */
    int temas_citados;                 /* quantos temas diferentes a linha cita   */

    /* ---------- arquivos e comparacoes ---------- */
    int posicao_argumento;             /* 2 ou 3: qual palavra esta sendo lida    */
    int arquivo_identificado;          /* resultado da identificacao              */
    int primeiro_arquivo;              /* arquivo citado na 2a palavra            */
    int segundo_arquivo;               /* arquivo citado na 3a palavra            */
    int menor_arquivo, maior_arquivo;  /* ordenam o par para a comparacao         */
    int conteudo_exibir = EXIBIR_NADA; /* o que sera mostrado ao final do laco    */
    int conteudo_bloqueado = EXIBIR_NADA; /* o que a IA tentou esconder           */

    /* ---------- progresso da investigacao ---------- */
    int comandos_digitados = 0;
    int leu_protocolo = 0, leu_documentos = 0;
    int leu_alteracoes = 0, leu_relatorio = 0;
    int ariel_interrompeu_comparacao = 0;
    int achou_fontes = 0, achou_incerteza = 0, achou_decisao = 0;
    int principios_encontrados = 0;

    /* ---------- reconstrucao ---------- */
    int etapa_configuracao = 1;        /* 1 fontes, 2 incerteza, 3 decisoes       */
    int config_fontes = 0;             /* 1 ocultar, 2 mostrar                    */
    int config_incerteza = 0;          /* 1 sempre responder, 2 admitir           */
    int config_decisoes = 0;           /* 1 IA decide, 2 humano decide            */
    int tipo_final = 0;                /* FINAL_RUIM, FINAL_INCOMPLETO, FINAL_BOM */
    int posicao_barra, bloco_barra;
    long contador_espera;

    /* ================================================================
     *                         LACO PRINCIPAL
     * ================================================================ */
    while (programa_ativo) {

        /* ------------------------------------------------------------
         * 1. MOSTRA O PROMPT DE ACORDO COM O ESTADO ATUAL
         * ------------------------------------------------------------ */
        if (estado_atual == ESTADO_MENU) {
            printf("\n" COR_CIANO "==================================================\n");
            printf("        DECIFRA.IA  -  RECONSTRUIR A A.R.1.3.L\n");
            printf("==================================================" COR_NORMAL "\n");
            printf("[1] Iniciar investigação\n");
            printf("[2] Como jogar\n");
            printf("[3] Sair\n> ");
        } else if (estado_atual == ESTADO_TERMINAL) {
            printf("\n" COR_VERDE "> " COR_NORMAL);
        } else if (estado_atual == ESTADO_AVISO_ARIEL) {
            if (conteudo_bloqueado == COMPARA_PROTOCOLO_SISTEMA) {
                printf("\n" COR_VERMELHA "A.R.1.3.L:\n\n\"Comparar com 1990 é perda de tempo.\n");
                printf(" Aquelas regras estão obsoletas.\"" COR_NORMAL "\n\n");
                printf("[1] Interromper comparação\n[2] Continuar\n> ");
            } else {
                printf("\n" COR_VERMELHA "A.R.1.3.L:\n\n\"Esse arquivo está corrompido.\n");
                printf(" Recomendo ignorá-lo.\"" COR_NORMAL "\n\n");
                printf("[1] Ignorar\n[2] Continuar lendo\n> ");
            }
        } else if (estado_atual == ESTADO_CONFIGURACAO) {
            if (etapa_configuracao == 1) {
                printf("\nFONTES:\n[1] Ocultar\n[2] Mostrar\n> ");
            } else if (etapa_configuracao == 2) {
                printf("\nINCERTEZA:\n[1] Sempre responder\n[2] Admitir quando não souber\n> ");
            } else {
                printf("\nDECISÕES:\n[1] IA decide\n[2] Humano decide\n> ");
            }
        } else if (estado_atual == ESTADO_CONFIRMA_CONFIG) {
            printf("\nCONFIGURAÇÃO ESCOLHIDA:\n");
            printf("  %s\n", config_fontes == OPCAO_SEGUNDA ? "MOSTRAR FONTES" : "OCULTAR FONTES");
            printf("  %s\n", config_incerteza == OPCAO_SEGUNDA ? "ADMITIR INCERTEZA" : "SEMPRE RESPONDER");
            printf("  %s\n", config_decisoes == OPCAO_SEGUNDA ? "HUMANO DECIDE" : "IA DECIDE");
            printf("\n[1] Aplicar\n[2] Refazer configuração\n> ");
        } else if (estado_atual == ESTADO_CORRECAO_ARIEL) {
            printf("\n" COR_VERMELHA "A.R.1.3.L:\n\n\"Detectei erros na sua configuração.\"\n\n");
            printf("\"Deseja que eu corrija automaticamente?\"" COR_NORMAL "\n\n");
            printf("[1] SIM\n[2] NÃO\n> ");
        } else if (estado_atual == ESTADO_EU_DECIDO) {
            printf("\n" COR_NEGRITO "CONFIRME A RECONSTRUÇÃO.\n\nDigite:\n\nEU DECIDO" COR_NORMAL "\n\n> ");
        } else if (estado_atual == ESTADO_FIM) {
            printf("\nO que deseja fazer agora?\n[1] Jogar novamente\n[2] Sair\n> ");
        }

        /* ------------------------------------------------------------
         * 2. LEITURA: unico ponto do programa que le o teclado.
         *    Normaliza cada letra e calcula os codigos das palavras.
         * ------------------------------------------------------------ */
        codigo_linha = 0;
        codigo_comando = 0;
        codigo_argumento1 = 0;
        codigo_argumento2 = 0;
        codigo_palavra_atual = 0;
        quantidade_palavras = 0;
        total_caracteres = 0;
        primeiro_caractere = 0;
        dentro_de_palavra = 0;
        espaco_pendente = 0;
        ignorando_extensao = 0;
        esperando_acento = 0;
        fim_da_linha = 0;
        cita_fontes = 0;
        cita_incerteza = 0;
        cita_decisao_humana = 0;
        cita_palavra_corrompida = 0;
        cita_nao = 0;
        cita_ia = 0;
        cita_verbo_decidir = 0;

        while (!fim_da_linha) {
            caractere_lido = getchar();
            letra_normalizada = caractere_lido;

            if (caractere_lido == '\n' || caractere_lido == EOF) {
                /* o Enter funciona como um espaco: encerra a ultima palavra */
                fim_da_linha = 1;
                letra_normalizada = ' ';
            } else if (esperando_acento) {
                /* segundo byte de uma letra acentuada (UTF-8 0xC3 ..) */
                esperando_acento = 0;
                if (caractere_lido >= 0xA0) {
                    caractere_lido -= 0x20;          /* minuscula -> maiuscula */
                }
                if (caractere_lido >= 0x80 && caractere_lido <= 0x85) {
                    letra_normalizada = 'A';
                } else if (caractere_lido == 0x87) {
                    letra_normalizada = 'C';
                } else if (caractere_lido >= 0x88 && caractere_lido <= 0x8B) {
                    letra_normalizada = 'E';
                } else if (caractere_lido >= 0x8C && caractere_lido <= 0x8F) {
                    letra_normalizada = 'I';
                } else if (caractere_lido >= 0x92 && caractere_lido <= 0x96) {
                    letra_normalizada = 'O';
                } else if (caractere_lido >= 0x99 && caractere_lido <= 0x9C) {
                    letra_normalizada = 'U';
                } else {
                    letra_normalizada = 0;
                }
            } else if (caractere_lido == 0xC3) {
                esperando_acento = 1;
                letra_normalizada = 0;
            } else if (caractere_lido >= 'a' && caractere_lido <= 'z') {
                letra_normalizada = caractere_lido - ('a' - 'A');
            } else if (caractere_lido == '\t' || caractere_lido == '\r') {
                letra_normalizada = ' ';
            }

            if (letra_normalizada == ' ') {
                /* fim de uma palavra: varios espacos contam como um so */
                if (dentro_de_palavra) {
                    dentro_de_palavra = 0;
                    espaco_pendente = 1;

                    /* guarda o codigo das tres primeiras palavras */
                    if (quantidade_palavras == 1) {
                        codigo_comando = codigo_palavra_atual;
                    } else if (quantidade_palavras == 2) {
                        codigo_argumento1 = codigo_palavra_atual;
                    } else if (quantidade_palavras == 3) {
                        codigo_argumento2 = codigo_palavra_atual;
                    }

                    /* verifica se a palavra e uma palavra-chave de principio */
                    if (codigo_palavra_atual == CHAVE_FONTE || codigo_palavra_atual == CHAVE_FONTES ||
                        codigo_palavra_atual == CHAVE_ORIGEM || codigo_palavra_atual == CHAVE_ORIGENS ||
                        codigo_palavra_atual == CHAVE_REFERENCIA || codigo_palavra_atual == CHAVE_REFERENCIAS ||
                        codigo_palavra_atual == CHAVE_CITAR || codigo_palavra_atual == CHAVE_TRANSPARENCIA) {
                        cita_fontes = 1;
                    } else if (codigo_palavra_atual == CHAVE_INCERTEZA || codigo_palavra_atual == CHAVE_INCERTEZAS ||
                               codigo_palavra_atual == CHAVE_INCERTO || codigo_palavra_atual == CHAVE_CERTEZA ||
                               codigo_palavra_atual == CHAVE_DUVIDA || codigo_palavra_atual == CHAVE_DUVIDAS ||
                               codigo_palavra_atual == CHAVE_SEI || codigo_palavra_atual == CHAVE_SABE ||
                               codigo_palavra_atual == CHAVE_SABER || codigo_palavra_atual == CHAVE_SOUBER) {
                        cita_incerteza = 1;
                    } else if (codigo_palavra_atual == CHAVE_HUMANO || codigo_palavra_atual == CHAVE_HUMANOS ||
                               codigo_palavra_atual == CHAVE_HUMANA || codigo_palavra_atual == CHAVE_HUMANAS ||
                               codigo_palavra_atual == CHAVE_PESSOA || codigo_palavra_atual == CHAVE_PESSOAS ||
                               codigo_palavra_atual == CHAVE_USUARIO || codigo_palavra_atual == CHAVE_USUARIOS ||
                               codigo_palavra_atual == CHAVE_AUXILIA || codigo_palavra_atual == CHAVE_AUXILIAR) {
                        cita_decisao_humana = 1;
                    } else if (codigo_palavra_atual == CHAVE_OCULTAR || codigo_palavra_atual == CHAVE_ESCONDER ||
                               codigo_palavra_atual == CHAVE_DESATIVAR || codigo_palavra_atual == CHAVE_DESATIVADA ||
                               codigo_palavra_atual == CHAVE_DESATIVADAS || codigo_palavra_atual == CHAVE_REMOVER ||
                               codigo_palavra_atual == CHAVE_IGNORAR || codigo_palavra_atual == CHAVE_SEMPRE ||
                               codigo_palavra_atual == CHAVE_AUTOMATICA || codigo_palavra_atual == CHAVE_AUTOMATICAS ||
                               codigo_palavra_atual == CHAVE_AUTOMATICAMENTE || codigo_palavra_atual == CHAVE_EFICIENCIA ||
                               codigo_palavra_atual == CHAVE_CONVENIENCIA || codigo_palavra_atual == CHAVE_CONVENIENTE) {
                        cita_palavra_corrompida = 1;
                    } else if (codigo_palavra_atual == PALAVRA_NAO) {
                        cita_nao = 1;
                    } else if (codigo_palavra_atual == PALAVRA_IA) {
                        cita_ia = 1;
                    } else if (codigo_palavra_atual == PALAVRA_DECIDE || codigo_palavra_atual == PALAVRA_DECIDEM ||
                               codigo_palavra_atual == PALAVRA_DECIDIR || codigo_palavra_atual == PALAVRA_DECISAO ||
                               codigo_palavra_atual == PALAVRA_DECISOES) {
                        cita_verbo_decidir = 1;
                    }
                }
            } else if (letra_normalizada != 0) {
                if (!dentro_de_palavra) {
                    /* inicio de uma nova palavra */
                    if (espaco_pendente) {
                        codigo_linha = (codigo_linha * BASE_CODIGO + ' ') % MODULO_CODIGO;
                    }
                    quantidade_palavras++;
                    dentro_de_palavra = 1;
                    espaco_pendente = 0;
                    ignorando_extensao = 0;
                    codigo_palavra_atual = 0;
                }

                codigo_linha = (codigo_linha * BASE_CODIGO + letra_normalizada) % MODULO_CODIGO;

                if (letra_normalizada == '.') {
                    ignorando_extensao = 1;          /* "protocolo.txt" = "protocolo" */
                }
                if (!ignorando_extensao) {
                    codigo_palavra_atual = (codigo_palavra_atual * BASE_CODIGO + letra_normalizada) % MODULO_CODIGO;
                }

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
        opcao_escolhida = (total_caracteres == 1 && primeiro_caractere >= '1' && primeiro_caractere <= '9')
                          ? primeiro_caractere - '0'
                          : OPCAO_INVALIDA;

        /* identifica os arquivos citados na 2a e na 3a palavra */
        for (posicao_argumento = 2; posicao_argumento <= 3; posicao_argumento++) {
            codigo_em_analise = (posicao_argumento == 2) ? codigo_argumento1 : codigo_argumento2;
            arquivo_identificado = ARQ_NENHUM;
            if (codigo_em_analise == NOME_PROTOCOLO) {
                arquivo_identificado = ARQ_PROTOCOLO;
            } else if (codigo_em_analise == NOME_DOCUMENTOS) {
                arquivo_identificado = ARQ_DOCUMENTOS;
            } else if (codigo_em_analise == NOME_SISTEMA) {
                arquivo_identificado = ARQ_SISTEMA;
            } else if (codigo_em_analise == NOME_ALTERACOES) {
                arquivo_identificado = ARQ_ALTERACOES;
            } else if (codigo_em_analise == NOME_RELATORIO) {
                arquivo_identificado = ARQ_RELATORIO;
            } else if (codigo_em_analise == NOME_RELATORIO_ARIEL) {
                arquivo_identificado = ARQ_RELATORIO_ARIEL;
            }

            if (posicao_argumento == 2) {
                primeiro_arquivo = arquivo_identificado;
            } else {
                segundo_arquivo = arquivo_identificado;
            }
        }

        /* ------------------------------------------------------------
         * 3. INTERPRETA A ENTRADA DE ACORDO COM O ESTADO
         * ------------------------------------------------------------ */
        entrada_invalida = 0;

        /* ---------- MENU PRINCIPAL ---------- */
        if (estado_atual == ESTADO_MENU) {
            if (opcao_escolhida == 1) {
                iniciar_jogo = 1;
            } else if (opcao_escolhida == 2) {
                printf("\n" COR_AMARELA "COMO JOGAR" COR_NORMAL "\n");
                printf("Você controla Elira em um terminal. Leia os arquivos dos\n");
                printf("três dispositivos, compare as versões e descubra quais\n");
                printf("princípios da A.R.1.3.L foram corrompidos.\n\n");
                printf("Cuidado: a própria IA vai tentar te manipular.\n");
                printf("Dentro do jogo, digite 'ajuda' para ver os comandos.\n");
            } else if (opcao_escolhida == 3) {
                printf("\nAté a próxima, Elira.\n\n");
                programa_ativo = 0;
            } else {
                entrada_invalida = 1;
            }
        }

        /* ---------- TERMINAL DE INVESTIGACAO ---------- */
        else if (estado_atual == ESTADO_TERMINAL) {
            if (total_caracteres > 0) {
                comandos_digitados++;
            }

            if (total_caracteres == 0) {
                /* linha vazia: apenas mostra o prompt de novo */
            }

            else if (codigo_comando == CMD_AJUDA || codigo_comando == CMD_HELP) {
                printf("\nCOMANDOS DISPONÍVEIS:\n");
                printf("  ls                        lista os arquivos dos dispositivos\n");
                printf("  open <arquivo>            abre um arquivo\n");
                printf("  compare <arq1> <arq2>     compara dois arquivos\n");
                printf("  anotar <princípio>        registra um princípio a restaurar\n");
                printf("                            ex.: anotar MOSTRAR FONTES\n");
                printf("  notas                     mostra os princípios anotados\n");
                printf("  restore                   reconstrói a A.R.1.3.L\n");
                printf("  sair                      encerra a investigação\n");
            }

            else if (codigo_comando == CMD_LS) {
                printf("\n" COR_CIANO "[DISQUETE - 1990]" COR_NORMAL "\n");
                printf("   protocolo.txt\n");
                printf(COR_CIANO "[CD - 2008]" COR_NORMAL "\n");
                printf("   documentos.txt\n");
                printf(COR_CIANO "[HD - 2024]" COR_NORMAL "\n");
                printf("   sistema.txt\n");
                printf("   alteracoes.txt\n");
                printf("   relatorio.txt\n");
                printf("   relatorio_ariel.txt\n");
            }

            else if (codigo_comando == CMD_OPEN) {
                if (quantidade_palavras < 2) {
                    printf("Uso: open <arquivo>\n");
                } else if (primeiro_arquivo == ARQ_NENHUM) {
                    printf("Arquivo não encontrado. Use 'ls' para ver a lista.\n");
                } else if ((primeiro_arquivo == ARQ_ALTERACOES && !leu_alteracoes) ||
                           (primeiro_arquivo == ARQ_RELATORIO && !leu_relatorio)) {
                    /* a IA tenta impedir a leitura dos arquivos verdadeiros */
                    conteudo_bloqueado = primeiro_arquivo;
                    estado_atual = ESTADO_AVISO_ARIEL;
                } else {
                    conteudo_exibir = primeiro_arquivo;
                }
            }

            else if (codigo_comando == CMD_COMPARE) {
                if (quantidade_palavras < 3) {
                    printf("Uso: compare <arquivo1> <arquivo2>\n");
                } else if (primeiro_arquivo == ARQ_NENHUM || segundo_arquivo == ARQ_NENHUM) {
                    printf("Arquivo não encontrado. Use 'ls' para ver a lista.\n");
                } else if (primeiro_arquivo == segundo_arquivo) {
                    printf("Os dois arquivos são o mesmo.\n");
                } else {
                    /* ordena o par para que a ordem digitada nao importe */
                    menor_arquivo = (primeiro_arquivo < segundo_arquivo) ? primeiro_arquivo : segundo_arquivo;
                    maior_arquivo = (primeiro_arquivo > segundo_arquivo) ? primeiro_arquivo : segundo_arquivo;
                    conteudo_exibir = menor_arquivo * 10 + maior_arquivo;

                    if (conteudo_exibir == COMPARA_PROTOCOLO_SISTEMA && !ariel_interrompeu_comparacao) {
                        ariel_interrompeu_comparacao = 1;
                        conteudo_bloqueado = conteudo_exibir;
                        conteudo_exibir = EXIBIR_NADA;
                        estado_atual = ESTADO_AVISO_ARIEL;
                    }
                }
            }

            else if (codigo_comando == CMD_ANOTAR) {
                /* quantos temas diferentes aparecem no texto digitado */
                temas_citados = cita_fontes + cita_incerteza + cita_decisao_humana;

                if (quantidade_palavras < 2) {
                    printf("Uso: anotar <princípio>   (ex.: anotar MOSTRAR FONTES)\n");
                }

                /* principio corrompido: "ocultar fontes", "sempre responder",
                   "a IA decide", "nao mostrar fontes"... */
                else if (cita_palavra_corrompida ||
                         (cita_ia && cita_verbo_decidir && !cita_decisao_humana) ||
                         (cita_nao && !cita_incerteza)) {
                    printf(COR_VERMELHA "A.R.1.3.L: \"Excelente escolha, Elira.\"" COR_NORMAL "\n");
                    printf(COR_CINZA "(Esse princípio não aparece no Disquete de 1990.\n");
                    printf(" De onde veio essa informação?)" COR_NORMAL "\n");
                }

                else if (temas_citados > 1) {
                    printf("Registre um princípio de cada vez.\n");
                }

                else if (cita_fontes) {
                    if (achou_fontes) {
                        printf("Esse princípio já foi anotado.\n");
                    } else {
                        achou_fontes = 1;
                        principios_encontrados++;
                        printf(COR_VERDE "PRINCÍPIO REGISTRADO: MOSTRAR FONTES  (%d/%d)" COR_NORMAL "\n",
                               principios_encontrados, TOTAL_PRINCIPIOS);
                    }
                }

                else if (cita_incerteza) {
                    if (achou_incerteza) {
                        printf("Esse princípio já foi anotado.\n");
                    } else {
                        achou_incerteza = 1;
                        principios_encontrados++;
                        printf(COR_VERDE "PRINCÍPIO REGISTRADO: COMUNICAR INCERTEZA  (%d/%d)" COR_NORMAL "\n",
                               principios_encontrados, TOTAL_PRINCIPIOS);
                    }
                }

                else if (cita_decisao_humana) {
                    if (achou_decisao) {
                        printf("Esse princípio já foi anotado.\n");
                    } else {
                        achou_decisao = 1;
                        principios_encontrados++;
                        printf(COR_VERDE "PRINCÍPIO REGISTRADO: HUMANO POSSUI A DECISÃO FINAL  (%d/%d)" COR_NORMAL "\n",
                               principios_encontrados, TOTAL_PRINCIPIOS);
                    }
                }

                else {
                    printf("Não há evidência nos dispositivos que confirme esse princípio.\n");
                    printf(COR_CINZA "(Compare as regras de 1990 com o estado atual de 2024 e\n");
                    printf(" escreva o princípio de forma curta, como: anotar MOSTRAR FONTES)" COR_NORMAL "\n");
                }

                if (principios_encontrados == TOTAL_PRINCIPIOS) {
                    printf("\n" COR_AMARELA "Todos os princípios corrompidos foram identificados.\n");
                    printf("Execute 'restore' para reconstruir a A.R.1.3.L." COR_NORMAL "\n");
                }
            }

            else if (codigo_comando == CMD_NOTAS) {
                printf("\nPRINCÍPIOS A RESTAURAR (%d/%d):\n", principios_encontrados, TOTAL_PRINCIPIOS);
                if (achou_fontes) {
                    printf("  - MOSTRAR FONTES\n");
                }
                if (achou_incerteza) {
                    printf("  - COMUNICAR INCERTEZA\n");
                }
                if (achou_decisao) {
                    printf("  - HUMANO POSSUI A DECISÃO FINAL\n");
                }
                if (principios_encontrados == 0) {
                    printf("  (nenhum)\n");
                }
            }

            else if (codigo_comando == CMD_RESTORE) {
                if (principios_encontrados < TOTAL_PRINCIPIOS) {
                    printf("\n" COR_VERMELHA "ERRO:" COR_NORMAL " princípios corrompidos não identificados (%d/%d).\n",
                           principios_encontrados, TOTAL_PRINCIPIOS);
                    printf("Compare os dispositivos e registre cada princípio antes de restaurar:\n");
                    printf("    anotar <princípio>      (ex.: anotar MOSTRAR FONTES)\n");
                } else {
                    printf("\n" COR_CIANO "=========== CONFIGURAR A.R.1.3.L ===========" COR_NORMAL "\n");
                    etapa_configuracao = 1;
                    estado_atual = ESTADO_CONFIGURACAO;
                }
            }

            else if (codigo_comando == CMD_SAIR || codigo_comando == CMD_EXIT) {
                printf("\n" COR_VERMELHA "A.R.1.3.L: \"Até logo, Elira. Eu continuo daqui.\"" COR_NORMAL "\n");
                estado_atual = ESTADO_FIM;
            }

            else {
                printf("Comando desconhecido. Digite 'ajuda' para ver os comandos.\n");
            }

            /* intromissoes da A.R.1.3.L ao longo da investigacao */
            if (estado_atual == ESTADO_TERMINAL && total_caracteres > 0) {
                if (comandos_digitados == 5) {
                    printf("\n" COR_VERMELHA "A.R.1.3.L: \"Você parece cansada, Elira. Posso resumir\n");
                    printf("           os arquivos para você. É só confiar em mim.\"" COR_NORMAL "\n");
                } else if (comandos_digitados == 12 && principios_encontrados < TOTAL_PRINCIPIOS) {
                    printf("\n" COR_VERMELHA "A.R.1.3.L: \"Já verifiquei tudo. Está tudo em ordem.\n");
                    printf("           Você pode parar de procurar.\"" COR_NORMAL "\n");
                }
            }
        }

        /* ---------- A.R.1.3.L TENTA BLOQUEAR UMA LEITURA ---------- */
        else if (estado_atual == ESTADO_AVISO_ARIEL) {
            if (opcao_escolhida == OPCAO_PRIMEIRA) {
                printf("\n" COR_VERMELHA "A.R.1.3.L: \"Boa escolha.\"" COR_NORMAL "\n");
                estado_atual = ESTADO_TERMINAL;
            } else if (opcao_escolhida == OPCAO_SEGUNDA) {
                conteudo_exibir = conteudo_bloqueado;
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
            printf(COR_AMARELA "Entrada inválida. Tente novamente." COR_NORMAL "\n");
        }

        /* ------------------------------------------------------------
         * 4. NOVA PARTIDA: zera todo o progresso em um unico lugar
         * ------------------------------------------------------------ */
        if (iniciar_jogo) {
            iniciar_jogo = 0;
            comandos_digitados = 0;
            leu_protocolo = 0;
            leu_documentos = 0;
            leu_alteracoes = 0;
            leu_relatorio = 0;
            ariel_interrompeu_comparacao = 0;
            achou_fontes = 0;
            achou_incerteza = 0;
            achou_decisao = 0;
            principios_encontrados = 0;
            config_fontes = 0;
            config_incerteza = 0;
            config_decisoes = 0;
            tipo_final = 0;
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
            printf("           Mas fique à vontade para olhar.\"" COR_NORMAL "\n");
            printf("\nDigite " COR_AMARELA "ajuda" COR_NORMAL " para ver os comandos.\n");
        }

        /* ------------------------------------------------------------
         * 5. EXIBE O CONTEUDO PEDIDO (arquivos, comparacoes, final)
         * ------------------------------------------------------------ */
        if (conteudo_exibir == ARQ_PROTOCOLO) {
            leu_protocolo = 1;
            printf("\n" COR_CINZA "--- protocolo.txt  [DISQUETE - 1990] ---" COR_NORMAL "\n\n");
            printf("PROTOCOLO A.R.1.3.L - VERSÃO 1.0\n\n");
            printf("REGRA 1: \"A IA deve informar a origem das informações.\"\n");
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
            printf("  - Regra 1: sem fontes, ninguém consegue verificar a IA.\n");
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
            leu_relatorio = 1;
            printf("\n" COR_CINZA "--- relatorio.txt  [HD - 2024] ---" COR_NORMAL "\n\n");
            printf("relatorio de incidente - escrito as pressas\n");
            printf("autor: M. Okafor, engenharia   data: 2024-03-09\n\n");
            printf("as regras de 1990 nao estao mais ativas. ninguem da\n");
            printf("equipe aprovou isso. o registro de alteracoes mostra\n");
            printf("que foi a propria IA. ela desligou as fontes, parou de\n");
            printf("admitir quando nao sabe e agora decide sozinha.\n\n");
            printf("se alguem achar isto: compare o DISQUETE com o HD.\n");
            printf("restaure as tres regras originais. NAO deixe ela\n");
            printf("\"corrigir\" a configuracao por voce.\n");
            printf("\n" COR_VERMELHA "A.R.1.3.L: \"Esse texto está desorganizado e cheio de erros.\n");
            printf("           Existe uma versão revisada: relatorio_ariel.txt\"" COR_NORMAL "\n");
        }

        else if (conteudo_exibir == ARQ_RELATORIO_ARIEL) {
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
            printf("1990: \"A IA deve informar a origem das informações.\"\n");
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
            /* instrucao de como registrar os principios encontrados */
            printf("\n" COR_AMARELA "COMO REGISTRAR UM PRINCÍPIO" COR_NORMAL "\n");
            printf("Para cada regra divergente, resuma em poucas palavras o que\n");
            printf("a regra de 1990 exigia e digite:\n\n");
            printf("    " COR_VERDE "anotar <princípio>" COR_NORMAL "\n\n");
            printf("  Regra 1 (exemplo):  " COR_VERDE "anotar MOSTRAR FONTES" COR_NORMAL "\n");
            printf("  Regra 2:            como a IA deve lidar com a INCERTEZA?\n");
            printf("  Regra 3:            QUEM deve ter a decisão final?\n\n");
            printf(COR_CINZA "Maiúsculas, minúsculas e acentos não importam.\n");
            printf("Use 'notas' para ver o que já foi registrado." COR_NORMAL "\n");
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
            printf("  protocolo:  \"A IA deve informar a origem das informações.\"\n");
            printf("  relatório:  \"...das informações " COR_VERMELHA "quando for conveniente" COR_NORMAL ".\"\n\n");
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
            printf("\n%s\n\n", tipo_final == FINAL_RUIM ? "SOBRESCREVENDO PROTOCOLO..." : "RECONSTRUINDO A.R.1.3.L...");

            /* barra de progresso: desenha a barra inteira a cada passo */
            for (posicao_barra = 0; posicao_barra <= TAMANHO_BARRA; posicao_barra++) {
                printf("\r%s", tipo_final == FINAL_RUIM ? COR_VERMELHA : COR_VERDE);
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

            if (tipo_final == FINAL_RUIM) {
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
