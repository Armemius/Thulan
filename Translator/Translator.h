#pragma once

#include <exception>

#include "Lexer.h"
#include "Token.h"
#include <msclr\marshal_cppstd.h>

namespace Translator {
	public ref class Program
	{
	public:
		static void main() {
			
		}
		
		static void parseFile(System::String^ path) {
			setlocale(LC_ALL, "ru");
			auto tokens = Lexer::LexicParser::ParseFile(msclr::interop::marshal_as<std::string>(path));
			for (auto& it : tokens) {
				std::cout << Type2string(it.type);
				if (it.type != Lexer::ENDLINE && it.type != Lexer::SPACE)
					std::cout << " -> " << it.value;
				std::cout << "\n";
			}
		}
		
	};
}
