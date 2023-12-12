#include "clinicaHOF.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <limits>
#include <sstream>

using namespace std;

void limparBufferEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void inserirProduto(const Produto &produto, const string &arquivo) {
    ofstream file(arquivo, ios::app);

    if (file.is_open()) {
        if (produto.custoCompra < 0 || produto.custoVenda < 0) {
            cerr << "Erro: Os valores de compra e venda devem ser não negativos." << endl;
            return;
        }

        file << produto.nomeProduto << " "
             << fixed << setprecision(2) << produto.custoCompra << " "
             << fixed << setprecision(2) << produto.custoVenda << endl;

        cout << "Produto novo inserido com sucesso!" << endl;
    } else {
        cerr << "Erro ao abrir o arquivo." << endl;
    }

    file.close();
}

void inserirPaciente(const Paciente &paciente, const string &arquivo2) {
    ofstream file(arquivo2, ios::app);

    if (file.is_open()) {
        if (paciente.idade < 0 || paciente.valorGasto < 0) {
            cerr << "Erro: A idade e o valor gasto devem ser não negativos." << endl;
            return;
        }

        file << paciente.nome << " "
             << paciente.idade << " "
             << paciente.procedimento << " "
             << fixed << setprecision(2) << paciente.valorGasto << endl;

        cout << "Paciente cadastrado com sucesso!" << endl;
    } else {
        cerr << "Erro ao abrir o arquivo." << endl;
    }

    file.close();
}

vector<Produto> recuperarProdutos(const string &arquivo) {
  vector<Produto> produtos;
  ifstream file(arquivo);

  if (file.is_open()) {
    Produto produto;
    while (file >> produto.nomeProduto >> produto.custoCompra >>
           produto.custoVenda) {
      produtos.push_back(produto);
    }
  } else {
    cerr << "Erro ao abrir o arquivo." << endl;
  }

  file.close();
  return produtos;
}

vector<Paciente> recuperarPacientes(const string &arquivo2) {
  vector<Paciente> pacientes;
  ifstream file(arquivo2);

  if (file.is_open()) {
    Paciente paciente;
    while (file >> paciente.nome >> paciente.idade >>
      paciente.procedimento >> paciente.valorGasto) {
      pacientes.push_back(paciente);
    }
  } else {
    cerr << "Erro ao abrir o arquivo." << endl;
  }

  file.close();
  return pacientes;
}

void exibirProdutos(const vector<Produto> &produtos) {
  cout << "\nLista de Produtos:" << endl << endl;
  for (const auto &produto : produtos) {
    cout << "Nome do Produto: " << produto.nomeProduto
        << "\nValor de Compra: " << fixed << setprecision(2) << produto.custoCompra 
        << "\nValor de Venda: " << fixed << setprecision(2) << produto.custoVenda << endl << endl;
  }
}

void exibirPacientes(const vector<Paciente> &pacientes) {
  cout << "\nLista de Pacientes:" << endl << endl;
  for (const auto &paciente : pacientes) {
    cout << "Nome do Paciente: " << paciente.nome
        << "\nIdade: " << paciente.idade
        <<"\nProcedimento: " << paciente.procedimento
        << "\nValor Gasto: " << fixed << setprecision(2) << paciente.valorGasto << endl << endl;
  }
}

void atualizarProduto(const string &nome, const string &novoValor, int opcao, const string &arquivo) {
    vector<Produto> produtos = recuperarProdutos(arquivo);

    bool produtoEncontrado = false;

    for (auto &produto : produtos) {
        if (produto.nomeProduto == nome) {
            produtoEncontrado = true;

            switch (opcao) {
            case 1:
                produto.nomeProduto = novoValor;
                break;
            case 2:
                try {
                    produto.custoCompra = stod(novoValor);
                } catch (const std::invalid_argument& e) {
                    cerr << "Erro: Valor de compra inválido. Certifique-se de inserir um número." << endl;
                    return;
                }
                break;
            case 3:
                try {
                    produto.custoVenda = stod(novoValor);
                } catch (const std::invalid_argument& e) {
                    cerr << "Erro: Valor de venda inválido. Certifique-se de inserir um número." << endl;
                    return;
                }
                break;
            default:
                cout << "Opção inválida de atualização.\n";
                return;
            }

            cout << "Informação atualizada com sucesso para " << novoValor << endl;
            break;
        }
    }

    if (!produtoEncontrado) {
        cout << "Produto não encontrado. Verifique o nome e tente novamente.\n";
        return;
    }

    ofstream file(arquivo);

    if (file.is_open()) {
        for (const auto &produto : produtos) {
            file << produto.nomeProduto << " " << fixed << setprecision(2) << produto.custoCompra << " " << produto.custoVenda << endl;
        }
    } else {
        cerr << "Erro ao abrir o arquivo para atualização." << endl;
    }

    file.close();
}

