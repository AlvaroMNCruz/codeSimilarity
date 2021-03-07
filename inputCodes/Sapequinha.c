#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

 
int qnt_usuarios, qnt_livros, qnt_reservas;

 
typedef struct usuario
{
	int id;
	char nome[100000];
	struct usuario *prox;
}usuario;

 
typedef struct livro
{
	int id;
	char autor[100000], titulo[100000];
	struct livro *prox;
}livro;

 
typedef struct reserva
{
	int id_usuario, id_livro, dia, mes, ano;
	struct reserva *prox;
}reserva;

 
usuario *leusuarios(file *arquivo, usuario *usuario)
{
	arquivo = fopen("usuarios.txt", "r");
	 
	for(int i=0; i<qnt_usuarios; i++)
	{
		 
		usuario *novo;
		novo = (usuario*) malloc(sizeof(usuario));
		int id;
		char nome[100000]={};
		
		fscanf(arquivo, "%d", &id);
		fscanf(arquivo, "%s", nome);
		
		novo->id = id;
		strcpy(novo->nome, nome);
		novo->prox = usuario;
		usuario = novo;
	}
	
	fclose(arquivo);
	
	return usuario;
}

 
livro *lelivros(file *arquivo, livro *livro)
{
	arquivo = fopen("livros.txt", "r");
	 
	for(int i=0; i<qnt_livros; i++)
	{
		 
		livro *novo;
		novo = (livro*) malloc(sizeof(livro));
		int id;
		char autor[100000]={}, titulo[100000];
		
		fscanf(arquivo, "%d", &id);
		fscanf(arquivo, "%s", autor);
		fscanf(arquivo, "%s", titulo);
		
		novo->id = id;
		strcpy(novo->autor, autor);
		strcpy(novo->titulo, titulo);
		novo->prox = livro;
		livro = novo;
	}
	
	fclose(arquivo);
	
	return livro;
}

 
reserva *lereservas(file *arquivo, reserva *reserva)
{
	arquivo = fopen("reservas.txt", "r");
	 
	for(int i=0; i<qnt_reservas; i++)
	{
		 
		reserva *novo;
		novo = (reserva*) malloc(sizeof(reserva));
		int id_usuario, id_livro, dia, mes, ano;
		
		fscanf(arquivo, "%d", &id_usuario);
		fscanf(arquivo, "%d", &id_livro);
		fscanf(arquivo, "%d", &dia);
		fscanf(arquivo, "%d", &mes);
		fscanf(arquivo, "%d", &ano);
		
		novo->id_usuario = id_usuario;
		novo->id_livro = id_livro;
		novo->dia = dia;
		novo->mes = mes;
		novo->ano = ano;
		novo->prox = reserva;
		reserva = novo;
	}
	
	fclose(arquivo);
	
	return reserva;
}

 
void salvaarquivo(file *arquivo, usuario *usuario, livro *livro, reserva *reserva, int opc)
{
	 
	if(opc==1)
	{
		usuario *aux = usuario;
		arquivo = fopen("usuarios.txt", "w");
		while(aux!=null && usuario!=null)
		{
			fprintf(arquivo, "%d ", usuario->id);
			fprintf(arquivo, "%s ", usuario->nome);
			usuario = usuario->prox;
			free(aux);
			aux = usuario;
		}
		
		fclose(arquivo);
	}
	 
	else if(opc==2)
	{
		livro *aux = livro;
		arquivo = fopen("livros.txt", "w");
		while(aux!=null && livro!=null)
		{
			fprintf(arquivo, "%d ", livro->id);
			fprintf(arquivo, "%s ", livro->autor);
			fprintf(arquivo, "%s ", livro->titulo);
			livro = livro->prox;
			free(aux);
			aux = livro;
		}
		
		fclose(arquivo);
	}
	 
	else if(opc==3)
	{
		reserva *aux = reserva;
		arquivo = fopen("reservas.txt", "w");
		while(aux!=null && livro!=null)
		{
			fprintf(arquivo, "%d ", reserva->id_usuario);
			fprintf(arquivo, "%d ", reserva->id_livro);
			fprintf(arquivo, "%d ", reserva->dia);
			fprintf(arquivo, "%d ", reserva->mes);
			fprintf(arquivo, "%d ", reserva->ano);
			reserva = reserva->prox;
			free(aux);
			aux = reserva;
		}
		
		fclose(arquivo);
	}
}

 
void listausuarios(usuario *usuario)
{
	 
	if(qnt_usuarios==0)
	{
		printf("\nerro: nao existem usuarios cadastrados!\n");
	}
	else
	{
		printf("\nlista de usuarios:\n");
		while(usuario!=null)
		{
			printf("\nid: %d\tnome: %s\n", usuario->id, usuario->nome);
			usuario = usuario->prox;
		}	
	}
}

 
void listalivros(livro *livro)
{
	 
	if(qnt_livros==0)
	{
		printf("\nerro: nao existem livros cadastrados!\n");
	}
	else
	{
		printf("\nlista de livros:\n");
		while(livro!=null)
		{
			printf("\nid: %d\tautor: %s\ttitulo: %s\n", livro->id, livro->autor, livro->titulo);
			livro = livro->prox;
		}
	}
}

 
void listareservas(reserva *reserva)
{
	 
	if(qnt_reservas==0)
	{
		printf("\nerro: nao existem livros reservados!\n");
	}
	else
	{
		printf("\nlista de reservas:\n");
		while(reserva!=null)
		{
			printf("\nid do usuario: %d\tid do livro: %d\t", reserva->id_usuario, reserva->id_livro);
			 
			 
			if(reserva->dia<10)
			{
				printf("0%d/",reserva->dia);
			}
			else
			{
				printf("%d/",reserva->dia);
			}
			 
			if(reserva->mes<10)
			{
				printf("0%d/",reserva->mes);
			}
			else
			{
				printf("%d/",reserva->mes);
			}
			 
			if(reserva->ano<10)
			{
				printf("000%d\n\n",reserva->ano);
			}
			else if(reserva->ano<100)
			{
				printf("00%d\n\n",reserva->ano);
			}
			else if(reserva->ano<1000)
			{
				printf("0%d\n\n",reserva->ano);
			}
			else
			{
				printf("%d\n\n",reserva->ano);
			}
			reserva = reserva->prox;
		}	
	}
}

 
usuario *criausuario(usuario *usuario)
{
	int id;
	char nome[100000];
	
	 
	usuario *novo;
	novo = (usuario*) malloc(sizeof(usuario));
	
	 
	int verifica=0;
	while(verifica!=1)
	{
		printf("\ndigite o id do usuario (ate 4 digitos):\n");
		scanf("%d",&id);
		
		if(id<10000 && id>0)
		{
			novo->id = id;
			verifica=1;
		}	
		else
		{
			printf("\nerro: id invalido!\n");
		}
	}
	
	 
	printf("\ndigite o nome do usuario:\n");
	scanf("%s",nome);
	fflush(stdin);
	strcpy(novo->nome, nome);
	
	printf("\ncadastrando usuario...\n");
	novo->prox = usuario;
	usuario = novo;
	printf("\nusuario cadastrado com sucesso!\n");
	qnt_usuarios++;
	return usuario;
}

 
usuario *deletausuario(usuario *usuario)
{
	 
	if(qnt_usuarios==0)
	{
		printf("\nerro: nao existem usuarios cadastrados!\n");
		return usuario;
	}
	 
	listausuarios(usuario);
	
	 
	int verifica=0, id;
	while(verifica!=1)
	{
		printf("\ndigite o id do usuario que deseja excluir:\n");
		scanf("%d",&id);
		
		if(id<10000 && id>0)
		{
			verifica=1;
		}	
		else
		{
			printf("\nerro: id invalido!\n");
		}	
	}
	
	usuario *aux = usuario, *aux2;
	
	 
	while(aux->id!=id && aux!=null)
	{
		aux2 = aux;
		aux = aux->prox;
	}
	
	 
	if(aux->id == id)
	{
		 
		if(usuario==aux)
		{
			printf("\ndeletando usuario...");
			usuario = usuario->prox;
			free(aux);
			printf("\nusuario deletado com sucesso!\n\n");
		}
		 
		else
		{
			printf("\ndeletando usuario...");
			aux2->prox = aux->prox;
			free(aux);	
			printf("\nusuario deletado com sucesso!\n\n");
		}
	}
	 
	else
	{
		printf("\nerro: id incorreto ou usuario nao existe!\n\n");
	}
	
	return usuario;
}

 
livro *crialivro(livro *livro)
{
	int id;
	char autor[100000], titulo[100000];
	
	 
	livro *novo;
	novo = (livro*) malloc(sizeof(livro));
	
	 
	int verifica=0;
	while(verifica!=1)
	{
		printf("\ndigite o id do livro (ate 4 digitos):\n");
		scanf("%d",&id);
		
		if(id<10000 && id>0)
		{
			novo->id = id;
			verifica=1;
		}	
		else
		{
			printf("\nerro: id invalido!\n");
		}
	}
	
	 
	printf("\ndigite o nome do autor:\n");
	scanf("%s",autor);
	fflush(stdin);
	strcpy(novo->autor, autor);
	
	 
	printf("\ndigite o titulo do livro:\n");
	scanf("%s",titulo);
	fflush(stdin);
	strcpy(novo->titulo, titulo);
	
	printf("\ncadastrando livro...\n");
	novo->prox = livro;
	livro = novo;
	printf("\nlivro cadastrado com sucesso!\n");
	
	qnt_livros++;
	return livro;
}

 
livro *deletalivro(livro *livro)
{
	 
	if(qnt_livros==0)
	{
		printf("\nerro: nao existem livros cadastrados!\n");
		return livro;
	}
	 
	listalivros(livro);
	
	 
	int verifica=0, id;
	while(verifica!=1)
	{
		printf("\ndigite o id do livro que deseja excluir:\n");
		scanf("%d",&id);
		
		if(id<10000 && id>0)
		{
			verifica=1;
		}	
		else
		{
			printf("\nerro: id invalido!\n");
		}	
	}
	
	livro *aux = livro, *aux2;
	
	 
	while(aux->id!=id && aux!=null)
	{
		aux2 = aux;
		aux = aux->prox;
	}
	
	 
	if(aux->id == id)
	{
		 
		if(livro==aux)
		{
			printf("\ndeletando livro...");
			livro = livro->prox;
			free(aux);
			printf("\nlivro deletado com sucesso!\n\n");
		}
		 
		else
		{
			printf("\ndeletando livro...");
			aux2->prox = aux->prox;
			free(aux);	
			printf("\nlivro deletado com sucesso!\n\n");
		}
	}
	 
	else
	{
		printf("\nerro: id incorreto ou livro nao existe!\n\n");
	}
	
	return livro;
}

 
reserva *reservalivro(usuario *usuario, livro *livro, reserva *reserva)
{
	usuario *aux=usuario;
	livro *aux2=livro;
	
	 
	if(qnt_usuarios==0 || qnt_livros==0)
	{
		printf("\nerro: nao existem usuarios ou livros suficientes cadastrados!\n");
		return reserva;
	}
	
	int id_usuario, id_livro, dia, mes, ano;
	
	 
	reserva *novo;
	novo = (reserva*) malloc(sizeof(reserva));
	
	 
	listausuarios(usuario);
	 
	listalivros(livro);
	
	 
	int verifica=0;
	while(verifica!=1)
	{
		aux=usuario;
		printf("\ndigite o id do usuario:\n");
		scanf("%d",&id_usuario);
		novo->id_usuario = id_usuario;
		
		 
		while(aux!=null && aux->id!=id_usuario)
		{
			aux = aux->prox;
		}
		if(aux==null)
		{
			printf("\nerro: id invalido!\n");
		}	
		else
		{
			verifica=1;
		}
	}
	
	 
	verifica=0;
	while(verifica!=1)
	{
		aux2=livro;
		printf("\ndigite o id do livro:\n");
		scanf("%d",&id_livro);
		novo->id_livro = id_livro;
		
		 
		while(aux2!=null && aux2->id!=id_livro)
		{
			aux2 = aux2->prox;
		}
		
		if(aux2==null)
		{
			printf("\nerro: id invalido!\n");
		}	
		else
		{
			verifica=1;
		}
	}
	
	printf("\ndigite a data de devolucao:\n\n");
	
	 
	verifica=0;
	int verifica1=0;
	while(verifica!=1)
	{
		verifica1=0;
		 
		while(verifica1!=1)
		{
			printf("dia: \n");
			scanf("%d",&dia);	
			
			if(dia>0 && dia<32)
			{
				novo->dia = dia;
				break;
			}
			else
			{
				printf("\nerro: dia invalido!\n\n");
			}
		}
		
		 
		while(verifica1!=1)
		{
			printf("mes: \n");
			scanf("%d",&mes);	
			
			if(dia>28 && mes==2)
			{
				printf("\nerro: data invalida!\n\n");
				verifica1=1;
			}
			else if(mes>0 && mes<13)
			{
				novo->mes = mes;
				break;
			}
			else
			{
				printf("\nerro: mes invalido!\n\n");
			}
		}
		
		 
		while(verifica1!=1)
		{
			printf("ano: \n");
			scanf("%d",&ano);	
			
			if(ano>0 && ano<10000)
			{
				printf("\n");
				novo->ano = ano;
				verifica1=1;
				verifica=1;
			}
			else
			{
				printf("\nerro: ano invalido!\n\n");
			}
		}
	}
	
	printf("\nreservando livro...\n");
	novo->prox = reserva;
	reserva = novo;
	printf("\nlivro reservado com sucesso!\n");
	
	qnt_reservas++;
	return reserva;
}

 
reserva *devolvelivro(usuario *usuario, livro *livro, reserva *reserva)
{
	usuario *aux3=usuario;
	livro *aux4=livro;
	
	 
	if(qnt_reservas==0)
	{
		printf("\nerro: nao existem livros reservados!\n");
		return reserva;
	}
	
	 
	listareservas(reserva);
	
	int id_usuario, id_livro;
	
	 
	int verifica=0;
	while(verifica!=1)
	{
		aux3=usuario;
		printf("\ndigite o id do usuario para devolucao:\n");
		scanf("%d",&id_usuario);
		
		 
		while(aux3!=null && aux3->id!=id_usuario)
		{
			aux3 = aux3->prox;
		}
		if(aux3==null)
		{
			printf("\nerro: id invalido!\n");
		}	
		else
		{
			verifica=1;
		}
	}
	
	 
	verifica=0;
	while(verifica!=1)
	{
		aux4=livro;
		printf("\ndigite o id do livro para devolucao:\n");
		scanf("%d",&id_livro);
		
		 
		while(aux4!=null && aux4->id!=id_livro)
		{
			aux4 = aux4->prox;
		}
		
		if(aux4==null)
		{
			printf("\nerro: id invalido!\n");
		}	
		else
		{
			verifica=1;
		}
	}
	
	reserva *aux = reserva, *aux2;
	
	 
	while(aux->id_usuario!=id_usuario && aux!=null)
	{
		aux2 = aux;
		aux = aux->prox;
	}
	 
	while(aux->id_livro!=id_livro && aux!=null)
	{
		aux2 = aux;
		aux = aux->prox;
	}
	
	 
	if(aux->id_usuario==id_usuario && aux->id_livro==id_livro)
	{
		 
		if(reserva==aux)
		{
			printf("\ndevolvendo livro...");
			reserva = reserva->prox;
			free(aux);
			printf("\nlivro devolvido com sucesso!\n\n");
		}
		 
		else
		{
			printf("\ndevolvendo livro...");
			aux2->prox = aux->prox;
			free(aux);	
			printf("\nlivro devolvido com sucesso!\n\n");
		}
	}
	 
	else
	{
		printf("\nerro: id incorreto ou reserva nao encontrada!\n\n");
	}
	
	qnt_reservas--;
	return reserva;
}

 
reserva *selectionsort(reserva *reserva, int opc) 
{ 

	reserva *aux, *aux1, *ant;
	int dia, mes, ano, id_usuario, id_livro;
	 
	if(opc==1)
	{
		 
		if(qnt_reservas==2)
		{
			aux = reserva->prox;
			if(aux->ano < reserva->ano)
			{
				reserva->prox = null;
				aux->prox = reserva;
				reserva = aux;
				return reserva;
			}
			else if(aux->ano == reserva->ano)
			{
				if(aux->mes < reserva->mes)
				{
					reserva->prox = null;
					aux->prox = reserva;
					reserva = aux;
					return reserva;
				}
				else if(aux->mes == reserva->mes)
				{
					if(aux->dia < reserva->dia)
					{
						reserva->prox = null;
						aux->prox = reserva;
						reserva = aux;
						return reserva;
					}
				}
			}
		}
		 
		else
		{
			aux=reserva;
			aux1=aux->prox;
			dia = aux->dia;
			mes = aux->mes;
			ano = aux->ano;
			
			for(int i=0; i<qnt_reservas; i++)
			{
				 
				dia = aux->dia;
				mes = aux->mes;
				ano = aux->ano;
				aux1=aux;
				 
				while(aux1!=null)
				{
					if(aux1->ano==ano)
					{
						if(aux1->mes==mes)
						{
							if(aux1->dia<dia)
							{
								id_usuario = aux1->id_usuario;
								id_livro = aux1->id_livro;
								dia = aux1->dia;
								mes = aux1->mes;
								ano = aux1->ano;
								aux1 = aux1->prox;
							}
							else
							{
								aux1 = aux1->prox;
							}
						}
						else if(aux1->mes<mes)
						{
							id_usuario = aux1->id_usuario;
							id_livro = aux1->id_livro;
							dia = aux1->dia;
							mes = aux1->mes;
							ano = aux1->ano;
							aux1 = aux1->prox;
						}
						else
						{
							aux1 = aux1->prox;
						}
					}
					else if(aux1->ano<ano)
					{
						id_usuario = aux1->id_usuario;
						id_livro = aux1->id_livro;
						dia = aux1->dia;
						mes = aux1->mes;
						ano = aux1->ano;
						aux1 = aux1->prox;
					}
					else
					{
						aux1 = aux1->prox;
					}
				}
				
				aux1 = aux;
				 
				 
				if(dia!=aux->dia||mes!=aux->mes||ano!=aux->ano)
				{
					 
					while(aux1->prox!=null&&(aux1->prox->ano!=ano||aux1->prox->mes!=mes||aux1->prox->dia!=dia))
					{
						aux1 = aux1->prox;
					}
					
					 
					if(aux1->prox!=null&&aux1->prox->ano==ano&&aux1->prox->mes==mes&&aux1->prox->dia==dia)
					{
						 
						if(aux==reserva&&aux1->prox->prox!=null)
						{
							 
							if(aux==aux1)
							{
								reserva = aux->prox;
								aux = reserva->prox;
								aux1->prox = aux;
								reserva->prox = aux1;
								ant = reserva;
								aux = reserva->prox;
								aux1 = aux;
							}
							 
							else
							{
								reserva = aux1->prox;
								aux1->prox = aux;
								aux1 = aux->prox;
								aux->prox = reserva->prox;
								reserva->prox = aux1;
								aux = aux1;
								ant = reserva;	
							}
						}
						 
						else if(aux==reserva&&aux1->prox->prox==null)
						{
							aux1->prox->prox = aux->prox;
							reserva=aux1->prox;
							aux1->prox = aux;
							aux->prox = null;
							ant = reserva;
							aux = reserva->prox;
							aux1=aux;
						}
						 
						else if(aux1->prox->prox==null)
						{
							ant->prox = aux1->prox;
							aux1->prox = aux;
							aux1=ant->prox;
							aux1->prox = aux->prox;
							aux->prox = null;
							aux = aux1->prox;
							ant = aux1;
							aux1 = aux;
						}
						 
						else
						{
							ant->prox = aux1->prox;
							aux1->prox = aux;
							aux1 = ant->prox->prox;
							ant->prox->prox = aux->prox;
							aux->prox = aux1;
							ant = ant->prox;
							aux = ant->prox;
							aux1 = aux;
						}
					}
				}
				else
				{
					ant = aux;
					aux = aux->prox;
				}
			}
			return reserva;
		}
		
	}
	else if(opc==2)
	{
		 
		if(qnt_reservas==2)
		{
			aux = reserva->prox;
			if(aux->ano > reserva->ano)
			{
				reserva->prox = null;
				aux->prox = reserva;
				reserva = aux;
				return reserva;
			}
			else if(aux->ano == reserva->ano)
			{
				if(aux->mes > reserva->mes)
				{
					reserva->prox = null;
					aux->prox = reserva;
					reserva = aux;
					return reserva;
				}
				else if(aux->mes == reserva->mes)
				{
					if(aux->dia > reserva->dia)
					{
						reserva->prox = null;
						aux->prox = reserva;
						reserva = aux;
						return reserva;
					}
				}
			}
		}
		 
		else
		{
			aux=reserva;
			aux1=aux->prox;
			dia = aux->dia;
			mes = aux->mes;
			ano = aux->ano;
			
			for(int i=0; i<qnt_reservas; i++)
			{
				dia = aux->dia;
				mes = aux->mes;
				ano = aux->ano;
				aux1=aux;
				 
				while(aux1!=null)
				{
					if(aux1->ano==ano)
					{
						if(aux1->mes==mes)
						{
							if(aux1->dia>dia)
							{
								id_usuario = aux1->id_usuario;
								id_livro = aux1->id_livro;
								dia = aux1->dia;
								mes = aux1->mes;
								ano = aux1->ano;
								aux1 = aux1->prox;
							}
							else
							{
								aux1 = aux1->prox;
							}
						}
						else if(aux1->mes>mes)
						{
							id_usuario = aux1->id_usuario;
							id_livro = aux1->id_livro;
							dia = aux1->dia;
							mes = aux1->mes;
							ano = aux1->ano;
							aux1 = aux1->prox;
						}
						else
						{
							aux1 = aux1->prox;
						}
					}
					else if(aux1->ano>ano)
					{
						id_usuario = aux1->id_usuario;
						id_livro = aux1->id_livro;
						dia = aux1->dia;
						mes = aux1->mes;
						ano = aux1->ano;
						aux1 = aux1->prox;
					}
					else
					{
						aux1 = aux1->prox;
					}
				}
				aux1 = aux;
				 
				 
				if(dia!=aux->dia||mes!=aux->mes||ano!=aux->ano)
				{
					 
					while(aux1->prox!=null&&(aux1->prox->ano!=ano||aux1->prox->mes!=mes||aux1->prox->dia!=dia))
					{
						aux1 = aux1->prox;
					}
					 
					if(aux1->prox!=null&&aux1->prox->ano==ano&&aux1->prox->mes==mes&&aux1->prox->dia==dia)
					{
						 
						if(aux==reserva&&aux1->prox->prox!=null)
						{
							 
							if(aux==aux1)
							{
								reserva = aux->prox;
								aux = reserva->prox;
								aux1->prox = aux;
								reserva->prox = aux1;
								ant = reserva;
								aux = reserva->prox;
								aux1 = aux;
							}
							 
							else
							{
								reserva = aux1->prox;
								aux1->prox = aux;
								aux1 = aux->prox;
								aux->prox = reserva->prox;
								reserva->prox = aux1;
								aux = aux1;
								ant = reserva;	
							}
						}
						 
						else if(aux==reserva&&aux1->prox->prox==null)
						{
							aux1->prox->prox = aux->prox;
							reserva=aux1->prox;
							aux1->prox = aux;
							aux->prox = null;
							ant = reserva;
							aux = reserva->prox;
							aux1=aux;
						}
						 
						else if(aux1->prox->prox==null)
						{
							ant->prox = aux1->prox;
							aux1->prox = aux;
							aux1=ant->prox;
							aux1->prox = aux->prox;
							aux->prox = null;
							aux = aux1->prox;
							ant = aux1;
							aux1 = aux;
						}
						 
						else
						{
							ant->prox = aux1->prox;
							aux1->prox = aux;
							aux1 = ant->prox->prox;
							ant->prox->prox = aux->prox;
							aux->prox = aux1;
							ant = ant->prox;
							aux = ant->prox;
							aux1 = aux;
						}
					}
				}
				else
				{
					ant = aux;
					aux = aux->prox;
				}
			}
			return reserva;	
		}
	}
}

 
int tamanho_arquivo(file *arquivo, const char *nome_arquivo)
{
    arquivo = fopen(nome_arquivo, "r");

    if(arquivo == null)
    {
    	return 0;	
	}

    fseek(arquivo, 0, seek_end);
    int tamanho = ftell(arquivo);
    fclose(arquivo);

    return tamanho;
}

