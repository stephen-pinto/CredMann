#include "pch.h"
#include "SerpentCryptoProvider.h"
#include "Util.h"
#include <cryptopp/sha.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/eax.h>
#include <cryptopp/base64.h>
#include <cryptopp/osrng.h>
#include <cryptopp/serpent.h>

using namespace std;
using namespace CryptoPP;
using namespace CredMannLib::Util;
using namespace CredMannLib::Security;

string SerpentCryptoProvider::GenerateChecksum(const vector<byte> content)
{
	string hash;
	SHA256 sha256;
	VectorSource vsrc(content, true,
		new HashFilter(sha256,
			new Base64Encoder(
				new StringSink(hash))));

	return hash;
}

string SerpentCryptoProvider::Encrypt(const SecByteBlock& key, const SecByteBlock& iv, const string& plainText)
{
	string encrText;

	try
	{
		EAX<Serpent>::Encryption encr;
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

string SerpentCryptoProvider::Decrypt(const SecByteBlock& key, const SecByteBlock& iv, const string& cipherText)
{
	string actText;

	try
	{
		EAX<Serpent>::Decryption decr;
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
