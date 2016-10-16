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

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#include <limits.h>

#include "libi2c/libi2c.h"

ssize_t i2c_transfer( unsigned bus, struct i2c_msg *msg, size_t count ) {
	ssize_t r;
	int fd = -1;
	char path[ 24 ];
//	int i;

	struct i2c_rdwr_ioctl_data data = {
		.msgs = msg,
		.nmsgs = count,
	};
/*
	for( i = 0; i < count; i++ ) {
		printf(
			"msg[  %u ]@%p\n\t"
			"addr: %04x\n\t"
			"buf:  %p\n\t"
			"len:  %u\n"
			,
			i, & msg[ i ],
			msg[ i ].addr,
			msg[ i ].buf,
			msg[ i ].len
		);
	}
*/

	memset( path, 0, sizeof( path ) );
	snprintf( path, sizeof( path ) - 1, "/dev/i2c-%u", bus );

	r = open( path, O_RDWR );
	if ( -1 == r ) {
		perror( "open" );
		goto out;
	}
	fd = r;

	r = ioctl( fd, I2C_SLAVE, msg[ 0 ].addr );
	if ( -1 == r ) {
		perror( "ioctl I2C_SLAVE" );
		goto closefd;
	}

	r = ioctl( fd, I2C_RDWR, & data );
	if ( -1 == r ) {
		perror( "ioctl I2C_RDWR" );
		goto closefd;
	}

closefd:
	close( fd );
	fd = -1;

out:
	return r;
}

ssize_t i2c_read( unsigned bus, uint16_t addr, void *buf, size_t buf_len ) {

	int r;

	struct i2c_msg msg;

	memset( & msg, 0, sizeof( msg ) );

	msg.addr = addr;
	msg.buf = buf;
	msg.flags = I2C_M_RD;
	msg.len = buf_len;

	r = i2c_transfer( bus, & msg, 1 );
	if ( 1 == r ) {
		r = buf_len;
	}

	return r;
}

ssize_t i2c_write( unsigned bus, uint16_t addr, void *buf, size_t buf_len ) {
	ssize_t r;

	struct i2c_msg msg;

	msg.addr = addr;
	msg.flags = 0;

	msg.buf = buf;
	msg.len = buf_len;

	r = i2c_transfer( bus, &msg, 1 );
	if ( 1 == r ) {
		r = buf_len;
	}
	return r;
}
