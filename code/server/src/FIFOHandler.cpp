/*
 * author: Elisa Maiettini
 * date: 30/11/2016
 */
#include <FIFOHandler.hpp>

 using namespace std;
 using namespace yarp::os;

 bool FIFOHandler::threadInit(){
   cout << "FIFOHandler: thread inizialization" << endl;
   FIFO = std::vector<int>();
   fifo_mutex = yarp::os::Semaphore();
   return true;

 }

 void FIFOHandler::run(){
   fifo_mutex.wait();

   cout << "FIFOHandler: the current FIFO is: {";
   std::vector<int>::iterator it;
   for(it = FIFO.begin(); it != FIFO.end() ; it++ ){
      cout << *it << " ";
   }
   cout << "}" << endl;
   fifo_mutex.post();
 }

 int FIFOHandler::getHead(){
   fifo_mutex.wait();
   int head = FIFO.front();
   fifo_mutex.post();
   return head;
 }

 void FIFOHandler::eraseTested(int tested_N){
   cout << "ServerModule: eresing tested number"<< tested_N << "from the FIFO" <<endl;
   std::vector<int>::iterator it = FIFO.begin();
   bool found = false;
   while(!found && it != FIFO.end()){
     if(*it == tested_N){
       FIFO.erase(it);
       found = true;
     }
     it++;
   }
   if(!found){
     cout << "ServerModule: number "<<tested_N<< "Not found in the FIFO..." << endl;
   }
 }

 void FIFOHandler::pushBack(int N){
   FIFO.push_back(N);
 }

 void FIFOHandler::interrupt(){
   cout << "FIFOHandler: thread interrupted" <<endl;
 }

 void FIFOHandler::threadRelease(){
   cout << "FIFOHandler: thread released" <<endl;
 }
