//principal.cpp
//Programa destinado a execução da verificação de pascal simples

#include <iostream>
#include "sintaxe.hpp"

int main(int argc, char const **argv) {
	if (argc == 2) {
		Pascalizador pascal;
		pascal.inicia((char*)argv[1]);
		pascal.analiza();

		std::cout << (pascal.valido ? "Certo" : "Errado") << std::endl;
	}
	else
		std::cout << "O programa" << argv[0] << " tem paramentros invalidos!" << std::endl;

	return 0;
}
