#include "MiniCppUnit.hxx"
#include "LibFileSystem.hxx"
#include <fstream>

#include "SingAlong.cxx"

class SingAlongTests : public TestFixture<SingAlongTests>
{
public:
	TEST_FIXTURE( SingAlongTests )
	{
		TEST_CASE( testCatalog_withNoArtists );
		TEST_CASE( testCatalog_withSoloArtist );
		TEST_CASE( testCatalog_withGroupArtist );
		TEST_CASE( testCatalog_withTwoArtists );
		TEST_CASE( testFindArtist_whenNoArtist );
		TEST_CASE( testFindArtist_whenArtistExists );
		TEST_CASE( testCatalog_withTrack );
		TEST_CASE( testCatalog_withTwoTracksWithDifferentDuration );
		TEST_CASE( testCatalog_withTracksOfDifferentArtists );
		TEST_CASE( testAddTrack_toArtistThatDoesNotExist );
		TEST_CASE( testAddTrack_whenMasterDoesNotExist );
		TEST_CASE( testCatalog_withUnlistedAlbum );
		TEST_CASE( testCatalog_withListedAlbum );
		TEST_CASE( testCatalog_withAlbumListedAndUnlisted );
		TEST_CASE( testCatalog_withTwoAlbums );
		TEST_CASE( testCatalog_albumWithTracks );
		TEST_CASE( testIncludeTrackOnAlbum_whenAlbumDoesNotExist );
	}

	/**
	 * setUp is automatically called before each test case
	 */
	void setUp()
	{
		LibFileSystem::createNetDirectory( "masters" );
	}

	/**
	 * tearDown is automatically called after each test case
	 */
	void tearDown()
	{
		LibFileSystem::cleanupDirectory( "masters" );
	}

	void createMasterFile( const std::string & name, int duration )
	{
		std::string completeName( "masters/" );
		completeName += name;
		std::ofstream os( completeName.c_str() );
		os << duration << std::endl;
	}


