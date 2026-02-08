Program Test2;

uses
  SysUtils;

Var
    N, I: Integer;
    Str: String;

Begin
    Readln(N);
    Str := IntToStr(N);
    I := Length(Str);
    While (I > 3) Do
    Begin
        Dec(I, 3);
        Insert(' ', Str, I + 1);
    End;
    Writeln(Str);
    Readln;

End.
