//Trabalho final de Fup - Sistema Gerenciador de Tarefas

#include <ctype.h>        //biblioteca para manipular caracteres
#include <locale.h>       //biblioteca para permitir acentua��o
#include <stdio.h>        //biblioteca para permitir entrada e sa�da padr�o
#include <stdlib.h>       //biblioteca para permitir aloca��o de mem�ria
#include <string.h>       //biblioteca para manipular vetores de caracteres
#define MAX_TAREFAS 5
                          //defini��o de tarefas por usu�rio



typedef struct{           //tipo estruturado para a data de criac�o da tarefa
char dia[3];              //string para armazenar dia da data de cria��o
char mes[3];              //string para armazenar mes da data de cria��o
char ano[5];              //string para armazenar ano da data de cria��o
}data;                    //nome do tipo estruturado


typedef struct{           //tipo estruturado para data de conclus�o da tarefa
char dia[3];              //string para armazenar dia da data de conclus�o
char mes[3];              //string para armazenar mes da data de conclus�o
char ano[5];              //string para armazenar ano da data de conclus�o
}data_conclusao;          //nome do tipo estruturado

typedef struct{           //Tipo estruturado para dados da tarefa
char id[9];               //string para armazenar ID
char titulo[100];         //string para armazenar titulo
char descricao[1000];     //string para armazenar descri��o
data Data_de_criacao;     //vari�vel do tipo data
data_conclusao Data_de_conclusao;//vari�vel do tipo data de conclus�o
char prioridade[10];      //string para armazenar titulo
char responsavel[100];    //string para armazenar titulo
char status[50];          //string para armazenar titulo
}Tarefa;                  //nome do tipo estruturado

typedef struct {          //tipo estruturado para dados do us�ario
char nome[100];           //string para armazenar nome
char senha[15];           //string para armazenar senha
Tarefa tarefas;           //vari�vel do tipo Tarefa
}usuario;                 //nome do tipo estruturado

void limparBuffer();      //Fun��o para limpar o buffer
void cadastro();          //prot�tipo fun��o cadastro
void login();             //prot�tipo fun��o login
void cadastroTarefa();    //prot�tipo da fun��o de criar tarefa
void editarTarefa();      //prot�tipo da fun��o de edi��o dos campos das tarefas
void excluirTarefa();     //prot�tipo da fun��o excluir tarefas
void listarUsuTarefa();   //prot�tipo da fun��o de listagem das tarefas do usu�rio
void listarPrioTarefa();  //prot�tipo da fun��o de listagem da tarefa por prioridade
void listarTituTarefa();  //prot�tipo da fun��o de listagem da tarefa por t�tulo
void exibirIDTarefa();    //prot�tipo da fun��o exibi��o de tarefas por ID
void exibirTafConcluida();//prot�tipo da fun��o exibi��o de tarefas concluidas do usu�rio
void RelatarTarefa();     //prot�tipo da fun��o relatario de Tarefas

int main() {
  setlocale(LC_ALL,"Portuguese");   //Fun��o usada para a utiliza��o do portugu�s nos textos
  usuario Usuarios;                 //vetor que armazena dados de at� 10 usu�rios
  int Opcao;                        //vari�vel que armazena a opc�o do usu�rio entre cadastro ou login
  char Usuario_login[100];          // vetor que armazena at� 100 caracteres do usu�rio
  char Senha_login[15];             // vetor que armazena at� 15 caracteres do usu�rio
  char linha[100];                  //string para armazenar dados quando for acessar o arquivo
  FILE *file = fopen("Usuarios.txt","r");//abre o arquivo para leitura
  int count=0;                      //declara��o de vari�vel contadora
while(1){                           // Loop infinito, executa at� ser interrompido por um break
printf("\n\t\t==============================================================================\n\t\t======================= SISTEMA GERENCIADOR DE TAREFAS =======================\n\t\t==============================================================================\n\n"); //mostra um cabe�alho do software na tela inicial
    printf("\t\t\t\t\t======= Cadastre-se =======\n\t\t\t\t======= J� possui conta? Fa�a o login =======\n"); // mostra op��es para cadastrar ou fazer login
    printf("[1]:Cadastrar novo usuario\n");                                                  //mostra op��o para cadastrar novo usu�rio
    printf("[2]:Login\n");                                                                   // mostra op��o para fazer login
    printf("[3]:Sair\n");                                                                    // mostra op��o para sair do programa
    printf("Selecione: ");                                                                 //pede que o usu�rio escolha uma op��o
scanf("%d", &Opcao);                                                                       //l� op��o escolhida pelo usu�rio
limparBuffer();


switch(Opcao){
case 1:
      while (fgets(linha, sizeof(linha), file)!=NULL){ // Contador do n�mero de usu�rios com base na linhas do arquivo
        count++;
      }
      fclose(file);                                    //fecha o arquivo para evitar problemas futuros
      if(count<10){                                    // Verifica se o n�mero de usu�rios � menor que 10
      cadastro(&Usuarios);                             //se sim, chama a fun��o de cadastro de novo usu�rio
      break;                                           //sai do switch
      }else if(count==10){                             //Verifica se o n�mero de usu�rios � igual a  10
      printf("==== Numero maximo de usuarios atingidos ====");//mostra que atingiu o limite de usu�rios
      continue;                                        //continua o loop
      }
case 2:
      system("cls");                                    //fun��o para limpar o terminal
      printf("\t\t\t\t========= Login =========\n");
      printf("Digite seu nome de usuario cadastrado: "); // Solicita o nome de usu�rio cadastrado
      fgets(Usuario_login, 100, stdin);                  //l� nome do usu�rio
      Usuario_login[strcspn(Usuario_login, "\n")] = '\0';//substitui o \n por \0 na string Usuario_login para garantir que a string n�o tenha quebra de linha
      printf("Digite sua senha: ");                      //solicita senha
      fgets(Senha_login, 15, stdin);                     //l� senha
      Senha_login[strcspn(Senha_login, "\n")] = '\0';    //substitui o \n por \0 na string senha_login para garantir que a string n�o tenha quebra de linha
      login(&Usuarios, Usuario_login, Senha_login);      // chama a fun��o login
      continue;                                          //continua o loop
case 3:
    return 0;                                            // termina o programa
    }
  }
}

