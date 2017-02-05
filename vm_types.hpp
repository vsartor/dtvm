#pragma once

#include <cinttypes>
#include <ostream>


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
std::ostream &operator<<(std::ostream &os, op const &o)
{
	switch (o) {
	case op::halt:
		return os << "halt";
	case op::noop:
		return os << "noop";
	case op::mov:
		return os << "mov ";
	case op::push:
		return os << "push";
	case op::pop:
		return os << "pop ";
	case op::add:
		return os << "add ";
	case op::sub:
		return os << "sub ";
	case op::mul:
		return os << "mul ";
	case op::div:
		return os << "div ";
	case op::mod:
		return os << "mod ";
	case op::cil:
		return os << "cil ";
	case op::cfl:
		return os << "cfl ";
	case op::ofv:
		return os << "ofv ";
	case op::onl:
		return os << "onl ";
	case op::cmp:
		return os << "cmp ";
	case op::cmpz:
		return os << "cmpz";
	case op::jmp:
		return os << "jmp ";
	case op::jgt:
		return os << "jgt ";
	case op::jeq:
		return os << "jeq ";
	case op::jlt:
		return os << "jlt ";
	}
}


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
	var(int64_t &i) : type(var_type::integer) { value.i = i; };
	var(double &f) : type(var_type::floating) { value.f = f; };
	var(op &o) : type(var_type::operation) { value.o = o; };

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
std::ostream &operator<<(std::ostream &os, var const &v) {
	switch (v.get_type()) {
	case var_type::integer:
		return os << v.as_int();
	case var_type::floating:
		return os << v.as_float();
	case var_type::operation:
		return os << v.as_op();
	}
}
