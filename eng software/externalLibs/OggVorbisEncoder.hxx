#ifndef OggVorbisEncoder_hxx
#define OggVorbisEncoder_hxx

#include <string>
#include <fstream>

namespace OGG
{
	class WavNotFound {}; //< An empty exception class.

	/*
	 * Simulates the compresion of a wav file into a ogg/vorbis file.
	 * In fact it simply writes a string describing the process.
	 * @throws WavNotFound when the inWavFile doesn't exists.
	 */
	inline void compress_to_ogg( const std::string& inWavFile, const std::string& outFilename, int bitrate )
	{
		std::ifstream wav;
		wav.open( inWavFile.c_str() );
		if ( !wav.is_open() ) throw WavNotFound();
		int duration;
		wav >> duration;

		std::ofstream oggFile( outFilename.c_str() );
		oggFile << "OGG extracted from '" << inWavFile
			<< "' at " << bitrate << " bps and length "
			<< duration << "s." << std::endl;
	}
} // namesapce OGG

#endif