int main()
{
	 
	file *arquivo;
	 
	usuario *usuario=null;
	livro *livro=null;
	reserva *reserva=null;
	
	 
	int errcode = access("quantidades.txt", f_ok);
	 
    if(errcode == 0)
    {
		 
    	if(tamanho_arquivo(arquivo, "quantidades.txt")==0)
    	{
    		 
		}
		else
		{
			 
			arquivo = fopen("quantidades.txt", "r");
			while(!feof(arquivo))
			{
				fscanf(arquivo, "%d %d %d", &qnt_usuarios, &qnt_livros, &qnt_reservas);	
			}
			fclose(arquivo);
		}			
	}
	 
	else
	{
		 
		if ((arquivo = fopen("quantidades.txt", "w")) == null) 
		{
			printf ("\nerro: arquivo quantidades nao pode ser criado!\n\n");
			fclose(arquivo);
		}
		else
		{
			fprintf(arquivo, "0 0 0");
			fclose(arquivo);
			qnt_usuarios = 0;
			qnt_livros = 0;
			qnt_reservas = 0;
		}
	}
	
	 
	errcode = access("usuarios.txt", f_ok);
	 
    if(errcode == 0)
    {
    	 
    	if(tamanho_arquivo(arquivo, "usuarios.txt")==0)
    	{
    		 
		}
		else
		{
			 
			usuario = leusuarios(arquivo, usuario);
		}	
	}
	 
	else
	{
		 
		if ((arquivo = fopen("usuarios.txt", "w")) == null) 
		{
			printf ("\nerro: arquivo usuarios nao pode ser criado!\n\n");
			fclose(arquivo);
		}
		else
		{
			fclose(arquivo);
		}
	}
	
	 
	errcode = access("livros.txt", f_ok);
	 
    if(errcode == 0)
    {
		 
    	if(tamanho_arquivo(arquivo, "livros.txt")==0)
    	{
    		 
		}
		else
		{
			 
			livro = lelivros(arquivo, livro);
		}		
	}
	 
	else
	{
		 
		if ((arquivo = fopen("livros.txt", "w")) == null) 
		{
			printf ("\nerro: arquivo livros nao pode ser criado!\n\n");
			fclose(arquivo);
		}
		else
		{
			fclose(arquivo);
		}	
	}
	
	 
	errcode = access("reservas.txt", f_ok);
	 
    if(errcode == 0)
    {
		 
    	if(tamanho_arquivo(arquivo, "reservas.txt")==0)
    	{
    		 
		}
		else
		{
			 
			reserva = lereservas(arquivo, reserva);
		}			
	}
	 
	else
	{
		 
		if ((arquivo = fopen("reservas.txt", "w")) == null) 
		{
			printf ("\nerro: arquivo reservas nao pode ser criado!\n\n");
			fclose(arquivo);
		}
		else
		{
			fclose(arquivo);
		}
	}
	
	 
	if(qnt_usuarios>0)
	{
		listausuarios(usuario);	
	}
	
	 
	if(qnt_livros>0)
	{
		listalivros(livro);
	}
	
	 
	if(qnt_reservas>0)
	{
		listareservas(reserva);
	}
	
	 
	int opc=10, opc2=0;
	while(opc!=0)
	{
		printf("\nselecione uma opcao:\n\n[0] salvar e sair\t[1] cadastrar usuario\n\n[2] cadastrar livro\t[3] excluir usuario\n\n[4] excluir livro\t[5] reservar livro\n\n[6] devolver livro\t[7] fazer consulta\n\n[8] ordenar livros reservados em ordem crescente de data de devolucao\n\n[9] ordenar livros reservados em ordem decrescente de data de devolucao\n\n");
		scanf("%d",&opc);
		
		if(opc!=0&&opc!=1&&opc!=2&&opc!=3&&opc!=4&&opc!=5&&opc!=6&&opc!=7&&opc!=8&&opc!=9)
		{
			printf("\nerro: opcao invalida!\n");
		}
		else
		{
			if(opc==0)
			{
				 
			}
			 
			else if(opc==1)
			{
				usuario = criausuario(usuario);
			}
			 
			else if(opc==2)
			{
				livro = crialivro(livro);
			}
			 
			else if(opc==3)
			{
				usuario = deletausuario(usuario);
			}
			 
			else if(opc==4)
			{
				livro = deletalivro(livro);
			}
			 
			else if(opc==5)
			{
				reserva = reservalivro(usuario, livro, reserva);
			}
			 
			else if(opc==6)
			{
				reserva = devolvelivro(usuario, livro, reserva);
			}
			 
			else if(opc==7)
			{
				printf("\nselecione uma opcao:\n\n[1] numero de usuarios\t[2] numero de livros\n\n[3] numero de livros reservados\t[4] listar usuarios\n\n[5] listar livros\t[6] listar reservas\n\n");
				scanf("%d",&opc2);
				
				if(opc2!=1&&opc2!=2&&opc2!=3&&opc2!=4&&opc2!=5&&opc2!=6)
				{
					printf("\nerro: opcao invalida!\n");
				}
				else
				{
					 
					if(opc2==1)
					{
						printf("\nnumero de usuarios: %d\n",qnt_usuarios);
					}
					 
					else if(opc2==2)
					{
						printf("\nnumero de livros: %d\n",qnt_livros);
					}
					 
					else if(opc2==3)
					{
						printf("\nnumero de livros reservados: %d\n",qnt_reservas);
					}
					 
					else if(opc2==4)
					{
						listausuarios(usuario);
					}
					 
					else if(opc2==5)
					{
						listalivros(livro);
					}
					 
					else if(opc2==6)
					{
						listareservas(reserva);	
					}
				}
			}
			 
			else if(opc==8)
			{
				if(qnt_reservas==0)
				{
					printf("\nerro: nao existem livros reservados!\n");
				}
				else if(qnt_reservas==1)
				{
					printf("\nerro: existe apenas 1 livro reservado!\n");
				}
				else
				{
					reserva = selectionsort(reserva, 1);	
				}
			}
			 
			else if(opc==9)
			{
				if(qnt_reservas==0)
				{
					printf("\nerro: nao existem livros reservados!\n");
				}
				else if(qnt_reservas==1)
				{
					printf("\nerro: existe apenas 1 livro reservado!\n");
				}
				else
				{
					reserva = selectionsort(reserva, 2);
				}
			}
		}	
	}
	
	 
	salvaarquivo(arquivo, usuario, livro, reserva, 1);
	salvaarquivo(arquivo, usuario, livro, reserva, 2);
	salvaarquivo(arquivo, usuario, livro, reserva, 3);
	
	 
	arquivo = fopen("quantidades.txt", "w");
	fprintf(arquivo, "%d %d %d", qnt_usuarios, qnt_livros, qnt_reservas);
	fclose(arquivo);
	
	return 0;
}
