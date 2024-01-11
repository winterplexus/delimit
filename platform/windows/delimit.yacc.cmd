cd ..\..\delimit\src

if exist y.tab.c ( 
     del y.tab.c
)
if exist y.tab.h ( 
     del y.tab.h
)
if exist parse.c ( 
     del parse.c
)
if exist parse.h ( 
     del parse.h
)

yacc.exe -d parse.y

ren y.tab.c parse.c
ren y.tab.h parse.h

cd ..\..\platform\windows