void limparBuffer(void){                                 //Fun��o para limpar o buffer
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

void cadastro(usuario *uPtr) {                                          //fun��o para cadastrar os usu�rios
  system("cls");                                                        //fun��o para limpar o terminal
  int senhaValida = 0;                                                  //declara��o de vari�vel contadora
  int Selecionar_opcoes;                                                //declara��o de vari�vel para armazenar op��o do usu�rio de manipular as tarefas

  printf("\t\t\t\t========= Cadastro de um novo usu�rio =========\n");
  printf("Digite o nome do novo usuario: ");                            // Solicita o nome do novo usu�rio
  fgets(uPtr->nome, 100, stdin);                                        //l� o nome
  uPtr->nome[strcspn(uPtr->nome, "\n")] = '\0';                         //substitui o \n por \0 na string nome para garantir que a string n�o tenha quebra de linha
  limparBuffer();
  printf("Requisitos para a senha:\nDeve ter entre 4 e 10 caracteres de tamanho.\nAo menos 1 letra mai�scula.\nAo menos 1 n�mero.\nAo menos 1 caractere especial.\n");//informa os requisitos da senha ao usu�rio
    printf("Digite a senha: ");                                        //solicita��o de senha
  fgets(uPtr->senha, 15, stdin);                                       //l� senha
  uPtr->senha[strcspn(uPtr->senha, "\n")] = '\0';                      //substitui o \n por \0 na string senha para garantir que a string n�o tenha quebra de linha
  limparBuffer();
  while(1){                                                            // Loop infinito, executa at� ser interrompido por um break para Verificar os requisitos da senha
    if (strlen(uPtr->senha) >= 4){
      if(strlen(uPtr->senha) <= 10){                                  //verifi��o para garantir o tamanho da senha
        senhaValida++;
      }
    }

    for (int i = 0; i < strlen(uPtr->senha); i++) {                   // Verifica se h� pelo menos uma letra mai�scula na senha
      if (isupper(uPtr->senha[i])) {
        senhaValida++;
        break;
      }
    }

    for (int i = 0; i < strlen(uPtr->senha); i++) {                   // Verifica se h� pelo menos um n�mero na senha
      if (isdigit(uPtr->senha[i])) {
        senhaValida++;
        break;
      }
    }

    for (int i = 0; i < strlen(uPtr->senha); i++) {                // Verifica se h� pelo menos um caractere especial na senha
      if (!isalnum(uPtr->senha[i])){
        senhaValida++;
        break;
      }
    }

    if (senhaValida != 4) {                                      //se vari�vel contadora for diferente de 4, ent�o significa que a senha n�o atendeu todos os requisitos
      printf("\n==== Senha invalida! =====\nDigite novamente: ");//solicita senha novamente
      fgets(uPtr->senha, 15, stdin);                             //l� senha
      uPtr->senha[strcspn(uPtr->senha, "\n")] = '\0';            //substitui o \n por \0 na string senha para garantir que a string n�o tenha quebra de linha
    }
    if (senhaValida != 4) {                           //se vari�vel contadora for diferente de 4, ent�o declara ela como zero para que ela fa�a possa contar os requisitos na pr�xima repeti��o
      senhaValida = 0;
    }
    else if(senhaValida==4){                          //se senha v�lida, faz o cadastro do usu�rio
    FILE *file= fopen("Usuarios.txt", "a");           //abre o arquivo no modo de acrescentar conte�do ao final do arquivo
    fprintf(file,"%s,%s\n",uPtr->nome,uPtr->senha);   //escreve o nome e a senha do usu�rio no arquivo
    printf("\n==== Usuario Cadastrado com sucesso! ====\n");
    fclose(file);                                      //fecha o arquivo
    break;                                             //interrompe o loop infinito
    }
    }
  system("cls");                                       //fun��o para limpar o terminal
  printf("Usu�rio: %s ========================================", uPtr->nome);//mostra o nome do usu�rio ja cadastrado
  while(1){
  printf("\n[1]: Criar tarefa\n");                        // Mostra op��o para criar tarefa
  printf("[2]: Editar tarefa\n");                         // Mostra op��o para editar tarefa
  printf("[3]: Excluir tarefa\n");                        // Mostra op��o para excluir tarefa
  printf("[4]: Listar tarefa por ID\n");                  // Lista a tarefa por id
  printf("[5]: Listar tarefa do usuario\n");              // Lista a terefa por usu�rio
  printf("[6]: Listar tarefa por prioridade\n");          // Lista as tarefas por prioridade
  printf("[7]: Listar tarefa por titulo\n");              // Lista a tarefa por t�tulo
  printf("[8]: Listar tarefas concluidas\n");             // Lista as tarefas conclu�das
  printf("[9]: Estatisticas das tarefas\n");              // mostra op��o para ver estat�sticas das tarefas
  printf("Escolha uma opcao: ");                        //solicita uma op��o
  scanf("%d",&Selecionar_opcoes);                       //l� op��o
  limparBuffer();
  switch(Selecionar_opcoes){
  case 1:
  cadastroTarefa(uPtr->tarefas,uPtr->nome);            // Chama a fun��o para cadastrar uma nova tarefa
  break;
  case 2:
  editarTarefa(uPtr->tarefas,uPtr->nome);              // Chama a fun��o para editar uma tarefa existente
  break;
  case 3:
  excluirTarefa(uPtr->tarefas,uPtr->nome);             // Chama a fun��o para excluir uma tarefa
  break;
  case 4:
  exibirIDTarefa(&uPtr->tarefas,&uPtr->nome);          //Chama a fun��o para exibir tarefa por ID
    break;
  case 5:
  listarUsuTarefa(&uPtr->tarefas,&uPtr->nome);       // Chama a fun��o para listar as tarefas do usu�rio logado
  break;
  case 6:
  listarPrioTarefa(&uPtr->tarefas,&uPtr->nome);        //Chama a fun��o para exibir tarefa por prioridade
  break;
  case 7:
  listarTituTarefa(&uPtr->tarefas,&uPtr->nome);        //Chama a fun��o para exibir tarefa por T�tulo
  break;
  case 8:
  exibirTafConcluida(&uPtr->tarefas,&uPtr->nome);      //Chama a fun��o para exibir tarefas conclu�das
    break;
  case 9:
  RelatarTarefa(&uPtr->tarefas,&uPtr->nome);         // Chama a fun��o para exibir estat�sticas das tarefas
  break;
  }
}
}

void login(usuario *uPtr, char usu[], char sen[]) {    //fun��o para fazer o login do usu�rio
  char linha[100];                                     //string para armazenar dados quando for acessar o arquivo
  int cont=0;                                          //declara��o de vari�vel contadora
  FILE *file=fopen("Usuarios.txt","r");                //abre o arquivo no modo leitura
  while (fgets(linha, sizeof(linha), file)!=NULL){     //l� uma linha do arquivo e armazena na string linha e o loop continua enquanto h� linhas restantes para ler no arquivo
  sscanf(linha,"%[^,],%s",uPtr->nome,uPtr->senha);     //l� o nome at� a virgula e senha at� espa�o em branco da string linha
  if(strcmp(uPtr->nome,usu)==0&&strcmp(uPtr->senha,sen)==0){ //compara se senha e usu�rio no cadastro e login s�o iguais
  cont=1;                                              //se sim, atribui 1 a vari�vel contadora que indica um login v�lido
  fclose(file);                                        // Fecha o arquivo
  break;                                               // Sai do loop
  }
  }
  if(cont==1){                                        //se vari�vel contadora igual a 1, indica um login v�lido e mostra as op��es de manipula��o de tarefas
  int Selecionar_opcoes;                              //solicita uma op��o do usu�rio
while(1){
  printf("Usu�rio: %s ========================================", uPtr->nome);//mostra o nome do usu�rio logado
  printf("\n[1]: Criar tarefa\n");                      // mostra op��o para criar tarefa
  printf("[2]: Editar tarefa\n");                       // mostra op��o para editar tarefa
  printf("[3]: Excluir tarefa\n");                      // mostra op��o para excluir tarefa
 printf("[4]: Listar tarefa por ID\n");                 // Lista a tarefa por id
  printf("[5]: Listar tarefa do usuario\n");            // Lista a tarefa por usu�rio
  printf("[6]: Listar tarefa por prioridade\n");         // Lista a tarefa por prioridade
  printf("[7]: Listar tarefa por titulo\n");            // Lista a tarefa por t�tulo
  printf("[8]: Listar tarefas concluidas\n");           // Lista a/as tarefas conclu�das
  printf("[9]: Estatisticas das tarefas\n");            // mostra op��o para ver estat�sticas das tarefas
  printf("Escolha uma opcao: ");                      //solicita uma op��o
  scanf("%d",&Selecionar_opcoes);                     //l� op��o
  limparBuffer();
  switch(Selecionar_opcoes){
  case 1:
  cadastroTarefa(&uPtr->tarefas,&uPtr->nome);        // Chama a fun��o para cadastrar uma nova tarefa para o usu�rio logado
  break;
  case 2:
  editarTarefa(&uPtr->tarefas,&uPtr->nome);          // Chama a fun��o para editar uma tarefa existente
  break;
  case 3:
  excluirTarefa(&uPtr->tarefas,&uPtr->nome);         // Chama a fun��o para excluir uma tarefa
  break;
  case 4:
  exibirIDTarefa(&uPtr->tarefas,&uPtr->nome);        //Chama a fun��o para exibir tarefa por ID
    break;
  case 5:
  listarUsuTarefa(&uPtr->tarefas,&uPtr->nome);       // Chama a fun��o para listar as tarefas do usu�rio logado
  break;
  case 6:
  listarPrioTarefa(&uPtr->tarefas,&uPtr->nome);      //Chama a fun��o para exibir tarefa por prioridade
    break;
  case 7:
  listarTituTarefa(&uPtr->tarefas,&uPtr->nome);      //Chama a fun��o para exibir tarefa por T�tulo
    break;
  case 8:
  exibirTafConcluida(&uPtr->tarefas,&uPtr->nome);    //Chama a fun��o para exibir tarefas conclu�das
    break;
  case 9:
  RelatarTarefa(&uPtr->tarefas,&uPtr->nome);         // Chama a fun��o para exibir estat�sticas das tarefas
  break;
  }
  }
  }

  if(cont<1){                                        //se a vari�vel contadora for menor que 1, significa que o usu�rio n�o est� cadastrado
   printf("\n==== Usuario nao encontrado! ====\n");
   printf("\n==== Cadastre-se para criar suas tarefas ====\n"); //recomenta��o de cadastro
  }
}




void cadastroTarefa(Tarefa *tPtr, usuario *uPtr){
    char linha[100];                                                   //declara��o da string linha para armazenar dados quando for acessar o arquivo
    int cont=0;                                                        //declara��o de vari�vel contadora
    int temDataC, validId = 0, validPrio = 0, validStatus = 0;         //declara��o de vari�veis auxiliares para validar restri��es
    char fileName[2000];                                                //declara��o de string para armazenar o nome do arquivo a partir do nome do usu�rio
    char ID_Temp[100];                                                 //declara��o de string para armazenar temporariamente o ID
    char prioridade1[] = "alta", prioridade2[] = "media", prioridade3[] = "baixa"; //declara��o de strings para garantir prioridades v�lidas
    char status1[] = "concluida", status2[] = "em andamento", status3[] = "pendente", status4[] = "cancelada"; //declara��o de strings para garantir status v�lidos
    int  contTarefa = 0;                                               //declara��o de vari�vel contadora

  sprintf(fileName,"%s.txt",uPtr->nome);                       //chama um arquivo com o nome do usu�rio
  FILE *file = fopen(fileName,"r");                            //abre o arquivo para leitura

  while(fgets(linha,sizeof(linha),file)!=NULL){                //conta quantas tarefas ja existem no arquivo
    contTarefa++;                                              //incrementa 1 � vari�vel contadora quando encontra uma tarefa
    }
  if(contTarefa == MAX_TAREFAS){                               //se atingir o limite de tarefas, exibe a mensagem de limite atingido
    printf("\n==== N�mero m�ximo de tarefas por usu�rio atingido!! ====\n");  //informa que o usu�rio atingiu o limite de tarefas
    return;
  }
    //fscanf(fileName, "%[^,]", tPtr->id);
    printf("\n\t\t\t\t========= Cadastro de um nova tarefa =========\n");
    printf("\nDigite o ID da tarefa (�nico e 8 numeros): ");     //solicita o ID da tarefa ao usu�rio
    scanf("%s", ID_Temp);                        //l� o ID
    ID_Temp[strcspn(ID_Temp, "\n")] = '\0';                      //substitui o \n por \0 na string do ID
    limparBuffer();                                  //copia a string ID_Temp para o membro id da estrutura apontada pelo ponteiro tPtr


    while(fgets(linha,sizeof(linha),file)!=NULL){         //(estrutura para garantir que o usu�rio n�o digite dois IDs iguais) l� as linhas do arquivo e armazena na string linha
    sscanf(linha,"%[^,],s",tPtr->id);                       //l� a string linha at� encontrar a v�rgula e armazena no membro id da estrutura apontada pelo ponteiro tPtr
    if(strcmp(tPtr->id, ID_Temp) == 0){                      //compara se os IDs s�o iguais
    cont=1;                                               //incrementa 1 � vari�vel contadora se os IDs forem iguais
    fclose(file);                                         //fecha o arquivo
    break;                                                //interrompe a estrutura de repeti��o
    }
  }
  while(cont==1){                                      // enquanto cont for igual a 1, solicita ao usu�rio que digite um ID diferente
  printf("\n==== ID repetido! =====\nDigite uma sequencia diferente (8 numeros): ");
  fgets(ID_Temp,sizeof(ID_Temp),stdin);                //l� o ID digitado
  ID_Temp[strcspn(ID_Temp, "\n")] = '\0';              //substitui o \n por \0 na string do ID_Temp para garantir que a string n�o tenha quebra de linha
  if(strcmp(tPtr->id,ID_Temp)==0){                    //compara se os IDs s�o iguais
  cont = 1;                                           //se iguais, atribui 1 a vari�vel contadora e volta para estrutura de pedir o ID novamente
  }else{
  cont = 0;                                          //se diferentes, atribui 0 a vari�vel contadora e garante que n�o pe�a o ID novamente
  strcpy(tPtr->id, ID_Temp);                         //copia a string ID_Temp para o membro id da estrutura apontada pelo ponteiro tPtr
     }
  }


  do {                                              //faz a valida��o do ID enquanto o ID n�o for v�lido
    if (strlen(ID_Temp) != 8) {                    //se o tamanho do ID for diferente de 8, pede outro ID
        printf("\n==== ID inv�lido, n�mero de caracteres diferente de 8! ====\n Insira um ID valido: ");
        fgets(ID_Temp, sizeof(ID_Temp), stdin);      //l� o novo ID
        ID_Temp[strcspn(ID_Temp, "\n")] = '\0';      //substitui o \n por \0 na string do ID para garantir que a string n�o tenha quebra de linha
    } else {                                           //sen�o, o tamanho do ID � v�lido
        validId++;                                     //incrementa 1 � vari�vel contadora
        for (int i = 0; i!=strlen(ID_Temp); i++) {    //la�o que percorre todos os caracteres do ID
            if (!isdigit(ID_Temp[i])){                //verifica se algum caractere n�o � um d�gito
                validId = 0;                           //se n�o for um n�mero, atribui zero a variavel para que a estrutura de repeti��o fa�a outra verifica��o novamente
                printf("\n=== ID invalido, foi inserido uma letra! ====\n Insira um ID valido: "); //solicita um ID v�lido novamente
                fgets(ID_Temp, sizeof(ID_Temp), stdin);                       //l� o ID
                ID_Temp[strcspn(ID_Temp, "\n")] = '\0';                       //substitui o \n por \0 na string do ID para garantir que a string n�o tenha quebra de linha
                break;                                                          //interrope o la�o de repeti��o
            }
        }
    }
} while (validId != 1);                                    // repete a estrutura acima enquanto a vari�vel contadora for diferente de 1
    strcpy(tPtr->id, ID_Temp);
    printf("Digite o titulo da tarefa: ");                 //solicita o t�tulo ao usu�rio
    fgets(tPtr->titulo, 100, stdin);                       //l� o t�tulo
    tPtr->titulo[strcspn(tPtr->titulo, "\n")] = '\0';      //substitui o \n por \0 na string do titulo para garantir que a string n�o tenha quebra de linha

    printf("Digite a descricao da tarefa: ");              //solicita a descri��o da tarefa
    fgets(tPtr->descricao, 1000, stdin);                   //l� descri��o da tarefa
    tPtr->descricao[strcspn(tPtr->descricao, "\n")] = '\0';//substitui o \n por \0 na string da descri��o para garantir que a string n�o tenha quebra de linha

    printf("Digite a data de criacao da tarefa: \n");      //solicita a data de cria��o da tarefa
    printf("Dia: ");
    fgets(tPtr->Data_de_criacao.dia,sizeof(tPtr->Data_de_criacao.dia),stdin);   //l� dia da cria��o da tarefa
    tPtr->Data_de_criacao.dia[strcspn(tPtr->Data_de_criacao.dia, "\n")] = '\0'; //substitui o \n por \0 na string dia para garantir que a string n�o tenha quebra de linha
  getchar();
    printf("Mes: ");
    fgets(tPtr->Data_de_criacao.mes,sizeof(tPtr->Data_de_criacao.mes),stdin);   //l� m�s da cria��o da tarefa
    tPtr->Data_de_criacao.mes[strcspn(tPtr->Data_de_criacao.mes, "\n")] = '\0'; //substitui o \n por \0 na string mes para garantir que a string n�o tenha quebra de linha
  getchar();
    printf("Ano: ");
    fgets(tPtr->Data_de_criacao.ano,sizeof(tPtr->Data_de_criacao.ano),stdin);   //l� ano da cria��o da tarefa
    tPtr->Data_de_criacao.ano[strcspn(tPtr->Data_de_criacao.ano, "\n")] = '\0'; //substitui o \n por \0 na string ano para garantir que a string n�o tenha quebra de linha
getchar();

    printf("Essa tarefa tem data de conclus�o, digite 1 - Sim ou 0 - N�o?: ");  //pergunta ao usu�rio se a tarefa possui data de conclus�o
    scanf("%d", &temDataC);                                                     //l� op��o do usu�rio
    limparBuffer();                                                                  //l� o \n e garante que o c�digo n�o prossiga sem que o usu�rio digite algo
    if(temDataC == 1){                                                          //se op�ao do usu�rio foi 1, pede-se a data
        printf("Digite a data de conclus�o da tarefa: \n");
        printf("Dia: ");
        scanf("%s", tPtr->Data_de_conclusao.dia);                              //l� dia da data de conclus�o
        limparBuffer();
        printf("M�s: ");
        scanf("%s", tPtr->Data_de_conclusao.mes);                              //l� mes da data de conclus�o
        limparBuffer();
        printf("Ano: ");
        scanf("%s", tPtr->Data_de_conclusao.ano);                              //l� ano da data de conclus�o
        limparBuffer();
    }
  if(temDataC == 0){ //If para se n�o tiver data de conclus�o
    strcpy(tPtr->Data_de_conclusao.dia, "00");
    strcpy(tPtr->Data_de_conclusao.mes, "00");
    strcpy(tPtr->Data_de_conclusao.ano, "0000");
    }

    printf("Digite a prioridade da tarefa (alta, media, baixa): ");            //solicita a prioridade da tarefa ao usu�rio
     fgets(tPtr->prioridade, 10, stdin);                                       //l� prioridade
    tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';                  //substitui o \n por \0 na string prioridade para garantir que a string n�o tenha quebra de linha
    do{                                                                        //estrutura de repeti��o para garantir que a prioridade digitada pelo usu�rio seja v�lida
        validPrio = 0;                                                         //vari�vel contadora iniciada com 0
        if(strcmp(tPtr->prioridade, prioridade1) == 0){                        //compara se prioridade digitada pelo usu�rio � igual a prioridade 'alta'
           validPrio++;                                                        //incrementa 1 � vari�vel contadora se forem iguais
        } else if(strcmp(tPtr->prioridade, prioridade2) == 0){                 //compara se prioridade digitada pelo usu�rio � igual a prioridade 'media'
           validPrio++;                                                        //incrementa 1 � vari�vel contadora se forem iguais
        } else if(strcmp(tPtr->prioridade, prioridade3) == 0){                 //compara se prioridade digitada pelo usu�rio � igual a prioridade 'baixa'
           validPrio++;                                                        //incrementa 1 � vari�vel contadora se forem iguais
        } else {                                                               // sen�o, informa que a prioridade � inv�lida
            printf("\n==== Prioridade inv�lida! ====\nDigite uma prioridade v�lida: ");//solicita a prioridade novamente
            fgets(tPtr->prioridade, 10, stdin);                                        //l� prioridade
            tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';                  //substitui o \n por \0 na string prioridade para garantir que a string n�o tenha quebra de linha
        }
    }while(validPrio != 1);                                                    //estrutura acima se repete enquanto a vari�vel contadora for diferente de 1

    printf("Digite o nome do usu�rio repons�vel pela tarefa: ");               //solicita o nome do respons�vel pela tarefa
    fgets(tPtr->responsavel, 100, stdin);                                      //l� nome do respons�vel
    tPtr->responsavel[strcspn(tPtr->responsavel, "\n")] = '\0';                //substitui o \n por \0 na string responsavel para garantir que a string n�o tenha quebra de linha

    printf("Digite o status atual da tarefa (concluida, em andamento, pendente, cancelada): ");//solicita o status da tarefa ao usu�rio
    fgets(tPtr->status, 50, stdin);                                            //l� status
    tPtr->status[strcspn(tPtr->status, "\n")] = '\0';                          //substitui o \n por \0 na string status (garante que a string n�o tenha quebra de linha)
    do{                                                                        //estrutura de repeti��o para garantir que o status digitado pelo usu�rio seja v�lido
        validStatus = 0;                                                       //vari�vel contadora iniciada com 0
        if(strcmp(tPtr->status, status1) == 0){                                //compara se status digitado pelo usu�rio � igual ao status 'concluida'
           validStatus++;                                                      //incrementa 1 � vari�vel contadora se forem iguais
        } else if(strcmp(tPtr->status, status2) == 0){                         //compara se status digitado pelo usu�rio � igual ao status 'em andamento'
           validStatus++;                                                      //incrementa 1 � vari�vel contadora se forem iguais
        } else if(strcmp(tPtr->status, status3) == 0){                         //compara se status digitado pelo usu�rio � igual ao status 'pendente'
           validStatus++;                                                      //incrementa 1 � vari�vel contadora se forem iguais
        } else if(strcmp(tPtr->status, status4) == 0){                         //compara se status digitado pelo usu�rio � igual ao status 'cancelada'
           validStatus++;                                                      //incrementa 1 � vari�vel contadora se forem iguais
        } else {                                                               // sen�o, informa que status � inv�lido
            printf("\n==== Status inv�lido! ====\nDigite um status v�lido: "); //solicita o status novamente
            fgets(tPtr->status, 50, stdin);                                    //l� status
            tPtr->status[strcspn(tPtr->status, "\n")] = '\0';                  //substitui o \n por \0 na string status para garantir que a string n�o tenha quebra de linha
        }
    }while(validStatus != 1);                                                  //estrutura acima se repete enquanto a vari�vel contadora for diferente de 1
    printf("\n\t\t\t\t========= Tarefa cadastrada com sucesso!! =========\n");//mostra que tarefa foi cadastrada
    sprintf(fileName,"%s.txt",uPtr->nome); //cria um arquivo com o nome do usu�rio
    if(contTarefa>=1){
    FILE *file2=fopen(fileName,"a");
    fprintf(file2,"\n");                                 //abre o arquivo no modo de acrescentar conte�do ao final do arquivo
    fprintf(file2,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",tPtr->id,tPtr->titulo,tPtr->descricao, //escreve todos os campos da tarefa na linha do arquivo apontado por file2
    tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano,
    tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano,
    tPtr->prioridade,tPtr->responsavel,tPtr->status);
    fclose(file2);

}
    else if(contTarefa<1){
    FILE *file2 = fopen(fileName,"w");                                          //abre o arquivo no modo de acrescentar conte�do ao final do arquivo
  fprintf(file2,"%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,",tPtr->id,tPtr->titulo,tPtr->descricao, //escreve todos os campos da tarefa na linha do arquivo apontado por file2
    tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano,
    tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano,
    tPtr->prioridade,tPtr->responsavel,tPtr->status);
    fclose(file2);
    }                                                            //fecha o arquivo para evitar problemas futuros

}




void editarTarefa(Tarefa *tPtr,usuario *uPtr){                               //fun��o para editar as tarefas
char fileName[2000];
sprintf(fileName, "%s.txt", uPtr->nome);                                     //cria um arquivo com o nome do usu�rio
FILE *file = fopen(fileName,"r");                                            //abre o arquivo no modo leitura
char linha[100];                                                             //string para armazenar dados quando for acessar o arquivo
char Temp[100];                                                              //string para armazenar dados tempor�rios
int cont=0;                                                                  //declara��o de vari�vel contadora
int contID = 0;                                                              //vari�vel contadora
char selecionar_id[8];                                                       //string para armazenar ID temporariamente
int validId;                                                                 //vari�vel para validar ID
int validPrio;                                                               //vari�vel para validar prioridade
int validStatus;                                                             //vari�vel para validar status
int selecionar_campo;                                                        //vari�vel para armazenar op��o do usu�rio
char prioridade1[] = "alta", prioridade2[] = "media", prioridade3[] = "baixa";  //declara��o de strings para garantir prioridades v�lidas
char status1[] = "concluida", status2[] = "em andamento", status3[] = "pendente", status4[] = "cancelada";//declara��o de strings para garantir status v�lidos
printf("\n\t\t\t\t========= Edi��o de uma tarefa =========\n");
printf("Escreva o ID da tarefa a ser editada: ");                            //solicita o ID da tarefa a ser editada
scanf("%s", selecionar_id);                                                  //l� ID
limparBuffer();
while(fgets(linha,sizeof(linha),file)!=NULL){                                //l� as linhas do arquivo e armazena na string linha at� que n�o haja conte�do no arquivo
sscanf(linha,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",tPtr->id,tPtr->titulo,tPtr->descricao,//l� todos os campos da tarefa a cada v�rgula na linha do arquivo
tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano,
tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano,
tPtr->prioridade,tPtr->responsavel,tPtr->status);

if(strcmp(tPtr->id,selecionar_id)==0){                                       //compara se os IDs s�o iguais
fclose(file);                                                                //fecha o arquivo
cont=1;                                                                      //atribui 1 � vari�vel contadora, indicando que o ID da tarefa digitada pelo usu�rio foi encontrada
break;                                                                       //quebra o loop infinito
}
}
if(cont==1){                                                                 //se vari�vel contadora for 1, mostra op��es de edi��o da tarefa
printf("Tarefa de ID: %s encontrada\n\n",tPtr->id);                          //mostra o ID da tarefa encontrada
printf("[1]:ID\n");                                                            // mostra op��o de mudar Id
printf("[2]:T�tulo\n");                                                        // mostra op��o de mudar t�tulo
printf("[3]:Descri��o\n");                                                     // mostra op��o de mudar descri��o
printf("[4]:Data de cria��o\n");                                               // mostra op��o de mudar data de cria��o
printf("[5]:Data de conclus�o\n");                                             // mostra op��o de mudar data de conclus�o
printf("[6]:Prioridade\n");                                                    // mostra op��o de mudar prioridade
printf("[7]:Respons�vel\n");                                                   // mostra op��o de mudar respons�vel
printf("[8]:Status\n");                                                        // mostra op��o de mudar status
printf("[9]:Editar todos os campos\n");                                        // mostra op��o de mudar todos os campos
printf("Escolha qual campo deseja editar: ");                                //solicita uma op��o
scanf("%d",&selecionar_campo);                                               //l� op��o
switch(selecionar_campo){
case 1:
                                                      //copia a string temp pra string id

  sprintf(fileName,"%s.txt",uPtr->nome);                                     //cria um arquivo com o nome do usu�rio
  FILE *file2 = fopen(fileName,"r");                                         //abre o arquivo no modo leitura

printf("Digite o novo ID: ");                                                //solicita novo ID
fgets(Temp,sizeof(Temp),stdin);                                              //l� no ID
Temp[strcspn(Temp, "\n")] = '\0';                                            //substitui o \n por \0 na string Temp para garantir que a string n�o tenha quebra de linha
limparBuffer();

  while(fgets(linha,sizeof(linha),file2)!=NULL){                             //l� as linhas do arquivo e armazena na string linha at� que n�o haja conte�do no arquivo
    sscanf(linha,"%[^,]",tPtr->id);                                          //l� os caracteres de linha at� a virgula e armazena no campo id
    if(strcmp(Temp,tPtr->id)==0){                                            //se od IDs forem iguais, atribui 1 � vari�vel contadora
    contID=1;
    fclose(file2);                                                          //fecha o arquivo apontado por file2
    break;                                                                  //quebra o loop
    }
  }
  while(contID==1){                                                        //enquanto a vari�vel contadora for 1,indique que os ids s�o repetidos
  printf("\n==== ID repetido! =====\nDigite uma sequencia diferente (8 numeros): ");//pede-se outro id diferente
  scanf("%s", Temp);                                                        //l� novo id
  limparBuffer();
  if(strcmp(tPtr->id,Temp)==0){                                            //se os IDs forem iguais, atribui 1 � vari�vel contadora
  contID = 1;
  }else{                                                                   //se os IDs forem diferentes, ent�o � v�lido e
  strcpy(tPtr->id, Temp);                                                  //copia a string tempor�ria v�lida para o campo id
  contID = 0;                                                              //validado, ent�o atribui zero � vari�vel contadora
    }
  }
fclose(file2);
strcpy(tPtr->id, Temp);
while(1){                                                                  // Loop infinito, executa at� ser interrompido por um break para Verificar os requisitos do id
    if (strlen(tPtr->id) != 8) {                                           //condicinal para garantir que o id tenha exatamente 8 caracteres
        printf("\n==== ID inv�lido, n�mero de caracteres diferente de 8! ====\n Insira um ID valido: ");
        fgets(tPtr->id, sizeof(tPtr->id), stdin);
        tPtr->id[strcspn(tPtr->id, "\n")] = '\0';
    }else{                                                                //sen�o, incrementa 1 � vari�vel contadora, indicando que o tamanho do id � v�lido
        validId=1;
        for (int i = 0; i!=strlen(tPtr->id); i++) {                       //la�o de repeti��o para garantir que o id seja somente n�meros
            if (!isdigit(tPtr->id[i])){
                validId = 0;                                              //se n�o for digito, atribui 1 � vari�vel contadora para que o id passe por toda verifica��o novamente
                printf("\n=== ID invalido, foi inserido uma letra! ====\n Insira um ID valido: ");// solicita o id novamente
                fgets(tPtr->id, sizeof(tPtr->id), stdin);                 //l� id
                tPtr->id[strcspn(tPtr->id, "\n")] = '\0';                 //substitui o \n por \0 na string id para garantir que a string n�o tenha quebra de linha
                break;                                                    //quebra o la�o de repeti��o quando o id se torna v�lido
            }
        }
    }
    if(validId==1){                                                        //se o id for v�lido, o break quebra o loop infinito
    break;
    }
    }
break;                                                                    //break para interromper o switch caso op��o 1 for realizada
case 2:
printf("Digite o novo titulo: ");                                        //solicita um novo t�tulo
scanf("%s",tPtr->titulo);                                          //l� o titulo                       //substitui o \n por \0 na string id para garantir que a string n�o tenha quebra de linha
limparBuffer();
break;
case 3:
printf("Digite a nova descri��o: ");                                     //solicita uma nova descri��o
fgets(tPtr->descricao, strlen(tPtr->descricao), stdin);                                         //l� a nova descri��o
limparBuffer();
break;
case 4:
printf("Digite a nova data de cri��o: ");                                //solicita nova data de cria��o
scanf("%s/%s/%s",tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano);
limparBuffer();
break;
case 5:
printf("Digite a nova data de conclus�o: ");                            //solicita nova data de conclus�o
scanf("%s/%s/%s",tPtr->Data_de_conclusao.dia,tPtr->Data_de_conclusao.mes,tPtr->Data_de_conclusao.ano);
limparBuffer();
break;
case 6:
printf("Digite a nova prioridade da tarefa: ");                         //solicita a nova prioridade
fgets(tPtr->prioridade,10,stdin);                                       //l� nova prioridade
tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';
limparBuffer();               //substitui o \n por \0 na string prioridade para garantir que a string n�o tenha quebra de linha
    do{                                                                 //estrutura de repeti��o para garantir que a prioridade digitada pelo usu�rio seja uma v�lida
        validPrio = 0;
        if(strcmp(tPtr->prioridade, prioridade1) == 0){                 //compara se prioridade digitada pelo usu�rio � igual a prioridade  alta
           validPrio++;
        } else if(strcmp(tPtr->prioridade, prioridade2) == 0){          //compara se prioridade digitada pelo usu�rio � igual a prioridade  media
           validPrio++;
        } else if(strcmp(tPtr->prioridade, prioridade3) == 0){          //compara se prioridade digitada pelo usu�rio � igual a prioridade baixa
           validPrio++;
        } else {                                                        //se n�o for uma das 3 op��es acima, solicita uma prioridade v�lida
            printf("\n==== Prioridade inv�lida! ====\nDigite uma prioridade v�lida: ");
            fgets(tPtr->prioridade, 10, stdin);                         //l� prioridade
            tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';
            limparBuffer();   //substitui o \n por \0 na string prioridade para garantir que a string n�o tenha quebra de linha
        }
    }while(validPrio != 1);                                             //estrutura acima se repete enquanto a vari�vel contadora for diferente de 1
    limparBuffer();
case 7:
printf("Digite o novo respons�vel pela tarefa: ");                     //solicita novo nome do respons�vel da tarefa
scanf("%s",tPtr->responsavel);                                    //l� novo nome do respons�vel
limparBuffer();
case 8:
printf("Digite o novo status da tarefa: ");                            //solicita novo status da tarefa
fgets(tPtr->status,50,stdin);                                          //l� novo status
tPtr->status[strcspn(tPtr->status, "\n")] = '\0';
limparBuffer();                      //substitui o \n por \0 na string status para garantir que a string n�o tenha quebra de linha
    do{                                                                //estrutura de repeti��o para garantir que o status digitado pelo usu�rio seja uma v�lido
        validStatus = 0;
        if(strcmp(tPtr->status, status1) == 0){                        //compara se status digitado pelo usu�rio � igual ao status concluida
           validStatus++;
        } else if(strcmp(tPtr->status, status2) == 0){                 //compara se status digitado pelo usu�rio � igual ao status em andamento
           validStatus++;
        } else if(strcmp(tPtr->status, status3) == 0){                 //compara se status digitado pelo usu�rio � igual ao status pendente
           validStatus++;
        } else if(strcmp(tPtr->status, status4) == 0){                 //compara se status digitado pelo usu�rio � igual ao status cancelada
           validStatus++;
        } else {                                                        //se n�o for uma das 4 op��es acima, solicita um novo status v�lido
            printf("\n==== Status inv�lido! ====\nDigite um status v�lido: ");
            fgets(tPtr->status, 50, stdin);                             //l� novo status
            tPtr->status[strcspn(tPtr->status, "\n")] = '\0';
            limparBuffer();           //substitui o \n por \0 na string status para garantir que a string n�o tenha quebra de linha
        }
    }while(validStatus != 1);                                           //estrutura acima se repete enquanto a vari�vel contadora for diferente de 1
limparBuffer();
case 9:
                                                           //declara��o de vari�vel contadora
  sprintf(fileName,"%s.txt",uPtr->nome);                                //chama um arquivo com o nome do usu�rio
  FILE *file3 = fopen(fileName,"r");                                    //abre o arquivo no modo leitura

printf("Digite o novo ID: ");                                           //solicita novo id neste caso
scanf("%s",Temp);                                                       //l� id                                                 //copia a string Temp para a string id para fazer compara��es posteriormente
limparBuffer();
contID = 0;                                      //substitui o \n por \0 na string status para garantir que a string n�o tenha quebra de linha


    while(fgets(linha,sizeof(linha),file3)!=NULL){                       //l� as linhas do arquivo e armazena na string linha at� que n�o haja conte�do no arquivo
    sscanf(linha,"%[^,]",tPtr->id);                                      //l� os caracteres de linha at� a virgula e armazena no campo id
    if(strcmp(Temp,tPtr->id)==0){                                        //se od IDs forem iguais, atribui 1 � vari�vel contadora e indica que o id n�o � v�lido
    contID=1;
    fclose(file3);                                                       //fecha o arquivo
    break;                                                               //interrrompe o loop infinito
    }
  }
  while(contID==1){                                                     //estrutura de repeti��o para garantir que o novo id seja diferente
  printf("\n==== ID repetido! =====\nDigite uma sequencia diferente (8 numeros): "); //solicita novo id
  scanf("%s", Temp);                                                                 //le novo id
  limparBuffer();
  if(strcmp(tPtr->id,Temp)==0){                                                     //compara se os IDs s�o iguais
  contID = 1;
  }else{                                                                            //se n�o for, copia o id da vari�vel tempor�ria para o campo id
  strcpy(tPtr->id, Temp);
  contID = 0;                                                                       //atribui 1 � vari�vel contadora, indicando que o id foi diferente
  }
  }
fclose(file3);
strcpy(tPtr->id, Temp);
do {                                                                                //faz a valida��o do ID enquanto o ID n�o for v�lido
    if (strlen(tPtr->id) != 8) {                                                    //se o tamanho do ID for diferente de 8, pede outro ID
        printf("\n==== ID inv�lido, n�mero de caracteres diferente de 8! ====\n Insira um ID valido: ");
        fgets(tPtr->id, sizeof(tPtr->id), stdin);                                   //l� novo id
        tPtr->id[strcspn(tPtr->id, "\n")] = '\0';
        limparBuffer();                                   //substitui o \n por \0 na string status para garantir que a string n�o tenha quebra de linha
      } else {                                                                      //sen�o, indica que o tamanho � v�lido
        validId++;
        for (int i = 0; i!=strlen(tPtr->id); i++) {                           //la�o que percorre todos os caracteres do ID
            if (!isdigit(tPtr->id[i])){                                       //verifica se algum caractere n�o � um d�gito
                validId = 0;                                                  //se n�o for um n�mero, atribui zero a variavel para que a estrutura de repeti��o fa�a outra verifica��o novamente
                printf("\n=== ID invalido, foi inserido uma letra! ====\n Insira um ID valido: ");//solicita novo id
                fgets(tPtr->id, sizeof(tPtr->id), stdin);                                         //l� novo id
                tPtr->id[strcspn(tPtr->id, "\n")] = '\0';
                limparBuffer();                                         //substitui o \n por \0 na string id para garantir que a string n�o tenha quebra de linha
              break;                                                                     //interrope o la�o de repeti��o garantindo que o novo n�o possui caracteres diferentes de numeros
            }
        }
    }
} while (validId != 1);                                                                 // repete a estrutura acima enquanto a vari�vel contadora for diferente de 1
printf("Digite o novo titulo: ");                                                       //quando as retri��es acimas fores validadas, solicita novo titulo
scanf("%s",tPtr->titulo);                                                          //l� novo titulo//substitui o \n por \0 na string titulo para garantir que a string n�o tenha quebra de linha
limparBuffer();
printf("Digite a nova descri��o: ");                                    //solicita nova descri��o
fgets(tPtr->descricao, strlen(tPtr->descricao), stdin);                                       //l� nova descri��o               //substitui o \n por \0 na string descri��o para garantir que a string n�o tenha quebra de linha
limparBuffer();
printf("Digite a nova data de cri��o: ");                                //solicita nova data de cria��o
scanf("%s/%s/%s",&tPtr->Data_de_criacao.dia,&tPtr->Data_de_criacao.mes,&tPtr->Data_de_criacao.ano);
limparBuffer();
printf("Digite a nova data de conclus�o: ");                                                       //solicita nova data de conclusao
scanf("%s/%s/%s",&tPtr->Data_de_conclusao.dia,&tPtr->Data_de_conclusao.mes,&tPtr->Data_de_conclusao.ano);
limparBuffer();//l� nova data de conclusao
printf("Digite a nova prioridade da tarefa: ");                                                //solicita nova prioridade
fgets(tPtr->prioridade,10,stdin);                                                              //l� nova prioridade
tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';
limparBuffer();                                      //substitui o \n por \0 na string prioridade para garantir que a string n�o tenha quebra de linha
    do{                                                                                        //estrutura de repeti��o para garantir que a prioridade digitada pelo usu�rio seja v�lida
        validPrio = 0;
        if(strcmp(tPtr->prioridade, prioridade1) == 0){                                        //compara se prioridade digitada pelo usu�rio � igual a prioridade 'alta'
           validPrio++;
        } else if(strcmp(tPtr->prioridade, prioridade2) == 0){                                 //compara se prioridade digitada pelo usu�rio � igual a prioridade 'media'
           validPrio++;
        } else if(strcmp(tPtr->prioridade, prioridade3) == 0){                                 //compara se prioridade digitada pelo usu�rio � igual a prioridade 'baixa'
           validPrio++;
        } else {                                                                               // sen�o, informa que a prioridade � inv�lida
            printf("\n==== Prioridade inv�lida! ====\nDigite uma prioridade v�lida: ");        //solicita prioridade novamente
            fgets(tPtr->prioridade, 10, stdin);                                                //l� prioridade
            tPtr->prioridade[strcspn(tPtr->prioridade, "\n")] = '\0';
            limparBuffer();                          //substitui o \n por \0 na string prioridade para garantir que a string n�o tenha quebra de linha
        }
    }while(validPrio != 1);                                                                    //estrutura acima se repete enquanto a vari�vel contadora for diferente de 1
limparBuffer();
printf("Digite o novo respons�vel pela tarefa: ");                                             //solicita nome do respons�vel
scanf("%s",tPtr->responsavel);                                      //l� nome do respons�vel                                   //substitui o \n por \0 na string prioridade para garantir que a string n�o tenha quebra de linha
limparBuffer();
printf("Digite o novo status da tarefa: ");                                                   //solicita novo status da tarefa
fgets(tPtr->status,50,stdin);                                                                 //l� status
tPtr->status[strcspn(tPtr->status, "\n")] = '\0';
limparBuffer();                                            //substitui o \n por \0 na string status para garantir que a string n�o tenha quebra de linha
    do{                                                                                       //estrutura de repeti��o para garantir que o status digitado pelo usu�rio seja v�lido
        validStatus = 0;
        if(strcmp(tPtr->status, status1) == 0){                                               //compara se status digitado pelo usu�rio � igual ao status 'concluida'
           validStatus++;
        } else if(strcmp(tPtr->status, status2) == 0){                                        //compara se status digitado pelo usu�rio � igual ao status 'em andamento'
           validStatus++;
        } else if(strcmp(tPtr->status, status3) == 0){                                        //compara se status digitado pelo usu�rio � igual ao status 'pendente'
           validStatus++;
        } else if(strcmp(tPtr->status, status4) == 0){                                        //compara se status digitado pelo usu�rio � igual ao status 'cancelada'
           validStatus++;
        } else {                                                                              // sen�o, informa que status � inv�lido
            printf("\n==== Status inv�lido! ====\nDigite um status v�lido: ");                //solicita novo status
            fgets(tPtr->status, 50, stdin);                                                   //l� status
            tPtr->status[strcspn(tPtr->status, "\n")] = '\0';
            limparBuffer();                                 //substitui o \n por \0 na string status para garantir que a string n�o tenha quebra de linha
        }
    }while(validStatus != 1);                                                                 //estrutura acima se repete enquanto a vari�vel contadora for diferente de 1
limparBuffer();
break;
}
}

sprintf(fileName,"%s.txt",uPtr->nome);                                                        //chama o arquivo com o nome do usu�rio
FILE *file4 = fopen(fileName,"r+");                                                           //abre o arquivo no modo de leitura quanto de escrita
fseek(file4, -strlen(linha), SEEK_CUR);                                                       //Procura no arquivo a primeira posi��o da linha
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

void excluirTarefa(Tarefa *tPtr,usuario *uPtr){                                              //Fun��o para exclus�o de uma tarefa
char linha[100];                                                                             //contador de linha
int cont=0;
int Cont_del=0;                                                                                  //contador
char fileName[2000];                                                                          //Vari�vel para o nome do arquivo
sprintf(fileName,"%s.txt",uPtr->nome);                                                       //pega o arquivo com o nome do us�ario
FILE *file = fopen(fileName,"r");                                                            //Abre o arquivo do usu�rio
FILE *file2 = fopen("Temp.txt","w");                                                         //Abre o arquivo tempor�rio
char selecionar_id[9];                                                                       //Vari�vel para guadar o ID
printf("\n\t\t\t\t========= Exclus�o de uma tarefa =========\n");
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
if (remove(fileName) == 0 && remove("Temp.txt") == 0) {             //Faz com que exclua o arquivo do usu�rio seja excluido e substituido pelo arquivo tempor�rio onde n�o tem mais essa tarefa
        printf("\n==== Tarefa exclu�da com sucesso!! ====\n");
        } else {
        printf("\n==== Erro ao excluir a tarefa!! ====\n");
        }
}
if(Cont_del>1){
if (remove(fileName) && rename("Temp.txt", fileName) == 0) {             //Faz com que exclua o arquivo do usu�rio seja excluido e substituido pelo arquivo tempor�rio onde n�o tem mais essa tarefa
        printf("\n==== Tarefa exclu�da com sucesso!! ====\n");
        } else {
        printf("\n==== Erro ao excluir a tarefa!! ====\n");
        }
}

}
if(cont<1){
printf("\n==== Tarefa nao encontrada!! ====\n");                                              //Se o cont n�o � 1 n�o tem uma tarefa com esse ID, logo n�o ser� encontrada
}
}


