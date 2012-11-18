#include "parsevtt.h"
#include <ctype.h>
#include <errno.h>

int
main( int argc, char **argv )
{
	const char *input_file = 0;
	webvtt_status result;
	parsevtt_t self;
	FILE *fh;
	int i;
	int ret = 0;
	for( i = 0; i < argc; ++i )
	{
		const char *a = argv[i];
		if( *a == '-' )
		{
			switch( a[1] )
			{
				case 'f':
				{
					const char *p = a+2;
					while( isspace(*p) ) ++p;
					if( *p )
					{
						input_file = p;
					}
					else if( i+1 < argc )
					{
						input_file = argv[i+1];
						++i;
					}
					else
					{
						fprintf( stderr, "error: missing parameter for switch `-f'\n" );
					}
				} break;
				
				case '?':
				{
					fprintf( stdout, "Usage: parsevtt -f <vttfile>\n" );
					return 0;
				} break;
			}
		}
	}
	if( !input_file )
	{
		fprintf( stderr, "error: missing input file.\n\nUsage: parsevtt -f <vttfile>\n" );
		return 1;
	}
	

	if( parsevtt_init( &self, input_file ) != WEBVTT_SUCCESS )
	{
		ret = 1;
	}
	else
	{
		ret = ( parsevtt_parse_file( &self ) == WEBVTT_SUCCESS ? 0 : 1 );
	}
	parsevtt_cleanup( &self );
	return ret;
}