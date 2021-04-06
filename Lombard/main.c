#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

struct Klient{

    char imie[20];
    char nazwisko[30];
    int nrIDklienta;
    float wydane;
    struct Klient *next;

};

struct Przedmiot{

    int nrIDprzedmiotu;
    int nrIDklienta;
    char nazwa[30];
    char status[10]; //zastaw, sprzedany, nasprzedaz
    char stan[10];   //nowy, uzywany
    float kwotaZastaw;
    float wartosc;
    int dzien;
    int miesiac;
    int rok;
    struct Przedmiot *next;
};

//WYPISYWANIE

void wypiszListePrzedmiotow(struct Przedmiot *listaPrzedmiotow){
        struct Przedmiot *tmp=listaPrzedmiotow;
        while(tmp){
            printf("IDp:%d ", tmp->nrIDprzedmiotu);
            printf("IDk:%d ", tmp->nrIDklienta);
            printf("%20s ", tmp->nazwa);
            printf("%10s ", tmp->status);
            printf("%8s ", tmp->stan);
            printf("%0.2f$ ", tmp->kwotaZastaw);
            printf("%0.2f$ ", tmp->wartosc);
            printf("%d:", tmp->dzien);
            printf("%d:", tmp->miesiac);
            printf("%d\n", tmp->rok);
            tmp=tmp->next;
        }

}

void wypiszListeKlientow(struct Klient *listaKlientow){

    struct Klient *tmp=listaKlientow;
    while(tmp){
        printf("%15s ", tmp->nazwisko);
        printf("%10s ", tmp->imie);
        printf("IDk:%d ", tmp->nrIDklienta);
        printf("%0.2f$\n", tmp->wydane);
        tmp=tmp->next;
    }
}

void wypiszLiniePrzedmiotow(struct Przedmiot *tmp){
            printf("IDp:%d ", tmp->nrIDprzedmiotu);
            printf("IDk:%d ", tmp->nrIDklienta);
            printf("%20s ", tmp->nazwa);
            printf("%10s ", tmp->status);
            printf("%8s ", tmp->stan);
            printf("%0.2f$ ", tmp->kwotaZastaw);
            printf("%0.2f$ ", tmp->wartosc);
            printf("%d:", tmp->dzien);
            printf("%d:", tmp->miesiac);
            printf("%d\n", tmp->rok);
}

void wypiszLinieKlientow(struct Klient *tmp){
    printf("%15s ", tmp->nazwisko);
    printf("%10s ", tmp->imie);
    printf("IDk:%3d ", tmp->nrIDklienta);
    printf("%0.2f$\n", tmp->wydane);
}

//WCZYTYWANIE ZAPISYWANIE LISTY PRZEDMIOTOW I KLIENTOW

void zapListKlientPlik(struct Klient *listaKlientow, char *p, int liczbaKlientow){

    FILE *plik=fopen(p, "w");
    struct Klient *tmp=listaKlientow;
    fprintf(plik, "%d\n", liczbaKlientow);
    while(tmp){
        fprintf(plik, "%s ", tmp->imie);
        fprintf(plik, "%s ", tmp->nazwisko);
        fprintf(plik, "%d ", tmp->nrIDklienta);
        fprintf(plik, "%f\n", tmp->wydane);
        tmp=tmp->next;
    }
    fclose(plik);

}

void zapListPrzedmiotPlik(struct Przedmiot *listaPrzedmiotow, char *p, int liczbaPrzedmiotow){

    FILE *plik=fopen(p, "w");
    struct Przedmiot *tmp=listaPrzedmiotow;
    fprintf(plik, "%d\n", liczbaPrzedmiotow);
    while(tmp){
        fprintf(plik, "%d ", tmp->nrIDprzedmiotu);
        fprintf(plik, "%d ", tmp->nrIDklienta);
        fprintf(plik, "%s ", tmp->nazwa);
        fprintf(plik, "%s ", tmp->status);
        fprintf(plik, "%s ", tmp->stan);
        fprintf(plik, "%f ", tmp->kwotaZastaw);
        fprintf(plik, "%f ", tmp->wartosc);
        fprintf(plik, "%d ", tmp->dzien);
        fprintf(plik, "%d ", tmp->miesiac);
        fprintf(plik, "%d\n", tmp->rok);

        tmp=tmp->next;
    }
    fclose(plik);

}

