#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
#include "datenbank.h"


void datenbank::arraylesen() {/*aktualisiert den vector, durch die Datei "array.txt". Dadurch hat der Vector immer alle
    Mitarbeiternummern gespeichert und es kann keine Mitarbeiternummer 2 mal vorkommen. Die Datei mit den Nummern wird nie
    zu Programm-ende gelöscht und daher ist es sehr pratkisch diese zu nutzen*/
    inarray.open("array.txt"); //Öffnen der "array.txt" Datei
    if (inarray.is_open()) { //Wenn "array.txt" offen ist, mach folgendes{...}
        std::string line; //jede zeile der liste wird dem string line zugewiesen
        while (std::getline(inarray, line)) { //solange eine Zeile in der Datei auslesbar ist...
            int integerline = 0; //Variable zum speichern der Mitarbeiternummer als int
            integerline = std::stoi(line); //konvertiere string zu integer und speichere in Variable 
            arraymitarbeiternum.push_back(integerline); //füge den Wert der Variable zum Vector hinzu
        }//diese Schleife fügt jede Mitarbeiternummer zum Vector hinten hinzu, die in der Datei abzulesen ist
    }
}

int datenbank::erstelleMitarbeiternummer() {/*Diese Funktion generiert eine 4 - Stellige Mitarbeiternummer,
    die nicht doppelt vorkommt und gibt diese zurück und speichert diese Nummer in der Datei "array.txt" ab und
    fügt diese Nummer dem vector der Mitarbeiternummern hinzu*/

    arraylesen();//aktualisiert den vector der Mitarbeiternummern, da wir den mit allen vorhandenen Mitarbeiternummern benötigen

    srand(time(0)); /*ein Befehl der eine Zufällige Nummer generiert, die abhängig von der Laufzeit
    des Programms ist. Dieses Level von "Zufälligkeit" reicht uns bei einer Datenbank jedoch völlig aus*/
    int mitarbeiternum = rand() % 9999 + 1; //die int-Variable bekommt einen Zufälligen Wert bis 9999 zugewiesen
    if (mitarbeiternum < 1000) { /*Da die rand() funktion abhängig von der Laufzeit des Programms ist,
        muss man darauf achten, dass vorallem am Anfang keine 3-Stelligen Mitarbeiternummern generiert werden.
        Daher addiere ich 1000 zur mitarbeiternum, wodurch diese garantiert nicht mehr 3-Stellig ist*/
        mitarbeiternum += 1000;
    }

    bool found = false;

    for (int i : arraymitarbeiternum) { //für jedes i-element aus dem vector der Mitarbeiternummern
        if (i == mitarbeiternum) { //falls das Element i gleich der generierten Mitarbeiternummer ist, setze found auf true
            found = true;
            break; //brich die Schleife ab wenn diese Condition gilt
        }
    }

    if (found) { /*wenn found true ist, dann laufe die Funktion nochmal durch
        (solange bis found false ist, also die Mitarbeiternummer völlig neu ist)*/
        return erstelleMitarbeiternummer();
    }
    else {//wenn found false ist...

        arraymitarbeiternum.push_back(mitarbeiternum);//füge die neue Mitarbeiternummer dem Vector der Mitarbeiternummern hinzu
        outarray.open("array.txt", std::ofstream::app);/*öffne "array.txt" in std::ofstream::app, damit der Inhalt der Datei erhalten bleibt
        und nur neues hinzugefügt wird */
        outarray << mitarbeiternum << std::endl;//schreibe Mitarbeiternummer in "array.txt"
        return mitarbeiternum;//gib Mitarbeiternummer zurück
    }
}

