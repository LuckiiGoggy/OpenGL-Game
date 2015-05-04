#ifndef CHARACTERSTAT_H
#define CHARACTERSTAT_H

#include <string>

class CharacterStat
{
public:
	CharacterStat(std::string name, int defaultVal, int minVal = INT_MIN, int maxVal = INT_MAX);
	
	/**Resets the stat to the default value.**/
	void Reset(void);

	/**Sets the stat to the desired value
		@param value - value to set stat to**/
	void SetValue(const int value);
	/**Returns the value of stat**/
	int GetValue(void);

	/**Sets the default value to the desired value
	@param value - value to set default value to**/
	void ChangeDefaultValue(const int value);
	/**Returns the default value**/
	int GetDefaultValue(void);


	/**Sets the minimum allowed value to the desired value
	@param value - value to set minimum allowed value to**/
	void SetMinValue(const int value);
	/**Sets the maximum allowed value to the desired value
	@param value - value to set maximum allowed value to**/
	void SetMaxValue(const int value);
	
	/**Returns the minimum allowed value**/
	int  GetMinValue(void);
	/**Returns the maximum allowed value**/
	int  GetMaxValue(void);

	/** Modifies min and max values to makes sure that 
		the min and max are the lower and higher 
		ends of the spectrum respectively.**/
	void ValidateMinMax(void);
	
	/**Operator overloads for the stat, allows the stat to be treated
		like an integer or only as its value
		**/
	CharacterStat& operator+=(const int rhs);
	CharacterStat& operator*=(const int rhs);
	CharacterStat& operator-=(const int rhs);
	CharacterStat& operator/=(const int rhs);
	CharacterStat& operator%=(const int rhs);

	bool operator==(const int rhs);
	bool operator<=(const int rhs);
	bool operator>=(const int rhs);
	bool operator< (const int rhs);
	bool operator> (const int rhs);

	CharacterStat& operator++(void);
	CharacterStat& operator--(void);

protected:
	std::string statName;
	int statValue;
	int defaultVal;

	int minValue;
	int maxValue;

	/**Checks if the statValue is within min and max, if not
		move to the closer limit.**/
	void CheckBounds(void);

};

#endif