//Trabalho final de Fup - Sistema Gerenciador de Tarefas

#include <ctype.h>        //biblioteca para manipular caracteres
#include <locale.h>       //biblioteca para permitir acentuação
#include <stdio.h>        //biblioteca para permitir entrada e saída padrão
#include <stdlib.h>       //biblioteca para permitir alocação de memória
#include <string.h>       //biblioteca para manipular vetores de caracteres
#define MAX_TAREFAS 5
                          //definição de tarefas por usuário



typedef struct{           //tipo estruturado para a data de criacão da tarefa
char dia[3];              //string para armazenar dia da data de criação
char mes[3];              //string para armazenar mes da data de criação
char ano[5];              //string para armazenar ano da data de criação
}data;                    //nome do tipo estruturado


typedef struct{           //tipo estruturado para data de conclusão da tarefa
char dia[3];              //string para armazenar dia da data de conclusão
char mes[3];              //string para armazenar mes da data de conclusão
char ano[5];              //string para armazenar ano da data de conclusão
}data_conclusao;          //nome do tipo estruturado

typedef struct{           //Tipo estruturado para dados da tarefa
char id[9];               //string para armazenar ID
char titulo[100];         //string para armazenar titulo
char descricao[1000];     //string para armazenar descrição
data Data_de_criacao;     //variável do tipo data
data_conclusao Data_de_conclusao;//variável do tipo data de conclusão
char prioridade[10];      //string para armazenar titulo
char responsavel[100];    //string para armazenar titulo
char status[50];          //string para armazenar titulo
}Tarefa;                  //nome do tipo estruturado

typedef struct {          //tipo estruturado para dados do usúario
char nome[100];           //string para armazenar nome
char senha[15];           //string para armazenar senha
Tarefa tarefas;           //variável do tipo Tarefa
}usuario;                 //nome do tipo estruturado

void limparBuffer();      //Função para limpar o buffer
void cadastro();          //protótipo função cadastro
void login();             //protótipo função login
void cadastroTarefa();    //protótipo da função de criar tarefa
void editarTarefa();      //protótipo da função de edição dos campos das tarefas
void excluirTarefa();     //protótipo da função excluir tarefas
void listarUsuTarefa();   //protótipo da função de listagem das tarefas do usuário
void listarPrioTarefa();  //protótipo da função de listagem da tarefa por prioridade
void listarTituTarefa();  //protótipo da função de listagem da tarefa por título
void exibirIDTarefa();    //protótipo da função exibição de tarefas por ID
void exibirTafConcluida();//protótipo da função exibição de tarefas concluidas do usuário
void RelatarTarefa();     //protótipo da função relatario de Tarefas

int main() {
  setlocale(LC_ALL,"Portuguese");   //Função usada para a utilização do português nos textos
  usuario Usuarios;                 //vetor que armazena dados de até 10 usuários
  int Opcao;                        //variável que armazena a opcão do usuário entre cadastro ou login
  char Usuario_login[100];          // vetor que armazena até 100 caracteres do usuário
  char Senha_login[15];             // vetor que armazena até 15 caracteres do usuário
  char linha[100];                  //string para armazenar dados quando for acessar o arquivo
  FILE *file = fopen("Usuarios.txt","r");//abre o arquivo para leitura
  int count=0;                      //declaração de variável contadora
while(1){                           // Loop infinito, executa até ser interrompido por um break
printf("\n\t\t==============================================================================\n\t\t======================= SISTEMA GERENCIADOR DE TAREFAS =======================\n\t\t==============================================================================\n\n"); //mostra um cabeçalho do software na tela inicial
    printf("\t\t\t\t\t======= Cadastre-se =======\n\t\t\t\t======= Já possui conta? Faça o login =======\n"); // mostra opções para cadastrar ou fazer login
    printf("[1]:Cadastrar novo usuario\n");                                                  //mostra opção para cadastrar novo usuário
    printf("[2]:Login\n");                                                                   // mostra opção para fazer login
    printf("[3]:Sair\n");                                                                    // mostra opção para sair do programa
    printf("Selecione: ");                                                                 //pede que o usuário escolha uma opção
scanf("%d", &Opcao);                                                                       //lê opção escolhida pelo usuário
limparBuffer();


switch(Opcao){
case 1:
      while (fgets(linha, sizeof(linha), file)!=NULL){ // Contador do número de usuários com base na linhas do arquivo
        count++;
      }
      fclose(file);                                    //fecha o arquivo para evitar problemas futuros
      if(count<10){                                    // Verifica se o número de usuários é menor que 10
      cadastro(&Usuarios);                             //se sim, chama a função de cadastro de novo usuário
      break;                                           //sai do switch
      }else if(count==10){                             //Verifica se o número de usuários é igual a  10
      printf("==== Numero maximo de usuarios atingidos ====");//mostra que atingiu o limite de usuários
      continue;                                        //continua o loop
      }
case 2:
      system("cls");                                    //função para limpar o terminal
      printf("\t\t\t\t========= Login =========\n");
      printf("Digite seu nome de usuario cadastrado: "); // Solicita o nome de usuário cadastrado
      fgets(Usuario_login, 100, stdin);                  //lê nome do usuário
      Usuario_login[strcspn(Usuario_login, "\n")] = '\0';//substitui o \n por \0 na string Usuario_login para garantir que a string não tenha quebra de linha
      printf("Digite sua senha: ");                      //solicita senha
      fgets(Senha_login, 15, stdin);                     //lê senha
      Senha_login[strcspn(Senha_login, "\n")] = '\0';    //substitui o \n por \0 na string senha_login para garantir que a string não tenha quebra de linha
      login(&Usuarios, Usuario_login, Senha_login);      // chama a função login
      continue;                                          //continua o loop
case 3:
    return 0;                                            // termina o programa
    }
  }
}

