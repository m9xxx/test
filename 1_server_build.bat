g++ -c ./Server/source/component.cpp -o ./Server/build/component.o 
g++ -c ./Server/source/main.cpp -o ./Server/build/main.o

g++ -shared ./Server/build/component.o ./Server/build/main.o -o ./dlls/Server.dll -lole32 -loleaut32 -luser32 -Wl,--kill-at 

g++ -c ./Server2/source/component.cpp -o ./Server2/build/component.o
g++ -c ./Server2/source/main.cpp -o ./Server2/build/main.o

g++ -shared ./Server2/build/component.o ./Server2/build/main.o -o ./dlls/Server2.dll -lole32 -loleaut32 -luser32 -Wl,--kill-at

pause