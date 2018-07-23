// sintaxe.hpp
// Arquivo com declaração da estrutura sintaxe

// inclui este arquivo apenas uma vez
#pragma once

#include <stack>
#include <string>
#include <vector>

struct sintaxe{
	std::string empilha;
	std::string desempilha;
} typedef Sintaxe;

struct Pascalizador{
	std::stack<std::string> pilha;
	std::vector<Sintaxe> sintaxes = {{"begin","end"},{"case","end"},{"program","begin"},{"if","begin"},{"for","begin"},{"while","begin"},
	{"procedure","begin"},{"function","begin"},{"repeat", "until"}};
	char* arquivo;
	bool valido;

	void inicia(char* Endereco);
	void analiza(void);
};
