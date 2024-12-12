@set name="task_1"
del visual.svg&& gcc simple_svg.cpp task_1.cpp -o task_1.exe&& task_1.exe
@<nul set /p x="del visual.svg && gcc simple_svg.cpp task_1.cpp -o task_1.exe && task_1.exe"| Clip
cmd
