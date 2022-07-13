#pragma once

#include "Common.h"
#include "ICryptoProvider.h"
#include <cryptopp/aes.h>
#include "BaseCryptoProvider.h"

namespace CredMannLib
{
	namespace Security
	{
		class AESCryptoProvider : public BaseCryptoProvider<CryptoPP::AES>
		{
		};
	}
}