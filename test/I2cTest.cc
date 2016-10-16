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

#include <stdlib.h> // EXIT_SUCCESS, getenv(3), atoi(3)
#include <sys/utsname.h> // uname(3)

#include <gtest/gtest.h>

#include "libi2c/I2c.h"

using namespace ::std;
using namespace ::com::github::cfriedt;

#ifndef ARRAY_SIZE
#define ARRAY_SIZE( x ) ( sizeof( x ) / sizeof( (x)[ 0 ] ) )
#endif // ARRAY_SIZE

#define OSPASS_() \
	if ( ospass ) { \
		std::cout << "skipping test because this platform is not 'Linux'" << std::endl; \
		return; \
	} \

class I2cTest : public ::testing::Test
{

public:

	I2c i2c;
	bool ospass;

	I2cTest();
	~I2cTest();

void SetUp();
void TearDown();
};

I2cTest::I2cTest()
{
}

I2cTest::~I2cTest() {
}

void I2cTest::SetUp() {
	struct utsname utsname;
	int rr;

	rr = uname( & utsname );
	ASSERT_EQ( EXIT_SUCCESS, rr );
	ospass = 0 != strcmp( "Linux", utsname.sysname );
	if ( ! ospass ) {
		i2c = I2c( 0 );
	}
}

void I2cTest::TearDown() {
}

TEST_F( I2cTest, I2cRead ) {

	OSPASS_();

	// read from the AT24

	size_t expected_size_t;
	size_t actual_size_t;

	const uint16_t addr = 0x50;
	uint8_t buf[ 2 ];

	expected_size_t = ARRAY_SIZE( buf );
	actual_size_t = i2c.read( addr, buf, expected_size_t );

	EXPECT_EQ( expected_size_t, actual_size_t );
}

TEST_F( I2cTest, I2cWrite ) {

	OSPASS_();

	// write to the AT24

	size_t expected_size_t;
	size_t actual_size_t;

	const uint16_t addr = 0x50;
	uint8_t buf[ 3 ] = { 0, 0, 0, };

	expected_size_t = ARRAY_SIZE( buf );
	actual_size_t = i2c.write( addr, buf, expected_size_t );

	EXPECT_EQ( expected_size_t, actual_size_t );
}

TEST_F( I2cTest, TestI2cTransfer ) {

	OSPASS_();

	const uint16_t addr = 0x50;

	size_t expected_size_t;
	size_t actual_size_t;

	uint8_t tx_buf[ 2 ] = { 0, 0, };
	uint8_t rx_buf[ 2 ] = { 0xa, 0xb, };

	struct i2c_msg msg[ 2 ];

	msg[ 0 ].addr = addr;
	msg[ 0 ].flags = 0;
	msg[ 0 ].buf = tx_buf;
	msg[ 0 ].len = ARRAY_SIZE( tx_buf );

	msg[ 1 ].addr = addr;
	msg[ 1 ].flags = I2C_M_RD;
	msg[ 1 ].buf = rx_buf;
	msg[ 1 ].len = ARRAY_SIZE( rx_buf );

	expected_size_t = ARRAY_SIZE( msg );
	actual_size_t = i2c.transfer( msg, expected_size_t );

	EXPECT_EQ( expected_size_t, actual_size_t );
}
