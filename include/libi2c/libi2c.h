/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016, Christopher Friedt <chrisfriedt@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef LIBI2C_H_
#define LIBI2C_H_

#include <sys/cdefs.h>

#include <stdint.h>
#include <sys/types.h>

__BEGIN_DECLS

#if defined( __linux__ )

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#else

#define I2C_RETRIES	0x0701
#define I2C_TIMEOUT	0x0702
#define I2C_SLAVE	0x0703
#define I2C_SLAVE_FORCE	0x0706
#define I2C_TENBIT	0x0704
#define I2C_FUNCS	0x0705
#define I2C_RDWR	0x0707
#define I2C_PEC		0x0708
#define I2C_SMBUS	0x0720

#define I2C_M_TEN		0x0010
#define I2C_M_RD		0x0001
#define I2C_M_STOP		0x8000
#define I2C_M_NOSTART		0x4000
#define I2C_M_REV_DIR_ADDR	0x2000
#define I2C_M_IGNORE_NAK	0x1000
#define I2C_M_NO_RD_ACK		0x0800
#define I2C_M_RECV_LEN		0x0400

struct i2c_msg {
	uint16_t addr;
	uint16_t flags;
	uint16_t len;
	uint8_t *buf;
};


struct i2c_rdwr_ioctl_data {
	struct i2c_msg *msgs;
	uint32_t nmsgs;
};

#define  I2C_RDWR_IOCTL_MAX_MSGS	42

#endif // defined( __linux__ )

ssize_t i2c_transfer( unsigned bus, struct i2c_msg *msg, size_t count );
ssize_t i2c_read( unsigned bus, uint16_t addr, void *buf, size_t buf_len );
ssize_t i2c_write( unsigned bus, uint16_t addr, void *buf, size_t buf_len );

__END_DECLS

#endif // LIBI2C_H_
