//
// Created by Gralerfics on 2022/12/18.
//

#ifndef _USER_STATE_H_
#define _USER_STATE_H_

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

#ifdef __cplusplus
}
#endif

#endif
