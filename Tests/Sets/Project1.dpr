Program SetsTest;

Uses
  System.SysUtils;

Var
    MySet: Set of 0..255;
    I, CountOfSet, Number: Integer;

Begin
    MySet := [];
    ReadLn(CountOfSet);

    For I := 1 To CountOfSet Do
    Begin
        ReadLn(Number);
        Include(MySet, Number);
    End;

    For I := 0 To 255 Do
        If I In MySet Then
            WriteLn(I);

    ReadLn;

End.
