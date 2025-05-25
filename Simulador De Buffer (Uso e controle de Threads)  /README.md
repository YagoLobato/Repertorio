# INSTRUÇÕES DE COMPILAÇÃO E EXECUÇÃO
Este projeto C utiliza pthreads e semaphores (bibliotecas POSIX), e é compilado via Makefile.

# Para compilar e executar este código, você precisará de um ambiente que suporte as bibliotecas POSIX, como Linux.
Linux (Ubuntu/Debian, Fedora, etc.): Perfeito.
Windows: É fortemente recomendado usar o Windows Subsystem for Linux (WSL). A compilação direta no Windows com ferramentas como MinGW pode funcionar, mas é mais complexa devido às diferenças na implementação de pthreads e semaphores. Para a melhor experiência, opte pelo WSL.
macOS: Geralmente compatível, pois possui um ambiente baseado em UNIX.

# Certifique-se de ter as seguintes ferramentas instaladas em seu sistema:
Compilador C (GCC): O GNU Compiler Collection é essencial para compilar o código.
Make: A ferramenta make é usada para automatizar o processo de compilação através do Makefile.
Bibliotecas de Desenvolvimento POSIX: Incluem os cabeçalhos e as bibliotecas para pthreads e semaphores. Para a execução do código é necessário o uso de bibliotecas que não funcionam nativamete.

# Para executar a partir do terminal, após navegar até o diretório do projeto, basta usar o comando "make":
"make": compila as 4 versões do código
"make buffer_simples": compila a versão base do código (sem sincronizações)
"make A": compila a versão A
"make B": compila a versão B
"make C": compila a versão C

# E depois o seu executável:
./buffer_simples
./A
./B
./C

#Também é possível compilar e gerar um executável qualquer para cada um individualmente, basta utilizar gcc (nome do arquivo.c) e -o (nome do executavel). 
