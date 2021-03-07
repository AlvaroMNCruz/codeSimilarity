#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <ctype.h>







typedef struct livro{ 
	char titulo[100];
	int id;
	int emprestado;
	time_t devolucao;
	
}book;



typedef struct usuario{ 
	char nome[100];
	int id;
	int emprestimos;
	int livros[2];
}user;


typedef struct data_l{ 
	int id;
	time_t entrega;
}data_livro;



struct tm *data_atual;


void leitura_de_numero(void* var, int tipo_de_numero); 
void mostrar_usuarios_todos(); 
void mostrar_livros_todos(); 
int leitura_de_usuario(user *pessoa, int id); 
int leitura_de_livro(book *exemplar, int id); 
void consulta(); 
void insertion(data_livro *vetor, int nelementos); 
void ordenar_livros(int ordem); 
void cadastros(); 
void cadastrar_livro(); 
void cadastrar_usuario(); 
void remover_livro(); 
void remover_usuario(); 
void emprestimo(); 
void emprestar(); 
void devolucao(); 


int main(){
	setlocale(lc_all, "portuguese"); 
	
	
	
	file *livros;
	int numero = 2;
	livros = fopen("livros.dat", "ab");
	if(ftell(livros) == 0){
		fwrite(&numero, sizeof(int), 1, livros);
	}
	
	fclose(livros);
	
	file *usuarios;
	usuarios = fopen("users.dat", "ab");
	if(ftell(usuarios) == 0){
		fwrite(&numero, sizeof(int), 1, usuarios);
	}
	fclose(usuarios);
	
	int menu;
	time_t segundos;
	
	
	
	
	do{
		time(&segundos); 
		data_atual = localtime(&segundos); 
		printf("\n\n\t\tdata %.2d/%.2d/%d\n\n", data_atual->tm_mday, data_atual->tm_mon+1, data_atual->tm_year+1900);
		printf("\t\t  __  __ ___ _  _ _   _ \n");
		printf("\t\t |  \\/  | __| \\| | | | |\n"); 
		printf("\t\t | |\\/| | _|| .` | |_| |\n");
		printf("\t\t |_|  |_|___|_|\\_|\\___/ \n\n");
		printf("\tescolha uma opã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o:\n\t\t[1] cadastros\n\t\t[2] emprã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â©stimos\n\t\t[3] consulta\n\t\t[4] sair\n\n\t\t--->");
		
		while(1){ 
			
			leitura_de_numero(&menu, 1);
			if(menu<1 || menu > 4){ 
				printf("\n\topã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o invã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡lida, digite novamente!\n\t\t--->");
			}
			else{
				break; 
			}
		}
		
		switch(menu){
			
			case 1: 
				cadastros();
				break;
				
			case 2: 
				emprestimo();
				break;
				
			case 3: 
				consulta();
				break;
				
			case 4: 
				
				break;
			
		}
		
	}while(menu!=4); 
	return 0;
}


int leitura_de_usuario(user *pessoa, int id){ 
	
	file *arquivo_users; 
	if((arquivo_users = fopen("users.dat", "rb"))==null){ 
		printf("\nerro ao abrir o arquivo\n");
		return -1;
	}
	int nusuarios;
	fread(&nusuarios, sizeof(int), 1, arquivo_users); 
	if(pessoa==null){ 
		return nusuarios;
	}
	
	if(id>nusuarios || id<1){ 
		printf("\nerro usuario nã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o encontrado\n");
		return -1;
	}
	fseek(arquivo_users, (sizeof(int) + (id-1)*sizeof(user)), seek_set ); 
	fread(pessoa, sizeof(user), 1, arquivo_users); 
	fclose(arquivo_users); 
	
	return nusuarios; 
}

