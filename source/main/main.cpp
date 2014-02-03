#include <iostream>

#include "main/main_app.hpp"

using namespace std;

int main(int argc, const char* argv[]) {
	try {
		return MainApp(argc, argv).run();
	}
	catch(exception& e) {
		cerr << "Exception thrown: " << e.what() << endl;
		cerr << "Exiting..." << endl;
		return 1;
	}
	catch(...) {
		cerr << "Unknown exception occured" << endl;
		return 1;
	}
}

