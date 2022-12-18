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
	USER_STATE_OK = 0,
	USER_STATE_FAIL,
	USER_STATE_IDLE,
	USER_STATE_BUSY,
	USER_STATE_COMPLETE,
	USER_STATE_RESERVE
} UserState;

#ifdef __cplusplus
}
#endif

#endif
