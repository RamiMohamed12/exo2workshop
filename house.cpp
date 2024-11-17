#include <iostream>
#include <string>

using namespace std;

class Piece {
protected:
    int nb_windows;
    string couleur;

public:
    Piece(int nb_windows, string couleur) : nb_windows(nb_windows), couleur(couleur) {}

    virtual ~Piece() {} // Ajout d'un destructeur virtuel pour rendre la classe polymorphe

    int getWindows() const {
        return nb_windows;
    }

    void setWindows(int windows) {
        nb_windows = windows;
    }

    string getcolor() const {
        return couleur;
    }

    void setcolor(string clr) {
        couleur = clr;
    }
};

class Sallebain : public Piece {
private:
    bool has_shower;

public:
    Sallebain(int windows, string clr, bool shower) : Piece(windows, clr), has_shower(shower) {}

    bool hasShower() const {
        return has_shower;
    }

    void setHasShower(bool shower) {
        has_shower = shower;
    }
};

class Chambre : public Piece {
private:
    int nb_beds;

public:
    Chambre(int windows, string clr, int beds) : Piece(windows, clr), nb_beds(beds) {}

    int getNbBeds() const {
        return nb_beds;
    }

    void setNbBeds(int beds) {
        nb_beds = beds;
    }
};

class Maison {
private:
    Piece** pieces;
    int max_rooms;
    int current_rooms;

public:
    Maison(int max_rooms)
        : max_rooms(max_rooms), current_rooms(0) {
        pieces = new Piece*[max_rooms];
    }

    void addPiece(Piece* room) {
        if (current_rooms < max_rooms) {
            pieces[current_rooms++] = room;
        } else {
            cout << "Capacité maximale atteinte. Impossible d'ajouter plus de pièces." << endl;
        }
    }

    int getNbOfBathroom() const {
        int count = 0;
        for (int i = 0; i < current_rooms; ++i) {
            if (dynamic_cast<Sallebain*>(pieces[i])) {
                count++;
            }
        }
        return count;
    }

    int getNbOfBedroom() const {
        int count = 0;
        for (int i = 0; i < current_rooms; ++i) {
            if (dynamic_cast<Chambre*>(pieces[i])) {
                count++;
            }
        }
        return count;
    }

    void displayDetails() const {
        for (int i = 0; i < current_rooms; ++i) {
            cout << "Pièce " << i + 1 << ": " << pieces[i]->getcolor()
                 << " avec " << pieces[i]->getWindows() << " fenêtre(s)." << endl;

            if (auto* bathroom = dynamic_cast<Sallebain*>(pieces[i])) {
                cout << "  - Cette pièce est une salle de bain. Douche : "
                     << (bathroom->hasShower() ? "Oui" : "Non") << endl;
            } else if (auto* bedroom = dynamic_cast<Chambre*>(pieces[i])) {
                cout << "  - Cette pièce est une chambre avec " << bedroom->getNbBeds()
                     << " lit(s)." << endl;
            }
        }
    }

    ~Maison() {
        for (int i = 0; i < current_rooms; ++i) {
            delete pieces[i];
        }
        delete[] pieces;
    }
};

int main() {
    Maison maison(5);

    maison.addPiece(new Piece(2, "Blanc"));
    maison.addPiece(new Sallebain(1, "Bleu", true));
    maison.addPiece(new Chambre(2, "Vert", 3));

    maison.displayDetails();

    cout << "Nombre de salles de bain : " << maison.getNbOfBathroom() << endl;
    cout << "Nombre de chambres : " << maison.getNbOfBedroom() << endl;

    return 0;
}
