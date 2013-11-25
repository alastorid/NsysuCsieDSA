@echo off
cls
::script by B003040020 


for /l %%i in (1,1,10) do (
echo Test case: %%i
B003040020_hw8.exe > result%%i.txt

)