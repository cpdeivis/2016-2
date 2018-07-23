#include <iostream>
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include <termios.h>

void termios_off(void)
{
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ICANON;
	t.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
void termios_on(void)
{
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= ICANON;
	t.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

struct Editor {
	char *nome;     // nome do arquivo de entrada
	char **linhas;  // as linhas do texto
	int sAlloc; 	// Size Alloc
	int nlinhas;    // total de linhas do texto
	int lin1;       // linha do texto na 1a linha da tela
	int col1;       // coluna do texto na 1a coluna da tela
	int lin2;       // linha do texto na última linha da tela
	int col2;       // coluna do texto na última coluna da tela

	// inicia o editor
	void inicia(void)
	{
		nome = nullptr;
		sAlloc = 50;
		linhas = new char*[sAlloc]; //Alloca 10 linhas para o editor
		nlinhas = lin1 = col1 = col2 = 0;
		lin2 = 20;
	}

	// destroi o editor
	void destroi(void)
	{
		delete[] nome;
		for (auto i = 0; i < nlinhas; i++) {
			delete[] linhas[i];
		}
		delete[] linhas;
		nlinhas = lin1 = col1 = col2 = 0;
		lin2 = 20;
	}

	// desenha o texto na tela
	void desenha(void)
	{
		system("clear");
		for(auto l= lin1; l < lin2; l++){
			std::cout << linhas[l] << std::endl;
		}
	}

	// realoca as linhas do editor para nova estrutura
	void re_linhas(int s)
	{
		char **resize;
		resize = new char*[s];
		for(int i = 0, j = 0; s > sAlloc ? i < sAlloc : i < s; i++)
		{
			j = 0;
			while(linhas[i][j] != '\0')
				j++;

			std::string paradebrigar = linhas[i];
			resize[i] = new char[j+1];
			paradebrigar.copy(resize[i], paradebrigar.length(),0);
			resize[i][paradebrigar.length()] = '\0';
		}

		linhas = resize;
		sAlloc = s;
	}

	// le um arquivo 'nome' e armazena na estrutura de dados
	void le_arquivo(const char* nome)
	{
		std::string Alinha;
		std::ifstream entrada {nome};
		while(entrada.good() && !entrada.eof() && std::getline(entrada, Alinha))
		{
			//std::cout << Alinha.size() << std::endl;n
			if(nlinhas == sAlloc){
				re_linhas(sAlloc + 50); //alloca mais 10 espaços de memória
			}
			linhas[nlinhas] = new char[Alinha.length() + 1];
			Alinha.copy(linhas[nlinhas], Alinha.length(), 0);
			linhas[nlinhas][Alinha.length()] = '\0';
			//strcpy(linhas[nlinhas], Alinha.c_str());

			nlinhas++;
		}
		if(sAlloc > nlinhas)
			re_linhas(nlinhas);//Faz a alocação exata de memória

		entrada.close();
	}

	// move o texto uma linha para cima
	void move_cima(void)
	{
		if(lin1 > 0)
			lin1--;
		if((lin2 - lin1) > 20)
			lin2--;
	}

	// move o texto uma linha para baixo
	void move_baixo(void)
	{
		if(lin2 < nlinhas)
			lin2++;
		if((lin2 - lin1) > 20)
			lin1++;
	}
};

int main(void)
{
	char c;
	Editor ed;
	ed.inicia();
	ed.le_arquivo("entrada.txt");
	ed.desenha();
	termios_off();

	while(true)
	{
		c = std::getchar();
		if(c == 'q' || c == 'Q')
			break;
		// adicione outros comandos abaixo
		if(c == 'w')
			ed.move_cima();
		if(c == 's')
			ed.move_baixo();

		ed.desenha();
	}

	termios_on();
	ed.destroi();

	return 0;
}
