#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "ConverterGroup.cxx"
#include "Artist.cxx"
#include "MailStub.hxx"

typedef std::list<Converter*> Converters;
typedef std::list<User*> Useres;
using namespace std;

typedef std::list<Artist*> Artists;

class SingAlong {
	private:
		string _catalog;
		list<Artist*> _artists;
		ConverterGroup _converterees;
		std::list<User*> _UsSing;

	
	public:
		//Default Constructor 
		SingAlong() {
			_catalog = "";
			_converterees.addConverter("mp3",128);
			_converterees.addConverter("ogg",128);
			_converterees.addConverter("mp3",192);
			_converterees.addConverter("ogg",192);
			_converterees.addConverter("mp3",96);
			_converterees.addConverter("ogg",96);
			
			
			
			/*list<Converter*> _aux=_converterees.get_list();
			string str;
			for (Converters::iterator it=_aux.begin(); it!=_aux.end(); it++){
				str=(*it)->print_info();
				ofstream newfile( "compressed/An artist - A track "+ str);
			}*/
			
		}
		~SingAlong(){ _converterees.freeMemory();}
		
		
		// Print a description of all Artists with her albums and tracks from SingAlong.
		std::string catalog() {
			for (Artists::iterator it=_artists.begin(); it!=_artists.end(); it++) {
				_catalog += (*it)->description();
 			}
			return _catalog;
		}
		
		void createArtist(const std::string &name, bool group) {
			Artist* artist = new Artist(name, group);
			_artists.push_back(artist);
		}
		void subscribeUserToStyle( const std::string &name, const std::string &name1 ){
			throw StyleException();
			
			
			
		}
		//Return a instance of artist passed as parameter
		Artist& findArtist(const std::string &name) {
			for (Artists::iterator it=_artists.begin(); it!=_artists.end(); it++) {
				if((*it)->name() == name) {
					return *(*it);
				}
			}
			throw ArtistExceptions();
		}
		User& findUser(const std::string &name) {
        for (Useres::iterator it = _UsSing.begin(); it != _UsSing.end(); it++) {
            if ((*it)->name() == name) {
                return *(*it);
            }
        }
        throw UserException();
    }
		void createNewTrack(const std::string &artist, const std::string &track, const std::string &masterFile) {
			Artist& artistFound = findArtist(artist);
			Track* newTrack = new Track(track, "masters/" + masterFile);
			artistFound.addTrack(newTrack);
			
			Useres suscribed= artistFound.getsuscribed();
			for (Useres::iterator it = suscribed.begin(); it != suscribed.end(); it++) {
				MailStub::theInstance().sendMail((*it)->name1(),"new track "+newTrack->title()+" by "+artistFound.name());
        }
			
			
			_converterees.convert( "masters/"+masterFile,"compressed/"+artist+" - "+track);
		}

		void createNewAlbum(const std::string &artist, const std::string &albumName) {
			Artist& artistFound = findArtist(artist);
			Album* newAlbum = new Album(albumName);
			artistFound.addAlbum(newAlbum);
		}
		 void createNewUser(const std::string &name, const std::string &mail) {

        User* us = new User(name, mail);
        _UsSing.push_back(us);
    }

		
		void listAlbum(const std::string &artist, const std::string &albumName) {
			Artist& artistFound = findArtist(artist);
			Album* albumFound = artistFound.findAlbum(albumName);
			albumFound->list();
		}
		
		void unlistAlbum(const std::string &artist, const std::string &albumName) {
			Artist& artistFound = findArtist(artist);
			Album* albumFound = artistFound.findAlbum(albumName);
			albumFound->unlist();
		}
		
		// Add a Track on Album of the Artist passed as parameter
		void includeTrackOnAlbum(const std::string &artist, const std::string &track, const std::string &albumName) {
			Artist& artistFound = findArtist(artist);
			Album* albumFound = artistFound.findAlbum(albumName);
			Track* trackFound = artistFound.findTrack(track);
			albumFound->addTrack(trackFound);
		}
		
		
		void subscribeUserToArtist( const std::string &us,const std::string &ArtistName) {
        Artist& artistFound = findArtist(ArtistName);

        User& UserFound = findUser(us);
       
        artistFound.addSubs(&UserFound);
    }
    std::string userList(){ 
		std::string descrp;
		for (Useres::iterator it = _UsSing.begin(); it != _UsSing.end(); it++) {
            descrp += (*it)->description();
        }
        return descrp;
    }
		std::string listSubscribedToArtist( const std::string &ArtistName ){
			Artist& artistFound = findArtist(ArtistName);
			std::string description=artistFound.userss();
			return description;
		}
		
	
		// Free all memory that SingAlong use.
		void freeMemory() {
			for (Artists::iterator it=_artists.begin(); it!=_artists.end(); it++) {
				(*it)->deleteTracks();
				(*it)->deleteAlbums();
				delete (*it);
			}
		}
};
