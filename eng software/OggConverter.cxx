#include "Converter.hxx"
#include "OggVorbisEncoder.hxx"
#include "LibFileSystem.hxx"


class OggConverter: public Converter {
	private:
		int _bitrate;
		std::string _type;

	public:
		// Default Constructor 
		OggConverter() {
			_bitrate = 128;
			_type = "ogg: ";
		}	
		// Complete Constructor 
		OggConverter(int bitrate) {
			_bitrate = bitrate;
			_type = "ogg: ";
		}
		
		// Destructor for OggConverter
		~OggConverter() {};
		
		std::string print_info(){
			return _type+std::to_string(_bitrate);
		}
		
		void set_bitrate(int num){
			_bitrate=num;
		}

		int bitrate(){
			return _bitrate;
		}
		
		std::string type(){
			return _type;
		}
			
		void convert(std::string MasterFile, std::string info){
			std::string str = " ["+std::to_string(_bitrate)+"].ogg";
			std::string outFile = info + str;
			std::ofstream newfile(outFile);
			OGG::compress_to_ogg(MasterFile.c_str() , outFile.c_str(), _bitrate);
		}	
		
		void bitrate(int num, std::string MasterFile, std::string info){
			std::string outFile = info + " [128].ogg";
			if(LibFileSystem::fileExists(MasterFile)==true)			
				OGG::compress_to_ogg(MasterFile.c_str() , outFile.c_str(), num);
			else
				throw MasterFileException();
		}			
};
