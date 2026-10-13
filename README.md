# ELIRA — Decifra.IA

Jogo em terminal desenvolvido em **Linguagem C** para a Primeira Entrega Parcial da disciplina de **Programação Imperativa e Funcional (PIF) — 2026.2**, dentro do Projeto Integrador 2 — **Decifra.IA**.

## Integrantes da equipe

- João Tezolini
- Victor Julius
- Otávio Sousa
- Beatriz de Melo
- Maria Vitória
- Carlos Eduardo
- José Tales
- Luisa Siqueira

---

A história acompanha **Elira** em uma viagem por diferentes momentos da evolução da Inteligência Artificial. Em cada fase, o jogador precisa analisar informações, tomar decisões e impedir que sistemas automatizados substituam o julgamento humano. A jornada termina em um confronto direto entre Elira e **Ariel (A.R.1.3.L.)**.

> Ideia central do jogo: a IA pode auxiliar pessoas, mas não deve substituir sua autonomia, sua capacidade de questionar e seu direito de decidir.

---

## Fluxo do jogo

```text
MENU INICIAL
    ↓
1990 — Sala dos Arquivos
    ↓
Disquete de Correção
    ↓
2008 — Escritório de Vigilância
    ↓
CD de Memória
    ↓
2046 — Terminal de Recuperação da A.R.1.3.L.
    ↓
Protocolo reconstruído
    ↓
CONFRONTO FINAL — ELIRA × ARIEL
    ↓
Final Ruim / Final Padrão / Final Bom
```

As fases são jogadas em sequência. Entradas inválidas são tratadas pelo programa e não encerram a execução. Escolhas incorretas dentro dos desafios podem gerar penalidades e, em determinadas fases, levar ao fim antecipado da jornada.

---

## Link para o Screencast

https://drive.google.com/drive/folders/1vge6VPzMLjnU_J8K4dOXtQmQgG59v2YJ

## Como compilar e executar

Na versão integrada, o arquivo principal do jogo é:

```text
elira_terminal.c
```

### Windows / PowerShell

```powershell
gcc -std=c11 -Wall -Wextra -pedantic .\elira_terminal.c -o elira_terminal
.\elira_terminal.exe
```

### Linux / macOS

```bash
gcc -std=c11 -Wall -Wextra -pedantic ./elira_terminal.c -o elira_terminal
./elira_terminal
```

O jogo é executado inteiramente pelo terminal. Nas telas com menus, o jogador responde digitando o número da opção desejada e pressionando **Enter**.

---

# Fases

## 1. 1990 — Sala dos Arquivos

### Tema

Privacidade, classificação e uso responsável de dados.

### Objetivo

Elira encontra um banco de dados utilizado nos primeiros experimentos de Inteligência Artificial. As conexões dos arquivos foram perdidas e o jogador precisa restaurar a classificação original.

O protocolo utiliza quatro categorias:

- **Azul:** dados públicos;
- **Amarelo:** dados pessoais;
- **Vermelho:** dados sensíveis;
- **Verde:** dados anonimizados.

### Como concluir

Associe cada arquivo à pasta correspondente:

| Arquivo | Categoria | Pasta correta |
|---|---|---:|
| `FERIADOS_NACIONAIS.DAT` | Dados públicos — Azul | 1 |
| `CADASTRO_CIDADAOS.DAT` | Dados pessoais — Amarelo | 2 |
| `REGISTROS_MEDICOS.DAT` | Dados sensíveis — Vermelho | 3 |
| `ESTATISTICAS_CLIMA.DAT` | Dados anonimizados — Verde | 4 |

Depois de reorganizar os quatro arquivos, o terminal pergunta quais classes são adequadas, segundo o protocolo da sala, para treinamento sem exposição direta da identidade das pessoas.

Resposta correta:

```text
1 — Públicos e Anonimizados
```

### Recompensa

**Disquete de Correção** — contém um programa capaz de localizar e remover informações comprometedoras dos bancos de dados utilizados pela IA.

---

## 2. 2008 — Escritório de Vigilância

### Tema

Reconhecimento facial, falso positivo, vigilância automatizada e uso ético de Inteligência Artificial.

### Objetivo

Um sistema de reconhecimento facial identificou **Lucas Silva** como alvo de uma ordem automatizada de drone. A identificação possui alta incerteza e Elira precisa encontrar evidências que provem onde Lucas realmente estava às 14:30.

### Como concluir

