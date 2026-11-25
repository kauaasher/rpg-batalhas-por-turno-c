# ⚔️ RPG de Batalha por Turnos

Projeto acadêmico desenvolvido em linguagem C, utilizando a biblioteca **Raylib** para criação de uma interface gráfica. O jogo consiste em um RPG de fantasia medieval com batalhas por turnos, gerenciamento de personagens, inventário e progressão.

## 🎮 Sobre o projeto

O jogador controlará uma equipe de seis personagens, podendo escolher entre sete classes diferentes. Cada personagem possuirá atributos próprios que influenciarão seu desempenho durante os combates.

A campanha será dividida em três fases, com diferentes grupos de monstros e uma batalha final contra um chefe (Boss).

As batalhas funcionarão por turnos, com a ordem de iniciativa definida inicialmente pela velocidade dos participantes.

## 🛡️ Classes disponíveis

O jogador poderá escolher entre sete classes:

- **Tank:** personagem especializado em resistir a danos.
- **Cavaleiro:** combatente focado em ataque e defesa.
- **Healer:** responsável pela cura e recuperação da equipe.
- **Arqueiro:** especialista em ataques à distância.
- **Mago:** utiliza magia e habilidades que consomem mana.
- **Suporte:** auxilia os aliados por meio de habilidades de apoio.
- **Assassino:** especializado em ataques rápidos e críticos.

## 📊 Atributos dos personagens

Cada personagem possuirá os seguintes atributos:

- **HP (Health Points):** pontos de vida.
- **MP (Mana Points):** pontos de mana.
- **Ataque:** determina o potencial de dano causado.
- **Defesa:** reduz o dano recebido.
- **Velocidade:** influencia a ordem de iniciativa.
- **Inteligência:** influencia habilidades mágicas.
- **Sorte:** influencia acontecimentos aleatórios durante as batalhas.

## ⚔️ Sistema de batalha

Durante seu turno, o jogador poderá realizar diferentes ações:

- Atacar inimigos.
- Defender-se.
- Utilizar habilidades.
- Consumir itens do inventário.

Ao vencer uma fase, a equipe receberá recompensas, como pontos para distribuir nos atributos, equipamentos e novas habilidades.

A campanha contará com três tentativas. Após três derrotas, a campanha será reiniciada.

## 🧩 Estruturas de dados

O projeto utilizará três estruturas de dados principais, implementadas em linguagem C:

| Estrutura | Aplicação |
|---|---|
| Fila | Controlar a ordem de iniciativa dos personagens e inimigos. |
| Lista encadeada ordenada | Organizar os itens do inventário alfabeticamente. |
| Pilha | Armazenar e controlar os efeitos temporários dos personagens. |

Também será utilizada uma pilha adicional para armazenar os estados anteriores da batalha, permitindo desfazer o último turno.

## 💾 Sistemas adicionais

- **Salvar e carregar:** permite armazenar e recuperar o progresso da campanha.
- **Log:** registra as ações realizadas durante os combates.
- **Replay:** permite reproduzir as ações registradas no histórico.
- **Aleatoriedade:** utilização de números aleatórios para determinar determinados valores e acontecimentos durante as partidas.
- **Desfazer turno:** permite recuperar o estado anterior da batalha.

## 🛠️ Tecnologias utilizadas

- Linguagem C
- Biblioteca Raylib
- Git e GitHub

## 📁 Organização do projeto

O código será organizado em módulos, separando as responsabilidades de cada funcionalidade para facilitar o desenvolvimento, a manutenção e o trabalho em equipe.

## 👥 Equipe

Projeto acadêmico desenvolvido em grupo para a disciplina de Algoritmos.

## 📌 Status do projeto

🚧 Em desenvolvimento.
