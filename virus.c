#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#define people 99
//#define time_period 1                            //Zeitraum, in dem uns die Interaktionen interessieren (in Tagen)
//#define num_pers 100                             //Anzahl an Leute, die generiert werden soll
//#define num_interact 500                         //Anzahl an Interaktionen insgesamt


//header
//------------------------------------------------------------------------
/*
-> zählt Zeilenanzahl einer Datei
-> parameter:   - Verlauf der Datei
-> return: Zeilenanzahl
*/
int count_lines(FILE * input);
//------------------------------------------------------------------------

//------------------------------------------------------------------------
/*
-> liest Namen der Textdatei ein, soll dann jeder Person eine ID geben
-> output: Person-ID | Name
-> parameter:
                - Verlauf der input-Textdatei
                - Verlauf der output-Textdatei (mit der ID)
                - Anzahl an Personen, die generiert werden sollen
-> return: erfolgreich = 0, Fehler beim input = -1, Fehler beim output = -2
*/
int id_name(char * input, char * output, int n);
//------------------------------------------------------------------------

//------------------------------------------------------------------------
/*liest Personen der Textdatei ein (Name + ID), generiert dann Interaktionen
-> output: Interaktions-ID | Person1-ID | Person2-ID | Zeitfenster
-> parameter:
                - Verlauf der input-Textdatei
                - Verlauf der output-Textdatei
                - Anzahl an Personen (= der generierten Personen aus der vorherigen Funktion)
                - Anzahl an Interaktionen insgesamt
                - Anzahl an Tagen (Zeitraum, in dem die Interaktionen stattfinden sollen)
-> return: erfolgreich = 0, Fehler beim output = -1
*/
int interactions(char * output, int n, int max_i, int t);
//------------------------------------------------------------------------

//------------------------------------------------------------------------
/*
-> Name wird übergeben
-> gibt ID zurück
-> -1 falls Datei nicht geöffnet werden kann
-> -2 falls Name nicht gefunden wird
*/
int search_id(char * input, char search_name[]);
//------------------------------------------------------------------------

//------------------------------------------------------------------------
/*
-> ID wird übergeben
-> gibt Namen (Pointer) zurück
*/
char *search_name(char * input, int search_id);


int dijkstra_algo(int PPL, int contact[PPL][PPL], int patient_null);

void graphviz(int node_count, char * input_weg);

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
    node_count = dijkstra_algo(people, infect, name_id);

    printf("Graphviz-Code wird ausgegeben...\n\n");
    printf("--------------------Graphviz-Code--------------------\n");
    graphviz(node_count,"infektionsweg.csv");
    printf("--------------------Graphviz-Code--------------------\n");
    printf("Graphviz-Code kann auf 'https://dreampuf.github.io/GraphvizOnline' eingegeben werden.\n");
    return 0;
}

int count_lines(FILE * input)
{
    int lines = 0;
    char c = getc(input);
    while( c != EOF)
    {
        if(c == '\n')
        {
            lines++;        //zählt bis zum Ende des Dokuments jeden Zeilenumbruch
        }
    c = getc(input);
    }
    return lines;
}

int id_name(char * input, char * output, int n)
{
    srand(time(NULL));
    char c;

    //Dateien öffnen/erstellen
    FILE *input_file=fopen(input, "r");
    if (input_file == NULL)
    {
        printf("%s konnte nicht geoeffnet werden.",input_file);
        return -1;
    }

    FILE *output_file=fopen(output, "w");
    if (output_file == NULL)
    {
        printf("%s konnte nicht geoeffnet werden.",output_file);
        return -2;
    }

    int names = count_lines(input_file);
    rewind(input_file);

    //ID's generieren
    for(int i = 0; i<n; i++)
    {
        int line = rand()%names;
        rewind(input_file);
        char name[20] = "";

        fprintf(output_file,"%d | ",i+1); //ID

        //Namen kopieren
        for(int j = 0; j<line; j++) //springt zur Zeile
        {
            while ((c=fgetc(input_file)) != '\n');
        }

        fscanf(input_file," %s", name);
        fprintf(output_file,"%s ",name);
        fprintf(output_file,"\n");
    }

    //Dateien wieder schließen
    fclose(input_file);
    fclose(output_file);

    return 0;
}


