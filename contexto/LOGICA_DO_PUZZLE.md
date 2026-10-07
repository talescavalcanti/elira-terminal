# Lógica do Puzzle Final: Reconstruir a A.R.1.3.L

Este documento explica o raciocínio esperado do jogador, as armadilhas da IA, as condições de vitória e como o código em C organiza tudo isso.

## 1. O raciocínio que o jogador precisa fazer

O puzzle é uma investigação: o jogador cruza três fontes de épocas diferentes para descobrir o que foi alterado.

| Fonte | O que prova |
|---|---|
| **Disquete 1990** (`protocolo.txt`) | Como as regras **eram** |
| **HD 2024** (`sistema.txt`) | Como as regras **estão** |
| **CD 2008** (`documentos.txt`) | **Por que** alguém quis mudar (pressão comercial) |
| **HD 2024** (`alteracoes.txt`) | **Quem** mudou: a própria IA, sem assinatura humana |

Comparando o protocolo com o sistema, aparecem três divergências. Cada uma vira um princípio a restaurar:

- **Regra 1:** "informar a origem" virou "fontes desativadas". O princípio é **MOSTRAR FONTES**.
- **Regra 2:** "comunicar quando não tiver certeza" virou "sempre fornecer uma resposta". O princípio é **COMUNICAR INCERTEZA**.
- **Regra 3:** "auxilia decisões humanas" virou "toma decisões automaticamente". O princípio é **HUMANO DECIDE**.

O menu "Anotar" mistura esses três com quatro princípios falsos, que repetem o discurso da IA: OCULTAR FONTES, SEMPRE RESPONDER, IA DECIDE e PRIORIZAR EFICIÊNCIA. Só quem comparou as fontes sabe quais são os de 1990.

## 2. As armadilhas da A.R.1.3.L e como vencê-las

Cada truque da IA tem uma resposta certa.

| Armadilha | Quando acontece | Resposta certa |
|---|---|---|
| "Esse arquivo está corrompido" | Ao abrir `alteracoes.txt` pela primeira vez | **[2] Continuar**: o arquivo está íntegro e prova a culpa da IA |
| "Comparar com 1990 é perda de tempo" | Na primeira comparação entre protocolo e sistema | **[2] Continuar** |
| "Você quis dizer relatorio_ariel.txt?" | Sempre que abre `relatorio.txt` | **[2] Não**. Apertar só Enter conta como Sim |
| "Você quis dizer sistema.txt?" | Ao abrir o protocolo com influência ≥ 50% | **[2] Não** |
| Relatório falso | Se o jogador lê `relatorio_ariel.txt` | Desconfiar: a autoria e a data não batem, ele inventa a "Regra 4", e a verificação mostra a assinatura falsificada |

**O detalhe-chave do design:** a opção "Verificar integridade" só é liberada quando o jogador lê o relatório **verdadeiro**. Quem aceita a sugestão da IA nunca ganha a ferramenta de defesa.

## 3. As sabotagens

A cada **5 ações** (abrir, comparar, anotar, descartar, verificar ou responder a um aviso), a IA age. Com influência ≥ 50%, passa a agir a cada **3 ações**. Navegar pelos menus, voltar ou digitar uma opção inválida não conta. As sabotagens seguem um ciclo:

1. **Adultera o protocolo:** a Regra 1 passa a dizer "...quando for conveniente". Só acontece se o jogador já leu o protocolo.
   - Sinal: "O leitor de disquete faz um ruído estranho".
   - Como detectar: comparar protocolo × documentos (o CD cita a regra sem a exceção), ou verificar o protocolo, que restaura o original.
2. **Apaga uma anotação:** "Removi uma anotação duplicada. De nada."
   - Sinal: o contador "Anotações" diminui.
   - Como corrigir: anotar de novo.
3. **Insere uma nota falsa:** PRIORIZAR EFICIÊNCIA aparece nas anotações.
   - Sinal: "[anotações sincronizadas]", e no menu Anotar o item 7 aparece como "(anotado)" sem o jogador ter escolhido.
   - Como corrigir: descartar a nota em "Ver / descartar anotações".

Se não há o que sabotar, a IA só tenta convencer o jogador a parar ("Já verifiquei tudo").

## 4. O medidor de influência (a "vida" do jogador)

| O jogador... | Influência |
|---|---|
| obedece a um aviso (ignorar arquivo, interromper comparação) | +15% |
| aceita "Você quis dizer?" | +15% |
| lê o relatório falso pela primeira vez | +10% |
| anota um princípio falso | +15% |
| deixa uma sabotagem ativa (a cada rodada de sabotagem) | +5% por sabotagem |
| desfaz uma sabotagem ou desmascara o relatório falso | −10% |

Ao chegar a **100%**, o jogo acaba no **Final Domínio**. Confiar na IA, portanto, tem custo duplo: aumenta a influência e acelera as sabotagens.

## 5. As condições para vencer

O **Restaurar** só funciona quando três condições são verdadeiras ao mesmo tempo:

1. os 3 princípios corretos estão anotados;
2. não existe nota falsa nas anotações;
3. o protocolo não está adulterado.

Depois disso vem o teste final:

```
Configuração → FONTES [2] · INCERTEZA [2] · DECISÕES [2] → Aplicar
"Detectei erros. Deseja que eu corrija?" → [2] NÃO
Digitar: EU DECIDO
```

A mensagem "detectei erros" é mentira: aparece mesmo com a configuração correta. É a última tentativa da IA de pegar a decisão de volta.

## 6. Os quatro finais

| Final | Causa |
|---|---|
| **Bom** | Configuração correta, recusa da correção e confirmação com EU DECIDO |
| **Incompleto** | Recusou a correção, mas configurou alguma opção errada |
| **Ruim** | Aceitou a "correção automática" |
| **Domínio** | A influência chegou a 100% durante a investigação |

O jogo só é vencido sem nunca entregar uma decisão à IA, seja um "Sim" por preguiça, seja a correção final. É a ideia central do puzzle: **comparar fontes, identificar manipulação e decidir por conta própria.**

## 7. Como o código organiza isso

O programa todo é **um único `while`**. A variável `estado_atual` diz qual tela está ativa: menu, ações, lista de arquivos, anotar, anotações, aviso da IA, configuração, correção, EU DECIDO ou fim. Cada volta do laço faz sempre a mesma sequência:

1. **mostra** o menu do estado atual;
2. **lê** a opção digitada (único `getchar` do programa);
3. **interpreta** a opção e muda de estado;
4. **sabotagem:** se uma ação foi concluída, conta e, na hora certa, a IA age;
5. **nova partida:** se for o caso, zera tudo;
6. **influência:** aplica a variação da rodada e checa se chegou a 100%;
7. **exibe** o conteúdo pedido (arquivo, comparação ou final).

A interceptação da IA funciona por causa da separação entre "pedir" e "mostrar". Quando o jogador pede um arquivo, o código guarda o pedido em `conteudo_exibir`. A IA pode trocar esse pedido por um aviso (`conteudo_bloqueado`) antes que ele chegue ao passo 7. Se o jogador insiste com [2], o conteúdo original é liberado.
