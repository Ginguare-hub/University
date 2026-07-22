//Program Test2;
//
//Uses
//  SysUtils;
//
//var
//  Value: Integer;
//  Ptr:  ^Integer;
//  Ptr2: ^Integer;
//
//begin
//    Value := 42;
//    Writeln(Value);
//
//    Ptr := @Value;
//    Ptr^ := 100;
//    Writeln(Value);
//
//    Ptr2 := @Ptr^;
//    Ptr2^ := 10;



program Test2;

uses
  SysUtils;

Type
    PInt = ^Integer;

var
    Value: Integer;
    Ptr: PInt;
    Ptr2: PInt;

begin
  Value := 42;
  Writeln(Value);

  Ptr := @Value;
  Ptr^ := 100;
  Writeln(Value);

  Ptr2 := Ptr;
  Ptr2^ := 10;
  Writeln(Value);
  readln;
end.

