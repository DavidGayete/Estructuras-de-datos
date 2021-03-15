#include <iostream>
#include <fstream>
#include <cstring>

#include "Exceptions1.hxx"

class Track{
	private:
		std::string _title;
		std::string _master;
		std::string _description;
		unsigned _duration;
		
	public:
		// Default Constructor 
		Track() {
			_title = "-- Untitled --";
			_duration = 0u;
			_description = "";
		}
		
		// Constructor with title 
		Track(const std::string &title) 
			: _title(title)
		{
			_duration = 0u;
			_description = "";
		}
		
		// Constructor with title and master, and set the description and duration with masterFile
		Track(const std::string &title, const std::string &master) 
			: _title(title), _master(master)
		{
			std::string line;
			std::ifstream myfile(master.c_str());			
			_description = "\t" + title + " [";
			if(myfile.is_open()) {
			    while (getline(myfile, line)) {
					_duration = std::stoul(line, nullptr, 0);
			    	_description += line + std::string("s]\n");
					_description += "\t\t" + master + "\n";
			    }
			    myfile.close();
			}
			else {
				throw TrackException();
			}
		}		
		
		// Constructor with title, master and duration, and set the description with masterFile
		Track(const std::string &title, const std::string &master, unsigned duration) 
			: _title(title), _master(master), _duration(duration)
		{
			std::string line;
			std::ifstream myfile(master.c_str());			
			_description = "\t" + title + " [";
			if(myfile.is_open()) {
			    while (getline(myfile, line)) {
			    	_description += line + std::string("s]\n");
					_description += "\t\t" + master + "\n";
			    }
			    myfile.close();
			}
			else {
				throw TrackException();
			}
		}
		
		// Getters
		std::string title() {
			return _title;
		}
		
		std::string master() {
			return _master;		
		}
		
		std::string description() {
			return _description;		
		}
		
		unsigned duration(){
			return _duration;
		}
		
		// Setters
		void title(const std::string &nombre){
			_title = nombre;
		}
		
		void master(const std::string &masteer){
			_master = masteer;
		}
		
		void duration(unsigned time){
			_duration = time;
		}
};
