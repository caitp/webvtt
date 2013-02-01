#include <webvttxx/abstract_parser>
#include <webvttxx/cue>

namespace WebVTT
{

AbstractParser::AbstractParser()
{
  webvtt_status status;
  if(WEBVTT_FAILED(status = webvtt_create_parser( &__parsedCue, &__reportError, this, &parser ) ) ) {
    /**
     * TODO: Throw error
     */
  }
}

AbstractParser::~AbstractParser()
{
  webvtt_delete_parser( parser );
}

::webvtt_status
AbstractParser::parseChunk( const void *chunk, webvtt_uint length, bool finished )
{
  return webvtt_parse_chunk( parser, chunk, length, (int)finished );
}

void WEBVTT_CALLBACK
AbstractParser::__parsedCue( void *userdata, webvtt_cue *pcue )
{
  Cue cue(pcue);
  /**
   * Cue object increases the reference count of pcue, so we can dereference it
   */
  webvtt_release_cue( &pcue );

  AbstractParser *self = reinterpret_cast<AbstractParser *>( userdata );
  self->parsedCue( cue );
}

int WEBVTT_CALLBACK
AbstractParser::__reportError( void *userdata, webvtt_uint line, webvtt_uint col, webvtt_error error )
{
  AbstractParser *self = reinterpret_cast<AbstractParser *>( userdata );
  Error err( line, col, error );
  if( !self->reportError( err ) ) {
    return -1;
  }
  return 0;
}

}
