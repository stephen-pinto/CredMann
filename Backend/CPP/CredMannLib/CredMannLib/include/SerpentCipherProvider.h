#pragma once

#include "Common.h"
#include "ICryptoProvider.h"
#include "BaseBlockCipherProvider.h"
#include <cryptopp/serpent.h>

namespace CredMannLib
{
	namespace Security
	{
		class SerpentCipherProvider : public BaseBlockCipherProvider<CryptoPP::Serpent>
		{
		};
	}
}