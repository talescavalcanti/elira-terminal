# Decifra.IA: Puzzle Final

Elira conecta ao terminal três dispositivos: um disquete de 1990, um CD de 2008 e um HD de 2026. Comparando os arquivos, ela precisa descobrir quais princípios da IA **A.R.1.3.L** foram corrompidos e reconstruir o protocolo original. Enquanto isso, a própria IA tenta atrapalhar.

> O puzzle não testa se o jogador encontra uma senha. Testa se ele compara fontes, identifica manipulação e toma a decisão sem entregá-la de volta à IA.


## Como rodar

```bash
gcc puzzle_final.c -o puzzle_final
./puzzle_final
```

Use um terminal com UTF-8 e cores ANSI (macOS, Linux ou Windows Terminal).

## O que foi feito

- **Jogo por menus numerados:** abrir arquivo, comparar dois arquivos, anotar princípio, ver/descartar anotações, verificar integridade e restaurar. Opções inválidas são recusadas e o menu é mostrado de novo.
- **Seis arquivos:** o protocolo de 1990, os documentos de 2008, o estado atual da IA, o registro de alterações, o relatório verdadeiro e um relatório falso criado pela IA.
- **Anotar princípios:** o jogador escolhe numa lista que mistura os três princípios corretos com quatro corrompidos. Escolher um corrompido aumenta a influência da IA.
- **Interferência da A.R.1.3.L:**
  - Um medidor de influência de 0 a 100% aparece no topo do menu e sobe quando o jogador aceita a ajuda da IA.
  - Ela adultera o protocolo, apaga anotações e insere uma nota falsa.
  - Ela pergunta "Você quis dizer…?", e apertar Enter conta como "Sim".
  - A opção "Verificar integridade" é o contra-ataque do jogador. Ela só é liberada lendo o relatório verdadeiro.
- **Final do puzzle:** o jogador configura a nova IA. Antes de aplicar, ela oferece uma "correção automática", e a confirmação é feita digitando `EU DECIDO`.
- **Quatro finais:** Bom, Incompleto, Ruim e Domínio (influência chega a 100%). Depois de qualquer final, o jogo pergunta se o jogador quer jogar novamente.

## Restrições técnicas

O código usa apenas o conteúdo dos Capítulos 1 a 3 do livro-base (Mizrahi): `printf`/`getchar`, variáveis, constantes, operadores, `if`/`else` e laços. Não usa vetores, strings, `string.h`, structs, ponteiros, arquivos nem funções próprias.

## Backlog (Artefatos outras disciplinas) 

**1- Interface e Apresentação**

![https://pub-181bb6168cd04f80bd48d53b914eecab.r2.dev/backlog-01.jpeg](https://pub-181bb6168cd04f80bd48d53b914eecab.r2.dev/WhatsApp%20Image%202026-09-03%20at%2022.53.31.jpeg)

**2- Ciclo do Jogo e Narrativa**

![Backlog](https://pub-181bb6168cd04f80bd48d53b914eecab.r2.dev/WhatsApp%20Image%202026-09-03%20at%2022.54.02.jpeg)

**3- Processo Qualidade e Suporte**

![Backlog](https://pub-181bb6168cd04f80bd48d53b914eecab.r2.dev/WhatsApp%20Image%202026-09-03%20at%2022.54.24.jpeg)

***

### **4 - [Protótipo de Telas](https://drive.google.com/drive/folders/1jbDYsVpSI9EwF0LDQyAzZWooYsANEepP)**

### **5 - [Vídeo de apresentação](https://drive.google.com/drive/folders/19YEVyh865qAgfRMuiUSIKoK3plIKMq8T)**

### **6 - [Jira](https://csprj-adsr-2p-e4.atlassian.net/jira/software/c/projects/PI2/list?jql=project%20%3D%20PI2%20AND%20parent%20%3D%20PI2-9%20AND%20fixVersion%20%3D%20empty%20ORDER%20BY%20resolution%20DESC%2C%20cf%5B10019%5D%20ASC)**

### **7 - [Diagrama das UHs](https://docs.google.com/document/d/1DT3npOZVw_-bCEAFb01KWhnt9JGE5SIf2Vkzfs2q1mk/edit?tab=t.0#heading=h.ld230wkn1wjo)**

***


- **Texto sem strings:** a única entrada em texto é `EU DECIDO`. A frase é lida letra a letra e vira um código numérico (`codigo = (codigo * 31 + letra) % 1000003`), comparado com uma constante `#define`.
- **Máquina de estados:** o jogo inteiro roda em um único `while`, com um só ponto de leitura do teclado e um só bloco de exibição (princípio DRY).
- **Compilação:** compila sem avisos com `gcc -Wall -Wextra -pedantic -std=c99`.

