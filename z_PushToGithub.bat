@ROBOCOPY %cd% "C:\Program Files\Git\code\C-Speed" *.c *.h *.txt *.ico *.bin *.rc *.bat *.png *.ttf /MIR /XD dirs .git media
@cd "C:\Program Files\Git\code\C-Speed"
@set commitMessage=""
@IF [%1]==[] (
	set commitMessage=Updated
) ELSE (
	set commitMessage=%1
)
@git init
@git add .
@git commit -m %commitMessage%
@git remote add origin https://github.com/123outerme/C-Speed
@git push origin master
@cd %~dp0
@pause Done! Press anything to continue.