#include <iostream>
#include "includes/cxxopts.hpp"
#include "bd.h"
using namespace std;
cxxopts::Options options(
	"bd_cli",
	"Interface de linha de comando para banco de dados"
);

void alerta()
{
	cout << "!!!" << endl;
}

bool validarNomeBD(cxxopts::ParseResult& result)
{
	if (result.count("n") == 0)
	{
		cout << "Voce deve especificar o nome do banco de dados com -n <name>" << endl;
		alerta();
		return false;
	}

	return true;
}

bool validarKey(cxxopts::ParseResult& result)
{
	if (result.count("k") == 0)
	{
		cout << "Voce deve especificar uma chave com -k <name>" << endl;
		alerta();
		return false;
	}

	return true;
}

bool validarValue(cxxopts::ParseResult& result)
{
	if (result.count("v") == 0)
	{
		cout << "Voce deve especificar um valor com -v <value>" << endl;
		alerta();
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	// Parametros da linha de comando
	options.add_options()
		("c,criar", "Criar um bd")
		("d,destruir", "Destruir um bd")
		("s,set", "Método set(), salvar chave/valor no bd")
		("g,get", "Método get(), buscar um dado no bd")
		("n,nome", "Nome do banco de dados (required)", cxxopts::value<std::string>())
		("k,key", "Chave para opções set/get", cxxopts::value<std::string>())
		("v,value", "Valor para opção set", cxxopts::value<std::string>());

	auto res = options.parse(argc, argv);

	if (res.count("c") == 1) {
		if (!validarNomeBD(res)) return 1;
		std::string nomeBD(res["n"].as<std::string>());
		unique_ptr<bd::IBD> bd(bd::PublicBD::criarVazio(nomeBD));
		return 0;
	}

	if (res.count("d") == 1) {
		if (!validarNomeBD(res)) return 1;
		std::string nomeBD(res["n"].as<std::string>());
		unique_ptr<bd::IBD> bd(bd::PublicBD::carregar(nomeBD));
		bd->destroy();
		return 0;
	}

	if (res.count("s") == 1)
	{
		if (!validarNomeBD(res)) return 1;
		if (!validarKey(res)) return 1;
		if (!validarValue(res)) return 1;

		std::string nomeBD(res["n"].as<std::string>());
		std::string k(res["k"].as<std::string>());
		std::string v(res["v"].as<std::string>());
		std::unique_ptr<bd::IBD> bd(bd::PublicBD::carregar(nomeBD));
		bd->setKeyValue(k, v);
		return 0;
	}

	if (res.count("g") == 1)
	{
		if (!validarNomeBD(res)) return 1;
		if (!validarKey(res)) return 1;

		std::string nomeBD(res["n"].as<std::string>());
		std::string k(res["k"].as<std::string>());
		std::unique_ptr<bd::IBD> bd(bd::PublicBD::carregar(nomeBD));
		cout << bd->getKeyValue(k) << endl;
		return 0;
	}

	cout << "Nenhum comando especificado" << endl;
	return 1;
}