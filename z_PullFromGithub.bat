@set folder=C:\Program Files\Git\tmp\pulls
@cd %folder%\C-Speed
@IF EXIST "%folder%\C-Speed\.git" (
	cd /d "%folder%\C-Speed\.git"
	for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)
	cd ..
)

@git init
@git remote add origin https://github.com/123outerme/C-Speed.git
git pull origin master --allow-unrelated-histories
@ROBOCOPY "%folder%\C-Speed" "C:\Program Files\Git\code\C-Speed" /MIR
@IF EXIST "%folder%\C-Speed" (
	@cd /d "%folder%\C-Speed"
	@for /F "delims=" %%i in ('dir /b') do (rmdir "%%i" /s/q || del "%%i" /s/q)
)
@ROBOCOPY "C:\Program Files\Git\code\C-Speed" %~dp0 *.c *.h *.txt *.ico *.rc *.png *.bat *.html *.css *.md /MIR /XD dirs .git GtL GtL-bin media
@cd "C:\Program Files\Git\code\C-Speed"
@git init
@git add -A
@cd %~dp0
@rem @pause Done! Press anything to continue.