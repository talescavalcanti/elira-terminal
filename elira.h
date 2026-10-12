#ifndef ELIRA_H
#define ELIRA_H

/* Quantidade de vidas compartilhada entre as salas iniciais. */
#define VIDAS_INICIAIS 5

/* Funcoes de apoio usadas pelas salas. */
int lerOpcaoValida(int minimo, int maximo);
void limparEntrada(void);

/* Cada sala devolve a quantidade de vidas restante.
   Se retornar 0, a jornada foi interrompida. */
int sala1990(int vidas);
int sala2008(int vidas);

/* A sala 2046 usa um sistema proprio de influencia.
   Retorna 1 quando o protocolo e restaurado corretamente
   e 0 quando o jogador falha ou abandona a investigacao. */
int sala2046(void);

/* Fase narrativa executada somente depois de concluir 2046. */
int confrontoFinal(void);

#endif