void datenbank::fuegeMitarbeiterhinzu() /*fragt den Benutzer nach den Daten des Mitarbeiters ab und
fügt diesen Mitarbeiter in die Datenbank hinzu und schreibt daher den Inhalt in die Datei "liste.txt" ein*/
{   //Abfrage der Daten und speicherung in Klassen Variable
    std::cout << "Vorname: " << std::endl;
    std::cin >> vname;//Variable vname wird der Vorname übergeben
    std::cout << "Name: " << std::endl;
    std::cin >> name;//Variable name wird der Nachname übergeben
    std::cout << "Postleitzahl: " << std::endl;
    std::cin >> plz;//Variable plz wird die Postleitzahl übergeben
    std::cout << "Was hat " << vname << " " << name << "für ein Gehalt?" << std::endl;
    std::cout << "Gehalt: " << std::endl;
    std::cin >> gehalt;//Variable gehalt wird das Gehalt übergeben
    mitarbeiternum = datenbank::erstelleMitarbeiternummer();//es wird eine neue Mitarbeiternummer generiert

    //Hinzufügen der abgespeicherten Daten in die ""liste.txt" Datei -->
    outdatei.open("liste.txt", std::ofstream::app);/*öffne "liste.txt" in std::ofstream::app,
    damit Inahlt nur hinzugefügt wird und nicht überschrieben wird, (Datenbank wird erweitert)*/
    outdatei << "Mitarbeiternummer: " << mitarbeiternum << std::endl;//zuerst wird Variable mitarbeiternum in die Zeile geschrieben
    outdatei << "Vorname: " << vname << std::endl << "Name: " << name << std::endl;
    outdatei << "Postleitzahl: " << plz << std::endl << "Gehalt: " << gehalt << " € \n" << std::endl;/*am Ende nochmal std::endl,
    damit eine leere Zeile zwischen jeden Mitarbeiter entseht*/
    //std::endl startet eine neue Zeile zwischen jeden Inhalt der eingeschrieben wird in die Datei



}

int datenbank::findeMitarbeiternumZeile() /*fragt den Benutzer nach der gesuchten Mitarbeiternummer und findet diese,
in dem die Funktion die Datei "liste.txt" Zeile für Zeile abliest und anschließend die Zeile in der es gefunden wurde
zurück gibt. Die Zeile wird als Variable definiert und erhöht sich um +1 bei jeder Iteration der Schleife, bis die Bedingung für
den gesuchten Mitarbeiter gilt. Wenn die Bedingung gilt wird die Schleife abgebrochen und
die Variable Zeile hat als Wert die Zeile in der die Mitarbeiternummer gefunden wurde*/
{
    std::cout << "Mitarbeiternummer: " << std::endl;//Abfrage, welche Mitarbeiternummer gesucht
    std::cin >> mitarbeiternum; //speicher die Mitarbeiternummer als int zuerst 
    std::string mitarbeiternum_string = std::to_string(mitarbeiternum); /*konvertiere die Mitarbeiternummer zu einem String,
    um diesen string mit jeder Zeile aus der Datei "liste.txt" vergleichen zu können*/

    mitarbeiternum_string.insert(0, "Mitarbeiternummer: "); /*Wir fügen "Mitarbeiternummer: " zum string vorne (an der Stelle 0) ein,
    damit wir unseren Mitarbeiter string sinvoll mit der liste.txt Datei, Zeile für Zeile abgleichen
    (da in der Datei bzw. Datenbank die Mitarbeiternummern in
    der Form abgespeichert sind: (x sind die Zahlen 0-9)[erste Zahl x != 0]
    Mitarbeiternummer: xxxx
    */

    int Zeile = 0; //definiere die aktuelle Zeile in der wir uns befinden

    std::ifstream indatei("liste.txt"); //öffne die Datei "liste.txt", zum auslesen der Zeilen

    if (indatei.is_open()) {//Wenn Datei "liste.txt" offen ist, mach folgendes{...}    
        std::string line; //String, der als Wert, pro iteration jede gelesene Zeile erhält
        while (std::getline(indatei, line)) { //solange Zeilen aus der Datei abzulesen sind speicher den Ihalt in line und mach folgendes {...}
            Zeile += 1; //erhöhe Zeile um +1
            if (line == mitarbeiternum_string) {  //Wenn der Inhalt der ausgelesenen Zeile gleich unserem Mitarbeiternummer string ist...                                           
                return Zeile;//gib die Zeile zurück 
            }

        }
        return 0;//Wenn die Mitarbeiternummer nicht gefunden wurde in der Datei, gib 0 zurück

    }
    //falls die Datei nicht ausgelesen werden kann, ist sie meist nicht geöffnet worden
    std::cout << "Datei konnte nicht geöffnet werden" << std::endl;
    return 1;
}


