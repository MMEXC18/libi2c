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

#ifndef libi2c_I2c_h_
#define libi2c_I2c_h_

#include <stdint.h>

#include "libi2c/libi2c.h"

namespace com {
namespace github {
namespace cfriedt {

class I2c {

public:
	I2c( unsigned bus );
	I2c();
	virtual ~I2c();

	size_t read( uint16_t addr, void *buf, size_t buf_len );
	size_t write( uint16_t addr, void *buf, size_t buf_len );
	size_t transfer( i2c_msg *msg, size_t msg_len );

protected:
	unsigned bus;
};

}
}
} // com.github.cfriedt

#endif // libi2c_I2c_h_
