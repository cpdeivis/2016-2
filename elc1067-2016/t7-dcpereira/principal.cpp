#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>

struct Vertice {
	std::string nome;
	std::list<std::string> adj;
};

void splita(std::string **vetor, std::string *linha){
	int pos = (*linha).find(' ');
	(*vetor)[0] = (*linha).substr(0, pos);
	(*vetor)[1] = (*linha).substr(pos + 1, (*linha).length() -1);
}
void insereGrafo(std::map<std::string, Vertice> *grafo, std::ifstream *entrada){
	std::string *vetor = new std::string[2];
	std::string linha;
	unsigned int ver, are;
	//pega a primeira linha com a quantidade de vertices e arestas
	std::getline(*entrada, linha);
	splita(&vetor, &linha);
	//converte as strings para int
	ver = std::stoi(vetor[0]);
	are = std::stoi(vetor[1]);
	if(!(ver == 0 && are != 0)){
		while(!(*entrada).eof() && std::getline(*entrada, linha)){
			splita(&vetor, &linha);
			if(ver != 0){
				//Insere os Vertices
				(*grafo)[vetor[0]] = Vertice();
				(*grafo)[vetor[0]].nome = vetor[1];
				ver--;
			}
			else if(are != 0){
				(*grafo)[vetor[0]].adj.push_back(vetor[1]);
				(*grafo)[vetor[1]].adj.push_back(vetor[0]);
				are--;
			}
			//else
				//throw std::runtime_error{"Arquivo com mais elementos do que o informado!"};
		}
		delete[] vetor;
		if(ver > 0)
			throw std::runtime_error{"O arquivo não possui todos os vertices informados!"};
		if(are > 0)
			throw std::runtime_error{"O arquivo não possui todas as arestas informadas!"};
	}
	else{
		delete[] vetor;
		throw std::runtime_error{"Verices em 0 e Arestas diferentes de 0"};
	}
}
void imprimeGrafo(std::map<std::string, Vertice> *grafo){
	auto ith = (*grafo).begin();
	while(ith != (*grafo).end()){
		std::cout << ith->first << " -> ";
		auto Ith = ith->second.adj.begin();
		while(Ith != ith->second.adj.end()){
			std::cout << *Ith << " ";
			Ith++;
		}
		std::cout << std::endl;
		ith++;
	}
}

int main(int argc, char **argv){
	try{
		if (argc == 2){
			std::ifstream entrada {argv[1]};
			if(!entrada.good()){
				throw std::runtime_error{"Na1 foi possivel abrir o arquivo"};
			}
			std::map<std::string, Vertice> grafo;
			insereGrafo(&grafo, &entrada);
			imprimeGrafo(&grafo);
		}
		else
			throw std::runtime_error{"Argumentos inválidos"};
	}
	catch(std::exception& e){
		std::cout << "ERRO: " << e.what() << std::endl;
	}

	return 0;
}
