program coursework;

uses
  Vcl.Forms,
  Unit1 in 'Unit1.pas' {GameForm},
  Unit2 in 'Unit2.pas' {InstructionForm};

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TGameForm, GameForm);
  Application.CreateForm(TInstructionForm, InstructionForm);
  Application.Run;
end.