int leitura_de_livro(book *exemplar, int id){
	
	file *arquivo_livros; 
	
	if((arquivo_livros = fopen("livros.dat", "rb"))==null){ 
		printf("\nerro ao abrir o arquivo\n");
		return -1;
	}
	int nlivros;
	fread(&nlivros, sizeof(int), 1, arquivo_livros); 
	if(exemplar == null){ 
		return nlivros;
	}
	
	if(id>nlivros || id<1){ 
		printf("\nerro livro nã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o encontrado\n");
		return -1;
	}
	
	fseek(arquivo_livros, ( sizeof(int) + (id - 1) * sizeof(book)), seek_set); 
	fread(exemplar, sizeof(book), 1, arquivo_livros); 
	fclose(arquivo_livros); 
	return nlivros; 
}

void consulta(){ 
	int menu;
	do{ 
		printf("\n\t[1] mostra todos os usuarios\n\t[2] mostra todos os livros\n\t[3] ordenar por data de entrega (crescente)\n\t[4] ordenar por data de entrega (decrescente)\n\t[5] sair\t\t--->");
		while(1){ 
			
			leitura_de_numero(&menu, 1); 
			if(menu<1 || menu > 5){ 
				printf("\n\topã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o invã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡lida, digite novamente!\n\t\t--->");
			}
			else{
				break; 
			}
		}
		
		switch(menu){ 
			
			case 1:
				mostrar_usuarios_todos(); 
				break;
				
			case 2:
				mostrar_livros_todos(); 
				break;
				
			case 3:
				ordenar_livros(0); 
				break;
			case 4:
				ordenar_livros(1); 
				break;
			case 5: 
				break;
		}
		
		
	}while(menu!=5); 
}

void mostrar_usuarios_todos(){ 
	user amostra;
	book exemplar;
	int i, j, nusuarios;
	nusuarios = leitura_de_usuario(null, 0); 
	printf("\n\texistem %d usuã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡rios\n", nusuarios); 
	for(i=1; i<=nusuarios; i++){ 
		leitura_de_usuario(&amostra, i); 
		printf("\n\n\tnome: %s\n\tid: %d\n\t%d/3 livros emprestados", amostra.nome, amostra.id, amostra.emprestimos); 
		if(amostra.emprestimos>0){ 
			for(j=0; j<amostra.emprestimos; j++){ 
				leitura_de_livro(&exemplar, amostra.livros[j]); 
				printf("\n\t\tlivro: %s\n\t\tid: %d", exemplar.titulo, exemplar.id); 
			}
		}
	}
	
	
}

void mostrar_livros_todos(){ 
	int nlivros, i;
	book exemplar;
	struct tm *data_de_entrega; 
	time_t segundos;
	time(&segundos);
	
	nlivros = leitura_de_livro(null, 0); 
	printf("existem %d livros", nlivros);
	for(i = 1; i<=nlivros; i++){ 
		leitura_de_livro(&exemplar, i); 
		printf("\n\n\ttã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â­tulo: %s\n\tid: %d\n\t", exemplar.titulo, exemplar.id); 
		if(exemplar.emprestado==1){ 
			data_de_entrega = localtime(&exemplar.devolucao);
			printf("situaã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o: emprestado\n\tentrega: %d/%d/%d", data_de_entrega->tm_mday, (data_de_entrega->tm_mon+1), (data_de_entrega->tm_year + 1900));
			if(segundos>exemplar.devolucao){ 
				printf("\n\tatrasado\n");
			}
		}
		else{ 
			printf("situaã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o: disponã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â­vel\n");
		}
	}
	
}

