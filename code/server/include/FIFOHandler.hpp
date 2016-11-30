/*
 * author: Elisa Maiettini
 * date: 30/11/2016
 */

#include <yarp/os/RateThread.h>
#include <yarp/os/Semaphore.h>

#include <vector>
#include <iostream>

using namespace std;
using namespace yarp::os;

class FIFOHandler : public RateThread{

private:

  Semaphore        fifo_mutex;
  vector<int>      FIFO;

public:

  FIFOHandler() : RateThread(10){}

  FIFOHandler(int ms_period) : RateThread(ms_period){}

  virtual void initThread();

  virtual void run();

  virtual void interrupt();

  virtual bool releaseThread();

  int getHead();

  vector<int> getFIFO();

  void eraseTested(int N);

  void pushBack(int N);

};
