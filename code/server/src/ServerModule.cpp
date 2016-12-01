/*
* author: Elisa Maiettini
* date: 26/11/2016
*/
#include<ServerModule.hpp>

using namespace std;
using namespace yarp::os;

bool ServerModule::respond(const Bottle &command, Bottle &reply){
	int tested_N;
	cout << "ServerModule: waiting message from client.."<< endl;

	if(command.get(0).asInt()==COLLATZ_VOCAB_REQ_ITEM){
		tested_N = command.get(1).asInt();
		cout << "ServerModule: received message of tested number:" << tested_N << endl;

		//updating CNT and FIFO
		cout << "ServerModule: updating CNT and FIFO.." << endl;
		CNT++;
		fifo_handler->pushBack(CNT);

		//choosing an other pair (N,T)
		cout << "ServerModule: choosing an other pair (N,T).." <<endl;
		int new_N = CNT;
		cout << "CNT: " << CNT << " ";

		int new_T = ((fifo_handler->getHead()) - 1);
		cout << "HEAD - 1 : " << new_T <<endl;

		//eresing tested number
		fifo_handler->eraseTested(tested_N);

		//preparing new bottle for the client
		cout << "ServerModule: preparing bottle for the client.."<< endl;
		reply.addInt(COLLATZ_VOCAB_ITEM);
		reply.addInt(new_N);
		reply.addInt(new_T);

	}else{
		cout << "invalid message received! with identifier: " << command.get(0).asInt() << endl;
	}
	return true;
}

bool ServerModule::updateModule(){
	return true;
}

bool ServerModule::configure(yarp::os::ResourceFinder &rf){
	CNT = 1;

	string port_name = rf.check("name", Value("server")).asString();
	int ms_period = rf.check("rate", Value(1000)).asInt();

	server_port.open(("/"+port_name).c_str());
	cout << "ServerModule: opened port: /" << port_name << endl;
	attach(server_port);

	cout << "ServerModule: staring fifo_handler" << endl;
	fifo_handler = new FIFOHandler(ms_period);
	fifo_handler->start();

	return true;
}

int main(int argc, char * argv[])
{
	Network yarp;
	ServerModule module;
	ResourceFinder rf;

	rf.configure(argc, argv);
	rf.setVerbose(true);

	cout << "ServerModule: Configuring and starting module. \n";
	module.runModule(rf);

	cout<<"ServerModule: Main returning..."<<endl;
	return 0;
}
