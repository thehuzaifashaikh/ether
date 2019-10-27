/* 2019 Huzaifa Shaikh. All Rights Reserved. */

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define internal static
#define SINGLE_CHAR_TOKEN(type) \
	return new token_t(m_start, ++m_current, type, m_line);

#ifdef _WIN32
enum color_e {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1, 
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_LIGHTBLUE = 9,
	COLOR_LIGHTGREEN = 10,
	COLOR_LIGHTCYAN = 11,
	COLOR_LIGHTRED = 12,
	COLOR_LIGHTMAGENTA = 13,
	COLOR_YELLOW = 14,
	COLOR_WHITE = 15,
};
#elif __linux__
enum color_e {
	COLOR_BLACK = 30,
	COLOR_BLUE = 34, 
	COLOR_GREEN = 32,
	COLOR_CYAN = 36,
	COLOR_RED = 31,
	COLOR_MAGENTA = 35,
	COLOR_LIGHTBLUE = 94,
	COLOR_LIGHTGREEN = 92,
	COLOR_LIGHTCYAN = 96,
	COLOR_LIGHTRED = 91,
	COLOR_LIGHTMAGENTA = 95,
	COLOR_YELLOW = 33,
	COLOR_WHITE = 37,
};
#endif

enum token_type {
	TOKEN_TAB,
	TOKEN_NEWLINE,
	TOKEN_PLUS,
	TOKEN_NIMUS,
	TOKEN_STAR,
	TOKEN_SLASH,
	TOKEN_BANG,
	TOKEN_CARET,
	TOKEN_AMPERSAND,
	TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_PAREN,
	TOKEN_LEFT_BRACKET,
	TOKEN_RIGHT_BRACKET,
	TOKEN_QUESTION,
	TOKEN_DOT,
	TOKEN_COMMA,
	TOKEN_LEFT_ANGLE_BRACKET,
	TOKEN_RIGHT_ANGLE_BRACKET,
	TOKEN_EQUAL,
	TOKEN_INT,
	TOKEN_FLOAT,
	TOKEN_DOUBLE,
	TOKEN_IDENTIFIER,
	TOKEN_STR,
	TOKEN_CHAR,
	TOKEN_EOF,
};

void change_terminal_color(color_e p_forecolor);

struct token_t {
	token_t(void) {
		start = NULL;
		end = NULL;
		type = TOKEN_EOF;
		line = 0;
	}

	token_t(const char* p_start, const char* p_end,
		  token_type p_type, unsigned int p_line) {
		start = p_start;
		end = p_end;
		type = p_type;
		line = p_line;
	}

	const char* 
	type_str(void) {
		switch (type) {
		case TOKEN_TAB: return "tab"; break;
		case TOKEN_NEWLINE: return "newline"; break;
		case TOKEN_PLUS: return "plus"; break;
		case TOKEN_NIMUS: return "minus"; break;
		case TOKEN_STAR: return "star"; break;
		case TOKEN_SLASH: return "slash"; break;
		case TOKEN_BANG: return "bang"; break;
		case TOKEN_CARET: return "caret"; break;
		case TOKEN_AMPERSAND:	return "ampersand"; break;
		case TOKEN_LEFT_PAREN: return "left paren"; break;
		case TOKEN_RIGHT_PAREN: return "right paren"; break;
		case TOKEN_LEFT_BRACKET: return "left bracket"; break;
		case TOKEN_RIGHT_BRACKET: return "right bracket"; break;
		case TOKEN_QUESTION: return "question"; break;
		case TOKEN_DOT: return "dot"; break;
		case TOKEN_COMMA: return "comma"; break;
		case TOKEN_LEFT_ANGLE_BRACKET: return "left angle bracket"; break;
		case TOKEN_RIGHT_ANGLE_BRACKET: return "right angle bracket"; break;
		case TOKEN_EQUAL: return "equal"; break;
		case TOKEN_INT: return "integer"; break;
		case TOKEN_FLOAT: return "float"; break;
		case TOKEN_DOUBLE: return "double"; break;
		case TOKEN_IDENTIFIER: return "identifier"; break;
		case TOKEN_STR: return "string"; break;
		case TOKEN_CHAR: return "char"; break;
		case TOKEN_EOF: return "eof"; break;
		default: break;
		}
		return "";
	}

	void 
	print_lexeme(void) {
		unsigned int spaces_to_print = 20;
		const char* c = start;

		while (c != end) {
			if (*c == '\n') {
				printf("<newline>");
				spaces_to_print -= 8;
			}
			else if (*c == '\t') {
				printf("<tab>");
				spaces_to_print -= 4;
			}
			else {
				printf("%c", *c);
			}
			++c;
			--spaces_to_print;
		}

		for (; spaces_to_print > 0; --spaces_to_print) {
			printf(" ");
		}
	}

