@echo off

SET SrcName=create_rect
SET SrcFile=code\%SrcName%.cpp
SET TopDir=J:\SDL\sdltut_novs\create_rect
SET SrcPath=%TopDir%\%SrcFile%
SET SDLDir=J:\SDL2-2.0.8
SET SDLLibDir=%SDLDir%\lib\x64
SET SDLIncludeDir=%SDLDir%\include

REM echo %SDLDir%

SET CommonCompilerFlags=-MTd -nologo -Gm- -GR- -EHa- -Od -Oi -fp:fast -WX -W4 -wd4201 -wd4100 -wd4189 -wd4456 -wd4505 -FC -Z7 -I%SDLIncludeDir%
REM SET CommonLinkerFlags= -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib
SET CommonLinkerFlags= -incremental:no -subsystem:WINDOWS -opt:ref -libpath:%SDLLibDir% SDL2.lib SDL2main.lib

IF NOT EXIST %TopDir%\build mkdir %TopDir%\build
pushd %TopDir%\build

REM del *.pdb > NUL 2> NUL
REM Optimization Switches /O2
REM echo WAITING FOR PDB > lock.tmp
cl %CommonCompilerFlags% %SrcPath% -Fm%SrcName%.map /link %CommonLinkerFlags%
popd