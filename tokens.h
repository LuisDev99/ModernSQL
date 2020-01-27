#ifndef TOKENS
#define TOKENS

enum Token : unsigned char
{
    Select = 1,
    Create,
    Update,
    Delete,
    Where,
    Using,
    On,
    Open_Par,
    Close_Par,
    Open_Brace,
    Close_Brace,
    Identifier,
    Int_Literal,
    Float_Literal,
    String_Literal,
    Bool_Literal,
    Date_Literal,
    Spread_Operator,
    Dot_Operator,
    Assign_Operator,
    Logical_Not_Operator,
    Logical_Or_Operator,
    Logical_And_Operator,
    Logical_GreaterThan_Operator,
    Logical_LessThan_Operator,
    Logical_Equal_Operator,
    Logical_NotEqual_Operator,
    Logical_GreaterEqual_Operator,
    Logical_LessEqual_Operator,
    ERROR,
};

#endif //TOKENS