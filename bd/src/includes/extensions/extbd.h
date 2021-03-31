#ifndef EXTBD_H
#define EXTBD_H

#include "../bd.h"
#include <unordered_map>
#include <filesystem>
#include <fstream>

namespace extbd
{
	struct Impl
	{
		std::unordered_map<std::string, std::string> kvStore;
	};

	class MemoryKeyValueStore : public bd::Store
	{
	private:
		std::unique_ptr<Impl> pImpl;

	public:
		MemoryKeyValueStore();
		~MemoryKeyValueStore();

		virtual void SetKeyValue(std::string key, std::string value);
		virtual std::string getKeyValue(std::string key);
		virtual void loadKeys(const std::string& dir);
		virtual void clear();
	};

	class EmbeddedBD : public bd::IBD
	{
	private:
		std::string nomeBD;
		std::string fullPath;
		std::unique_ptr<extbd::MemoryKeyValueStore> pMemoryStore;

	public:
		EmbeddedBD(std::string nomeBD, std::string fullPath);
		virtual ~EmbeddedBD();

		static const std::unique_ptr<bd::IBD> criarVazio(std::string nomeBD);
		static const std::unique_ptr<bd::IBD> carregar(std::string nomeBD);

		virtual void setKeyValue(std::string key, std::string value);
		virtual std::string getKeyValue(std::string key);
		virtual std::string getDirectory();
		virtual void destroy();
	};
}

#endif // !EXTBD_H
