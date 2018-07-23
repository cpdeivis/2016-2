#include <iostream>
#include <fstream>
#include <vector>

struct Aluno {
  int matricula;
  float n1, n2;
  std::string nome;
};

int main(int argc, char const *argv[]) {
  bool i = true;
  Aluno estudante;
  std::string chave;
  std::vector<Aluno> alunos;
  std::ifstream entrada {"text.txt"};

  while (entrada >> estudante.matricula) {
    entrada >> estudante.n1 >> estudante.n2;
    std::getline(entrada, estudante.nome);
    alunos.push_back(estudante);
  }

  std::cout << "Digite o(s) termo(s) de pesquisa (CASE SENSITIVE): ";
  std::getline(std::cin, chave);

  for(Aluno& discente: alunos)
    if(discente.nome.find(chave) != std::string::npos)
    {
      i = false;
      std::cout << (discente.n1 + discente.n2)/2 << " " << discente.nome << std::endl;
    }

  if(i)
    std::cout << "Nenhum resultado foi encontrado!" << std::endl;

  return 0;
}
