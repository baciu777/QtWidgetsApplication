#include "validator.h"
#include <sstream>

void ActivityValidator::validate(const Activity& ac)
{
	vector<string> msgs;
	if (ac.getname().size() == 0)
		msgs.push_back("Invalid name!");
	if (ac.getdescription().size() == 0)
		msgs.push_back("Invalid description!");
	if (ac.gettype().size() == 0)
		msgs.push_back("Invalid type!");
	if (ac.getduration() < 0)
		msgs.push_back("Invalid duration!");
	if (msgs.size() > 0)
		throw ValidatorException(msgs);
}
ostream& operator<<(ostream& out, const ValidatorException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}
