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
    Vcl.ExtCtrls,
    Vcl.ComCtrls,
    Vcl.StdCtrls,
    Vcl.Menus,
    Math,
    Unit2;

Const
    MAP_WIDTH = 16;   //клеток по горизонтали (X) слева - направо
    MAP_HEIGHT = 16;  //клеток по вертикали  (Y) снизу - вверх
    CELL_SIZE = 64;   //пикселей
    MAX_TOWER_HEALTH: Integer = 20;
    START_COINS: Integer = 50;

    TURRET_PRICES: Array [0..3] Of Integer = (0, 25, 30, 55);
    TURRET_RADII: Array [0..3] Of Double = (0.0, 3.0, 4.0, 2.0);
    TURRET_FIRE_RATE: Array [0..3] Of Double = (0.0, 1.2, 1.5, 0.7);

    BULLET_DAMAGE: Array [0..3] Of Double = (0.0, 34.0, 10.0, 20.0);
    BULLET_SLOW: Array [0..3] Of Double = (0.0, 1.0, 0.9, 1.0);
    IS_BULLET_AOE: Array [0..3] Of Boolean = (False, False, False, True);       // AOE - Area Of Effect     Урон/ЭФфект по области
    IS_BULLET_TRACKING: Array  [0..3] Of Boolean = (False, True, True, False);
    BULLET_SPEED: Array [0..3] Of Double = (0.0, 3.0, 5.0, 2.0);

    ENEMY_MAX_HEALTH: Array [0..3] Of Double = (0, 100.0, 250.0, 50.0);
    ENEMY_SPEED: Array [0..3] Of Double = (0, 2.0, 1.0, 2.5);
    ENEMY_REWARD: Array [0..3] Of Integer = (0, 2, 3, 2);

Type
    TTurretType = (TurrNone, TurrCommon, TurrSlowing, TurrAreaDamaging);
    TEnemyType = (EnNone, EnCommon, EnHeavy, EnFast);
    TGroundType = (GtGrass, GtRoad, GtBase);
    TDirection = (DirNone, DirRight, DirUp, DirLeft, DirDown);

    TPosition = Record
        CellX: Integer;
        CellY: Integer;
    End;

    TTurret = Record
        TurretType: TTurretType;
        Radius: Double;
        ReloadProgress: Double;         // 0 to 1
        FireRate: Double;
    End;

    TMap = Record
        TypeOfGround: TGroundType;
        Turret: TTurret;
        EnemyDirection: TDirection;
        IsAvailibleForTurret: Boolean;
    End;

    TMatrixOfMap = Array [0 .. MAP_WIDTH - 1, 0 .. MAP_HEIGHT - 1] Of TMap;

    TEnemy = Record
        EnemyType: TEnemyType;
        Health: Double;
        MaxHealth: Double;
        Speed: Double;               //клеток в секунду
        Pos: TPosition;             //текущая клетка (X - горизонталь, Y - вертикаль)
        DistanceProgress: Double;
        Reward: Integer;
        IsAlive: Bool;
    End;

    PTEnemy = ^TEnemy;
    TEnemySpawns = Record
        EnemyID: Integer;
        StartTime: Double;
        EndTime: Double;
        EnemyCount: Integer;
        EnemyCountCurrent: Integer;
    End;

    // Сделать Record Position CellX CellY
    TBullet = Record
        DistanceProgress: Double;
        Speed: Double;
        TargetedEnemy: PTEnemy;
        TargetPos: TPosition;
        TurretPos: TPosition;
        IsTracking: Bool;   // 1 - к врагу, 0 - к клетке
    End;

    PTBulletNode = ^TBulletNode;
    PTBullet = ^TBullet;
    TBulletNode = Record
        Bullet: TBullet;
        Next: PTBulletNode;
        Prev: PTBulletNode;
    End;

    TBulletList = Record
        Head: PTBulletNode;
    End;

    PTEnemySpawnsNode = ^TEnemySpawnsNode;
    TEnemySpawnsNode = Record
        EnemySpawns: TEnemySpawns;
        Next: PTEnemySpawnsNode;
        Prev: PTEnemySpawnsNode;
    End;

    TEnemySpawnsList = Record
        Head: PTEnemySpawnsNode;
    End;

    TGameForm = Class(TForm)
    MapBox: TPaintBox;
    GameTimer: TTimer;
    TimeLabel: TLabel;
    Label1: TLabel;
    MainMenu: TMainMenu;
    MenuOptionMenu: TMenuItem;
    MenuOptionQuit: TMenuItem;
    MenuOptionAutor: TMenuItem;
    CellOptionScrollBox: TScrollBox;
    CommonTurretPanel: TPanel;
    SlowingTurretPanel: TPanel;
    SelectBox: TShape;
    AreaTurretPanel: TPanel;
    TowerHealthLabel: TLabel;
    CoinsLabel: TLabel;
    CommonTurretImage: TImage;
    SlowingTurretImage: TImage;
    AreaTurretImage: TImage;
    CommonTurretPriceLabel: TLabel;
    SlowingTurretPriceLabel: TLabel;
    AreaTurretPriceLabel: TLabel;
    MenuOptionInstruction: TMenuItem;
    Procedure MapBoxPaint(Sender: TObject);
    Procedure GameTimerTimer(Sender: TObject);
    Procedure FormCreate(Sender: TObject);
    Procedure FormDestroy(Sender: TObject);
    procedure MapBoxMouseDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
    procedure CommonTurretPanelClick(Sender: TObject);
    procedure SlowingTurretPanelClick(Sender: TObject);
    procedure AreaTurretPanelClick(Sender: TObject);
    procedure MenuOptionMenuClick(Sender: TObject);
    procedure FormCanResize(Sender: TObject; var NewWidth, NewHeight: Integer;
      var Resize: Boolean);
    function FormHelp(Command: Word; Data: THelpEventData;
      var CallHelp: Boolean): Boolean;
    procedure MenuOptionInstructionClick(Sender: TObject);
    procedure MenuOptionAutorClick(Sender: TObject);

    Private
    Public
    End;

    Function Clamp(Const MIN, MAX: Double; Value: Double): Double;

Var
    GameForm: TGameForm;

    MapData: TMatrixOfMap;
    GameTime: Double;

    GrassTex, RoadRightTex, RoadUpTex, RoadLeftTex, RoadDownTex, BaseTex, TurretCommonTex, TurretSlowingTex, TurretAreaTex: TBitmap;

    Enemies: Array Of TEnemy;
    EnemyTemplates: Array Of TEnemy;
    EnemySpawnsList: TEnemySpawnsList;

    SelectedPos: TPosition;
    Coins, TowerHealth: Integer;
    BulletList: TBulletList;

