#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "testdaten.h"
#include "dijkstra.h"
#include "graphviz.h"
#define people 99
//#define time_period 1                            //Zeitraum, in dem uns die Interaktionen interessieren (in Tagen)
//#define num_pers 100                             //Anzahl an Leute, die generiert werden soll
//#define num_interact 500                         //Anzahl an Interaktionen insgesamt



int main()
{
     printf("--------------------Virus-Tracker--------------------\n\n");

    printf("Wie viele Personen sollen generiert werden?\n");
    printf("Personenanzahl (< 100): ");
    int persons = 0;
    do
    {
        scanf("%d",&persons);
    }while(persons < 1 || persons > 99);
    int return_id = id_name("names.csv","id_name.csv",persons);
    if(return_id!=0)
    {
        printf("\nFEHLER. Programm wird beendet.");
        return 0;
    }

    printf("Wie viele Interaktionen sollen generiert werden?\n");
    printf("Anzahl an Interaktionen: ");
    int ints = 0;
    do
    {
        scanf("%d",&ints);
    }while(ints<=0);

    printf("Welcher Zeitraum soll betrachet werden?\n");
    printf("Anzahl an Tagen: ");
    int days = 0;
    do
    {
        scanf("%d",&days);
    }while(days <= 0);
    interactions("interactions.csv",persons, ints, days);

    printf("Geben Sie den Namen der Infizierten Person ein.\n");
    printf("Personen koennen in der 'id_name.csv' Datei nachgeschaut werden.\n");
    printf("(Bitte Datei danach wieder schliessen.)\n");
    printf("Name: ");
    char name[20];
    int name_id = 0;
    do
    {
        scanf(" %s",name);
        name_id = search_id("id_name.csv",name);
    }while(name_id<=0);

    //printf("TEST NAME ID %d",name_id);


    printf("\nPersonen mit den laengsten Interaktionen werden ermittelt...\n");
    int infect[people][people];
    int node_count = 0;
    node_count = dijkstra_algo(people,infect, name_id);

    printf("Graphviz-Code wird ausgegeben...\n\n");
    printf("--------------------Graphviz-Code--------------------\n");
    graphviz(node_count,"infektionsweg.csv");
    printf("--------------------Graphviz-Code--------------------\n");
    printf("Graphviz-Code kann auf 'https://dreampuf.github.io/GraphvizOnline' eingegeben werden.\n");
    return 0;
}
