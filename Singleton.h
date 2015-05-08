
#ifndef _2____Singleton_h
#define _2____Singleton_h

// 此为一个完全单例的宏


// .h中的单例声明
#define singleton_h(name) + (instancetype)share##name;


// .m中的单例实现，可以自动判断当前环境是ARC还是非ARC
// ARC
#if __has_feature(objc_arc)
#define singleton_m(name) \
static id instance;\
+ (instancetype)allocWithZone:(struct _NSZone *)zone\
{\
    static dispatch_once_t onceToken;\
    dispatch_once(&onceToken, ^{\
        instance = [super allocWithZone:zone];\
    });\
    return instance;\
}\
\
+ (instancetype)share##name\
{\
    static dispatch_once_t onceToken;\
    dispatch_once(&onceToken, ^{\
        instance = [[self alloc] init];\
    });\
    return instance;\
}\
+ (id)copyWithZone:(struct _NSZone *)zone\
{\
    return instance;\
}

// 非ARC
#else

#define singleton_m(name) \
static id instance;\
+ (instancetype)allocWithZone:(struct _NSZone *)zone\
{\
    static dispatch_once_t onceToken;\
    dispatch_once(&onceToken, ^{\
    instance = [super allocWithZone:zone];\
    });\
    return instance;\
}\
\
+ (instancetype)share##name\
{\
    static dispatch_once_t onceToken;\
    dispatch_once(&onceToken, ^{\
    instance = [[self alloc] init];\
    });\
    return instance;\
}\
- (oneway void)release\
{\
   \
}\
- (instancetype)retain\
{\
    return self;\
}\
- (NSUInteger)retainCount\
{\
    return 1;\
}\
- (instancetype)autorelease\
{\
    return self;\
}\
+ (id)copyWithZone:(struct _NSZone *)zone\
{\
    return instance;\
}

#endif

#endif
