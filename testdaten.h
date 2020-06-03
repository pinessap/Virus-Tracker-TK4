#ifndef testdaten_h
#define testtdaten_h

//header
/*
-> zählt Zeilenanzahl einer Datei
-> parameter:   - Verlauf der Datei
-> return: Zeilenanzahl
*/
int count_lines(FILE * input);

/*
-> liest Namen der Textdatei ein, soll dann jeder Person eine ID geben
-> output: Person-ID | Name
-> parameter:
                - Verlauf der input-Textdatei
                - Verlauf der output-Textdatei 
                - Anzahl an Personen, die generiert werden sollen
-> return: erfolgreich = 0, Fehler beim input = -1, Fehler beim output = -2
*/
int id_name(char * input, char * output, int n);

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

/*
-> Name wird übergeben
-> gibt ID zurück
*/
int search_id(char * input, char search_name[]);

/*
-> speichert alle Spalten der interactions.csv in eigene arrays
(kann auch in die main gepackt werden, um die arrays anderen Funktionen zu übergeben)
*/
int interactions_array(char * input);

#endif //testdaten_h