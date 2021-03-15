#include "Converter.hxx"


class Mp3Converter: public Converter {
	private:
		int _bitrate;
		std::string _type;

	public:
		// Default Constructor 
		Mp3Converter() {
			_bitrate = 128;
			_type = "mp3: ";
		}	
		
		// Complete Constructor 
		Mp3Converter(int bitrate) {
			_bitrate = bitrate;
			_type = "mp3: ";
		}
		
		// Destructor for Mp3Converter
		~Mp3Converter() {};
		
		std::string print_info(){
			return _type+std::to_string(_bitrate);
				
		}
		
		void convert(std::string MasterFile, std::string info){
			std::string str = " ["+std::to_string(_bitrate)+"].mp3";
			std::string outFile = info + str;
			std::ofstream newfile(outFile);
			int res;
			switch ( _bitrate )	{
				case 96 : res = frk_MP3_compression(MasterFile.c_str() , outFile.c_str(), bps96 ); break;
				case 128: res = frk_MP3_compression(MasterFile.c_str() , outFile.c_str(), bps128 ); break;
				case 192: res = frk_MP3_compression(MasterFile.c_str() , outFile.c_str(), bps192 ); break;
				case 240: res = frk_MP3_compression(MasterFile.c_str() , outFile.c_str(), bps240 ); break;
				default: throw UnsupportedFormat();
			}
		}	
		
		void bitrate(int num, std::string MasterFile, std::string info){
			std::string outFile = info + " [128].mp3";
			int res;
			switch ( num )	{
				case 96 : res = frk_MP3_compression(MasterFile.c_str() , outFile.c_str(), bps96 ); break;
				case 128: res = frk_MP3_compression(MasterFile.c_str() , outFile.c_str(), bps128 ); break;
				case 192: res = frk_MP3_compression(MasterFile.c_str() , outFile.c_str(), bps192 ); break;
				case 240: res = frk_MP3_compression(MasterFile.c_str() , outFile.c_str(), bps240 ); break;
				default: throw UnsupportedFormat();
			}
			if(res == -1)
				throw MasterFileException();
		}	
};
