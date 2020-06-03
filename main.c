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
    /*
    id_name("C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\names.csv",
              "C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\test_id.csv",num_pers);
    */

    //TEST: interactions
    //interactions("C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\library\\interactions.csv", num_pers, num_interact,time_period);
 
    //TEST: search_id
    char name[] = "Adele";
    int test = 0;
    test = search_id("C:\\Users\\inesp\\OneDrive\\FH\\BMR2\\PAD\\PROJEKT\\Testdatenerstellung\\test_id.csv", name);
    printf("%d",test);

    return 0;
}