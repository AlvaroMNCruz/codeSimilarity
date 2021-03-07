#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 
struct node{
	int data;  
	char nomelivro[333]; 
	char nomeuser[333];
	
	struct node *link;  
};

int count = 0;  

 

void countnodes(struct node *head);  
void printdata(struct node *head);  

 
void addend(struct node *head, int data, char livro[333], char user[333]);
struct node *addbeg(struct node *head, int data, char livro[333], char user[333]);  
void addmid(struct node *head, int data, int pos);

struct node *delfirst(struct node *head);  
void dellast(struct node *head);
void delmid(struct node **head, int pos);

void sort(struct node *head);
struct node *reverse(struct node *head);

 
void printfile(struct node *head);  
void readfile(struct node *head);  
void checkifmt();

 
void addenduser(struct node *head, int book, int useradd);
void delmiduser(struct node **head);

void printdatauser(struct node *head);
unsigned int countnum(unsigned int i);
void printdates(int num);

int main()
{
	checkifmt();  
	
	struct node *head = (struct node*)malloc(sizeof(struct node));  
	
	 
	head->data = 99999999;
	strcpy(head->nomeuser,"usuario");
	strcpy(head->nomelivro, "livro");
	head->link = null;
	
	readfile(head);  
	
	 
	dellast(head);
	
	 
	int ans;
	int on = 1;
	
	 
	do
	{	
		countnodes(head);  
		printf("----------------------------------\n");
		printf("1. adicionar usuario e livro\n");
		printf("2. adicionar usuario\n");
		printf("3. adicionar livro\n");
		printf("4. remover livro\n");
		printf("5. exibir lista\n");
		printf("6. organizar lista\n");
		printf("7. reverter ordem\n");
		printf("0. sair\n");
		printf("----------------------------------\n");
		scanf("%d", &ans);
		
		switch(ans)
		{
			case 0:  
				printf("fechando...\n");
				on = 0;
			break;
			
			case 1: 
				addenduser(head, 1, 1);
				printfile(head);
			break;	
			
			case 2: 
				addenduser(head, 0, 1);
				printfile(head);
			break;
			
			case 3: 
				addenduser(head, 1, 0);
				printfile(head);
			break;
				
			case 4: 
				delmiduser(&head);
				printfile(head);
			break;
			
			case 5: 
				printfile(head);
				printdatauser(head);
			break;
			
			case 6: 
				sort(head);
				printdatauser(head);
				printfile(head);
			break;	
			
			case 7:
				head = reverse(head);
				printdatauser(head);
				printfile(head);
			break;
						
			default:
				printf("input invalido!\n");
			break;	
		}
	}while(on == 1);
	
	printfile(head);  
	
	return 0;
}

 

void countnodes(struct node *head)  
{	
	count = 0;  
	
	if(head == null)
	{
		printf("a lista esta vazia\n");
	}
	
	struct node *ptr = null;
	ptr = head;
	
	while(ptr != null)  
	{
		count++;  
		ptr = ptr->link;  
	}
	
	printf("ha %d livros na lista\n", count);  
}

void printdata(struct node *head) 
{
	int linprint = 1;  
	
	if(head == null)
	{
		printf("\n----------------------------------\n");
		printf("a lista esta vazia\n");
		printf("----------------------------------\n\n");
	}else
	{
		struct node *ptr = null;
		ptr = head;
	
		printf("----------------------------------\n");
		while(ptr != null)
		{
			printf("%d - ", linprint);
			printf("%d ", ptr->data);
			printf("%s ", ptr->nomeuser);
			printf("%s\n", ptr->nomelivro);
		
			ptr = ptr->link;
			linprint++;
		}
		printf("----------------------------------\n");
		
	}
}

void printdatauser(struct node *head) 
{
	int linprint = 1;  
	
	if(head == null)
	{
		printf("\n----------------------------------\n");
		printf("a lista esta vazia\n");
		printf("----------------------------------\n\n");
	}else
	{
		struct node *ptr = null;
		ptr = head;
		int datatemp;
		
		printf("----------------------------------\n");
		while(ptr != null)
		{
			datatemp = ptr->data;
			
			printf("%d - ", linprint);
			 
			printdates(datatemp);
			printf("%s ", ptr->nomeuser);
			printf("%s\n", ptr->nomelivro);
			
		
			ptr = ptr->link;
			linprint++;
		}
		printf("----------------------------------\n");
		
	}
}

