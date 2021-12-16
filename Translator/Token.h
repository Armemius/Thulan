#pragma once

#include <string>

namespace Translator {
	namespace Lexer {
		enum Types {
			VALUE,
			ID,
			BRACKETS,
			BLOCK,
			COMMENT,
			STRING,
			KEYWORD,
			TYPE,
			OPERATION,
			GRAMMAR,
			ENDLINE,
			SPACE
		};

		std::string Type2string(Types type) {
			switch (type)
			{
			case VALUE:
				return "Value";
				break;
			case ID:
				return "Id";
				break;
			case BRACKETS:
				return "Brackets";
				break;
			case BLOCK:
				return "Block";
				break;
			case COMMENT:
				return "Comment";
				break;
			case STRING:
				return "String";
				break;
			case KEYWORD:
				return "Keyword";
				break;
			case OPERATION:
				return "Operation";
				break;
			case GRAMMAR:
				return "Grammar";
				break;
			case ENDLINE:
				return "Endline";
				break;
			case SPACE:
				return "Space";
				break;
			case TYPE:
				return "Type";
				break;
			default:
				return "Not defined";
				break;
			}
		}

		public struct Token {
			Types type;
			std::string value;
		};
	}
}