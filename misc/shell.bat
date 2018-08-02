@echo off

subst J: "C:\stuff\src"

call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvarsall.bat" x86_amd64

set PATH=%PATH%;J:\SDL2-2.0.8\lib\x64