int datenbank::findeMitarbeiternameZeile()/*fragt den Benutzer nach Vor- und Nachnamen und findet dazu die Mitarbeiternummer,
in dem die Funktion die Datei "liste.txt" Zeile für Zeile abliest und anschließend wenn die erste Zeile dem Vornamen entspricht und
die darrauf folgende dem Nachnamen, die Zeile zurück gibt, in der der Nachnamen-Bedingung gilt.
Die Zeile wird als Variable definiert und erhöht sich um +1 bei jeder Iteration der Schleife, bis die Bedingung für
den gesuchten Mitarbeiter Nachnamen gilt. Wenn die Bedingungen gelten wird die Schleife abgebrochen und
die Variable Zeile hat als Wert die Zeile in der der Nachname gefunden wurde*/
{

    std::cout << "Vorname: " << std::endl;//Abfrage Vorname
    std::cin >> vname;//speicher Vorname in Variable vname
    vname.insert(0, "Vorname: ");/*füge an der Stelle 0 (Anfang vom String) den Text "Vorname: ", damit der vname string sinvoll
    mit jeder Zeile der Datei "liste.txt" bzw. mit der Datenbank, abgeglichen werden kann*/

    std::cout << "Name: " << std::endl;//Abfrage Nachname
    std::cin >> name;//speicher Nachname in Variable name
    name.insert(0, "Name: ");/*füge an der Stelle 0 (Anfang vom String) den Text "Nachname: ", damit der name string sinvoll
    mit jeder Zeile der Datei "liste.txt" bzw. mit der Datenbank, abgeglichen werden kann*/


    int Zeile = 0; //definiere aktuelle Zeile

    std::ifstream indatei("liste.txt");
    //indatei.open("liste.txt");

    if (indatei.is_open()) { //Wenn Datei "liste.txt" offen ist, mach folgendes {...}

        std::string line;
        while (std::getline(indatei, line)) {//Es wird die Zeile gesucht wo gesuchter vname und danach name steht          
            Zeile += 1;//bei jeder Iteration wird Zeile um +1 erhöht
            if (line == vname) {//Wenn der Vorname gleich dem string vname ist, mach folgendes{...}
                std::getline(indatei, line);//lese Zeile aus und weise string line dadurch einen neuert Wert zu
                if (line == name) { //Wenn der Nachname gleich dem string name ist, mach folgendes{...}
                    //erhöhe noch einmal Zeile +1 (so haben wir die Zeile wo der Nachname steht), und gib diese anschließend zurück
                    Zeile += 1;
                    return Zeile;

                }

            }

        }
        return 0; //Wenn der Mitarbeiter nicht gefunden wurde, dann gebe 0 zurück

    }
    //falls die Datei nicht ausgelesen werden kann, ist sie meist nicht geöffnet worden
    std::cout << "Datei konnte nicht geöffnet werden" << std::endl;
    return 1;
}

void datenbank::neuesGehalt() /*überschreibt das alte Gehalt eines Mitarbeiters in ein neues vom Benutzer eingegebenes um
und speichert es in die Datei "liste.txt", in dem die Funktion die Zeile +4 speichert,
wo die Mitarbeiternummer des Mitarbeiters sich befindet und bei dem man das Gehalt verändert werden soll. Dann wird durch die
Datei "liste.txt" iteriert und eine current_line Variable jedes mal um
+1 bei jeder iteration erhöht, wo eine Zeile ausgelesen wird. Dies wird solang gemacht, bis current_line == linenum -1
gilt und dann wird einfach das neue Gehalt abgefragt und durch das alte in die Datei ersetzt, in dem es einfach überschrieben wird*/
{
    std::fstream datei("liste.txt", std::ios::in | std::ios::out);//öffne Datei "liste.txt", zum ein und auslesen 


    if (datei.is_open()) { //Wenn die Datei "liste.txt" offen ist, mach folgendes{...}

        int linenum = findeMitarbeiternumZeile() + 4; /*Es wird eine int Variable mit der Zeile definiert,
        in der sich das Gehalt des Mitarbeiters befindet, daher findet man den Mitarbeiter zunächst anhand
        der Mitarbeiternummer und addiert dann +4 zur Zeile, um zur Zeile zu kommen, wo das Gehalt gespeichert ist*/

        std::string line;//definiere einen string der als Wert die ,pro iteration, gelesene Zeile erhält
        for (int current_line = 1; std::getline(datei, line); current_line++) {//erhöhe current_line (aktuelle Zeile) um +1 pro iteration
            if (current_line == linenum - 1) { //Wenn die aktuelle Zeile gleich der gesuchten Zeile -1 ist, dann mach folgendes {...}
                std::cout << "neues Gehalt: " << std::endl; //Abfrage nach neuem Gehalt 
                std::cin >> line;//neues Gehalt wird als string gespeichert
                line.insert(0, "Gehalt: ");/*füge "Gehalt: " an der Stelle 0 des Strings,
                also an den Anfang, damit die Strucktur in der Datenbank erhalten bleibt*/
                line.append(" €");//füge ein € Zeichen am Ende hinzu, damit die Strucktur der Datenbank erhalten bleibt



                /* Setze den Dateizeiger auf den Anfang der aktuellen Zeile,
                damit keine Fehler entstehen wenn neuer Inhalt in die Datei eingeschrieben wird */
                datei.seekp(datei.tellg());

                datei << line; //Gehalt aktuallisiert, das alte Gehalt wurde überschrieben
                break;//brich aus der Funktion aus
            }
        }

    }
    else {
        //falls die Datei nicht ausgelesen werden kann, ist sie meist nicht geöffnet worden
        std::cout << "Datei konnte nicht geöffnet werden" << std::endl;
    }

}

