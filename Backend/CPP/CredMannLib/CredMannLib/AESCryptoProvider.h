#pragma once

#include "Common.h"
#include "ICryptoProvider.h"

namespace CredMannLib
{
	namespace Security
	{
		class AESCryptoProvider : public ICryptoProvider
		{
		public:

			// Inherited via ICryptoProvider
			virtual std::string GenerateChecksum(const std::vector<CryptoPP::byte> content) override;

			virtual std::string Encrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string& plainText) override;

			virtual std::string Decrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string& cipherText) override;
		};
	}
}