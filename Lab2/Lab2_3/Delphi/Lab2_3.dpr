Program Lab2_3;

Uses
    System.SysUtils;

Type
    TArr = Array Of Array Of Integer;

Function WriteInMatrix(N: Integer): TArr;

Var
    ArrayA: TArr;
    Number, I, J: Integer;

Begin

    Number := 0;
    I := 0;
    J := 0;

    SetLength(ArrayA, N);
    For I := 0 To High(ArrayA) Do
        SetLength(ArrayA[I], N);

    For I := 0 To High(ArrayA) Do
        For J := 0 To High(ArrayA[I]) Do
        Begin
            Write('Write element [', I + 1, ',', J + 1, '] of matrix: ');
            ReadLn(Number);
            ArrayA[I, J] := Number;
        End;

    WriteInMatrix := ArrayA;

End;

Procedure WriteOutMatrix(ArrayA: TArr);

Var
    I, J: Integer;

Begin

    I := 0;
    J := 0;

    For I := 0 To High(ArrayA) Do
    Begin
        For J := 0 To High(ArrayA[I]) Do
            Write(ArrayA[I, J], ' ');
        WriteLn;
    End;

End;

Function SortConditional(ArrayA: TArr): TArr;

Var
    I, J, K, Limiter, BoubleSortLimiter: Integer;

Begin
    I := 0;
    J := 0;
    Limiter := High(ArrayA);
    BoubleSortLimiter := Length(ArrayA) * (Length(ArrayA) Div 2);

    For K := 1 To BoubleSortLimiter Do
    Begin

        Limiter := High(ArrayA);

        For I := 0 To High(ArrayA) Do
        Begin

            If Odd(I) Then
            Begin

                If I = 2 * (Length(ArrayA) Div 2) Then
                    Limiter := High(ArrayA) - 1;

                For J := 0 To Limiter Do
                Begin

                    If (J + 1 < High(ArrayA[I])) Or (J + 1 = High(ArrayA[I])) Then // Можно запихнуть в функцию
                    Begin

                        If ArrayA[I, J] < ArrayA[I, J + 1] Then
                        Begin
                            ArrayA[I, J] := ArrayA[I, J] + ArrayA[I, J + 1];
                            ArrayA[I, J + 1] := ArrayA[I, J] - ArrayA[I, J + 1];
                            ArrayA[I, J] := ArrayA[I, J] - ArrayA[I, J + 1];
                        End;

                    End
                    Else
                    If (I + 2 < High(ArrayA)) Or (I + 2 = High(ArrayA)) Then
                    Begin

                        If ArrayA[I, J] < ArrayA[I + 2, 0] Then
                        Begin
                            ArrayA[I, J] := ArrayA[I, J] + ArrayA[I + 2, 0];
                            ArrayA[I + 2, 0] := ArrayA[I, J] - ArrayA[I + 2, 0];
                            ArrayA[I, J] := ArrayA[I, J] - ArrayA[I + 2, 0];
                        End;

                    End;

                End;

            End;

        End;
    End;

    SortConditional := ArrayA;

End;

Var
    MyArray: TArr;
    N: Integer;

Begin

    N := 1;

    WriteLn('The program takes a two-dimensional square matrix of order n and arranges the elements of the rows with even numbers of the matrix in descending order.');

    Write('Write the order of the matrix: ');
    ReadLn(N);

    MyArray := WriteInMatrix(N);
    MyArray := SortConditional(MyArray);
    WriteOutMatrix(MyArray);

    ReadLn;

End.
