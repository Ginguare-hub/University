Unit Unit1;

Interface

Uses
    Winapi.Windows,
    Winapi.Messages,
    System.SysUtils,
    System.Variants,
    System.Classes,
    Vcl.Graphics,
    Vcl.Controls,
    Vcl.Forms,
    Vcl.Dialogs,
    Vcl.Menus,
    Vcl.StdCtrls,
    Vcl.Grids,
    Vcl.ExtDlgs,
    Unit2;

Type
    TMainForm = Class(TForm)
        MainMenu: TMainMenu;
        FileTub: TMenuItem;
        InstructonTub: TMenuItem;
        AboutDeveloperTub: TMenuItem;
        OpenTubButton: TMenuItem;
        SaveTubButton: TMenuItem;
        CloseTubButton: TMenuItem;
        Separator3: TMenuItem;
        TaskLabel: TLabel;
        NumberNEdit: TEdit;
        ResultButton: TButton;
        OpenTextFileDialog: TOpenTextFileDialog;
        SaveTextFileDialog: TSaveTextFileDialog;
        Separator2: TMenuItem;
        Separator1: TMenuItem;
    AnswerEdit: TEdit;
        SaveDialog: TSaveDialog;
        OpenDialog: TOpenDialog;
        Procedure ResultButtonClick(Sender: TObject);
    procedure NumberNEditChange(Sender: TObject);
    Private
        { Private declarations }
    Public
        { Public declarations }
    End;

Var
    MainForm: TMainForm;

Implementation

{$R *.dfm}

Procedure TMainForm.ResultButtonClick(Sender: TObject);
Var
    Number, CurrNumber, Answer, I: Integer;
Begin
    Answer := 0;
    CurrNumber := 1;
    I := 1;

    Number := StrToInt(NumberNEdit.Text);

    For I := 1 To Number Do
    Begin
        CurrNumber := CurrNumber * -2;
        Answer := Answer + CurrNumber;
    End;

    AnswerEdit.Text := IntToStr(Answer);
End;


procedure TMainForm.NumberNEditChange(Sender: TObject);
begin
    //
    ResultButton.Enabled := Not String.IsNullOrEmpty(NumberNEdit.Text);
end;

End.
