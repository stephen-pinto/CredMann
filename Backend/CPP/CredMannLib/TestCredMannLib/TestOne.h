#pragma once

#include <iostream>
#include <tuple>
#include "../CredMannLib/PasswordStrengthner.h"
#include "../CredMannLib/SaltGenerator.h"
#include "../CredMannLib/Util.h"

using namespace CredMannLib::Password;
using namespace CredMannLib::Util;
using namespace CryptoPP;
using namespace std;

#define KEY_SIZE 32
#define DEFAULT_ITERATIONS 1024

tuple<SecByteBlock, string> GenKey(SecByteBlock& pass, SecByteBlock& iv)
{
	PasswordStrengthner ps;
	SecByteBlock key = ps.GenerateKey_PKCS5_PBKDF2(pass, iv, DEFAULT_ITERATIONS);
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

int Run(int argc, char** argv)
{
	Test2();
	return 0;
}