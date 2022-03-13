#include "domain.h"

string Activity::getname() const
{
	return name;

}
string Activity::getdescription() const
{
	return description;

}
string Activity::gettype() const
{
	return type;

}
int Activity::getduration() const noexcept
{
	return duration;
}
void Activity::setname(const string& val)
{
	name = val;

}
void Activity::setdescription(const string& val)
{
	description = val;

}
void Activity::settype(const string& val)
{
	type = val;

}
void Activity::setduration(int val) noexcept
{
	duration = val;
}