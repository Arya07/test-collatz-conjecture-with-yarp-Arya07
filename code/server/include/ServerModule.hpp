/*
 * author: Elisa Maiettini
 * date: 26/11/2016
 */
#include <iostream>
#include <iomanip>
#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/RpcServer.h>
#include <yarp/os/Semaphore.h>

#include <vocabs.hpp>
#include <FIFOHandler.hpp>

#include <stdio.h>
#include <string>
#include <ctime>
#include <vector>

using namespace std;
using namespace yarp::os;

class ServerModule : public RFModule{
private:

	RpcServer        server_port;
	int              CNT;
  FIFOHandler 	   *fifo_handler;

public:

  double getPeriod(){
    return 1.0;
  }

  bool interruptModule(){
    server_port.interrupt();
    return true;
  }

  bool close(){
    server_port.close();
    return true;
  }

  virtual bool respond(const Bottle &command, Bottle &reply);


  virtual bool updateModule();

  bool configure(yarp::os::ResourceFinder &rf);

};
