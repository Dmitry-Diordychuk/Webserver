#include "Signal.hpp"

Signal::Signal(/* args */) : _read_ready(false), _write_ready(false) {}

Signal::~Signal() {}

void Signal::setRead(bool b) {
	_read_ready = b;
}

void Signal::setWrite(bool b) {
	_write_ready = b;
}

bool Signal::writeReady() {
	bool ret = _write_ready;
	_write_ready = false;
	return (ret);
}

bool Signal::readReady() {
	bool ret = _read_ready;
	_read_ready = false;
	return (ret);
}
