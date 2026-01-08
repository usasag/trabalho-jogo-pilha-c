# 🎮 Torres de Hanói - Jogo Interativo em C

Um jogo clássico implementado em **C puro** com estrutura de dados **Pilha (Stack)**, completamente autossuficiente em um único arquivo compilável.

---

## 📋 Sumário

1. [Sobre o Jogo](#sobre-o-jogo)
2. [O que o Jogo Tem](#o-que-o-jogo-tem)
3. [Como Jogar](#como-jogar)
4. [Como Compilar e Executar](#como-compilar-e-executar)
5. [Estruturas de Dados Utilizadas](#estruturas-de-dados-utilizadas)
6. [Explicação Detalhada da Pilha](#explicação-detalhada-da-pilha)
7. [Arquitetura do Código](#arquitetura-do-código)
8. [Exemplos de Uso](#exemplos-de-uso)
9. [Requisitos](#requisitos)

---

## 🎯 Sobre o Jogo

**Torres de Hanói** é um quebra-cabeça matemático clássico que consiste em mover uma pilha de discos de um pino (Torre) para outro, seguindo regras específicas. O jogo é perfeito para demonstrar o uso prático de **estruturas de dados em pilha** e recursão.

### História
O jogo foi inventado pelo matemático francês Édouard Lucas em 1883. A lenda diz que monges budistas resolvem este quebra-cabeça em um templo com 64 discos de ouro. De acordo com o paradoxo do Fibonacci, quando terminarem, o universo chegará ao fim!

---

## ✨ O que o Jogo Tem

### Funcionalidades Principais

✅ **Menu de Dificuldade Interativo**
- Fácil (3 discos) - 7 movimentos mínimos
- Médio (4 discos) - 15 movimentos mínimos
- Difícil (5 discos) - 31 movimentos mínimos
- Extremo (6 discos) - 63 movimentos mínimos
- Customizado (1-10 discos)

✅ **Interface Gráfica em Terminal**
- Visualização das torres em tempo real com caracteres Unicode (█)
- Barras horizontais (═) representando a base
- Barras verticais (|) representando os pinos
- Status detalhado: número de discos em cada torre, total de movimentos

✅ **Sistema de Validação de Movimentos**
- Impede mover disco maior sobre disco menor
- Verifica torres vazias
- Valida entrada do usuário
- Mensagens de erro claras e informativas

✅ **Rastreamento de Pontuação**
- Conta total de movimentos realizados
- Calcula número mínimo teórico necessário (2^n - 1)
- Compara desempenho ao vencer

✅ **Recursos Especiais**
- Comando 'h' para visualizar instruções durante o jogo
- Comando 's' para sair graciosamente
- Feedback visual com emojis (✓, ❌, 🎉, 🌟)
- Verificação automática de vitória

---

## 🎮 Como Jogar

### Objetivo
Mover todos os discos da **Torre A** para a **Torre C**, utilizando a Torre B como auxiliar se necessário.

### Regras Fundamentais

1. **Apenas um disco pode ser movido por vez**
   - Você remove apenas o disco do topo de uma torre

2. **Nunca coloque um disco maior sobre um disco menor**
   - Esta é a restrição principal do quebra-cabeça

3. **Use qualquer torre intermediária necessária**
   - A Torre B pode ser usada como área de armazenamento temporário

### Passo a Passo para Jogar

```
1. Execute o programa
2. Escolha um nível de dificuldade (1-5)
3. Leia as instruções
4. Pressione ENTER para começar
5. Digite movimentos no formato: ORIGEM DESTINO
   Exemplo: A C (move um disco de A para C)
6. Use 'h' para ajuda, 's' para sair
7. Complete quando todos os discos estiverem em C
```

### Exemplo de Partida (3 discos)

```
Estado Inicial:
  Torre A: [1, 2, 3]  (3 no topo)
  Torre B: []
  Torre C: []

Movimentos sugeridos:
1. A B  (move disco 1 de A para B)
2. A C  (move disco 2 de A para C)
3. B C  (move disco 1 de B para C)
4. A B  (move disco 3 de A para B)
5. C A  (move disco 1 de C para A)
6. C B  (move disco 2 de C para B)
7. A B  (move disco 1 de A para B)

Total: 7 movimentos (número mínimo possível)
```

---

## 🔧 Como Compilar e Executar

### Compilação Simples

```bash
gcc -o hanoi hanoi_game.c
```

### Compilação com Flags de Otimização

```bash
gcc -O2 -Wall -Wextra -o hanoi hanoi_game.c
```

**Flags explicadas:**
- `-O2`: Otimização de nível 2 para melhor desempenho
- `-Wall`: Mostra todos os warnings
- `-Wextra`: Mostra warnings adicionais
- `-o hanoi`: Nome do executável resultante

### Execução

```bash
./hanoi
```

**Ou no Windows (usando MinGW):**
```bash
gcc -o hanoi.exe hanoi_game.c
hanoi.exe
```

---

## 🏗️ Estruturas de Dados Utilizadas

### 1. Estrutura Principal: PILHA (Stack)

Uma pilha é uma estrutura de dados **LIFO (Last In, First Out)**, onde o último elemento inserido é o primeiro a ser removido.

```c
typedef struct {
    int discos[MAX_PILHA];  // Array para armazenar elementos
    int topo;               // Índice do elemento no topo (-1 = vazio)
} Pilha;
```

**Características:**
- Acesso limitado: apenas no topo
- Operações O(1): inserção e remoção constantes
- Ideal para "undo/redo", navegação, e parsing

### 2. Estrutura de Controle do Jogo

```c
typedef struct {
    Pilha torres[3];      // 3 pilhas: A, B, C
    int num_discos;       // Número total de discos
    int movimentos;       // Contador de movimentos
} Jogo;
```

---

## 📚 Explicação Detalhada da Pilha

### Operações Fundamentais

#### **1. Inicializar (Criar Pilha Vazia)**

```c
void pilha_inicializar(Pilha *p) {
    p->topo = -1;  // -1 significa pilha vazia
}
```

**O que faz:** Define a pilha como vazia, setando o índice `topo` para -1.

---

#### **2. Empilhar (Push) - Adicionar Elemento**

```c
int pilha_empilhar(Pilha *p, int disco) {
    if (pilha_cheia(p)) {
        printf("Erro: Pilha cheia!\n");
        return 0;
    }
    p->discos[++(p->topo)] = disco;  // Incrementa topo e insere
    return 1;
}
```

**Exemplo prático:**
```
Antes:  topo = 1, discos = [3, 2, ?, ?]
Operação: pilha_empilhar(&torres[0], 1)
Depois:  topo = 2, discos = [3, 2, 1, ?]
```

**Operações:** O(1) - Tempo constante

---

#### **3. Desempilhar (Pop) - Remover Elemento**

```c
int pilha_desempilhar(Pilha *p) {
    if (pilha_vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        return -1;
    }
    return p->discos[(p->topo)--];  // Retorna e decrementa topo
}
```

**Exemplo prático:**
```
Antes:  topo = 2, discos = [3, 2, 1, ?]
Operação: pilha_desempilhar(&torres[0])
Depois:  topo = 1, discos = [3, 2, 1, ?]
Retorno: 1 (o valor que estava no topo)
```

**Complexidade:** O(1) - Tempo constante

---

#### **4. Consultar Topo (Peek)**

```c
int pilha_topo(Pilha *p) {
    if (pilha_vazia(p)) {
        return -1;
    }
    return p->discos[p->topo];  // Retorna sem remover
}
```

**Diferença importante:** Ao contrário de `desempilhar()`, `topo()` não remove o elemento, apenas consulta.

---

#### **5. Verificações Utilitárias**

```c
int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

int pilha_cheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int pilha_tamanho(Pilha *p) {
    return p->topo + 1;
}
```

### Por Que Usar Pilha para Torres de Hanói?

| Requisito | Propriedade da Pilha |
|-----------|---------------------|
| Só mexer no topo | LIFO (Last In, First Out) |
| Não acessar elemento do meio | Acesso restrito ao topo |
| Rápido inserir/remover | O(1) para push/pop |
| Fácil controlar ordem | Estrutura ordenada naturalmente |

---

## 🏛️ Arquitetura do Código

### Organização Modular

```
hanoi_game.c
│
├── DEFINIÇÕES E TIPOS
│   ├── #define MAX_DISCOS, MAX_PILHA
│   └── typedef Pilha, Jogo
│
├── FUNÇÕES DA PILHA (Camada 1)
│   ├── pilha_inicializar()
│   ├── pilha_vazia()
│   ├── pilha_cheia()
│   ├── pilha_empilhar()
│   ├── pilha_desempilhar()
│   ├── pilha_topo()
│   └── pilha_tamanho()
│
├── FUNÇÕES DO JOGO (Camada 2)
│   ├── jogo_inicializar()
│   ├── jogo_exibir()
│   ├── jogo_mover()
│   ├── jogo_venceu()
│   └── movimentos_minimos()
│
├── FUNÇÕES DE INTERFACE (Camada 3)
│   ├── exibir_instrucoes()
│   └── menu_dificuldade()
│
└── FUNÇÃO PRINCIPAL
    └── main() - Loop principal do jogo
```

### Fluxo de Execução

```
START
  │
  ├─→ Exibe boas-vindas
  │
  ├─→ menu_dificuldade()
  │     └─→ Retorna número de discos
  │
  ├─→ jogo_inicializar()
  │     └─→ Cria 3 pilhas vazias
  │     └─→ Empilha discos em ordem na Torre A
  │
  ├─→ exibir_instrucoes()
  │
  └─→ LOOP PRINCIPAL (enquanto não vencer):
        │
        ├─→ jogo_exibir()
        │     ├─→ Mostra torres graficamente
        │     └─→ Status do jogo
        │
        ├─→ jogo_venceu()? SIM → Vitória!
        │
        ├─→ Lê entrada do usuário
        │
        ├─→ jogo_mover() ou comando especial
        │     └─→ Valida movimento
        │     └─→ Empilha/desempilha
        │     └─→ Incrementa contador
        │
        └─→ Volta ao topo do loop

FIM
```

---

## 💡 Exemplos de Uso

### Exemplo 1: Jogar com 3 Discos (Fácil)

```
Escolha: 1
Discos: 3
Mínimo: 7 movimentos

>>> A B
✓ Moveu disco 1 de A para B

>>> A C
✓ Moveu disco 2 de A para C

>>> B C
✓ Moveu disco 1 de B para C

>>> A B
✓ Moveu disco 3 de A para B

>>> C A
✓ Moveu disco 1 de C para A

>>> C B
✓ Moveu disco 2 de C para B

>>> A B
✓ Moveu disco 1 de A para B

🎉 PARABÉNS! VOCÊ VENCEU! 🎉
Movimentos: 7
Resultado: PERFEITO! 🌟
```

### Exemplo 2: Movimento Ilegal

```
Estado: Torre A tem [3,2], Torre C vazia

>>> A C
✓ Moveu disco 2 de A para C

>>> A C
❌ Movimento ilegal! Disco maior sobre menor!
   Você tentou mover disco 3 sobre disco 2
```

### Exemplo 3: Torre Vazia

```
>>> B A
❌ A torre B está vazia!
```

---

## 📦 Requisitos

### Sistema Operacional
- Linux
- macOS
- Windows (com MinGW ou Cygwin)

### Compilador
- GCC (GNU Compiler Collection)
- Clang
- Microsoft Visual C++

### Dependências
- Apenas bibliotecas padrão do C:
  - `stdio.h` - Entrada/Saída
  - `stdlib.h` - Utilitários gerais
  - `string.h` - Manipulação de strings
  - `ctype.h` - Classificação de caracteres

### Características de Suporte
- Terminal com suporte a Unicode (para caracteres ═, █, │)
- Mínimo: terminal básico (funciona mesmo sem Unicode)

---

## 🧮 Análise Matemática

### Fórmula de Movimentos Mínimos

Para N discos, o número mínimo de movimentos é:

$$\text{Movimentos Mínimos} = 2^N - 1$$

**Exemplos:**
- 1 disco: 2^1 - 1 = **1** movimento
- 2 discos: 2^2 - 1 = **3** movimentos
- 3 discos: 2^3 - 1 = **7** movimentos
- 4 discos: 2^4 - 1 = **15** movimentos
- 5 discos: 2^5 - 1 = **31** movimentos
- 6 discos: 2^6 - 1 = **63** movimentos
- 10 discos: 2^10 - 1 = **1023** movimentos
- 64 discos: 2^64 - 1 = **18,446,744,073,709,551,615** movimentos!

### Complexidade de Tempo

| Operação | Complexidade |
|----------|-------------|
| Empilhar | O(1) |
| Desempilhar | O(1) |
| Verificar topo | O(1) |
| Verificar vitória | O(N) - onde N é número de discos |
| Movimento completo | O(1) |

### Complexidade de Espaço

- **Estrutura de Pilha:** O(N) - onde N é o número máximo de discos
- **Estrutura de Jogo:** O(3N) = O(N) - três pilhas independentes

---

## 🎓 Conceitos Aprendidos

Ao estudar este código, você aprenderá sobre:

1. **Estruturas de Dados**
   - Implementação de pilha com array
   - Operações LIFO (Last In, First Out)

2. **Programação em C**
   - Definição de structs
   - Passagem de ponteiros
   - Alocação estática vs dinâmica

3. **Algoritmos**
   - Validação de movimentos
   - Rastreamento de estado do jogo
   - Cálculo de números mínimos

4. **Design de Interface**
   - Tratamento de entrada do usuário
   - Visualização de estruturas de dados
   - Feedback ao usuário

5. **Boas Práticas**
   - Comentários descritivos
   - Nomes de função claros
   - Separação de responsabilidades
   - Tratamento de erros

---

## 🚀 Possíveis Expansões

1. **Adicionar Dificuldade Progressiva**
   - Tempo limite para cada movimento
   - Limite de movimentos permitidos

2. **Sistema de Salvamento**
   - Salvar/carregar posição do jogo
   - Histórico de movimentos

3. **Modo Resolução Automática**
   - Algoritmo recursivo que resolve automaticamente
   - Visualização do passo a passo

4. **Estatísticas**
   - Rastreamento de melhores tempos
   - Contador de partidas ganhas

5. **Multiplayer**
   - Competição entre dois jogadores
   - Modo de turnos

---

## 📖 Referências

- **Livro:** "Introduction to Algorithms" - Cormen, Leiserson, Rivest, Stein
- **Estruturas de Dados:** "Data Structures and Program Design in C" - Kruse et al.
- **Wikipedia:** https://en.wikipedia.org/wiki/Tower_of_Hanoi
- **Matemática:** https://en.wikipedia.org/wiki/Powers_of_2

---

## 📝 Licença

Este projeto é fornecido como material educacional. Sinta-se livre para usar, modificar e distribuir.

---

## 👨‍💻 Autor

Desenvolvido como demonstração prática de **estruturas de dados em C** e **boas práticas de programação**.

**Data:** Janeiro de 2026

---

## ❓ Dúvidas Frequentes

### P: Por que usar -1 para indicar pilha vazia?
**R:** Porque os índices válidos são 0 a (MAX_PILHA-1). O -1 é um sentinela que claramente indica "sem elementos".

### P: Posso adicionar mais de 10 discos?
**R:** Sim! Modifique `MAX_DISCOS` no código. Porém, o tempo de resolução crescerá exponencialmente (2^N).

### P: Qual é a melhor estratégia para resolver?
**R:** Existem algoritmos recursivos eficientes. O padrão é: mover N-1 discos para B, mover maior para C, mover N-1 de B para C.

### P: Por que a pilha usa array e não lista ligada?
**R:** Array é mais simples, rápido e suficiente para este caso. Lista ligada seria útil com tamanho variável.

### P: Posso adaptar para outros jogos?
**R:** Sim! A estrutura de pilha é útil para: undo/redo, calculadora (notação polonesa reversa), análise sintática, etc.

---

**Divirta-se jogando! 🎮**
