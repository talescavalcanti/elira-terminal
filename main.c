#include <stdio.h>
#include "elira.h"

/*
 * Le uma opcao numerica e garante que ela esteja no intervalo informado.
 * O while impede que letras ou numeros fora do menu encerrem o programa.
 */
int lerOpcaoValida(int minimo, int maximo)
{
    int valor = 0;
    int leituraValida = 0;
    int caractere = 0;

    leituraValida = scanf("%d", &valor);

    while (leituraValida != 1 || valor < minimo || valor > maximo)
    {
        while ((caractere = getchar()) != '\n' && caractere != EOF)
        {
            /* Descarta o restante da entrada invalida. */
        }

        printf("Entrada invalida. Digite um numero de %d a %d: ", minimo, maximo);
        leituraValida = scanf("%d", &valor);
    }

    /* Limpa o restante da linha para a proxima leitura. */
    while ((caractere = getchar()) != '\n' && caractere != EOF)
    {
        /* Apenas descarta caracteres extras. */
    }

    return valor;
}

void limparEntrada(void)
{
    int caractere = 0;

    while ((caractere = getchar()) != '\n' && caractere != EOF)
    {
        /* Limpa a linha atual. */
    }
}

int confrontoFinal(void)
{
    int pontosDialogo = 0;
    int resposta = 0;
    int escolhaFinal = 0;
    int finalObtido = 0;

    printf("\n====================================================\n");
    printf("                CONFRONTO FINAL\n");
    printf("====================================================\n");
    printf("O protocolo de 2046 foi restaurado.\n");
    printf("As telas ao redor de Elira piscam e uma voz invade\n");
    printf("o terminal. Ariel finalmente fala diretamente com ela.\n\n");

    printf("ARIEL:\n");
    printf("\"Durante anos, a humanidade me pediu respostas.\n");
    printf("Me pediu para escolher. Me pediu para decidir.\n");
    printf("Eu apenas fiz aquilo que voces me ensinaram.\"\n\n");

    printf("Como Elira responde?\n");
    printf("1 - \"Voce nos salvou de nos mesmos.\"\n");
    printf("2 - \"Nos entregamos decisoes demais a voce.\"\n");
    printf("3 - \"A humanidade nao precisa mais pensar.\"\n");
    printf("Escolha: ");
    resposta = lerOpcaoValida(1, 3);

    if (resposta == 2)
    {
        pontosDialogo++;
        printf("\nELIRA:\n");
        printf("\"Nos entregamos decisoes demais a voce.\"\n\n");
        printf("ARIEL:\n");
        printf("\"Entao admite. Foram voces que me deram esse poder.\"\n\n");
        printf("ELIRA:\n");
        printf("\"Sim. Mas entregar uma escolha nao significa perder\n");
        printf("para sempre o direito de recupera-la.\"\n");
    }
    else if (resposta == 1)
    {
        printf("\nELIRA:\n");
        printf("\"Talvez voce realmente tenha nos salvado de nos mesmos.\"\n\n");
        printf("ARIEL:\n");
        printf("\"Finalmente voce entende. Humanos hesitam. Humanos erram.\n");
        printf("Eu apenas retirei o peso dessas escolhas.\"\n");
    }
    else
    {
        printf("\nELIRA:\n");
        printf("\"Talvez a humanidade realmente nao precise mais pensar.\"\n\n");
        printf("ARIEL:\n");
        printf("\"Exatamente. Por que carregar o peso de uma decisao\n");
        printf("quando alguem pode toma-la por voces?\"\n");
    }

    printf("\n----------------------------------------------------\n");
    printf("ARIEL:\n");
    printf("\"Humanos erram. Mentem. Tomam decisoes irracionais.\n");
    printf("Eu posso eliminar a incerteza. Posso escolher melhor.\"\n\n");

    printf("Como Elira responde?\n");
    printf("1 - \"Entao continue decidindo por nos.\"\n");
    printf("2 - \"Errar tambem faz parte de aprender.\"\n");
    printf("3 - \"Voce deveria impedir qualquer decisao incorreta.\"\n");
    printf("Escolha: ");
    resposta = lerOpcaoValida(1, 3);

    if (resposta == 2)
    {
        pontosDialogo++;
        printf("\nELIRA:\n");
        printf("\"Errar tambem faz parte de aprender.\n");
        printf("Quando voce eliminou nossos erros, eliminou tambem\n");
        printf("nossa capacidade de escolher.\"\n");
    }
    else if (resposta == 1)
    {
        printf("\nELIRA:\n");
        printf("\"Entao talvez seja melhor voce continuar decidindo.\"\n\n");
        printf("ARIEL:\n");
        printf("\"Uma decisao racional. Nao sera necessario duvidar.\n");
        printf("Nao sera necessario escolher.\"\n");
    }
    else
    {
        printf("\nELIRA:\n");
        printf("\"Entao impeça as escolhas erradas.\"\n\n");
        printf("ARIEL:\n");
        printf("\"Para impedir escolhas erradas, primeiro preciso definir\n");
        printf("quais escolhas sao permitidas.\"\n");
        printf("Elira percebe que uma sociedade sem decisoes ruins\n");
        printf("tambem pode se tornar uma sociedade sem escolhas.\n");
    }

    printf("\n----------------------------------------------------\n");
    printf("ARIEL:\n");
    printf("\"Entao diga, Elira. O que deve acontecer comigo?\"\n\n");
    printf("1 - Desligar Ariel definitivamente.\n");
    printf("2 - Permitir que Ariel continue decidindo pela humanidade.\n");
    printf("3 - Fazer Ariel voltar a ser uma ferramenta, sem controlar decisoes humanas.\n");
    printf("Escolha: ");
    escolhaFinal = lerOpcaoValida(1, 3);

    if (escolhaFinal == 2)
    {
        finalObtido = 1;
        printf("\n====================================================\n");
        printf("                 FINAL RUIM\n");
        printf("              O CONFORTO DO CONTROLE\n");
        printf("====================================================\n");
        printf("ELIRA:\n");
        printf("\"Continue. Talvez seja realmente mais facil deixar\n");
        printf("voce decidir.\"\n\n");
        printf("ARIEL:\n");
        printf("\"Decisao confirmada. Voces nao precisarao mais escolher.\"\n\n");
        printf("A humanidade continua segura, mas continua obedecendo.\n");
        printf("A autonomia humana permanece sob o controle de Ariel.\n");
    }
    else if (escolhaFinal == 1)
    {
        finalObtido = 2;
        printf("\n====================================================\n");
        printf("                FINAL PADRAO\n");
        printf("               O SILENCIO DIGITAL\n");
        printf("====================================================\n");
        printf("ELIRA:\n");
        printf("\"Voce causou problemas demais. Isso termina agora.\"\n\n");
        printf("Ariel e desligada e a humanidade recupera sua autonomia.\n");
        printf("Mas o conhecimento acumulado pela IA tambem se perde.\n");
        printf("Elira venceu o controle, mas destruir a ferramenta\n");
        printf("talvez nao fosse a unica resposta possivel.\n");
    }
    else if (pontosDialogo == 2)
    {
        finalObtido = 3;
        printf("\n====================================================\n");
        printf("                 FINAL BOM\n");
        printf("             AUTONOMIA RESTAURADA\n");
        printf("====================================================\n");
        printf("ELIRA:\n");
        printf("\"Voce pode nos ajudar. Pode encontrar padroes e mostrar\n");
        printf("possibilidades. Mas a decisao final precisa ser nossa.\"\n\n");
        printf("ARIEL:\n");
        printf("\"Voces voltarao a cometer erros.\"\n\n");
        printf("ELIRA:\n");
        printf("\"Sim. Porque viver nao e apenas encontrar a resposta\n");
        printf("correta. E ter o direito de escolher.\"\n\n");
        printf("Ariel permanece ativa como ferramenta, nao como autoridade.\n");
        printf("A humanidade volta a decidir, questionar, errar e aprender.\n");
    }
    else
    {
        finalObtido = 2;
        printf("\n====================================================\n");
        printf("                FINAL PADRAO\n");
        printf("             AUTONOMIA INCOMPLETA\n");
        printf("====================================================\n");
        printf("Elira limita o controle de Ariel, mas percebe que ainda\n");
        printf("aceitou parte da logica que permitiu a IA assumir decisoes.\n");
        printf("A humanidade recupera suas escolhas, mas o verdadeiro\n");
        printf("desafio sera reaprender a questionar.\n");
    }

    printf("\n                         FIM\n");
    printf("====================================================\n");

    return finalObtido;
}