void atualizarPaciente(const string &nome, const string &novoValor, int opcao, const string &arquivo2) {
    vector<Paciente> pacientes = recuperarPacientes(arquivo2);

    bool pacienteEncontrado = false;

    for (auto &paciente : pacientes) {
        if (paciente.nome == nome) {
            pacienteEncontrado = true;

            switch (opcao) {
            case 1:
                paciente.nome = novoValor;
                break;
            case 2:
                try {
                    paciente.idade = stoi(novoValor);
                } catch (const std::invalid_argument& e) {
                    cerr << "Erro: Idade inválida. Certifique-se de inserir um número inteiro." << endl;
                    return;
                }
                break;
            case 3:
                paciente.procedimento = novoValor;
                break;
            case 4:
                try {
                    paciente.valorGasto = stod(novoValor);
                } catch (const std::invalid_argument& e) {
                    cerr << "Erro: Valor de gasto inválido. Certifique-se de inserir um número." << endl;
                    return;
                }
                break;
            default:
                cout << "Opção inválida de atualização.\n";
                return;
            }

            cout << "Informação atualizada com sucesso para " << novoValor << endl;
            break;
        }
    }

    if (!pacienteEncontrado) {
        cout << "Paciente não encontrado. Verifique o nome e tente novamente.\n";
        return;
    }

    ofstream file(arquivo2);

    if (file.is_open()) {
        for (const auto &paciente : pacientes) {
            file << paciente.nome << " " << paciente.idade << " " << paciente.procedimento << " " << fixed << setprecision(2) << paciente.valorGasto << endl;
        }
    } else {
        cerr << "Erro ao abrir o arquivo para atualização." << endl;
    }

    file.close();
}

float totalCompraProduto(const vector<Produto>& produtos, const string& arquivo) {
  float total = 0;
  for (const auto& produto : produtos) {
    total += produto.custoCompra;
  }
  
  return total;
}

float totalCompraPaciente(const vector<Paciente>& pacientes, const string& arquivo2) {
  float total = 0;
  for(const auto& paciente : pacientes) {
    total += paciente.valorGasto;
  }
  return total;
}

float lucroBruto(const vector<Produto>& produtos, const string& arquivo, const vector<Paciente>& pacientes, const string& arquivo2) {
  
  float totalCompra = totalCompraProduto(produtos, arquivo);
  float totalVenda = totalCompraPaciente(pacientes, arquivo2);
  
  float lucro = totalVenda - totalCompra;

  return lucro;
}

vector<Usuario> carregarUsuariosDoArquivo(const string& arquivoUsuarios) {
    vector<Usuario> usuarios;
    ifstream file(arquivoUsuarios);

    if (file.is_open()) {
        Usuario usuario;
        while (file >> usuario.login >> usuario.senha) {
            usuarios.push_back(usuario);
        }
    } else {
        cerr << "Erro ao abrir o arquivo de usuários." << endl;
    }

    file.close();
    return usuarios;
}

bool verificarCredenciais(const string& login, const string& senha, const vector<Usuario>& usuarios) {
    for (const auto& usuario : usuarios) {
        if (login == usuario.login && senha == usuario.senha) {
            return true; 
        }
    }
    return false; 
}

