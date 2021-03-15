

class UnsupportedFormat : public std::exception {
	public:
		const char * what() const throw () {
			return "This format is not supported";
		}
};

class MasterFileException : public std::exception {
	public:
		const char * what() const throw () {
			return "The master file does not exist";
		}
};

class ConverterException : public std::exception {
	public:
		const char * what() const throw () {
			return "The converter doesn't exist\n";
		}
};


