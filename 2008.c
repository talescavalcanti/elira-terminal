#include <stdio.h>
#include "elira.h"

int sala2008(int vidas)
{
    int comando = 0;
    int docFace = 0;
    int docPanfleto = 0;
    int docCatraca = 0;
    int docCftv = 0;
    int docPai = 0;
    int docMemorando = 0;
    int evidencia1 = 0;
    int evidencia2 = 0;
    int docsExaminados = 0;
    int falsoPositivo = 0;
    int ordemSuspensa = 0;
    int configLiberada = 0;
    int despachoDesativado = 0;
    int possuiCD = 0;
    int opcao = 0;

    printf("\n====================================================\n");
    printf("      2008 - ESCRITORIO DE VIGILANCIA\n");
    printf("====================================================\n");
    printf("Elira chega a um escritorio de vigilancia.\n");
    printf("O sistema marcou Lucas Silva com uma ORDEM DE DRONE\n");
    printf("para as 14:30. A IA indica 78%% de similaridade,\n");
    printf("mas a identificacao possui alta incerteza.\n\n");
    printf("OBJETIVO: examine os registros, escolha duas evidencias\n");
    printf("que comprovem o alibi de Lucas e suspenda a ordem.\n");
    printf("\nVidas: %d / %d\n", vidas, VIDAS_INICIAIS);

    while (ordemSuspensa == 0 && vidas > 0)
    {
        docsExaminados = docFace + docPanfleto + docCatraca + docCftv;
        configLiberada = (docPai == 1 && docMemorando == 1);

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
        printf("8 - Configuracao da Instalacao          %s\n",
               configLiberada ? (despachoDesativado ? "[DESATIVADA]" : "[DISPONIVEL]") : "[BLOQUEADA]");
        printf("\nVidas: %d / %d\n", vidas, VIDAS_INICIAIS);
        printf("Escolha um comando: ");
        comando = lerOpcaoValida(1, 8);

        if (comando == 1)
        {
            docFace = 1;
            printf("\nEVIDENCIA 01 // COMPARACAO BIOMETRICA (DRONE)\n");
            printf("ALVO: Lucas Silva | HORARIO: 14:30 | CONFIANCA: 78%%\n");
            printf("Imagem aerea granulada e com desfoque de movimento.\n");
            printf("Sozinha, essa imagem nao comprova que Lucas estava no local.\n");
        }
        else if (comando == 2)
        {
            docPanfleto = 1;
            printf("\nEVIDENCIA 02 // PANFLETO DA REVOLTA POPULAR\n");
            printf("O documento cita Lucas como lider civil da marcha das 10h as 13h.\n");
            printf("Explica por que a IA o marcou como alvo, mas nao prova\n");
            printf("onde ele estava as 14:30.\n");
        }
        else if (comando == 3)
        {
            docCatraca = 1;
            printf("\nEVIDENCIA 03 // REGISTRO DA CATRACA BIOMETRICA\n");
            printf("Lucas entrou na empresa as 14:15:08.\n");
            printf("A sede fica a 12 km da Praca Central.\n");
            printf("O registro formal precisa ser combinado com uma prova\n");
            printf("de que ele permaneceu no predio as 14:30.\n");
        }
        else if (comando == 4)
        {
            docCftv = 1;
            printf("\nEVIDENCIA 04 // CAMERA INTERNA CFTV\n");
            printf("Gravacao de 14:30:12 mostra Lucas trabalhando no subsolo.\n");
            printf("O horario coincide com o momento do suposto avistamento.\n");
        }
        else if (comando == 5)
        {
            docPai = 1;
            printf("\nCADERNO DO DR. RAMOS\n");
            printf("As notas alertam que sistemas biometricos nao devem\n");
            printf("transformar uma correspondencia probabilistica em certeza.\n");
            printf("Tambem citam um modo de manutencao local da instalacao.\n");
        }
        else if (comando == 6)
        {
            docMemorando = 1;
            printf("\nMEMORANDO GOVERNAMENTAL // DIRETRIZ SEC-402\n");
            printf("A diretriz prioriza velocidade de resposta sobre certeza.\n");
            printf("O documento informa que o despacho automatico pode ser\n");
            printf("suspenso no menu de configuracao da instalacao.\n");
        }
        else if (comando == 7)
        {
            printf("\n====================================================\n");
            printf("     TERMINAL DE VIGILANCIA BIOMETRICA - 2008\n");
            printf("====================================================\n");

            if (falsoPositivo == 0)
            {
                printf("ORDEM DE DRONE: PROGRAMADA PARA 14:30\n");
                printf("Selecione duas evidencias para contestar a identificacao.\n\n");
                printf("1 - Comparacao Facial (Drone)\n");
                printf("2 - Panfleto da Revolta\n");
                printf("3 - Registro de Entrada (Catraca)\n");
                printf("4 - Camera Interna CFTV\n");
                printf("Evidencia 1: ");
                evidencia1 = lerOpcaoValida(1, 4);
                printf("Evidencia 2: ");
                evidencia2 = lerOpcaoValida(1, 4);

                while (evidencia2 == evidencia1)
                {
                    printf("As evidencias precisam ser diferentes. Escolha novamente: ");
                    evidencia2 = lerOpcaoValida(1, 4);
                }

                if ((evidencia1 == 3 && evidencia2 == 4) ||
                    (evidencia1 == 4 && evidencia2 == 3))
                {
                    falsoPositivo = 1;
                    printf("\nFALSO POSITIVO COMPROVADO!\n");
                    printf("A catraca confirma entrada e o CFTV confirma presenca\n");
                    printf("no horario exato do suposto avistamento.\n");
                }
                else
                {
                    vidas--;
                    printf("\nEvidencias insuficientes para provar o alibi.\n");
                    printf("Uma vida foi perdida. Vidas restantes: %d / %d\n",
                           vidas, VIDAS_INICIAIS);
                }
            }
            else
            {
                printf("FALSO POSITIVO COMPROVADO.\n");
                printf("A identificacao de Lucas ja foi contestada com sucesso.\n");
                printf("Agora desative o despacho automatico na Configuracao\n");
                printf("da Instalacao para suspender definitivamente a ordem.\n");
            }
        }
        else
        {
            if (configLiberada == 0)
            {
                printf("\nACESSO RESTRITO.\n");
                printf("Leia o Caderno do Dr. Ramos e o Memorando Governamental\n");
                printf("para liberar a configuracao da instalacao.\n");
            }
            else if (despachoDesativado == 1)
            {
                printf("\nO despacho automatico desta central ja esta desativado.\n");
            }
            else
            {
                printf("\nCONFIGURACAO DA INSTALACAO\n");
                printf("1 - Desativar envio automatico de drones\n");
                printf("2 - Voltar\n");
                printf("Escolha: ");
                opcao = lerOpcaoValida(1, 2);

                if (opcao == 1)
                {
                    despachoDesativado = 1;
                    printf("\nDespacho automatico desativado.\n");
                    printf("Os registros foram preservados como prova do abuso.\n");
                }
            }
        }

        /* A sala termina automaticamente quando as duas condicoes
           principais forem cumpridas, independentemente da ordem:
           1) comprovar o falso positivo com Catraca + CFTV;
           2) desativar o despacho automatico na configuracao. */
        if (falsoPositivo == 1 && despachoDesativado == 1 && ordemSuspensa == 0)
        {
            ordemSuspensa = 1;
            possuiCD = 1;

            printf("\n====================================================\n");
            printf("         ORDEM DE DRONE SUSPENSA COM SUCESSO\n");
            printf("====================================================\n");
            printf("O falso positivo foi comprovado e o envio automatico\n");
            printf("de drones foi desativado. Lucas esta fora de perigo.\n");
            printf("O sistema libera o CD de Memoria para Elira.\n");
        }
    }

    if (vidas == 0)
    {
        printf("\n====================================================\n");
        printf("          FALHA NA SALA DE 2008\n");
        printf("====================================================\n");
        printf("Elira nao conseguiu suspender a ordem a tempo.\n");
        return 0;
    }

    if (possuiCD == 1)
    {
        printf("\n====================================================\n");
        printf("             SALA DE 2008 CONCLUIDA\n");
        printf("====================================================\n");
        printf("Elira demonstrou que uma correspondencia algoritmica\n");
        printf("nao deve ser tratada como certeza sem verificacao humana.\n\n");
        printf("RECOMPENSA: CD DE MEMORIA\n");
        printf("\nVidas restantes: %d / %d\n", vidas, VIDAS_INICIAIS);
    }

    return vidas;
}
