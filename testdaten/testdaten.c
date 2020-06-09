#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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
        printf("%s konnte nicht geöffnet werden.",input_file);
        return -1;
    }

    FILE *output_file=fopen(output, "w");
    if (output_file == NULL)
    {
        printf("%s konnte nicht geöffnet werden.",output_file);
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
    char c;
    int max_time = (t*1440); //1440 Minuten = 1 Tag

    //Datei erstellen
    FILE *output_file=fopen(output, "w");
    if (output_file == NULL)
    {
        printf("%s konnte nicht geöffnet werden.",output_file);
        return -1;
    }

    //ID's generieren
    int j = 0;
    int k = 0;
    int l = 0;
    for(int i = 0; i<max_i; i++)
    {
        fprintf(output_file,"%d | ",i+1); //Interkations-ID
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
        printf("%s konnte nicht geöffnet werden.",input_file);
        return -1;
    }
    int id = 0;
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
    //do
    //{
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
    return i;
    return 0;
}

int interactions_array(char * input)
{
    FILE *input_file=fopen(input, "r");
    if (input_file == NULL)
    {
        printf("%s konnte nicht geöffnet werden.",input_file);
        return -1;
    }
    fpos_t position;
    fgetpos(input_file, &position);
    int lines = count_lines(input_file);
    rewind(input_file);
    int *i_id, *id_1, *id_2, *time;
    i_id = malloc(lines*sizeof(int));
    id_1 = malloc(lines*sizeof(int));
    id_2 = malloc(lines*sizeof(int));
    time = malloc(lines*sizeof(int));
    int i = 0, j = 0;
    while(j != lines)
    {
        fsetpos(input_file, &position);
        while(fscanf(input_file,"%d | %d | %d | %d\n",&i_id[i], &id_1[i], &id_2[i], &time[i])!=EOF) //speichert jede Spalte in ein eigenes array
        {
            i++;
        }
        fgetpos(input_file, &position);
        j++;
    }

    //for(i=0; i < lines; i++)
      //printf("time[%d] = %d\n", i+1, time[i]);

    fclose(input_file);
    return 0;
}
