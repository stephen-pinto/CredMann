#pragma once

#include "Common.h"
#include "FileChunkerState.h"

namespace CredMannLib
{
	namespace Util
	{
		class FileChunker
		{
		public:
			FileChunker(const file_size_t chunkSize);
			~FileChunker();

			void OpenFile(const std::string filePath);
			std::vector<byte_t> ReadNextChunk();
			bool HasMore();
			void Close();

		private:
			file_size_t chunkSize;
			FileChunkerState state;
		};
	}
}