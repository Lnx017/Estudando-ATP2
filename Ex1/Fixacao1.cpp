#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<conio2.h>

struct TpPessoa
{
	char nome[30],endereco[30];
	int telefone;
};

int BuscaExaustiva(FILE *Ptr, char nome[])
{
    TpPessoa aux;
    int TL, i = 0;
    fseek(Ptr, 0, 2);
    TL = ftell(Ptr) / sizeof(TpPessoa);
    rewind(Ptr);
    fread(&aux, sizeof(TpPessoa), 1, Ptr);
    while(!feof(Ptr) && stricmp(nome, aux.nome) != 0)
    {
        fread(&aux, sizeof(TpPessoa), 1, Ptr);
        i++;
    }
    if(!feof(Ptr) && stricmp(nome, aux.nome) == 0)
        return i;
    else
        return -1;
}

void BuscaNome()
{
    TpPessoa RP;
    char auxnome[30];
    FILE *Ptr = fopen("Pessoas.dat", "rb+");
    if(Ptr == NULL)
    {
        printf("\nErro ao abrir arquivo!");
        return;
    }
    printf("\nDigite o nome da pessoa que busca: ");
    fflush(stdin);
    gets(auxnome);
    int pos = BuscaExaustiva(Ptr, auxnome);
    if(pos == -1)
        printf("\nPessoa nao encontrada");
    else
    {
        fseek(Ptr, pos * sizeof(TpPessoa), 0);
        fread(&RP, sizeof(TpPessoa), 1, Ptr);
        printf("\nNome: %s", RP.nome);
        printf("\nEndereco: %s", RP.endereco);
        printf("\nNumero: %d", RP.telefone);
    }
    getch();
    fclose(Ptr);
}
int BuscaIndexada(FILE *Ptr,char nome[30])
{
	TpPessoa aux;
	rewind(Ptr);
	fread(&aux,sizeof(TpPessoa),1,Ptr);
	while(!feof(Ptr) && stricmp(nome,aux.nome)!=0)
	{
		fread(&aux,sizeof(TpPessoa),1,Ptr);
	}
	if(!feof(Ptr) && stricmp(nome,aux.nome)==0)
		return ftell(Ptr)-sizeof(TpPessoa);
	else
		return -1;
}

void CadPessoa ()
{
	TpPessoa Pessoa;
	char auxnome[30];
	
	FILE *Ptr = fopen("Pessoas.dat", "rb+");
	if(Ptr == NULL)
	{
		printf("Criando arquivo...");
		Ptr = fopen("Pessoas.dat", "wb+");
	}
	
	system("cls");
	printf("\nDigite o nome: ");
	fflush(stdin); gets(auxnome);
	while(auxnome[0]!='\0')
	{
		if(BuscaIndexada(Ptr,auxnome)==-1)
		{
			strcpy(Pessoa.nome,auxnome);
			printf("\nEndereco: "); fflush(stdin);
			gets(Pessoa.endereco);
			printf("\nTelefone: ");
			scanf("%d", &Pessoa.telefone);
			fwrite(&Pessoa,sizeof(TpPessoa),1,Ptr);
		}
		else
			printf("\nPessoa ja cadastrada!!");	
		printf("\nDigite o nome: ");
		fflush(stdin); gets(auxnome);
	}
	fclose(Ptr);
}

int main()
{
    char nome[30];
    int pos;
    FILE *Ptr;
    CadPessoa();
    BuscaNome();
    return 0;
}