void ordenar_livros(int ordem){ 
	int n_livros, i;
	n_livros = leitura_de_livro(null, 0);
	data_livro *datas;
	book exemplar; 
	time_t segundos;
	time(&segundos);
	struct tm *data_de_entrega;
	datas = (data_livro*) malloc(n_livros*sizeof(data_livro));
	
	
	for(i = 1; i<=n_livros; i++){ 
		leitura_de_livro(&exemplar, i); 
		(datas+ i - 1)->id = i; 
		(datas + i - 1)->entrega = exemplar.devolucao; 
	}
	insertion(datas, n_livros); 
	
	
	if(ordem == 0){ 
		for(i=0; i<n_livros; i++){ 
			leitura_de_livro(&exemplar, datas[i].id); 
			printf("\n\n\ttã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â­tulo: %s\n\tid: %d\n\t", exemplar.titulo, exemplar.id); 
			if(exemplar.emprestado==1){ 
				data_de_entrega = localtime(&exemplar.devolucao);
				printf("situaã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o: emprestado\n\tentrega: %d/%d/%d", data_de_entrega->tm_mday, (data_de_entrega->tm_mon+1), (data_de_entrega->tm_year + 1900));
				if(segundos>exemplar.devolucao){
					printf("\n\tatrasado\n");
				}
			}
			else{ 
				printf("situaã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o: disponã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â­vel\n");
			}
		}
	}
	if(ordem == 1){ 
		for(i=n_livros-1; i>=0; i--){ 
			leitura_de_livro(&exemplar, datas[i].id); 
			printf("\n\n\ttã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â­tulo: %s\n\tid: %d\n\t", exemplar.titulo, exemplar.id); 
			if(exemplar.emprestado==1){ 
				data_de_entrega = localtime(&exemplar.devolucao);
				printf("situaã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o: emprestado\n\tentrega: %d/%d/%d", data_de_entrega->tm_mday, (data_de_entrega->tm_mon+1), (data_de_entrega->tm_year + 1900));
				if(segundos>exemplar.devolucao){
					printf("\n\tatrasado\n");
				}
			}
			else{ 
				printf("situaã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o: disponã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â­vel\n");
			}
		}
	}	
	
} 

void insertion(data_livro* numeros, int nelementos){ 
	int i, j;
	data_livro aux;
	for(i=1; i<nelementos; i++){ 
		j = i;
		while(difftime((numeros+j)->entrega, (numeros + j - 1)->entrega) < 0 && j != 0){ 
			aux = *(numeros + j);
			*(numeros + j) = *(numeros + j - 1); 
			*(numeros + j - 1) = aux;
			j--;
		}
	}
}

void cadastros(){ 
	int menu;
	do{
		
		printf("\n\tescolha uma opã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o:\n\t\t[1] cadastrar livro\n\t\t[2] cadastrar usuã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡rio\n\t\t[3] remover livro\n\t\t[4] remover usuã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡rio\n\t\t[5] sair\n\t\t--->");
		while(1){ 
			
			leitura_de_numero(&menu, 1);
			if(menu<1 || menu > 5){ 
				printf("\n\topã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o invã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡lida, digite novamente!\n\t\t--->");
			}
			else{
				break; 
			}
		}
		
		switch(menu){ 
			case 1: 
				cadastrar_livro();
				break;
			case 2: 
				cadastrar_usuario();
				break;
			case 3: 
				remover_livro();
				break;
			case 4: 
				remover_usuario();
				break;
			case 5: 
				
				break;
		}
		
		
	}while(menu != 5); 
	
}

void cadastrar_livro(){ 
	book exemplar;
	file *arquivo; 
	int n;
	char titulo[100];
	printf("\n\tdigite o nome do livro a ser cadastrado\n"); 
	scanf("%[^\n]s", titulo); 
	strcpy(exemplar.titulo, titulo); 
	n = leitura_de_livro(null, 0); 
	n++; 
	exemplar.id = n; 
	exemplar.emprestado = 0; 
	exemplar.devolucao = 0; 
	
	if((arquivo = fopen("livros.dat", "rb+")) == null){ 
		printf("\n\n\terro ao abrir o arquivo\n"); 
		return; 
	}
	
	
	fwrite(&n, sizeof(int), 1, arquivo); 
	
	fseek(arquivo, 0, seek_end); 
	fwrite(&exemplar, sizeof(book), 1, arquivo); 
	
	fclose(arquivo); 
} 

void cadastrar_usuario(){ 
	user pessoa;
	int i, n; 
	file*arquivo;
	
	n = leitura_de_usuario(null, 0); 
	
	
	
	char nome[100];
	printf("\n\tdigite o nome do usuario\n\t\t--->"); 
	scanf("%[^\n]s", nome); 
	strcpy(pessoa.nome, nome); 
	pessoa.emprestimos = 0; 
	n++; 
	pessoa.id = n; 
	for(i=0; i<3; i++){ 
		pessoa.livros[i] = 0;
	}
	
	if((arquivo = fopen("users.dat", "rb+")) == null){ 
		printf("\n\n\terro ao abrir o arquivo\n"); 
		return;
	}
	
	
	fwrite(&n, sizeof(int), 1, arquivo); 
	fseek(arquivo, 0, seek_end); 
	fwrite(&pessoa, sizeof(user), 1, arquivo); 
	
	fclose(arquivo); 
	
} 

