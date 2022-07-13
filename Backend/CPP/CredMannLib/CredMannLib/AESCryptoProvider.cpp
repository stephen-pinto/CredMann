#include "pch.h"
#include "AESCryptoProvider.h"
#include "Util.h"
#include <cryptopp/aes.h>
#include <cryptopp/sha.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/eax.h>
#include <cryptopp/base64.h>
#include <cryptopp/xts.h>
#include <cryptopp/osrng.h>

using namespace std;
using namespace CryptoPP;
using namespace CredMannLib::Util;
using namespace CredMannLib::Security;

string AESCryptoProvider::GenerateChecksum(const vector<byte> content)
{
	string hash;
	SHA256 sha256;
	VectorSource vsrc(content, true,
		new HashFilter(sha256,
			new Base64Encoder(
				new StringSink(hash))));

	return hash;
}

string AESCryptoProvider::Encrypt(const SecByteBlock& key, const SecByteBlock& iv, const string& plainText)
{
	string encrText;

	try
	{
		EAX<AES>::Encryption encr;
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

string AESCryptoProvider::Decrypt(const SecByteBlock& key, const SecByteBlock& iv, const string& cipherText)
{
	string actText;

	try
	{
		EAX<AES>::Decryption decr;
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
