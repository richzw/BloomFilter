
class Unpacked_BOOL{
  bool imp;

public:
  	Unpacked_BOOL(bool b=false):imp(b){}
	Unpacked_BOOL(int b):imp(b){}
	Unpacked_BOOL(const Unpacked_BOOL& b):imp(b.imp){}

	operator const bool&() const { return imp; }
	operator bool&() { return imp; }

	bool& operator=(bool b) { return imp = b; }
	bool& operator=(int b) { return imp = b; }
	bool& operator=(const Unpacked_BOOL& b) { return imp = b.imp; }
};
