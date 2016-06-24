#ifndef STR_H
#define STR_H

int is_upper(byte);
int is_lower(byte);
int is_alpha(byte);
int is_num(byte);
int is_alphanum(byte);
int is_ws(byte);

int utf8_trailing(byte);
int utf8_continuation(byte);

#endif
