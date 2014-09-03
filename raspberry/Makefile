all : rf24 rf24-sqlite3

rf24: rf24.cpp
	g++ -lstdc++ -lrt -lrf24-bcm rf24.cpp -o rf24.out

rf24-sqlite3: rf24-sqlite3.cpp
	g++ -lstdc++ -lrt -lrf24-bcm -lsqlite3 rf24-sqlite3.cpp -o rf24-sqlite3.out