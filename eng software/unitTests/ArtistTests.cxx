#include "MiniCppUnit.hxx"
#include "Artist.cxx"

class ArtistTests : public TestFixture<ArtistTests>
{
public:
	TEST_FIXTURE( ArtistTests )
	{
		TEST_CASE( testName_byDefault );
		TEST_CASE( testName_afterModifying );
		TEST_CASE( testArtist_getDescription );
	}

	void testName_byDefault()
	{
		Artist artist("Kase-O");
		ASSERT_EQUALS( "Kase-O", artist.name() );
	}

	void testName_afterModifying()
	{
		Artist artist("Kase-O");
		artist.name("Sho Hai");
		ASSERT_EQUALS( "Sho Hai", artist.name() );
	}

	void testArtist_getDescription()
	{
		Artist artist("Kase-O", false);
		ASSERT_EQUALS( "Kase-O [solo]\n", artist.description() );
	}
};

REGISTER_FIXTURE( ArtistTests )


