#include "../includes/extensions/extbd.h"
namespace fs = std::filesystem;

extbd::MemoryKeyValueStore::MemoryKeyValueStore() { pImpl = std::make_unique<Impl>(); }

extbd::MemoryKeyValueStore::~MemoryKeyValueStore() {}

void extbd::MemoryKeyValueStore::SetKeyValue(std::string key, std::string value)
{
	//pImpl->kvStore[key] = value;
	pImpl->kvStore.insert({ key,value });
}

std::string extbd::MemoryKeyValueStore::getKeyValue(std::string key)
{
	std::unordered_map<std::string, std::string>::const_iterator x = pImpl->kvStore.find(key);
	if (x == pImpl->kvStore.end()) return "Not found"; // TODO Melhorar => error handling
	return x->second;
}

void extbd::MemoryKeyValueStore::loadKeys(const std::string& dir)
{
	// carregando arquivos com extensao .kv
	for (auto& x : fs::directory_iterator(dir))
	{
		if (x.exists() && x.is_regular_file())
		{
			// verificando se arquivo possui .kv, se sim abrir arquivo
			if (".kv" == x.path().extension())
			{
				std::string keyCompleta{ x.path().filename().string() };
				std::string key{ keyCompleta.substr(0, keyCompleta.size() - 7) };
				// e.g keyCompleta => abc_str.kv | key => abc

				std::ifstream inFile{ x.path() };
				std::string value{};
				inFile.seekg(0, std::ios::end);
				value.reserve(inFile.tellg());
				inFile.seekg(0, std::ios::beg);
				value.assign(std::istreambuf_iterator<char>(inFile),
					std::istreambuf_iterator<char>());

				pImpl->kvStore.insert({ key, value });
			}
		}
	}

	// Debug
	//for (auto const& x : pImpl->kvStore) std::cout << x.first << ": " << x.second << std::endl;
}

void extbd::MemoryKeyValueStore::clear()
{
	pImpl->kvStore.clear();
}
