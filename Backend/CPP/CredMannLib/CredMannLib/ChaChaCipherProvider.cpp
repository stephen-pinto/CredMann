#include "pch.h"
#include "ChaChaCipherProvider.h"
#include <iostream>

using namespace CredMannLib::Security;
using namespace CryptoPP;
using namespace std;

string ChaChaCipherProvider::GenerateChecksum(const vector<CryptoPP::byte> content)
{
	string hash;
	SHA256 sha256;
	VectorSource vsrc(content, true,
		new HashFilter(sha256,
			new Base64Encoder(
				new StringSink(hash))));

	return hash;
}

string ChaChaCipherProvider::Encrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const string& plainText)
{
	string encrText;

	try
	{
		ChaCha::Encryption encr;
		encr.SetKeyWithIV(key, key.size(), iv, iv.size());
		StringSource str(plainText, true,
			new StreamTransformationFilter(
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

string ChaChaCipherProvider::Decrypt(const CryptoPP::SecByteBlock& key, const CryptoPP::SecByteBlock& iv, const string& cipherText)
{
	string actText;

	try
	{
		ChaCha::Decryption decr;
		decr.SetKeyWithIV(key, key.size(), iv, iv.size());
		StringSource str(cipherText, true,
			new StreamTransformationFilter(
				decr,
				new StringSink(actText)
			)
		);
	}
	catch (const Exception& e)
	{
		cerr << e.what() << '\n';
		throw e;
	}

	return actText;
}