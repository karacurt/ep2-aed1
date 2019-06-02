#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

using namespace std;

typedef struct s
{
    char letra;
    struct s *prox;
} NO;

NO *listarNivel(NO *p)
{

    NO *inicio = (NO *)malloc(sizeof(NO));
    inicio->tipo = -1;
    inicio->prox = NULL;
    inicio->sublista = NULL;
    NO *resp = inicio;

    while (p)
    {

        if (p->tipo == 1)
        {
            if (inicio->tipo == -1)
            {
                resp->chave = p->chave;
                resp->tipo = 1;
                resp->prox = NULL;
            }
            else
            {

                resp->prox = (NO *)malloc(sizeof(NO));
                resp = resp->prox;
                resp->chave = p->chave;
                resp->tipo = 1;
                resp->prox = NULL;
            }
        }

        p = p->prox;
    }

    return inicio;
}

NO *listarSubNivel(NO *p)
{

    NO *inicio = (NO *)malloc(sizeof(NO));
    inicio->tipo = -1;
    NO *resp = inicio;

    while (p)
    {

        if (p->tipo != 1 && p->tipo != 2)
            return NULL;

        if (inicio->tipo == -1)
        {
            resp->prox = NULL;
        }
        else
        {
            resp->prox = (NO *)malloc(sizeof(NO));
            resp = resp->prox;
            resp->prox = NULL;
        }

        if (p->tipo == 1)
        {
            resp->chave = p->chave;
            resp->tipo = 1;
        }
        if (p->tipo == 2)
        {
            resp->sublista = p->sublista;
            resp->tipo = 2;
        }
        p = p->prox;
    }
    return inicio;
}

int verificarSub(NO *p)
{
    int resp = -1;
    while (p)
    {
        if (p->tipo == 2)
            resp = 10;
        p = p->prox;
    }
    return resp;
}

NO *listarChaves(NO *entrada)
{
    NO *p = entrada;
    NO *lista = NULL;
    NO *resp = listarNivel(p);
    lista = resp;

    if (lista->tipo != -1)
    {
        while (lista->prox)
            lista = lista->prox;
    }

    NO *sublista = (NO *)malloc(sizeof(NO));
    sublista->tipo = -1;
    NO *subinit = NULL;

    while (p)
    {

        if (p->tipo == 2)
        {

            if (sublista->tipo == -1 && p->sublista)
            {

                subinit = listarSubNivel(p->sublista);
                sublista = subinit;
                while (sublista->prox)
                    sublista = sublista->prox;
            }
            else if (p->sublista)
            {

                sublista->prox = listarSubNivel(p->sublista);
                while (sublista->prox)
                    sublista = sublista->prox;
            }
        }
        p = p->prox;
    }

    int temSub = verificarSub(subinit);

    if (temSub == -1)
    {
        if (lista->tipo != -1)
            lista->prox = subinit;
        else
            resp = subinit;
    }
    else
    {
        if (lista->tipo != -1)
        {
            subinit = listarChaves(subinit);
            lista->prox = subinit;
        }
        else
        {
            subinit = listarChaves(subinit);
            resp = subinit;
        }
    }

    return resp;
}
