#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define m 10

struct Data
{ 
    int dia;
    int mes;
    int ano;
};
struct Registro
{
    char matricula[m];
    char nome[40];
    struct Data data;
    float nota;
    struct Registro *next;
};

typedef struct Data data;
typedef struct Registro registro;

void incluir(registro *head );
void excluir(registro *head );
void listar(registro *head  );
void inverso(registro *head );
void numelementos(registro *head );
void limpar(registro *head );

void excluirItem(registro *anterior, registro *excluido);
int listavazia(registro *head);
void insere(registro *anterior, registro *novo);

int main(){
    int comando;
    registro *head = (registro *)malloc(sizeof(registro));
    head->next = NULL;

    void (*funcoes[6])(registro *head);
    funcoes[0] = limpar;
    funcoes[1] = incluir;
    funcoes[2] = excluir;
    funcoes[3] = listar;
    funcoes[4] = inverso;
    funcoes[5] = numelementos;

    do
    {   
        scanf("%d", &comando);
        if (comando>=0 && comando <=5) funcoes[comando](head);
    } while (comando!=0);
    printf("\n");
    return 0;
}

void incluir(registro *head )
{
    registro *temp = head, *aluno = (registro *)malloc(sizeof(registro ));
    scanf(" %s", aluno->matricula);
    scanf(" %s", aluno->nome);
    scanf("%d/%d/%d", &aluno->data.dia, &aluno->data.mes, &aluno->data.ano);
    scanf("%f", &aluno->nota);
    aluno->next = NULL;
    while(temp->next != NULL) temp = temp->next;
    temp->next = aluno;
}

void excluir(registro *head)
{
    char matri[m];
    scanf("%s", matri);
    if (listavazia(head) == 0) return ;
    registro *temp = head->next, *aux = head, *tempRemove;
    while(temp != NULL){
        if (strcmp(temp->matricula, matri) == 0){
            tempRemove=temp;
            temp=temp->next;
            excluirItem(aux,tempRemove);
            continue;
        }
        temp = temp->next;
        aux = aux->next;
    }
}

void listar(registro *head )
{
    if (listavazia(head) == 0) return ;
    registro *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
        printf("%s, %s, %d/%d/%d, %.2f\n", temp->matricula, temp->nome, 
            temp->data.dia, temp->data.mes, temp->data.ano, temp->nota);
    }
}

void inverso(registro *head )
{
    if (listavazia(head) == 0) return ;
    registro *temp, *contra = (registro *)malloc(sizeof(registro *));
    contra->next = NULL;
    while (head->next != NULL)
    {
        temp = head->next;
        head->next = temp->next;
        insere(contra, temp);

    }
    listar(contra);
    while (contra->next != NULL)
    {
        temp = contra->next;
        contra->next = temp->next;
        insere(head, temp);
    }
    free(contra);
}
void numelementos(registro *head )
{
    registro *temp = head;
    int count = 0;
    while(temp->next != NULL)
    {
        temp=temp->next;
        count++;
    }
    printf("%d\n", count);
}

void limpar(registro *head )
{
    int t = 0;
    while(head->next != NULL)
    {
        excluirItem(head, head->next);
        t++;
    }
    head->next = NULL;
    free(head);
    for (int i=0; i<t; i++) printf("-");
}

int listavazia(registro *head)
{
    if(head->next!=NULL) return 1;
    printf("Lista Vazia!\n");
    return 0;
}

void insere(registro *anterior, registro *novo)
{
    novo->next = anterior->next;
    anterior->next = novo;
}


void excluirItem(registro *anterior, registro *excluido)
{
    anterior->next = excluido->next;
    excluido->next = NULL;
    free(excluido);
}