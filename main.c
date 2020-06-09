#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "testdaten.h"
#define time_period 1                            //Zeitraum, in dem uns die Interaktionen interessieren (in Tagen)
#define num_pers 100                             //Anzahl an Leute, die generiert werden soll
#define num_interact 500                         //Anzahl an Interaktionen insgesamt



int main()
{
    printf("--------------------Virus-Tracker--------------------\n");
    printf("Wie viele Personen sollen generiert werden?\n");
    printf("Personenanzahl (< 1754): ");
    int persons = 0;
    do{
        scanf("%d",&persons);
    }while(persons < 1 || persons > 1753);
    int return_id = id_name("names.csv","id_name.csv",persons);
    if(return_id!=0)
    {
        printf("\nFEHLER. Programm wird beendet.");
        return 0;
    }

    return 0;
}