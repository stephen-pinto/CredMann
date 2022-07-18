#pragma once

#include "Common.h"
#include <map>

using namespace std;

#define GUID_LEN 16

namespace CredMannLib
{
	namespace Models
	{
		struct CredPackFile
		{
			char Salt[KEY_SIZE];
			string CipherText;
 		};

		struct CredPackDBHeader
		{
			char Id[GUID_LEN];
			size_t TotalLength;
			size_t ActualLength;
			string Body;
		};

		struct CredPackDBBody
		{	
			size_t ActualLength;
			//string 
		};
	}
}