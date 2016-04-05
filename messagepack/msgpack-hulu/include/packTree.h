/*************************************************************************
    > File Name: packNode.h
    > Author: shuaixiang
    > Mail: shuaixiang@yuewen.com
    > Created Time: Tue 05 Apr 2016 06:21:32 AM UTC
 ************************************************************************/

#include "packer.h"

#ifdef __cplusplus
extern "C" {
#endif

    //interface
    void PackTree_Child(Object *node, Object *obj);
    void PackTree_Next(Object *node, Object *obj);

    Object* PackNode_String(string_t str, size_t len);
    Object* PackNode_Char(char c);
    Object* PackNode_Short(short d);
    Object* PackNode_Int(int d);
    Object* PackNode_Long(long d);
    Object* PackNode_LongLong(long long d);
    Object* PackNode_UnsignedChar(unsigned char d);
    Object* PackNode_UnsignedShort(unsigned short d);
    Object* PackNode_UnsignedInt(unsigned int d);
    Object* PackNode_UnsignedLong(unsigned long d);
    Object* PackNode_UnsignedLongLong(unsigned long long d);
    Object* PackNode_Nil();
    Object* PackNode_True();
    Object* PackNode_False();
    Object* PackNode_Float(float d);
    Object* PackNode_Double(double d);
    Object* PackNode_Bin(ubyte_t * b, size_t len);
#ifdef __cplusplus
}
#endif
