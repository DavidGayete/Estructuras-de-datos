#include <iostream>
#include <string> 
#include <list>

#include "Track.cxx"


typedef std::list<Track*> Tracks;

class Album {
	private:
		std::string _title;
		std::string _description;
		std::list<Track*> _tracks;
		bool _list;
		
	public:
		// Default Constructor 
		Album() { 
			_title = "-- Untitled --";
			_list = false;
			initDescription();
		} 
		
		// Constructor with title 
		Album(const std::string &title) 
			: _title(title)
		{
			_list = false;
			initDescription();
		}	
		
		// Create the description of this Album when is created.
		void initDescription() {
			if(isListed())
				_description = "Album: " + _title + "\n";
			else
				_description = "Album: " + _title + " " + "[unlisted]\n";
		}
		
		// Create the description of this Album with all descriptions of each Track.
		std::string description() {
			int cont = 1;
			for (Tracks::iterator it=_tracks.begin(); it!=_tracks.end(); it++) {
				_description += std::to_string(cont) + " - " + (*it)->title() + " [" + std::to_string((*it)->duration()) + "s]\n";
				cont++;
			}
			return _description;
		}
		
		// Add a Track on this album
		void addTrack(Track* track) {
			_tracks.push_back(track);
		}
		
		// Getters
		std::string title() {
			return _title;
		}

		bool isListed() {
			return _list;
		}
		
		//Setters
		void title(const std::string &theName) {
			_title = theName;
		}
		
		//Set _list attribut to true
		void listByInput(const std::string &title) {
			char listed = title[title.size()-1];
			
			if(listed == 'Y')
			  _list = true;
			else
			  _list = false;
		}
		
		//Set _list attribut to true and modify the description
		void list() {
			_description = "Album: " + _title + "\n";
			_list = true;
		}
		
		//Set _list attribut to false and modify the description
		void unlist() {
			_description = "Album: " + _title + " " + "[unlisted]\n";
			_list = false;
		}
};