void remover_usuario(){ 
	int id, n, i;
	user removido, *pessoas; 
	printf("\n\tqual o id do usuã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡rio que se deseja remover?\n\t\t--->"); 
	n = leitura_de_usuario(null, 0); 
	if(n==0){ 
		printf("\n\tnã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o existe usuã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡rio para ser removido\n");
		return;
	}
	while(1){ 
			
		leitura_de_numero(&id, 1);
		if(id<1 || id > n){ 
			printf("\n\topã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o invã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡lida, digite novamente!\n\t\t--->");
		}
		else{
			break; 
		}
	}
	leitura_de_usuario(&removido, id); 
	if(removido.emprestimos != 0){ 
		printf("o usuario nã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o pode ser removido, primeiro faã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§a a devoluã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o");
		return; 
	}
	
	
	file*arquivo; 
	if((arquivo = fopen("users.dat", "rb")) == null){ 
		printf("\n\n\terro ao abrir o arquivo\n");
		return; 
	}
	
	pessoas = (user*)malloc(n*sizeof(user)); 
	fread(&n, sizeof(int), 1, arquivo); 
	for(i=0; i<n; i++){ 
		fread((pessoas+i), sizeof(user), 1, arquivo);
	}
	fclose(arquivo); 
	remove("livros.dat"); 
	if((arquivo = fopen("users.dat", "wb")) == null){ 
		printf("\n\n\terro ao abrir o arquivo\n");
		return; 
	}
	
	
	n--; 
	fwrite(&n, sizeof(int), 1, arquivo); 
	for(i=0; i<=n; i++){ 
		if(i+1 != id){
			if(i+1>id){ 
				(pessoas+i)->id--;
			}
			fwrite((pessoas + i), sizeof(user), 1, arquivo); 
		}
	}
	fclose(arquivo); 
	
	for(i=0; i<n;i++){ 
		free((pessoas+i));
	}
}

void remover_livro(){ 
	
	int id, n, i; 
	book removido, *exemplares;
	printf("\n\tqual o id do livro que se deseja remover?\n\t\t--->");
	n = leitura_de_livro(null, 0); 
	if(n==0){ 
		printf("\n\tnã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o existe livro para ser removido\n");
		return;
	}
	while(1){ 
			
		leitura_de_numero(&id, 1);
		if(id<1 || id > n){ 
			printf("\n\topã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o invã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡lida, digite novamente!\n\t\t--->");
		}
		else{
			break; 
		}
	}
	leitura_de_livro(&removido, id); 
	if(removido.emprestado != 0){ 
		printf("o livro emprestado nã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o pode ser removido, primeiro faã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§a a devoluã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o"); 
		return;
	}
	
	
	file*arquivo; 
	if((arquivo = fopen("livros.dat", "rb")) == null){ 
		printf("\n\n\terro ao abrir o arquivo\n");
		return;
	}
	
	exemplares = (book*)malloc(n*sizeof(book)); 
	fread(&n, sizeof(int), 1, arquivo); 
	for(i=0; i<n; i++){ 
		fread((exemplares+i), sizeof(book), 1, arquivo); 
	}
	fclose(arquivo); 
	remove("livros.dat"); 
	if((arquivo = fopen("livros.dat", "wb")) == null){ 
		printf("\n\n\terro ao abrir o arquivo\n"); 
		return;
	}
	
	
	n--; 
	fwrite(&n, sizeof(int), 1, arquivo); 
	for(i=0; i<=n; i++){ 
		if(i+1 != id){ 
			if(i+1>id){ 
				(exemplares+i)->id--;
			}
			fwrite((exemplares + i), sizeof(book), 1, arquivo); 
		}
	}
	fclose(arquivo); 
	
	for(i=0; i<n;i++){ 
		free((exemplares+i));
	}

}




