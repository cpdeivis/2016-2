#include <string>
#include <list>

struct Posicao {
	int linha;
	int coluna;
};
struct Palavra {
	std::string palavra; // a palavra
	int contagem;        // palavras encontradas
	std::list<Posicao> lista; // lista com a posição de cada palavra

	void imprime(void);
};

struct No{
	Palavra info;
	struct No* esq;
	struct No* dir;

	//No(std::string palavra, Posicao pos);
	void setEsq(No *no);
	void setDir(No *no);
};

struct Arvore{
	No * raiz;

	void insere(std::string palavra, Posicao pos);
	void insereNo(No* no, std::string palavra, Posicao pos);
	void destroi(void);
	void destroiNo(No* no);

	void emOrdem(No* no);//Primeiro a sub-árvore esquerda, depois a raiz, e finalmente a sub-árvore direita
	void preOrdem(No* no);//Primeiro a raiz, depois a sub-árvore esquerda, e finalmente a sub-árvore direita
	void posOrdem(No* no);//Primeiro a sub-árvore esquerda, depois a sub-árvore direita, e finalmente a raiz
};
