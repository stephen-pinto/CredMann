#pragma once

#include "Common.h"
#include <cryptopp/secblockfwd.h>

namespace CredMannLib
{
	namespace Security
	{
		class ICryptoProvider
		{
		public:
			std::string GenerateChecksum(const std::vector<byte_t> content);
			std::string Encrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, std::string plainText);
			std::string Decrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, std::string cipherText);
		};
	}
}