void exibirIDTarefa(Tarefa *tPtr,usuario *uPtr){    //Fun��o para exibir a tarefa com base no ID
char fileName[2000];
sprintf(fileName,"%s.txt",uPtr->nome);              //Abre a file com o nome do usu�rio
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
printf("==== Data de Conclus�o ====\n");
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

void listarPrioTarefa(Tarefa *tPtr,usuario *uPtr){                                //Fun��o para lista por prioridade
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
printf("==== Data de Conclus�o ====\n");
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
sprintf(fileName,"%s.txt",uPtr->nome);                // Procura o arquivo com o nome do usu�rio
FILE *file = fopen(fileName,"r");                     // Abre o arquivo com o nome de usu�rio
char linha[100];
int cont=0;
char selecionar_titu[9];
printf("\n\t\t\t\t========= Listagem por T�tulo =========\n");
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
printf("==== Data de Conclus�o ====\n");
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

void listarUsuTarefa(Tarefa *tPtr,usuario *uPtr){      //Lista as tarefas do usu�rio
char fileName[2000];
char linha[100];
int cont=0;
sprintf(fileName,"%s.txt",uPtr->nome);
FILE *file = fopen(fileName,"r");

printf("\\n\t\t\t\t========= Tarefas do Usuario %s =========\n",uPtr->nome);

while(fgets(linha,sizeof(linha),file)!=NULL){     //Vai listar todas as tarefas ate n�o conter mais nenhuma
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
printf("==== Data de Conclus�o ====\n");
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

void exibirTafConcluida(Tarefa *tPtr,usuario *uPtr){ //Exibir tarefa que est�o marcadas como conclu�da
char fileName[2000];
char concluida[] = "conclu�da";
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
if(strcmp(tPtr->status,concluida)==0){ //Compara para saber se tem alguma tarefa com status conclu�do
cont=1;
printf("\n==== ID ====\n");
printf("%s\n",tPtr->id);
printf("==== Titulo ====\n");
printf("%s\n",tPtr->titulo);
printf("==== Descricao ====\n");
printf("%s\n",tPtr->descricao);
printf("==== Data de inicio ====\n");
printf("%s/%s/%s\n",tPtr->Data_de_criacao.dia,tPtr->Data_de_criacao.mes,tPtr->Data_de_criacao.ano);
printf("==== Data de Conclus�o ====\n");
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
void RelatarTarefa(Tarefa *tPtr,usuario *uPtr) {  //Mostra as estat�sticas do usu�rio
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
contCon++;  //Contador de tarefas conclu�das
}
if(strcmp(tPtr->status,status2)==0){
contAnd++;  //Contador de tarefas em andamento
}
if(strcmp(tPtr->status,status3)==0){
contPend++;  //Contador de tarefas em pend�ncia
}
if(strcmp(tPtr->status,status4)==0){
contCanc++;   //Contador de tarefas canceladas
}
if(strcmp(tPtr->prioridade,prioridade1)==0){
contAlt++; //Contador de prioridade alta
}
if(strcmp(tPtr->prioridade,prioridade2)==0){
contMed++;  //Contador de prioridade m�dia
}
if(strcmp(tPtr->prioridade,prioridade3)==0){
contBaix++;  //Contador de prioridade baixa
}
}
if(contTaf == 0){
    printf("O usuario %s, n�o possui nenhuma tarefa cadastrada\n", uPtr->nome); //If se o usu�rio n�o tem tarefas
} else if(contTaf == 1){
    printf("O usuario %s, cadastrou %d tarefa\n", uPtr->nome,contTaf);   //If se o usu�rio tem 1 tarefa
}else if(contTaf > 1){
    printf("O usuario %s, cadastrou %d tarefas\n", uPtr->nome,contTaf); //If se o usu�rio tem mais de uma tarefa
}

printf("Tarefas conclu�das: %d\n", contCon);
printf("Tarefas em andamento: %d\n", contAnd);
printf("Tarefas em pend�ncia: %d\n", contPend);
printf("Tarefas canceladas: %d\n", contCanc);
printf("Tarefas com prioridade alta: %d\n", contAlt);
printf("Tarefas com prioridade m�dia: %d\n", contMed);
printf("Tarefas com prioridade baixa: %d\n", contBaix);
}
