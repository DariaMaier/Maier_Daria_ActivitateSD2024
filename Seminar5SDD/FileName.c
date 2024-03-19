#include <stdio.h>
#include<malloc.h>

typedef struct Santier Santier; //definim un alias
typedef struct Nod Nod;

struct Santier {
    char* numeProiect;
    int nrMuncitori;
    float suprafata;
};

struct Nod {
    Santier santier;//informatia utila
    Nod* next;//adresa urmatorului nod
};

//o functie care sa afiseze numele santierului cu densitatea cea mai mare de muncitori pe m^2
float densitateMuncitori(Santier santier) {
    if (santier.suprafata > 0) {
        return santier.nrMuncitori / santier.suprafata;
    }
    else return 0;
}

char* numeSantierDensitateMaxima(Nod* lista) {
    float max = 0;
    char* aux = NULL;
    while (lista != NULL) {
        if (densitateMuncitori(lista->santier) > max) {
            max = densitateMuncitori(lista->santier);
            aux = lista->santier.numeProiect;
        }
        lista = lista->next; //deplasarea
    }
    if (aux != NULL) {
        char* numeProiectDensitate = (char*)malloc(strlen(aux) + 1);
        strcpy(numeProiectDensitate, aux);

        return numeProiectDensitate;
    }
    else return NULL;
}

Santier initializareSantier(const char* numeProiect, int nrMuncitori, float suprafata) {
    Santier santier;
    santier.numeProiect = (char*)malloc(strlen(numeProiect) + 1);
    strcpy(santier.numeProiect, numeProiect);
    santier.nrMuncitori = nrMuncitori;
    santier.suprafata = suprafata;
    return santier;
}

Nod* inserareInceput(Santier santier, Nod* lista) {
    Nod* nod = (Nod*)malloc(sizeof(Nod));
    nod->santier = santier;
    nod->next = lista;
    return nod;

}

//functie care sa afiseze lista
void afisareSantier(Santier santier) {
    printf("Santierul %s are %d muncitori si %f m^2 suprafata\n", santier.numeProiect, santier.nrMuncitori, santier.suprafata);
}

int sumaMuncitori(Nod* lista) {
    int suma = 0;
    while (lista != NULL) {
        suma = suma + lista->santier.nrMuncitori;
        lista = lista->next;
    }
    return suma;

}


void afiseazaLista(Nod* lista) {
    while (lista != NULL) {
        //procesare
        afisareSantier(lista->santier);
        lista = lista->next;
    }
}

//functie de stergere a listei
void stergereLista(Nod** lista) {
    while ((*lista) != NULL) {
        free((*lista)->santier.numeProiect); //am sters numele proiectului
        Nod* aux;
        aux = (*lista)->next;
        free(*lista);
        (*lista) = aux;
    }
    (*lista) = NULL;
}

int main() {
    Nod* lista = NULL;
    Santier s1 = initializareSantier("Santier 1", 10, 300);
    Santier s2 = initializareSantier("Santier 2", 12, 400);
    Santier s3 = initializareSantier("Santier 3", 15, 200);
    lista = inserareInceput(s1, lista);
    lista = inserareInceput(s2, lista);
    lista = inserareInceput(s3, lista);
    lista = inserareInceput(initializareSantier("Santier 4", 10, 34), lista);

    afiseazaLista(lista);

    int suma = 0;
    suma = sumaMuncitori(lista);
    printf("Suma este % d", suma);

    printf("\n%s\n", numeSantierDensitateMaxima(lista));

    stergereLista(&lista);
    afiseazaLista(lista);


}