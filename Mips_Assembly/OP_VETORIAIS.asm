.data
tamanho: .word 5
vetor1: .space 20
vetor2: .space 20   
vetor_soma: .space 20
vetor_escalado: .space 20  
msg_1:  .asciiz "Digite os elementos dos 2 vetores: \n"
msg_2:  .asciiz "Vetor 1 \n"
msg_3:  .asciiz "Vetor 2 \n"
msg_4:  .asciiz "Digite um elemento: "
msg_5: .asciiz "Produto vetorial: "
msg_6: .asciiz "Vetor Soma: "
msg_7: .asciiz "Insira um valor escalar: "
msg_8: .asciiz "Vetores escalados: \n"
quebra_linha: .asciiz "\n"
linha:  .asciiz "______________________________________________________________________________________________________________________________________________________________________________________________\n"

.text
main:
    lw $t2, tamanho
    
    li $v0, 4             
    la $a0, linha
    syscall
    
    li $v0, 4            
    la $a0, quebra_linha            
    syscall
    
    li $v0, 4             
    la $a0, msg_1
    syscall
  
#inicializa vet1   
    li $v0, 4             
    la $a0, msg_2
    syscall
	
    la $a0, vetor1    
    jal inicializa_vet   

#inicializa vet2
    li $v0, 4
    la $a0, msg_3
    syscall
    
    la $a0, vetor2    
    jal inicializa_vet        
	
#imprime os vetores
    li $v0, 4            
    la $a0, quebra_linha            
    syscall
    
    li $v0, 4             
    la $a0, msg_2
    syscall
    
    la $a0, vetor1   
    jal imprime_vet   
    
    li $v0, 4            
    la $a0, quebra_linha            
    syscall
    
    li $v0, 4
    la $a0, msg_3
    syscall
    
    la $a0, vetor2   
    jal imprime_vet     
    
    li $v0, 4            
    la $a0, quebra_linha            
    syscall
    
    #calcula Produto Vetorial
    la $a0, vetor1
    la $a1, vetor2
    jal produto_vetorial
    move $t0, $v0
    
    li $v0, 4
    la $a0, msg_5
    syscall
    
    li $v0, 1
    move $a0, $t0
    syscall
  	
    li $v0, 4            
    la $a0, quebra_linha            
    syscall
    
    #calcula vetor1 + vetor2
    li $v0, 4            
    la $a0, quebra_linha            
    syscall
     
    la $a0, vetor1
    la $a1, vetor2
    #jal soma_vetores
    
    li $v0, 4
    la $a0, msg_6
    syscall
    
    la $a0, vetor_soma
    jal imprime_vet
    
    #calcula escalar N x vetor1 e N x vetor2
    li $v0, 4            
    la $a0, quebra_linha            
    syscall
     
    li $v0, 4
    la $a0, msg_7
    syscall
    
    li $v0, 5 
    syscall   #lendo o escalar do terminal
    move $a3, $v0
    
    # calcula o vetor escalado do vet 1 e imprime dps
    li $v0, 4
    la $a0, msg_8
    syscall
    
    li $v0, 4
    la $a0, msg_2
    syscall
    
    la $a0, vetor1
    #jal produto_escalar
    
    la $a0, vetor_escalado
    jal imprime_vet

    li $v0, 4            
    la $a0, quebra_linha            
    syscall
    
    #Agora o vetor escalar do vet 2 e imprime
    li $v0, 4
    la $a0, msg_3
    syscall
    
    la $a0, vetor2
    #jal produto_escalar
    
    la $a0, vetor_escalado
    jal imprime_vet
    
    # fim do codigo
    li $v0, 4            
    la $a0, quebra_linha            
    syscall
    
    li $v0, 4             
    la $a0, linha
    syscall
    
    j exit
    
    
                                                                                   
