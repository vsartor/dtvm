// Copyright (c) 2017 Victhor S. Sartorio. All rights reserved.
// Licensed under the MIT License. See LICENSE file in the project root.

#pragma once

#include <string>


// This namespace holds argument variables globally
// They should only be written to during the initialization phase of `main`.
namespace dtvm_args {
	// "-no-acc" or "-no-ansi-color-codes"
	// Disables the usage of ANSI color codes in the application
	extern bool no_ansi_color_codes;
	// "-parse-and-print"
	// Makes it so the application only parses and pretty print the bytecode
	// instead of also executing it
	extern bool parse_and_print;
	// "-r8" or "-r16" or "-r32"
	// Number of registers for the VM
	extern int num_regs;
	// "-e<name>"
	// Sets the entry point of the program to be the label <name>, by default it's start
	extern std::string entry_point;
};
