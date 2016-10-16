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

#include <iostream>

#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "libi2c/I2c.h"

using namespace ::std;
using namespace ::com::github::cfriedt;

I2c::I2c( unsigned bus )
:
	bus( bus )
{
}
I2c::I2c()
:
	bus( -1 )
{
}

I2c::~I2c() {
}

size_t I2c::read( uint16_t addr, void *buf, size_t buf_len ) {
	ssize_t r;
 	r = i2c_read( bus, addr, buf, buf_len );
 	if ( buf_len != (size_t)r ) {
 		if ( 0 == errno ) {
 			errno = EIO;
 		}
		throw std::system_error( errno, std::system_category() );
 	}
	return r;
}

size_t I2c::write( uint16_t addr, void *buf, size_t buf_len ) {
	ssize_t r;
 	r = i2c_write( bus, addr, buf, buf_len );
 	if ( buf_len != (size_t)r ) {
 		if ( 0 == errno ) {
 			errno = EIO;
 		}
		throw std::system_error( errno, std::system_category() );
 	}
	return r;
}

size_t I2c::transfer( i2c_msg *msg, size_t count ) {
	ssize_t r;
 	r = i2c_transfer( bus, msg, count );
 	if ( count != (size_t)r ) {
 		if ( 0 == errno ) {
 			errno = EIO;
 		}
		throw std::system_error( errno, std::system_category() );
 	}

	return r;
}
