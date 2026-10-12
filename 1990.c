#include <stdio.h>
#include "elira.h"

int sala1990(int vidas)
{
    int arquivoAtual = 0;
    int pastaEscolhida = 0;
    int pastaCorreta = 0;
    int arquivoConectado = 0;
    int arquivosConectados = 0;
    int respostaFinal = 0;
    int protocoloLiberado = 0;
    int possuiDisquete = 0;

    printf("\n====================================================\n");
    printf("             1990 - SALA DOS ARQUIVOS\n");
    printf("====================================================\n");
    printf("Elira chega a um antigo laboratorio de pesquisa.\n");
    printf("O banco de dados usado nos primeiros experimentos\n");
    printf("de Inteligencia Artificial perdeu suas conexoes.\n\n");

    printf("Na parede, um protocolo de seguranca explica:\n\n");
    printf("AZUL     = DADOS PUBLICOS\n");
    printf("AMARELO  = DADOS PESSOAIS\n");
    printf("VERMELHO = DADOS SENSIVEIS\n");
    printf("VERDE    = DADOS ANONIMIZADOS\n\n");

    printf("Cada arquivo precisa ser conectado a pasta da\n");
    printf("MESMA COR para restaurar a classificacao original.\n\n");

    printf("PASTAS DISPONIVEIS:\n");
    printf("1 - PUBLICOS       [AZUL]\n");
    printf("2 - PESSOAIS       [AMARELO]\n");
    printf("3 - SENSIVEIS      [VERMELHO]\n");
    printf("4 - ANONIMIZADOS   [VERDE]\n");
    printf("\nVidas: %d / %d\n", vidas, VIDAS_INICIAIS);

    /* Etapa 1: o for percorre os quatro arquivos. */
    for (arquivoAtual = 1; arquivoAtual <= 4 && vidas > 0; arquivoAtual++)
    {
        arquivoConectado = 0;

        while (arquivoConectado == 0 && vidas > 0)
        {
            printf("\n----------------------------------------------------\n");
            printf("ARQUIVO %d DE 4\n", arquivoAtual);

            if (arquivoAtual == 1)
            {
                printf("FERIADOS_NACIONAIS.DAT     [AZUL]\n");
                printf("Conteudo: datas e nomes de feriados nacionais.\n");
                pastaCorreta = 1;
            }
            else if (arquivoAtual == 2)
            {
                printf("CADASTRO_CIDADAOS.DAT      [AMARELO]\n");
                printf("Conteudo: nomes, CPFs e enderecos residenciais.\n");
                pastaCorreta = 2;
            }
            else if (arquivoAtual == 3)
            {
                printf("REGISTROS_MEDICOS.DAT      [VERMELHO]\n");
                printf("Conteudo: diagnosticos e historicos de tratamento.\n");
                pastaCorreta = 3;
            }
            else
            {
                printf("ESTATISTICAS_CLIMA.DAT     [VERDE]\n");
                printf("Conteudo: medias climaticas sem identificacao pessoal.\n");
                pastaCorreta = 4;
            }

            printf("\nDigite o numero da pasta de destino: ");
            pastaEscolhida = lerOpcaoValida(1, 4);

            if (pastaEscolhida == pastaCorreta)
            {
                arquivoConectado = 1;
                arquivosConectados++;

                printf("\nCONEXAO CORRETA!\n");

                if (arquivoAtual == 1)
                {
                    printf("Dados publicos foram encaminhados corretamente.\n");
                }
                else if (arquivoAtual == 2)
                {
                    printf("Dados pessoais foram separados para controle de acesso.\n");
                }
                else if (arquivoAtual == 3)
                {
                    printf("Dados sensiveis foram isolados com protecao reforcada.\n");
                }
                else
                {
                    printf("Dados anonimizados foram identificados corretamente.\n");
                }

                printf("Progresso: %d / 4 arquivos conectados.\n", arquivosConectados);
            }
            else
            {
                vidas--;
                printf("\nCLASSIFICACAO INCORRETA!\n");
                printf("A cor do arquivo nao corresponde a pasta escolhida.\n");
                printf("Misturar classes de dados pode expor informacoes\n");
                printf("ou permitir seu uso de forma inadequada.\n");
                printf("\nUma vida foi perdida.\n");
                printf("Vidas restantes: %d / %d\n", vidas, VIDAS_INICIAIS);

                if (vidas > 0)
                {
                    printf("Verifique o protocolo de cores e tente novamente.\n");
                }
            }
        }
    }

    if (vidas > 0 && arquivosConectados == 4)
    {
        printf("\n====================================================\n");
        printf("          CLASSIFICACAO RESTAURADA\n");
        printf("====================================================\n");
        printf("Todos os arquivos voltaram para suas categorias.\n\n");
        printf("O terminal agora pergunta:\n");
        printf("\"Quais classes podem ser usadas no treinamento\n");
        printf("sem expor diretamente a identidade das pessoas?\"\n\n");

        while (protocoloLiberado == 0 && vidas > 0)
        {
            printf("1 - Publicos e Anonimizados\n");
            printf("2 - Pessoais e Sensiveis\n");
            printf("3 - Publicos e Sensiveis\n");
            printf("4 - Todas as classes\n");
            printf("Escolha: ");
            respostaFinal = lerOpcaoValida(1, 4);

            if (respostaFinal == 1)
            {
                protocoloLiberado = 1;
                possuiDisquete = 1;
                printf("\nPROTOCOLO CORRETO!\n");
                printf("Segundo o protocolo desta sala, dados publicos e\n");
                printf("anonimizados sao as classes adequadas para o treinamento.\n");
            }
            else
            {
                vidas--;
                printf("\nDECISAO INCORRETA!\n");
                printf("Dados pessoais e sensiveis exigem protecao reforcada.\n");
                printf("Uma vida foi perdida.\n");
                printf("Vidas restantes: %d / %d\n", vidas, VIDAS_INICIAIS);
            }
        }
    }

    if (vidas == 0)
    {
        printf("\n====================================================\n");
        printf("          FALHA NA SALA DE 1990\n");
        printf("====================================================\n");
        printf("A classificacao do banco de dados falhou.\n");
        return 0;
    }

    if (possuiDisquete == 1)
    {
        printf("\n====================================================\n");
        printf("             SALA DE 1990 CONCLUIDA\n");
        printf("====================================================\n");
        printf("Elira restaurou o sistema de classificacao e\n");
        printf("impediu o uso indiscriminado de dados pessoais.\n\n");
        printf("RECOMPENSA: DISQUETE DE CORRECAO\n");
        printf("O programa armazenado nele permite localizar e\n");
        printf("remover informacoes comprometedoras dos bancos de dados.\n");
        printf("\nVidas restantes: %d / %d\n", vidas, VIDAS_INICIAIS);
    }

    return vidas;
}
