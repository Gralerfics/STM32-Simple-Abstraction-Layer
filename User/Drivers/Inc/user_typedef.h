//
// Created by Gralerfics on 2022/12/18.
//

#ifndef _USER_TYPEDEF_H_
#define _USER_TYPEDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

typedef enum {
	OK = 0,
	FAIL,
	IDLE,
	BUSY,
	COMPLETE,
	RESERVE
} UserState;

typedef enum {
	s, ms, us, Hz, kHz, MHz
} UserTimeUnit;

typedef void (*UserCallbackFunc)();

#ifdef __cplusplus
}
#endif

#endif
