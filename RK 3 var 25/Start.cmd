@set name="task_1"
del visual.svg&& gcc %nsame%.cpp -o %name%.exe&& %name%.exe
@<nul set /p x="del visual.svg && gcc %name%.cpp -o %name%.exe && %name%.exe"| Clip
cmd