Implementation

{$R *.dfm}

//-------------------------------------------------------------------
//Функции карты
//-------------------------------------------------------------------
Procedure ClearMap(Var Map: TMatrixOfMap);
Var
    I, J: Integer;
Begin
    For I := Low(Map) To High(Map) Do
    Begin
        For J := Low(Map[I]) To High(Map[I]) Do
        Begin
            Map[I, J].TypeOfGround := TGroundType.GtGrass;
            Map[I, J].Turret.TurretType := TTurretType.TurrNone;
            Map[I, J].EnemyDirection := TDirection.DirNone;
            Map[I, J].IsAvailibleForTurret := True;
        End;
    End;
End;

Function SetMap1(): TMatrixOfMap;
Var
    MapData: TMatrixOfMap;
    I, J: Integer;
Begin
    ClearMap(MapData);

    For J := 0 To 4 Do
    Begin
        MapData[3, J].TypeOfGround := TGroundType.GtRoad;
    End;

    For I := 3 To 12 Do
    Begin
        MapData[I, 4].TypeOfGround := TGroundType.GtRoad;
    End;

    For J := 4 To 10 Do
    Begin
        MapData[12, J].TypeOfGround := TGroundType.GtRoad;
    End;

    For I := 12 DownTo 5 Do
    Begin
        MapData[I, 10].TypeOfGround := TGroundType.GtRoad;
    End;

    MapData[5, 11].TypeOfGround := TGroundType.GtRoad;

    //База
    For I := 4 To 6 Do
    Begin
        MapData[I, 12].TypeOfGround := TGroundType.GtBase;
        MapData[I, 13].TypeOfGround := TGroundType.GtBase;
    End;

    SetMap1 := MapData;
End;

Procedure WriteEnemySpawnsToFile();
Var
    Element: TEnemySpawns;
    SpawnsDataTypedFile: File Of TEnemySpawns;
    UntypedFile: TextFile;
Begin
    AssignFile(UntypedFile, '.\EnemySpawnsData.txt');
    AssignFile(SpawnsDataTypedFile, '.\EnemySpawnsData.dat');

    Reset(UntypedFile);
    Rewrite(SpawnsDataTypedFile);

    While (Not EOF(UntypedFile)) Do
    Begin
        Read(UntypedFile, Element.EnemyID);
        Read(UntypedFile, Element.StartTime);
        Read(UntypedFile, Element.EndTime);
        Read(UntypedFile, Element.EnemyCount);
        Element.EnemyCountCurrent := 0;

        Write(SpawnsDataTypedFile, Element);
    End;

    CloseFile(UntypedFile);
    CloseFile(SpawnsDataTypedFile);
End;

//-------------------------------------------------------------------
//Поиск стартовой клетки (клетка Road на краю поля)
//-------------------------------------------------------------------
Function FindStartCell(Var StartX, StartY: Integer): Boolean;
Var
    I, J: Integer;
    IsFound, IsBorder: Boolean;
Begin
    IsFound := False;
    IsBorder := False;
    StartX := -1;
    StartY := -1;

    For I := 0 To High(MapData) Do
    Begin
        For J := 0 To High(MapData[I]) Do
        Begin
            IsBorder := ((I = Low(MapData))
                         Or (I = High(MapData))
                         Or (J = Low(MapData[I]))
                         Or (J = High(MapData[I])));

            If (IsBorder And (MapData[I, J].TypeOfGround = TGroundType.GtRoad)) Then
            Begin
                IsFound := True;
                StartX := I;
                StartY := J;
            End;
        End;
    End;

    If (StartX = -1) Then
    Begin
        ShowMessage('Ошибка: Начальная клетка появления врагов не найдена');
    End;

    FindStartCell := IsFound;
End;

//-------------------------------------------------------------------
//Расчёт направлений для дорог
//-------------------------------------------------------------------
Function FindFirstDirection(Map: TMatrixOfMap): TDirection;
var
    X, Y: Integer;
begin
    FindStartCell(X, Y);

    If (X = Low(Map)) Then
    Begin
        FindFirstDirection := DirRight;
    End
    Else
    Begin
        If (X = High(Map)) Then
        Begin
            FindFirstDirection := DirLeft;
        End
        Else
        Begin
            If (Y = Low(Map[X])) Then
            Begin
            	FindFirstDirection := DirUp;
            End
            Else
            Begin
                If (Y = High(Map[X])) Then
                Begin
                    FindFirstDirection := DirDown;
                End;
            End;
        End;
    End;
end;

Procedure JumpToNextCell(Map: TMatrixOfMap; Var X, Y: Integer);
Begin
    If (Map[X, Y].EnemyDirection <> DirNone) Then
    Begin
        If ((Map[X, Y].EnemyDirection = DirRight) And (X < High(Map))) Then
        Begin
            Inc(X);
        End
        Else
        Begin
            If ((Map[X, Y].EnemyDirection = TDirection.DirUp) And (Y < High(Map))) Then
            Begin
                Inc(Y);
            End
            Else
            Begin
                If ((Map[X, Y].EnemyDirection = TDirection.DirLeft) And (X > Low(Map))) Then
                Begin
                    Dec(X);
                End
                Else
                Begin
                    If ((Map[X, Y].EnemyDirection = TDirection.DirDown) And (Y > Low(Map))) Then
                    Begin
                        Dec(Y);
                    End;
                End;
            End;
        End;
    End;
End;

// Принимает "начальную" клетку с определённым направлением, возвращает следующую клетку X Y, устанавливает направление клетки
// а также Boolean как признак конца
// Переходит на след. клетку
Function SetDirection(Var Map: TMatrixOfMap; Var Pos: TPosition): Boolean;
Var
    IsEnd, IsNotSamePos: Boolean;
    CheckPos: TPosition;
    PrevDir: TDirection;
