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
			
			virtual std::string GenerateChecksum(const std::vector<CryptoPP::byte> content) = 0;

			virtual std::string Encrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string& plainText) = 0;

			virtual std::string Decrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string& cipherText) = 0;
		};
	}
}