#pragma once

#include <exception>

#include "Lexer.h"
#include "Token.h"
#include <msclr\marshal_cppstd.h>

using namespace System::Collections::Generic;
using msclr::interop::marshal_as;

namespace Translator {
	public ref class Lexic {
	public:
		static void main() {
			
		}
		static List<System::Tuple<int, System::String^>^>^ parseFile(System::String^ path) {
			setlocale(LC_ALL, "ru");
			auto tokens = Lexer::LexicParser
				::ParseFile(marshal_as<std::string>(path));
			Lexer::LexicParser::Normalize(&tokens);

			auto list = gcnew List<System::Tuple<int, System::String^>^>();
			
			for (auto& it : tokens) {
				list->Add(gcnew System::Tuple<int, System::String^>
					(it.type, marshal_as<System::String^>(it.value)));
			}

			return list;
		}
		
	};
}
