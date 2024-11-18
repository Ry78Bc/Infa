@set name="laba_9_3"
gcc %name%.c -o %name%.exe && %name%.exe
@<nul set /p x="gcc %name%.c -o %name%.exe && %name%.exe"| Clip
cmd
