#pragma once

#include "ofMain.h"

#include "Constants.h"

#include "detail/coroutine.hpp"
// more info about boost::coroutine => http://www.boost.org/doc/libs/1_54_0/doc/html/boost_asio/reference/coroutine.html

OFX_ANIMATION_PRIMITIVES_BEGIN_NAMESPACE

typedef coroutine Generator;

#ifndef $seq
# define $seq(c) CORO_REENTER(c)
#endif

#ifndef $inf
# define $inf(c) CORO_REENTER(c) for(;;)
#endif

#ifndef yield
# define yield CORO_YIELD
#endif

#ifndef fork
# define fork CORO_FORK
#endif

OFX_ANIMATION_PRIMITIVES_END_NAMESPACE