void datenbank::loescheMitarbeiter() /*löscht einen Mitarbeiter aus der Datenbank: Also aus der Datei "liste.txt" und seine 
Mitarbeiternummer aus der Datei "array.txt" */
{
    std::cout << "Welchen Mitarbeiter möchten Sie aus der Datenbank entfernen? " << std::endl; //Abfrage
    int line_delete; 
    line_delete = findeMitarbeiternumZeile(); //line_delete bekommt die Zeile, wo die gesuchte Mitarbeiternummer ist zugewiesen
    if (line_delete == 0) { //wenn line_delete den Wert 0 hat, dann wurde kein Mitarbeitergefunden
        std::cout << "****************************************" << std::endl;
        std::cout << "Diese Mitarbeiternummer existiert nicht." << std::endl;
        std::cout << "****************************************" << std::endl;
        loescheMitarbeiter(); //frag nochmal die Mitarbeiternummer ab
    }
    /*ich arbeite mit 2 Dateien, eine leere Datei wird benutzt um alles zu kopieren, ausser die Daten des zu löschenden Mitarbeiters. 
    Die Originaldatei wird anschließend vom Inhalt leer gemacht und so umbenannt, dass man diese direkt als leere Datei für einen erneueten Funktionsaufruf verwenden kann.
    Die Kopie Datei wird wie die frühere Original Datei umbenannt, so kann man diese auch bei erneutem Funktionsaufruf verwenden */

    std::ifstream datei("liste.txt");//datei zum lesen - Original Datei
    std::ofstream neuedatei("temp_liste.txt"); // temporäre datei zum schreiben - Kopie Datei

    std::string line; //Inhalt der aktuellen Zeile wird string hier gespeichert
    int current_line = 1; //aktuelle Zeile
    std::string mitarbeiternummer; /*für die Mitarbeiternummerliste (andere Datei "array.txt") brauchen wir die zu löschende 
    Mitarbeiternummer vom gelöschten Mitarbeiter*/

    while (std::getline(datei, line)) { /*solange die Datei eine Zeile zum auslesen hat, speicher den Inhalt in line und
        mach folgendes {...} */
        if (current_line == line_delete) { //wenn aktuelle Zeile == zu löschenden Zeile (Mitarbeiternummer des zu löschenden)
            mitarbeiternummer = line; //mitarbeiternummer string bekommt die aktuell ausgelesene Zeile als Inhalt zugewiesen
            mitarbeiternummer.erase(0, 19); /*der "Mitarbeiternummer: " - Teil des Strings muss entfernt werden, da in der array datei, 
            dieser Teil des Strings nicht vorhanden ist*/


        }

        if ((current_line != line_delete) and //wenn (aktuelle Zeile != Zeile von Mitarbeiternummer vom zu löschenden Mitarbeiter) und ...
            (current_line != line_delete + 1) and//wenn (aktuelle Zeile != Zeile von Vorname vom zu löschenden Mitarbeiter) und ...
            (current_line != line_delete + 2) and//wenn (aktuelle Zeile != Zeile von Name vom zu löschenden Mitarbeiter) und ...
            (current_line != line_delete + 3) and//wenn (aktuelle Zeile != Zeile von Postleitzahl vom zu löschenden Mitarbeiter) und ...
            (current_line != line_delete + 4) and//wenn (aktuelle Zeile != Zeile von Gehalt vom zu löschenden Mitarbeiter) und ...
            (current_line != line_delete + 5)) {//wenn (aktuelle Zeile != leere freie Zeile nach dem zu löschenden Mitarbeiter) dann mach {...}
            neuedatei << line << std::endl; /*schreibe alles von der Original Datei in die Kopie Datei "temp_liste.txt",
            ausser den Mitarbeiter der löschen ist */
        }//so werden alle Daten ausser die vom zu löschenden Mitarbeiter neu geschrieben 
        current_line++; //erhöhe aktuelle Zeile um +1
    }

    //schließe beide Dateien
    neuedatei.close();
    datei.close();

    //Dateien so umbenennen, dass wir diese beim nächsten Funktionsaufruf wieder verwenden können
    rename("liste.txt", "tempName.txt");//dazu brauchen wir einen temporären namen

    std::ofstream temp_datei("tempName.txt", std::ios::trunc); /*Der Inhalt der früheren Original Datei wird entleert,
    so können wir diese nächstes mal wieder verwenden*/
    temp_datei.close(); //Anschließend Datei schließen


    rename("temp_liste.txt", "liste.txt"); /*Nur noch der Name der Orinaldatei muss wieder hergestellt werden 
    und nun haben wir eine neue Original Datei für das nächste mal, die alles beinhält ausser dem gelöschten Mitarbeiter*/
    rename("tempName.txt", "temp_liste.txt");/*Die frühere Original Datei ist nun leer und hat den Namen
    für eine temporäre Datei, die man beim nächsten Funktionsaufruf wieder verwenden kann*/


    /*Nun wenden wir das gleiche Schema auf die Mitarbeiternummer-liste. 
    Wir haben einen String mit der Mitarbeiternummer von dem vorherigen Teil der Funktion direkt mitgenommen 
    und kopieren die datei mit dem gleichen Prinzip wie zuvor, nur dass die Zeile mit der Mitarbeiternummer des zu löschenden Mitarbeiters,
    nicht mit rüber kopiert werden soll*/
    std::ifstream listedatei("array.txt");//datei zum lesen-Original Datei
    std::ofstream neuelistedatei("temp_array.txt");//temporäre datei zum schreiben - Kopie Datei

    std::string liste_line;
    while (std::getline(listedatei, liste_line)) { //liste_line bekommt jede Zeile von "array.txt" als Wert
        liste_line.resize(mitarbeiternummer.length());//Um Fehler zu vermeiden wird liste_line auf die Größe von mitarbeiternummer gesetzt

        if (liste_line != mitarbeiternummer) { /*Wenn der aktuelle Wert der Zeile != die Zeile von der zu löschenden Mitarbeiternummer ist,
            dann schreibe es in die temporäre Datei ein.*/
            neuelistedatei << liste_line << std::endl;
        }
    }

    //schließe beide Dateien
    neuelistedatei.close();
    listedatei.close();

    //Dateien so umbenennen, dass wir diese beim nächsten Funktionsaufruf wieder verwenden können
    rename("array.txt", "tempName.txt"); //dazu brauchen wir einen temporären namen

    std::ofstream temp_liste_datei("tempName.txt", std::ios::trunc); /*Der Inhalt der früheren Original Datei wird entleert, so können wir diese nächstes mal wieder verwenden*/
    temp_liste_datei.close(); //Anschließend Datei schließen

    rename("temp_array.txt", "array.txt"); /*Nur noch der Name der Orinaldatei muss wieder hergestellt werden und nun haben wir eine neue Original Datei,
    die alles beinhält ausser die gelöschte Mitarbeiternummer*/
    rename("tempName.txt", "temp_array.txt");/*Die frühere Original Datei ist nun leer und hat den Namen für eine temporäre Datei,
    die man beim nächsten Funktionsaufruf wieder verwenden kann*/





}

