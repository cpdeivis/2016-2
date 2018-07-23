#include <iostream>
#include <string>
#include <fstream>
#include <vector>
//#include <utility>
#include "arvore.hpp"

const std::vector<char> especial {'.', ',', '?', '/', '|', '\\', '!', ':',
	';', '(', ')', '{', '}', '[', ']', '=', '+', '-', '_', '<', '>', '#',
	'$', '%', '&', '*', '~', '^', '`', ' ', '\'', '"'};
bool pontuacao(char c){
	bool achou = false;
	auto ith = especial.begin();
	while(!achou && ith != especial.end()){
		if(c == *ith)
			achou = true;
		ith++;
	}
	return achou;
}
void arrumaLinha(std::string * linha, bool dir, int * pos){
	if(!(*linha).empty()){
		if(dir){
			if(pontuacao((*linha).at(0))){
				(*linha) = (*linha).substr(1);
				(*pos)++;
				arrumaLinha(linha, 1, pos);
			}
			arrumaLinha(linha, 0, pos);
		}
		else{
			int length = (*linha).length() - 1;
			if(pontuacao((*linha).at(length))){
				(*linha) = (*linha).substr(0, length);
				arrumaLinha(linha, 0, pos);
			}
		}
		return;
	}
	return;
}

void processaLinha(std::string linha, Arvore * bonsai, int lin){
	//size = tamanho da string, posI = posição inicial
	int posI = 0, posE = linha.length() - 1;
	std::string cortando;

	while(posE != -1){
		posE = linha.find(' ', posI);
		cortando = linha.substr(posI, posE - posI);
		if(!cortando.empty()){
			arrumaLinha(&cortando, 1, &posI);
		}
		if(!cortando.empty()){
			for(char& c : cortando) {
				c = std::tolower(c);
			}
			bonsai->insere(cortando, {lin, (posI++) + 1});
		}
		posI = posE + 1;
	}
	//std::cout << size << std::endl;
}

int main(int argc, char const **argv) {
	if (argc == 2) {
		std::ifstream entrada {argv[1]};
		if(!entrada.good()){
			std::cout << "Na1 foi possivel abrir o arquivo " << argv[1] << std::endl;
			return 0;
		}
		std::string linha;
		Arvore arbusto;
		arbusto.raiz = NULL;
		//arbusto.insere("palavra", {0,0});
		//arbusto.insere("palavra", {1,0});
		int lin = 1;
		std::cout << std::endl;
		while (!entrada.eof() && std::getline(entrada, linha)){
			processaLinha(linha, &arbusto, lin);
			lin++;
		}
		if(arbusto.raiz != NULL){
			arbusto.emOrdem(arbusto.raiz);
			arbusto.destroi();
		}
		else
			std::cout << "Nada foi indexado!" << std::endl;

	}
	else
		std::cout << "O programa" << argv[0] << " tem paramentros invalidos!" << std::endl;
	return 0;
}
