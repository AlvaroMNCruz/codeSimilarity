 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro{  
	char titulo[50];  
	struct livro *proxlivro;
}livro;

typedef struct user{  
	char nome[50];  
	struct user *prox;
}cadastro;

typedef struct reserva{  
	char nomeuser[50];  
	char nomelib[50];   
	int data;           
	struct reserva *proxres;
}reserva;

void adduser(cadastro **head, cadastro **tail, cadastro **novono){  
	if(*head==null){
		*head = *novono;                                    
		*tail = *novono;                                    
		(*novono)->prox = null;                             
	}
	else{
		(*tail)->prox = *novono;
		(*novono)->prox = null;
		*tail = *novono;
	}
}

void addbook(livro **cabeca, livro **cauda, livro **newno){  
	if(*cabeca==null){
		*cabeca = *newno;
		*cauda = *newno;
		(*newno)->proxlivro = null;
	}
	else{
		(*cauda)->proxlivro = *newno;
		(*newno)->proxlivro = null;
		*cauda = *newno;
	}
}

void addres(reserva **top, reserva **bottom, reserva **no){  
	if(*top==null){
		*top = *no;
		*bottom = *no;
		(*no)->proxres = null;
	}
	else{
		(*bottom)->proxres = *no;
		(*no)->proxres = null;
		*bottom = *no;
	}
}

printuser(cadastro **head){  
	int i;
	cadastro *aux=*head;
	for(i=0; aux!=null; i++)  
	{
		printf("%s\n", aux->nome);
		aux=aux->prox;  
	}
}

printbook(livro **cabeca){  
	int i;
	livro *aux=*cabeca;
	for(i=0; aux!=null; i++)  
	{
		printf("%s\n", aux->titulo);
		aux=aux->proxlivro;  
	}
}

printreserva(reserva **top){  
	int i;
	reserva *aux=*top;
	for(i=0; aux!=null; i++)  
	{
		printf("%s - %s - %d\n", aux->nomeuser, aux->nomelib, aux->data);
		aux=aux->proxres;  
	}
}

int main()
{
	file *fuser;  
	file *flib;   
	file *fres;   
	int op, contuser, contbook, dat;
	char name[50], book[50];
	cadastro *aux, *head=null, *tail=null, auxaux;  
	livro *aux2, *cabeca=null, *cauda=null;  
	reserva *aux3, *top=null, *bottom=null;  
	printf("\t\t-biblioteca-\n");
	fuser = fopen("user.dat", "a");  
	fuser = fopen("user.dat", "r");  
	fseek(fuser,0,seek_end);  
	if(ftell(fuser)!=0){  
		fseek(fuser,0,seek_set);  
		while(!feof(fuser)){
			cadastro *novono;
			novono = (cadastro*) malloc(sizeof(cadastro));  
			fscanf(fuser, "%[^\n]\n", novono->nome);  
			adduser(&head, &tail, &novono);
			contuser++;  
		}
	}
	flib = fopen("library.dat", "a");  
	flib = fopen("library.dat", "r");  
	fseek(flib,0,seek_end);  
	if(ftell(flib)!=0){  
		fseek(flib,0,seek_set);  
		while(!feof(flib)){
			livro *newno;
			newno = (livro*) malloc(sizeof(livro));
			fscanf(flib, "%[^\n]\n", newno->titulo);  
			addbook(&cabeca, &cauda, &newno);
			contbook++;  
		}
	}
	fres = fopen("reservados.dat", "a");  
	fres = fopen("reservados.dat", "r");  
	fseek(fres,0,seek_end);  
	if(ftell(fres)!=0){  
		fseek(fres,0,seek_set);  
		while(!feof(fres)){
			reserva *no;
			no = (reserva*) malloc(sizeof(reserva));  
			fscanf(fres, "%[^\n] %[^\n] %d\n", no->nomeuser, no->nomelib, &no->data);  
			addres(&top, &bottom, &no);
		}
	}
	printf("\ndigite:\n1 (cadastrar usuario)\n2 (cadastrar livro)\n3 (imprimir usuario)\n4 (imprimir livro)\n5 (salvar usuarios)\n6 (salvar livros)\n7 (reservar livro)\n8 (salvar emprestimos)\n9 (devolver livros)\n-1 (sair)\n");
	while(op!=-1){
		printf("\n");
		printf("op: ");
		scanf("%d", &op);
		printf("\n");
		switch(op){  
			case 1:{  
				printuser(&head);
				cadastro *novono;
				novono = (cadastro*) malloc(sizeof(cadastro));  
				setbuf(stdin,null);
				printf("nome: ");
				scanf("%[^\n]", novono->nome);  
				adduser(&head, &tail, &novono);  
				break;
			}
			case 2:{  
				printbook(&cabeca);
				livro *newno;
				newno = (livro*) malloc(sizeof(livro));
				setbuf(stdin,null);
				printf("titulo: ");
				scanf("%[^\n]", newno->titulo);  
				addbook(&cabeca, &cauda, &newno);  
				break;
			}
			case 3:{  
				printuser(&head);
				if(contuser!=0){
					printf("total de usuarios: %d\n", contuser);  
				}
				break;
			}
			case 4:{  
				printbook(&cabeca);
				if(contbook!=0){
					printf("total de livros: %d\n", contbook);  
				}
				break;
			}
			case 5:{  
				fuser = fopen("user.dat", "w");  
				aux = head;  
				while(aux!=null){
					fprintf(fuser, "%s\n", aux->nome);
					aux = aux->prox;  
				}
				printf("**usuarios salvos**");
				break;
			}
			case 6:{  
				flib = fopen("library.dat", "w");  
				aux2 = cabeca;  
				while(aux2!=null){
					fprintf(flib, "%s\n", aux2->titulo);  
					aux2 = aux2->proxlivro;  
				}
				printf("**livros salvos**");
				break;
			}
			case 7:{  
				printf("\t-usuarios-\n");
				printuser(&head);  
				printf("\n\t-livros-\n");
				printbook(&cabeca);  
				reserva *no;
				no = (reserva*) malloc(sizeof(reserva));  
				setbuf(stdin,null);
				printf("\nescreva o nome do aluno a reservar algum livro: ");
				scanf("%[^\n]", no->nomeuser);
				setbuf(stdin,null);
				printf("escreva o nome do livro reservado: ");
				scanf("%[^\n]", no->nomelib);                           
				setbuf(stdin,null); 
				printf("data de devolucao: ");
				scanf("%d", &no->data);
				addres(&top, &bottom, &no);  
				break;
			}
			case 8:{  
				fres = fopen("reservados.dat", "w");  
				aux3 = top;  
				while(aux3!=null){
					setbuf(stdin,null);
					fprintf(fres, "%s %s %d\n", aux3->nomeuser, aux3->nomelib, aux3->data);  
					aux3 = aux3->proxres;  
				}
				printf("**reservas salvas**\n");
				printreserva(&top);  
				break;
			}
			case 9:{  
				char auxstr[50];  
				int i;
				setbuf(stdin,null);
				printreserva(&top);
                printf("digite o nome que deseja remover da lista de reservados: ");
                setbuf(stdin, null);
                scanf("%[^\n]", &auxstr);  
                aux3 = top;
                for(i=0;aux3!=null;i++){ 
                    if(strstr(aux3->nomelib,auxstr)!=null) free(aux3);  
                aux3 = aux3->proxres;  
                }
				break;
			}
		}
	}
	 
	 
	fclose(fuser);
	fclose(flib);     
	fclose(fres);
	return 0;
}
