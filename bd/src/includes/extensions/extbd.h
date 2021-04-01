#ifndef EXTBD_H
#define EXTBD_H

#include "../bd.h"
#include <unordered_map>
#include <filesystem>
#include <fstream>

namespace extbd
{
	struct MemoryImpl
	{
		std::unordered_map<std::string, std::string> kvStore;
	};

	struct FileImpl
	{
		std::string nomeBD;
		std::string fullPath;
	};

	class FileKeyValueStore : public bd::FStore
	{
	private:
		std::unique_ptr<FileImpl> pFileImpl;

	public:
		FileKeyValueStore(std::string nomeBD, std::string fullPath);
		~FileKeyValueStore();

		virtual void SetKeyValue(std::string key, std::string value);
		virtual std::string getDirectory();
		virtual void clear();

	};

	class MemoryKeyValueStore : public bd::MStore
	{
	private:
		std::unique_ptr<MemoryImpl> pMemoryImpl;

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
		std::unique_ptr<MemoryKeyValueStore> pMemoryStore;
		std::unique_ptr<FileKeyValueStore> pFileStore;

	public:
		EmbeddedBD(std::string nomeBD, std::string fullPath);
		virtual ~EmbeddedBD();

		static const std::unique_ptr<bd::IBD> criarVazio(std::string nomeBD);
		static const std::unique_ptr<bd::IBD> carregar(std::string nomeBD);

		virtual void setKeyValue(std::string key, std::string value);
		virtual std::string getKeyValue(std::string key);
		virtual std::string getDirectory();
		virtual void destruir();
	};
}

#endif // !EXTBD_H
