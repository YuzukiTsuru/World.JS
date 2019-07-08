@echo off

cd build
node WorldJS.js


copy WorldJS.js ..\test\
copy WorldJS.js.mem ..\test\
