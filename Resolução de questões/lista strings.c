#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//1----------------------------------------------------------------------------------
/*int main(){
	char frase[]="progamadores sao ferramentas para converter cafeina em codigo";
	int cont=strlen(frase),i;
	printf("contem %d letras\n\n",cont);
	for( i=0;i<=cont;i++){
		if(frase[i]!='a' && frase[i]!='e' && frase[i]!='i' && frase[i]!='o' && frase[i]!='u' && frase[i]!='A'&& frase[i]!='E' && frase[i]!='I'&& frase[i]!='O' && frase[i]!='U'){
			printf("%c",frase[i]);
		} 
	}
}
*/
//2-------------------------------------------------------------------------------------------------
/*int main(){
	char frase[]="a melhor maneira de prever o futuro e inventa-lo";
	int i,cont=0;
	int aux=strlen(frase);
	for(i=0;i<=aux;i++){
		if(frase[i]=='a' || frase[i]=='e' || frase[i]=='i' || frase[i]=='o' || frase[i]=='u'){
			cont++;
		}
	}printf("possui %d vogais ",cont);
}
*/
//3---------------------------------------------------------------------------------------------
/*int main(){
int cont=0,i;
char frase[20];
char caracter;
fgets(frase,20,stdin);
fflush(stdin);
puts(frase);
printf("qual caractere voce quer buscar?");
scanf("%c",&caracter);
printf("   %c\n",caracter);
		int aux=strlen(frase);
			for(i=0;i<=aux;i++){
				if(frase[i]==caracter){
					cont++;
				}
		}printf("possui %d unidades do caracter %c",cont,caracter);
}
*/
 //4-------------------------------------------------------------------------------------------------
 /*int main(){
 	char frase[20];
 	char palavra[10];
 	char *tokenptr;
 	int cont=0,i,aux;
 	printf("digite uma frase: ");
 		fgets(frase,20,stdin);
 			fflush(stdin);
 				puts(frase);
 		printf("digite uma palavra a ser buscada: ");
 			fgets(palavra,10,stdin);
 			fflush(stdin);
 				puts(palavra);
 				
 				tokenptr=strtok(frase," ");
 				
 			
 				while(tokenptr!= NULL){
 						if(strcmp(tokenptr,palavra)==0){
 							cont++;
 							
						 }
				}	
			 printf("\na palavra %s possui %d ocorrências na frase",palavra,cont);

return 0;
} *///5----------------------------------------------------------------------------------------------------
 /*int main(){
 	char sigla[2];
 	fgets(sigla,3,stdin);
 	puts(sigla);
 	
 	if(sigla[0]=='c' && sigla[1]=='e'){
	 printf("cearense!");
}
 	else if(sigla[0]=='p' && sigla[1]=='i'){
	 printf("piauiense. ");
	 }
	 
	 return 0;
 }*/
 //6----------------------------------------------------------------------------------------------
