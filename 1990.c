#include <stdio.h>

int main(void)
{
    /* =============================================================
       ELIRA - SALA DE 1990
       Tema: Privacidade, classificacao e uso responsavel de dados
       Mecanica: conectar arquivos a pastas da mesma cor

       Conteudos de C:
       - printf / scanf
       - variaveis e constantes
       - operadores
       - if / else
       - while
       - do-while
       - for
       ============================================================= */

    const int VIDAS_INICIAIS = 5;

    int vidas = VIDAS_INICIAIS;
    int jogarNovamente = 1;
    int opcaoMenu = 0;
    int leituraValida = 0;

    /* Estado da sala de 1990 */
    int arquivoAtual = 0;
    int pastaEscolhida = 0;
    int pastaCorreta = 0;
    int arquivoConectado = 0;
    int arquivosConectados = 0;

    /* Verificacao final do tema da sala */
    int respostaFinal = 0;
    int protocoloLiberado = 0;

    /* Recompensa */
    int possuiDisquete = 0;

    do
    {
        /* Reinicia a partida */
        vidas = VIDAS_INICIAIS;
        arquivosConectados = 0;
        protocoloLiberado = 0;
        possuiDisquete = 0;

        printf("\n====================================================\n");
        printf("                    E L I R A\n");
        printf("====================================================\n");
        printf("1 - Iniciar jornada\n");
        printf("2 - Sair\n");
        printf("Escolha uma opcao: ");

        leituraValida = scanf("%d", &opcaoMenu);

        while (leituraValida != 1 || opcaoMenu < 1 || opcaoMenu > 2)
        {
            if (leituraValida != 1)
            {
                scanf("%*s");
            }

            printf("Entrada invalida. Digite 1 para jogar ou 2 para sair: ");
            leituraValida = scanf("%d", &opcaoMenu);
        }

        if (opcaoMenu == 2)
        {
            jogarNovamente = 0;
        }
        else
        {
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
            printf("MESMA COR para restaurar a classificacao original.\n");

            printf("\nPASTAS DISPONIVEIS:\n");
            printf("1 - PUBLICOS       [AZUL]\n");
            printf("2 - PESSOAIS       [AMARELO]\n");
            printf("3 - SENSIVEIS      [VERMELHO]\n");
            printf("4 - ANONIMIZADOS   [VERDE]\n");

            printf("\nVidas: %d / %d\n", vidas, VIDAS_INICIAIS);

            /* =====================================================
               ETAPA 1 - REORGANIZACAO DOS ARQUIVOS
               O for percorre os quatro arquivos.
               ===================================================== */

            for (arquivoAtual = 1;
                 arquivoAtual <= 4 && vidas > 0;
                 arquivoAtual++)
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
                    leituraValida = scanf("%d", &pastaEscolhida);

                    /* Entrada invalida nao retira vida */
                    while (leituraValida != 1 ||
                           pastaEscolhida < 1 ||
                           pastaEscolhida > 4)
                    {
                        if (leituraValida != 1)
                        {
                            scanf("%*s");
                        }

                        printf("Entrada invalida. Digite um numero de 1 a 4: ");
                        leituraValida = scanf("%d", &pastaEscolhida);
                    }

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

                        printf("Progresso: %d / 4 arquivos conectados.\n",
                               arquivosConectados);
                    }
                    else
                    {
                        vidas--;

                        printf("\nCLASSIFICACAO INCORRETA!\n");
                        printf("A cor do arquivo nao corresponde a pasta escolhida.\n");
                        printf("Misturar classes de dados pode expor informacoes\n");
                        printf("ou permitir seu uso de forma inadequada.\n");

                        printf("\nUma vida foi perdida.\n");
                        printf("Vidas restantes: %d / %d\n",
                               vidas,
                               VIDAS_INICIAIS);

                        if (vidas > 0)
                        {
                            printf("Verifique o protocolo de cores e tente novamente.\n");
                        }
                    }
                }
            }

            /* =====================================================
               ETAPA 2 - DECISAO DE TREINAMENTO

               A classificacao por cores foi restaurada.
               Agora o jogador precisa demonstrar que entendeu
               quais dados podem alimentar a IA.
               ===================================================== */

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

                    printf("\nEscolha: ");
                    leituraValida = scanf("%d", &respostaFinal);

                    while (leituraValida != 1 ||
                           respostaFinal < 1 ||
                           respostaFinal > 4)
                    {
                        if (leituraValida != 1)
                        {
                            scanf("%*s");
                        }

                        printf("Entrada invalida. Digite um numero de 1 a 4: ");
                        leituraValida = scanf("%d", &respostaFinal);
                    }

                    if (respostaFinal == 1)
                    {
                        protocoloLiberado = 1;
                        possuiDisquete = 1;

                        printf("\nPROTOCOLO CORRETO!\n");
                        printf("Dados publicos e anonimizados podem ser usados\n");
                        printf("sem expor diretamente informacoes pessoais.\n");
                    }
                    else
                    {
                        vidas--;

                        printf("\nDECISAO INCORRETA!\n");
                        printf("Dados pessoais e sensiveis exigem protecao e nao\n");
                        printf("devem ser enviados livremente ao treinamento.\n");

                        printf("Uma vida foi perdida.\n");
                        printf("Vidas restantes: %d / %d\n",
                               vidas,
                               VIDAS_INICIAIS);
                    }
                }
            }

            /* =====================================================
               DESFECHO DA SALA
               ===================================================== */

            if (vidas == 0)
            {
                printf("\n====================================================\n");
                printf("                    GAME OVER\n");
                printf("====================================================\n");
                printf("A classificacao do banco de dados falhou.\n");
                printf("Informacoes pessoais ficaram expostas ao sistema.\n");
                printf("A viagem de Elira e interrompida.\n");
                printf("\nFINAL RUIM / APOCALIPTICO\n");
            }
            else if (possuiDisquete == 1)
            {
                printf("\n====================================================\n");
                printf("               SALA DE 1990 CONCLUIDA\n");
                printf("====================================================\n");
                printf("Elira restaurou o sistema de classificacao e\n");
                printf("impediu o uso indiscriminado de dados pessoais.\n\n");

                printf("Um compartimento se abre no terminal.\n");
                printf("Dentro dele existe um antigo disquete.\n\n");

                printf("RECOMPENSA: DISQUETE DE CORRECAO\n");
                printf("O programa armazenado nele permite localizar e\n");
                printf("remover informacoes comprometedoras dos bancos\n");
                printf("de dados utilizados pela IA.\n\n");

                printf("TEMA APRENDIDO:\n");
                printf("Privacidade, classificacao e uso responsavel de dados.\n");

                printf("\nVidas restantes: %d / %d\n",
                       vidas,
                       VIDAS_INICIAIS);
            }

            /* =====================================================
               GAME LOOP
               ===================================================== */

            printf("\nDeseja jogar novamente?\n");
            printf("1 - Sim\n");
            printf("2 - Nao\n");
            printf("Escolha: ");

            leituraValida = scanf("%d", &jogarNovamente);

            while (leituraValida != 1 ||
                   (jogarNovamente != 1 &&
                    jogarNovamente != 2))
            {
                if (leituraValida != 1)
                {
                    scanf("%*s");
                }

                printf("Entrada invalida. Digite 1 para sim ou 2 para nao: ");
                leituraValida = scanf("%d", &jogarNovamente);
            }

            if (jogarNovamente == 2)
            {
                jogarNovamente = 0;
            }
        }

    } while (jogarNovamente == 1);

    printf("\nObrigado por jogar ELIRA.\n");

    return 0;
}
