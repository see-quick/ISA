all: compileServer compileClient

compileServer: 
	g++ mainServer.cpp server/Server.cpp server/Server.h server/Controller.cpp server/Controller.h server/Boards.cpp server/Boards.h server/Board.cpp server/Board.h server/Commend.cpp server/Commend.h ParseArgs.cpp ParseArgs.h -o isaserver
compileClient: 
	g++ mainClient.cpp client/Client.cpp client/Client.h client/ClientController.cpp client/ClientController.h ParseArgs.cpp ParseArgs.h -o isaclient
server:
	./isaserver -p 12000
client:
	./isaclient -p 12000
clean:
	rm isaserver
	rm isaclient
