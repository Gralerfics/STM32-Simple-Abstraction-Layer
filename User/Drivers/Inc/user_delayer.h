//
// Created by Gralerfics on 2022/12/18.
//

#ifndef _USER_DELAYER_H_
#define _USER_DELAYER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

class Delayer {
public:
	static void byFactor(uint32_t _t, uint32_t _factor);

	static void s(uint32_t _t);
	static void ms(uint32_t _t);
	static void us(uint32_t _t);
};

#ifdef __cplusplus
}
#endif

#endif