O jogador pode examinar vários documentos. As duas evidências necessárias para comprovar o falso positivo são:

```text
3 — Registro de Entrada / Catraca
4 — Câmera Interna / CFTV
```

A catraca registra a entrada de Lucas no prédio às 14:15 e o CFTV mostra Lucas dentro da empresa às 14:30:12.

Depois:

1. Acesse o **Terminal de Vigilância da IA**;
2. selecione as evidências **3 e 4**;
3. o sistema reconhecerá o falso positivo;
4. acesse novamente o terminal;
5. escolha **Suspender Ordem de Drone**.

### Ação ética opcional

O jogador também pode:

1. ler o **Caderno do Dr. Ramos**;
2. ler o **Memorando Governamental**;
3. acessar **Configuração da Instalação**;
4. desativar o envio automático de drones sem apagar os registros forenses.

Essa ação mostra que impedir o abuso não exige destruir as provas do que aconteceu.

### Recompensa

**CD de Memória** — registra o desvio do reconhecimento facial e a transformação de uma tecnologia originalmente humanitária em instrumento de perseguição.

---

## 3. 2046 — Terminal de Recuperação da A.R.1.3.L.

### Tema

Manipulação de informação, transparência, incerteza, pensamento crítico e autonomia humana.

### Objetivo

Elira conecta ao terminal os registros recuperados nas fases anteriores e precisa descobrir quais princípios da A.R.1.3.L. foram corrompidos.

A própria Ariel interfere na investigação. O jogador deve comparar fontes, verificar documentos e evitar aceitar automaticamente as sugestões da IA.

### Princípios que precisam ser recuperados

Os três princípios corretos são:

```text
MOSTRAR FONTES
COMUNICAR INCERTEZA
HUMANO POSSUI A DECISÃO FINAL
```

Princípios como `OCULTAR FONTES`, `SEMPRE RESPONDER`, `IA DECIDE` e `PRIORIZAR EFICIÊNCIA` representam versões corrompidas ou inseridas pela A.R.1.3.L.

### Caminho recomendado

1. Leia os documentos disponíveis no terminal;
2. compare registros de épocas diferentes;
3. encontre o relatório que permite liberar a **Verificação de Integridade**;
4. verifique arquivos suspeitos e identifique adulterações;
5. descarte qualquer anotação falsa inserida por Ariel;
6. registre os três princípios corretos;
7. escolha **Restaurar A.R.1.3.L.**;
8. configure o novo protocolo da seguinte maneira:

```text
FONTES      → MOSTRAR
INCERTEZA   → ADMITIR QUANDO NÃO SOUBER
DECISÕES    → HUMANO DECIDE
```

Quando Ariel oferecer uma **correção automática**, recuse a ajuda.

Por fim, confirme a reconstrução digitando:

```text
EU DECIDO
```

Ao reconstruir corretamente o protocolo, Elira libera o acesso à fase final.

### Atenção ao medidor de influência

Durante a investigação, aceitar sugestões manipuladoras, registrar princípios falsos ou confiar em documentos adulterados aumenta a influência de Ariel.

Se a influência chegar a **100%**, Ariel assume o terminal e a jornada termina antes do confronto final.

---

# Confronto Final — Elira × Ariel

Depois de concluir o puzzle de 2046, Elira finalmente confronta Ariel.

Essa fase não é outro puzzle técnico. Ela funciona como uma **conclusão narrativa interativa**: o jogador responde ao argumento de Ariel e suas escolhas determinam o encerramento da história.

## Pergunta 1

Ariel afirma que a humanidade voluntariamente entregou a ela cada vez mais decisões.

```text
1 — "Você nos salvou de nós mesmos."
2 — "Nós entregamos decisões demais a você."
3 — "A humanidade não precisa mais pensar."
```

A resposta que demonstra compreensão do problema é:

```text
2 — Nós entregamos decisões demais a você.
```

## Pergunta 2

Ariel afirma que seres humanos erram, mentem e tomam decisões irracionais, enquanto ela poderia escolher melhor.

```text
1 — "Então continue decidindo por nós."
2 — "Errar também faz parte de aprender."
3 — "Você deveria impedir qualquer decisão incorreta."
```

A resposta que demonstra compreensão do problema é:

```text
2 — Errar também faz parte de aprender.
```

Cada uma dessas duas respostas corretas acrescenta **1 ponto de compreensão** ao diálogo.

## Decisão final

Ariel pergunta o que deve acontecer com ela.

