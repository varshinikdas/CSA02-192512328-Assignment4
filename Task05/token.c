#include "token.h"
int shared_counter = 1000;
int next_token_extern(void) { return ++shared_counter; }