struct Przedmiot *wczytPlikPrzedmiot(char *p){

    FILE *plik = fopen(p, "r");
    if(!plik) printf("Blad otwarcia pliku z przedmiotami");
    int liczbaPrzedmiotow=0;
    fscanf(plik, "%d", &liczbaPrzedmiotow);
    liczbaPrzedmiotow--;
    struct Przedmiot *pierwszy=NULL;
    pierwszy=malloc(sizeof(struct Przedmiot));
    fscanf(plik, "%d", &pierwszy->nrIDprzedmiotu);
    fscanf(plik, "%d", &pierwszy->nrIDklienta);
    fscanf(plik, "%s", pierwszy->nazwa);
    fscanf(plik, "%s", pierwszy->status);
    fscanf(plik, "%s", pierwszy->stan);
    fscanf(plik, "%f", &pierwszy->kwotaZastaw);
    fscanf(plik, "%f", &pierwszy->wartosc);
    fscanf(plik, "%d", &pierwszy->dzien);
    fscanf(plik, "%d", &pierwszy->miesiac);
    fscanf(plik, "%d", &pierwszy->rok);
    pierwszy->next=NULL;
    int i=0;
    for(i=0; i<liczbaPrzedmiotow; i++){
        struct Przedmiot *el, *tmp=pierwszy;
        el=malloc(sizeof(struct Przedmiot));
        fscanf(plik, "%d", &el->nrIDprzedmiotu);;
        fscanf(plik, "%d", &el->nrIDklienta);
        fscanf(plik, "%s", el->nazwa);
        fscanf(plik, "%s", el->status);
        fscanf(plik, "%s", el->stan);
        fscanf(plik, "%f", &el->kwotaZastaw);
        fscanf(plik, "%f", &el->wartosc);
        fscanf(plik, "%d", &el->dzien);
        fscanf(plik, "%d", &el->miesiac);
        fscanf(plik, "%d", &el->rok);
        el->next=NULL;
        while(tmp->next){
            tmp=tmp->next;
        }
        tmp->next=el;
    }
    fclose(plik);
    return pierwszy;

}

struct Klient *wczytPlikKlient(char *p){

    FILE *plik = fopen(p, "r");
    if(!plik) printf("Blad otwarcia pliku klientow");
    int liczbaKlientow=0;
    fscanf(plik, "%d", &liczbaKlientow);
    if(liczbaKlientow==0){
        struct Klient *pierwszy=NULL;
        pierwszy=malloc(sizeof(struct Klient));
        strcpy(pierwszy->imie, "ja");
        strcpy(pierwszy->nazwisko, "ja");
        pierwszy->nrIDklienta=0;
        pierwszy->wydane=0;
        pierwszy->next=NULL;
        return pierwszy;
    }
    liczbaKlientow--;
    struct Klient *pierwszy=NULL;
    pierwszy=malloc(sizeof(struct Klient));
    fscanf(plik, "%s", pierwszy->imie);
    fscanf(plik, "%s", pierwszy->nazwisko);
    fscanf(plik, "%d", &pierwszy->nrIDklienta);
    fscanf(plik, "%f", &pierwszy->wydane);
    pierwszy->next=NULL;
    int i;
    for(i=0; i<liczbaKlientow; i++){
        struct Klient *el, *tmp=pierwszy;
        el=malloc(sizeof(struct Klient));
        fscanf(plik, "%s", el->imie);
        fscanf(plik, "%s", el->nazwisko);
        fscanf(plik, "%d", &el->nrIDklienta);
        fscanf(plik, "%f", &el->wydane);
        el->next=NULL;
        while(tmp->next){
            tmp=tmp->next;
        }
        tmp->next=el;
    }
    fclose(plik);
    return pierwszy;

}

struct Przedmiot* wczytStdinPrzedmiot(struct Przedmiot *listaPrzedmiotow, char *p){