	void testCatalog_withNoArtists()
	{
		SingAlong business;

		ASSERT_EQUALS(
			"",
			business.catalog()
		);
	}
	void testCatalog_withSoloArtist()
	{
		SingAlong business;
		business.createArtist( "A solo artist", false );

		ASSERT_EQUALS(
			"A solo artist [solo]\n",
			business.catalog()
		);
		business.freeMemory();
	}
	void testCatalog_withGroupArtist()
	{
		SingAlong business;
		business.createArtist( "A group artist", true );

		ASSERT_EQUALS(
			"A group artist [group]\n",
			business.catalog()
		);
		business.freeMemory();
	}
	void testCatalog_withTwoArtists()
	{
		SingAlong business;
		business.createArtist( "A solo artist", false );
		business.createArtist( "A group artist", true );

		ASSERT_EQUALS(
			"A solo artist [solo]\n"
			"A group artist [group]\n",
			business.catalog()
		);
		business.freeMemory();
	}
	void testFindArtist_whenNoArtist()
	{
		SingAlong business;
		try
		{
			business.findArtist( "Does not exist" );
			FAIL( "An exception should be caught!" );
		}
		catch( std::exception & e )
		{
			ASSERT_EQUALS( "The artist does not exist", e.what() );
			business.freeMemory();
		}
	}
	void testFindArtist_whenArtistExists()
	{
		SingAlong business;
		business.createArtist( "An artist", false );
		Artist & artist = business.findArtist( "An artist" );

		ASSERT_EQUALS(
			"An artist",
			artist.name()
		);
		business.freeMemory();
	}
	void testCatalog_withTrack()
	{
		SingAlong business;
		business.createArtist( "An artist", false );

		createMasterFile( "aMasterFile.wav", 30 );
		business.createNewTrack( "An artist", "A track", "aMasterFile.wav" );

		ASSERT_EQUALS(
			"An artist [solo]\n"
			"\tA track [30s]\n"
			"\t\tmasters/aMasterFile.wav\n",
			business.catalog()
		);
		business.freeMemory();
	}
	void testCatalog_withTwoTracksWithDifferentDuration()
	{
		SingAlong business;
		business.createArtist( "An artist", false );

		createMasterFile( "aMasterFile.wav", 30 );
		business.createNewTrack( "An artist", "A track", "aMasterFile.wav" );

		createMasterFile( "anotherMasterFile.wav", 50 );
		business.createNewTrack( "An artist", "Another track", "anotherMasterFile.wav" );

		ASSERT_EQUALS(
			"An artist [solo]\n"
			"\tA track [30s]\n"
			"\t\tmasters/aMasterFile.wav\n"
			"\tAnother track [50s]\n"
			"\t\tmasters/anotherMasterFile.wav\n",
			business.catalog()
		);
		business.freeMemory();
	}
	void testCatalog_withTracksOfDifferentArtists()
	{
		SingAlong business;
		business.createArtist( "An artist", false );
		business.createArtist( "Another artist", false );

		createMasterFile( "aMasterFile.wav", 30 );
		business.createNewTrack( "An artist", "A track", "aMasterFile.wav" );

		createMasterFile( "anotherMasterFile.wav", 30 );
		business.createNewTrack( "Another artist", "Another track", "anotherMasterFile.wav" );
		createMasterFile( "aThirdMasterFile.wav", 50 );
		business.createNewTrack( "Another artist", "A third track", "aThirdMasterFile.wav" );

		ASSERT_EQUALS(
			"An artist [solo]\n"
			"\tA track [30s]\n"
			"\t\tmasters/aMasterFile.wav\n"
			"Another artist [solo]\n"
			"\tAnother track [30s]\n"
			"\t\tmasters/anotherMasterFile.wav\n"
			"\tA third track [50s]\n"
			"\t\tmasters/aThirdMasterFile.wav\n",
			business.catalog()
		);
		business.freeMemory();
	}
	void testAddTrack_toArtistThatDoesNotExist()
	{
		SingAlong business;
		createMasterFile( "aMasterFile.wav", 30 );
		try
		{
			business.createNewTrack( "An artist", "A track", "aMasterFile.wav" );
			FAIL( "An exception should be caught!" );
		}
		catch( std::exception & e )
		{
			ASSERT_EQUALS( "The artist does not exist", e.what() );
			business.freeMemory();
		}
	}
	void testAddTrack_whenMasterDoesNotExist()
	{
		SingAlong business;
		business.createArtist( "An artist", false );
		try
		{
			business.createNewTrack( "An artist", "A track", "aMasterFile.wav" );
			FAIL( "An exception should be caught!" );
		}
		catch( std::exception & e )
		{
			ASSERT_EQUALS( "The master file does not exist", e.what() );
			business.freeMemory();
		}
	}
	void testCatalog_withUnlistedAlbum()
	{
		SingAlong business;
		business.createArtist( "An artist", false );
		business.createNewAlbum( "An artist", "An album" );

		ASSERT_EQUALS(
			"An artist [solo]\n"
			"Album: An album [unlisted]\n",
			business.catalog()
		);
		business.freeMemory();
	}
	void testCatalog_withListedAlbum()
	{
		SingAlong business;
		business.createArtist( "An artist", false );
		business.createNewAlbum( "An artist", "An album" );
		business.listAlbum( "An artist", "An album" );

		ASSERT_EQUALS(
			"An artist [solo]\n"
			"Album: An album\n",
			business.catalog()
		);
		business.freeMemory();
	}
	void testCatalog_withAlbumListedAndUnlisted()
	{
		SingAlong business;
		business.createArtist( "An artist", false );
		business.createNewAlbum( "An artist", "An album" );
		business.listAlbum( "An artist", "An album" );
		business.unlistAlbum( "An artist", "An album" );

		ASSERT_EQUALS(
			"An artist [solo]\n"
			"Album: An album [unlisted]\n",
			business.catalog()
		);
		business.freeMemory();
	}
	void testCatalog_withTwoAlbums()
	{
		SingAlong business;
		business.createArtist( "An artist", false );
		business.createNewAlbum( "An artist", "An album" );
		business.createNewAlbum( "An artist", "Another album" );

		ASSERT_EQUALS(
			"An artist [solo]\n"
			"Album: An album [unlisted]\n"
			"Album: Another album [unlisted]\n",
			business.catalog()
		);
		business.freeMemory();
	}
	void testCatalog_albumWithTracks()
	{
		SingAlong business;
		business.createArtist( "An artist", false );
		business.createNewAlbum( "An artist", "An album" );

		createMasterFile( "aMasterFile.wav", 30 );
		business.createNewTrack( "An artist", "A track", "aMasterFile.wav" );

		createMasterFile( "anotherMasterFile.wav", 50 );
		business.createNewTrack( "An artist", "Another track", "anotherMasterFile.wav" );

		business.includeTrackOnAlbum( "An artist", "A track", "An album" );
		business.includeTrackOnAlbum( "An artist", "Another track", "An album" );

		ASSERT_EQUALS(
			"An artist [solo]\n"
			"\tA track [30s]\n"
			"\t\tmasters/aMasterFile.wav\n"
			"\tAnother track [50s]\n"
			"\t\tmasters/anotherMasterFile.wav\n"
			"Album: An album [unlisted]\n"
			"1 - A track [30s]\n"
			"2 - Another track [50s]\n",
			business.catalog()
		);
		business.freeMemory();
	}
	void testIncludeTrackOnAlbum_whenAlbumDoesNotExist()
	{
		SingAlong business;
		business.createArtist( "An artist", false );

		createMasterFile( "aMasterFile.wav", 30 );
		business.createNewTrack( "An artist", "A track", "aMasterFile.wav" );

		try
		{
			business.includeTrackOnAlbum( "An artist", "A track", "An album" );
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS( "The album does not exist", e.what() );
		}
		business.freeMemory();
	}
};

REGISTER_FIXTURE( SingAlongTests )


