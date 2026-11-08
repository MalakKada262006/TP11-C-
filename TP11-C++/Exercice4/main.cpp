#include <iostream>
#include <string>
#include <vector>
#include <memory>

class NoeudFichier {
protected:
    std::string m_nom;

public:
    NoeudFichier(const std::string& nom) : m_nom(nom) {}
    virtual ~NoeudFichier() = default;

    std::string nom() const {
        return m_nom;
    }

    virtual int taille() const = 0;
};

class Fichier : public NoeudFichier {
private:
    int m_taille;

public:
    Fichier(const std::string& nom, int taille)
        : NoeudFichier(nom), m_taille(taille) {}

    int taille() const override {
        return m_taille;
    }
};

class Dossier : public NoeudFichier {
private:
    std::vector<std::unique_ptr<NoeudFichier>> m_enfants;

public:
    Dossier(const std::string& nom) : NoeudFichier(nom) {}

    void ajouter(std::unique_ptr<NoeudFichier> enfant) {
        m_enfants.push_back(std::move(enfant));
    }

    // Calcul récursif de la taille totale du dossier
    int taille() const override {
        int tailleTotale = 0;
        for (const auto& enfant : m_enfants) {
            tailleTotale += enfant->taille();
        }
        return tailleTotale;
    }

    void afficher(int niveau = 0) const {
        std::string indentation(niveau * 2, ' ');
        std::cout << indentation << "[Dossier] " << nom() << " (Taille totale : " << taille() << " Ko)\n";

        for (const auto& enfant : m_enfants) {
            Dossier* sousDossier = dynamic_cast<Dossier*>(enfant.get());
            if (sousDossier) {
                sousDossier->afficher(niveau + 1);
            } else {
                std::cout << indentation << "  - [Fichier] " << enfant->nom()
                          << " (" << enfant->taille() << " Ko)\n";
            }
        }
    }
};

int main() {
    auto racine = std::make_unique<Dossier>("Racine");

    auto dossierDocs = std::make_unique<Dossier>("Documents");
    dossierDocs->ajouter(std::make_unique<Fichier>("CV.pdf", 120));
    dossierDocs->ajouter(std::make_unique<Fichier>("Rapport.docx", 350));

    auto dossierImages = std::make_unique<Dossier>("Images");
    dossierImages->ajouter(std::make_unique<Fichier>("photo1.png", 2048));
    dossierImages->ajouter(std::make_unique<Fichier>("photo2.jpg", 1500));

    auto sousDossierProjet = std::make_unique<Dossier>("ProjetCPP");
    sousDossierProjet->ajouter(std::make_unique<Fichier>("main.cpp", 15));
    sousDossierProjet->ajouter(std::make_unique<Fichier>("Forme.hpp", 5));

    dossierDocs->ajouter(std::move(sousDossierProjet));

    racine->ajouter(std::move(dossierDocs));
    racine->ajouter(std::move(dossierImages));
    racine->ajouter(std::make_unique<Fichier>("notes.txt", 10));

    std::cout << "--- Structure du systeme de fichiers --- \n\n";
    racine->afficher();

    std::cout << "Taille totale du dossier Racine : " << racine->taille() << " Ko\n";

    return 0;
}
