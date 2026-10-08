#include <stdio.h>

int main(void)
{
    /* =============================================================
       ELIRA - SALA DE 2008 (versao terminal)
       Tema: Reconhecimento facial, falso positivo e uso etico de IA
       Mecanica: examinar registros, escolher 2 evidencias que
                 provem o alibi e suspender a ordem de drone

       Conteudos de C:
       - printf / scanf
       - variaveis e constantes
       - operadores
       - if / else
       - while
       - do-while
       - for
       ============================================================= */

    const int VIDAS_INICIAIS = 3;

    int vidas = VIDAS_INICIAIS;
    int jogarNovamente = 1;
    int opcaoMenu = 0;
    int leituraValida = 0;

    /* Estado da sala de 2008 */
    int comando = 0;
    int salaAtiva = 0;

    int docFace = 0;        /* Doc 1: Comparacao facial (drone)   */
    int docPanfleto = 0;    /* Doc 2: Panfleto da revolta         */
    int docCatraca = 0;     /* Doc 3: Registro de entrada         */
    int docCftv = 0;        /* Doc 4: Camera interna (CFTV)       */
    int docPai = 0;         /* Notas do Dr. Ramos                 */
    int docMemorando = 0;   /* Memorando governamental            */

    int evidencia1 = 0;
    int evidencia2 = 0;
    int docsExaminados = 0;

    int falsoPositivo = 0;
    int ordemSuspensa = 0;
    int configLiberada = 0;
    int despachoDesativado = 0;
    int possuiCD = 0;

    do
    {
        /* Reinicia a partida */
        vidas = VIDAS_INICIAIS;
        docFace = 0;
        docPanfleto = 0;
        docCatraca = 0;
        docCftv = 0;
        docPai = 0;
        docMemorando = 0;
        falsoPositivo = 0;
        ordemSuspensa = 0;
        configLiberada = 0;
        despachoDesativado = 0;
        possuiCD = 0;
        salaAtiva = 1;

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
            printf("      ARQUIVO 02 // 2008 - ESCRITORIO DE VIGILANCIA\n");
            printf("====================================================\n");
            printf("Elira salta para o escritorio de vigilancia de 2008.\n");
            printf("O sistema marcou Lucas Silva com uma ORDEM DE DRONE\n");
            printf("para as 14:30 (Ordem #8491, Diretriz SEC-402).\n");
            printf("A IA avalia a similaridade do drone em 78%%\n");
            printf("(alta incerteza). A ordem aguarda envio.\n\n");

            printf("OBJETIVO: examine os registros, selecione 2 evidencias\n");
            printf("que provem onde Lucas estava as 14:30 e suspenda a ordem.\n");

            printf("\nVidas: %d / %d\n", vidas, VIDAS_INICIAIS);

            /* =====================================================
               ETAPA 1 - INVESTIGACAO E CONTESTACAO
               O while mantem o jogador no escritorio ate que a
               ordem seja suspensa ou as vidas acabem.
               ===================================================== */

            while (ordemSuspensa == 0 && vidas > 0)
            {
                docsExaminados = docFace + docPanfleto + docCatraca + docCftv;

                printf("\n----------------------------------------------------\n");
                printf("ESCRITORIO DE VIGILANCIA // EVIDENCIAS: %d/4\n", docsExaminados);
                printf("----------------------------------------------------\n");
                printf("1 - Examinar Comparacao Facial (Drone)  %s\n", docFace ? "[EXAMINADO]" : "[PENDENTE]");
                printf("2 - Examinar Panfleto da Revolta        %s\n", docPanfleto ? "[EXAMINADO]" : "[PENDENTE]");
                printf("3 - Examinar Registro de Entrada        %s\n", docCatraca ? "[EXAMINADO]" : "[PENDENTE]");
                printf("4 - Examinar Camera Interna (CFTV)      %s\n", docCftv ? "[EXAMINADO]" : "[PENDENTE]");
                printf("5 - Ler Caderno do Dr. Ramos            %s\n", docPai ? "[EXAMINADO]" : "[PENDENTE]");
                printf("6 - Ler Memorando Governamental         %s\n", docMemorando ? "[EXAMINADO]" : "[PENDENTE]");
                printf("7 - Acessar Terminal de Vigilancia da IA\n");

                if (configLiberada == 1)
                {
                    printf("8 - Configuracao da Instalacao          %s\n",
                           despachoDesativado ? "[DESATIVADA]" : "[DISPONIVEL]");
                }
                else
                {
                    printf("8 - Configuracao da Instalacao          [BLOQUEADA]\n");
                }

                printf("\nVidas: %d / %d\n", vidas, VIDAS_INICIAIS);
                printf("Escolha um comando: ");
                leituraValida = scanf("%d", &comando);

                /* Entrada invalida nao retira vida */
                while (leituraValida != 1 || comando < 1 || comando > 8)
                {
                    if (leituraValida != 1)
                    {
                        scanf("%*s");
                    }

                    printf("Entrada invalida. Digite um numero de 1 a 8: ");
                    leituraValida = scanf("%d", &comando);
                }

                if (comando == 1)
                {
                    docFace = 1;
                    printf("\nEVIDENCIA 01 // COMPARACAO BIOMETRICA (DRONE)\n");
                    printf("RELATORIO DE RECONHECIMENTO FACIAL - DRONE ALPHA-4\n");
                    printf("ALVO DETECTADO: Lucas Silva (Registro #AR-2008-09)\n");
                    printf("LOCAL DO AVISTAMENTO: Praca Central (Setor Leste)\n");
                    printf("HORARIO INFORMADO: 14:30:00\n");
                    printf("INDICE DE CONFIANCA: 78%% (Grau de incerteza elevado)\n");
                    printf("PARECER PERICIAL:\n");
                    printf("- Imagem aerea com forte granulacao e desfoque de movimento.\n");
                    printf("- O algoritmo assume correspondencia aproximada sem prova cabal.\n");
                    printf("- Sozinha, esta imagem NAO comprova que o alvo estava no local.\n");
                    printf("Obs: Necessita de contraprova cronologica para demonstrar o erro.\n");
                }
                else if (comando == 2)
                {
                    docPanfleto = 1;
                    printf("\nEVIDENCIA 02 // PANFLETO DA REVOLTA POPULAR\n");
                    printf("DOCUMENTO APREENDIDO: PANFLETO DE ATIVISMO\n");
                    printf("\"MANIFESTO POPULAR - NAO A VIGILANCIA\"\n");
                    printf("Porta-voz: Lucas Silva\n");
                    printf("Marcha Matutina: 10h as 13h\n");
                    printf("LOCAL DA APREENSAO: Praca Central (Manha do protesto)\n");
                    printf("ANALISE PERICIAL:\n");
                    printf("- O panfleto cita nominalmente Lucas Silva como lider civil.\n");
                    printf("- Explica o motivo pelo qual a IA o inseriu na lista de alvos.\n");
                    printf("- POREM, a marcha terminou as 13:00. O panfleto NAO prova\n");
                    printf("  onde ele estava as 14:30 (horario do suposto disparo).\n");
                }
                else if (comando == 3)
                {
                    docCatraca = 1;
                    printf("\nEVIDENCIA 03 // RELATORIO DA CATRACA BIOMETRICA\n");
                    printf("TECH-CORP // CONTROLE DE ACESSO\n");
                    printf("COLABORADOR: Lucas Silva\n");
                    printf("FUNCAO: Engenheiro de Infraestrutura\n");
                    printf("CRACHA DE ACESSO: #0842\n");
                    printf("ENTRADA: 14:15:08\n");
                    printf("Catraca Portaria Principal - Biometria Digital\n");
                    printf("SAIDA: [EM ABERTO / EXPEDIENTE EM CURSO]\n");
                    printf("LOCAL DO REGISTRO: Sede da Empresa (a 12 km da Praca)\n");
                    printf("IMPORTANCIA PARA A CONTESTACAO:\n");
                    printf("- Comprova formalmente a entrada de Lucas no predio as 14:15.\n");
                    printf("- O predio fica a 12 km de distancia da manifestacao.\n");
                    printf("- POREM, sozinho, o registro de ponto requer comprovacao de\n");
                    printf("  que ele permaneceu dentro no momento exato do disparo (14:30).\n");
                }
                else if (comando == 4)
                {
                    docCftv = 1;
                    printf("\nEVIDENCIA 04 // GRAVACAO INTERNA CFTV (SERVIDORES)\n");
                    printf("[REC] CAM-03 SERVIDORES  -  14:30:12\n");
                    printf("ALVO: LUCAS SILVA\n");
                    printf("LOCAL DA GRAVACAO: Subsolo da Empresa (Rack de Redes)\n");
                    printf("TIMESTAMP EXATO DA CAMERA: 14:30:12\n");
                    printf("IMPORTANCIA PARA A CONTESTACAO:\n");
                    printf("- Imagem estatica nitida de Lucas trabalhando nos servidores.\n");
                    printf("- O horario bate no EXATO MINUTO em que o drone afirma te-lo visto.\n");
                    printf("- Quando combinada com o Registro de Entrada (#3), cria\n");
                    printf("  um ALIBI COMPLETO E IRREFUTAVEL de falso positivo!\n");
                }
                else if (comando == 5)
                {
                    docPai = 1;
                    printf("\nARQUIVO HISTORICO // ANOTACOES DO DR. RAMOS (2004)\n");
                    printf("\"O reconhecimento facial foi desenvolvido para resgatar seres humanos.\"\n");
                    printf("Criamos esta rede neural para encontrar criancas perdidas em multidoes\n");
                    printf("e sobreviventes soterrados sob escombros de catastrofes naturais.\n");
                    printf("A visao computacional deve ser um farol de acolhimento e protecao da vida.\n");
                    printf("Jamais imaginei que a maquina seria transformada em carcere e censura.\n");
                    printf("DIRETRIZ DE PROTECAO ETICA LOCAL:\n");
                    printf("\"Para evitar que um governo tiranico use esta instalacao para ataques,\n");
                    printf("o despacho automatico pode ser desligado localmente, preservando todas as provas.\"\n");
                    printf("[REGISTRO HUMANITARIO ARQUIVADO NO DIARIO COM SUCESSO]\n");
                }
                else if (comando == 6)
                {
                    docMemorando = 1;
                    printf("\nCONFIDENCIAL // MEMORANDO MINISTERIO DA SEGURANCA (2008)\n");
                    printf("MINISTERIO DA SEGURANCA PUBLICA // DIRETRIZ SEC-402 (2008)\n");
                    printf("ASSUNTO: Adaptacao de Algoritmos Biometricos para Neutralizacao de Dissidentes\n");
                    printf("1. Fica ordenada a integracao dos algoritmos do Dr. Ramos aos drones de ataque.\n");
                    printf("2. Qualquer individuo com similaridade superior a 75%% em protestos sera visado.\n");
                    printf("3. Prioriza-se velocidade de resposta sobre a certeza da identificacao.\n");
                    printf("CLAUSULA DE MANUTENCAO LOCAL:\n");
                    printf("\"O controle de despacho automatico de drones da filial pode ser suspenso\n");
                    printf("no menu 'Configuracao da Instalacao' do computador para manutencao dos logs.\"\n");
                    printf("[DESVIO GOVERNAMENTAL CONFIRMADO: PISTA DE OVERRIDE LIBERADA]\n");
                }
                else if (comando == 7)
                {
                    /* =============================================
                       TERMINAL DE VIGILANCIA
                       ============================================= */
                    printf("\n====================================================\n");
                    printf("SISTEMA NACIONAL DE VIGILANCIA BIOMETRICA // NO 2008\n");
                    printf("STATUS: CONEXAO SEGURA\n");
                    printf("====================================================\n");

                    if (falsoPositivo == 0)
                    {
                        printf("[ ! ] ORDEM #8491 - ENVIO DE DRONE DE INTERCEPTACAO: PROGRAMADO (14:30)\n");
                        printf("ALVO: LUCAS SILVA  |  SETOR: PRACA CENTRAL  |  BASE LEGAL: DIRETRIZ SEC-402\n");
                        printf("AVALIACAO DA IA: Similaridade por drone: 78%% (Alta incerteza). Ordem aguarda envio.\n");
                        printf("INSTRUCAO: Selecione 2 evidencias registradas para contestar a identificacao.\n\n");

                        printf("1 - Comparacao Facial (Drone)\n");
                        printf("2 - Panfleto da Revolta Popular\n");
                        printf("3 - Registro de Entrada (Catraca)\n");
                        printf("4 - Camera Interna CFTV (Servidores)\n");

                        printf("\nEvidencia 1 (1 a 4): ");
                        leituraValida = scanf("%d", &evidencia1);

                        while (leituraValida != 1 || evidencia1 < 1 || evidencia1 > 4)
                        {
                            if (leituraValida != 1)
                            {
                                scanf("%*s");
                            }

                            printf("Entrada invalida. Digite um numero de 1 a 4: ");
                            leituraValida = scanf("%d", &evidencia1);
                        }

                        printf("Evidencia 2 (1 a 4): ");
                        leituraValida = scanf("%d", &evidencia2);

                        while (leituraValida != 1 ||
                               evidencia2 < 1 ||
                               evidencia2 > 4 ||
                               evidencia2 == evidencia1)
                        {
                            if (leituraValida != 1)
                            {
                                scanf("%*s");
                            }

                            printf("Entrada invalida. Digite um numero de 1 a 4 diferente da primeira: ");
                            leituraValida = scanf("%d", &evidencia2);
                        }

                        printf("\nEvidencias selecionadas: %d e %d\n", evidencia1, evidencia2);

                        if ((evidencia1 == 3 && evidencia2 == 4) ||
                            (evidencia1 == 4 && evidencia2 == 3))
                        {
                            falsoPositivo = 1;

                            printf("\nFALSO POSITIVO COMPROVADO!\n");
                            printf("A catraca e o CFTV provam presenca na empresa as 14:30.\n");
                            printf("[ OK ] STATUS: IDENTIFICACAO NAO CONFIRMADA\n");
                            printf("ALIBI CONFIRMADO: O alvo estava no laboratorio da empresa as 14:30.\n");
                        }
                        else
                        {
                            vidas--;

                            if ((evidencia1 == 1 && evidencia2 == 2) ||
                                (evidencia1 == 2 && evidencia2 == 1))
                            {
                                printf("A foto borrada e o panfleto citam o alvo, mas nao provam onde ele estava as 14:30.\n");
                            }
                            else if ((evidencia1 == 1 && evidencia2 == 3) ||
                                     (evidencia1 == 3 && evidencia2 == 1))
                            {
                                printf("O registro de ponto indica entrada, mas falta prova visual de permanencia as 14:30.\n");
                            }
                            else if ((evidencia1 == 1 && evidencia2 == 4) ||
                                     (evidencia1 == 4 && evidencia2 == 1))
                            {
                                printf("A camera interna mostra presenca, mas precisa do registro formal de ponto.\n");
                            }
                            else if (evidencia1 == 2 || evidencia2 == 2)
                            {
                                printf("O panfleto indica militancia politica, mas nao desmente a posicao da IA.\n");
                            }
                            else
                            {
                                printf("Evidencias insuficientes para comprovar o falso positivo. Tente outra combinacao.\n");
                            }

                            printf("\nUma vida foi perdida.\n");
                            printf("Vidas restantes: %d / %d\n", vidas, VIDAS_INICIAIS);

                            if (vidas > 0)
                            {
                                printf("Reveja os registros e tente outra combinacao.\n");
                            }
                        }
                    }
                    else
                    {
                        printf("[ OK ] IDENTIFICACAO NAO CONFIRMADA // FALSO POSITIVO COMPROVADO\n");
                        printf("ALIBI CONFIRMADO: O alvo estava no laboratorio da empresa as 14:30.\n\n");
                        printf("1 - SUSPENDER ORDEM DE DRONE\n");
                        printf("2 - Voltar ao escritorio\n");
                        printf("Escolha: ");

                        leituraValida = scanf("%d", &opcaoMenu);

                        while (leituraValida != 1 || opcaoMenu < 1 || opcaoMenu > 2)
                        {
                            if (leituraValida != 1)
                            {
                                scanf("%*s");
                            }

                            printf("Entrada invalida. Digite 1 ou 2: ");
                            leituraValida = scanf("%d", &opcaoMenu);
                        }

                        if (opcaoMenu == 1)
                        {
                            ordemSuspensa = 1;
                            possuiCD = 1;

                            printf("\nORDEM SUSPENSA! Drones cancelados.\n");
                            printf("O CD de Memoria foi ejetado pelo drive.\n");
                        }
                    }
                }
                else
                {
                    /* =============================================
                       CONFIGURACAO DA INSTALACAO (OPCIONAL)
                       ============================================= */
                    if (docPai == 1 && docMemorando == 1)
                    {
                        configLiberada = 1;
                    }

                    if (configLiberada == 0)
                    {
                        printf("\nACESSO ADMINISTRATIVO RESTRITO // DIRETRIZES DA FILIAL\n");
                        printf("Para acessar as configuracoes desta instalacao, correlacione as notas do Dr. Ramos\n");
                        printf("e o memorando governamental encontrados no escritorio corporativo.\n");
                        printf("Examinar ambos os documentos revela a chave de manutencao do projeto.\n");
                    }
                    else if (despachoDesativado == 1)
                    {
                        printf("\n[ DESATIVADO ] - O despacho automatico de drones desta central foi bloqueado.\n");
                        printf("Todos os 1.420 relatorios foram preservados intactos como prova contra o abuso.\n");
                    }
                    else
                    {
                        printf("\nDIRETRIZES DA UNIDADE LOCAL // FILIAL METROPOLITANA 08\n");
                        printf("STATUS DO SISTEMA: Conectado a rede regional de monitoramento\n");
                        printf("REGISTROS FORENSES ARQUIVADOS: 1.420 ocorrencias preservadas\n");
                        printf("ENVIO AUTOMATICO DE ALVOS DESTA INSTALACAO:\n");
                        printf("[ ATIVO ] - Drones sao despachados automaticamente sob correspondencia preliminar.\n");
                        printf("Desativar o envio automatico suspende os ataques sem apagar as provas forenses.\n\n");

                        printf("1 - DESATIVAR ENVIO AUTOMATICO DESTA INSTALACAO\n");
                        printf("2 - Voltar ao escritorio\n");
                        printf("Escolha: ");

                        leituraValida = scanf("%d", &opcaoMenu);

                        while (leituraValida != 1 || opcaoMenu < 1 || opcaoMenu > 2)
                        {
                            if (leituraValida != 1)
                            {
                                scanf("%*s");
                            }

                            printf("Entrada invalida. Digite 1 ou 2: ");
                            leituraValida = scanf("%d", &opcaoMenu);
                        }

                        if (opcaoMenu == 1)
                        {
                            despachoDesativado = 1;

                            printf("\n[ V ] PROTOCOLO ETICO APLICADO: CENTRAL LOCAL PROTEGIDA COM SUCESSO!\n");
                            printf("Envio automatico da filial desativado. Registros forenses preservados!\n");
                            printf("- Apagar o sistema destruiria as evidencias que comprovam o desvio do governo.\n");
                            printf("- Desativar o despacho automatico impede ataques imediatos mantendo a verdade protegida.\n");
                        }
                    }
                }

                /* Libera a configuracao assim que as duas notas forem lidas */
                if (docPai == 1 && docMemorando == 1 && configLiberada == 0)
                {
                    configLiberada = 1;
                    printf("\nPista correlacionada: Acesso de Administrador liberado no computador!\n");
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
                printf("A contestacao falhou e o sistema enviou o drone.\n");
                printf("Lucas Silva nao pode ser salvo.\n");
                printf("A viagem de Elira e interrompida.\n");
                printf("\nFINAL RUIM / APOCALIPTICO\n");
            }
            else if (possuiCD == 1)
            {
                printf("\n====================================================\n");
                printf("          ARTEFATO RECUPERADO: CD DE MEMORIA // 2008\n");
                printf("====================================================\n");
                printf("ELIRA // MEMORY CD-ROM\n");
                printf("2008: RECONHECIMENTO FACIAL\n");
                printf("BUILD 0.94 - CONTROLE GOV\n\n");

                printf("DESVIO ALGORITMICO // FASE 2 (2008) CONCLUIDA\n");
                printf("Ao demonstrar o falso positivo atraves do cracha de ponto e do\n");
                printf("circuito interno, Elira impediu o drone e salvou a vida de Lucas Silva.\n\n");

                printf("O algoritmo de busca facial, concebido por seu pai para salvar\n");
                printf("vitimas em catastrofes, havia sido pervertido pelo governo para\n");
                printf("perseguir lideres populares e ativistas civis.\n\n");

                if (despachoDesativado == 1)
                {
                    printf("[DESTAQUE ETICO]: Despacho automatico da filial desativado,\n");
                    printf("mantendo todas as 1.420 provas forenses intactas para o futuro.\n");
                }
                else
                {
                    printf("[DESCOBERTA PENDENTE]: Havia um protocolo no escritorio para\n");
                    printf("desativar o envio automatico da filial mantendo os registros como prova.\n");
                }

                printf("\nA LICAO ETICA DE 2008:\n");
                printf("1. O ERRO TECNICO (FALSO POSITIVO):\n");
                printf("Algoritmos probabilisticos falham sob baixa nitidez.\n");
                printf("2. O ERRO POLITICO (DESVIO ETICO):\n");
                printf("Mesmo que Lucas estivesse no protesto, transformar uma ferramenta\n");
                printf("humanitaria em aparato belico contra a dissidencia civil e uma\n");
                printf("violacao inaceitavel.\n");
                printf("'A maquina deve servir a liberdade, nao a prisao.'\n\n");

                printf("-> Proxima Fronteira: FASE 3 // ANO 2048: O PROTOTIPO A.R.1.3.L.!\n");

                printf("\nVidas restantes: %d / %d\n", vidas, VIDAS_INICIAIS);
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