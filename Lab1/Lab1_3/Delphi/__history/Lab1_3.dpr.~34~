Program Lab1_3;

Uses
  System.SysUtils;

//Const
//    EPSILON: Real = 0.0001;

Var
    X0, X1, Derivative, LowerLimit, UpperLimit, FuncFromXEqualX, Epsilon : Real;
    Count : Integer = 0;

Begin

    X0 := 0.0;
    X1 := 0.0;
    Derivative := 0.0;
    LowerLimit := 0.0;
    UpperLimit := 1.0;

    WriteLn('Программа находит корень уравнения ln(7,622x) – 8,59х + 5 = 0 с точностью эпсилон методом простой итерации.');
    WriteLn('Введите число эпсилон, рекомендуемое значение от 0.1');
    ReadLn(Epsilon);

    //ReadLn(LowerLimit);
    //ReadLn(UpperLimit);

    X1 := (LowerLimit + UpperLimit) / 2;
    X0 := X1;

    FuncFromXEqualX := (ln(7.622*X0) + 5) / 8.59;

    Derivative := 1 / (8.59 * X0);

    If Abs(Derivative) < 1 Then
    Begin
        Repeat
            Count := Count + 1;
            X0 := X1;
            FuncFromXEqualX := (ln(7.622 * X0) + 5) / 8.59;
            X1 := FuncFromXEqualX;

        Until ((Abs(X1 - X0)) < EPSILON) Or (Count > 100);
        WriteLn('X = ', X1:3:10, '  ', count);
    End
    Else
    Begin
        WriteLn('Корней методом простой итерации на данном промежутке найти не удалось')
    End;

    ReadLn;
End.