	const char* start;
	const char* end;
	token_type type;
	unsigned int line;
};

class lexer_t {
public:
	void 
	init(std::string* p_stream, std::string p_stream_name) {
		m_stream = p_stream;
		m_stream_name = p_stream_name;
		m_start = m_stream->c_str();
		m_current = m_stream->c_str();
		m_line = 1;
		m_line_beginning = m_start;
	}

	token_t*
	get_next_token(void) {
		if (is_end_of_file()) {
			return nullptr;
		} 
		m_start = m_current;

		switch (*m_start) {
		case '\r':
		case ' ':
			m_current++;
			return get_next_token();
			break;

		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I':
		case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
		case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z': case 'a':
		case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j':
		case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's':
		case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z': case '_':
			while (isalnum(*m_current) || *m_current == '_') {
				++m_current;
			}
			return new token_t(m_start, m_current, TOKEN_IDENTIFIER, m_line);
			break;

		case '0': case '1':
		case '2': case '3':
		case '4': case '5':
		case '6': case '7':
		case '8': case '9': 
			while (isdigit(*m_current)) {
				++m_current;
			}
			if (*m_current == '.') {
				++m_current;
				if (*m_current == 'f') {
					lex_error("incomplete float constant");
				} 
				else if (!isdigit(*m_current)) {
					lex_error("incomplete double constant");
				} 
				
				while (isdigit(*m_current)) {
					++m_current;
				}
				if (*m_current == 'f') {
					return new token_t(m_start, ++m_current, TOKEN_FLOAT, m_line);
				}
				return new token_t(m_start, m_current, TOKEN_DOUBLE, m_line);
			} 
			return new token_t(m_start, m_current, TOKEN_INT, m_line);
			break;

		case '\"':
			++m_start;
			++m_current;
			while (*m_current != '"') {
				if (is_end_of_file()) {
					lex_error("unterminated string");
					return nullptr;
				}
				++m_current;
			}
			return new token_t(m_start, m_current++, TOKEN_STR, m_line);
			break;

		case '\n':
			m_line_beginning = ++m_current;
			return new token_t(m_start, m_current, TOKEN_NEWLINE, m_line++);
			break;

		case '\t': SINGLE_CHAR_TOKEN(TOKEN_TAB); break;
		case '+': SINGLE_CHAR_TOKEN(TOKEN_PLUS); break;
		case '-': SINGLE_CHAR_TOKEN(TOKEN_NIMUS); break;
		case '*': SINGLE_CHAR_TOKEN(TOKEN_STAR); break;
		case '/': SINGLE_CHAR_TOKEN(TOKEN_SLASH); break;
		case '!': SINGLE_CHAR_TOKEN(TOKEN_BANG); break;
		case '^': SINGLE_CHAR_TOKEN(TOKEN_CARET); break;
		case '&': SINGLE_CHAR_TOKEN(TOKEN_AMPERSAND); break;
		case '(': SINGLE_CHAR_TOKEN(TOKEN_LEFT_PAREN); break;
		case ')': SINGLE_CHAR_TOKEN(TOKEN_RIGHT_PAREN); break;
		case '[': SINGLE_CHAR_TOKEN(TOKEN_LEFT_BRACKET); break;
		case ']': SINGLE_CHAR_TOKEN(TOKEN_RIGHT_BRACKET); break;
		case '?': SINGLE_CHAR_TOKEN(TOKEN_QUESTION); break;
		case '.': SINGLE_CHAR_TOKEN(TOKEN_DOT); break;
		case ',': SINGLE_CHAR_TOKEN(TOKEN_COMMA); break;
		case '<': SINGLE_CHAR_TOKEN(TOKEN_LEFT_ANGLE_BRACKET); break;
		case '>': SINGLE_CHAR_TOKEN(TOKEN_RIGHT_ANGLE_BRACKET); break;
		case '=': SINGLE_CHAR_TOKEN(TOKEN_EQUAL); break;
			
		default:
			lex_error("unexpected character");
			return nullptr;
			break;
		}
		
		return nullptr;
	}

private:
	inline bool
	is_end_of_file(void) const {
		return m_current >= (m_stream->c_str() + m_stream->size());
	}

	void
	lex_error(const std::string& p_msg) const {
		unsigned int offset_from_line_start = (unsigned int)(m_current - m_line_beginning + 1);
		printf("[%s:%u:%u]: ", m_stream_name.c_str(), m_line, offset_from_line_start);
		change_terminal_color(COLOR_LIGHTRED);
		printf("(error) ");
		change_terminal_color(COLOR_WHITE);
		printf("%s\n", p_msg.c_str());
		print_error_line(m_line, offset_from_line_start);
	}