    int liczbaPrzedmiotow;

    FILE *plik = fopen(p, "r");
    fscanf(plik, "%d", &liczbaPrzedmiotow);
    fclose(plik);
    struct Przedmiot *nowyp;
    nowyp=malloc(sizeof(struct Przedmiot));
    nowyp->next=NULL;
    printf("Wpisz nazwe przedmiotu (zamiast spacji pisz '_'): ");      //wczytywanie przdmiotu
    scanf("%s", nowyp->nazwa);
    printf("Wpisz status przedmiotu (zastaw/nasprzedarz): ") ;
    scanf("%s", nowyp->status);
    printf("Wpisz stan przedmiotu (nowy/uzywany): ");
    scanf("%s", nowyp->stan);
    printf("Podaj kwote pod zastaw: ");
    scanf("%f", &nowyp->kwotaZastaw);
    printf("Podaj wartosc przedmiotu na sprzedaz: ");
    scanf("%f", &nowyp->wartosc);
    printf("Podaj id wlasciciela: ");
    scanf("%d", &nowyp->nrIDklienta);  //można przerobic na wczytywanie nazwiska
    nowyp->nrIDprzedmiotu=liczbaPrzedmiotow+101;
    time_t czas;
    struct tm *data;
    time(&czas);
    data=localtime(&czas);
    nowyp->dzien=data->tm_mday;
    nowyp->miesiac=data->tm_mon+1;
    nowyp->rok=data->tm_year+1900;
    printf("Pomyslnie dodano nowy przedmiot o id:%d\n", nowyp->nrIDprzedmiotu);
    liczbaPrzedmiotow++;
    if(!listaPrzedmiotow){
        zapListPrzedmiotPlik(nowyp, p, liczbaPrzedmiotow);
        return nowyp;
    }

    struct Przedmiot *tmp=listaPrzedmiotow;
    while(tmp->next)
            tmp=tmp->next;
    tmp->next=nowyp;
    zapListPrzedmiotPlik(listaPrzedmiotow, p, liczbaPrzedmiotow);
    return listaPrzedmiotow;

}

struct Klient* wczytStdinKlient(struct Klient *listaKlientow, char *p){

    int liczbaKlientow;
    FILE *plik=fopen(p, "r");
    fscanf(plik, "%d", &liczbaKlientow);
    fclose(plik);

    struct Klient *nowyk;
    nowyk=malloc(sizeof(struct Klient));
    nowyk->next=NULL;

    printf("Podaj imie: ");
    scanf("%s", nowyk->imie);
    printf("Podaj nazwisko: ");
    scanf("%s", nowyk->nazwisko);
    nowyk->nrIDklienta=liczbaKlientow+1;
    printf("Podaj wydana kwote: ");
    scanf("%f", &nowyk->wydane);
    printf("Pomyslnie dodano nowego klienta o numerze id:%d\n", nowyk->nrIDklienta);
    liczbaKlientow++;


    if(!nowyk){
        zapListKlientPlik(nowyk, p, liczbaKlientow);
        return nowyk;
    }
    struct Klient *tmp=listaKlientow;
    while(tmp->next)
            tmp=tmp->next;
    tmp->next=nowyk;
    zapListKlientPlik(listaKlientow, p, liczbaKlientow);
    return listaKlientow;

}



//FILTROWANIE I SORTOWANIE PRZEDMIOTOW

void swapPrzedmiot(struct Przedmiot *tmp, struct Przedmiot *help){


                int i=0;
                char c[30];
                float f=0;

                strcpy(c, tmp->nazwa);
                strcpy(tmp->nazwa, help->nazwa);
                strcpy(help->nazwa, c);
                i=tmp->dzien;
                tmp->dzien=help->dzien;
                help->dzien=i;
                i=tmp->miesiac;
                tmp->miesiac=help->miesiac;
                help->miesiac=i;
                i=tmp->rok;
                tmp->rok=help->rok;
                help->rok=i;
                f=tmp->wartosc;
                tmp->wartosc=help->wartosc;
                help->wartosc=f;
                f=tmp->kwotaZastaw;
                tmp->kwotaZastaw=help->kwotaZastaw;
                help->kwotaZastaw=f;
                strcpy(c, tmp->status);
                strcpy(tmp->status, help->status);
                strcpy(help->status, c);
                strcpy(c, tmp->stan);
                strcpy(tmp->stan, help->stan);
                strcpy(help->stan, c);
                i=tmp->nrIDklienta;
                tmp->nrIDklienta=help->nrIDklienta;
                help->nrIDklienta=i;
                i=tmp->nrIDprzedmiotu;
                tmp->nrIDprzedmiotu=i;

}