/* int main(){
 	int i;
 	char frase[100];
 	printf("digite uma frase: ");
 	fgets(frase,100,stdin);
 	fflush(stdin);
 	
 		for(i=0;i<=strlen(frase);i++){
 			if(frase[i]!=' '){
 				printf("%c",frase[i]);
 				
			 }else{
			 printf("\n");
			 }
		 }
		 return 0;
 }
 */
 //7--------------------------------------------------------------------------------------------------
 /*int main(){
 	char frase[100];
 	int qv=0,qc=0,i;
 	printf("digite uma frase: ");
 	fgets(frase,100,stdin);
 	   
 	   for(i=0;i<strlen(frase);i++){
 	   		if(frase[i]=='a' || frase[i]=='e' || frase[i]=='i' || frase[i]=='o' || frase[i]=='u' || frase[i]=='A'){
 	   			qv++;
				}else{
					qc++;
				}
		}printf("possui %d vogais e %d consoantes",qv,qc-1);
 	
 }
 */
 //8---------------------------------------------------------------------------------------------------
 /*int main(){
 	int i;
 	char n;
 	char frase[100];
 	printf("digite uma letra ");
 	scanf("%c",&n);
 	fflush(stdin);
 	printf("digite uma frase ");
 		fgets(frase,100,stdin);
 		fflush(stdin);
 			for(i=0;i<strlen(frase);i++){
 				if(frase[i]!=n){
 					printf("%c",frase[i]);
				 	} 					
				 }
 }*/
 //9------------------------------------------------------------------------------------------------
 /*
 int main(){
 	char frase[40];
 	int i;
 	printf("digite uma frase ");
 	fgets(frase,40,stdin);
 	
 	while(strlen(frase)>20){
 			printf("frase invalida, digite novamente ");
 			fgets(frase,40,stdin);
		 }for(i=0;i<strlen(frase);i++){
		 	printf("%c\n",frase[i]);
		 }
 }
 */
 //10---------------------------------------------------------------------------------------------------
 /*int main(){
 	int i;
 	char frase[100];
 	printf("digite uma frase ");
 	fgets(frase,100,stdin);
 	
 		for(i=strlen(frase);i>=0;i--){
 			printf("%c",frase[i]);
		 }
 }
 */
 //11-----------------------------------------------------------------------------------------------------
 /*int main(){
 	char f1[100];
 	int i,cont=0;
 	char f2[100];
 	printf("digite a primeira frase ");
 	fgets(f1,100,stdin);
 	fflush(stdin);
 	printf("digite a segunda frase ");
 	fgets(f2,100,stdin);
 	
 		for(i=0;i<strlen(f1);i++){
 			f1[i]=tolower(f1[i]);
		 } for(i=0;i<strlen(f2);i++){
 			f2[i]=tolower(f2[i]);
		 } 
		 
	 
 	if(strcmp(f2,f1)==0){
 		printf("sao iguais");
	 }else{
	 	printf("são diferentes");
	 }
}*/
 
 //12------------------------------------------------------------------------------------------------------------
/* int main(){
 	int i;
 	char frase[100];
 	char velho,novo;
 	printf("digite uma frase: ");
 	fgets(frase,100,stdin);
 	fflush(stdin);
 		printf("qual caracter você quer retirar da frase? ");
 		scanf("%c",&velho);
 		fflush(stdin);
 		printf("qual caracter você deseja inserir? ");
 		scanf("%c",&novo);
 		
		 for(i=0;i<strlen(frase);i++){
		 	if(frase[i]==velho){
		 		frase[i]=novo;
			 }
		 }	printf("%s",frase);	
 }*/
 //13---------------------------------------------------------------------------------------------------------------
 /*int main(){
 	int i;
 	char senha[100];
 	printf("digite uma senha: ");
 	fgets(senha,100,stdin);
 	fflush(stdin);
					 	for(i=0;i<strlen(senha);i++){
 					if(isdigit(senha[i])!=0){
 						printf(" ");
					 }else{
					 while(strlen(senha)<=6 || strlen(senha)>=12 ){
 					printf("digite uma senha válida: ");
 									fgets(senha,100,stdin);
 									fflush(stdin);
				 }	
		}
	}
}
*/ 
//------------------------PONTEIROS--------------------------------------------------
//1---------------------------------------------------------------------------------
/*int main(){
	int n=10;
	int *ponteiro;
	ponteiro=&n;
	printf("o valor de n eh %d e o endereço de ponteiro eh %")
}*/ 
 
 //-------------------TIPOS ESTRUTURADOS--------------------------------------
 
 /*typedef struct{
 	int dia,mes,ano;
 }Nascimento;
 typedef struct{
 	int conta,agencia;
 	char nome[30];
 	Nascimento nascimento;
 }dados;
 
	 	void leitura_data(dados *ptr){
	 		printf("--------leitura dos dados----------\n");
	 	printf("digite seu dia de nascimento: ");
	 	scanf("%d",&ptr->nascimento.dia);
	 	getchar();
	 	printf("digite seu mes de nascimento: ");
	 	scanf("%d",&ptr->nascimento.mes);
	 	getchar();
	 	printf("digite seu ano de nascimento: ");
	 	scanf("%d",&ptr->nascimento.ano);
	 	getchar();
	 }
 			void leitura(dados *ptr2){
			 	
			 	printf("digite nome: ");
			 	fgets(ptr2->nome,30,stdin);
			 	fflush(stdin);
			 	printf("digite conta: ");
			 	scanf("%d",&ptr2->conta);
			 	getchar();
			 	printf("digite agencia: ");
			 	scanf("%d",&ptr2->agencia);
			 	getchar();
			 }	 void mostrar(dados *p){
			 	printf("---------------mostrando os dados------------------\n");
			 	printf("nome %snascimento: %d/%d/%d\nagencia: %d\nconta: %d\n ",p->nome,p->nascimento.dia,p->nascimento.mes,p->nascimento.ano,p->agencia,p->conta);
			 }
					 int main(){
					 	dados s;
					 	dados *ptr=&s;
					 	leitura_data(ptr);
					 	leitura(ptr);
					 	mostrar(ptr);
 	return 0;
 }*/
