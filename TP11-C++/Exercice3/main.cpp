#include <iostream>
#include <vector>
#include <memory>

class Animal {
public:
    virtual void crier() const = 0;

    void info() const {
        std::cout << "Je suis un animal." << std::endl;
    }

    virtual ~Animal() = default;
};

class Chien : public Animal {
public:
    void crier() const override {
        std::cout << "Wouf !" << std::endl;
    }
};

class Chat : public Animal {
public:
    void crier() const override {
        std::cout << "Miaou !" << std::endl;
    }
};

class Vache : public Animal {
public:
    void crier() const override {
        std::cout << "Meuh !" << std::endl;
    }
};

int main() {
    std::vector<std::unique_ptr<Animal>> animaux;

    animaux.push_back(std::make_unique<Chien>());
    animaux.push_back(std::make_unique<Chat>());
    animaux.push_back(std::make_unique<Vache>());

    std::cout << "--- Demonstration du comportement des animaux ---\n\n";

    for (size_t i = 0; i < animaux.size(); ++i) {
        std::cout << "Animal " << i + 1 << " :\n  Info  : ";
        animaux[i]->info();

        std::cout << "  Cri   : ";
        animaux[i]->crier();
        std::cout << "\n";
    }

    return 0;
}
