#ifndef __SIGNAL_HPP__
#define __SIGNAL_HPP__

class Signal
{
private:
	bool _read_ready;
	bool _write_ready;

public:
	Signal();
	~Signal();

	void setRead(bool b);
	void setWrite(bool b);
	bool writeReady();
	bool readReady();
};

#endif // __SIGNAL_HPP__
