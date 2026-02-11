#include <iostream>
#include "datenbank.h"

int main() {

    datenbank Mitarbeiter;

    std::cout << "**************************************************" << std::endl;
    std::cout << "  Wilkommen, dass ist die Mitarbeiterdatenbank    " << std::endl;
    std::cout << "**************************************************" << std::endl;
    std::cout << "Was möchten Sie machen?" << std::endl;

    std::cout << "1: Mitarbeiter zur Datenbank hinzufuegen" << std::endl;
    std::cout << "2: Mitarbeiter von der Datenbank löschen" << std::endl;
    std::cout << "3: Mitarbeiter-Daten ansehen" << std::endl;
    std::cout << "4: Gehalt eines Mitarbeiters verändern" << std::endl;
    std::cout << "**************************************************" << std::endl;
    std::cout << "0: Programm schließen" << std::endl;
    std::cout << "**************************************************" << std::endl;
    std::cout << "Eingabe: ";
    int Eingabe;
    std::cin >> Eingabe;
    switch (Eingabe) {
    case 1:
        std::cout << "***************************************" << std::endl;
        std::cout << "Sie wollen einen Mitarbeiter hinzufügen" << std::endl;
        std::cout << "***************************************" << std::endl;
        Mitarbeiter.fuegeMitarbeiterhinzu();
        std::cout << "***********************************************************" << std::endl;
        std::cout << "Mitarbeiter erfolgreich hinzugefügt (siehe Datei liste.txt)" << std::endl;
        std::cout << "****************************************************************************" << std::endl;
        std::cout << "Die Mitarbeiternummer " << Mitarbeiter.mitarbeiternum << " wurde zugewiesen." << std::endl;
        std::cout << "****************************************************************************" << std::endl;
        break;
    case 2:
        std::cout << "***************************************" << std::endl;
        std::cout << "Sie wollen einen Mitarbeiter löschen" << std::endl;
        std::cout << "***************************************" << std::endl;
        std::cout << "Dazu benötigen Sie die Mitarbeiternummer" << std::endl;
        std::cout << "***************************************" << std::endl;
        Mitarbeiter.loescheMitarbeiter();
        std::cout << "***************************************" << std::endl;
        std::cout << "Mitarbeiter wurde erfolgreich gelöscht" << std::endl;
        std::cout << "***************************************" << std::endl;
        break;
    case 3:
        std::cout << "*********************************************" << std::endl;
        std::cout << "Was möchten Sie einsehen?" << std::endl;


        int Eingabe3;
        std::cout << "1: Postleitzahl und Gehalt eines Mitarbeiters" << std::endl;
        std::cout << "2: Mitarbeiternummer eines Mitarbeiters" << std::endl;
        std::cout << "*********************************************" << std::endl;
        std::cout << "0: Programm schließen" << std::endl;
        std::cout << "*********************************************" << std::endl;
        std::cout << "Eingabe: ";
        std::cin >> Eingabe3;
        switch (Eingabe3) {
        case 1:
            std::cout << "**********************************************************************" << std::endl;
            std::cout << "Sie wollen die Postleitzahl und das Gehalt eines Mitarbeiters einsehen" << std::endl;
            std::cout << "**********************************************************************" << std::endl;
            std::cout << "Dazu benötigen Sie einen Mitarbeiter -Vornamen und -Namen" << std::endl;
            std::cout << "**********************************************************************" << std::endl;
            Mitarbeiter.PlzGehalt();
            break;
        case 2:
            std::cout << "************************************************************" << std::endl;
            std::cout << "Sie wollen die Mitarbeiternummer eines Mitarbeiters einsehen" << std::endl;
            std::cout << "************************************************************" << std::endl;
            std::cout << "Dazu benötigen Sie einen Mitarbeiter -Vornamen und -Namen" << std::endl;
            std::cout << "************************************************************" << std::endl;
            Mitarbeiter.findeMitarbeiternummer();
            break;

        case 0:
            return 0;
        default:
            std::cout << "___________________________" << std::endl;
            std::cout << "Eingabe ist nicht definiert" << std::endl;
            std::cout << "Programm wird beendet " << std::endl;
            std::cout << "___________________________" << std::endl;
            return 0;

        }
        break;
    case 4:
        std::cout << "**************************************************" << std::endl;
        std::cout << "Sie wollen das Gehalt eines Mitarbeiters verändern" << std::endl;
        std::cout << "**************************************************" << std::endl;
        std::cout << "Dazu benötigen Sie die Mitarbeiternummer" << std::endl;
        std::cout << "**************************************************" << std::endl;
        Mitarbeiter.neuesGehalt();
        std::cout << "************************************************" << std::endl;
        std::cout << "Das Gehalt des Mitarbeiters wurde aktualliesiert" << std::endl;
        std::cout << "************************************************" << std::endl;
        break;
    case 0:
        return 0;
    default:
        std::cout << "___________________________" << std::endl;
        std::cout << "Eingabe ist nicht definiert" << std::endl;
        std::cout << "Programm wird beendet " << std::endl;
        std::cout << "___________________________" << std::endl;
        return 0;


    }












    return 0;
}
