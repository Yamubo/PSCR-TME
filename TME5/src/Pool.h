#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize) ;
	void start (int nbthread){
		threads.reserve(nbthread);
		for(int i = 0 ; i < nbthread ; i++){
			threads.emplace_back(poolWorker,ref(queue));
		}
	}
	void submit (Job * job) ;
	void stop(){
		queue.setBlocking(false);
		for(auto &t_threads : threads){
			t.join();
		}
		threads.clear();
	}

	void poolWorker(Queue<Job> & queue){
		while(true){
			Job * j = queue.pop();
			if(j==nullptr)break;
			j -> run();
			J -> delete(); 
		}
	}
	~Pool() ;
};

}
