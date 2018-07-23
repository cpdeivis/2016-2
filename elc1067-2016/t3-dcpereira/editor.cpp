// editor.cpp
// Arquivo com funções da estrutura Editor
//
// The MIT License (MIT)
//
// Copyright (c) 2016 João V. Lima, UFSM
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>
#include <fstream>
#include <functional>

#include "editor.hpp"
#include "Tela.hpp"

// Utiliza as funções de tela
using namespace tela;

void Editor::inicia(void)
{
	// esta função está pronta
	tela.inicia(600, 400, "Editor de texto");
	lin1 = 0;
	col1 = 0;
	lin2 = tela.tam.alt / fonte.alt;
	col2 = tela.tam.larg / fonte.larg;
	colcur = 0;
	lincur = 0;

	// apenas calcula o tamanho de uma letra em pixels
	const char* texto { "A" } ;
	fonte = tela.tamanho_texto(texto);
}

void Editor::destroi(void)
{
	//delete texto;
	lin1 = 0;
	col1 = 0;
	lin2 = 0;
	col2 = 0;
	colcur = 0;
	lincur = 0;
	tela.finaliza();
}

void Editor::desenha(void)
{
	Cor preto = {0.0, 0.0, 0.0};
	Ponto pt;
	tela.limpa();
	tela.cor(preto);

	for(auto i = lin1; i < nlinhas && i < lin2-lin1; i++){
		std::string imprime = " ";

		pt.x = 1;
		pt.y = (i - lin1)*fonte.alt + 1;
		if(i < linhas.size())
		{
			if(linhas[i].length() < col2)
			{
				if(col1 < linhas[i].length())
					imprime = linhas[i].substr(col1, linhas[i].length()-col1);
			}
		}
		if(col1 < linhas[i].size())
			imprime = linhas[i].substr(col1, col2-col1);
		tela.texto(pt, imprime.c_str());
	}
	desenha_cursor();
}

void Editor::atualiza(void)
{
	// TODO terminar
	desenha();
	tela.mostra();
	tela.espera(30);
}

void Editor::desenha_cursor(void)
{
	// TODO terminar
	Cor preto = {0.0, 0.0, 0.0};
	Ponto pt1, pt2;

	/* posicao x (horizontal) do cursor */
	pt1.x = fonte.larg*colcur + 1;
	/* posicao y (vertical) do cursor */
	pt1.y = lincur * fonte.alt;
	pt2.x = pt1.x;
	pt2.y = pt1.y + fonte.alt;
	tela.cor(preto);
	tela.linha(pt1, pt2);
}

bool Editor::processa_comandos(void)
{
	// TODO terminar
	int tecla = tela.tecla();
	int modificador = tela.tecla_modif();
	/* Commands: */
	if(modificador & ALLEGRO_KEYMOD_CTRL)
	{
		switch (tecla) {
			case ALLEGRO_KEY_Q:
				std::cout << "CTRL+Q SAIR\n";
				tecla = 0;
				return false;
			case ALLEGRO_KEY_S:
				std::cout << "CTRL+S SALVAR e PARAR DE EDITAR\n";
				tecla = 0;
				salvar();
				estado = Estado::nada;
				break;
			case ALLEGRO_KEY_E:
				std::cout << "CTRL+E EDITAR\n";
				tecla = 0;
				estado = Estado::editando;
				break;
			case ALLEGRO_KEY_J:
				std::cout << "CTRL+J GRUDAR (JUNTAR) LINHAS\n";
				tecla = 0;
				gruda_linha();
				break;
			case ALLEGRO_KEY_N:
				std::cout << "CTRL+N QUEBRAR LINHAS\n";
				tecla = 0;
				quebra_linha();
				break;
		}
	}
	switch (tecla) {
		case ALLEGRO_KEY_LEFT:
			move_esq();
			break;
		case ALLEGRO_KEY_RIGHT:
			move_dir();
			break;
		case ALLEGRO_KEY_UP:
			move_cima();
			break;
		case ALLEGRO_KEY_DOWN:
			move_baixo();
			break;
		default:
			if(estado == Estado::editando){
				switch (tecla) {
					case ALLEGRO_KEY_BACKSPACE:
						remove_char();
						break;
					case ALLEGRO_KEY_DELETE:
						deleta_char();
						break;
					case ALLEGRO_KEY_SPACE:
						insere_char(' ');
						break;
					default:
						if((tecla >= ALLEGRO_KEY_A) && (tecla <= ALLEGRO_KEY_Z))
							insere_char(static_cast<char>(tecla + 96));
						break;
				}
			}
			break;
	}

	return true;
}

