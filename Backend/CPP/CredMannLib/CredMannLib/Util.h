#pragma once

#include "Common.h"
#include <cryptopp/hex.h>
#include <cryptopp/secblockfwd.h>

namespace CredMannLib
{
	namespace Util
	{
		class UtilServices
		{
		public:
			std::string HexEncode(const CryptoPP::SecByteBlock& content);
			CryptoPP::SecByteBlock HexDecode(const std::string& content);
		};

		std::string UtilServices::HexEncode(const CryptoPP::SecByteBlock& content)
		{
			std::string encodedContent;
			CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(encodedContent));
			encoder.Put(content.data(), content.size());
			encoder.MessageEnd();
			return encodedContent;
		}

		CryptoPP::SecByteBlock UtilServices::HexDecode(const std::string& content)
		{
			CryptoPP::SecByteBlock decodedContent;
			CryptoPP::HexDecoder decoder;
			decoder.Put((CryptoPP::byte*)content.data(), content.length());
			decoder.MessageEnd();
			decodedContent.resize(decoder.MaxRetrievable());
			decoder.Get(&decodedContent[0], decodedContent.size());
			return decodedContent;
		}
	}
}