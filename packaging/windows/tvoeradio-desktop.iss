[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{EEEE173E-5082-4296-B20D-4192CB42467A}
AppName=Твоёрадио Десктоп
AppVersion=2.0
AppPublisher=Твоёрадио
AppPublisherURL=http://tvoeradio.org/
AppSupportURL=http://vkontakte.ru/tvoeradio_official
AppUpdatesURL=http://tvoeradio.org/desktop/
DefaultDirName={pf}\Tvoeradio Desktop
DisableProgramGroupPage=yes
OutputBaseFilename=tvoeradio-desktop-2.0-setup
Compression=lzma
SolidCompression=yes

[Languages]
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "files\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{commonprograms}\Твоёрадио Десктоп"; Filename: "{app}\tvoeradio-desktop.exe"
Name: "{userdesktop}\Твоёрадио Десктоп"; Filename: "{app}\tvoeradio-desktop.exe"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Твоёрадио Десктоп"; Filename: "{app}\tvoeradio-desktop.exe"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\tvoeradio-desktop.exe"; Description: "{cm:LaunchProgram,Твоёрадио Десктоп}"; Flags: nowait postinstall skipifsilent

[Messages]
WelcomeLabel1=Установка программы%n«Твоёрадио Десктоп»
