cd ..\..\delimit\src

if exist lex.yy.c ( 
     del lex.yy.c
)
if exist lex.c ( 
     del lex.c
)

flex.exe -I lex.l

ren lex.yy.c lex.c

cd ..\..\platform\windows