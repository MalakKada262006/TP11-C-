#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

class Forme {
public:
    virtual double aire() const = 0;

    virtual ~Forme() = default;
};

class Cercle : public Forme {
private:
    double rayon;

public:
    Cercle(double r) : rayon(r) {}

    double aire() const override {
        return M_PI * rayon * rayon;
    }
};

class Rectangle : public Forme {
private:
    double longueur;
    double largeur;

public:
    Rectangle(double l, double L) : longueur(l), largeur(L) {}

    double aire() const override {
        return longueur * largeur;
    }
};

int main() {
    std::vector<std::unique_ptr<Forme>> formes;
    int choix = 0;

    std::cout << "--- Gestionnaire de Formes Geometriques ---\n";

    while (true) {
        std::cout << "\nQue voulez-vous ajouter ?\n";
        std::cout << "1. Un Cercle\n";
        std::cout << "2. Un Rectangle\n";
        std::cout << "3. Terminer la saisie et afficher les aires\n";
        std::cout << "Choix : ";
        std::cin >> choix;

        if (choix == 1) {
            double r;
            std::cout << "Entrez le rayon du cercle : ";
            std::cin >> r;
            formes.push_back(std::make_unique<Cercle>(r));
        }
        else if (choix == 2) {
            double l, L;
            std::cout << "Entrez la longueur du rectangle : ";
            std::cin >> l;
            std::cout << "Entrez la largeur du rectangle : ";
            std::cin >> L;
            formes.push_back(std::make_unique<Rectangle>(l, L));
        }
        else if (choix == 3) {
            break;
        }
        else {
            std::cout << "Choix invalide, veuillez reessayer.\n";
        }
    }

    std::cout << "\n--- Calcul des aires ---\n";
    for (size_t i = 0; i < formes.size(); ++i) {
        std::cout << "Forme " << i + 1 << " : Aire = " << formes[i]->aire() << std::endl;
    }

    return 0;
}
