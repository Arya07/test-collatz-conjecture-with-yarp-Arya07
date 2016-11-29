/*
 * author: Elisa Maiettini
 * date: 26/11/2016
 */
#include <iostream>
#include <iomanip>
#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/RpcServer.h>
#include <yarp/os/RateThread.h>

#include <vocabs.hpp>

#include <stdio.h>
#include <string>
#include <ctime>
#include <list>


using namespace std;
using namespace yarp::os;
class ServerModule : public RFModule
{
private:

	RpcServer server_port;
	RateThread fifo_controller;
	std::list<int> FIFO;
	Semaphore fifo_mutex;
	int CNT;
	Bottle in, out;

public:
    double getPeriod()  {        return 1.0;  }

    virtual bool respond(const Bottle &command, Bottle &reply)
  	{
      return true;
  	}

    virtual bool updateModule()
  	{
			int tested_N;
			cout << "receiving message from client.."<< endl;
		  server_port.read(in,true);
			if(in.get(0).asInt()==COLLATZ_VOCAB_ITEM_REQ){
				tested_N = in.get(1).asInt();
				cout << "received message from client with N: " << N << endl;

				cout  "updating CNT and FIFO" <<endl;
				CNT++;
				fifo_mutex.wait();
				FIFO.push_back(CNT

				cout  "choosing an other pair (N,T).." <<endl;
				int new_N = CNT;
				int new_T = ()*(FIFO.begin()))-1;

				cout  "eresing tested number"<< tested_N << "from the FIFO" <<endl;
				ereseTested(tested_N);

				fifo_mutex.post();

				cout << "prepering bottle for the client.."<< endl;
				out.addInt(COLLATZ_VOCAB_ITEM);
				out.addInt(new_N);
				out.addInt(new_T);

				cout << "sending message to client.."<< endl;
				server_port.reply(out);
			}

			in.clear();
      out.clear();
  		return true;
  	}


    bool configure(yarp::os::ResourceFinder &rf)
    {
			CNT = 0;
      string port_name = rf.find("name").asString().c_str();

      server_port.open(("/"+port_name).c_str());
      cout << "opened port: /" + port_name << endl;

      //attach(server_port);
      //cout <<"attached port: /"+port_name<< endl;

      return true;
    }

    bool interruptModule()
    {
      server_port.interrupt();
      return true;
    }

    bool close()
    {

      server_port.close();

      return true;
    }

		void ereseTested(int N){
			std::list<int>::iterator it = FIFO.begin();
			bool found = false;
			while(!found && it != FIFO.end()){
				if(*it == tested_N){
					cout << "number"<<*it<< "tested. Eresing.." << endl;
					FIFO.erase(it);
					found = true;
				}
				it++;
			}
			if(!found){
				cout << "number"<<tested_N<< "Not found in the FIFO..." << endl;
			}

		}
};

  int main(int argc, char * argv[])
  {
    /* initialize yarp network */
    Network yarp;
    /* create your module */
    ServerModule module;
    /* prepare and configure the resource finder */
    ResourceFinder rf;
    rf.configure(argc, argv);
    rf.setVerbose(true);
    cout << "Configuring and starting module. \n";
    module.runModule(rf);   // This calls configure(rf) and, upon success, the module execution begins with a call to updateModule()
    cout<<"Main returning..."<<endl;
    return module.runModule(rf);
  }
