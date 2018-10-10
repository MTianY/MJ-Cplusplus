//
//  test_c.h
//  C++FirstDemo
//
//  Created by 马天野 on 2018/10/11.
//  Copyright © 2018 Maty. All rights reserved.
//

#ifndef test_c_h
#define test_c_h

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    int getSum(int a, int b);
#ifdef __cplusplus
}
#endif

#endif /* test_c_h */


