#include "bin_manip.hpp"

namespace manip{
	write_le_int32::write_le_int32(std::int32_t x): _x(x) {}
	std::ostream& operator<<(std::ostream& out, write_le_int32 val){
		int shift = 0;
		for (int i = 0; i < NUM_OF_BYTES; ++i){
			int32_t a = ((val._x >> shift) & 0xFF);
			out.put(a);
			shift += SHIFT_BY_BYTE;
		}
		return out;
	}

	read_le_int32::read_le_int32(int32_t& x): _x(&x) {}
	std::istream& operator>>(std::istream& in, read_le_int32 val){
		char bytes[NUM_OF_BYTES];
		in.read(bytes, NUM_OF_BYTES);
		*val._x = 0;
		int shift = 0;
		for (int i = 0; i < NUM_OF_BYTES; ++i){
			*val._x += (unsigned char)(bytes[i]) << shift;
			shift += SHIFT_BY_BYTE;
		}
		return in;
	}
	write_bool::write_bool(bool b): _b(b) {}
	std::ostream& operator<<(std::ostream& out, write_bool val){
		out.put(val._b);
		return out;
	}

	read_bool::read_bool(bool& b): _b(&b) {}
	std::istream& operator>>(std::istream& in, read_bool val){
		in.read((char*)val._b, 1);
		return in;
	}

	write_c_str::write_c_str(const char* s){
		strcpy(_s, s);
		

	}
	std::ostream& operator<<(std::ostream& out, const write_c_str& val){
		out.write(val._s, strlen(val._s) + 1);
		return out;
	}
	read_c_str::read_c_str(char* s, size_t lenn){
		_s = s;
		_lenn = lenn + 1;
	}
	std::istream& operator>>(std::istream& in, const read_c_str& val){
		size_t i = 0;
		while((in.get(val._s[i])) && i < val._lenn){
			if (val._s[i] == '\0'){
				break;
			}
			i += 1;
		}
		if (i >= val._lenn && val._s[i - 1] != '\0'){
			throw std::invalid_argument("name format is not correct");
		}
		return in;
	}
}