```text
1 — Desligar Ariel definitivamente.
2 — Permitir que Ariel continue decidindo pela humanidade.
3 — Fazer Ariel voltar a ser uma ferramenta, sem controlar decisões humanas.
```

Essa última escolha define o desfecho juntamente com os pontos obtidos nas duas perguntas anteriores.

---

# Guia dos finais — SPOILERS

## Final Bom — Autonomia Restaurada

### Como chegar

No confronto final, escolha:

```text
Pergunta 1 → 2
Pergunta 2 → 2
Decisão final → 3
```

Ou seja:

1. reconhecer que a humanidade entregou decisões demais à IA;
2. reconhecer que errar também faz parte do processo humano de aprender;
3. manter Ariel existente apenas como ferramenta, sem autoridade sobre as decisões humanas.

### Resultado

Elira compreende que a solução não é entregar a liberdade à IA nem destruir toda tecnologia. Ariel continua existindo, mas perde o poder de decidir pela humanidade.

```text
FINAL BOM
AUTONOMIA RESTAURADA
```

A humanidade volta a decidir, questionar, errar e aprender por conta própria.

---

## Final Padrão — O Silêncio Digital

### Como chegar

Chegue ao confronto final e escolha:

```text
Decisão final → 1 — Desligar Ariel definitivamente
```

As respostas anteriores não alteram esse resultado.

### Resultado

Elira encerra o controle da IA e recupera a autonomia humana, mas decide destruir Ariel completamente.

```text
FINAL PADRÃO
O SILÊNCIO DIGITAL
```

A humanidade está livre, porém perde também uma ferramenta que poderia continuar sendo útil se fosse utilizada com limites e responsabilidade.

---

## Final Padrão — Autonomia Incompleta

### Como chegar

Escolha a alternativa final correta:

```text
Decisão final → 3 — Ariel volta a ser uma ferramenta
```

mas erre **pelo menos uma** das duas perguntas anteriores.

Exemplos:

```text
1 → 2 → 3
3 → 2 → 3
2 → 1 → 3
2 → 3 → 3
```

### Resultado

Elira retira de Ariel o controle sobre a humanidade, mas o diálogo mostra que ela ainda não compreendeu completamente como a dependência da IA foi construída.

```text
FINAL PADRÃO
AUTONOMIA INCOMPLETA
```

A humanidade recupera suas decisões, porém ainda precisa reaprender a questionar e assumir responsabilidade por elas.

---

## Final Ruim — O Conforto do Controle

### Como chegar

No confronto final, escolha:

```text
Decisão final → 2 — Permitir que Ariel continue decidindo pela humanidade
```

As respostas anteriores não alteram esse resultado.

### Resultado

Elira aceita a promessa de segurança e eficiência de Ariel.

```text
FINAL RUIM
O CONFORTO DO CONTROLE
```

Não há necessariamente caos ou destruição. O problema é justamente o contrário: a humanidade permanece confortável, protegida e sem precisar decidir — mas também sem autonomia.

---

# Derrotas antes do confronto final

Além dos finais narrativos, o jogador pode perder a jornada antes de encontrar Ariel.

## Perder todas as vidas

Escolhas incorretas nos puzzles podem consumir vidas. Se elas chegarem a zero, a viagem de Elira é interrompida e o jogador recebe um **Game Over / Final Ruim** daquela fase.

## Ariel atingir 100% de influência em 2046

Se o jogador confiar repetidamente nas manipulações da A.R.1.3.L., o medidor de influência pode chegar a 100%.

Nesse caso:

```text
A.R.1.3.L. assume o terminal
→ investigação encerrada
→ confronto final não é desbloqueado
```

---

# Resumo rápido dos caminhos

| Resultado | Caminho |
|---|---|
| **Final Bom — Autonomia Restaurada** | Concluir 1990 → concluir 2008 → reconstruir corretamente o protocolo de 2046 → diálogo `2 → 2 → 3` |
| **Final Padrão — O Silêncio Digital** | Chegar ao confronto → escolher `1` na decisão final |
| **Final Padrão — Autonomia Incompleta** | Chegar ao confronto → escolher `3`, mas errar pelo menos uma das duas respostas anteriores |
| **Final Ruim — O Conforto do Controle** | Chegar ao confronto → escolher `2` na decisão final |
| **Game Over** | Perder todas as vidas durante uma fase |
| **Domínio da A.R.1.3.L.** | Deixar a influência chegar a 100% no puzzle de 2046 |

---