#inicializa_vet(int* vet)
#Guarde o endereco do vetor a ser inicializado em $a0 antes de chamar a funcao      EX: la $a0, vetor1 
#Inicializa o vetor do argumento com entradas do terminal.                          #   jal inicializa_vet
             
inicializa_vet:
    li $t0, 0          
    move $t1, $a0 
    
laco_ini:
    bge $t0, $t2, fim_laco_ini 
   
    li $v0, 4            
    la $a0, msg_4
    syscall

    li $v0, 5            
    syscall
    sw $v0, ($t1)        

    addi $t1, $t1, 4       
    addi $t0, $t0, 1  
    j laco_ini
        
fim_laco_ini:   
    jr $ra

#imprime_vet(int* vet)
#Guarde o endereco do vetor a ser impresso em $a0 antes de chamar a funcao      EX: la $a0, vetor_soma
#Imprime o vetor do argumento                                                   #   jal imprime_vet
imprime_vet:
    li $t0, 0          
    move $t1, $a0 
    
print_loop:
    bge $t0, $t2, fim_loop 
    
    lw $a0, ($t1)         
    li $v0, 1            
    syscall       
	
    li $v0, 11             
    li $a0, 32             # ASCII para ' '
    syscall

    addi $t1, $t1, 4       
    addi $t0, $t0, 1       

    j print_loop
fim_loop:
    li $v0, 4             
    la $a0, quebra_linha            
    syscall
    
    jr $ra


#produto_vetorial(int* vet1, int* vet2)
#Guarde o endereco dos vetores em $a0 e $a1 antes de chamar a funcao           EX: la $a0, vetor1
#Calcula o produto vetorial de dois vetores e "retorna" o retultado em $v0     #   la $a1, vetor2
					                                       #   jal produto_vetorial
produto_vetorial:
    move $t1, $a0
    move $t3, $a1
    li $v0, 0
    li $t4, 0
    
loop_prod_vet:
    bge $t4, $t2, fim_loop_prod_vet
    
    lw $t6, ($t1) #$t6 e $t7 recebem os elementos dos vetores
    lw $t7, ($t3)
    mul $t5, $t6, $t7 
    add $v0, $v0, $t5 #incrementa o $v0
    
    addi $t4, $t4, 1
    addi $t1, $t1, 4
    addi $t3, $t3, 4
    
    j loop_prod_vet
fim_loop_prod_vet:
    jr $ra
 
#soma_vetores(int* vet1, int* vet2)
#Guarde o endereco dos vetores em $a0 e $a1 antes de chamar a funcao                         EX: la $a0, vetor1
#Calcula o vetor soma resultante de dois vetores e "retorna" os retultados em vetor_soma     #   la $a1, vetor2
					                                                     #   jal soma_vetores    
soma_vetores:
    move $t1, $a0 #vet1
    move $t3, $a1 #vet2
    li $t0, 0
    la $t4, vetor_soma
    
loop_soma:
    #bota aqui a condicao natha, lembra de usar o link "fim_loop_soma" no desvio
    #faz o vetor_soma($a3) receber as somas dos elementos
    
    j loop_soma
fim_loop_soma:
    jr $ra    

#produto_escalar(int* vet, int escalar)
#Guarde o endereco do vetor em $a0 e o escalar em $a3 antes de chamar a funcao                                 EX:  la $a0, vetor1
#Calcula o vetor escalado e "retorna" os retultados em vetor_escalado     			                #   move $a3, $v0
					                                                                        #   jal produto_escalar
produto_escalar:
    move $t1, $a0 #vet
    move $t3, $a3 #escalar
    la $t4, vetor_escalado
    li $t0, 0 
loop_escalar:
    #bota aqui a condicao Daniel, lembra de usar o link "fim_loop_escalar" no desvio
    #faz o vetor_escalado($t4) receber os elementos multiplicados pelo escalar ($t3)
    
    
    j loop_escalar
fim_loop_escalar:
    jr $ra 
    
#finalizador do programa                                                                                    
exit: 
    li $v0, 10
    syscall

