cd /d "%~dp0build"
premake5.exe clean
premake5.exe vs2026 --backend=glfw --graphics=opengl43
pause