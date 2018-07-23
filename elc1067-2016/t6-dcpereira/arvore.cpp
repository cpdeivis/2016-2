#include <iostream>
#include <string>
#include "arvore.hpp"

void Palavra::imprime(void){
	auto itr = lista.begin();
	std::cout << palavra << " " << contagem << " (" << itr->linha << ":" << itr->coluna;
	itr++;
	while(itr != lista.end()){
		std::cout << ", " << itr->linha << ":" << itr->coluna;
		itr++;
	}
	std::cout << ")" << std::endl;
}

void No::setEsq(No *no){
	esq = no;
}
void No::setDir(No *no){
	dir = no;
}

void Arvore::emOrdem(No* no){
	if(no != NULL){
		emOrdem(no->esq);
		no->info.imprime();
		emOrdem(no->dir);
	}
}
void Arvore::preOrdem(No* no){
	if(no != NULL){
		no->info.imprime();
		preOrdem(no->esq);
		preOrdem(no->dir);
	}
}
void Arvore::posOrdem(No* no){
	if(no != NULL){
		posOrdem(no->esq);
		posOrdem(no->dir);
		no->info.imprime();
	}
}
void nozeira(No* no, std::string palavra, Posicao pos){
	no->esq = NULL;
	no->dir = NULL;
	//this->info = new Palavra();
	no->info.palavra = palavra;
	no->info.contagem = 1;
	no->info.lista.push_front(pos);
}
void Arvore::insere(std::string palavra, Posicao pos){
	//std::cout << "oi"<< std::endl;
	if(raiz == NULL){//A árvore está vazia
		//raiz = new No(palavra, pos);
		raiz = new No();
		nozeira(raiz, palavra, pos);
	}
	else
		insereNo(raiz, palavra, pos);
}
void Arvore::insereNo(No* no, std::string palavra, Posicao pos){
	//A palavra a ser inserida é alfabeticamente menor do que a palavra
	//contida no nó
	if(no->info.palavra.compare(palavra) > 0){
		if(no->esq != NULL)
			insereNo(no->esq, palavra, pos);
		else{
			//No* novo = new No(palavra, pos);
			No* novo = new No();
			nozeira(novo, palavra, pos);
			no->setEsq(novo);
		}
	}
	//A palavra a ser inserida é alfabeticamente maior do que a palavra
	//contida no nó
	else if(no->info.palavra.compare(palavra) < 0){
		if(no->dir != NULL)
			insereNo(no->dir, palavra, pos);
		else{
			//No* novo = new No(palavra, pos);
			No* novo = new No();
			nozeira(novo, palavra, pos);
			no->setDir(novo);
		}
	}
	//A palavra a ser inserida é igual a palavra contida no nó
	else{
		no->info.contagem++;
		no->info.lista.push_back(pos);
	}
}

void Arvore::destroi(void){
	if(raiz != NULL)
		destroiNo(raiz);
}
void Arvore::destroiNo(No* no){
	if(no != NULL){
		destroiNo(no->esq);
		destroiNo(no->dir);
		no->info.lista.clear();
		delete no;
	}
}
