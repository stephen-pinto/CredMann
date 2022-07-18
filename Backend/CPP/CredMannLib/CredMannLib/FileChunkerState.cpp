#include "pch.h"
#include "FileChunkerState.h"

using namespace CredMannLib::Util;

file_size_t FileChunkerState::GetTotalChunks(file_size_t chunkSize)
{
    size_t chunks = TotalBytes / chunkSize;
    if (TotalBytes % chunkSize > 0)
        chunks++;
    return chunks;
}

void FileChunkerState::Close()
{
    //Close the stream
    if (Stream != NULL)
    {
        Stream->close();
        delete (Stream);
    }
    //Clear all the flags
    TotalBytes = 0;
    TotalChunksObtained = 0;
    LastChunkSize = 0;
    Stream = NULL;
}