int obterEscolha() {
    int escolha;

    while (true) {
        cout << "Escolha: ";

        if (cin >> escolha && escolha >= 1 && escolha <= 10) {
            break; // Sai do loop se a escolha for válida
        }

        cout << "Opção inválida. Digite um número de 1 a 10." << endl;

        // Limpa o buffer do teclado para evitar entradas inválidas
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return escolha;
}

void menu(){
    const string arquivo = "produtosHOF.txt";
    const string arquivo2 = "pacientes.txt";
    const string arquivoUsuarios = "usuarios.txt";
    int escolha;
  
    cout << "\nBem vindo ao menu principal." << endl;

    do {
      cout << "\nMenu:\n" << endl;
      cout << "1. Inserir Produto\n";
      cout << "2. Cadastrar Paciente\n";
      cout << "3. Exibir Produtos\n";
      cout << "4. Exibir Pacientes\n";
      cout << "5. Atualizar Informação do Produto\n";
      cout << "6. Atualizar Informação do Paciente\n";
      cout << "7. Exibir Valor Total de Compras de Produtos\n";
      cout << "8. Exibir Valor Total de Vendas de Pacientes\n";
      cout << "9. Exibir Lucro Bruto\n";
      cout << "10. Sair\n";

      escolha = obterEscolha();
      cout << "\nEscolha válida: " << escolha << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      switch (escolha) {
        case 1: {
            Produto novoProduto;
            cout << "Digite o nome do produto: ";
            cin >> novoProduto.nomeProduto;
            cout << "Digite o valor de compra: R$ ";
            while (!(cin >> novoProduto.custoCompra)) {
                cout << "Entrada inválida. Digite um valor de compra válido: R$ ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Digite o valor de venda: R$ ";
            while (!(cin >> novoProduto.custoVenda)) {
                cout << "Entrada inválida. Digite um valor de venda válido: R$ ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            inserirProduto(novoProduto, arquivo);
            break;
          }
        case 2: {
             Paciente novoPaciente;
            cout << "Digite o nome do paciente: ";
            cin >> novoPaciente.nome;
  
            cout << "Digite a idade do paciente: ";
            while (!(cin >> novoPaciente.idade)) {
                cout << "Entrada inválida. Digite uma idade válida: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "Digite o procedimento realizado: ";
            cin >> novoPaciente.procedimento;
  
            cout << "Digite o valor de gasto: R$ ";
            while (!(cin >> novoPaciente.valorGasto)) {
                cout << "Entrada inválida. Digite um valor de gasto válido: R$ ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            inserirPaciente(novoPaciente, arquivo2);
            break;
          }
        case 3: {
          vector<Produto> produtos = recuperarProdutos(arquivo);
          exibirProdutos(produtos);
          break;
        }
        case 4: {
          vector<Paciente> pacientes = recuperarPacientes(arquivo2);
          exibirPacientes(pacientes);
          break;
        }
        case 5: {
          string nome, novoValor;
          int opcao;
          cout << "Digite o nome do produto do qual deseja atualizar: ";
          cin >> nome;
          cout << "Escolha o que deseja atualizar:\n";
          cout << "1. Nome do Produto\n";
          cout << "2. Valor de Compra\n";
          cout << "3. Valor de Venda\n";
          cout << "Opção: ";
          cin >> opcao;
          cout << "Digite o novo valor: ";
          cin >> novoValor;
  
          atualizarProduto(nome, novoValor, opcao, arquivo);
          break;
        }
        case 6: {
          string nome, novoValor;
          int opcao;
          cout << "Digite o nome do paciente do qual deseja atualizar: ";
          cin >> nome;
          cout << "Escolha o que deseja atualizar:\n";
          cout << "1. Nome do Paciente\n";
          cout << "2. Idade do Paciente\n";
          cout << "3. Procedimento\n";
          cout << "4. Valor Gasto\n";
          cout << "Opção: ";
          cin >> opcao;
          cout << "Digite um novo valor: ";
          cin >> novoValor;
  
          atualizarPaciente(nome, novoValor, opcao, arquivo2);
          break;
        }
        case 7: {
          vector<Produto> produtos = recuperarProdutos(arquivo);
  
          float valorTotal = totalCompraProduto(produtos, arquivo);
  
          cout << "\nValor total de compras: R$ " << valorTotal << endl;
          break;
        }
        case 8: {
          vector<Paciente> pacientes = recuperarPacientes(arquivo2);
  
          float valorTotal = totalCompraPaciente(pacientes, arquivo2);
  
          cout << "\nValor total de vendas: R$ " << valorTotal << endl;
  
          break;
        }
        case 9: {
            vector<Produto> produtos = recuperarProdutos(arquivo);
            vector<Paciente> pacientes = recuperarPacientes(arquivo2);
  
            float resultadoLucro = lucroBruto(produtos, arquivo, pacientes, arquivo2);
  
            cout << "\nLucro bruto: R$ " << resultadoLucro << endl;
            break;
          }
        case 10:
          cout << "Saindo do programa. Até mais!\n";
          break;
        default:
          cout << "Opção inválida. Tente novamente.\n";
        }
    } while (escolha != 10);
}