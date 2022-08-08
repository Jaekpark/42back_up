#ifndef _FT_CONFIG_HPP
#define _FT_CONFIG_HPP

#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>

#define _BEGIN_NAMESPACE_FT namespace ft {
#define _END_NAMESPACE_FT }

#define INPUT_ITER 1
#define OUTPUT_ITER 2
#define FORWARD_ITER 3
#define BIDIR_ITER 4
#define RANDOM_ITER 5
#ifndef NAMESPACE
#define NAMESPACE ft
#endif

#endif