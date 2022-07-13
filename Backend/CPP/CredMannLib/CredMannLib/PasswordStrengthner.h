#pragma once

#include "Common.h"
#include <cryptopp/cryptlib.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include "SaltGenerator.h"

#define DEFAULT_ITERATIONS 50000

namespace CredMannLib
{
	namespace Password
	{
		class PasswordStrengthner
		{
		public:
			CryptoPP::SecByteBlock GenerateKey_PKCS5_PBKDF2(const CryptoPP::SecByteBlock& password, const CryptoPP::SecByteBlock& salt, unsigned int iterations = DEFAULT_ITERATIONS);
		};
	}
}

