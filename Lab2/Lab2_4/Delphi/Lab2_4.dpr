Program Lab2_4;

{$APPTYPE CONSOLE}
{$R *.res}

uses
  System.SysUtils;

Type
    TArrC = Array Of Char;

    //Õ¿œ»—¿“‹ ‘”Õ ÷»ﬁ œ–Œ¬≈– »

Function PowerOfTwo(Power: Integer): Integer;

Var
    I, Answer: Integer;

Begin
    // œ–Œ¬≈– ¿ Õ≈ Ã≈Õ‹ÿ≈ À» «¿ 0 » Õ≈ ¡ŒÀ‹ÿ≈ «¿ ~30
    Answer := 1;

    For I := 1 To Power Do
        Answer := Answer * 2;

    PowerOfTwo := Answer;

End;

Function TetradeToHexidecimal(Tetrade: Integer): Char;

Var
    CArray: TArrC;
    Answer, I: Integer;

Begin
    Answer := 0;
    I := 0;
    CArray := ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'];

    While Tetrade <> 0 Do
    Begin

        Answer := Answer + (Tetrade mod 10) * PowerOfTwo(I);
        Tetrade := Tetrade div 10;

        I := I + 1;
    End;

    TetradeToHexidecimal := CArray[Answer];
End;


//Function BinatyArrayLength


Function BinaryToHexidecimal(BNumber: Integer): TArrC;

Const
    Base: Integer = 2;

Var
    Counter, Tetrade, ALength: Integer;
    AnswerArray: TArrC;

Begin
    ALength := BNumber div 10000;
    If BNumber mod 10000 > 0 Then
        ALength := ALength + 1;

    Counter := 0;

    SetLength(AnswerArray, ALength);

    While BNumber <> 0 Do
    Begin

        Tetrade := BNumber mod 10000;
        BNumber := BNumber div 10000;

        AnswerArray[Counter] := TetradeToHexidecimal(Tetrade);

        //WriteLn(AnswerArray[Counter]);

        Counter := Counter + 1;
    End;

End;

Procedure WriteOutArray(ArrayA: TArrC);

Var
    I: Integer;

Begin

    I := 0;

    For I := High(ArrayA) DownTo 0 Do
        Write(ArrayA[I], ' ');

End;

Var
    A: TArrC;

Begin

//    SetLength(A, 4);
//
//    A := ['1'];
//
//    WriteOutArray(A);

    WriteOutArray(BinaryToHexidecimal(1));





    ReadLn;
End.