int interactions(char * output, int n, int max_i, int t)
{
    srand(time(NULL));
    //char c;
    int max_time = (t*1440); //1440 Minuten = 1 Tag

    //Datei erstellen
    FILE *output_file=fopen(output, "w");
    if (output_file == NULL)
    {
        printf("%s konnte nicht geoeffnet werden.",output_file);
        return -1;
    }

    //ID's generieren
    int j = 0;
    int k = 0;
    int l = 0;
    for(int i = 0; i<max_i; i++)
    {
        fprintf(output_file,"%d | ",i+1); //Interaktions-ID
        j = rand() % n + 1;
        fprintf(output_file,"%d | ",j); //Person 1 ID
        do
        {
            k = rand() % n + 1;
        } while(k==j);
        fprintf(output_file,"%d | ",k); //Person 2 ID

        l = rand() % max_time + 1; //Minutenanzahl

        fprintf(output_file,"%d",l);
        fprintf(output_file,"\n");
    }

    //Datei wieder schließen
    fclose(output_file);

    return 0;
}

int search_id(char * input, char search_name[])
{
    FILE *input_file=fopen(input, "r");
    if (input_file == NULL)
    {
        printf("%s konnte nicht geoeffnet werden.",input_file);
        return -1;
    }
    //int id = 0;
    //fpos_t position;
    //fgetpos(input_file, &position); //Anfangsposition wird gespeichert
    int lines = count_lines(input_file); //Zeilenanzahl wird gespeichert
    rewind(input_file);

    int *id_array;
    char **name_array;

    id_array = malloc(lines*sizeof(int));
    name_array = malloc(sizeof(char*)*lines);
    for(int k = 0; k<lines;k++)
    {
        name_array[k] = malloc(20*sizeof(char));
    }

    int i = 0;
    //int j = 0;
    char string[20];
    //while(j != lines)
    //{
        //fsetpos(input_file, &position);
        while(fscanf(input_file,"%d | %s\n",&id_array[i], string)!=EOF) //speichert jede Spalte in ein eigenes array
        {
            strcpy(name_array[i],string);
            //printf("%s - %s",name_array[i],string);
            i++;
        }
        //fgetpos(input_file, &position);
        //j++;
    //}
    int z;

        for(i=0;i<lines;i++)
        {
            z=strcmp(search_name,name_array[i]);
            if(z==0)
            {
                break;
            }
        }
        if(z!=0)
        {
            i=-2;
        }

    /*for(i=0; i < lines; i++)
      printf("name[%d] = %s\n", i+1, name_array[i]);*/

    fclose(input_file);
    return (i+1);
}

char *search_name(char * input, int search_id)
{
    FILE *input_file=fopen(input, "r");
    if (input_file == NULL)
    {
        printf("%s konnte nicht geoeffnet werden.",input_file);
        exit(-1);
        //return -1;
    }
    //char name[20];
    fpos_t position;
    fgetpos(input_file, &position); //Anfangsposition wird gespeichert
    int lines = count_lines(input_file); //Zeilenanzahl wird gespeichert
    rewind(input_file);

    int *id_array;
    char **name_array;

    id_array = malloc(lines*sizeof(int));
    name_array = malloc(sizeof(char*)*lines);
    for(int k = 0; k<lines;k++)
    {
        name_array[k] = malloc(20*sizeof(char));
    }

    int i = 0;
    int j = 0;
    char string[20];
    while(j != lines)
    {
        fsetpos(input_file, &position);
        while(fscanf(input_file,"%d | %s\n",&id_array[i], string)!=EOF) //speichert jede Spalte in ein eigenes array
        {
            strcpy(name_array[i],string);
            i++;
        }
        fgetpos(input_file, &position);
        j++;
    }
    int z;

        for(i=0;i<lines;i++)
        {
            if(search_id == id_array[i])
            {
                z = 0;
                fclose(input_file);
                char *return_string = malloc(20);
                strcpy(return_string,name_array[i]);
                return return_string;
            }
        }
        if(z!=0)
        {
            fclose(input_file);
            printf("FEHLER. ID wurde nicht gefunden.");
            exit(-2);
            //return -2;
        }

    /*for(i=0; i < lines; i++)
      printf("name[%d] = %s\n", i+1, name_array[i]);*/

}

