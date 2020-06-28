#include <iostream>
#include <cstdlib>
#include <glog/logging.h>

#include "wmmm.hpp"

int main (int argc, char* argv[]) {

	::google::InitGoogleLogging(argv[0]);
	std::unique_ptr<WMMM> wmmm(WMMM::create()); 

	if (!wmmm) {

		LOG(ERROR) << "Failed to initialise window manager.";
		return EXIT_FAILURE;
	}

	wmmm->run();

	return EXIT_SUCCESS;

}