void limparBuffer(void){                                 //Função para limpar o buffer
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

void cadastro(usuario *uPtr) {                                          //função para cadastrar os usuários
  system("cls");                                                        //função para limpar o terminal
  int senhaValida = 0;                                                  //declaração de variável contadora
  int Selecionar_opcoes;                                                //declaração de variável para armazenar opção do usuário de manipular as tarefas

  printf("\t\t\t\t========= Cadastro de um novo usuário =========\n");
  printf("Digite o nome do novo usuario: ");                            // Solicita o nome do novo usuário
  fgets(uPtr->nome, 100, stdin);                                        //lê o nome
  uPtr->nome[strcspn(uPtr->nome, "\n")] = '\0';                         //substitui o \n por \0 na string nome para garantir que a string não tenha quebra de linha
  limparBuffer();
  printf("Requisitos para a senha:\nDeve ter entre 4 e 10 caracteres de tamanho.\nAo menos 1 letra maiúscula.\nAo menos 1 número.\nAo menos 1 caractere especial.\n");//informa os requisitos da senha ao usuário
    printf("Digite a senha: ");                                        //solicitação de senha
  fgets(uPtr->senha, 15, stdin);                                       //lê senha
  uPtr->senha[strcspn(uPtr->senha, "\n")] = '\0';                      //substitui o \n por \0 na string senha para garantir que a string não tenha quebra de linha
  limparBuffer();
  while(1){                                                            // Loop infinito, executa até ser interrompido por um break para Verificar os requisitos da senha
    if (strlen(uPtr->senha) >= 4){
      if(strlen(uPtr->senha) <= 10){                                  //verifição para garantir o tamanho da senha
        senhaValida++;
      }
    }

    for (int i = 0; i < strlen(uPtr->senha); i++) {                   // Verifica se há pelo menos uma letra maiúscula na senha
      if (isupper(uPtr->senha[i])) {
        senhaValida++;
        break;
      }
    }

    for (int i = 0; i < strlen(uPtr->senha); i++) {                   // Verifica se há pelo menos um número na senha
      if (isdigit(uPtr->senha[i])) {
        senhaValida++;
        break;
      }
    }

    for (int i = 0; i < strlen(uPtr->senha); i++) {                // Verifica se há pelo menos um caractere especial na senha
      if (!isalnum(uPtr->senha[i])){
        senhaValida++;
        break;
      }
    }

    if (senhaValida != 4) {                                      //se variável contadora for diferente de 4, então significa que a senha não atendeu todos os requisitos
      printf("\n==== Senha invalida! =====\nDigite novamente: ");//solicita senha novamente
      fgets(uPtr->senha, 15, stdin);                             //lê senha
      uPtr->senha[strcspn(uPtr->senha, "\n")] = '\0';            //substitui o \n por \0 na string senha para garantir que a string não tenha quebra de linha
    }
    if (senhaValida != 4) {                           //se variável contadora for diferente de 4, então declara ela como zero para que ela faça possa contar os requisitos na próxima repetição
      senhaValida = 0;
    }
    else if(senhaValida==4){                          //se senha válida, faz o cadastro do usuário
    FILE *file= fopen("Usuarios.txt", "a");           //abre o arquivo no modo de acrescentar conteúdo ao final do arquivo
    fprintf(file,"%s,%s\n",uPtr->nome,uPtr->senha);   //escreve o nome e a senha do usuário no arquivo
    printf("\n==== Usuario Cadastrado com sucesso! ====\n");
    fclose(file);                                      //fecha o arquivo
    break;                                             //interrompe o loop infinito
    }
    }
  system("cls");                                       //função para limpar o terminal
  printf("Usuário: %s ========================================", uPtr->nome);//mostra o nome do usuário ja cadastrado
  while(1){
  printf("\n[1]: Criar tarefa\n");                        // Mostra opção para criar tarefa
  printf("[2]: Editar tarefa\n");                         // Mostra opção para editar tarefa
  printf("[3]: Excluir tarefa\n");                        // Mostra opção para excluir tarefa
  printf("[4]: Listar tarefa por ID\n");                  // Lista a tarefa por id
  printf("[5]: Listar tarefa do usuario\n");              // Lista a terefa por usuário
  printf("[6]: Listar tarefa por prioridade\n");          // Lista as tarefas por prioridade
  printf("[7]: Listar tarefa por titulo\n");              // Lista a tarefa por título
  printf("[8]: Listar tarefas concluidas\n");             // Lista as tarefas concluídas
  printf("[9]: Estatisticas das tarefas\n");              // mostra opção para ver estatísticas das tarefas
  printf("Escolha uma opcao: ");                        //solicita uma opção
  scanf("%d",&Selecionar_opcoes);                       //lê opção
  limparBuffer();
  switch(Selecionar_opcoes){
  case 1:
  cadastroTarefa(uPtr->tarefas,uPtr->nome);            // Chama a função para cadastrar uma nova tarefa
  break;
  case 2:
  editarTarefa(uPtr->tarefas,uPtr->nome);              // Chama a função para editar uma tarefa existente
  break;
  case 3:
  excluirTarefa(uPtr->tarefas,uPtr->nome);             // Chama a função para excluir uma tarefa
  break;
  case 4:
  exibirIDTarefa(&uPtr->tarefas,&uPtr->nome);          //Chama a função para exibir tarefa por ID
    break;
  case 5:
  listarUsuTarefa(&uPtr->tarefas,&uPtr->nome);       // Chama a função para listar as tarefas do usuário logado
  break;
  case 6:
  listarPrioTarefa(&uPtr->tarefas,&uPtr->nome);        //Chama a função para exibir tarefa por prioridade
  break;
  case 7:
  listarTituTarefa(&uPtr->tarefas,&uPtr->nome);        //Chama a função para exibir tarefa por Título
  break;
  case 8:
  exibirTafConcluida(&uPtr->tarefas,&uPtr->nome);      //Chama a função para exibir tarefas concluídas
    break;
  case 9:
  RelatarTarefa(&uPtr->tarefas,&uPtr->nome);         // Chama a função para exibir estatísticas das tarefas
  break;
  }
}
}

void login(usuario *uPtr, char usu[], char sen[]) {    //função para fazer o login do usuário
  char linha[100];                                     //string para armazenar dados quando for acessar o arquivo
  int cont=0;                                          //declaração de variável contadora
  FILE *file=fopen("Usuarios.txt","r");                //abre o arquivo no modo leitura
  while (fgets(linha, sizeof(linha), file)!=NULL){     //lê uma linha do arquivo e armazena na string linha e o loop continua enquanto há linhas restantes para ler no arquivo
  sscanf(linha,"%[^,],%s",uPtr->nome,uPtr->senha);     //lê o nome até a virgula e senha até espaço em branco da string linha
  if(strcmp(uPtr->nome,usu)==0&&strcmp(uPtr->senha,sen)==0){ //compara se senha e usuário no cadastro e login são iguais
  cont=1;                                              //se sim, atribui 1 a variável contadora que indica um login válido
  fclose(file);                                        // Fecha o arquivo
  break;                                               // Sai do loop
  }
  }
  if(cont==1){                                        //se variável contadora igual a 1, indica um login válido e mostra as opções de manipulação de tarefas
  int Selecionar_opcoes;                              //solicita uma opção do usuário
while(1){
  printf("Usuário: %s ========================================", uPtr->nome);//mostra o nome do usuário logado
  printf("\n[1]: Criar tarefa\n");                      // mostra opção para criar tarefa
  printf("[2]: Editar tarefa\n");                       // mostra opção para editar tarefa
  printf("[3]: Excluir tarefa\n");                      // mostra opção para excluir tarefa
 printf("[4]: Listar tarefa por ID\n");                 // Lista a tarefa por id
  printf("[5]: Listar tarefa do usuario\n");            // Lista a tarefa por usuário
  printf("[6]: Listar tarefa por prioridade\n");         // Lista a tarefa por prioridade
  printf("[7]: Listar tarefa por titulo\n");            // Lista a tarefa por título
  printf("[8]: Listar tarefas concluidas\n");           // Lista a/as tarefas concluídas
  printf("[9]: Estatisticas das tarefas\n");            // mostra opção para ver estatísticas das tarefas
  printf("Escolha uma opcao: ");                      //solicita uma opção
  scanf("%d",&Selecionar_opcoes);                     //lê opção
  limparBuffer();
  switch(Selecionar_opcoes){
  case 1:
  cadastroTarefa(&uPtr->tarefas,&uPtr->nome);        // Chama a função para cadastrar uma nova tarefa para o usuário logado
  break;
  case 2:
  editarTarefa(&uPtr->tarefas,&uPtr->nome);          // Chama a função para editar uma tarefa existente
  break;
  case 3:
  excluirTarefa(&uPtr->tarefas,&uPtr->nome);         // Chama a função para excluir uma tarefa
  break;
  case 4:
  exibirIDTarefa(&uPtr->tarefas,&uPtr->nome);        //Chama a função para exibir tarefa por ID
    break;
  case 5:
  listarUsuTarefa(&uPtr->tarefas,&uPtr->nome);       // Chama a função para listar as tarefas do usuário logado
  break;
  case 6:
  listarPrioTarefa(&uPtr->tarefas,&uPtr->nome);      //Chama a função para exibir tarefa por prioridade
    break;
  case 7:
  listarTituTarefa(&uPtr->tarefas,&uPtr->nome);      //Chama a função para exibir tarefa por Título
    break;
  case 8:
  exibirTafConcluida(&uPtr->tarefas,&uPtr->nome);    //Chama a função para exibir tarefas concluídas
    break;
  case 9:
  RelatarTarefa(&uPtr->tarefas,&uPtr->nome);         // Chama a função para exibir estatísticas das tarefas
  break;
  }
  }
  }

  if(cont<1){                                        //se a variável contadora for menor que 1, significa que o usuário não está cadastrado
   printf("\n==== Usuario nao encontrado! ====\n");
   printf("\n==== Cadastre-se para criar suas tarefas ====\n"); //recomentação de cadastro
  }
}




void cadastroTarefa(Tarefa *tPtr, usuario *uPtr){
    char linha[100];                                                   //declaração da string linha para armazenar dados quando for acessar o arquivo
    int cont=0;                                                        //declaração de variável contadora
    int temDataC, validId = 0, validPrio = 0, validStatus = 0;         //declaração de variáveis auxiliares para validar restrições
    char fileName[2000];                                                //declaração de string para armazenar o nome do arquivo a partir do nome do usuário
    char ID_Temp[100];                                                 //declaração de string para armazenar temporariamente o ID
    char prioridade1[] = "alta", prioridade2[] = "media", prioridade3[] = "baixa"; //declaração de strings para garantir prioridades válidas
    char status1[] = "concluida", status2[] = "em andamento", status3[] = "pendente", status4[] = "cancelada"; //declaração de strings para garantir status válidos
    int  contTarefa = 0;                                               //declaração de variável contadora

  sprintf(fileName,"%s.txt",uPtr->nome);                       //chama um arquivo com o nome do usuário
  FILE *file = fopen(fileName,"r");                            //abre o arquivo para leitura

  while(fgets(linha,sizeof(linha),file)!=NULL){                //conta quantas tarefas ja existem no arquivo
    contTarefa++;                                              //incrementa 1 à variável contadora quando encontra uma tarefa
    }
  if(contTarefa == MAX_TAREFAS){                               //se atingir o limite de tarefas, exibe a mensagem de limite atingido
    printf("\n==== Número máximo de tarefas por usuário atingido!! ====\n");  //informa que o usuário atingiu o limite de tarefas
    return;
  }
    //fscanf(fileName, "%[^,]", tPtr->id);
    printf("\n\t\t\t\t========= Cadastro de um nova tarefa =========\n");
    printf("\nDigite o ID da tarefa (único e 8 numeros): ");     //solicita o ID da tarefa ao usuário
    scanf("%s", ID_Temp);                        //lê o ID
    ID_Temp[strcspn(ID_Temp, "\n")] = '\0';                      //substitui o \n por \0 na string do ID
    limparBuffer();                                  //copia a string ID_Temp para o membro id da estrutura apontada pelo ponteiro tPtr


    while(fgets(linha,sizeof(linha),file)!=NULL){         //(estrutura para garantir que o usuário não digite dois IDs iguais) lê as linhas do arquivo e armazena na string linha
    sscanf(linha,"%[^,],s",tPtr->id);                       //lê a string linha até encontrar a vírgula e armazena no membro id da estrutura apontada pelo ponteiro tPtr
    if(strcmp(tPtr->id, ID_Temp) == 0){                      //compara se os IDs são iguais
    cont=1;                                               //incrementa 1 à variável contadora se os IDs forem iguais
    fclose(file);                                         //fecha o arquivo
    break;                                                //interrompe a estrutura de repetição
    }
  }
  while(cont==1){                                      // enquanto cont for igual a 1, solicita ao usuário que digite um ID diferente
  printf("\n==== ID repetido! =====\nDigite uma sequencia diferente (8 numeros): ");
  fgets(ID_Temp,sizeof(ID_Temp),stdin);                //lê o ID digitado
  ID_Temp[strcspn(ID_Temp, "\n")] = '\0';              //substitui o \n por \0 na string do ID_Temp para garantir que a string não tenha quebra de linha
  if(strcmp(tPtr->id,ID_Temp)==0){                    //compara se os IDs são iguais
  cont = 1;                                           //se iguais, atribui 1 a variável contadora e volta para estrutura de pedir o ID novamente
  }else{
  cont = 0;                                          //se diferentes, atribui 0 a variável contadora e garante que não peça o ID novamente
  strcpy(tPtr->id, ID_Temp);                         //copia a string ID_Temp para o membro id da estrutura apontada pelo ponteiro tPtr
     }
  }


  do {                                              //faz a validação do ID enquanto o ID não for válido
    if (strlen(ID_Temp) != 8) {                    //se o tamanho do ID for diferente de 8, pede outro ID
        printf("\n==== ID inválido, número de caracteres diferente de 8! ====\n Insira um ID valido: ");
        fgets(ID_Temp, sizeof(ID_Temp), stdin);      //lê o novo ID
        ID_Temp[strcspn(ID_Temp, "\n")] = '\0';      //substitui o \n por \0 na string do ID para garantir que a string não tenha quebra de linha
    } else {                                           //senão, o tamanho do ID é válido
        validId++;                                     //incrementa 1 à variável contadora
        for (int i = 0; i!=strlen(ID_Temp); i++) {    //laço que percorre todos os caracteres do ID
            if (!isdigit(ID_Temp[i])){                //verifica se algum caractere não é um dígito
                validId = 0;                           //se não for um número, atribui zero a variavel para que a estrutura de repetição faça outra verificação novamente
                printf("\n=== ID invalido, foi inserido uma letra! ====\n Insira um ID valido: "); //solicita um ID válido novamente
                fgets(ID_Temp, sizeof(ID_Temp), stdin);                       //lê o ID
                ID_Temp[strcspn(ID_Temp, "\n")] = '\0';                       //substitui o \n por \0 na string do ID para garantir que a string não tenha quebra de linha
                break;                                                          //interrope o laço de repetição
            }
        }
    }
} while (validId != 1);                                    // repete a estrutura acima enquanto a variável contadora for diferente de 1
    strcpy(tPtr->id, ID_Temp);
    printf("Digite o titulo da tarefa: ");                 //solicita o título ao usuário
    fgets(tPtr->titulo, 100, stdin);                       //lê o título
    tPtr->titulo[strcspn(tPtr->titulo, "\n")] = '\0';      //substitui o \n por \0 na string do titulo para garantir que a string não tenha quebra de linha

    printf("Digite a descricao da tarefa: ");              //solicita a descrição da tarefa
    fgets(tPtr->descricao, 1000, stdin);                   //lê descrição da tarefa
    tPtr->descricao[strcspn(tPtr->descricao, "\n")] = '\0';//substitui o \n por \0 na string da descrição para garantir que a string não tenha quebra de linha

    printf("Digite a data de criacao da tarefa: \n");      //solicita a data de criação da tarefa
    printf("Dia: ");
    fgets(tPtr->Data_de_criacao.dia,sizeof(tPtr->Data_de_criacao.dia),stdin);   //lê dia da criação da tarefa
    tPtr->Data_de_criacao.dia[strcspn(tPtr->Data_de_criacao.dia, "\n")] = '\0'; //substitui o \n por \0 na string dia para garantir que a string não tenha quebra de linha
  getchar();
    printf("Mes: ");
    fgets(tPtr->Data_de_criacao.mes,sizeof(tPtr->Data_de_criacao.mes),stdin);   //lê mês da criação da tarefa
    tPtr->Data_de_criacao.mes[strcspn(tPtr->Data_de_criacao.mes, "\n")] = '\0'; //substitui o \n por \0 na string mes para garantir que a string não tenha quebra de linha
  getchar();
    printf("Ano: ");
    fgets(tPtr->Data_de_criacao.ano,sizeof(tPtr->Data_de_criacao.ano),stdin);   //lê ano da criação da tarefa
    tPtr->Data_de_criacao.ano[strcspn(tPtr->Data_de_criacao.ano, "\n")] = '\0'; //substitui o \n por \0 na string ano para garantir que a string não tenha quebra de linha
getchar();

    printf("Essa tarefa tem data de conclusão, digite 1 - Sim ou 0 - Não?: ");  //pergunta ao usuário se a tarefa possui data de conclusão
    scanf("%d", &temDataC);                                                     //lê opção do usuário
    limparBuffer();                                                                  //lê o \n e garante que o código não prossiga sem que o usuário digite algo
    if(temDataC == 1){                                                          //se opçao do usuário foi 1, pede-se a data
        printf("Digite a data de conclusão da tarefa: \n");
        printf("Dia: ");
        scanf("%s", tPtr->Data_de_conclusao.dia);                              //lê dia da data de conclusão
        limparBuffer();
        printf("Mês: ");
        scanf("%s", tPtr->Data_de_conclusao.mes);                              //lê mes da data de conclusão
        limparBuffer();
        printf("Ano: ");
        scanf("%s", tPtr->Data_de_conclusao.ano);                              //lê ano da data de conclusão
        limparBuffer();
    }
  if(temDataC == 0){ //If para se não tiver data de conclusão
    strcpy(tPtr->Data_de_conclusao.dia, "00");
    strcpy(tPtr->Data_de_conclusao.mes, "00");
    strcpy(tPtr->Data_de_conclusao.ano, "0000");
    }

    printf("Digite a prioridade da tarefa (alta, media, baixa): ");            //solicita a prioridade da tarefa ao usuário
     fgets(tPtr->prioridade, 10, stdin);                                       //lê prioridade
    tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';                  //substitui o \n por \0 na string prioridade para garantir que a string não tenha quebra de linha
    do{                                                                        //estrutura de repetição para garantir que a prioridade digitada pelo usuário seja válida
        validPrio = 0;                                                         //variável contadora iniciada com 0
        if(strcmp(tPtr->prioridade, prioridade1) == 0){                        //compara se prioridade digitada pelo usuário é igual a prioridade 'alta'
           validPrio++;                                                        //incrementa 1 à variável contadora se forem iguais
        } else if(strcmp(tPtr->prioridade, prioridade2) == 0){                 //compara se prioridade digitada pelo usuário é igual a prioridade 'media'
           validPrio++;                                                        //incrementa 1 à variável contadora se forem iguais
        } else if(strcmp(tPtr->prioridade, prioridade3) == 0){                 //compara se prioridade digitada pelo usuário é igual a prioridade 'baixa'
           validPrio++;                                                        //incrementa 1 à variável contadora se forem iguais
        } else {                                                               // senão, informa que a prioridade é inválida
            printf("\n==== Prioridade inválida! ====\nDigite uma prioridade válida: ");//solicita a prioridade novamente
            fgets(tPtr->prioridade, 10, stdin);                                        //lê prioridade
            tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';                  //substitui o \n por \0 na string prioridade para garantir que a string não tenha quebra de linha
        }
    }while(validPrio != 1);                                                    //estrutura acima se repete enquanto a variável contadora for diferente de 1

    printf("Digite o nome do usuário reponsável pela tarefa: ");               //solicita o nome do responsável pela tarefa
    fgets(tPtr->responsavel, 100, stdin);                                      //lê nome do responsável
    tPtr->responsavel[strcspn(tPtr->responsavel, "\n")] = '\0';                //substitui o \n por \0 na string responsavel para garantir que a string não tenha quebra de linha

    printf("Digite o status atual da tarefa (concluida, em andamento, pendente, cancelada): ");//solicita o status da tarefa ao usuário
    fgets(tPtr->status, 50, stdin);                                            //lê status
    tPtr->status[strcspn(tPtr->status, "\n")] = '\0';                          //substitui o \n por \0 na string status (garante que a string não tenha quebra de linha)
    do{                                                                        //estrutura de repetição para garantir que o status digitado pelo usuário seja válido
        validStatus = 0;                                                       //variável contadora iniciada com 0
        if(strcmp(tPtr->status, status1) == 0){                                //compara se status digitado pelo usuário é igual ao status 'concluida'
           validStatus++;                                                      //incrementa 1 à variável contadora se forem iguais
        } else if(strcmp(tPtr->status, status2) == 0){                         //compara se status digitado pelo usuário é igual ao status 'em andamento'
           validStatus++;                                                      //incrementa 1 à variável contadora se forem iguais
        } else if(strcmp(tPtr->status, status3) == 0){                         //compara se status digitado pelo usuário é igual ao status 'pendente'
           validStatus++;                                                      //incrementa 1 à variável contadora se forem iguais
        } else if(strcmp(tPtr->status, status4) == 0){                         //compara se status digitado pelo usuário é igual ao status 'cancelada'
           validStatus++;                                                      //incrementa 1 à variável contadora se forem iguais
        } else {                                                               // senão, informa que status é inválido
            printf("\n==== Status inválido! ====\nDigite um status válido: "); //solicita o status novamente
            fgets(tPtr->status, 50, stdin);                                    //lê status
            tPtr->status[strcspn(tPtr->status, "\n")] = '\0';                  //substitui o \n por \0 na string status para garantir que a string não tenha quebra de linha
        }
    }while(validStatus != 1);                                                  //estrutura acima se repete enquanto a variável contadora for diferente de 1
    printf("\n\t\t\t\t========= Tarefa cadastrada com sucesso!! =========\n");//mostra que tarefa foi cadastrada
    sprintf(fileName,"%s.txt",uPtr->nome); //cria um arquivo com o nome do usuário
    if(contTarefa>=1){
    FILE *file2=fopen(fileName,"a");
    fprintf(file2,"\n");                                 //abre o arquivo no modo de acrescentar conteúdo ao final do arquivo
    fprintf(file2,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",tPtr->id,tPtr->titulo,tPtr->descricao, //escreve todos os campos da tarefa na linha do arquivo apontado por file2
    tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano,
    tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano,
    tPtr->prioridade,tPtr->responsavel,tPtr->status);
    fclose(file2);

}
    else if(contTarefa<1){
    FILE *file2 = fopen(fileName,"w");                                          //abre o arquivo no modo de acrescentar conteúdo ao final do arquivo
  fprintf(file2,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",tPtr->id,tPtr->titulo,tPtr->descricao, //escreve todos os campos da tarefa na linha do arquivo apontado por file2
    tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano,
    tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano,
    tPtr->prioridade,tPtr->responsavel,tPtr->status);
    fclose(file2);
    }                                                            //fecha o arquivo para evitar problemas futuros

}




void editarTarefa(Tarefa *tPtr,usuario *uPtr){                               //função para editar as tarefas
char fileName[2000];
sprintf(fileName, "%s.txt", uPtr->nome);                                     //cria um arquivo com o nome do usuário
FILE *file = fopen(fileName,"r");                                            //abre o arquivo no modo leitura
char linha[100];                                                             //string para armazenar dados quando for acessar o arquivo
char Temp[100];                                                              //string para armazenar dados temporários
int cont=0;                                                                  //declaração de variável contadora
int contID = 0;                                                              //variável contadora
char selecionar_id[8];                                                       //string para armazenar ID temporariamente
int validId;                                                                 //variável para validar ID
int validPrio;                                                               //variável para validar prioridade
int validStatus;                                                             //variável para validar status
int selecionar_campo;                                                        //variável para armazenar opção do usuário
char prioridade1[] = "alta", prioridade2[] = "media", prioridade3[] = "baixa";  //declaração de strings para garantir prioridades válidas
char status1[] = "concluida", status2[] = "em andamento", status3[] = "pendente", status4[] = "cancelada";//declaração de strings para garantir status válidos
printf("\n\t\t\t\t========= Edição de uma tarefa =========\n");
printf("Escreva o ID da tarefa a ser editada: ");                            //solicita o ID da tarefa a ser editada
scanf("%s", selecionar_id);                                                  //lê ID
limparBuffer();
while(fgets(linha,sizeof(linha),file)!=NULL){                                //lê as linhas do arquivo e armazena na string linha até que não haja conteúdo no arquivo
sscanf(linha,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",tPtr->id,tPtr->titulo,tPtr->descricao,//lê todos os campos da tarefa a cada vírgula na linha do arquivo
tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano,
tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano,
tPtr->prioridade,tPtr->responsavel,tPtr->status);

if(strcmp(tPtr->id,selecionar_id)==0){                                       //compara se os IDs são iguais
fclose(file);                                                                //fecha o arquivo
cont=1;                                                                      //atribui 1 à variável contadora, indicando que o ID da tarefa digitada pelo usuário foi encontrada
break;                                                                       //quebra o loop infinito
}
}
if(cont==1){                                                                 //se variável contadora for 1, mostra opções de edição da tarefa
printf("Tarefa de ID: %s encontrada\n\n",tPtr->id);                          //mostra o ID da tarefa encontrada
printf("[1]:ID\n");                                                            // mostra opção de mudar Id
printf("[2]:Título\n");                                                        // mostra opção de mudar título
printf("[3]:Descrição\n");                                                     // mostra opção de mudar descrição
printf("[4]:Data de criação\n");                                               // mostra opção de mudar data de criação
printf("[5]:Data de conclusão\n");                                             // mostra opção de mudar data de conclusão
printf("[6]:Prioridade\n");                                                    // mostra opção de mudar prioridade
printf("[7]:Responsável\n");                                                   // mostra opção de mudar responsável
printf("[8]:Status\n");                                                        // mostra opção de mudar status
printf("[9]:Editar todos os campos\n");                                        // mostra opção de mudar todos os campos
printf("Escolha qual campo deseja editar: ");                                //solicita uma opção
scanf("%d",&selecionar_campo);                                               //lê opção
switch(selecionar_campo){
case 1:
                                                      //copia a string temp pra string id

  sprintf(fileName,"%s.txt",uPtr->nome);                                     //cria um arquivo com o nome do usuário
  FILE *file2 = fopen(fileName,"r");                                         //abre o arquivo no modo leitura

printf("Digite o novo ID: ");                                                //solicita novo ID
fgets(Temp,sizeof(Temp),stdin);                                              //lê no ID
Temp[strcspn(Temp, "\n")] = '\0';                                            //substitui o \n por \0 na string Temp para garantir que a string não tenha quebra de linha
limparBuffer();

  while(fgets(linha,sizeof(linha),file2)!=NULL){                             //lê as linhas do arquivo e armazena na string linha até que não haja conteúdo no arquivo
    sscanf(linha,"%[^,]",tPtr->id);                                          //lê os caracteres de linha até a virgula e armazena no campo id
    if(strcmp(Temp,tPtr->id)==0){                                            //se od IDs forem iguais, atribui 1 à variável contadora
    contID=1;
    fclose(file2);                                                          //fecha o arquivo apontado por file2
    break;                                                                  //quebra o loop
    }
  }
  while(contID==1){                                                        //enquanto a variável contadora for 1,indique que os ids são repetidos
  printf("\n==== ID repetido! =====\nDigite uma sequencia diferente (8 numeros): ");//pede-se outro id diferente
  scanf("%s", Temp);                                                        //lê novo id
  limparBuffer();
  if(strcmp(tPtr->id,Temp)==0){                                            //se os IDs forem iguais, atribui 1 à variável contadora
  contID = 1;
  }else{                                                                   //se os IDs forem diferentes, então é válido e
  strcpy(tPtr->id, Temp);                                                  //copia a string temporária válida para o campo id
  contID = 0;                                                              //validado, então atribui zero à variável contadora
    }
  }
fclose(file2);
strcpy(tPtr->id, Temp);
while(1){                                                                  // Loop infinito, executa até ser interrompido por um break para Verificar os requisitos do id
    if (strlen(tPtr->id) != 8) {                                           //condicinal para garantir que o id tenha exatamente 8 caracteres
        printf("\n==== ID inválido, número de caracteres diferente de 8! ====\n Insira um ID valido: ");
        fgets(tPtr->id, sizeof(tPtr->id), stdin);
        tPtr->id[strcspn(tPtr->id, "\n")] = '\0';
    }else{                                                                //senão, incrementa 1 à variável contadora, indicando que o tamanho do id è válido
        validId=1;
        for (int i = 0; i!=strlen(tPtr->id); i++) {                       //laço de repetição para garantir que o id seja somente números
            if (!isdigit(tPtr->id[i])){
                validId = 0;                                              //se não for digito, atribui 1 à variável contadora para que o id passe por toda verificação novamente
                printf("\n=== ID invalido, foi inserido uma letra! ====\n Insira um ID valido: ");// solicita o id novamente
                fgets(tPtr->id, sizeof(tPtr->id), stdin);                 //lê id
                tPtr->id[strcspn(tPtr->id, "\n")] = '\0';                 //substitui o \n por \0 na string id para garantir que a string não tenha quebra de linha
                break;                                                    //quebra o laço de repetição quando o id se torna válido
            }
        }
    }
    if(validId==1){                                                        //se o id for válido, o break quebra o loop infinito
    break;
    }
    }
break;                                                                    //break para interromper o switch caso opção 1 for realizada
case 2:
printf("Digite o novo titulo: ");                                        //solicita um novo título
scanf("%s",tPtr->titulo);                                          //lê o titulo                       //substitui o \n por \0 na string id para garantir que a string não tenha quebra de linha
limparBuffer();
break;
case 3:
printf("Digite a nova descrição: ");                                     //solicita uma nova descrição
fgets(tPtr->descricao, strlen(tPtr->descricao), stdin);                                         //lê a nova descrição
limparBuffer();
break;
case 4:
printf("Digite a nova data de crição: ");                                //solicita nova data de criação
scanf("%s/%s/%s",tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano);
limparBuffer();
break;
case 5:
printf("Digite a nova data de conclusão: ");                            //solicita nova data de conclusão
scanf("%s/%s/%s",tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano);
limparBuffer();
break;
case 6:
printf("Digite a nova prioridade da tarefa: ");                         //solicita a nova prioridade
fgets(tPtr->prioridade,10,stdin);                                       //lê nova prioridade
tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';
limparBuffer();               //substitui o \n por \0 na string prioridade para garantir que a string não tenha quebra de linha
    do{                                                                 //estrutura de repetição para garantir que a prioridade digitada pelo usuário seja uma válida
        validPrio = 0;
        if(strcmp(tPtr->prioridade, prioridade1) == 0){                 //compara se prioridade digitada pelo usuário é igual a prioridade  alta
           validPrio++;
        } else if(strcmp(tPtr->prioridade, prioridade2) == 0){          //compara se prioridade digitada pelo usuário é igual a prioridade  media
           validPrio++;
        } else if(strcmp(tPtr->prioridade, prioridade3) == 0){          //compara se prioridade digitada pelo usuário é igual a prioridade baixa
           validPrio++;
        } else {                                                        //se não for uma das 3 opções acima, solicita uma prioridade válida
            printf("\n==== Prioridade inválida! ====\nDigite uma prioridade válida: ");
            fgets(tPtr->prioridade, 10, stdin);                         //lê prioridade
            tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';
            limparBuffer();   //substitui o \n por \0 na string prioridade para garantir que a string não tenha quebra de linha
        }
    }while(validPrio != 1);                                             //estrutura acima se repete enquanto a variável contadora for diferente de 1
    limparBuffer();
case 7:
printf("Digite o novo responsável pela tarefa: ");                     //solicita novo nome do responsável da tarefa
scanf("%s",tPtr->responsavel);                                    //lê novo nome do responsável
limparBuffer();
case 8:
printf("Digite o novo status da tarefa: ");                            //solicita novo status da tarefa
fgets(tPtr->status,50,stdin);                                          //lê novo status
tPtr->status[strcspn(tPtr->status, "\n")] = '\0';
limparBuffer();                      //substitui o \n por \0 na string status para garantir que a string não tenha quebra de linha
    do{                                                                //estrutura de repetição para garantir que o status digitado pelo usuário seja uma válido
        validStatus = 0;
        if(strcmp(tPtr->status, status1) == 0){                        //compara se status digitado pelo usuário é igual ao status concluida
           validStatus++;
        } else if(strcmp(tPtr->status, status2) == 0){                 //compara se status digitado pelo usuário é igual ao status em andamento
           validStatus++;
        } else if(strcmp(tPtr->status, status3) == 0){                 //compara se status digitado pelo usuário é igual ao status pendente
           validStatus++;
        } else if(strcmp(tPtr->status, status4) == 0){                 //compara se status digitado pelo usuário é igual ao status cancelada
           validStatus++;
        } else {                                                        //se não for uma das 4 opções acima, solicita um novo status válido
            printf("\n==== Status inválido! ====\nDigite um status válido: ");
            fgets(tPtr->status, 50, stdin);                             //lê novo status
            tPtr->status[strcspn(tPtr->status, "\n")] = '\0';
            limparBuffer();           //substitui o \n por \0 na string status para garantir que a string não tenha quebra de linha
        }
    }while(validStatus != 1);                                           //estrutura acima se repete enquanto a variável contadora for diferente de 1
limparBuffer();
case 9:
                                                           //declaração de variável contadora
  sprintf(fileName,"%s.txt",uPtr->nome);                                //chama um arquivo com o nome do usuário
  FILE *file3 = fopen(fileName,"r");                                    //abre o arquivo no modo leitura

printf("Digite o novo ID: ");                                           //solicita novo id neste caso
scanf("%s",Temp);                                                       //lê id                                                 //copia a string Temp para a string id para fazer comparações posteriormente
limparBuffer();
contID = 0;                                      //substitui o \n por \0 na string status para garantir que a string não tenha quebra de linha


    while(fgets(linha,sizeof(linha),file3)!=NULL){                       //lê as linhas do arquivo e armazena na string linha até que não haja conteúdo no arquivo
    sscanf(linha,"%[^,]",tPtr->id);                                      //lê os caracteres de linha até a virgula e armazena no campo id
    if(strcmp(Temp,tPtr->id)==0){                                        //se od IDs forem iguais, atribui 1 à variável contadora e indica que o id não é válido
    contID=1;
    fclose(file3);                                                       //fecha o arquivo
    break;                                                               //interrrompe o loop infinito
    }
  }
  while(contID==1){                                                     //estrutura de repetição para garantir que o novo id seja diferente
  printf("\n==== ID repetido! =====\nDigite uma sequencia diferente (8 numeros): "); //solicita novo id
  scanf("%s", Temp);                                                                 //le novo id
  limparBuffer();
  if(strcmp(tPtr->id,Temp)==0){                                                     //compara se os IDs são iguais
  contID = 1;
  }else{                                                                            //se não for, copia o id da variável temporária para o campo id
  strcpy(tPtr->id, Temp);
  contID = 0;                                                                       //atribui 1 à variável contadora, indicando que o id foi diferente
  }
  }
fclose(file3);
strcpy(tPtr->id, Temp);
do {                                                                                //faz a validação do ID enquanto o ID não for válido
    if (strlen(tPtr->id) != 8) {                                                    //se o tamanho do ID for diferente de 8, pede outro ID
        printf("\n==== ID inválido, número de caracteres diferente de 8! ====\n Insira um ID valido: ");
        fgets(tPtr->id, sizeof(tPtr->id), stdin);                                   //lê novo id
        tPtr->id[strcspn(tPtr->id, "\n")] = '\0';
        limparBuffer();                                   //substitui o \n por \0 na string status para garantir que a string não tenha quebra de linha
      } else {                                                                      //senão, indica que o tamanho é válido
        validId++;
        for (int i = 0; i!=strlen(tPtr->id); i++) {                           //laço que percorre todos os caracteres do ID
            if (!isdigit(tPtr->id[i])){                                       //verifica se algum caractere não é um dígito
                validId = 0;                                                  //se não for um número, atribui zero a variavel para que a estrutura de repetição faça outra verificação novamente
                printf("\n=== ID invalido, foi inserido uma letra! ====\n Insira um ID valido: ");//solicita novo id
                fgets(tPtr->id, sizeof(tPtr->id), stdin);                                         //lê novo id
                tPtr->id[strcspn(tPtr->id, "\n")] = '\0';
                limparBuffer();                                         //substitui o \n por \0 na string id para garantir que a string não tenha quebra de linha
              break;                                                                     //interrope o laço de repetição garantindo que o novo não possui caracteres diferentes de numeros
            }
        }
    }
} while (validId != 1);                                                                 // repete a estrutura acima enquanto a variável contadora for diferente de 1
printf("Digite o novo titulo: ");                                                       //quando as retrições acimas fores validadas, solicita novo titulo
scanf("%s",tPtr->titulo);                                                          //lê novo titulo//substitui o \n por \0 na string titulo para garantir que a string não tenha quebra de linha
limparBuffer();
printf("Digite a nova descrição: ");                                    //solicita nova descrição
fgets(tPtr->descricao, strlen(tPtr->descricao), stdin);                                       //lê nova descrição               //substitui o \n por \0 na string descrição para garantir que a string não tenha quebra de linha
limparBuffer();
printf("Digite a nova data de crição: ");                                //solicita nova data de criação
scanf("%s/%s/%s",&tPtr->Data_de_criacao.dia,&tPtr->Data_de_criacao.mes,&tPtr->Data_de_criacao.ano);
limparBuffer();
printf("Digite a nova data de conclusão: ");                                                       //solicita nova data de conclusao
scanf("%s/%s/%s",&tPtr->Data_de_conclusao.dia,&tPtr->Data_de_conclusao.mes,&tPtr->Data_de_conclusao.ano);
limparBuffer();//lê nova data de conclusao
printf("Digite a nova prioridade da tarefa: ");                                                //solicita nova prioridade
fgets(tPtr->prioridade,10,stdin);                                                              //lê nova prioridade
tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';
limparBuffer();                                      //substitui o \n por \0 na string prioridade para garantir que a string não tenha quebra de linha
    do{                                                                                        //estrutura de repetição para garantir que a prioridade digitada pelo usuário seja válida
        validPrio = 0;
        if(strcmp(tPtr->prioridade, prioridade1) == 0){                                        //compara se prioridade digitada pelo usuário é igual a prioridade 'alta'
           validPrio++;
        } else if(strcmp(tPtr->prioridade, prioridade2) == 0){                                 //compara se prioridade digitada pelo usuário é igual a prioridade 'media'
           validPrio++;
        } else if(strcmp(tPtr->prioridade, prioridade3) == 0){                                 //compara se prioridade digitada pelo usuário é igual a prioridade 'baixa'
           validPrio++;
        } else {                                                                               // senão, informa que a prioridade é inválida
            printf("\n==== Prioridade inválida! ====\nDigite uma prioridade válida: ");        //solicita prioridade novamente
            fgets(tPtr->prioridade, 10, stdin);                                                //lê prioridade
            tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';
            limparBuffer();                          //substitui o \n por \0 na string prioridade para garantir que a string não tenha quebra de linha
        }
    }while(validPrio != 1);                                                                    //estrutura acima se repete enquanto a variável contadora for diferente de 1
limparBuffer();
printf("Digite o novo responsável pela tarefa: ");                                             //solicita nome do responsável
scanf("%s",tPtr->responsavel);                                      //lê nome do responsável                                   //substitui o \n por \0 na string prioridade para garantir que a string não tenha quebra de linha
limparBuffer();
printf("Digite o novo status da tarefa: ");                                                   //solicita novo status da tarefa
fgets(tPtr->status,50,stdin);                                                                 //lê status
tPtr->status[strcspn(tPtr->status, "\n")] = '\0';
limparBuffer();                                            //substitui o \n por \0 na string status para garantir que a string não tenha quebra de linha
    do{                                                                                       //estrutura de repetição para garantir que o status digitado pelo usuário seja válido
        validStatus = 0;
        if(strcmp(tPtr->status, status1) == 0){                                               //compara se status digitado pelo usuário é igual ao status 'concluida'
           validStatus++;
        } else if(strcmp(tPtr->status, status2) == 0){                                        //compara se status digitado pelo usuário é igual ao status 'em andamento'
           validStatus++;
        } else if(strcmp(tPtr->status, status3) == 0){                                        //compara se status digitado pelo usuário é igual ao status 'pendente'
           validStatus++;
        } else if(strcmp(tPtr->status, status4) == 0){                                        //compara se status digitado pelo usuário é igual ao status 'cancelada'
           validStatus++;
        } else {                                                                              // senão, informa que status é inválido
            printf("\n==== Status inválido! ====\nDigite um status válido: ");                //solicita novo status
            fgets(tPtr->status, 50, stdin);                                                   //lê status
            tPtr->status[strcspn(tPtr->status, "\n")] = '\0';
            limparBuffer();                                 //substitui o \n por \0 na string status para garantir que a string não tenha quebra de linha
        }
    }while(validStatus != 1);                                                                 //estrutura acima se repete enquanto a variável contadora for diferente de 1
limparBuffer();
break;
}
}

sprintf(fileName,"%s.txt",uPtr->nome);                                                        //chama o arquivo com o nome do usuário
FILE *file4 = fopen(fileName,"r+");                                                           //abre o arquivo no modo de leitura quanto de escrita
fseek(file4, -strlen(linha), SEEK_CUR);                                                       //Procura no arquivo a primeira posição da linha
fprintf(file4, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",                                       //escreve no arquivo todos os campos de uma tarefa
tPtr->id, tPtr->titulo, tPtr->descricao,
tPtr->Data_de_criacao.dia, tPtr->Data_de_criacao.mes, tPtr->Data_de_criacao.ano,
tPtr->Data_de_conclusao.dia, tPtr->Data_de_conclusao.mes, tPtr->Data_de_conclusao.ano,
tPtr->prioridade, tPtr->responsavel, tPtr->status);
fprintf(file4,"\n");
fclose(file4);                                                                               //fecha o arquivo
if(cont<1){
fclose(file4);                                                                                //fecha o arquivo
printf("\n==== Tarefa nao encontrada ====\n");
}
}

void excluirTarefa(Tarefa *tPtr,usuario *uPtr){                                              //Função para exclusão de uma tarefa
char linha[100];                                                                             //contador de linha
int cont=0;
int Cont_del=0;                                                                                  //contador
char fileName[2000];                                                                          //Variável para o nome do arquivo
sprintf(fileName,"%s.txt",uPtr->nome);                                                       //pega o arquivo com o nome do usúario
FILE *file = fopen(fileName,"r");                                                            //Abre o arquivo do usuário
FILE *file2 = fopen("Temp.txt","w");                                                         //Abre o arquivo temporário
char selecionar_id[9];                                                                       //Variável para guadar o ID
printf("\n\t\t\t\t========= Exclusão de uma tarefa =========\n");
printf("Digite o ID da tarefa para excluir: ");                                              //Pega o ID para excluir
scanf("%s",selecionar_id);
selecionar_id[strcspn(selecionar_id, "\n")] = '\0';
limparBuffer();
while(fgets(linha,sizeof(linha),file)!=NULL){
Cont_del++;
sscanf(linha,"%[^,]",tPtr->id);                                                            //Faz o scan no arquivo para ver se tem algum ID igual ao inserido
if(strcmp(tPtr->id,selecionar_id)==0){
printf("\n==== Tarefa de ID: %s Encontrada ====\n",tPtr->id);                              //Se encontrar o ID digitado o cont = 1
cont=1;
}
else{
fprintf(file2,"%s",linha);
}
}
fclose(file);
fclose(file2);

if(cont==1){
if(Cont_del==1){
if (remove(fileName) == 0 && remove("Temp.txt") == 0) {             //Faz com que exclua o arquivo do usuário seja excluido e substituido pelo arquivo temporário onde não tem mais essa tarefa
        printf("\n==== Tarefa excluída com sucesso!! ====\n");
        } else {
        printf("\n==== Erro ao excluir a tarefa!! ====\n");
        }
}
if(Cont_del>1){
if (remove(fileName) && rename("Temp.txt", fileName) == 0) {             //Faz com que exclua o arquivo do usuário seja excluido e substituido pelo arquivo temporário onde não tem mais essa tarefa
        printf("\n==== Tarefa excluída com sucesso!! ====\n");
        } else {
        printf("\n==== Erro ao excluir a tarefa!! ====\n");
        }
}

}
if(cont<1){
printf("\n==== Tarefa nao encontrada!! ====\n");                                              //Se o cont não é 1 não tem uma tarefa com esse ID, logo não será encontrada
}
}


void exibirIDTarefa(Tarefa *tPtr,usuario *uPtr){    //Função para exibir a tarefa com base no ID
char fileName[2000];
sprintf(fileName,"%s.txt",uPtr->nome);              //Abre a file com o nome do usuário
FILE *file = fopen(fileName,"r");
char linha[100];
int cont=0;
char selecionar_id[9];
printf("\n\t\t\t\t========= Listagem por ID =========\n");
printf("Digite o ID da tarefa para listar: ");
scanf("%s",selecionar_id);
selecionar_id[strcspn(selecionar_id, "\n")] = '\0';
limparBuffer();
while(fgets(linha,sizeof(linha),file)!=NULL){
sscanf(linha,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",tPtr->id,tPtr->titulo,tPtr->descricao,
&tPtr->Data_de_criacao.dia,&tPtr->Data_de_criacao.mes,&tPtr->Data_de_criacao.ano,
&tPtr->Data_de_conclusao.dia,&tPtr->Data_de_conclusao.mes,&tPtr->Data_de_conclusao.ano,
tPtr->prioridade,tPtr->responsavel,tPtr->status); // Puxa todos os dados da tarefa a ser exibida
if(strcmp(selecionar_id,tPtr->id)==0){            //Compara o Id inserido com os que tem no arquivo
printf("Tarefa encontrada");
cont=1;
break;
}
}
fclose(file);                                      //Fecha o arquivo
if(cont==1){
printf("\n==== ID ====\n");
printf("%s\n",tPtr->id);
printf("==== Titulo ====\n");
printf("%s\n",tPtr->titulo);
printf("==== Descricao ====\n");
printf("%s\n",tPtr->descricao);
printf("==== Data de inicio ====\n");
printf("%s/%s/%s\n",tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano);
printf("==== Data de Conclusão ====\n");
printf("%s/%s/%s\n",tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano);
printf("==== Prioridade ====\n");
printf("%s\n",tPtr->prioridade);
printf("==== Responsavel ====\n");
printf("%s\n",tPtr->responsavel);
printf("==== Status ====\n");
printf("%s\n",tPtr->status);
}
if(cont<1){
printf("\n==== Tarefa nao encontrada!! ====\n");
}
}

void listarPrioTarefa(Tarefa *tPtr,usuario *uPtr){                                //Função para lista por prioridade
char fileName[2000];
sprintf(fileName,"%s.txt",uPtr->nome);
FILE *file = fopen(fileName,"r");
char linha[100];
int cont=0;
char selecionar_prio[9];
printf("\n\t\t\t\t========= Listagem por Prioridade =========\n");
printf("Digite a prioridade da tarefa para listar: ");
scanf("%s",selecionar_prio);
selecionar_prio[strcspn(selecionar_prio, "\n")] = '\0';
limparBuffer();
while(fgets(linha,sizeof(linha),file)!=NULL){
sscanf(linha,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",tPtr->id,tPtr->titulo,tPtr->descricao,
&tPtr->Data_de_criacao.dia,&tPtr->Data_de_criacao.mes,&tPtr->Data_de_criacao.ano,
&tPtr->Data_de_conclusao.dia,&tPtr->Data_de_conclusao.mes,&tPtr->Data_de_conclusao.ano,
tPtr->prioridade,tPtr->responsavel,tPtr->status); //Puxa todos os dados da tarefa a ser exibida
if(strcmp(selecionar_prio,tPtr->prioridade)==0){
cont=1;
printf("\n====ID ====\n");
printf("%s\n",tPtr->id);
printf("==== Titulo ====\n");
printf("%s\n",tPtr->titulo);
printf("==== Descricao ====\n");
printf("%s\n",tPtr->descricao);
printf("==== Data de inicio ====\n");
printf("%s/%s/%s\n",tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano);
printf("==== Data de Conclusão ====\n");
printf("%s/%s/%s\n",tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano);
printf("==== Prioridade ====\n");
printf("%s\n",tPtr->prioridade);
printf("==== Responsavel ====\n");
printf("%s\n",tPtr->responsavel);
printf("==== Status ====\n");
printf("%s\n",tPtr->status);
}
}
fclose(file);

if(cont<1){
printf("\n==== Tarefa nao encontrada!! ====\n");
}
}

void listarTituTarefa(Tarefa *tPtr, usuario *uPtr){   // Listar tarefa por titulo
char fileName[2000];
sprintf(fileName,"%s.txt",uPtr->nome);                // Procura o arquivo com o nome do usuário
FILE *file = fopen(fileName,"r");                     // Abre o arquivo com o nome de usuário
char linha[100];
int cont=0;
char selecionar_titu[9];
printf("\n\t\t\t\t========= Listagem por Título =========\n");
printf("Digite o titulo da tarefa para listar: ");
scanf("%s",selecionar_titu);
selecionar_titu[strcspn(selecionar_titu, "\n")] = '\0';
limparBuffer();
while(fgets(linha,sizeof(linha),file)!=NULL){
sscanf(linha,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",tPtr->id,tPtr->titulo,tPtr->descricao,
&tPtr->Data_de_criacao.dia,&tPtr->Data_de_criacao.mes,&tPtr->Data_de_criacao.ano,
&tPtr->Data_de_conclusao.dia,&tPtr->Data_de_conclusao.mes,&tPtr->Data_de_conclusao.ano,
tPtr->prioridade,tPtr->responsavel,tPtr->status);
if(strcmp(selecionar_titu,tPtr->titulo)==0){
cont=1;
printf("\n==== ID ====\n");
printf("%s\n",tPtr->id);
printf("==== Titulo ====\n");
printf("%s\n",tPtr->titulo);
printf("==== Descricao ====\n");
printf("%s\n",tPtr->descricao);
printf("==== Data de inicio ====\n");
printf("%s/%s/%s\n",tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano);
printf("==== Data de Conclusão ====\n");
printf("%s/%s/%s\n",tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano);
printf("==== Prioridade ====\n");
printf("%s\n",tPtr->prioridade);
printf("==== Responsavel ====\n");
printf("%s\n",tPtr->responsavel);
printf("==== Status ====\n");
printf("%s\n",tPtr->status);
}
}
fclose(file);

if(cont<1){
printf("\n==== Tarefa nao encontrada!! ====\n");
}
}

void listarUsuTarefa(Tarefa *tPtr,usuario *uPtr){      //Lista as tarefas do usuário
char fileName[2000];
char linha[100];
int cont=0;
sprintf(fileName,"%s.txt",uPtr->nome);
FILE *file = fopen(fileName,"r");

printf("\\n\t\t\t\t========= Tarefas do Usuario %s =========\n",uPtr->nome);

while(fgets(linha,sizeof(linha),file)!=NULL){     //Vai listar todas as tarefas ate não conter mais nenhuma
sscanf(linha,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",tPtr->id,tPtr->titulo,tPtr->descricao,
tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano,
tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano,
tPtr->prioridade,tPtr->responsavel,tPtr->status);
cont=1;
printf("\n==== ID ====\n");
printf("%s\n",tPtr->id);
printf("==== Titulo ====\n");
printf("%s\n",tPtr->titulo);
printf("==== Descricao ====\n");
printf("%s\n",tPtr->descricao);
printf("==== Data de inicio ====\n");
printf("%s/%s/%s\n",tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano);
printf("==== Data de Conclusão ====\n");
printf("%s/%s/%s\n",tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano);
printf("==== Prioridade ====\n");
printf("%s\n",tPtr->prioridade);
printf("==== Responsavel ====\n");
printf("%s\n",tPtr->responsavel);
printf("==== Status ====\n");
printf("%s\n",tPtr->status);
}
fclose(file);

if(cont<1){
printf("\n==== Nenhuma tarefa encontrada!! ====\n");
}
}

void exibirTafConcluida(Tarefa *tPtr,usuario *uPtr){ //Exibir tarefa que estão marcadas como concluída
char fileName[2000];
char concluida[] = "concluída";
sprintf(fileName,"%s.txt",uPtr->nome);
FILE *file = fopen(fileName,"r");
char linha[100];
int cont=0;
printf("\\n\t\t\t\t========= Tarefas concluidas por %s =========\n",uPtr->nome);
while(fgets(linha,sizeof(linha),file)!=NULL){
sscanf(linha,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",tPtr->id,tPtr->titulo,tPtr->descricao,
&tPtr->Data_de_criacao.dia,&tPtr->Data_de_criacao.mes,&tPtr->Data_de_criacao.ano,
&tPtr->Data_de_conclusao.dia,&tPtr->Data_de_conclusao.mes,&tPtr->Data_de_conclusao.ano,
tPtr->prioridade,tPtr->responsavel,tPtr->status);
if(strcmp(tPtr->status,concluida)==0){ //Compara para saber se tem alguma tarefa com status concluído
cont=1;
printf("\n==== ID ====\n");
printf("%s\n",tPtr->id);
printf("==== Titulo ====\n");
printf("%s\n",tPtr->titulo);
printf("==== Descricao ====\n");
printf("%s\n",tPtr->descricao);
printf("==== Data de inicio ====\n");
printf("%s/%s/%s\n",tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano);
printf("==== Data de Conclusão ====\n");
printf("%s/%s/%s\n",tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano);
printf("==== Prioridade ====\n");
printf("%s\n",tPtr->prioridade);
printf("==== Responsavel ====\n");
printf("%s\n",tPtr->responsavel);
printf("==== Status ====\n");
printf("%s\n",tPtr->status);
}
}
fclose(file);

if(cont<1){
printf("\n==== Tarefa nao encontrada!! ====\n");
}
}
void RelatarTarefa(Tarefa *tPtr,usuario *uPtr) {  //Mostra as estatísticas do usuário
char fileName[2000];
char linha[100];
char prioridade1[] = "alta", prioridade2[] = "media", prioridade3[] = "baixa";
char status1[] = "concluida", status2[] = "em andamento", status3[] = "pendente", status4[] = "cancelada";
int contTaf=0,contCon=0,contAnd=0,contPend=0,contCanc=0,contAlt=0,contMed=0,contBaix=0;
sprintf(fileName,"%s.txt",uPtr->nome);
FILE *file = fopen(fileName,"r");

while(fgets(linha,sizeof(linha),file)!=NULL){
contTaf++;
sscanf(linha,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",tPtr->id,tPtr->titulo,tPtr->descricao,
tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano,
tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano,
tPtr->prioridade,tPtr->responsavel,tPtr->status); //Puxa os dados da tarefa
if(strcmp(tPtr->status,status1)==0){
contCon++;  //Contador de tarefas concluídas
}
if(strcmp(tPtr->status,status2)==0){
contAnd++;  //Contador de tarefas em andamento
}
if(strcmp(tPtr->status,status3)==0){
contPend++;  //Contador de tarefas em pendência
}
if(strcmp(tPtr->status,status4)==0){
contCanc++;   //Contador de tarefas canceladas
}
if(strcmp(tPtr->prioridade,prioridade1)==0){
contAlt++; //Contador de prioridade alta
}
if(strcmp(tPtr->prioridade,prioridade2)==0){
contMed++;  //Contador de prioridade média
}
if(strcmp(tPtr->prioridade,prioridade3)==0){
contBaix++;  //Contador de prioridade baixa
}
}
if(contTaf == 0){
    printf("O usuario %s, não possui nenhuma tarefa cadastrada\n", uPtr->nome); //If se o usuário não tem tarefas
} else if(contTaf == 1){
    printf("O usuario %s, cadastrou %d tarefa\n", uPtr->nome,contTaf);   //If se o usuário tem 1 tarefa
}else if(contTaf > 1){
    printf("O usuario %s, cadastrou %d tarefas\n", uPtr->nome,contTaf); //If se o usuário tem mais de uma tarefa
}

printf("Tarefas concluídas: %d\n", contCon);
printf("Tarefas em andamento: %d\n", contAnd);
printf("Tarefas em pendência: %d\n", contPend);
printf("Tarefas canceladas: %d\n", contCanc);
printf("Tarefas com prioridade alta: %d\n", contAlt);
printf("Tarefas com prioridade média: %d\n", contMed);
printf("Tarefas com prioridade baixa: %d\n", contBaix);
}
