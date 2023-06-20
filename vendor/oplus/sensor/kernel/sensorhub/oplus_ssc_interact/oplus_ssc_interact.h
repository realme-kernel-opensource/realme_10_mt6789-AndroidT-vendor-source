/* SPDX-License-Identifier: GPL-2.0-only  */
/*
 * Copyright (C) 2018-2020 Oplus. All rights reserved.
 */
#ifndef __OPLUS_SSC_INTERACTIVE_H__
#define __OPLUS_SSC_INTERACTIVE_H__

#include <linux/miscdevice.h>
#include <linux/kfifo.h>
#include <linux/spinlock.h>
#include <linux/workqueue.h>
#include <linux/kobject.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/param.h>
#include <linux/notifier.h>

enum {
	NONE_TYPE = 0,
	LCM_DC_MODE_TYPE,
	LCM_BRIGHTNESS_TYPE,
	MAX_INFO_TYPE,
};


enum {
	LCM_DC_OFF = 0,
	LCM_DC_ON  = 1
};

struct als_info{
	uint16_t brightness;
	uint16_t dc_mode;
};

struct fifo_frame{
	uint8_t type;
	uint16_t data;
};

struct ssc_interactive{
	struct als_info a_info;
	struct miscdevice mdev;
	DECLARE_KFIFO_PTR(fifo, struct fifo_frame);
	spinlock_t fifo_lock;
	spinlock_t rw_lock;
	wait_queue_head_t wq;
	struct notifier_block nb;
	bool report_brightness;
};

#endif /* __OPLUS_SSC_INTERACTIVE_H__ */