void addend(struct node *head, int data, char livro[333], char user[333])  
{
	struct node *ptr;
	struct node *temp;  
	
	ptr = head;
	temp = (struct node*)malloc(sizeof(struct node));  
	
	 
	temp->data = data;
	strcpy(temp->nomeuser, user);
	strcpy(temp->nomelivro, livro);
	
	temp->link = null;  
	
	while(ptr->link != null)  
	{
		ptr = ptr->link;
	}
	
	ptr->link = temp;  
}

struct node *addbeg(struct node *head, int data, char livro[333], char user[333]) 
{
	struct node *ptr = (struct node*)malloc(sizeof(struct node));  
	
	 
	ptr->data = data;
	strcpy(ptr->nomeuser, user);
	strcpy(ptr->nomelivro, livro);
	ptr->link = null;  
	
	ptr->link = head;  
	head = ptr;  
	
	return head;
}

void addmid(struct node *head, int data, int pos)  
{
	struct node *ptr = head;
	struct node *newnode = (struct node*)malloc(sizeof(struct node));  
	
	 
	newnode->data = data;
	newnode->link = null;  
	
	pos--;  
	while(pos != 1)
	{
		ptr = ptr->link;  
		pos--;  
	}
	
	newnode->link = ptr->link;  
	ptr->link = newnode;  
}

struct node *delfirst(struct node *head)  
{
	struct node *temp = head;
	
	if(head == null)
	{
		printf("nao ha como deletar o primeiro node pois a lista esta vazia\n");
	}else
	{
		head = head->link;
		free(temp);
		temp = null;
	}
	return head;
}

void dellast(struct node *head) 
{
	struct node *temp = head;
	struct node *temp2 = head;
	
	if(head == null)
	{
		printf("list is empty\n");
	}else if(head->link == null)
	{
		free(head);
		head = null;
	}else
	{
		while(temp->link != null)
		{
			temp2 = temp;
			temp = temp->link;
		}
		temp2->link = null;
		free(temp);
		temp = null;
	}
}

void delmid(struct node **head, int pos) 
{
	struct node *crnt = *head;
	struct node *prev = *head;
	
	if(*head == null)
	{
		 
	}else if(pos == 1)
	{
		*head = crnt->link;
		free(crnt);
		crnt == null;
	}else
	{
		while(pos != 1)
		{
			prev = crnt;
			crnt = crnt->link;
			
			pos--;
		}
		prev->link = crnt->link;
		free(crnt);
		crnt = null;
	}
}

void sort(struct node *head) 
{
	struct node *i;
	struct node *j;
	int datatemp;
	char usertemp[333];
	char livrotemp[333];
	
	for(i = head; i->link != null; i = i->link)
	{
		for(j = i->link; j != null; j = j->link)
		{
			if(i->data > j->data)
			{
				datatemp = i->data;
				strcpy(usertemp, i->nomeuser);
				strcpy(livrotemp, i->nomelivro);
				
				i->data = j->data;
				strcpy(i->nomeuser, j->nomeuser);
				strcpy(i->nomelivro, j->nomelivro);
				
				j->data = datatemp;
				strcpy(j->nomeuser, usertemp);
				strcpy(j->nomelivro, livrotemp);
			}
		}
	}
}

void printfile(struct node *head)  
{	
	file *fwrte;
	fwrte = fopen("reg.txt", "w");
	
	struct node *ptr = null;
	ptr = head;
	
	while(ptr != null)
	{
		fprintf(fwrte, "%d ", ptr->data);
		fprintf(fwrte, "%s ", ptr->nomeuser);
		fprintf(fwrte, "%s\n", ptr->nomelivro);
		ptr = ptr->link;
	}
	
	printf("registrando...\n");
	
	fclose(fwrte);
}

