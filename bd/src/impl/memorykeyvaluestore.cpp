#include "../includes/extensions/extbd.h"
namespace fs = std::filesystem;

extbd::MemoryKeyValueStore::MemoryKeyValueStore()
{
	pMemoryImpl = std::make_unique<MemoryImpl>();
}

extbd::MemoryKeyValueStore::~MemoryKeyValueStore() {}

void extbd::MemoryKeyValueStore::SetKeyValue(std::string key, std::string value)
{
	//pMemoryImpl->kvStore[key] = value;
	pMemoryImpl->kvStore.insert({ key,value });
}

std::string extbd::MemoryKeyValueStore::getKeyValue(std::string key)
{
	std::unordered_map<std::string, std::string>::const_iterator x = pMemoryImpl->kvStore.find(key);
	if (x == pMemoryImpl->kvStore.end()) return "Not found"; // TODO Melhorar => error handling
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

				pMemoryImpl->kvStore.insert({ key, value });
			}
		}
	}

	// Debug
	//for (auto const& x : pMemoryImpl->kvStore) std::cout << x.first << ": " << x.second << std::endl;
}

void extbd::MemoryKeyValueStore::clear()
{
	pMemoryImpl->kvStore.clear();
}