void emprestimo(){
	
	int menu;
	do{
		
		printf("\n\tescolha uma opã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o:\n\t\t[1] emprestar livro\n\t\t[2] devoluã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o de livro\n\t\t[3] sair\n\t\t--->");
		while(1){ 
			
			leitura_de_numero(&menu, 1);
			if(menu<1 || menu > 5){ 
				printf("\n\topã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o invã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡lida, digite novamente!\n\t\t--->");
			}
			else{
				break; 
			}
		}
		
		switch(menu){ 
			case 1:
				emprestar(); 
				break;
			case 2:
				devolucao(); 
				break;
			case 3:
				break;
		}
		
		
	}while(menu != 3); 
	
	
}

void emprestar(){ 
	int id_livro, id_usuario, n_livros, n_usuarios;
	n_livros = leitura_de_livro(null, 0); 
	n_usuarios = leitura_de_usuario(null, 0);
	book exemplar;
	user pessoa;
	time_t segundos;
	time(&segundos); 
	printf("\n\tdigite o id do livro\n\t\t--->");
	while(1){ 
			
		leitura_de_numero(&id_livro, 1);
		if(id_livro<1 || id_livro > n_livros){ 
			printf("\n\topã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o invã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡lida, digite novamente!\n\t\t--->");
		}
		else{
			break; 
		}
	}
	leitura_de_livro(&exemplar, id_livro); 
	if(exemplar.emprestado == 1){ 
		printf("o livro jã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡ estã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡ emprestado");
		return;
	}
	printf("\n\tdigite o id do usuã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡rio\n\t\t--->"); 
	while(1){ 
			
		leitura_de_numero(&id_usuario, 1);
		if(id_livro<1 || id_livro > n_usuarios){ 
			printf("\n\topã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o invã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡lida, digite novamente!\n\t\t--->");
		}
		else{
			break; 
		}
	}
	leitura_de_usuario(&pessoa, id_usuario); 
	if(pessoa.emprestimos == 3){ 
		printf("o usuario jã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡ tem emprestado muitos livros");
		return;
	}
	exemplar.emprestado = 1; 
	exemplar.devolucao = segundos + 604800; 
	pessoa.livros[pessoa.emprestimos] = id_livro; 
	pessoa.emprestimos++; 
	
	file *arquivo_livro, *arquivo_pessoa; 
	if((arquivo_livro = fopen("livros.dat", "rb+")) == null){ 
		printf("\n\n\terro ao abrir o arquivo\n");
		return;
	}
	fseek(arquivo_livro, (sizeof(int) + (id_livro-1)*sizeof(book)), seek_set); 
	fwrite(&exemplar, sizeof(book), 1, arquivo_livro); 
	fclose(arquivo_livro); 
	if((arquivo_pessoa = fopen("users.dat", "rb+")) == null){ 
		printf("\n\n\terro ao abrir o arquivo\n");
		return;
	}
	fseek(arquivo_pessoa, (sizeof(int) + (id_usuario-1)*sizeof(user)), seek_set); 
	fwrite(&pessoa, sizeof(user), 1, arquivo_pessoa); 
	fclose(arquivo_pessoa); 
	
}