Begin
    IsEnd := True;
    IsNotSamePos := False;

    PrevDir := Map[Pos.CellX, Pos.CellY].EnemyDirection;

    JumpToNextCell(Map, Pos.CellX, Pos.CellY);
    CheckPos.CellX := Pos.CellX;
    CheckPos.CellY := Pos.CellY;

    If (PrevDir = TDirection.DirRight) Then
    Begin
        Map[Pos.CellX, Pos.CellY].EnemyDirection := TDirection.DirDown;
    End
    Else
    Begin
        Map[Pos.CellX, Pos.CellY].EnemyDirection := Pred(PrevDir);
    End;

    JumpToNextCell(Map, CheckPos.CellX, CheckPos.CellY);
    IsNotSamePos := Not((CheckPos.CellX = Pos.CellX) And (CheckPos.CellY = Pos.CellY));

    If (IsNotSamePos And (Map[CheckPos.CellX, CheckPos.CellY].TypeOfGround = GtRoad)) Then
    Begin
        IsEnd := False;
    End
    Else
    Begin
        CheckPos.CellX := Pos.CellX;
        CheckPos.CellY := Pos.CellY;
        Map[Pos.CellX, Pos.CellY].EnemyDirection := PrevDir;

        JumpToNextCell(Map, CheckPos.CellX, CheckPos.CellY);
        IsNotSamePos := Not((CheckPos.CellX = Pos.CellX) And (CheckPos.CellY = Pos.CellY));

        If (IsNotSamePos And (Map[CheckPos.CellX, CheckPos.CellY].TypeOfGround = GtRoad) ) Then
        Begin
            IsEnd := False;
        End
        Else
        Begin
            CheckPos.CellX := Pos.CellX;
            CheckPos.CellY := Pos.CellY;

            If (PrevDir = TDirection.DirDown) Then
            Begin
                Map[Pos.CellX, Pos.CellY].EnemyDirection := TDirection.DirRight;
            End
            Else
            Begin
                Map[Pos.CellX, Pos.CellY].EnemyDirection := Succ(PrevDir);
            End;

            JumpToNextCell(Map, CheckPos.CellX, CheckPos.CellY);
            IsNotSamePos := Not((CheckPos.CellX = Pos.CellX) And (CheckPos.CellY = Pos.CellY));

            If (IsNotSamePos And (Map[CheckPos.CellX, CheckPos.CellY].TypeOfGround = GtRoad) ) Then
            Begin
                IsEnd := False;
            End;
        End;

    End;

    If (IsEnd) Then
    Begin
        Map[Pos.CellX, Pos.CellY].EnemyDirection := PrevDir; // проверить удаляются ли элементы или нет
    End;

    SetDirection := IsEnd;
End;

Procedure CalculateEnemyDirections(Var Map: TMatrixOfMap);
Var
    Pos, StartPos: TPosition;
    IsStop: Boolean;
Begin
    IsStop := False;
    StartPos.CellX := 0;
    StartPos.CellY := 0;

    FindStartCell(StartPos.CellX, StartPos.CellY);

    Pos.CellX := StartPos.CellX;
    Pos.CellY := StartPos.CellY;

    Map[Pos.CellX, Pos.CellY].EnemyDirection := FindFirstDirection(Map);

    Repeat
        IsStop := SetDirection(Map, Pos);
    Until IsStop;
End;

//-------------------------------------------------------------------
//Шаблоны врагов
//-------------------------------------------------------------------
Procedure InitEnemyTemplates();
Const
    COUNT_ENEMIES: Integer = 3;
Begin
    SetLength(EnemyTemplates, COUNT_ENEMIES);

    EnemyTemplates[0].EnemyType := EnCommon;
    EnemyTemplates[0].Health := ENEMY_MAX_HEALTH[Ord(EnCommon)];
    EnemyTemplates[0].MaxHealth := ENEMY_MAX_HEALTH[Ord(EnCommon)];
    EnemyTemplates[0].Speed := ENEMY_SPEED[Ord(EnCommon)];
    EnemyTemplates[0].Reward := ENEMY_REWARD[Ord(EnCommon)];

    EnemyTemplates[1].EnemyType := EnHeavy;
    EnemyTemplates[1].Health := ENEMY_MAX_HEALTH[Ord(EnHeavy)];
    EnemyTemplates[1].MaxHealth := ENEMY_MAX_HEALTH[Ord(EnHeavy)];
    EnemyTemplates[1].Speed := ENEMY_SPEED[Ord(EnHeavy)];
    EnemyTemplates[1].Reward := ENEMY_REWARD[Ord(EnHeavy)];

    EnemyTemplates[2].EnemyType := EnFast;
    EnemyTemplates[2].Health := ENEMY_MAX_HEALTH[Ord(EnFast)];
    EnemyTemplates[2].MaxHealth := ENEMY_MAX_HEALTH[Ord(EnFast)];
    EnemyTemplates[2].Speed := ENEMY_SPEED[Ord(EnFast)];
    EnemyTemplates[2].Reward := ENEMY_REWARD[Ord(EnFast)];
End;

Procedure InitTurret(TurretPos: TPosition; TurretType: TTurretType);
Begin
    MapData[TurretPos.CellX, TurretPos.CellY].Turret.TurretType := TurretType;
    MapData[TurretPos.CellX, TurretPos.CellY].Turret.FireRate := TURRET_FIRE_RATE[Ord(TurretType)];
    MapData[TurretPos.CellX, TurretPos.CellY].Turret.Radius := TURRET_RADII[Ord(TurretType)];

    MapData[TurretPos.CellX, TurretPos.CellY].IsAvailibleForTurret := False;
    MapData[TurretPos.CellX, TurretPos.CellY].Turret.ReloadProgress := 0;
End;

//------------------------------------------------------------------
// Процедуры списка
//------------------------------------------------------------------
Procedure Append(Var BulletList: TBulletList; Bullet: TBullet); Overload // Добавляем в начало
Var
    BulletNode: PTBulletNode;
Begin
    New(BulletNode);
    BulletNode^.Bullet := Bullet;

    If BulletList.Head <> Nil Then
    Begin
        BulletNode^.Next := BulletList.Head;
        BulletList.Head^.Prev := BulletNode;
    End
    Else
    Begin
        BulletNode^.Next := Nil;
    End;

    BulletNode^.Prev := Nil;
    BulletList.Head := BulletNode;
End;

Procedure Delete(Var BulletList: TBulletList; BulletNode: PTBulletNode); Overload // Добавляем в начало
Begin
    If (BulletList.Head = BulletNode) Then
    Begin
        BulletList.Head := BulletNode.Next;
    End
    Else
    Begin
        BulletNode^.Prev^.Next := BulletNode.Next;
    End;

    If (BulletNode^.Next <> Nil) Then
    Begin
        BulletNode^.Next^.Prev := BulletNode^.Prev;
    End;

    Dispose(BulletNode);
End;

