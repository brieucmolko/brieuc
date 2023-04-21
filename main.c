#include <stdio.h>
#include <allegro.h>
#include <time.h>
#include <stdlib.h>

// SECTION A : CONSTANTES #define
#define NFOURMI 100;
#define TX 10;
#define TY 20;
#define lol;

// SECTION B : DEFINITIONS DES STRUCTURES
typedef struct fourmie{
    int posx,posy;
    int depx,depy;
}t_f;

// SECTION C : PROTOTYPES DES SOS-PROGRAMMES
/*void tempo(int millisec)
{
    clock_t  t0,t;
    t0=clock();
    do
    {
        t=clock();
    }while((t-t0)<millisec);
}*/

void aleaDepFourmi(t_f* fourmie)
{
    do {
        fourmie->depx=(rand()%5)-2;
        fourmie->depy=(rand()%5)-2;
    }while((fourmie->depx == 0) && (fourmie->depy == 0));
}

t_f* creer_fourmie()
{
    t_f* fourmie;
    fourmie = (t_f*) malloc(sizeof(t_f));
    fourmie->posx=rand()%790;
    fourmie->posy=rand()%580;
    fourmie->depx=0;
    fourmie->depy=0;
    return (fourmie);
}

void actualiserFourmi(t_f* fourmie)
{
    fourmie->posx+=fourmie->depx;
    fourmie->posy+=fourmie->depy;
    if(fourmie->posx >790)
    {
        fourmie->posx=790;
        fourmie->depx= -fourmie->depx;
    }
    if(fourmie->posy >580)
    {
        fourmie->posy=580;
        fourmie->depy= -fourmie->depy;
    }
    if(fourmie->posx <0)
    {
        fourmie->posx=0;
        fourmie->depx= -fourmie->depx;
    }
    if(fourmie->posy <0)
    {
        fourmie->posy=0;
        fourmie->depy= -fourmie->depy;
    }
}
void  dessinerFourmi(BITMAP* buffer, t_f*fourmie , int a , int b , int c)
{
    rectfill(buffer,fourmie->posx,fourmie->posy,(fourmie->posx)+10,(fourmie->posy)+20,makecol(a,b,c));
}
void remplirTabFourmis(t_f** tabfourmie)
{
    int i;
    for(i=0;i<100;i++)
    {
        tabfourmie[i]=creer_fourmie();
        aleaDepFourmi(tabfourmie[i]);
    }
}
int collision_fourmi(t_f* tabfourmie1,t_f* tabfourmie2)
{
    if((abs(tabfourmie2->posx-tabfourmie1->posx) <= 10) && (abs(tabfourmie2->posy-tabfourmie1->posy) <= 20) && (tabfourmie2 != tabfourmie1))
    {
        return  1;
    }
    else
    {
        return 0;
    }
}

void actualiserTabFourmis(t_f** tabfourmie)
{   int i,j;

    for(i=0;i<100;i++)
    {
        actualiserFourmi(tabfourmie[i]);
        for(j=0;j<100;j++)
        {
            if(collision_fourmi(tabfourmie[j],tabfourmie[i]))
            {
                aleaDepFourmi(tabfourmie[i]);
                actualiserFourmi(tabfourmie[i]);
                aleaDepFourmi(tabfourmie[j]);
                actualiserFourmi(tabfourmie[j]);

            }
        }
    }
}
void dessinertabfourmie(BITMAP* buffer, t_f** tabfourmie, int a , int b , int c)
{
    int i;
    for(i=0;i<100;i++)
    {
        dessinerFourmi(buffer, tabfourmie[i],a,b,c);
    }
}
// Programme principal
int main()
{
    
    t_f* fourmie;
    int i;
    t_f* tabfourmie[100];
    srand(time(NULL));
    remplirTabFourmis(&tabfourmie);

    // SECTION D : DECLARATIONS DES VARIABLES DU MAIN


    // SECTION E : INITIALISATION ALLEGRO
    allegro_init();
    install_keyboard();
    install_mouse();
    srand(time(NULL));
    // SECTION F : OUVERTURE MODE GRAPHIQUE
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        allegro_message("probleme mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);
    rectfill(buffer, 0, 0, 800, 600, makecol(255,255,255));
    show_mouse(buffer);//Visualisation de la souris
    //Bouton gauche
    int fin = 0;
    int mx=400,my=300;
    int mx2,my2,j;


    while(!fin) {

        dessinertabfourmie(buffer, &tabfourmie[0],255,255,255);
        actualiserTabFourmis(&tabfourmie[0]);
        dessinertabfourmie(buffer, &tabfourmie[0],255,0,0);
        rest(5);
        if (mouse_b & 1) {
            printf("Le bouton gauche est appuye\n");
            while(mouse_b & 1) {
                mx2= mouse_x;
                my2= mouse_y;
                line(buffer, mx, my,mx2 , my2, makecol(rand()%255, rand()%255, rand()%255));
            }
        }
        //Bouton droit
        if (mouse_b & 2) {
            printf("Le bouton droit est appuye\n");
            mx=mouse_x;
            my=mouse_y;
            printf("%d  %d",mx, my);
        }
        blit(buffer,screen,0,0,0,0, SCREEN_W,SCREEN_H);
        if(key[KEY_SPACE])
        {
            clear_to_color(buffer, makecol(255,255,255));
        }
    }


    readkey();
    // SECTION G : AVANT BOUCLE JEU

    // SECTION H : BOUCLE JEU
    // SECTION I : TERMINER LE PROGRAMME

    return 0;
} END_OF_MAIN();

// SECTION J : DEFINITIONS DES SOUS-PROGRAMMES
