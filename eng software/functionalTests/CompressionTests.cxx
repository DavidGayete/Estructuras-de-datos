#include "MiniCppUnit.hxx"
#include "LibFileSystem.hxx"
#include <fstream>
#include "SingAlong.cxx"

class CompressionTests : public TestFixture<CompressionTests>
{
public:
	TEST_FIXTURE( CompressionTests )
	{
		TEST_CASE( compressionTestByDefault_withOneMaster );
	}

	/**
	 * setUp is automatically called before each test case
	 */
	void setUp()
	{
		LibFileSystem::createNetDirectory( "masters" );
		LibFileSystem::createNetDirectory( "compressed" );
		LibFileSystem::createNetDirectory( "config" );
	}

	/**
	 * tearDown is automatically called after each test case
	 */
	void tearDown()
	{
		LibFileSystem::cleanupDirectory( "masters" );
		LibFileSystem::cleanupDirectory( "compressed" );
		LibFileSystem::cleanupDirectory( "config" );
	}

	void createMasterFile( const std::string & name, int duration )
	{
		std::string completeName( "masters/" );
		completeName += name;
		std::ofstream os( completeName.c_str() );
		os << duration << std::endl;
	}
	
	void compressionTestByDefault_withOneMaster()
	{
		SingAlong business;
		business.createArtist( "An artist", false );

		createMasterFile( "aMasterFile.wav", 120 );
		business.createNewTrack( "An artist", "A track", "aMasterFile.wav" );

		ASSERT_EQUALS(
			"compressed/An artist - A track [128].mp3\n"
			"compressed/An artist - A track [128].ogg\n"
			"compressed/An artist - A track [192].mp3\n"
			"compressed/An artist - A track [192].ogg\n"
			"compressed/An artist - A track [96].mp3\n"
			"compressed/An artist - A track [96].ogg\n"

,
			LibFileSystem::listDirectoryInOrder( "compressed" )
		);
		business.freeMemory();
	}

	
};

REGISTER_FIXTURE( CompressionTests )


