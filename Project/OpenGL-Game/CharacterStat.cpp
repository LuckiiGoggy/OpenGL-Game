#include "CharacterStat.h"
#include <utility>

CharacterStat::CharacterStat(void)
{
	statName = "Stat";
	defaultVal = 0;
	statValue = 0;
	minValue = INT_MIN;
	maxValue = INT_MAX;
}

CharacterStat::CharacterStat(std::string name, int defVal, int minVal, int maxVal)
{
	statName = name;
	defaultVal = defVal;
	statValue = defaultVal;
	minValue = minVal;
	maxValue = maxVal;
}

void CharacterStat::SetValue(const int value){
	if (value >= minValue && value <= maxValue) 
		statValue = value;
	else if (value < minValue) statValue = minValue;
	else if (value > maxValue) statValue = maxValue;
}

int CharacterStat::GetValue(void){ return statValue; }


void CharacterStat::ChangeDefaultValue(const int value){
	if (value >= minValue && value <= maxValue)
		defaultVal = value;
	else if (value < minValue) defaultVal = minValue;
	else if (value > maxValue) defaultVal = maxValue;
}

int CharacterStat::GetDefaultValue(void){
	return defaultVal;
}

void CharacterStat::SetMinValue(const int value){
	minValue = value;
}

void CharacterStat::SetMaxValue(const int value){
	maxValue = value;
}

int  CharacterStat::GetMinValue(void){
	return minValue;
}

int CharacterStat::GetMaxValue(void){
	return maxValue;
}

void CharacterStat::ValidateMinMax(void){
	if (maxValue < minValue) std::swap(minValue, maxValue);
}

void CharacterStat::CheckBounds(void){
	if (statValue > maxValue) statValue = maxValue;
	if (statValue < minValue) statValue = minValue;
}

CharacterStat& CharacterStat::operator+=(const int rhs){
	statValue += rhs;
	CheckBounds();

	return *this;
}
CharacterStat& CharacterStat::operator-=(const int rhs){
	statValue -= rhs;
	CheckBounds();

	return *this;
}
CharacterStat& CharacterStat::operator*=(const int rhs){
	statValue *= rhs;
	CheckBounds();

	return *this;
}
CharacterStat& CharacterStat::operator/=(const int rhs){
	statValue /= rhs;
	CheckBounds();

	return *this;
}
CharacterStat& CharacterStat::operator%=(const int rhs){
	statValue %= rhs;
	CheckBounds();

	return *this;
}

bool CharacterStat::operator==(const int rhs){
	return (statValue == rhs);
}
bool CharacterStat::operator<=(const int rhs){
	return (statValue <= rhs);
}
bool CharacterStat::operator>=(const int rhs){
	return (statValue >= rhs);
}
bool CharacterStat::operator< (const int rhs){
	return (statValue <  rhs);
}
bool CharacterStat::operator> (const int rhs){
	return (statValue >  rhs);
}

CharacterStat& CharacterStat::operator++(void){
	statValue++;
	CheckBounds();

	return *this;
}
CharacterStat& CharacterStat::operator--(void){
	statValue--;
	CheckBounds();

	return *this;
}


std::string CharacterStat::GetName(void){
	return statName;
}


void CharacterStat::Reset(void){
	statValue = defaultVal;
}