int dijkstra_algo(int PPL, int contact[PPL][PPL], int patient_null)
{
    int contmin[PPL][PPL]; //Kontaktminute zwischen zwei Personen
    int mintime[PPL];      //die Minuten an Zeit bei Kontakt
    int visited[PPL];      //welche Nodes schon besucht wurden
    int i;
    int j;
    int v;
    //hier kommen die Deklarierungen fuer die Werte der Matrix
    int conID;
    int pers_a;
    int pers_b;
    int min;



    for(i=0; i<PPL; i++)    //erstmal beide Matrizen mit 0 initialisieren
    {
        for(j=0; j<PPL; j++)
        {
            contact[i][j]=0;
            contmin[i][j] = contact[i][j];
        }
    }
    FILE* interaction;
    interaction = fopen("interactions.csv","r");
    if(interaction == NULL)
    {
        printf("Datei nicht gefunden!");
        return -1;
    }

    FILE *output_file=fopen("infektionsweg.csv", "w");
    if (output_file == NULL)
    {
        printf("%s konnte nicht geoeffnet werden.",output_file);
        return -2;
    }

    while(fscanf(interaction,"%d | %d | %d | %d", &conID, &pers_a, &pers_b, &min)!=EOF)
    {
        contmin[pers_a][pers_b]=min;
        contmin[pers_b][pers_a]=contmin[pers_a][pers_b];
    }

    contact = contmin;

    fclose(interaction);
    for(i=0; i<=PPL; i++)
    {

        mintime[i]=0;
        visited[i]=0;
    }
    int counter = 0;

    for(j=1; j<=PPL; j++)
    {
        counter++;
        for(i=1; i<PPL; i++) //alle nicht besuchte nodes sind auf 0 initialisiert visited[]=0
        {
            mintime[i]=mintime[i-1];
            if(mintime[i]<contmin[patient_null][i] && visited[i]==0)
            {
                v=i;
                mintime[i]=contmin[patient_null][v];

            }
            visited[v]=1;
        }

            //printf("Die Uebertragung der Krankheit ueber den Personen findet wie folgt statt: %d -> %d\n",patient_null, v);
            //printf("Sie hatten %d Minuten miteinander Kontakt.\n", mintime[v]);
            fprintf(output_file,"%d | %d | %d\n",patient_null, v,mintime[v]);

        visited[patient_null]=1;
        visited[v]=1;
        patient_null = v;


        if(mintime[v]==0)
        {
            break;
        }

    }
    printf("Letzte moeglich infizierte Personen-ID: %d\n", v);
    fclose(output_file);
    //printf("%d", counter);
    return counter;
}

void graphviz(int node_count, char * input_weg)
{
    /*FILE *file_ID=fopen(input_ID, "r");
    if (file_ID == NULL)
    {
        printf("%s konnte nicht geoeffnet werden.",input_ID);
        exit(-1);
    }*/

    FILE *file_weg=fopen(input_weg, "r");
    if (file_weg == NULL)
    {
        printf("%s konnte nicht geoeffnet werden.",input_weg);
        exit(-1);
    }

    //printf("\n\nTEST %d\n\n",node_count);

    int i = 0;
    int j = 0;
    int *id_1, *id_2, *time;
    id_1 = malloc(node_count*sizeof(int));
    id_2 = malloc(node_count*sizeof(int));
    time = malloc(node_count*sizeof(int));

        while(fscanf(file_weg,"%d | %d | %d\n",&id_1[i], &id_2[i], &time[i])!=EOF) //speichert jede Spalte in ein eigenes array
        {
            i++;
        }



    printf("digraph Virus\n{\n");
    printf("   subgraph cluster_1\n{\n");
    printf("     node [style=filled];\n     ");
    for(i = 0; i<node_count-1; i++)
    {
        printf("%s, ", search_name("id_name.csv",id_1[i]));
    }
    printf(" %s;\n", search_name("id_name.csv",id_2[node_count-1]));
    printf("   }\n");

    printf("   start -> %s;\n", search_name("id_name.csv",id_1[0]));

    for(i = 0; i<node_count-1; i++)
    {
        printf("   %s -> %s [label=\"%d\"]\n",search_name("id_name.csv",id_1[i]),search_name("id_name.csv",id_2[i]),time[i]);
    }
    printf("   %s -> end;\n\n", search_name("id_name.csv",id_2[node_count-1]));

    printf("   start [shape=Mdiamond];\n");
    printf("   end [shape=Msquare];\n");
    printf("}\n\n");
}