Procedure Append(Var EnemySpawnsList: TEnemySpawnsList; EnemySpawns: TEnemySpawns); Overload // Добавляем в начало
Var
    EnemySpawnsNode: PTEnemySpawnsNode;
Begin
    New(EnemySpawnsNode);
    EnemySpawnsNode^.EnemySpawns := EnemySpawns;

    If EnemySpawnsList.Head <> Nil Then
    Begin
        EnemySpawnsNode^.Next := EnemySpawnsList.Head;
        EnemySpawnsList.Head^.Prev := EnemySpawnsNode;
    End
    Else
    Begin
        EnemySpawnsNode^.Next := Nil;
    End;

    EnemySpawnsNode^.Prev := Nil;
    EnemySpawnsList.Head := EnemySpawnsNode;
End;

Procedure Delete(Var EnemySpawnsList: TEnemySpawnsList; EnemySpawnsNode: PTEnemySpawnsNode); Overload // Добавляем в начало
Begin
    If (EnemySpawnsList.Head = EnemySpawnsNode) Then
    Begin
        EnemySpawnsList.Head := EnemySpawnsNode.Next;
    End
    Else
    Begin
        EnemySpawnsNode^.Prev^.Next := EnemySpawnsNode.Next;
    End;

    If (EnemySpawnsNode^.Next <> Nil) Then
    Begin
        EnemySpawnsNode^.Next^.Prev := EnemySpawnsNode^.Prev;
    End;

    Dispose(EnemySpawnsNode);
End;

//------------------------------------------------------------
//Создание врага
//-------------------------------------------------------------------
Procedure SpawnEnemy(TemplateIndex: Integer);
Var
    NewEnemy: TEnemy;
    EnemyCount: Integer;
    StartPos: TPosition;
Begin
    EnemyCount := 0;

    If FindStartCell(StartPos.CellX, StartPos.CellY) Then
    Begin
        NewEnemy := EnemyTemplates[TemplateIndex];
        NewEnemy.Pos.CellX := StartPos.CellX;
        NewEnemy.Pos.CellY := StartPos.CellY;
        NewEnemy.IsAlive := True;

        EnemyCount := Length(Enemies);
        SetLength(Enemies, EnemyCount + 1);
        Enemies[EnemyCount] := NewEnemy;
    End;
End;

//-------------------------------------------------------------------
//Обновление позиций врагов
//-------------------------------------------------------------------
Procedure UpdateEnemies(DeltaTime: Double);
Var
    I: Integer;
Begin
    I := 0;

    While I < Length(Enemies) Do
    Begin
        If (Enemies[I].Health <= 0.0) Then
        Begin
            If (Enemies[I].IsAlive) Then
            Begin
                Coins := Coins + ENEMY_REWARD[Ord(Enemies[I].EnemyType)];
            End;

            Enemies[I].IsAlive := False;
        End;

        If (Enemies[I].IsAlive) Then
        Begin
            Enemies[I].DistanceProgress := Enemies[I].DistanceProgress + Enemies[I].Speed * DeltaTime;

            While Enemies[I].DistanceProgress > 1 Do
            Begin
                JumpToNextCell(MapData, Enemies[I].Pos.CellX, Enemies[I].Pos.CellY);
                Enemies[I].DistanceProgress := Enemies[I].DistanceProgress - 1;
            End;

            //Проверка достижения базы
            If (Enemies[I].Pos.CellX >= 0) And (Enemies[I].Pos.CellX < MAP_WIDTH) And (Enemies[I].Pos.CellY >= 0) And (Enemies[I].Pos.CellY < MAP_HEIGHT) Then
            Begin
                If ((MapData[Enemies[I].Pos.CellX, Enemies[I].Pos.CellY].TypeOfGround = TGroundType.GtBase) And Enemies[I].IsAlive) Then
                Begin
                    Enemies[I].IsAlive := False;
                    Dec(TowerHealth);
                End;

                Inc(I);
            End
            Else
            Begin
                Inc(I);
            End;
        End
        Else
        Begin
            Inc(I);
        End;
    End;
End;

Function CalculateDistanceSquared(X1, Y1, X2, Y2: Integer): Integer;
Var
    DistanceSquared: Integer;
Begin
    DistanceSquared := (X2-X1)*(X2-X1) + (Y2-Y1)*(Y2-Y1);
    CalculateDistanceSquared := DistanceSquared;
End;

Procedure UpdateBullets(DeltaTime: Double);
Var
    Iterator, Temp: PTBulletNode;
    CurrBullet: PTBullet;
    TargetedEnemy: PTEnemy;
    Damage, SpeedMult: Double;
    TurretTypeID, I: Integer;
    TargetPos: TPosition;
Begin
    CurrBullet := Nil;
    Temp := Nil;
    Iterator := BulletList.Head;
    Damage := 0;
    SpeedMult := 0;
    TurretTypeID := 0;
    TargetPos.CellX := 0;
    TargetPos.CellY := 0;

    While Iterator <> Nil Do
    Begin
        CurrBullet := @Iterator^.Bullet;
        CurrBullet^.DistanceProgress := CurrBullet^.DistanceProgress + CurrBullet^.Speed * DeltaTime;

        If (CurrBullet^.DistanceProgress > 1) Then
        Begin
            Temp := Iterator;
            Iterator := Iterator^.Next;
            TurretTypeID := Ord(MapData[CurrBullet^.TurretPos.CellX, CurrBullet^.TurretPos.CellY].Turret.TurretType);
            Damage := BULLET_DAMAGE[TurretTypeID];
            SpeedMult := BULLET_SLOW[TurretTypeID];

            If (IS_BULLET_AOE[TurretTypeID]) Then
            Begin
                If (CurrBullet^.IsTracking) Then
                Begin
                    TargetPos.CellX := CurrBullet^.TargetedEnemy^.Pos.CellX;
                    TargetPos.CellY := CurrBullet^.TargetedEnemy^.Pos.CellY;
                End
                Else
                Begin
                    TargetPos.CellX := CurrBullet^.TargetPos.CellX;
                    TargetPos.CellY := CurrBullet^.TargetPos.CellY;
                End;

                For I := 0 To High(Enemies) Do
                Begin
                    If (Enemies[I].IsAlive And (Enemies[I].Pos.CellX = TargetPos.CellX) And (Enemies[I].Pos.CellY = TargetPos.CellY)) Then
                    Begin
                        Enemies[I].Health := Enemies[I].Health - Damage;
                        Enemies[I].Speed := Enemies[I].Speed * SpeedMult;
                    End;
                End;

            End
            Else
            Begin
                If (CurrBullet^.IsTracking) Then
                Begin
                    TargetedEnemy := CurrBullet^.TargetedEnemy;
                End
                Else
                Begin
                    TargetPos.CellX := CurrBullet^.TargetPos.CellX;
                    TargetPos.CellY := CurrBullet^.TargetPos.CellY;

                    TargetedEnemy := Nil;

                    // Поиск врага в клетке
                    For I := 0 To High(Enemies) Do
                    Begin
                        If (Enemies[I].IsAlive And (Enemies[I].Pos.CellX = TargetPos.CellX) And (Enemies[I].Pos.CellX = TargetPos.CellX)) Then
                        Begin
                            TargetedEnemy := @Enemies[I];
                        End;
                    End;

                End;

                If (TargetedEnemy <> Nil) Then
                Begin
                    TargetedEnemy^.Health := TargetedEnemy^.Health - Damage;
                    TargetedEnemy^.Speed := TargetedEnemy^.Speed * SpeedMult;
                End;
            End;

            Delete(BulletList, Temp);
        End
        Else
        Begin
            Iterator := Iterator^.Next;
        End;
    End;
