#pragma once

#include <iostream>
#include <tuple>
#include "../CredMannLib/PasswordStrengthner.h"
#include "../CredMannLib/SaltGenerator.h"
#include "../CredMannLib/Util.h"
#include "../CredMannLib/AESCipherProvider.h"
#include "../CredMannLib/SerpentCipherProvider.h"
#include "../CredMannLib/BaseBlockCipherProvider.h"
#include "../CredMannLib/TwofishCipherProvider.h"

using namespace CredMannLib::Password;
using namespace CredMannLib::Security;
using namespace CredMannLib::Util;
using namespace CryptoPP;
using namespace std;

#define KEY_SIZE 32
#define TEST_ITERATIONS 1024

void Test1();
void Test2();
void Test3();
void Test4();
void Test5();

int Run(int argc, char** argv)
{
	Test5();
	return 0;
}

tuple<SecByteBlock, string> GenKey(SecByteBlock& pass, SecByteBlock& iv)
{
	PasswordStrengthner ps;
	SecByteBlock key = ps.GenerateKey_PKCS5_PBKDF2(pass, iv, TEST_ITERATIONS);
	string result;
	HexEncoder encoder(new StringSink(result));
	encoder.Put(key, key.size());
	encoder.MessageEnd();
	return tuple<SecByteBlock, string>(key, result);
}

tuple<SecByteBlock, string> GenKey2(SecByteBlock& pass, SecByteBlock& iv)
{
	PasswordStrengthner ps;
	SecByteBlock key = ps.GenerateKey_PKCS5_PBKDF2(pass, iv, DEFAULT_ITERATIONS);
	string result;
	UtilServices serv;
	result = serv.HexEncode(key);
	return tuple<SecByteBlock, string>(key, result);
}

void Test1()
{
	
	SaltGenerator sg;
	SecByteBlock iv = sg.GenerateIV(KEY_SIZE);
	string password1 = "somepass";
	SecByteBlock pass1((const CryptoPP::byte*)password1.data(), password1.length());	
	auto comb1 = GenKey(pass1, iv);

	string password2 = "otherpass";
	SecByteBlock pass2((const CryptoPP::byte*)password2.data(), password2.length());
	auto comb2 = GenKey(pass2, iv);

	string password3 = "somepass ";
	SecByteBlock pass3((const CryptoPP::byte*)password3.data(), password3.length());
	auto comb3 = GenKey(pass3, iv);
	_PRINT("1.: " << get<1>(comb1));
	_PRINT("2.: " << get<1>(comb2));
	_PRINT("3.: " << get<1>(comb3));
}

void Test2()
{
	SaltGenerator sg;
	SecByteBlock iv = sg.GenerateIV(KEY_SIZE);
	string password1 = "somepass";
	SecByteBlock pass1((const CryptoPP::byte*)password1.data(), password1.length());
	auto comb1 = GenKey(pass1, iv);

	string password2 = "somepass";
	SecByteBlock pass2((const CryptoPP::byte*)password2.data(), password2.length());
	auto comb2 = GenKey2(pass2, iv);
	_PRINT("1.: " << get<1>(comb1));
	_PRINT("2.: " << get<1>(comb2));

	_PRINT("\nOriginal");
	for (int i = 0; i < 20; i++)
	{
		std::cout << get<0>(comb2)[i];
	}

	UtilServices serv;
	SecByteBlock decodedKey = serv.HexDecode(get<1>(comb2));

	_PRINT("\nDecoded");
	for (int i = 0; i < 20; i++)
	{
		std::cout << decodedKey[i];
	}
}

void Test3()
{
	SaltGenerator sg;
	SecByteBlock iv = sg.GenerateIV(KEY_SIZE);
	SecByteBlock salt = sg.GenerateIV(KEY_SIZE);
	string password1 = "somepass";
	SecByteBlock pass1((const CryptoPP::byte*)password1.data(), password1.length());
	auto comb1 = GenKey(pass1, salt);

	AESCipherProvider provider;
	string origText = "This is some plain text which we wish to encrypt";
	string encrText = provider.Encrypt(get<0>(comb1), iv, "This is some plain text which we wish to encrypt...");
	string decrText = provider.Decrypt(get<0>(comb1), iv, encrText);

	_PRINT("Encr. Text: " << encrText << "|||");
	_PRINT("Decr. Text: " << decrText << "|||");
}

void Test4()
{
	SaltGenerator sg;
	SecByteBlock iv = sg.GenerateIV(KEY_SIZE);
	SecByteBlock salt = sg.GenerateIV(KEY_SIZE);
	string password1 = "somepass";
	SecByteBlock pass1((const CryptoPP::byte*)password1.data(), password1.length());
	auto comb1 = GenKey(pass1, salt);

	SerpentCipherProvider provider;
	string origText = "This is some plain text which we wish to encrypt";
	string encrText = provider.Encrypt(get<0>(comb1), iv, "This is some plain text which we wish to encrypt...");
	string decrText = provider.Decrypt(get<0>(comb1), iv, encrText);

	_PRINT("Encr. Text: " << encrText << "|||");
	_PRINT("Decr. Text: " << decrText << "|||");
}

void Test5()
{
	SaltGenerator sg;
	SecByteBlock iv = sg.GenerateIV(KEY_SIZE);
	SecByteBlock salt = sg.GenerateIV(KEY_SIZE);
	string password1 = "somepass";
	SecByteBlock pass1((const CryptoPP::byte*)password1.data(), password1.length());
	auto comb1 = GenKey(pass1, salt);

	BaseBlockCipherProvider<Twofish> provider;
	string origText = "This is some plain text which we wish to encrypt";
	string encrText = provider.Encrypt(get<0>(comb1), iv, "This is some plain text which we wish to encrypt...");
	string decrText = provider.Decrypt(get<0>(comb1), iv, encrText);

	_PRINT("Encr. Text: " << encrText << "|||");
	_PRINT("Decr. Text: " << decrText << "|||");
}