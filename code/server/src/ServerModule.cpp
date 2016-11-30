/*
 * author: Elisa Maiettini
 * date: 26/11/2016
 */
#include<ServerModule.hpp>

using namespace std;
using namespace yarp::os;

bool ServerModule::updateModule()
{
	int tested_N;
	cout << "ServerModule: waiting message from client.."<< endl;
  server_port.read(in,true);

	if(in.get(0).asInt()==COLLATZ_VOCAB_REQ_ITEM){
		tested_N = in.get(1).asInt();
		cout << "ServerModule: received message of tested number: " << tested_N << endl;

		//updating CNT and FIFO
		cout << "ServerModule: updating CNT and FIFO" << endl;
		CNT++;
		fifo_mutex.wait();
		FIFO.push_back(CNT);

		//choosing an other pair (N,T)
		cout << "ServerModule: choosing an other pair (N,T).." <<endl;
		int new_N = CNT;
		cout << "CNT: " << CNT <<endl;

		std::list<int>::iterator it1 = FIFO.begin();
		int new_T = ((*it1)-1);
		cout << "HEAD - 1 : " << new_T <<endl;

		//eresing tested number
		cout << "ServerModule: eresing tested number"<< tested_N << "from the FIFO" <<endl;
		std::list<int>::iterator it = FIFO.begin();
		bool found = false;
		while(!found && it != FIFO.end()){
			if(*it == tested_N){
				FIFO.erase(it);
				found = true;
			}
			it++;
		}
		if(!found){
			cout << "ServerModule: number"<<tested_N<< "Not found in the FIFO..." << endl;
		}

		fifo_mutex.post();

		//prepering new bottle for the client
		cout << "ServerModule: prepering bottle for the client.."<< endl;
		out.addInt(COLLATZ_VOCAB_ITEM);
		out.addInt(new_N);
		out.addInt(new_T);

		//sending response to the client
		cout << "ServerModule: sending message to client.."<< endl;
		server_port.reply(out);
	}

	in.clear();
  out.clear();
	return true;
}


bool ServerModule::configure(yarp::os::ResourceFinder &rf)
{
	CNT = 1;
  string port_name = rf.find("name").asString().c_str();

  server_port.open(("/"+port_name).c_str());
  cout << "ServerModule: opened port: /" + port_name << endl;

	FIFO = std::list<int>();

  return true;
}


std::list<int>::iterator ServerModule::getFIFO(){
	fifo_mutex.wait();
	std::list<int>::iterator it = FIFO.begin();
	fifo_mutex.post();

	return it;
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
  return module.runModule(rf);
}
