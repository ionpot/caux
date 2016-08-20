#include "def.h"
#include "chr.h"

int
is_upper(char b)
{
	return ASC('A', b, 'Z');
}

int
is_lower(char b)
{
	return ASC('a', b, 'z');
}

int
is_alpha(char b)
{
	return is_upper(b)
		|| is_lower(b)
		|| (b == '_');
}

int
is_num(char b)
{
	return ASC('0', b, '9');
}

int
is_alphanum(char b)
{
	return is_alpha(b) || is_num(b);
}

int
is_ws(char b)
{
	return (b == ' ') || (b == '\t');
}

int
utf8_trailing(char b)
{
	if (b < 0x80) {
		return 0;
	}

	if (b < 0xE0) {
		return 1;
	}

	if (b < 0xF0) {
		return 2;
	}

	if (b < 0xF8) {
		return 3;
	}

	return 0;
}

int
utf8_continuation(char b)
{
	return ASC(0x80, b, 0xBF);
}
