Unit Unit2;

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
    Vcl.Dialogs, Vcl.StdCtrls;

Type
    TGuideForm = Class(TForm)
    GuideLabel: TLabel;
    CloseButton: TButton;
    procedure CloseButtonClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);

    Private
        { Private declarations }
    Public
        { Public declarations }
    End;

Var
    GuideForm: TGuideForm;

Implementation

{$R *.dfm}

procedure TGuideForm.CloseButtonClick(Sender: TObject);
begin
    Close;
end;

procedure TGuideForm.FormCreate(Sender: TObject);
begin
    GuideLabel.Left := (ClientWidth - GuideLabel.Width) Div 2;
end;

end.
