#pragma once

#include "Common.h"
#include "ICryptoProvider.h"
#include "BaseBlockCipherProvider.h"
#include <cryptopp/aes.h>

namespace CredMannLib
{
	namespace Security
	{
		class AESCipherProvider : public BaseBlockCipherProvider<CryptoPP::AES>
		{
		};
	}
}