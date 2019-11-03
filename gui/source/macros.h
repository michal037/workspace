/*
 * MIT License
 * Copyright (c) 2017 Michal Kozakiewicz, github.com/michal037
 */

#ifndef GLOBAL_MACROS_H
#define GLOBAL_MACROS_H

/** Object's macros **/
/* Method with arguments */
#define obj(object, method, ...) ((object).method(&(object), __VA_ARGS__))

/* Method with arguments but without 'this' object */
#define objwt(object, method, ...) ((object).method(__VA_ARGS__))

/* Method without arguments */
#define objwa(object, method) ((object).method(&(object)))

/* Variable  */
#define objv(object, variable) ((object).variable)

/** Function public / private **/
#define public
#define private static

/** max() / min() **/
#define M3MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define M3MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _b : _a; })

#endif /* GLOBAL_MACROS_H */
