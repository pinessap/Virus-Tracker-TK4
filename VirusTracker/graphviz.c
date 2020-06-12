#include <stdio.h>
#include <stdlib.h>
#include "graphviz.h"
#include "testdaten.h"

void graphviz(int node_count, char * input_weg)
{

    FILE *file_weg=fopen(input_weg, "r");
    if (file_weg == NULL)
    {
        printf("%s konnte nicht geoeffnet werden.",input_weg);
        exit(-1);
    }

    //printf("\n\nTEST %d\n\n",node_count);

    int i = 0;
    //int j = 0;
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