#include <iostream>
#include <vector>
#include <memory>

class Paiement {
public:
    virtual void effectuerPaiement(double montant) const = 0;
    virtual ~Paiement() = default;
};

class PaiementCarte : public Paiement {
public:
    void effectuerPaiement(double montant) const override {
        std::cout << "Paiement de " << montant << " DH par carte bancaire." << std::endl;
    }
};

class PaiementEspece : public Paiement {
public:
    void effectuerPaiement(double montant) const override {
        std::cout << "Paiement de " << montant << " DH en especes." << std::endl;
    }
};

int main() {
    std::vector<std::unique_ptr<Paiement>> moyensDePaiement;

    moyensDePaiement.push_back(std::make_unique<PaiementCarte>());
    moyensDePaiement.push_back(std::make_unique<PaiementEspece>());
    moyensDePaiement.push_back(std::make_unique<PaiementCarte>());
    moyensDePaiement.push_back(std::make_unique<PaiementEspece>());

    std::vector<double> montants = {340.50, 65.00, 1800.00,79.9};

    std::cout << "--- Simulation des Paiements ---\n\n";

    for (size_t i = 0; i < moyensDePaiement.size(); ++i) {
        std::cout << "Transaction " << i + 1 << " : ";
        moyensDePaiement[i]->effectuerPaiement(montants[i]);
    }

    return 0;
}