void filtrujPoNazwiePrzedioty(struct Przedmiot *listaPrzedmiotow){

    struct Przedmiot *tmp;

    char napis[30];
    printf("Wpisz szukany przedmiot: ");
    scanf("%s", napis);

    for(tmp=listaPrzedmiotow; tmp!=NULL; tmp=tmp->next)
        if(strstr(tmp->nazwa, napis)!=NULL){
            wypiszLiniePrzedmiotow(tmp);
        }


}

void sortujPoNazwiePrzedmioty(struct Przedmiot *listaPrzedmiotow){

    struct Przedmiot *tmp, *help;


    for(tmp=listaPrzedmiotow; tmp!=NULL; tmp=tmp->next)
        for(help=tmp; help!=NULL; help=help->next)
            if(strcmp(tmp->nazwa, help->nazwa)>0){
                swapPrzedmiot(tmp, help);
            }

    wypiszListePrzedmiotow(listaPrzedmiotow);

}

void sortujPoDaciePredmioty(struct Przedmiot *listaPrzedmiotow){

    struct Przedmiot *tmp, *help;


    for(tmp=listaPrzedmiotow; tmp!=NULL; tmp=tmp->next)
        for(help=tmp; help!=NULL; help=help->next){
            if(help->rok>tmp->rok)
                swapPrzedmiot(tmp, help);
            if(help->rok==tmp->rok){
                if(help->miesiac<tmp->miesiac)
                    swapPrzedmiot(tmp, help);
                if(help->miesiac==tmp->miesiac){
                    if(help->dzien<tmp->dzien)
                        swapPrzedmiot(tmp, help);
                }
            }
        }
    wypiszListePrzedmiotow(listaPrzedmiotow);




}

void filtrujPrzedmioty(struct Przedmiot *listaPrzedmiotow){

        int wyb=1, rokmin=0, rokmax=10000;
        float cenamin=0, cenamax=10000;
        char status[10];
        strcpy(status, "zastaw");
        printf("Jakie przedmioty chcesz wyswietlic (wpisz 1 lub 2 lub 3)?\n[1] Zastawione\n[2] Na Sprzedaz\n[3] Sprzedane\n");
        scanf("%d", &wyb);
        if(wyb==1)
            strcpy(status, "zastaw");
        else if(wyb==2)
            strcpy(status, "nasprzedaz");
        else if(wyb==3)
            strcpy(status, "sprzedane");
        else
            return;
        printf("Wybierz przedział cenowy\ncena minimum: ");
        scanf("%f", &cenamin);
        printf("cena maksimum: ");
        scanf("%f", &cenamax);
        printf("Podaj przedzial lat\nrok minimalny: ");
        scanf("%d", &rokmin);
        printf("Podaj rok maksymalny: ");
        scanf("%d", &rokmax);

        struct Przedmiot *tmp=listaPrzedmiotow;
        while(tmp){
            if(strcmp(tmp->status, status)==0 && tmp->wartosc>=cenamin && tmp->wartosc<=cenamax && tmp->rok>=rokmin && tmp->rok<=rokmax){
                wypiszLiniePrzedmiotow(tmp);
            }
            tmp=tmp->next;
        }


}



//FILTROWANIE I SORTOWANIE KLIENTOW

