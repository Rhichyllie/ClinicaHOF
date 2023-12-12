#include "clinicaHOF.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  const string arquivo = "produtosHOF.txt";
  const string arquivo2 = "pacientes.txt";
  const string arquivoUsuarios = "usuarios.txt";
  vector<Usuario> usuarios = carregarUsuariosDoArquivo(arquivoUsuarios);

  string login, senha;

  bool credenciais_corretas = false;

  while (!credenciais_corretas) {
      cout << "Digite o login: ";
      cin >> login;
      cout << "\nDigite a senha: ";
      cin.ignore(); // Limpa o buffer do teclado, removendo o caractere de nova linha pendente
      getline(cin, senha);

      credenciais_corretas = verificarCredenciais(login, senha, usuarios);

      if (!credenciais_corretas) {
          cout << "\nLogin ou senha incorretos. Tente novamente." << endl;
      }
  }

  menu();

  return 0;
}
