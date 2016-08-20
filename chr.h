#ifndef CHR_H
#define CHR_H

int is_upper(char);
int is_lower(char);
int is_alpha(char);
int is_num(char);
int is_alphanum(char);
int is_ws(char);

int utf8_trailing(char);
int utf8_continuation(char);

#endif
