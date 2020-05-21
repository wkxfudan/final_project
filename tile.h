#pragma once
#include<iostream>

namespace Game {
	using ull=unsigned long long;

	class tile 
	{
	private:
		int value;
		bool upgradeflag;
	public:
		tile() { value = 2; upgradeflag = false; }
		tile(const tile& other) { this->value = other.value; upgradeflag = false;}
		tile(int value) { this->value = value; upgradeflag = false;}
		int getvalue() const { return value; }
		void upgrade() { value *= 2; }
		void setflag(bool update) { upgradeflag = update; }
		bool getflag() const { return this->upgradeflag; }
	};
	bool operator==(const tile& tile1, const tile& tile2);
}