void readfile(struct node *head)
{
	file *fread;
	fread = fopen("reg.txt", "a+");
	
	char buffer[9999];
	char buffer2[9999];
	int lin = 1;
	
	if(fgets(buffer2, 10000, fread) == null)
	{
		 
	}else
	{	
		struct node *ptr = (struct node*)malloc(sizeof(struct node));
		head->link = ptr;
	
		fscanf(fread, "%d %s %s", &ptr->data, &ptr->nomelivro, &ptr->nomeuser);
		 
	
		addend(head, ptr->data, ptr->nomelivro, ptr->nomeuser);
		ptr = ptr->link;
		
		
		while( (fgets(buffer, 100000, fread)) != null )
		{
			fscanf(fread, "%d %s %s", &ptr->data, &ptr->nomelivro, &ptr->nomeuser);
			addend(head, ptr->data, ptr->nomelivro, ptr->nomeuser);
			 
		
			lin++;
			ptr = ptr->link;
		}
		
		dellast(head);  
	
	}
	
	fclose(fread);
}

void addenduser(struct node *head, int book, int useradd)  
{
	 
	 
	int data;
	int dia;
	int mes;
	int ano;
	char livro[333];
	char user[333];
	
	struct node *ptr;
	struct node *temp;  

	ptr = head;
	temp = (struct node*)malloc(sizeof(struct node));  
	
	if(book == 1)
	{
		printf("digite o nome do livro: ");
		scanf(" %[^\n]%*c", &livro);
	}else
	{
		strcpy(livro, "nobook");
	}
	
	if(useradd == 1)
	{
		printf("digite o nome do usuario: ");
		scanf(" %[^\n]%*c", &user);
	}else
	{
		strcpy(user, "nouser");
	}
	
	
	if(book == 1 && useradd == 1)
	{
		printf("digite o ano de devolucao: ");
		scanf("%d", &ano);		
		data = ano*10000;
		
		printf("digite o mes de devolucao: ");
		scanf("%d", &mes);
		data = data + (mes*100);
		
		printf("digite o dia de devolucao: ");
		scanf("%d", &dia);
		
		data = data + dia;
		
	}else if(book == 1 && useradd == 0)
	{
		data = 80808080;
	}else if(book == 0 && useradd == 1)
	{
		data = 90909090;
	}
	
	 
	temp->data = data;
	strcpy(temp->nomeuser, user);
	strcpy(temp->nomelivro, livro);
	temp->link = null;
	
	while(ptr->link != null) 
	{
		ptr = ptr->link;
	}
	
	ptr->link = temp;
}

void delmiduser(struct node **head)  
{
	int pos;	
	struct node *crnt = *head;
	struct node *prev = *head;
	
	printf("----------------------------------\n");
	printdata(*head);
	printf("----------------------------------\n");
	printf("digite o livro deseja excluir: ");
	scanf("%d", &pos);
	
	if(*head == null)
	{
		 
	}else if(pos == 1)
	{
		*head = crnt->link;
		free(crnt);
		crnt == null;
	}else
	{
		while(pos != 1)
		{
			prev = crnt;
			crnt = crnt->link;
			
			pos--;
		}
		prev->link = crnt->link;
		free(crnt);
		crnt = null;
	}
}

struct node *reverse(struct node *head)  
{
	struct node *prev = null;
	struct node *next = null;
	
	while(head != null)
	{
		next = head->link;
		head->link = prev;
		prev = head;
		head = next;
	}
	
	head = prev;
	return head;
}

void checkifmt()  
{
	int check = 0;
	char test[9999];
	
	file *fread;
	
	fread = fopen("reg.txt", "a+");
	
	fprintf(fread, "\n");
	
	fclose(fread);
}

unsigned int countnum(unsigned int i)  
{
 	unsigned int sum = 1;
 	
 	while(i/=10)
 	{
 		sum++;
	}
	 
 	return sum;
}

void printdates(int num)  
{
	int digits;
	int i;
	
	digits = countnum(num);
	
	char date[digits];
	
	while (digits--)
	{
 		date[digits] = num%10;
 		num/=10;
 		 
	}
	
	for(i = 6; i < 8; i++)
	{
		printf("%d", date[i]);
	}
	printf("/");
	
	for(i = 4; i < 6; i++)
	{
		printf("%d", date[i]);
	}
	printf("/");
	
	for(i = 0; i < 4; i++)
	{
		printf("%d", date[i]);
	}
	printf(" ");
}

