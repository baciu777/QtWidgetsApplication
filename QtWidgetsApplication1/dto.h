#pragma once
class Dto_duration
{
private:
	int duration;
	int number;
public:
	Dto_duration() noexcept : duration{ 1 }, number{ 0 }
	{

	};
	Dto_duration(int duration)noexcept :duration{ duration }, number{ 1 }
	{

	}
	void addNr() noexcept { number++; }int getduration()noexcept { return duration; }int getNumber() noexcept { return number; }
};