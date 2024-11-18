@set name="laba"
gcc %name%.c -o %name%.exe && %name%.exe
@<nul set /p x="gcc %name%.c -o %name%.exe && %name%.exe"| Clip
cmd