End;

Procedure UpdateTurretOnCell(Pos: TPosition; DeltaTime: Double);
Var
    I, DistanceSquared, TurretID: Integer;
    IsToStop: Boolean;
    Bullet: TBullet;
    CurrCell: ^TMap;
Begin
    DistanceSquared := 0;
    TurretID := 0;
    IsToStop := False;
    CurrCell := @MapData[Pos.CellX, Pos.CellY];

    CurrCell^.Turret.ReloadProgress := CurrCell^.Turret.ReloadProgress + (CurrCell^.Turret.FireRate * DeltaTime);
    CurrCell^.Turret.ReloadProgress := Clamp(0, 1.1, CurrCell^.Turret.ReloadProgress);

    If (CurrCell^.Turret.ReloadProgress > 1) Then
    Begin
        I := 0;
        IsToStop := False;

        While ((I < Length(Enemies)) And Not IsToStop) Do
        Begin

            If (Enemies[I].IsAlive) Then
            Begin
                DistanceSquared := CalculateDistanceSquared(Pos.CellX, Pos.CellY, Enemies[I].Pos.CellX, Enemies[I].Pos.CellY);

                If ((DistanceSquared < (CurrCell^.Turret.Radius * CurrCell^.Turret.Radius))) Then
                Begin
                    IsToStop := True;
                End
                Else
                Begin
                    Inc(I);
                End;
            End
            Else
            Begin
                Inc(I);
            End;
        End;

        If (IsToStop) Then
        Begin
            While (CurrCell^.Turret.ReloadProgress > 1) Do   // Создаём пулю
            Begin
                CurrCell^.Turret.ReloadProgress := CurrCell^.Turret.ReloadProgress - 1;
                TurretID := Ord(CurrCell^.Turret.TurretType);

                Bullet.DistanceProgress := 0;
                Bullet.Speed := BULLET_SPEED[TurretID];
                Bullet.IsTracking := IS_BULLET_TRACKING[TurretID];

                If Bullet.IsTracking Then
                Begin
                    Bullet.TargetedEnemy := @Enemies[I];
                End
                Else
                Begin
                    Bullet.TargetPos.CellX := Enemies[I].Pos.CellX;
                    Bullet.TargetPos.CellY := Enemies[I].Pos.CellY;
                End;

                Bullet.TurretPos.CellX := Pos.CellX;
                Bullet.TurretPos.CellY := Pos.CellY;

                Append(BulletList, Bullet);
            End;
        End;
    End;
End;

Procedure UpdateTurrets(DeltaTime: Double);
Var
    I, J: Integer;
    CurrPos: TPosition;
Begin
    CurrPos.CellX := 0;
    CurrPos.CellY := 0;

    For I := 0 To MAP_WIDTH - 1 Do
    Begin
        For J := 0 To MAP_HEIGHT - 1 Do
        Begin
            CurrPos.CellX := I;
            CurrPos.CellY := J;

            If (MapData[I, J].Turret.TurretType <> TurrNone) Then
            Begin
                UpdateTurretOnCell(CurrPos, DeltaTime);
            End;
        End;
    End;
End;

//-------------------------------------------------------------------
//Отрисовка врагов
//-------------------------------------------------------------------
Procedure DrawEnemies(Canvas: TCanvas);
Var
    I: Integer;
    ScreenPos, DeltaPos: TPosition;
Begin
    ScreenPos.CellX := 0;
    ScreenPos.CellY := 0;
    DeltaPos.CellX := 0;
    DeltaPos.CellY := 0;

    For I := 0 To Length(Enemies) - 1 Do
    Begin
        If (Enemies[I].IsAlive) Then
        Begin
            DeltaPos.CellX := 0;
            DeltaPos.CellY := 0;

            case MapData[Enemies[I].Pos.CellX, Enemies[I].Pos.CellY].EnemyDirection of
                DirUp:
                    DeltaPos.CellY := 1;
                DirDown:
                    DeltaPos.CellY := -1;
                DirRight:
                    DeltaPos.CellX := 1;
                DirLeft:
                    DeltaPos.CellX := -1;
            end;

            // Враги перемещаются красиво, но становяться на вокую клетку ТОЛЬКО окогда наступают на её середину
            ScreenPos.CellX := Trunc((Enemies[I].Pos.CellX + (Enemies[I].DistanceProgress { - 0.5}) * DeltaPos.CellX) * CELL_SIZE);
            ScreenPos.CellY := Trunc((MAP_HEIGHT - 1 - Enemies[I].Pos.CellY - (Enemies[I].DistanceProgress {- 0.5}) * DeltaPos.CellY) * CELL_SIZE);

            If Enemies[I].EnemyType = EnCommon Then
            Begin
                Canvas.Brush.Color := ClBlue

            End
            Else
            Begin
                If Enemies[I].EnemyType = EnHeavy Then
                Begin
                    Canvas.Brush.Color := ClRed;
                End
                Else
                Begin
                    Canvas.Brush.Color := ClGreen;

                End;
            End;

            Canvas.Ellipse(ScreenPos.CellX + 5, ScreenPos.CellY + 5, ScreenPos.CellX + CELL_SIZE - 5, ScreenPos.CellY + CELL_SIZE - 5);
        End;
    End;
End;

