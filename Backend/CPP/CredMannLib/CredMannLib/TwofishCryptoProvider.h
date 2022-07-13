#pragma once

#include "Common.h"
#include "ICryptoProvider.h"
#include "BaseCryptoProvider.h"
#include <cryptopp/twofish.h>

namespace CredMannLib
{
	namespace Security
	{
		class TwofishCryptoProvider : public BaseCryptoProvider<CryptoPP::Twofish>
		{
		};
	}
}