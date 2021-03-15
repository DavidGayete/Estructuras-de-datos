#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "Album.cxx"
#include "User.cxx"
typedef std::list<Track*> Tracks;
typedef std::list<Album*> Albums;
typedef std::list<User*> Useres;
class Artist {
	private:
		std::string _name;
		std::string _description;
		std::list<Track*> _tracks;
		std::list<Album*> _albums;
		std::list<User*> _UsArtist;
		bool _group;

	public:
		// Default Constructor 
		Artist() {
			_group = true;
			initDescription();
		}	
		
		// Constructor with name of artist
		Artist(const std::string &name) 
			: _name(name)
		{
			_group = true;
			initDescription();
		}	
		
		// Constructor with name of artist and info about group/solo
		Artist(const std::string &name, bool group) 
			: _name(name), _group(group)
		{
			initDescription();
		}		

		// Set description when Artist is created.
		void initDescription() {
			if(isGroup())
				_description += _name + " " + "[group]\n";
			else
				_description += _name + " " + "[solo]\n";
		}
				
		// Upload description with all descriptions from Tracks and Albums of this Artist		
		std::string description() {
			for (Tracks::iterator it=_tracks.begin(); it!=_tracks.end(); it++) {
				_description += (*it)->description();
			}
			for (Albums::iterator it=_albums.begin(); it!=_albums.end(); it++) {
				_description += (*it)->description();
			}
			for (Useres::iterator it = _UsArtist.begin(); it != _UsArtist.end(); it++) {
            _description += (*it)->name();
        }
			return _description;
		}
		std::string userss(){
			std::string aa;
			for (Useres::iterator it = _UsArtist.begin(); it != _UsArtist.end(); it++) {
            
            
           aa +=(*it)->print();
			}
			
			return aa;
		}
		
		
		// Getters
		std::string name() {
			return _name;
		}
		
		bool isGroup() {
			return _group;
		}
		
		std::list<Track*> getTracks() {
			return _tracks; 	
		}

		//Setters
		void name(const std::string &name) {
			_name = name;
		}
	
		// Add Track on the track list of this Artist
		void addTrack(Track* track) {
			_tracks.push_back(track);
		}

		// Add Album on the album list of this Artist
		void addAlbum(Album* album) {
			_albums.push_back(album);		
		}
		void addSubs(User* us) {
			_UsArtist.push_back(us);
		}
		
		// Return the Album that check with the name passed as parameter OR throw AlbumException
		Album* findAlbum(const std::string &name) {
			for (Albums::iterator it=_albums.begin(); it!=_albums.end(); it++) {
				if((*it)->title() == name) {
					return (*it);
				}
			}
			throw AlbumException();
		}

		// Return the Track that check with the name passed as parameter OR throw TrackException
		Track* findTrack(const std::string &name) {
			for (Tracks::iterator it=_tracks.begin(); it!=_tracks.end(); it++) {
				if((*it)->title() == name) {
					return (*it);
				}
			}
			throw TrackException();
		}
		
		Useres getsuscribed(){
			
			return _UsArtist;
		}
		
		/*** MANAGE MEMORY LEAKS!! ***/
		void deleteAlbums() {
			for (Albums::iterator it=_albums.begin(); it!=_albums.end(); it++) {
				delete (*it);
			}
		}
		void deleteTracks() {
			for (Tracks::iterator it=_tracks.begin(); it!=_tracks.end(); it++) {
				delete (*it);
			}
		}
};
