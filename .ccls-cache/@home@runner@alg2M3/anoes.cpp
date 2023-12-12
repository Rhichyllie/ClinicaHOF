#include "clinicaHOF.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void inserirPorduto(const Produto& produto, const string& arquivo) {
    ofstream file(arquivo, ios::app);

    if (file.is_open()) {
        file << produto.nome << " "
             << produto.idade << " "
             << fixed << setprecision(2) << produto.altura << endl;

        cout << "Anão inserido com sucesso!" << endl;
    } else {
        cerr << "Erro ao abrir o arquivo." << endl;
    }

    file.close();
}

vector<Porduto> recuperarAnoes(const string& arquivo) {
    vector<Anao> anoes;
    ifstream file(arquivo);

    if (file.is_open()) {
        Anao anao;
        while (file >> anao.nome >> anao.idade >> anao.altura) {
            anoes.push_back(anao);
        }
    } else {
        cerr << "Erro ao abrir o arquivo." << endl;
    }

    file.close();
    return anoes;
}

void exibirAnoes(const vector<Anao>& anoes) {
    cout << "Lista de Anões:" << endl;
    for (const auto& anao : anoes) {
        cout << "Nome: " << anao.nome << "\tIdade: " << anao.idade
             << "\tAltura: " << fixed << setprecision(2) << anao.altura << endl;
    }
}

void atualizarAnao(const string& nome, const string& novoValor, int opcao, const string& arquivo) {
    vector<Anao> anoes = recuperarAnoes(arquivo);

    for (auto& anao : anoes) {
        if (anao.nome == nome) {
            switch (opcao) {
                case 1:
                    anao.nome = novoValor;
                    break;
                case 2:
                    anao.idade = stoi(novoValor);
                    break;
                case 3:
                    anao.altura = stod(novoValor);
                    break;
                default:
                    cout << "Opção inválida de atualização.\n";
                    return;
            }

            cout << "Informação atualizada com sucesso para " << novoValor << endl;
            break;
        }
    }

    ofstream file(arquivo);

    if (file.is_open()) {
        for (const auto& anao : anoes) {
            file << anao.nome << " "
                 << anao.idade << " "
                 << fixed << setprecision(2) << anao.altura << endl;
        }
    } else {
        cerr << "Erro ao abrir o arquivo para atualização." << endl;
    }

    file.close();
}