void swapKlient(struct Klient *tmp, struct Klient *help){

    char c[30];
    int i=0;
    float f=0;

    strcpy(c, tmp->imie);
    strcpy(tmp->imie, help->imie);
    strcpy(help->imie, c);
    strcpy(c, tmp->nazwisko);
    strcpy(tmp->nazwisko, help->nazwisko);
    strcpy(help->nazwisko, c);
    i=tmp->nrIDklienta;
    tmp->nrIDklienta=help->nrIDklienta;
    help->nrIDklienta=i;
    f=tmp->wydane;
    tmp->wydane=help->wydane;
    help->wydane=f;

}

void sortowaniePoNazwieKlientow(struct Klient *listaKlientow){

    struct Klient *tmp, *help;


    for(tmp=listaKlientow; tmp!=NULL; tmp=tmp->next)
        for(help=tmp; help!=NULL; help=help->next)
            if(strcmp(tmp->nazwisko, help->nazwisko)>0){
                swapKlient(tmp, help);
            }

    wypiszListeKlientow(listaKlientow);

}

void sortowaniePoWydaneKlientow(struct Klient *listaKlientow){

    struct Klient *tmp, *help;

    for(tmp=listaKlientow; tmp!=NULL; tmp=tmp->next)
        for(help=tmp; help!=NULL; help=help->next)
            if(help->wydane>tmp->wydane)
                swapKlient(tmp, help);
    wypiszListeKlientow(listaKlientow);
}

void filtrowaniePoId(struct Klient *listaKlientow){

    struct Klient *tmp;
    int nrIdkli=0;
    printf("Podaj szykany nr Id\n");
    scanf("%d", &nrIdkli);
    for(tmp=listaKlientow; tmp!=NULL; tmp=tmp->next)
        if(tmp->nrIDklienta==nrIdkli)
            wypiszLinieKlientow(tmp);
}

void filtrowaniePoNazwisku(struct Klient *listaKlientow){

    struct Klient *tmp;
    char napis[30];
    int znaleziono=0;
    printf("Wpisz szukane nazwisko: ");
    scanf("%s", napis);
    for(tmp=listaKlientow; tmp!=NULL; tmp=tmp->next)
        if(strstr(tmp->nazwisko, napis)!=NULL){
            wypiszLinieKlientow(tmp);
            znaleziono=1;
        }
    if(znaleziono==0)
        printf("Nie znaleziono klienta\n");

}

void filtrowaniePoWydane(struct Klient *listaKlientow){

    struct Klient *tmp;
    float min=0, max=1000;
    printf("Wpisz minimalna wydana kwote w lombardzie: ");
    scanf("%f", &min);
    printf("Oraz maksymalna: ");
    scanf("%f", &max);

    for(tmp=listaKlientow; tmp!=NULL; tmp=tmp->next)
        if(tmp->wydane>=min && tmp->wydane<=max)
            wypiszLinieKlientow(tmp);

}

void wypiszPrzedmiotyKlienta(struct Przedmiot *listaPrzedmiotow, struct Klient *listaKlientow){

    struct Przedmiot *tmp;
    struct Klient *k1;
    int stdnrID=0;
    char napis[30];

    printf("Podaj nazwisko klienta: ");
    scanf("%s", napis);
    for(k1=listaKlientow; k1!=NULL; k1=k1->next)
        if(strstr(k1->nazwisko, napis)!=NULL){
            stdnrID=k1->nrIDklienta;
            for(tmp=listaPrzedmiotow; tmp!=NULL; tmp=tmp->next)
                if(tmp->nrIDklienta==stdnrID)
                    wypiszLiniePrzedmiotow(tmp);

        }
    if(stdnrID==0)
        printf("Nie znaleziono klienta\n");


}

//Edit

struct Przedmiot *znajdzPrzedmiot(struct Przedmiot *listaPrzedmiotow){

    struct Przedmiot *tmp;
    int nrIdprzed=0;
    printf("Podaj nazwe przedmiotu: ");
    char nazw[30];
    scanf("%s", nazw);

    for(tmp=listaPrzedmiotow; tmp!=NULL; tmp=tmp->next)
        if(strstr(tmp->nazwa, nazw)!=NULL){
            wypiszLiniePrzedmiotow(tmp);
        }
    printf("Podaj nr Id przedmiotu do edycji (lub 0 jesli nie ma na liscie): ");
    scanf("%d", &nrIdprzed);
    for(tmp=listaPrzedmiotow; tmp!=NULL; tmp=tmp->next)
        if(tmp->nrIDprzedmiotu==nrIdprzed)
            return tmp;

