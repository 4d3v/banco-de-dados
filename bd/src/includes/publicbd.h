#ifndef PUBLICBD_H
#define PUBLICBD_H

#include "bd.h"

namespace bd
{
	class PublicBD
	{
	public:
		PublicBD();
		static std::unique_ptr<bd::IBD> criarVazio(std::string& nomeBD);
		static std::unique_ptr<bd::IBD> carregar(std::string& nomeBD);
	};
}

#endif // !1
