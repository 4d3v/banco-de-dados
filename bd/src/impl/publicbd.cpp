#include "../includes/publicbd.h"
#include "../includes/extensions/extbd.h"

bd::PublicBD::PublicBD() {}

std::unique_ptr<bd::IBD> bd::PublicBD::criarVazio(std::string& nomeBD)
{
	return extbd::EmbeddedBD::criarVazio(nomeBD);
}

std::unique_ptr<bd::IBD> bd::PublicBD::carregar(std::string& nomeBD)
{
	return extbd::EmbeddedBD::carregar(nomeBD);
}
