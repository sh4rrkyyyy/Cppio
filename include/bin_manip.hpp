#pragma once
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
int32_t const MAX_LEN = 101;
int const NUM_OF_BYTES = 4;
int const SHIFT_BY_BYTE = 8;
namespace manip{
	class write_le_int32{
	public:
		write_le_int32(std::int32_t x);
		friend std::ostream& operator<<(std::ostream& out, write_le_int32 val);
	private:
		std::int32_t _x;
	};

	class read_le_int32{
	public:
		read_le_int32(int32_t& x);
		friend std::istream& operator>>(std::istream& in, read_le_int32 val);
	private:
		int32_t* _x;
	};

	class write_bool{
	public:
		write_bool(bool b);
		friend std::ostream& operator<<(std::ostream& out, write_bool val);
	private:
		bool _b;
	};

	class read_bool{
	public:
		read_bool(bool& b);
		friend std::istream& operator>>(std::istream& in, read_bool val);
	private:
		bool *_b;
	};

	class write_c_str{
	public:
		write_c_str(const char* s);
		friend std::ostream& operator<<(std::ostream& out, const write_c_str& val);
	private:
		char _s[101];
		int32_t lenn;
	};

	class read_c_str{
	public:
		read_c_str(char* s, size_t lenn);
		friend std::istream& operator>>(std::istream& in, const read_c_str& val);
	private:
		char* _s;
		size_t _lenn;
	};
}
