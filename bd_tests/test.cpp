#include "pch.h"
#include "bd.h"
#include <filesystem>
namespace fs = std::filesystem;

/*
 * Testes de gerenciamento
 */
TEST(GerenciamentoBD, CriarBancoDeDadosVazio)
{
	/*
	 * 1. Como administrador do banco de dados
	 * 2. Necessito criar um novo banco de dados vazio
	 * 3. Para que possa guardar e ler dados
	 */
	std::string nomeBD{ "testebd" };
	std::unique_ptr<bd::IBD> bd{ bd::PublicBD::criarVazio(nomeBD) };

	/*
	 * Requisitos para sucesso:
	 * 1. bd é uma referência válida para IBD
	 * 2. bd possui pasta criada no diretório com nome == nomeBD
	 */
	EXPECT_TRUE(fs::is_directory(fs::status(bd->getDirectory())));

	const auto& p = fs::directory_iterator(bd->getDirectory());
	EXPECT_TRUE(p == end(p)); // Atualmente não há diretórios dentro de testebd

	// excluindo dir depois dos testes
	bd->destruir();
	EXPECT_FALSE(fs::is_directory(fs::status(bd->getDirectory())));

	/*
	 * REFS
	 * https://en.cppreference.com/w/cpp/filesystem/is_directory
	 * https://en.cppreference.com/w/cpp/filesystem/directory_iterator
	 */
}

TEST(GerenciamentoBD, CarregarBancoDeDados)
{
	/*
	 * 1. Como usuário do banco de dados
	 * 2. Necessito criar uma referência para um banco de dados existente
	 * 3. Para que possa guardar e ler dados
	 */
	std::string nomeBD{ "testebd" };
	std::unique_ptr<bd::IBD> bd{ bd::PublicBD::criarVazio(nomeBD) };
	std::unique_ptr<bd::IBD> bd2{ bd::PublicBD::carregar(nomeBD) };

	/*
	 * Requisitos para sucesso:
	 * 1. bd é uma referência válida para IBD
	 * 2. bd possui pasta criada no diretório com nome == nomeBD
	 */
	EXPECT_TRUE(fs::is_directory(fs::status(bd2->getDirectory())));

	const auto& p = fs::directory_iterator(bd2->getDirectory());
	EXPECT_TRUE(p == end(p)); // Atualmente não há diretórios dentro de testebd

	bd->destruir();
	EXPECT_FALSE(fs::is_directory(fs::status(bd2->getDirectory())));
}

TEST(GerenciamentoKeyValues, GuardarLerKeyValue)
{
	/*
	 * 1. Como usuário do banco de dados
	 * 2. Necessito guardar e ler dado no formato chave/valor (key/value)
	 * 3. Para que possa manter dados para futuro uso
	*/
	std::string key{ "testechave" };
	std::string value{ "testevalor" };
	std::string nomeBD{ "testebd" };
	std::unique_ptr<bd::IBD> bd{ bd::PublicBD::criarVazio(nomeBD) };

	/*
	 * Requisitos para sucesso:
	 * 1. método setKeyValue deve salvar o valor dentro do arquivo ${key}_str.kv
	 * e.g arquivo: testechave_str.kv | valor guardado: testevalor
	 * 2. método getKeyValue deve retornar o mesmo valor da variável value
	 */
	bd->setKeyValue(key, value);
	EXPECT_EQ(value, bd->getKeyValue(key));

	// fazendo loop e deletando todos arquivos antes de deletar banco de dados
	for (const auto& entry : fs::directory_iterator(bd->getDirectory()))
		fs::remove_all(entry.path());

	bd->destruir();
}