void datenbank::PlzGehalt() {


    int Zeile;
    Zeile = findeMitarbeiternameZeile();
    if (Zeile == 0) {
        std::cout << "Mitarbeiter nicht gefunden" << std::endl;
    }


    int current_line = 1;
    std::string line;

    std::ifstream indatei("liste.txt");

    while (std::getline(indatei, line)) {
        current_line += 1;
        if (Zeile == current_line - 1) {
            std::cout << "****************" << std::endl;
            std::cout << "PLZ und GEHALT: " << std::endl;
            std::cout << "****************" << std::endl;
            std::getline(indatei, line);            //Postleitzahl
            std::cout << line << std::endl;
            std::getline(indatei, line);            //Gehalt 
            std::cout << line << std::endl;



        }

    }


}

void datenbank::findeMitarbeiternummer() {
    int Zeile;
    Zeile = findeMitarbeiternameZeile();

    int current_line = 0;

    std::ifstream indatei("liste.txt");
    std::string line;
    while (std::getline(indatei, line)) {
        current_line++;
        if (current_line == Zeile - 2) {
            std::cout << "***********************************************************************" << std::endl;
            std::cout << vname << std::endl;
            std::cout << name << std::endl;
            std::cout << "***********************************************************************" << std::endl;
            std::cout << line << std::endl;
            std::cout << "***********************************************************************" << std::endl;
        }

    }





}