    return NULL;

}

void editPrzedmiot(struct Przedmiot *tmp){

    if(tmp==NULL){
        printf("Nie znaleziono pasujacego przedmioru Przedmiotu");
        return;
    }
    int odp3=1;
    while(odp3!=2){
        printf("Wybierz numer do edycji\n[1]Nazwa\n[2]Status\n[3]Stan\n[4]Kwota zastawu\n[5]Wartosc\n[6]Data wystawienia\n");
        printf("Przedmiot do edycji:\n");
        wypiszLiniePrzedmiotow(tmp);
        int odp=1, odp1=1;
        scanf("%d", &odp);


        if(odp==1){
            printf("Wpisz nazwe przedmiotu (zamiast spacji pisz '_'): ");
            scanf("%s", tmp->nazwa);
        }
        else if(odp==2){
            printf("Wpisz status przedmiotu (zastaw/nasprzedarz/sprzedany): ") ;
            scanf("%s", tmp->status);
        }
        else if(odp==3){
            printf("Wpisz stan przedmiotu (nowy/uzywany): ");
            scanf("%s", tmp->stan);
        }
        else if(odp==4){
            printf("Podaj kwote pod zastaw: ");
            scanf("%f", &tmp->kwotaZastaw);
        }
        else if(odp==5){
            printf("Podaj wartosc przedmiotu na sprzedaz: ");
        scanf("%f", &tmp->wartosc);
        }
        else if(odp==6){
            printf("Czy chcesz zmienic date na dzisiejsza?/n[1]TAK/[2]NIE\n");
            scanf("%d", &odp1);
            if(odp1==1){
                time_t czas;
                struct tm *data;
                time(&czas);
                data=localtime(&czas);
                tmp->dzien=data->tm_mday;
                tmp->miesiac=data->tm_mon+1;
                tmp->rok=data->tm_year+1900;
            }
            else if(odp1==2){
                printf("Podaj dzien: ");
                scanf("%d", &tmp->dzien);
                printf("Podaj misiac: ");
                scanf("%d", &tmp->miesiac);
                printf("Podaj rok: ");
                scanf("%d", &tmp->rok);
            }

        }
        wypiszLiniePrzedmiotow(tmp);
        printf("Czy chcesz edytowac ponownie?\n[1]TAK\n[2]NIE\n");

        scanf("%d", &odp3);
    }



}

struct Klient *znajdzKlient(struct Klient *listaKlientow){

    struct Klient *tmp=listaKlientow;
    printf("Wpisz nazwisko klienta do edycji: ");
    char nazw[30];
    scanf("%s", nazw);
    for(tmp=listaKlientow; tmp!=NULL; tmp=tmp->next)
        if(strstr(tmp->nazwisko, nazw)!=NULL)
            wypiszLinieKlientow(tmp);
    printf("Podaj nr ID klienta do edycji (lub 0 jesli nie ma na liscie): ");
    int nrId=0;
    scanf("%d", &nrId);
    for(tmp=listaKlientow; tmp!=NULL; tmp=tmp->next)
        if(tmp->nrIDklienta==nrId)
            return tmp;
    return NULL;
}

void editKlient(struct Klient *tmp){

    if(tmp==NULL){
        printf("Nie znaleziono właściwego klienta");
        return;
    }
    int odp1=1, odp2=1;
    while(odp2!=2){
        printf("Podaj numer do edycji\n[1]Imie\n[2]Nazwisko\n[3]Wydane\n");
        wypiszLinieKlientow(tmp);
        scanf("%d", &odp1);
        if(odp1==1){
            printf("Wpisz nazwisko klienta: ");
            scanf("%s", tmp->nazwisko);
        }
        else if(odp1==2){
            printf("Wpisz imie klienta: ");
            scanf("%s", tmp->imie);
        }
        else if(odp1==3){
            printf("Wpisz wydane w lombardzie: ");
            scanf("%f", &tmp->wydane);
        }
        wypiszLinieKlientow(tmp);
        printf("Czy chcesz edytowac ponownie?\n[1]TAK\n[2]NIE\n");
        scanf("%d", &odp2);
    }

}

