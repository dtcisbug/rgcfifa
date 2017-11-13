#ifndef NONCOPYALBE_INC
#define NONCOPYALBE_INC

class Noncopyable
{
protected:
	Noncopyable() {}
	~Noncopyable() {}
private:  // emphasize the following members are private
	Noncopyable( const Noncopyable& );
	const Noncopyable& operator=( const Noncopyable& );
};

#endif