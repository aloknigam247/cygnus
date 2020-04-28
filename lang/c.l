%{
#include "c-bison.h"
%}
%%
[a-z]+ { return TYPE; }
%%