/*
 typedef struct{
 	int dia,mes,ano;
 }Data;
 typedef struct{
 	int conta,agencia;
 	char nome[30];	
 }Dados;

 typedef struct{
 	Data data;
 	int valor;
 	Dados favorecido;
 	Dados depositante;
 }Cliente;
 
	 	void leitura_data(Cliente *ptr){
	 		printf("--------leitura da data do depósito----------\n");
	 	printf("dia: ");
	 	scanf("%d",&(ptr->data.dia));
	 	getchar();
	 	printf("mes: ");
	 	scanf("%d",&ptr->data.mes);
	 	getchar();
	 	printf("ano: ");
	 	scanf("%d",&ptr->data.ano);
	 	getchar();
	 }
 			void leituraDepositante(Cliente *ptr2){
			 	printf("--------leitura dos dados do depositante------------\n");
			 	printf("nome: ");
			 	fgets(ptr2->depositante.nome,30,stdin);
			 	fflush(stdin);
			 	printf("conta: ");
			 	scanf("%d",&ptr2->depositante.conta);
			 	getchar();
			 	printf("agencia: ");
			 	scanf("%d",&ptr2->depositante.agencia);
			 	getchar();
			 	printf("valor: ");
			 	scanf("%d",&ptr2->valor);
			 	getchar();
			 }
			 void leituraFavorecido(Cliente *ptr){
			 	printf("--------leitura dos dados do favorecido------------\n");
			 	printf("nome: ");
			 	fgets(ptr->favorecido.nome,30,stdin);
			 	ptr->favorecido.nome[strcspn(ptr->favorecido.nome,"\n")]='\0';
			 	printf("conta: ");
			 	scanf("%d",&ptr->favorecido.conta);
			 	getchar();
			 	printf("agencia: ");
			 	scanf("%d",&ptr->favorecido.agencia);
			 	getchar();
			 }
			 
			 	 void mostrar(Cliente *pd ){
			 	printf("---------------mostrando os dados do depositante------------------\n");
			 	printf("nome: %sdata do deposito: %d/%d/%d\nagencia: %d\nconta: %d\n valor: %d\n",pd->depositante.nome,pd->data.dia,pd->data.mes,pd->data.ano,pd->depositante.agencia,pd->depositante.conta,pd->valor);
					printf("-------------mostrando dados do favorecido-----------------\n");
					printf("nome: %s agencia: %d\nconta: %d\n",pd->favorecido.nome,pd->favorecido.agencia,pd->favorecido.conta);
								 }
					 int main(){
					 	Cliente s;
					 	Cliente *ptr=&s;
					 	leitura_data(ptr);
					 	
					 		leituraDepositante(ptr);
					 			leituraFavorecido(ptr);
						 			mostrar(ptr);
 	return 0;
 };*/
