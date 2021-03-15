#include "MiniCppUnit.hxx"
#include "LibFileSystem.hxx"
#include <fstream>

#include "ConverterGroup.cxx"


class ConverterGroupTests : public TestFixture<ConverterGroupTests>
{
public:
	TEST_FIXTURE( ConverterGroupTests )
	{
		TEST_CASE( testConvert_withMp3Converter );
		TEST_CASE( testConvert_withoutConverter );
		
		TEST_CASE( testConvert_withOggConverter );
		TEST_CASE( testConvert_withOggConverterAndDifferentBitrate );
		TEST_CASE( testConvert_withMp3AndOggConverters );
		TEST_CASE( testConvert_withUnknownConverter );
		
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
		std::ofstream os( completeName.c_str());
		os << duration << std::endl;
	}
	
	void testConvert_withMp3Converter()
	{
		ConverterGroup converters;
		converters.addConverter("mp3",128);
		
		ASSERT_EQUALS("mp3: 128\n", converters.info());
		converters.freeMemory();
	}
	void testConvert_withoutConverter()
	{
		ConverterGroup converters;
		
		ASSERT_EQUALS("Lista vacia", converters.info());
		converters.freeMemory();
	}
	void testConvert_withOggConverter()
	{
		ConverterGroup converters;
		converters.addConverter("ogg",128);
		
		ASSERT_EQUALS(
			"ogg: 128\n",
			converters.info( )
		);
		converters.freeMemory();
	}
	
	void testConvert_withOggConverterAndDifferentBitrate() {
		ConverterGroup converters;
		converters.addConverter("ogg",128);
		converters.addConverter("ogg",192);
		
		ASSERT_EQUALS(
			"ogg: 128\n"
			 "ogg: 192\n",
			converters.info( )
		);
		converters.freeMemory();
	}
	
	void testConvert_withMp3AndOggConverters() {
		ConverterGroup converters;
		converters.addConverter("mp3",128);
		converters.addConverter("ogg",192);
		
		ASSERT_EQUALS(
			"mp3: 128\n"
			 "ogg: 192\n",
			converters.info( )
		);
		converters.freeMemory();
	}

	void testConvert_withUnknownConverter() {
		ConverterGroup converters;
		converters.addConverter("mp3",128);
		try {
			converters.addConverter("hey",128);
			FAIL( "An exception should be caught!" );
		} catch ( std::exception & e ) {
			ASSERT_EQUALS("The converter doesn't exist\n", e.what());
		}
		converters.freeMemory();
	}
};

REGISTER_FIXTURE( ConverterGroupTests )

