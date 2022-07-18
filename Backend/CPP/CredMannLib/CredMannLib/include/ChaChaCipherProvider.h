#pragma once

#include "ICryptoProvider.h"
#include <cryptopp/cryptlib.h>
#include <cryptopp/eax.h>
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>
#include <cryptopp/filters.h>
#include <cryptopp/chacha.h>

namespace CredMannLib
{
	namespace Security
	{
		class ChaChaCipherProvider : public ICryptoProvider
		{
		public:

			// Inherited via ICryptoProvider
			virtual std::string GenerateChecksum(const std::vector<CryptoPP::byte> content) override;

			virtual std::string Encrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string& plainText) override;

			virtual std::string Decrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string& cipherText) override;
		};		
	}
}