/*
typedef struct{
	int media,matricula;
	char nome[30];
}Aluno;

void leitura(Aluno *ptr){
	int a=0,b=0,c=0;
	while(1){printf("digite seu nome: ");
		fgets(ptr->nome,30,stdin);
		fflush(stdin);
		while(nome!='1 && ')
		if(ptr->media>=0 || ptr->media<=10){
			break;
		}if(strlen(ptr->matricula)==6){
			break;
		}if(*ptr->nome!='1' && *ptr->nome!='2' && *ptr->nome!='3' && *ptr->nome!='4' && *ptr->nome!='5'){
			break;
		}
	}printf("digite seu nome: " );
	fgets(ptr->nome,30,stdin);
	fflush(stdin);
	printf("sua matricula: ");
	scanf("%d",&ptr->matricula);
	getchar();
	printf("sua media: ");
	scanf("%d",&ptr->media);
	getchar();
};
int main(){
	Aluno aux;
	Aluno *ptr=&aux;
	leitura(ptr);
};*/
 
 /*int main(){
 int i;
 	char v[4]="1,2,3,4";
 	int *ptr=&v;
 	for(i=0;i<4;i++){
 		printf("%p\n",ptr);
 		ptr++;
	 }
 }*/
 //---------------------------VETORES DE CARACTERES------------------------------------------------------------------------------
 
 /*int main(){
 	char v[8]="abutrebe";
 	char *p;
 	p=strrchr(v,'b');
 	printf("%c",*p);
 		printf("%c",*(p+1));
 }*/
 /*#define MAX_NOME 50
#define TAM_MATRICULA 7

typedef struct {
    char nome[MAX_NOME];
    char matricula[TAM_MATRICULA];
    float media;
} Aluno;

int validarNome(const char *nome) {
    int i;
    for (i = 0; nome[i] != '\0'; i++) {
        if (isdigit(nome[i])) {
            return 0; // nome inválido
        }
    }
    return 1; // nome válido
}

int validarMatricula(const char *matricula) {
	int i;
    if (strlen(matricula) != TAM_MATRICULA - 1) {
        return 0; // matrícula inválida
    }
    for ( i = 0; i < TAM_MATRICULA - 1; i++) {
        if (!isdigit(matricula[i])) {
            return 0; // matrícula inválida
        }
    }
    return 1; // matrícula válida
}

int validarMedia(float media) {
    if (media < 0 || media > 10) {
        return 0; // média inválida
    }
    return 1; // média válida
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Aluno aluno;

    while (1) {
        printf("Digite o nome do aluno: ");
        fgets(aluno.nome, sizeof(aluno.nome), stdin);
        aluno.nome[strcspn(aluno.nome, "\n")] = '\0'; // Remover o caractere de nova linha

        if (!validarNome(aluno.nome)) {
            printf("Nome inválido. O nome não deve conter dígitos.\n");
            continue;
        }

        printf("Digite a matrícula do aluno: ");
        fgets(aluno.matricula, sizeof(aluno.matricula), stdin);
        aluno.matricula[strcspn(aluno.matricula, "\n")] = '\0'; // Remover o caractere de nova linha

        if (!validarMatricula(aluno.matricula)) {
            printf("Matrícula inválida. A matrícula deve ter exatamente 6 dígitos.\n");
            continue;
        }

        printf("Digite a média do aluno: ");
        if (scanf("%f", &aluno.media) != 1) {
            printf("Valor inválido para a média. Digite um número válido.\n");
            limparBufferEntrada();
            continue;
        }
        limparBufferEntrada();

        if (!validarMedia(aluno.media)) {
            printf("Média inválida. A média deve estar entre 0 e 10.\n");
            continue;
        }

        break; // Dados válidos, sair do loop
    }

    printf("\nInformações do aluno:\n");
    printf("Nome: %s\n", aluno.nome);
    printf("Matrícula: %s\n", aluno.matricula);
    printf("Média: %.2f\n", aluno.media);

    return 0;
}*/
 
 #include <stdio.h>
#include <windows.h>

// Define cores utilizando códigos de cores do console do Windows
#define COLOR_RED     12
#define COLOR_GREEN   10
#define COLOR_RESET   7

int main() {
    // Obtém o handle do console
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Exemplo de uso das cores
    SetConsoleTextAttribute(consoleHandle, COLOR_RED);
    printf("                                 Texto em vermelho\n");

    SetConsoleTextAttribute(consoleHandle, COLOR_GREEN);
    printf("\n\n                                Texto em verde\n");

    SetConsoleTextAttribute(consoleHandle, COLOR_RESET);

    return 0;
}

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 






























