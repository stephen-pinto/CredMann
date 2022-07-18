#pragma once

#include "Common.h"
#include "ICryptoProvider.h"
#include "BaseBlockCipherProvider.h"
#include <cryptopp/twofish.h>

namespace CredMannLib
{
	namespace Security
	{
		class TwofishCipherProvider : public BaseBlockCipherProvider<CryptoPP::Twofish>
		{
		};
	}
}