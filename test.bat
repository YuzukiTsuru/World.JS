@echo off

cd build

% Copy file for test % 
copy *.js ..\test\
copy *.js.mem ..\test\
copy *.wasm ..\test\
copy *.data ..\test\
copy *.wasm.map ..\test\

cd ..