Uses SysUtils;

Type
    TIntArray = Array [0 .. 19] Of Integer;

Procedure WriteAnswers(Var Arr: TIntArray; Size: Integer);
begin
    asm

        push esi
        push edi
        push ebx
        push ecx

        mov esi, Arr
        mov ecx, Size

    @@next:
        mov eax, [esi]      // загрузка элемента массива
        xor edx, edx
        mov ebx, 5
        div ebx

        cmp edx, 0           // Проверка отстатка
        jz @@skip

        mov dword ptr [esi], 0

    @@skip:
        add esi, 4
        loop @@next

        pop ecx
        pop ebx
        pop edi
        pop esi

    end;
end;

Var
    Arr: TIntArray;
    I, Count: Integer;

Begin
    Count := 0;

    Randomize;

    Writeln('Программа генерирует массив из 10 элементов и выводит элементы, которые кратны 5 и их колличество.');

    For I := 0 To 19 Do
        Arr[I] := Random(999) + 1;

    Write('Массив:          ');
    For I := 0 To 19 Do
        Write(Arr[I]:6);
    WriteLn;

    WriteAnswers(Arr, 20);

    Write('После обработки: ');
    For I := 0 To 19 Do
        If (Arr[I] > 0) Then
        Begin
            Write(Arr[I]:6);
            Inc(Count);
        End
        Else
            Write('      ');
    WriteLn;

    WriteLn('Колличество: ', count);

    ReadLn;
End.
