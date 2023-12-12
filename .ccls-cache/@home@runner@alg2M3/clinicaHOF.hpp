#ifndef CLINICAHOF_HPP
#define CLINICAHOF_HPP
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Usuario {
    string login;
    string senha;
};

struct Produto {
    string nomeProduto;
    double custoCompra;
    double custoVenda;
};

struct Paciente {
    string nome;
    int idade;
    string procedimento;
    double valorGasto;
};

void cadastrarUsuario(const Usuario& usuario, const string& arquivoUsuarios);
bool verificarCredenciais(const string& login, const string& senha, const string& arquivoUsuarios);
void inserirProduto(const Produto& produto, const string& arquivo);
vector<Produto> recuperarProdutos(const string& arquivo);
void exibirProdutos(const vector<Produto>& produtos);
void atualizarProduto(const string& nome, const string& novoValor, int opcao, const string& arquivo);
void inserirPaciente(const Paciente& paciente, const string& arquivo2);
void exibirPacientes(const vector<Paciente>& pacientes);
vector<Paciente> recuperarPacientes(const string& arquivo2);
void atualizarPaciente(const string& nome, const string& novoValor, int opcao, const string& arquivo2);
float totalCompraProduto(const vector<Produto>& produtos, const string& arquivo);
float totalCompraPaciente(const vector<Paciente>& pacientes, const string& arquivo2);
float lucroBruto(const vector<Produto>& produtos, const string& arquivo, const vector<Paciente>& pacientes, const string& arquivo2);
bool verificarCredenciais(const string& login, const string& senha, const vector<Usuario>& usuarios);
vector<Usuario> carregarUsuariosDoArquivo(const string& arquivoUsuarios);
void menu();
#endif