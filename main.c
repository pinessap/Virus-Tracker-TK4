#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "testdaten.h"
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
    /*id_name("C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\names.csv",
              "C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\test_id.csv",10);
    */

    //TEST: interactions
    interactions("C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\interactions.csv", num_pers, num_interact,time_period);

    //TEST: search_id
    /*char name[] = "Adele";
    int test = 0;
    test = search_id("C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\test_id.csv", name);
    printf("%d",test);*/

    //interactions_array("C:\\Users\\inesp\\Desktop\\interactions.csv");
    /*char * input = "C:\\Users\\inesp\\Desktop\\interactions.csv";
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

    struct node* head = NULL;
    char name[] = "Adele";
    add_back(head,name,10,i_id,id_1,id_2,time);

    fclose(input_file);*/

    return 0;
}