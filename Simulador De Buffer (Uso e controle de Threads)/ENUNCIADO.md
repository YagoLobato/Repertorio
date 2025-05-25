# 🧪 Prática de Laboratório: Teste e Depuração de Código Concorrente

**Disciplina:** ICC014 – Laboratório de Programação Avançada  
 

## 🎯 Objetivo Geral
Avaliar diferentes técnicas de depuração e sincronização em programas concorrentes com condições de corrida, por meio de diagnóstico e correção de erros usando ferramentas e abordagens clássicas:

- Correção usando: **mutexes**, **semáforos POSIX** e **monitores** (`pthread_cond_t`)

---

## 🧩 Parte 1 – Código base

Você receberá o código `buffer_simples.c`, que simula um buffer circular com um produtor e um consumidor. O código **não possui sincronização**, o que pode gerar **condições de corrida**.

---

## 🔍 Parte 2 – Diagnóstico com Técnicas

### 1. Instrumentação Manual
Use `printf()` para rastrear comportamentos incorretos.

### 2. Valgrind Helgrind
Execute:
```bash
valgrind --tool=helgrind ./buffer_simples
```

### 3. Testes Determinísticos
Adicione `sleep()` ou use `pthread_barrier_t` para testar execuções ordenadas.

### 4. Tracing e Profiling
Use `strace`, `perf`, ou `gprof` para observar desempenho e chamadas ao sistema.

---

## 🔧 Parte 3 – Correções com Mecanismos de Sincronização

### ✅ Versão A – Mutex
Use `pthread_mutex_t` para proteger `in`, `out`, `count`.

### ✅ Versão B – Semáforos
Use `sem_t` com:
- `sem_vazio`
- `sem_cheio`
- `sem_mutex`

### ✅ Versão C – Monitor (mutex + condição)
Implemente um monitor com `pthread_mutex_t` + `pthread_cond_t`.

---

## ✅ Parte 4 – Entrega

Entregue os seguintes arquivos:

1. Código original + versões A, B, C
2. Relatório (máx. 1 página) respondendo:
   - Quais problemas foram detectados?
   - Qual técnica foi mais eficaz?
   - Qual sincronização foi mais fácil de usar?
   - Houve diferença de desempenho?
3. Prints ou logs das execuções e testes

---

## 🛠️ Compilação

```bash
gcc -Wall -g -pthread buffer_simples.c -o buffer_simples
```

Use `make` para facilitar a compilação se desejar.
---
