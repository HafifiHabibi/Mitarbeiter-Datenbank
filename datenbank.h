#include <fstream>
#include <vector>

class datenbank {
public:
    ///Elemente für individuellen Mitarbeiter:
    int mitarbeiternum; //mitarbeiternummer
    std::string vname;  //Vorname 
    std::string name;   //Nachname
    int plz;           //Postleitzahl
    double gehalt;      //Gehalt
    
    std::vector<int>arraymitarbeiternum;//vector wo alle mitarbeiternummern gespeichert werden (muss immer aktualisiert werden, durch Fkt)



    int erstelleMitarbeiternummer();//neue einzigartige Mitarbeiternummer generieren
    int findeMitarbeiternumZeile(); //findet die Zeile wo die gesuchte Mitarbeiternummer sich befindet
    int findeMitarbeiternameZeile(); //findet die Zeile wo der gesuchte Mitarbeitername steht (abhängig vom Vornamen)

    void fuegeMitarbeiterhinzu();//fügt Mitarbeiter zur Datenbank hinzu und seine Mitarbeiternummer zur anderen Datei
    void PlzGehalt();//gibt die Postleitzahl und das Gehalt eines Mitarbeiters aus 
    void neuesGehalt();//gibt einem Mitarbeiter eins neues Gehalt und aktualisiert dies in der Datenbank
    void loescheMitarbeiter();//löscht einen Mitarbeiter und seine Mitarbeiternummer aus der Datenbank und aus der anderen Datei
    void findeMitarbeiternummer();//findet anhand eines Mitarbeiter-Namen, seine Mitarbeiternummer

    std::ofstream outdatei;//Datei "liste.txt", die zum einschreiben von Zeilen genutzt wird, um neue Mitarbeiter hinzu zu fügen
    std::ifstream indatei;//Datei "liste.txt", die zum Zeilen auslesen benutzt wird (Datenbank)

    std::ofstream outarray;//Datei "array.txt", die zum einschreiben von Zeilen genutzt wird, um neue Mitarbeiternummern hinzu zu fügen
    std::ifstream inarray;//Datei "array.txt", die zum Zeilen auslesen benutzt wird (Mitarbeiternummerliste)

    std::fstream datei;//Datei "liste.txt", die zum einschreiben und auslesen gleichzeitig genutzt wird (also ein- und auslesen)


    void arraylesen();//Damit wird der vector der Mitarbeiternummern aktualisiert, es wird die Mitarbeiternummern-liste dazu verwendet

};