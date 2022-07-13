#pragma once

#include "ICryptoProvider.h"
#include <cryptopp/cryptlib.h>
#include <cryptopp/eax.h>
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>

namespace CredMannLib
{
	namespace Security
	{
		template<typename T>
		class BaseCryptoProvider : public ICryptoProvider
		{
		public:

			// Inherited via ICryptoProvider
			virtual std::string GenerateChecksum(const std::vector<CryptoPP::byte> content) override;

			virtual std::string Encrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string& plainText) override;

			virtual std::string Decrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string& cipherText) override;
		};

		template<typename T>
		std::string BaseCryptoProvider<T>::GenerateChecksum(const std::vector<CryptoPP::byte> content)
		{
			using namespace CryptoPP;
			using namespace std;

			string hash;
			SHA256 sha256;
			VectorSource vsrc(content, true,
				new HashFilter(sha256,
					new Base64Encoder(
						new StringSink(hash))));

			return hash;
		}

		template<typename T>
		std::string BaseCryptoProvider<T>::Encrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string& plainText)
		{
			using namespace CryptoPP;
			using namespace std;
			string encrText;

			try
			{
				EAX_Final<T, true> encr;
				//EAX<AES>::Encryption encr;
				encr.SetKeyWithIV(key, key.size(), iv, iv.size());
				StringSource str(plainText, true,
					new AuthenticatedEncryptionFilter(
						encr,
						new StringSink(encrText)
					)
				);
			}
			catch (const Exception& e)
			{
				cerr << e.what() << '\n';
				throw e;
			}

			return encrText;
		}

		template<typename T>
		std::string BaseCryptoProvider<T>::Decrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const std::string& cipherText)
		{
			using namespace CryptoPP;
			using namespace std;
			string actText;

			try
			{
				EAX_Final<T, false> decr;
				//EAX<AES>::Decryption decr;
				decr.SetKeyWithIV(key, key.size(), iv, iv.size());
				StringSource str(cipherText, true,
					new AuthenticatedDecryptionFilter(
						decr,
						new StringSink(actText)
					)
				);
			}
			catch (const Exception& e)
			{
				std::cerr << e.what() << '\n';
				throw e;
			}

			return actText;
		}
	}
}

