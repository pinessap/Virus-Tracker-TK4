#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define time_period 14                          //Zeitraum, in dem uns die Interaktionen interessieren (14 Tage Inkubationszeit)
#define num_pers 10                             //Anzahl an Leute, die generiert werden soll
#define num_interact 10                         //Anzahl an Interaktionen insgesamt


int main()
{
    printf("Hello world!\n");
    //TEST: count_lines
    /*
    char *filename = "C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\testfile.txt";
    FILE *testfile=fopen(filename, "r");
    if (NULL == testfile)
    {
        printf("could not open %s",testfile);
        exit(-1);
    }
    int n = count_lines(testfile);
    printf("Anzahl an Zeilen: %d",n);
    fclose(testfile);
    */

    //TEST: id_name
    /*
    id_name("C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\names.csv",
              "C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\test_id.csv",10);
    */

    //TEST: interactions
    interactions("C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\interactions.csv", 10, num_interact);
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

    //ID's generieren
    for(int i = 0; i<n; i++)
    {
        fprintf(output_file,"%d | ",i+1);
        //Namen kopieren
        while ((c=fgetc(input_file)) != '\n')
        {
            fputc(c,output_file);
        }
        fprintf(output_file,"\n");
    }

    //Dateien wieder schließen
    fclose(input_file);
    fclose(output_file);

    return 0;
}

int interactions(char * output, int n, int max_i)
{
    srand(time(NULL));
    char c;
    int max_time = (time_period*1440); //1440 Minuten = 1 Tag

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
        do
        {
            l = rand() % max_time + 1;
        } while(k==j);
        fprintf(output_file,"%d",l);
        fprintf(output_file,"\n");
    }
    
    //Datei wieder schließen
    fclose(output_file);

    return 0;
}
