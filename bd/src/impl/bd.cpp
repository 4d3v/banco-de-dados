#include "../includes/extensions/extbd.h"
namespace fs = std::filesystem;

extbd::EmbeddedBD::EmbeddedBD(std::string nomeBD, std::string fullPath)
	: pFileStore{ std::make_unique<FileKeyValueStore>(nomeBD, fullPath) },
	pMemoryStore{ std::make_unique<MemoryKeyValueStore>() }
{
	pMemoryStore->loadKeys(fullPath);
}

extbd::EmbeddedBD::~EmbeddedBD() {}

const std::unique_ptr<bd::IBD> extbd::EmbeddedBD::criarVazio(std::string nomeBD)
{
	std::string baseDir{ ".publicbd" };
	if (!fs::exists(baseDir)) fs::create_directory(baseDir);

	std::string fullPath{ baseDir + "/" + nomeBD };
	if (!fs::exists(fullPath)) fs::create_directory(fullPath);

	return std::make_unique<extbd::EmbeddedBD>(nomeBD, fullPath);
}

const std::unique_ptr<bd::IBD> extbd::EmbeddedBD::carregar(std::string nomeBD)
{
	std::string baseDir{ ".publicbd" };
	std::string fullPath{ baseDir + "/" + nomeBD };
	return std::make_unique<extbd::EmbeddedBD>(nomeBD, fullPath);
}

void extbd::EmbeddedBD::setKeyValue(std::string key, std::string value)
{
	pFileStore->SetKeyValue(key, value);
	pMemoryStore->SetKeyValue(key, value);
}

std::string extbd::EmbeddedBD::getKeyValue(std::string key)
{
	return pMemoryStore->getKeyValue(key);
}

std::string extbd::EmbeddedBD::getDirectory()
{
	return pFileStore->getDirectory();
}

void extbd::EmbeddedBD::destruir()
{
	pFileStore->clear();
	pMemoryStore->clear();
}