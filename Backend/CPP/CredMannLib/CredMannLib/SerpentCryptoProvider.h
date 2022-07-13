#pragma once

#include "Common.h"
#include "ICryptoProvider.h"
#include "BaseCryptoProvider.h"
#include <cryptopp/serpent.h>

namespace CredMannLib
{
	namespace Security
	{
		class SerpentCryptoProvider : public BaseCryptoProvider<CryptoPP::Serpent>
		{
		};
	}
}