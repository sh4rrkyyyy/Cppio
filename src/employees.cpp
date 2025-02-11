#include "employees.h"
#include "bin_manip.hpp"
namespace employee{
	Employee::Employee(std::string name, int32_t base_salary): _name(name), _base_salary(base_salary) {}

	Developer::Developer(std::string name, int32_t base_salary, bool has_bonus): Employee(name, base_salary){
		_has_bonus = has_bonus;
	}

	SalesManager::SalesManager(std::string name, int32_t base_salary, int32_t sold_nm, int32_t price): Employee(name, base_salary){
		_sold_nm = sold_nm;
		_price = price;
	}

	int Developer::salary() const {
	    int salary = _base_salary;
	    if (_has_bonus) { salary += 1000; }
	    return salary;
	}

	int SalesManager::salary() const {
	    return _base_salary + _sold_nm * _price * 0.01;
	}

	void EmployeesArray::add(Employee* emp){
		_employees.push_back(emp);
	}

	int EmployeesArray::total_salary() const{
		int total = 0;
		for (size_t i = 0; i < _employees.size(); ++i){
			total += _employees[i]->salary();
		}
		return total;
	}
	void Employee::print_text(std::ostream& out) const{
		out << "Name: " << _name.c_str() << std::endl << "Base Salary: " << _base_salary << std::endl;
	}
	void Employee::print_bin(std::ofstream& out) const{
		out << manip::write_c_str((char*)_name.c_str()) << manip::write_le_int32(_base_salary);
	}
	void Employee::get_text(std::istream& in){
		in >> _name >> _base_salary;
	}
	void Employee::get_bin(std::ifstream& in){
		char name[MAX_LEN];
    	in >> manip::read_c_str(name, sizeof(name)) >> manip::read_le_int32(_base_salary);
    	_name = name;
	}
	void Developer::print_text(std::ostream& out) const{
		out << "Developer" << std::endl;
		Employee::print_text(out);
		out << "Has bonus: " << (_has_bonus ? '+' : '-');
	}

	void Developer::print_bin(std::ofstream& out) const{
		out << manip::write_le_int32(1);
		Employee::print_bin(out);
		out << manip::write_bool(_has_bonus);
	}

	void Developer::get_text(std::istream& in){
		Employee::get_text(in);
		 in >> _has_bonus;
	}

	void Developer::get_bin(std::ifstream& in){
		Employee::get_bin(in);
		in >> manip::read_bool(_has_bonus);
	}

	void SalesManager::print_text(std::ostream& out) const{
		out << "Sales Manager" << std::endl;
		Employee::print_text(out);
		out << "Sold items: " << _sold_nm << std::endl << "Item price: " << _price;
	}

	void SalesManager::print_bin(std::ofstream& out) const{
		out << manip::write_le_int32(2);
		Employee::print_bin(out);
		out << manip::write_le_int32(_sold_nm) << manip::write_le_int32(_price);
	}

	void SalesManager::get_text(std::istream& in){
		Employee::get_text(in);
		in >> _sold_nm >> _price;
	}

	void SalesManager::get_bin(std::ifstream& in){
		Employee::get_bin(in);
		in >> manip::read_le_int32(_sold_nm) >> manip::read_le_int32(_price);
	}
	std::istream& operator>>(std::istream& in, Employee& emp){
		emp.get_text(in);
		return in;
	}

	std::ifstream& operator>>(std::ifstream& in, Employee& emp){
		emp.get_bin(in);
		return in;
	}

	std::ostream& operator<<(std::ostream& out, Employee& emp){
		emp.print_text(out);
		return out;
	}

	std::ofstream& operator<<(std::ofstream& out, Employee& emp){
		emp.print_bin(out);
		return out;
	}

	EmployeesArray::EmployeesArray(){
		_employees = std::vector<Employee*>();
	}
	EmployeesArray::~EmployeesArray(){
		for (size_t i = 0; i < _employees.size(); ++i){
			delete _employees[i];
		}
	}

	std::ostream& operator<<(std::ostream& out, const EmployeesArray& arr){
		for (size_t i = 0; i < arr._employees.size(); ++i){
			out << i + 1 << ". " << *arr._employees[i] << std::endl;
		}
		out << "== Total salary: " << arr.total_salary() << std::endl << std::endl;
		return out;
		
	}
	std::ofstream& operator<<(std::ofstream& out, const EmployeesArray& arr){
		out << manip::write_le_int32((int32_t)arr._employees.size());
		for (size_t i = 0; i < arr._employees.size(); ++i){
			out << *arr._employees[i];
		}
		return out;
	}

	std::ifstream& operator>>(std::ifstream& in, EmployeesArray& arr){
		int32_t num;
		in >> manip::read_le_int32(num);
		for (int32_t i = 0; i < num; ++i){
			int32_t type;
			in >> manip::read_le_int32(type);
			if (type == 1){
				Employee* e = new Developer();
					in >> *e;
					arr.add(e);
			}
			else if (type == 2){
				Employee* e = new SalesManager();
					in >> *e;
					arr.add(e);
			}
			
		}
		return in;
	}
	std::istream& operator>>(std::istream& in, EmployeesArray& arr){
		int type;
		in >> type;
		if (type == 1){
			Employee* e = new Developer();
			in >> *e;
			arr.add(e);
		}
		else if (type == 2){
			Employee* e  = new SalesManager();
			in >> *e;
			arr.add(e);
		}
		return in;
	}

}


