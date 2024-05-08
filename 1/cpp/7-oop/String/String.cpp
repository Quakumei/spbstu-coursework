#include "String.h"


std::ostream& operator<<(std::ostream& os, const String& str){
	os << str.pointer_; 
	return os;
}