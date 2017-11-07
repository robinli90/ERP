// Disable4786.h
//
//
//

#ifndef _DISABLE4786_H_
#define _DISABLE4786_H_

#pragma warning(disable:4786)

class MSVC6_4786WorkAround {
public:
	MSVC6_4786WorkAround() {}
};

static MSVC6_4786WorkAround MSVC6_IS_A_PIECE_OF_SHIT;

#endif