void devolucao(){ 
	
	int id_livro, id_usuario, n_livros, n_usuarios;
	n_livros = leitura_de_livro(null, 0); 
	n_usuarios = leitura_de_usuario(null, 0);
	book exemplar;
	user pessoa;
	time_t segundos;
	time(&segundos); 
	
	
	
	
	
	printf("\n\tdigite o id do livro\n\t\t--->"); 
	while(1){ 
			
		leitura_de_numero(&id_livro, 1);
		if(id_livro<1 || id_livro > n_livros){ 
			printf("\n\topã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o invã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡lida, digite novamente!\n\t\t--->");
		}
		else{
			break; 
		}
	}
	leitura_de_livro(&exemplar, id_livro); 
	if(exemplar.emprestado != 1){ 
		printf("o livro nã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o estã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡ emprestado");
		return;
	}
	printf("\n\tdigite o id do usuã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡rio\n\t\t--->"); 
	while(1){ 
			
		leitura_de_numero(&id_usuario, 1);
		if(id_livro<1 || id_livro > n_usuarios){ 
			printf("\n\topã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â§ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o invã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡lida, digite novamente!\n\t\t--->");
		}
		else{
			break; 
		}
	}
	leitura_de_usuario(&pessoa, id_usuario); 
	if(pessoa.livros[0]!=id_livro && pessoa.livros[1]!=id_livro && pessoa.livros[2]!=id_livro){ 
		printf("o usuã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡rio nã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â£o pegou emprestado este livro"); 
		return; 
	}
	
	if(pessoa.livros[0]==id_livro){ 
		pessoa.livros[0] = pessoa.livros[1];
		pessoa.livros[1] = pessoa.livros[2];
		pessoa.livros[2] = 0;
	}
	else if(pessoa.livros[1]!=id_livro){ 
		pessoa.livros[1] = pessoa.livros[2];
		pessoa.livros[2] = 0;
	}
	else if(pessoa.livros[2]!=id_livro){ 
		pessoa.livros[2] = 0;
	}
	pessoa.emprestimos--; 
	exemplar.emprestado = 0; 
	
	file *arquivo_livro, *arquivo_pessoa; 
	if((arquivo_livro = fopen("livros.dat", "rb+")) == null){ 
		printf("\n\n\terro ao abrir o arquivo\n");
		return; 
	}
	fseek(arquivo_livro, (sizeof(int) + (id_livro-1)*sizeof(book)), seek_set); 
	fwrite(&exemplar, sizeof(book), 1, arquivo_livro); 
	fclose(arquivo_livro); 
	if((arquivo_pessoa = fopen("users.dat", "rb+")) == null){ 
		printf("\n\n\terro ao abrir o arquivo\n");
		return; 
	}
	fseek(arquivo_pessoa, (sizeof(int) + (id_usuario-1)*sizeof(user)), seek_set); 
	fwrite(&pessoa, sizeof(user), 1, arquivo_pessoa); 
	fclose(arquivo_pessoa); 
}



void leitura_de_numero(void* var, int tipo_de_numero){ 
	
int i = 0, confirmacao_de_leitura; 

char numerotxt[11]; 
 
do{ 


confirmacao_de_leitura = 1; 
fflush(stdin); 
if(gets(numerotxt)==null){
	
	confirmacao_de_leitura = 0;
}
else{

	while(numerotxt[i]!='\0'){  
			if(!isdigit(numerotxt[i])){ 
				
				if(confirmacao_de_leitura == 2){ 
					confirmacao_de_leitura = 0; 
					break;
				}
				
				confirmacao_de_leitura = 2; 
				if(!(numerotxt[i] == '.' || numerotxt[i] ==',')){ 
					confirmacao_de_leitura = 0; 
					break;
				}
				if(numerotxt[i]=='.'){ 
					numerotxt[i]=','; 
				}
			}
			i++; 
	}
}
if(strlen(numerotxt)==0){ 
	confirmacao_de_leitura = 0; 
}else if(confirmacao_de_leitura==2 && tipo_de_numero == 1){ 
	printf("\n\tã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â© esperado um nã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢âºmero inteiro!\n\n\tdigite novamente:  "); 
	confirmacao_de_leitura = 0; 
}else if(confirmacao_de_leitura == 0){ 
	printf("\n\tentrada invã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â¡lida! ã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢â© esperado um nã£â£ã¢â£ã£â¢ã¢â£ã£â£ã¢â¢ã£â¢ã¢âºmero.\n\n\tdigite novamente:  "); 
}

}while(confirmacao_de_leitura==0); 

		if(tipo_de_numero == 1){ 
			int* var_int = var; 
			*var_int = atol(numerotxt); 
		}
		else if(tipo_de_numero == 2){ 
			float* var_float = var; 
			*var_float =(float) atof(numerotxt); 
		}
		
	return; 
}


