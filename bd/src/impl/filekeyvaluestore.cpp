#include "../includes/extensions/extbd.h";
namespace fs = std::filesystem;

extbd::FileKeyValueStore::FileKeyValueStore(std::string nomeBD, std::string fullPath)
{
	pFileImpl = std::make_unique<FileImpl>();
	pFileImpl->nomeBD = nomeBD;
	pFileImpl->fullPath = fullPath;
}

extbd::FileKeyValueStore::~FileKeyValueStore() {}

void extbd::FileKeyValueStore::SetKeyValue(std::string key, std::string value)
{
	std::ofstream outFile{ pFileImpl->fullPath + "/" + key + "_str.kv",
			std::ios::out | std::ios::trunc };
	if (outFile) outFile << value;
	outFile.close();
}

void extbd::FileKeyValueStore::clear()
{
	for (const auto& entry : fs::directory_iterator(pFileImpl->fullPath))
		fs::remove_all(entry.path());
	fs::remove(pFileImpl->fullPath);
}

std::string extbd::FileKeyValueStore::getDirectory()
{
	return pFileImpl->fullPath;
}
