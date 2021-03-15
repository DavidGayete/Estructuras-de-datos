
class ArtistExceptions : public std::exception {
	public:
		const char * what() const throw () {
			return "The artist does not exist";
		}
};

class TrackException : public std::exception {
	public:
		const char * what() const throw () {
			return "The master file does not exist";
		}
};

class AlbumException : public std::exception {
	public:
		const char * what() const throw () {
			return "The album does not exist";
		}
};
class UserException : public std::exception {
public:

    const char * what() const throw () {
        return "The User does not exist";
    }
};
class StyleException : public std::exception {
public:

    const char * what() const throw () {
        return "The user does not exist";
    }
};

