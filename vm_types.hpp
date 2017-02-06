#pragma once

#include <cinttypes>
#include <ostream>
#include <vector>
#include <iostream>


enum class op {
	halt, // Halts execution of the VM
	noop, // No operations happens

	mov,  // Move value from r1 to r2
	push, // Push value from r1 to top of stack
	pop,  // Pop value from top of stack to r1

	add,  // Add value of r1 to r2
	sub,  // Subtract value of r1 from r2
	mul,  // Multiply value of r2 by 41
	div,  // Divide value of r2 by r1

	mod,  // Remainder of the integer division r2/r1

	cil,  // Copy integer literal to r1
	cfl,  // Copy floating point literal to r1

	ofv,  // Output formated value of r1 to stdout
	onl,  // Output a newline to stdout and flush it

	cmp,  // Compare r1 and r2
	cmpz, // Compare r1 to zero

	jmp,  // Jump to label
	jgt,  // Jump to label if last comparison was `true` for `>`
	jeq,  // Jump to label if last comparison was `true` for `=`
	jlt,  // Jump to label if last comparison was `true` for `<`
};

// Implement the "<<" ostream operator for op
std::ostream &operator<<(std::ostream &os, op const &o);


enum class var_type {
	integer,
	floating,
	operation,
};


class var {
private:
	var_type type;

	union {
		int64_t i;
		double f;
		op o;
	} value;

public:
	var() = delete; // No default constructor
	var(int64_t i) : type(var_type::integer) { value.i = i; };
	var(double f) : type(var_type::floating) { value.f = f; };
	var(op o) : type(var_type::operation) { value.o = o; };

	var_type get_type() const { return type; };

	// Assignment operator overloading
	var operator=(const int64_t &rhs) {
		type = var_type::integer;
		value.i = rhs;
		return *this;
	};
	var operator=(const double &rhs) {
		type = var_type::floating;
		value.f = rhs;
		return *this;
	};
	var operator=(const op &rhs) {
		type = var_type::operation;
		value.o = rhs;
		return *this;
	};

	// @TODO Maybe add type checking. If an attempt is made to get `as_T`
	// when type is not T, throw a runtime error.
	int as_int() const { return value.i; };
	double as_float() const { return value.f; };
	op as_op() const { return value.o; };
};

// Implement the "<<" ostream operator for 'var'
std::ostream &operator<<(std::ostream &os, var const &v);


class Code {
private:
	std::vector<var> data;

public:
	int curr_index;

	Code() : data(std::vector<var>()), curr_index(0) {};


	void push_op(op o) {
		curr_index++;
		data.push_back(var(o));
	};
	void push_int(int64_t i) {
		curr_index++;
		data.push_back(var(i));
	};
	void push_float(double f) {
		curr_index++;
		data.push_back(var(f));
	};


	void display() const {
		auto it = data.begin();
		it++;

		while (true) {
			if (it == data.end()) {
				std::cout << std::endl;
				return;
			}

			std::cout << std::endl;
			switch (it->as_op()) {
			case op::halt:
				std::cout << it->as_op();
				it++;
				break;

			case op::noop:
				std::cout << it->as_op();
				it++;
				break;

			case op::mov:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::push:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::pop:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::add:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::sub:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::mul:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::div:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::mod:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::cil:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::cfl:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_float() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::ofv:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::onl:
				std::cout << it->as_op();
				it++;
				break;

			case op::cmp:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::cmpz:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::jmp:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::jgt:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::jeq:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			case op::jlt:
				std::cout << it->as_op() << '\t';
				it++;
				std::cout << it->as_int();
				it++;
				break;

			default:
				std::cout << "????";
			}
		}
	};
};
