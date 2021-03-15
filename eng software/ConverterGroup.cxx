#include <list>
#include <stdio.h>

#include "OggConverter.cxx"
#include "Mp3Converter.cxx"

typedef std::list<Converter*> Converters;

class ConverterGroup {
	private:
		std::list<Converter*> _converters;
	
	public:
		// Default Constructor 
		ConverterGroup() { }	
		void convert (std::string MasterFile, std::string info){
			for (Converters::iterator it=_converters.begin(); it!=_converters.end(); it++) 
					(*it)->convert( MasterFile, info);
		}	
		
		void addConverter(std::string tipus, int bit) {
			Converter* converter;
			if(tipus.compare("mp3")==0) {
				Mp3Converter* mp3Converter=new Mp3Converter(bit); 
				converter = mp3Converter;
				
				_converters.push_back(converter);
			}
			else if(tipus.compare("ogg")==0) {
				OggConverter* oggConverter=new OggConverter(bit); 
				converter = oggConverter;
				_converters.push_back(converter);
			}
			else
				throw ConverterException();
		}
		std::list<Converter*> get_list(){
			return _converters;
		}
		
		std::string info(){
			if(!_converters.empty()){
				std::string info;
				for (Converters::iterator it=_converters.begin(); it!=_converters.end(); it++) 
					info += (*it)->print_info()+"\n";
				return info;
			}
			else
				return "Lista vacia";
		}
		
		// Free all memory that ConverterGroup use.
		void freeMemory() {
			for (Converters::iterator it=_converters.begin(); it!=_converters.end(); it++)
				delete (*it);
		}
};
