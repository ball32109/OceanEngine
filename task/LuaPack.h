#ifndef LUAPACK_H
#define LUAPACK_H

#define BLOCK_SIZE 128


class LuaPack
{
public:
	struct Block {
		Block* _next;
		char _buffer[BLOCK_SIZE];
	};

	struct WriteBlock {
		Block* _head;
		Block* _current;
		int _len;
		int _ptr;
	};

public:
	LuaPack(void);
	~LuaPack(void);

protected:

};

#endif