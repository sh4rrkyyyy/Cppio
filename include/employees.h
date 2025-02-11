#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED
#include <vector>
#include <stdint.h>
#include <istream>
#include <ostream>
#include <fstream>
#include <string>
#include <cstring>
namespace employee{
  class Employee{
  public:
    Employee(std::string name = "", int32_t base_salary = 0);
    virtual ~Employee() {};
    virtual int salary() const = 0;
    virtual void print_text(std::ostream& out) const = 0;
    virtual void print_bin(std::ofstream& out) const = 0;
    virtual void get_text(std::istream& in) = 0;
    virtual void get_bin(std::ifstream& in) = 0;

    friend std::istream& operator>>(std::istream& in, Employee& emp);
    friend std::ostream& operator<<(std::ostream& out, const Employee& emp);
    friend std::ifstream& operator>>(std::ifstream& in, Employee& emp);
    friend std::ofstream& operator<<(std::ofstream& out, const Employee& emp);

  protected:
    std::string _name;
    int32_t _base_salary;

  };
  class Developer : public Employee{
  public:
    Developer(std::string name = "", int32_t base_salary = 0, bool has_bonus = false);
    int salary() const override;

    void print_text(std::ostream& out) const override;
    void print_bin(std::ofstream& out) const override;
    void get_text(std::istream& in) override;
    void get_bin(std::ifstream& in) override;
  private:
    bool _has_bonus;
  };

  class SalesManager : public Employee{
  public:
    SalesManager(std::string name = "", int32_t base_salary = 0, int32_t sold_nm = 0, int32_t price = 0);
    int salary() const override;

    void print_text(std::ostream& out) const override ;
    void print_bin(std::ofstream& out) const override;
    void get_text(std::istream& in) override;
    void get_bin(std::ifstream& in) override;
  private:
    int32_t _sold_nm, _price;
  };

  class EmployeesArray {
  public:
    EmployeesArray();
    ~EmployeesArray();
    void add(Employee *emp);
    int total_salary() const;
    friend std::ostream& operator<<(std::ostream& out, const EmployeesArray& arr);
    friend std::ofstream& operator<<(std::ofstream& out, const EmployeesArray& arr);
    friend std::ifstream& operator>>(std::ifstream& in, EmployeesArray& arr);
    friend std::istream& operator>>(std::istream& in, EmployeesArray& arr);
  private:
    std::vector<Employee*>_employees;
  };
}

#endif