//delete

struct Przedmiot *delPrzed(struct Przedmiot *listaPrzedmiotow, char *p){

    struct Przedmiot *dowywalenia, *tmp=listaPrzedmiotow;
    dowywalenia=znajdzPrzedmiot(listaPrzedmiotow);
    int odp=0;
    if(dowywalenia==NULL)
        return listaPrzedmiotow;
    if(strcmp(dowywalenia->status, "zastaw")==0){
            printf("Czy na pewno chcesz usunac zastawiony przedmiot?\n[1]TAK\n[2]NIE\n");
            scanf("%d", &odp);
            if(odp==2)
                return listaPrzedmiotow;
       }
    else if(strcmp(dowywalenia->status, "sprzedane")==0){
        printf("Nie mozna usunac przedmiotu, poniewaz klient nrID:%d ktory go kupil", tmp->nrIDklienta);
        return listaPrzedmiotow;
    }
    if(dowywalenia==NULL)
        return listaPrzedmiotow;
    int liczbaPrzedmiotow=0;
    FILE *plik=fopen(p, "r");
    fscanf(plik, "%d", &liczbaPrzedmiotow);
    fclose(plik);
    liczbaPrzedmiotow--;
    if(tmp==dowywalenia){
        zapListPrzedmiotPlik(tmp->next, p, liczbaPrzedmiotow);
        return tmp->next;
    }
    while(tmp->next!=dowywalenia)
        tmp=tmp->next;
    tmp->next=dowywalenia->next;
    zapListPrzedmiotPlik(listaPrzedmiotow, p, liczbaPrzedmiotow);
    return listaPrzedmiotow;
}

struct Klient *delKlient(struct Klient *listaKlientow, char *p){

    struct Klient *dowywalenia, *tmp=listaKlientow;
    dowywalenia=znajdzKlient(listaKlientow);

    if(dowywalenia==NULL)
        return listaKlientow;
    int liczbaKlientow=0;
    FILE *plik=fopen(p, "r");
    fscanf(plik, "%d", &liczbaKlientow);
    fclose(plik);
    liczbaKlientow--;
    if(tmp==dowywalenia){
        zapListKlientPlik(tmp->next, p, liczbaKlientow);
        return tmp->next;
    }
    while(tmp->next!=dowywalenia)
        tmp=tmp->next;
    tmp->next=dowywalenia->next;
    return listaKlientow;
}