void Editor::le_arquivo(const char* nome){
	std::ifstream entrada {nome};
	if(entrada.is_open()){
		std::string linha;
		while(std::getline(entrada, linha)){
			linhas.push_back(linha);
		}
		std::cout << linhas.size() << std::endl;
		entrada.close();
	}
}

void Editor::move_cima(void)
{
	if(lincur > 0) {
		lincur--;
		if (lincur < lin1){
			lin1--;
			lin2--;
		}
	}
}

void Editor::move_baixo(void)
{
	lincur++;
	if (lincur > lin2){
		lin1++;
		lin2++;
	}
}

void Editor::move_esq(void)
{
	if(colcur > 0){
		colcur--;
		if (colcur < col1){
			col1--;
			col2--;
		}
	}
}

void Editor::move_dir(void)
{
	colcur++;
	if (colcur > col2){
		col1++;
		col2++;
	}
}

void Editor::insere_char(const char c)
{
	auto i = 0;
	auto dif = 0;
	auto size = 0;
	if(lincur >= linhas.size()){
		dif = lincur - linhas.size();
		size = linhas.size();
		do{
			std::string nLinha = " ";
			std::cout << dif << std::endl;
			std::vector<std::string>::iterator nth = linhas.begin() + size + i;
			linhas.insert(nth, nLinha);
			i++;
		} while(i < dif);
	}
	if(colcur >= linhas[lincur].size()){
		dif = colcur - linhas[lincur].size();
		i = 0;
		size = linhas[lincur].size();
		do{
			int sth = size + i;
			linhas[lincur].insert(sth, " ");
			i++;
		} while(i < dif);

	}
	std::string& linha = std::ref(linhas[lincur]);
	linha.insert(colcur, 1, c);
	move_dir();
}

void Editor::remove_char(void)
{
	if (colcur == 0 && lincur > 0){
		lincur--;
		colcur = linhas[lincur].size();
		gruda_linha();
	}
	else if(colcur > 0 && colcur <= linhas[lincur].size()){
		std::string& linha = std::ref(linhas[lincur]);
		linha.erase(linha.begin()+colcur-1);
		move_esq();
	}
}
void Editor::deleta_char(void)
{
	if (colcur >= linhas[lincur].size() && lincur < linhas.size()){
		gruda_linha();
	}
	else if(colcur < linhas[lincur].size()){
		std::string& linha = std::ref(linhas[lincur]);
		linha.erase(linha.begin()+colcur);
	}
}

void Editor::gruda_linha(void)
{
	if(lincur != linhas.size())
	{
		std::string concat = linhas[lincur + 1];
		linhas[lincur].append(concat);
		std::vector<std::string>::iterator nth = linhas.begin() + lincur + 1;
		linhas.erase(nth);
		nlinhas--;
	}
}

void Editor::quebra_linha(void)
{
	std::vector<std::string>::iterator nth = linhas.begin() + lincur + 1;
	std::string nstr(" ");
	if(linhas[lincur].size() > colcur){
		nstr = linhas[lincur].substr(colcur, linhas[lincur].size() - colcur);
		linhas[lincur].erase(colcur, linhas[lincur].size() - colcur);
	}
	linhas.insert(nth, nstr);
	nlinhas++;
}

void Editor::salvar(void)
{
	std::ofstream fileText ("entrada.txt");
	if(fileText.is_open()){
		for(auto i = 0; i < linhas.size(); i++)
		{
			std::string strSave = linhas[i];
			strSave.append("\n");
			fileText << strSave;
		}

		fileText.close();
	}
	else
		std::cout << "Não foi possível abrir o arquivo!" << std::endl;
}
