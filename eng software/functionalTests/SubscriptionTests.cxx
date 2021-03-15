#include "MiniCppUnit.hxx"
#include "LibFileSystem.hxx"

#include <fstream>
#include "SingAlong.cxx"


class SubscriptionTests : public TestFixture<SubscriptionTests>
{
public:
	TEST_FIXTURE( SubscriptionTests )
	{
	TEST_CASE( testUserList_withOneUser );
	TEST_CASE( testUserList_withTwoUsers );
		TEST_CASE( testListSubscribedToArtist_withOneUser );
		TEST_CASE( testListSubscribedToArtist_withTwoUsers );
		TEST_CASE( testListSubscribedToArtist_whenUserDoesNotExist );
		// Notification Tests: 
		TEST_CASE( testCreateNewTrack_notifyUserSubscribedToArtist );
		TEST_CASE( testCreateNewTrack_notifyTwoUsersSubscribedToArtist );
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
		MailStub::theInstance().removeSent();
	}

	void createMasterFile( const std::string & name, int duration )
	{
		std::string completeName( "masters/" );
		completeName += name;
		std::ofstream os( completeName.c_str() );
		os << duration << std::endl;
	}
	
	void testUserList_withOneUser()
	{
		SingAlong business;
		business.createNewUser( "A user", "a@mail.org" );
		ASSERT_EQUALS( "A user <a@mail.org>\n", business.userList() );
	}
	void testUserList_withTwoUsers()
	{
		SingAlong business;
		business.createNewUser( "A user", "a@mail.org" );
		business.createNewUser( "Another user", "another@mail.org" );
		ASSERT_EQUALS(
			"A user <a@mail.org>\n"
			"Another user <another@mail.org>\n",
			business.userList()
		);
	}
	void testListSubscribedToArtist_withOneUser()
	{
		SingAlong business;
		business.createNewUser( "A user", "a@mail.org" );
		business.createArtist( "An artist", false );
		business.subscribeUserToArtist( "A user", "An artist" );
		ASSERT_EQUALS(
			"A user\n", 
			business.listSubscribedToArtist( "An artist" )
		);				
	}
	void testListSubscribedToArtist_withTwoUsers()
	{
		SingAlong business;
		business.createNewUser( "A user", "a@mail.org" );
		business.createNewUser( "Another user", "another@mail.org" );
		business.createArtist( "An artist", false );
		
		business.subscribeUserToArtist( "A user", "An artist" );
		business.subscribeUserToArtist( "Another user", "An artist" );
		
		ASSERT_EQUALS(
			"A user\n"
			"Another user\n",
			business.listSubscribedToArtist( "An artist" )
		);
	}
	void testListSubscribedToArtist_whenUserDoesNotExist()
	{
		SingAlong business;
		try
		{
			business.subscribeUserToStyle( "A user", "An artist" );
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS( "The user does not exist", e.what() );
		}
	}
	void testCreateNewTrack_notifyUserSubscribedToArtist()
	{
		SingAlong business;
		business.createArtist( "An artist", false );
		business.createNewUser( "A user", "a@mail.org" );
		business.subscribeUserToArtist( "A user", "An artist" );

		createMasterFile( "aMasterFile.wav", 30 );
		business.createNewTrack( "An artist", "A track", "aMasterFile.wav" );
		ASSERT_EQUALS(
			"To: A user <a@mail.org>\n"
			"Subject: new track A track by An artist\n"
			"\n", 
			MailStub::theInstance().sentMails()
		);
	}
	void testCreateNewTrack_notifyTwoUsersSubscribedToArtist()
	{
		SingAlong business;
		business.createArtist( "An artist", false );
		business.createArtist( "Another artist", false );
		business.createNewUser( "A user", "a@mail.org" );
		business.createNewUser( "Another user", "another@mail.org" );

		business.subscribeUserToArtist( "A user", "An artist" );
		business.subscribeUserToArtist( "Another user", "Another artist" );

		createMasterFile( "aMasterFile.wav", 30 );
		business.createNewTrack( "An artist", "A track", "aMasterFile.wav" );

		createMasterFile( "anotherMasterFile.wav", 40 );
		business.createNewTrack( "Another artist", "Another track", "anotherMasterFile.wav" );

		ASSERT_EQUALS(
			"To: A user <a@mail.org>\n"
			"Subject: new track A track by An artist\n"
			"\n"
			"To: Another user <another@mail.org>\n"
			"Subject: new track Another track by Another artist\n"
			"\n", 
			MailStub::theInstance().sentMails()
		);
	}
	
};

REGISTER_FIXTURE( SubscriptionTests )

