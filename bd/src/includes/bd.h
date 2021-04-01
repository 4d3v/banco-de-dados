#ifndef BD_H
#define BD_H

#include <memory>
#include <string>

namespace bd
{
	class Store
	{
	public:
		Store() = default;
		virtual ~Store() = default;

	};

	class FStore : public Store
	{
	public:
		FStore() = default;
		virtual ~FStore() = default;
		virtual void SetKeyValue(std::string key, std::string value) = 0;
		virtual std::string getDirectory() = 0;
		virtual void clear() = 0;
	};

	class MStore : public Store
	{
	public:
		MStore() = default;
		virtual ~MStore() = default;
		virtual void SetKeyValue(std::string key, std::string value) = 0;
		virtual std::string getKeyValue(std::string key) = 0;
		virtual void loadKeys(const std::string& dir) = 0;
		virtual void clear() = 0;
	};

	class IBD
	{
	public:
		IBD() = default;
		virtual ~IBD() = default;

		virtual void setKeyValue(std::string key, std::string value) = 0;
		virtual std::string getKeyValue(std::string key) = 0;
		virtual std::string getDirectory() = 0;
		virtual void destruir() = 0;
	};
}

#endif // !BD_H