Procedure DrawBullets(Canvas: TCanvas);
Var
    ScreenPos, DeltaPos: TPosition;
    TargetPixelX, TargetPixelY: Double;
    I: Integer;
    Iterator: PTBulletNode;
    CurrBullet: PTBullet;
Begin
    ScreenPos.CellX := 0;
    ScreenPos.CellY := 0;
    DeltaPos.CellX := 0;
    DeltaPos.CellY := 0;
    TargetPixelX := 0.0;
    TargetPixelY := 0.0;
    Iterator := BulletList.Head;
    CurrBullet := Nil;

    While (Iterator <> Nil) Do
    Begin
        CurrBullet := @Iterator^.Bullet;

        DeltaPos.CellX := 0;
        DeltaPos.CellY := 0;

        If CurrBullet.IsTracking Then
        Begin
            case MapData[CurrBullet^.TargetedEnemy^.Pos.CellX, CurrBullet^.TargetedEnemy^.Pos.CellY].EnemyDirection of
                DirUp:
                    DeltaPos.CellY := 1;
                DirDown:
                    DeltaPos.CellY := -1;
                DirRight:
                    DeltaPos.CellX := 1;
                DirLeft:
                    DeltaPos.CellX := -1;
            end;

            TargetPixelX := (CurrBullet^.TargetedEnemy^.Pos.CellX + (CurrBullet^.TargetedEnemy^.DistanceProgress) * DeltaPos.CellX) * CELL_SIZE;
            TargetPixelY := (CurrBullet^.TargetedEnemy^.Pos.CellY + (CurrBullet^.TargetedEnemy^.DistanceProgress) * DeltaPos.CellY) * CELL_SIZE;

        End
        Else
        Begin
            TargetPixelX := CurrBullet^.TargetPos.CellX * CELL_SIZE;
            TargetPixelY := CurrBullet^.TargetPos.CellY * CELL_SIZE;
        End;

        ScreenPos.CellX := Trunc(CELL_SIZE * (CurrBullet^.TurretPos.CellX * (1 - CurrBullet^.DistanceProgress)) + TargetPixelX * (CurrBullet^.DistanceProgress));
        ScreenPos.CellY := MAP_HEIGHT * CELL_SIZE - Trunc(CELL_SIZE * (CurrBullet^.TurretPos.CellY * (1 - CurrBullet^.DistanceProgress)) + TargetPixelY * (CurrBullet^.DistanceProgress)) - CELL_SIZE;

        Canvas.Brush.Color := ClMenuText;

        Canvas.Ellipse(ScreenPos.CellX + 20, ScreenPos.CellY + 20, ScreenPos.CellX + CELL_SIZE - 20, ScreenPos.CellY + CELL_SIZE - 20);

        Iterator := Iterator^.Next;
    End;

End;

Procedure ReadEnemySpawns();
Var
    ReadedFile: File Of TEnemySpawns;
    Len: Integer;
    Element: TEnemySpawns;
Begin
    Len := 0;

    AssignFile(ReadedFile, '.\EnemySpawnsData.dat');

    Reset(ReadedFile);

    While (Not EOF(ReadedFile)) Do
    Begin
        Read(ReadedFile, Element);

        Append(EnemySpawnsList, Element);
    End;

    CloseFile(ReadedFile);
End;

Procedure CreateTextures();
Begin
    GrassTex := TBitmap.Create;
    BaseTex := TBitmap.Create;

    RoadRightTex := TBitmap.Create;
    RoadUpTex := TBitmap.Create;
    RoadLeftTex := TBitmap.Create;
    RoadDownTex := TBitmap.Create;

    TurretCommonTex := TBitmap.Create;
    TurretSlowingTex := TBitmap.Create;
    TurretAreaTex := TBitmap.Create;
End;

Procedure LoadTextures();
Begin
    GrassTex.LoadFromFile('.\textures\grass_texture.bmp');
    BaseTex.LoadFromFile('.\textures\base_texture.bmp');

    RoadRightTex.LoadFromFile('.\textures\road_rigth_texture.bmp');
    RoadUpTex.LoadFromFile('.\textures\road_up_texture.bmp');
    RoadLeftTex.LoadFromFile('.\textures\road_left_texture.bmp');
    RoadDownTex.LoadFromFile('.\textures\road_down_texture.bmp');

    TurretCommonTex.LoadFromFile('.\textures\common_turret_texture.bmp');
    TurretSlowingTex.LoadFromFile('.\textures\slowing_turret_texture.bmp');
    TurretAreaTex.LoadFromFile('.\textures\area_turret_texture.bmp');
End;

Procedure FreeTextures();
Begin
    GrassTex.Free;
    BaseTex.Free;

    RoadRightTex.Free;
    RoadUpTex.Free;
    RoadLeftTex.Free;
    RoadDownTex.Free;

    TurretCommonTex.Free;
    TurretSlowingTex.Free;
    TurretAreaTex.Free;
End;

//    TURRET_PRICES: Array [0..3] Of Integer = (0, 25, 30, 55);
//    TURRET_RADII: Array [0..3] Of Double = (0.0, 3.0, 4.0, 2.0);
//    TURRET_FIRE_RATE: Array [0..3] Of Double = (0.0, 1.2, 1.5, 0.7);
//
//    BULLET_DAMAGE: Array [0..3] Of Double = (0.0, 34.0, 10.0, 20.0);
//    BULLET_SLOW: Array [0..3] Of Double = (0.0, 1.0, 0.9, 1.0);
//    IS_BULLET_AOE: Array [0..3] Of Boolean = (False, False, False, True);       // AOE - Area Of Effect     Урон/ЭФфект по области
//    IS_BULLET_TRACKING: Array  [0..3] Of Boolean = (False, True, True, False);
//    BULLET_SPEED: Array [0..3] Of Double = (0.0, 3.0, 5.0, 2.0);

Procedure SetTurretMenuHint(Panel: TPanel; TurrType: TTurretType);
Var
    TurrIndex: Integer;
    Radius, FireRate, DamagePerBullet, SlowingMult, BulletSpeed: Double;
    IsAOE, IsTracking: Bool;
