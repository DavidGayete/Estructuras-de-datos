#include "MiniCppUnit.hxx"
#include "LibFileSystem.hxx"
#include <fstream>

#include "Converter.hxx"
#include "Mp3Converter.cxx"

class Mp3ConverterTests : public TestFixture<Mp3ConverterTests>
{
public:
	TEST_FIXTURE( Mp3ConverterTests )
	{
		TEST_CASE( testConvert_generateFile );
		TEST_CASE( testConvert_generateContent );
		
		TEST_CASE( testConvert_withDifferentBitrate );
		TEST_CASE( testConvert_withUnsupportedFormat );
		TEST_CASE( testConvert_withInexistentMaster );
		TEST_CASE( testConvert_polymorphicCall );
		
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
	
	void testConvert_generateFile()
	{
		Mp3Converter converter;
		createMasterFile("Master.wav" ,50) ;
		converter.convert("masters/Master.wav" ,"compressed/Prefix") ;

		ASSERT_EQUALS(
			"compressed/Prefix [128].mp3\n",
			LibFileSystem::listDirectoryInOrder( "compressed" )
		);
	}
	void testConvert_generateContent()
	{
		Mp3Converter converter;
		createMasterFile("Master.wav" ,50) ;
		converter.convert("masters/Master.wav" ,"compressed/Prefix") ;

		ASSERT_EQUALS(
			"MP3 extracted from 'masters/Master.wav' at 128 bps and length 50s.\n",
			LibFileSystem::fileContent( "compressed/Prefix [128].mp3" )
		);
	}
	void testConvert_withDifferentBitrate()
	{
		Mp3Converter converter;
		createMasterFile("Master.wav" ,50) ;
		converter.convert("masters/Master.wav" ,"compressed/Prefix") ;
		converter.bitrate(96, "masters/Master.wav","compressed/Prefix");

		ASSERT_EQUALS(
			"MP3 extracted from 'masters/Master.wav' at 96 bps and length 50s.\n",
			LibFileSystem::fileContent( "compressed/Prefix [128].mp3" )
		);
	}
	
	void testConvert_withUnsupportedFormat() {
		Mp3Converter converter;
		createMasterFile("Master.wav" ,50) ;
		converter.convert("masters/Master.wav" ,"compressed/Prefix") ;
		
		try{
			converter.bitrate(906, "masters/Master.wav","compressed/Prefix");
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS( "This format is not supported", e.what() );
		}
	}
	
	void testConvert_withInexistentMaster() {
		Mp3Converter converter;
		createMasterFile("Master.wav" ,50) ;
		converter.convert("masters/Master.wav" ,"compressed/Prefix") ;
		
		try{
			converter.bitrate(96, "masters/Masater.wav","compressed/Prefix");
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS( "The master file does not exist", e.what() );
		}
	}

	void testConvert_polymorphicCall() {
		Converter *converter;
		Mp3Converter mp3Converter; 
		converter = &mp3Converter;
		createMasterFile("Master.wav" ,50) ;
		converter->convert("masters/Master.wav" ,"compressed/Prefix") ;
		converter->bitrate(96, "masters/Master.wav","compressed/Prefix");

		ASSERT_EQUALS(
			"MP3 extracted from 'masters/Master.wav' at 96 bps and length 50s.\n",
			LibFileSystem::fileContent( "compressed/Prefix [128].mp3" )
		);
	}
	
	
};

REGISTER_FIXTURE( Mp3ConverterTests )


