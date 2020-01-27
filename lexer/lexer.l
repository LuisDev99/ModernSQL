%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "tokens.h"

%}

%option c++
%option outfile="Scanner.cpp"
%option case-insensitive
%option noyywrap


COMMENT (["//".*])|("/*"[A-Za-z][0-9]"*/")
WHITESPACE [\t\r\f" "]
WHATUP [azxsdssd]

IDENTIFIER ({LETTER}|"_")({LETTER}|{DIGIT})*

STRING_LITERAL ["]({LETTER}|{DIGIT}|" "|[%=@,-=()_])*["]
DATE_LITERAL {DIGIT}{DIGIT}"/"{DIGIT}{DIGIT}"/"{DIGIT}{DIGIT}{DIGIT}{DIGIT}

DIGIT [0-9]
LETTER [a-zA-Z]

INT_LITERAL {DIGIT}+
FLOAT_LITERAL {DIGIT}+"."{DIGIT}+


%%

"select"      { return Select;                          } 
"create"      { return Create;                          }
"insert"      { return Create;                          }
"update"      { return Update;                          }          
"delete"      { return Delete;                          }          
"where"       { return Where;                           }      
"using"       { return Using;                           }              
"on"          { return On;                              }      
"("           { return Open_Par;                        }  
")"           { return Close_Par;                       }  
"{"           { return Open_Brace;                      }  
"}"           { return Close_Brace;                     }  
"true"        { return Bool_Literal;                    }      
"false"       { return Bool_Literal;                    }      
"..."         { return Spread_Operator;                 }
"."           { return Dot_Operator;                    }  
"=="          { return Logical_Equal_Operator;          }      
"="           { return Assign_Operator;                 }  
"!"           { return Logical_Not_Operator;            }  
"not"         { return Logical_Not_Operator;            }    
"||"          { return Logical_Or_Operator;             }      
"or"          { return Logical_Or_Operator;             }      
"&&"          { return Logical_And_Operator;            }      
"and"         { return Logical_And_Operator;            }  
">"           { return Logical_GreaterThan_Operator;    }  
"<"           { return Logical_LessThan_Operator;       }  
">="          { return Logical_GreaterEqual_Operator;   }      
"<="          { return Logical_LessEqual_Operator;      }      



{IDENTIFIER}    { return Identifier;}


{INT_LITERAL}    { return Int_Literal;}
{FLOAT_LITERAL}  { return Float_Literal;}
{STRING_LITERAL} { return String_Literal;}
{DATE_LITERAL}   { return Date_Literal;}


{WHITESPACE}    {}
{COMMENT}       {}

.               { return ERROR;  }


%%