Begin
    TurrIndex := Ord(TurrType);

    Radius := TURRET_RADII[TurrIndex];
    FireRate := TURRET_FIRE_RATE[TurrIndex];
    DamagePerBullet := BULLET_DAMAGE[TurrIndex];
    SlowingMult := BULLET_SLOW[TurrIndex];
    BulletSpeed := BULLET_SPEED[TurrIndex];
    IsTracking := IS_BULLET_TRACKING[TurrIndex];
    IsAOE := IS_BULLET_AOE[TurrIndex];

    Panel.ShowHint := True;

    Panel.Hint := Format('Урон за снаряд: %f' + #13#10
                         + 'Радиус: %f' + #13#10
                         + 'Скорострельность: %f' + #13#10
                         + 'Скорость снаряда: %f' + #13#10
                         + 'Множитель замедления: %f' + #13#10, [DamagePerBullet, Radius, FireRate, BulletSpeed, SlowingMult]);

    If (IsAOE) Then
    Begin
        Panel.Hint := Panel.Hint + 'Урон по области: Да' + #13#10;
    End
    Else
    Begin
        Panel.Hint := Panel.Hint + 'Урон по области: Нет' + #13#10;
    End;

    If (IsTracking) Then
    Begin
        Panel.Hint := Panel.Hint + 'Метод атаки: По противнику';
    End
    Else
    Begin
        Panel.Hint := Panel.Hint + 'Метод атаки: По клетке';
    End;
End;

//-------------------------------------------------------------------
//Form события
//-------------------------------------------------------------------
Procedure TGameForm.FormCanResize(Sender: TObject; var NewWidth, NewHeight: Integer; var Resize: Boolean);
Begin
    Resize := False;
End;

Procedure TGameForm.FormCreate(Sender: TObject);
Begin
    GameTime := 0.0;
    TowerHealth := MAX_TOWER_HEALTH;
    Coins := START_COINS;
    BulletList.Head := Nil;

    WriteEnemySpawnsToFile();

    CreateTextures();
    LoadTextures();

    MapData := SetMap1();
    CalculateEnemyDirections(MapData);

    ReadEnemySpawns();

    InitEnemyTemplates();
    SetLength(Enemies, 0);

    SetTurretMenuHint(SlowingTurretPanel, TTurretType.TurrSlowing);
    SetTurretMenuHint(CommonTurretPanel, TTurretType.TurrCommon);
    SetTurretMenuHint(AreaTurretPanel, TTurretType.TurrAreaDamaging);

    Application.HintHidePause := -1;
End;

Procedure TGameForm.FormDestroy(Sender: TObject);
Begin
    FreeTextures();
End;

Function TGameForm.FormHelp(Command: Word; Data: THelpEventData; Var CallHelp: Boolean): Boolean;
Begin
    CallHelp := False;
End;

Procedure TGameForm.MapBoxMouseDown(Sender: TObject; Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
Begin
    SelectedPos.CellX := X Div CELL_SIZE;
    SelectedPos.CellY := (CELL_SIZE * MAP_HEIGHT - Y) Div CELL_SIZE;

    SelectBox.Left := SelectedPos.CellX * CELL_SIZE + MapBox.Left;
    SelectBox.Top := (MAP_HEIGHT - SelectedPos.CellY - 1) * CELL_SIZE + MapBox.Top;
End;

Procedure TGameForm.MapBoxPaint(Sender: TObject);
Var
    I, J: Integer;
    CellRect: TRect;
Begin
    With MapBox.Canvas Do
    Begin
        For I := 0 To MAP_WIDTH - 1 Do
        Begin
            For J := 0 To MAP_HEIGHT - 1 Do
            Begin
                CellRect := Rect(I * CELL_SIZE, (MAP_HEIGHT - 1 - J) * CELL_SIZE, (I + 1) * CELL_SIZE, (MAP_HEIGHT - J) * CELL_SIZE);

                If MapData[I, J].TypeOfGround = TGroundType.GtGrass Then
                Begin
                    StretchDraw(CellRect, GrassTex);

                    case MapData[I, J].Turret.TurretType Of
                        TurrCommon:  StretchDraw(CellRect, TurretCommonTex);
                        TurrSlowing:  StretchDraw(CellRect, TurretSlowingTex);
                        TurrAreaDamaging:    StretchDraw(CellRect, TurretAreaTex);
                    end;

                End
                Else
                Begin
                    If MapData[I, J].TypeOfGround = TGroundType.GtRoad Then
                    Begin
                        case MapData[I, J].EnemyDirection Of
                            DirRight: StretchDraw(CellRect, RoadRightTex);
                            DirLeft:  StretchDraw(CellRect, RoadLeftTex);
                            DirDown:  StretchDraw(CellRect, RoadDownTex);
                            DirUp:    StretchDraw(CellRect, RoadUpTex);
                        else
                            StretchDraw(CellRect, RoadRightTex);
                        end;
                    End
                    Else
                    Begin
                        If MapData[I, J].TypeOfGround = TGroundType.GtBase Then
                        Begin
                            StretchDraw(CellRect, BaseTex);
                        End;

                    End;
                End;
            End;
        End;
    End;

    DrawEnemies(MapBox.Canvas);
    DrawBullets(MapBox.Canvas);
End;

procedure TGameForm.MenuOptionAutorClick(Sender: TObject);
begin
    GameTimer.Enabled := False;
    Application.MessageBox(PChar('Автор: Педько Владислав, гр. 551004'), PChar('Автор'), MB_OK);
    GameTimer.Enabled := True;
end;

procedure TGameForm.MenuOptionInstructionClick(Sender: TObject);
Var
    InstructionForm: TInstructionForm;
Begin
    GameTimer.Enabled := False;
    InstructionForm := TInstructionForm.Create(Self);
    InstructionForm.ShowModal;
    InstructionForm.Free;
    GameTimer.Enabled := True;
End;

procedure TGameForm.MenuOptionMenuClick(Sender: TObject);
begin
    Close;
end;

Procedure TGameForm.CommonTurretPanelClick(Sender: TObject);
Begin
    If ((MapData[SelectedPos.CellX, SelectedPos.CellY].TypeOfGround = TGroundType.GtGrass) And MapData[SelectedPos.CellX, SelectedPos.CellY].IsAvailibleForTurret) Then
    Begin
        Coins := Coins - TURRET_PRICES[Ord(TTurretType.TurrCommon)];
        InitTurret(SelectedPos, TurrCommon);
    End;
End;

procedure TGameForm.SlowingTurretPanelClick(Sender: TObject);
begin
    If ((MapData[SelectedPos.CellX, SelectedPos.CellY].TypeOfGround = TGroundType.GtGrass) And MapData[SelectedPos.CellX, SelectedPos.CellY].IsAvailibleForTurret) Then
    Begin
        Coins := Coins - TURRET_PRICES[Ord(TTurretType.TurrSlowing)];
        InitTurret(SelectedPos, TurrSlowing);
    End;
end;

procedure TGameForm.AreaTurretPanelClick(Sender: TObject);
begin
    If ((MapData[SelectedPos.CellX, SelectedPos.CellY].TypeOfGround = TGroundType.GtGrass) And MapData[SelectedPos.CellX, SelectedPos.CellY].IsAvailibleForTurret) Then
    Begin
        Coins := Coins - TURRET_PRICES[Ord(TTurretType.TurrAreaDamaging)];
        InitTurret(SelectedPos, TurrAreaDamaging);
    End;
end;

Function Clamp(Const MIN, MAX: Double; Value: Double): Double;
Var
    Answer: Double;
Begin
    Answer := Value;

    If (Value < MIN) Then
    Begin
        Answer := MIN;
    End
    Else
    Begin
        If (Value > MAX) Then
        Begin
            Answer := MAX;
        End;
    End;

    Clamp := Answer;
End;

Procedure UpdateButtons();
Begin
    GameForm.CommonTurretPriceLabel.Caption := Format('Цена: %d', [TURRET_PRICES[Ord(TTurretType.TurrCommon)]]);
    GameForm.SlowingTurretPriceLabel.Caption := Format('Цена: %d', [TURRET_PRICES[Ord(TTurretType.TurrSlowing)]]);
    GameForm.AreaTurretPriceLabel.Caption := Format('Цена: %d', [TURRET_PRICES[Ord(TTurretType.TurrAreaDamaging)]]);

    If (Coins >= TURRET_PRICES[Ord(TTurretType.TurrCommon)]) Then
    Begin
        GameForm.CommonTurretPriceLabel.Enabled := True;
        GameForm.CommonTurretPanel.Enabled := True;
    End
    Else
    Begin
        GameForm.CommonTurretPriceLabel.Enabled := False;
        GameForm.CommonTurretPanel.Enabled := False;
    End;

    If (Coins >= TURRET_PRICES[Ord(TTurretType.TurrSlowing)]) Then
    Begin
        GameForm.SlowingTurretPriceLabel.Enabled := True;
        GameForm.SlowingTurretPanel.Enabled := True;
    End
    Else
    Begin
        GameForm.SlowingTurretPriceLabel.Enabled := False;
        GameForm.SlowingTurretPanel.Enabled := False;
    End;

    If (Coins >= TURRET_PRICES[Ord(TTurretType.TurrAreaDamaging)]) Then
    Begin
        GameForm.AreaTurretPriceLabel.Enabled := True;
        GameForm.AreaTurretPanel.Enabled := True;
    End
    Else
    Begin
        GameForm.AreaTurretPriceLabel.Enabled := False;
        GameForm.AreaTurretPanel.Enabled := False;
    End;
End;

Procedure SetTimeLabel();
Const
    SEC_IN_MIN = 60;
Var
    Hours, Minutes, Seconds: Integer;
Begin
    Hours := Trunc(GameTime) Div (SEC_IN_MIN * SEC_IN_MIN);
    Minutes := (Trunc(GameTime) Div SEC_IN_MIN) Mod SEC_IN_MIN;
    Seconds := Trunc(GameTime) Mod SEC_IN_MIN;
    GameForm.TimeLabel.Caption := Format('Время: %.2d:%.2d:%.2d', [Hours, Minutes, Seconds]);
End;

// TODO: Таймер немного отстаёт от реального времени
Procedure TGameForm.GameTimerTimer(Sender: TObject);
Const
    COIN_EARN_INTERVAL = 1000;
    MILISECONDS_IN_SECOND = 1000;
Var
    DeltaTime: Double;
    CountToSpawn, I: Integer;
    Element: TEnemySpawns;
    Iterator: PTEnemySpawnsNode;
    WillStopSpawnEnemies, HasNoAliveEnemies: Boolean;
Begin
    DeltaTime := GameTimer.Interval / MILISECONDS_IN_SECOND;
    GameTime := GameTime + DeltaTime;

    SetTimeLabel();

    If (((Round(GameTime * MILISECONDS_IN_SECOND)) Mod COIN_EARN_INTERVAL) < 10) Then
    Begin
        Inc(Coins);
        CoinsLabel.Caption := Format('Монеты: %4d', [Coins]);
    End;

    TowerHealthLabel.Caption := Format('Жизни: %d/%d', [TowerHealth, MAX_TOWER_HEALTH]);

    If (TowerHealth <= 0) Then
    Begin
        GameTimer.Enabled := False;
        Application.MessageBox(PChar('Ваша база потерпела поражение!'), PChar('Поражение'), MB_OK + MB_ICONEXCLAMATION);
        Close;
    End;

    Iterator := EnemySpawnsList.Head;
    WillStopSpawnEnemies := True;
    While (Iterator <> Nil) Do
    Begin
        Element := Iterator^.EnemySpawns;

        If (Element.EndTime > GameTime) Then
        Begin
            WillStopSpawnEnemies := False;
        End;

        If(Element.EndTime - Element.StartTime < 0.01) Then
        Begin
            CountToSpawn := Element.EnemyCount;
        End
        Else
        Begin
            CountToSpawn := Trunc(Element.EnemyCount*(Clamp(0.0, 1.0, (GameTime-Element.StartTime)/(Element.EndTime-Element.StartTime))));
        End;

        While (CountToSpawn > Iterator^.EnemySpawns.EnemyCountCurrent) Do
        Begin
            SpawnEnemy(Element.EnemyID);
            Inc(Iterator^.EnemySpawns.EnemyCountCurrent);
        End;

        Iterator := Iterator^.Next;
    End;

    HasNoAliveEnemies := True;
    If (WillStopSpawnEnemies) Then
    Begin
        For I := 0 To High(Enemies) Do
        Begin
            If (Enemies[I].IsAlive) Then
            Begin
                HasNoAliveEnemies := False;
            End;
        End;
    End;

    If (HasNoAliveEnemies And WillStopSpawnEnemies) Then
    Begin
        GameTimer.Enabled := False;
        Application.MessageBox(PChar('Ваша база успешно выстояла все атаки врага!'), PChar('Победа'), MB_OK + MB_ICONASTERISK);
        Close;
    End;

    UpdateButtons();
    UpdateEnemies(DeltaTime);
    UpdateTurrets(DeltaTime);
    UpdateBullets(DeltaTime);

    MapBox.Invalidate;
End;

End.

// Добавить состояние игрока "жизни" "деньги" и подумать над снарядами. И систему урона по игроку
// Сделать отображение меню магазина турелей