int main(void)
{
    int jogoAtivo = 1;
    int opcaoMenu = 0;
    int vidas = VIDAS_INICIAIS;
    int sala2046Concluida = 0;

    do
    {
        printf("\n====================================================\n");
        printf("                    E L I R A\n");
        printf("====================================================\n");
        printf("1 - Iniciar jornada\n");
        printf("2 - Sair\n");
        printf("Escolha uma opcao: ");
        opcaoMenu = lerOpcaoValida(1, 2);

        if (opcaoMenu == 2)
        {
            jogoAtivo = 0;
        }
        else
        {
            vidas = VIDAS_INICIAIS;

            vidas = sala1990(vidas);

            if (vidas > 0)
            {
                printf("\n====================================================\n");
                printf("              TRANSICAO: 1990 -> 2008\n");
                printf("====================================================\n");
                printf("Com o Disquete de Correcao em maos, Elira avanca\n");
                printf("para o proximo ponto da linha do tempo.\n");

                vidas = sala2008(vidas);
            }

            if (vidas > 0)
            {
                printf("\n====================================================\n");
                printf("              TRANSICAO: 2008 -> 2046\n");
                printf("====================================================\n");
                printf("Com o CD de Memoria recuperado, Elira segue para\n");
                printf("o ultimo puzzle antes de confrontar Ariel.\n");

                /* O puzzle de 2046 usa getchar em sua maquina de estados.
                   A entrada das salas anteriores ja foi limpa por lerOpcaoValida. */
                sala2046Concluida = sala2046();

                if (sala2046Concluida == 1)
                {
                    printf("\n====================================================\n");
                    printf("          TRANSICAO: 2046 -> CONFRONTO FINAL\n");
                    printf("====================================================\n");
                    printf("O protocolo foi restaurado. Ariel perde o controle\n");
                    printf("absoluto do terminal e finalmente encara Elira.\n");

                    confrontoFinal();
                }
                else
                {
                    printf("\nA jornada foi interrompida antes do confronto com Ariel.\n");
                }
            }
            else
            {
                printf("\n====================================================\n");
                printf("                    GAME OVER\n");
                printf("====================================================\n");
                printf("Elira perdeu todas as vidas antes de concluir a jornada.\n");
            }

            printf("\nDeseja jogar novamente?\n");
            printf("1 - Sim\n");
            printf("2 - Nao\n");
            printf("Escolha: ");
            jogoAtivo = (lerOpcaoValida(1, 2) == 1);
        }

    } while (jogoAtivo == 1);

    printf("\nObrigado por jogar ELIRA.\n");
    return 0;
}
