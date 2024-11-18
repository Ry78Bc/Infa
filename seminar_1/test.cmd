@echo off

@REM set %a%

kv_ur.exe 2 3 -5

echo %ERRORLEVEL%

if %ERRORLEVEL%==-1.5 (
  echo success
) else (
  echo error
)

kv_ur.exe 5 -8 -4

echo %ERRORLEVEL%

if %ERRORLEVEL%==1.6 (
  echo success
) else (
  echo error
)

echo.
pause
