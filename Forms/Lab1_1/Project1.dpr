program Project1;

uses
  Vcl.Forms,
  Unit1 in 'Unit1.pas' {MainForm},
  Unit2 in '..\Lab1_2\Unit2.pas' {GuideForm},
  Vcl.Themes,
  Vcl.Styles,
  Unit3 in 'Unit3.pas' {CloseForm};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;
end.
