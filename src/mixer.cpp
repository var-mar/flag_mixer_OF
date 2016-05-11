#include "mixer.h"

mixer::mixer() {}

void mixer::setup(vector<flag>* _flags) {
	flags = _flags;
	mixedFlag = new flag();
	mixedFlag->setup(
		flags->at(0).getBackground(),
		flags->at(1).getLayers(),
		flags->at(2).getMotif()
	);

}

flag* mixer::getMixedFlag() {
	return mixedFlag;
}