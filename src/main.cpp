#include <employees.h>
#include <bin_manip.hpp>

int main(){
	auto v = employee::EmployeesArray();
	bool flag = true;
	while(flag){
		std::string s;
		std::cin >> s;

		if (s == "exit"){
			flag = false;
			break;
		}
		else if (s == "list"){
			std::cout << v;
		}
		else if(s == "add"){
			std::cin >> v;	
		}
		else if (s == "save"){
			std::string fname;
			std::cin >> fname;
			std::ofstream out;
    		out.open(fname);
    		out << v;
		}
		else if (s == "load"){
			std::string fname;
			std::cin >> fname;
			std::ifstream in;
    		in.open(fname, std::ios::binary);
    		in >> v;
		}
	}
}
