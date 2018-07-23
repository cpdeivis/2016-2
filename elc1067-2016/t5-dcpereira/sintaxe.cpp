#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include "sintaxe.hpp"


//Era pra ter a inicialização do sintaxes aqui
//Mas deu bode
void Pascalizador::inicia(char* Endereco){
	arquivo = Endereco; //Passa o endereco do arquivo para dentro da estrutura
	valido = true; //Inicia como válida
}

void Pascalizador::analiza(void){
	std::ifstream entrada {arquivo};
	valido = entrada.good();
	if(!valido)
		return;

	std::string linha;
	std::string l_whitespace;//linha sem espaços em branco
	int size;

	while (valido && !entrada.eof() && std::getline(entrada, linha)) {
		//Verificador para desempilhar
		l_whitespace = linha;
		l_whitespace.erase(std::remove(l_whitespace.begin(),l_whitespace.end(),' '),l_whitespace.end());
		auto ith = sintaxes.begin();
		while (ith != sintaxes.end()) {
			size = (*ith).desempilha.size();
			//if(linha.find((*ith).desempilha) != std::string::npos){
			if(l_whitespace.size() >= size && l_whitespace.substr(0, size-1) == (*ith).desempilha){
				if(!pilha.empty()){
					size =  pilha.top().size();
					//if(linha.find(pilha.top()) != std::string::npos){
					if(l_whitespace.size() >= size && l_whitespace.substr(0, size-1) == pilha.top()){
						pilha.pop();
						ith = sintaxes.end();
					}
					else{
						std::cout << "Esperado: " << pilha.top() << " , recebido: " << linha << std::endl;
						valido = false;
						return;
					}
				}
				else{
					valido = false;
					return;
				}
			}
			else
				ith++;
		}

		//Verificador para empilhar
		ith = sintaxes.begin();
		while (ith != sintaxes.end()) {
			size = (*ith).empilha.size();
			//if(linha.find((*ith).empilha) != std::string::npos){
			if(l_whitespace.size() >= size && l_whitespace.substr(0, size-1) == (*ith).empilha){
				pilha.push((*ith).desempilha);
				ith = sintaxes.end();
			}
			else
				ith++;
		}
	}
}
