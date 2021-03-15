#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include <iostream>
#include <fstream>
#include <string.h>

#include "Exceptions.hxx"
#include "FraunhofferTools.hxx"

class Converter{
	private:
		std::string _type;
		int _bitrate;

	public:
		// Default Constructor 
		Converter() {}	
		
		// Virtual Destructor
		virtual ~Converter() {};

		virtual void convert(std::string MasterFile, std::string info){};	
		
		virtual void bitrate(int num, std::string MasterFile, std::string info){};	
			
		virtual std::string print_info() {
			return "Converter";
		};
		
		virtual void set_bitrate(int num){};
		
		virtual int bitrate(){
			return  _bitrate;
		}
		
		virtual std::string type(){
			return _type;
		}
};

#endif
