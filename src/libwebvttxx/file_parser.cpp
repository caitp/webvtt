#include <stdlib.h>
#include <webvttxx/file_parser>

namespace WebVTT
{

FileParser::FileParser( const char *fPath )
 : filePath( fPath )
{
  reader.open( fPath, std::ios::in | std::ios::binary );

  if( !reader.good() ) {
    // TODO: Throw
  }
}

FileParser::~FileParser()
{
  if( reader.is_open() ) {
    reader.close();
  }
}

bool
FileParser::parse()
{
  bool final = false;
  ::webvtt_status status;
  char buffer[0x1000];
  if( !reader.good() ) {
    return false;
  }

  do {
    reader.read( buffer, sizeof buffer );
    uint len = (uint)reader.gcount();
    final = reader.eof();
    status = parseChunk( buffer, len, final );
  } while( !final && !WEBVTT_FAILED(status) );

  return status == WEBVTT_SUCCESS;
}

}
