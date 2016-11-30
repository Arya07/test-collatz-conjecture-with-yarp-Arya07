/*
 * author: Elisa Maiettini
 * date: 30/11/2016
 */

#include <yarp/os/RateThread.h>

#include <list>

#include<ServerModule.hpp>


using namespace std;
using namespace yarp::os;

class FIFOController : public RateThread{

private:

  ServerModule server_moudle;

public:

  FIFOController(int ms_period, ServerModule &server_moudle);

  virtual void threadInit();

  virtual void run();

  virtual void interrupt();

  virtual bool releaseThread();

}
