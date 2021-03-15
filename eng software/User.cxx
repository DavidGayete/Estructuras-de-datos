#include <iostream>
#include <fstream>
#include <string>
#include <list>
class User {
private:
    std::string _name;
    std::string _mail;
    std::string _description;


public:

    User(const std::string &name, const std::string &mail)
    : _name(name), _mail(mail) {
        _name = name;
        _mail = mail;
    }
    std::string name(){
        return _name;
    }
    std::string name1(){
        return _name+" <" + _mail+">";
    }
    
    std::string description(){
		_description= _name+" <"+_mail+">\n";
		return _description;
		
	}
	std::string print(){
		_description = _name+"\n";
		return _description;
		
	}
};
