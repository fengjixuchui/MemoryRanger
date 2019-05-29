
#include "windows.h"
#include "stdio.h"
#include "wchar.h"
#include <tchar.h>
#include <locale.h> // LC_ALL

#include <iostream>
#include <string>

#include "mem_attacker.h" // class MemAttacker
#include "..\shared\mem_attacker_shared.h" // MEM_ATTACKER_SYS_FILE, MEM_ATTACKER_SERVNAME_APP, MEM_ATTACKER_LINKNAME_APP
#include "resource.h" // MEM_ATTACKER_RESOURCE 

#include <iostream>
#include "..\..\utils\console_font_colors.h" // add colors for the console

int wmain(int argc, wchar_t *argv[], wchar_t *envp[]) {
	argc; argv; envp; // to avoid warning C4100
	setlocale(LC_ALL, "");
	setvbuf(stdout, NULL, _IONBF, 0);
	eku::init_console_font_colors();

//	if (check_windows_support::is_ok()) 
	{
		mem_attacker :: MemAttacker attacker;
		SetConsoleTitle(MEM_ATTACKER_NAME);
		if (attacker.is_ok(MEM_ATTACKER_RESOURCE, MEM_ATTACKER_SYS_FILE, MEM_ATTACKER_SERVNAME_APP, MEM_ATTACKER_LINKNAME_APP))
		{
			mem_attacker::init_input_commands();
			do {
				mem_attacker::print_supported_commands(eku::red, MEM_ATTACKER_NAME, MEM_ATTACKER_DETAILS);
				switch (mem_attacker::parse_call(attacker)) {
				case mem_attacker::PARSE_RESULT::WRONG:
					std::cout << eku::red << "---wrong input, try again---" << endl;
					break;
				case mem_attacker::PARSE_RESULT::QUIT:
					cin.ignore();
					cout << "Press enter to exit." << endl;
					cin.ignore(); // std::system("PAUSE");
					return 0;
				}
				cin.clear();
				//cin.ignore(10000, '\n');
				fflush(stdin);
				std::cout << endl;
			} while (true);
		}
	}
}