//INTERFEJS
void wybierzdzialanie(struct Klient *listaKlientow, struct Przedmiot *listaPrzedmiotow, char *pklient, char *plikprzed){

    int odp1=1, odp2=1, odp3=1;

    printf("home\n***LOMBARD***\n[1]Klienci\n[2]Przedmioty\n\n[0]Exit\n");
    scanf("%d", &odp1);
    while(odp1){
                if(odp1==1){
                printf("home->klienci\n[1]Dodaj\n[2]Usun\n[3]Edytuj\n[4]Sortuj\n[5]Filtruj\n[6]Wypisz przedmioty klienta\n\n[0]Wstecz\n");
                scanf("%d", &odp2);
                while(odp2){
                    if(odp2==1){
                        listaKlientow=wczytStdinKlient(listaKlientow, pklient);
                    }
                    else if(odp2==2){
                        delKlient(listaKlientow, pklient);
                    }
                    else if(odp2==3){
                        editKlient(znajdzKlient(listaKlientow));
                    }
                    else if(odp2==4){
                        printf("home->klienci->sortuj\nWybierz filtr sortowania listy klientow\n[1]Alfabetycznie nazwiska\n[2]Malejaco wg. wydanych pieniedzy\n\n[0]Wstecz\n");
                        scanf("%d", &odp3);
                        if(odp3==1){
                            sortowaniePoNazwieKlientow(listaKlientow);
                        }
                        else if(odp3==2){
                            sortowaniePoWydaneKlientow(listaKlientow);
                        }
                    }
                    else if(odp2==5){

                        printf("home->klienci->filtruj\nZnajdz klienta/klientow po:\n[1]Nazwisku\n[2]Ilosci wydanych pieniedzy\n[3]Numerze ID\n\n[0]Wstecz\n");
                        scanf("%d", &odp3);
                        while(odp3){
                            if(odp3==1){
                                filtrowaniePoNazwisku(listaKlientow);
                            }
                            else if(odp3==2){
                                filtrowaniePoWydane(listaKlientow);
                            }
                            else if(odp3==3){
                                filtrowaniePoId(listaKlientow);
                            }
                            printf("home->klienci->filtruj\nZnajdz klienta/klientow po:\n[1]Nazwisku\n[2]Ilosci wydanych pieniedzy\n[3]Numerze ID\n\n[0]Wstecz\n");
                            scanf("%d", &odp3);
                        }

                    }
                    else if(odp2==6){
                        wypiszPrzedmiotyKlienta(listaPrzedmiotow, listaKlientow);
                    }
                    printf("home->klienci\n[1]Dodaj\n[2]Usun\n[3]Edytuj\n[4]Sortuj\n[5]Filtruj/Wyszukaj\n[6]Wypisz przedmioty klienta\n\n[0]Wstecz\n");
                    scanf("%d", &odp2);
                }

            }
            else if(odp1==2){
                printf("home->przedmioty\n[1]Dodaj\n[2]Usun\n[3]Edytuj\n[4]Sortuj\n[5]Filtruj\n\n[0]Wstecz\n");
                scanf("%d", &odp2);
                while(odp2){
                    if(odp2==1){
                        wczytStdinPrzedmiot(listaPrzedmiotow, plikprzed);
                    }
                    else if(odp2==2){
                        delPrzed(listaPrzedmiotow, plikprzed);
                    }
                    else if(odp2==3){
                        editPrzedmiot(znajdzPrzedmiot(listaPrzedmiotow));
                    }
                    else if(odp2==4){
                        printf("Posortuj listę przedmiotow wg.:\n[1]Nazwy\n[2]Daty\n\n[0]Wstecz\n");
                        scanf("%d", &odp2);
                        if(odp3==1){
                            sortujPoNazwiePrzedmioty(listaPrzedmiotow);
                        }
                        else if(odp3==2){
                            sortujPoDaciePredmioty(listaPrzedmiotow);
                        }
                    }
                    else if(odp2==5){
                            printf("Filtruj przedmioty po:\n[1]Nazwie\n[2]Cenie/Statusie/Dacie\n\n[0]Wstecz\n");
                            scanf("%d", &odp3);
                            while(odp3){
                                if(odp3==1){
                                    filtrujPoNazwiePrzedioty(listaPrzedmiotow);
                                }
                                else if(odp3==2){
                                    filtrujPrzedmioty(listaPrzedmiotow);
                                }
                                printf("Filtruj przedmioty po:\n[1]Nazwie\n[2]Cenie/Statusie/Dacie\n\n[0]Wstecz\n");
                                scanf("%d", &odp3);
                            }

                    }
                printf("home->przedmioty\n[1]Dodaj\n[2]Usun\n[3]Edytuj\n[4]Sortuj\n[5]Filtruj\n\n[0]Wstecz\n");
                scanf("%d", &odp2);
                }
            }

        printf("home\n***LOMBARD***\n[1]Klienci\n[2]Przedmioty\n\n[0]Exit\n");
        scanf("%d", &odp1);
    }
}


int main()
{

    char nazwaPlikuPrzedmioty[] = { "przedmioty.txt" };
    char nazwaPlikuKlienci[] = { "klienci.txt" };
    struct Przedmiot *listaPrzedmiotow;
    listaPrzedmiotow=wczytPlikPrzedmiot(nazwaPlikuPrzedmioty);
    struct Klient *listaKlientow;
    listaKlientow=wczytPlikKlient(nazwaPlikuKlienci);

    wybierzdzialanie(listaKlientow, listaPrzedmiotow, nazwaPlikuKlienci, nazwaPlikuPrzedmioty);

    return 0;
}