	void
	lex_warning(const std::string& p_msg) const {
		unsigned int offset_from_line_start = (unsigned int)(m_current - m_line_beginning + 1);
		printf("[%s:%u:%u]: ", m_stream_name.c_str(), m_line, offset_from_line_start);
		change_terminal_color(COLOR_GREEN);
		printf("(warning) ");
		change_terminal_color(COLOR_WHITE);
		printf("%s\n", p_msg.c_str());
		print_error_line(m_line, offset_from_line_start);
		exit(1);
	}

	void
	print_error_line(unsigned int p_line, unsigned int p_column_to_be_highlighted) const {
		if (p_line == 0) {
			return;
		}

		const char* line_start = m_stream->c_str();
		unsigned int current_line = 1;
		while (current_line < p_line) {
			if (*line_start == '\n') {
				++current_line;
			}
			++line_start;
		}

		const char* const line_start_const = line_start;
		printf("    %d | ", p_line);
		while (true) {
			if (*line_start == '\n') break;
			else if (*line_start == '\r') break;
			else if (*line_start == '\0') break;

			bool change_color = (line_start_const + p_column_to_be_highlighted - 1) == line_start;
			if (change_color) {
				change_terminal_color(COLOR_LIGHTRED);	// TODO: save font backgrund and foreground
			}

			printf("%c", *line_start);
			++line_start;

			if (change_color) {
				change_terminal_color(COLOR_WHITE);	// TODO: save font backgrund and foreground
			}
		}
		printf("\n");
	}

private:
	std::string* m_stream;
	std::string m_stream_name;
	const char* m_start;
	const char* m_current;
	const char* m_line_beginning;
	unsigned int m_line;
};

struct decl_t {

};

struct stmt_t {

};

struct expr_t {
	
};

struct parser_data_t {
	std::vector<decl_t*> decls;
	std::vector<stmt_t*> stmts;
	std::vector<expr_t*> exprs;
	std::vector<token_t*> tokens;
};

class parser_t {
public:
	void 
	init(std::string* p_stream, std::string p_stream_name, lexer_t* p_lexer) {
		m_stream = p_stream;
		m_stream_name = p_stream_name;
		m_parser_data = new parser_data_t();
		m_lexer = p_lexer;
		
		get_tokens();
	}

	parser_data_t*
	parse(void) {
		while (parse_decl());
		return m_parser_data;	
	}

	bool
	parse_decl() {
		return false;
	}

	~parser_t(void) {
		for (unsigned int decl = 0; decl < m_parser_data->decls.size(); decl++) {
			delete m_parser_data->decls.at(decl);
		}	

		for (unsigned int stmt = 0; stmt < m_parser_data->stmts.size(); stmt++) {
			delete m_parser_data->stmts.at(stmt);
		}	

		for (unsigned int expr = 0; expr < m_parser_data->exprs.size(); expr++) {
			delete m_parser_data->exprs.at(expr);
		}	

		for (unsigned int token = 0; token < m_parser_data->tokens.size(); token++) {
			delete m_parser_data->tokens.at(token);
		}	

		delete m_parser_data;
	}

private:
	void
	get_tokens(void) {
		token_t* token;
		while ((token = m_lexer->get_next_token()) != nullptr) {
			m_parser_data->tokens.push_back(token);
		}
		m_parser_data->tokens.push_back(new token_t()); // EOF token
	}

private:
	std::string* m_stream;
	std::string m_stream_name;
	parser_data_t* m_parser_data;
	lexer_t* m_lexer;
};

internal std::string*
read_file(const std::string& p_path) {
	std::ifstream file(p_path, std::ios::binary);
	if (file.fail()) {
		printf("[ERROR][%s]: unable to open file\n", p_path.c_str());
		exit(1);
	}

	std::string* contents = new std::string();
	std::string line;
	while (std::getline(file, line)) {
		contents->append(line + "\n");
	}
	return contents;
}

int 
main() {
	//std::string stream = "a \"hello world! + 1 _hello1 -HELLO _H 3ee";
	//std::string stream = "\"hello world\"";
	//std::string stream = "1.f 2.1f 1 10 2.0 0";
	std::string* stream = read_file("hello_world.eth");

	lexer_t l;
	l.init(stream, "hello_world.eth");

	parser_t p;
	p.init(stream, "hello_world.eth", &l);

	parser_data_t* data = p.parse();
	//for (token_t* tok: data->tokens) {
	//	tok->print_lexeme();
	//}
	delete stream;
}

void
change_terminal_color(color_e p_forecolor) {
#ifdef _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), p_forecolor);
#elif __linux__
	printf("\033[%um", (unsigned int)p_forecolor);
#endif
}

#undef internal
#undef SINGLE_CHAR_TOKEN
