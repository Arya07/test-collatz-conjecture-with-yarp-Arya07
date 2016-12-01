/*
* author: Elisa Maiettini
* date: 26/11/2016
*/
#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/RpcClient.h>

#include <vocabs.hpp>
#include <CollatzTester.hpp>

#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;
using namespace yarp::os;

class ClientModule : public RFModule{

private:

	RpcClient client_port;

	Bottle request, response;
	int N, T;

public:
	double getPeriod(){   return 1.0;  }

	virtual bool respond(const Bottle &command, Bottle &reply){  return true; }

	virtual bool updateModule(){

		//prepering and sending bottle for the server
		request.addInt(COLLATZ_VOCAB_REQ_ITEM);
		request.addInt(N);

		cout << "ClientModule: client sending request.." << N << endl;
		client_port.write(request,response);

		//collecting server response
		if(response.get(0).asInt() == COLLATZ_VOCAB_ITEM){
			cout << "ClientModule: client elaborating server response.." << endl;
			N = response.get(1).asInt();
			T = response.get(2).asInt();

			//testing the received pair
			CollatzTester::testPair(N, T);
			cout << "ClientModule: client has tested int "<< N << "with threshold " << T <<"and is sending request.." << endl;

		}else{
			cout << "invalid message received! with identifier: " << response.get(0).asInt() << endl;
		}

		request.clear();
		response.clear();

		return true;
	}

	bool configure(yarp::os::ResourceFinder &rf){
		N = 0;
		T = 0;

		string port_name = rf.find("name").asString().c_str();
		client_port.open(("/"+port_name).c_str());
		cout << "ClientModule: opened port: /" + port_name << endl;

		return true;
	}

	bool interruptModule(){
		client_port.interrupt();
		return true;
	}

	bool close(){
		client_port.close();
		return true;
	}
};

int main(int argc, char * argv[]){
	Network yarp;
	ClientModule module;
	ResourceFinder rf;

	rf.configure(argc, argv);
	rf.setVerbose(true);

	cout << "ClientModule: Configuring and starting module. \n";
	module.runModule(rf);
	return 0;
}
