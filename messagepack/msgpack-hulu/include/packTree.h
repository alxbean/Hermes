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
    //data struct
    typedef struct{
        Object *root;
        Object *node;
        bool_t isChild;
    } TreeCTX;

    //interface
    TreeCTX * InitPackTree();
    void PackNode_String(TreeCTX *ctx, string_t str, size_t len);
    void PackNode_Char(TreeCTX *ctx, char c);
    void PackNode_Short(TreeCTX *ctx, short d);
    void PackNode_Int(TreeCTX *ctx, int d);
    void PackNode_Long(TreeCTX *ctx, long d);
    void PackNode_LongLong(TreeCTX *ctx, long long d);
    void PackNode_UnsignedChar(TreeCTX *ctx, unsigned char d);
    void PackNode_UnsignedShort(TreeCTX *ctx, unsigned short d);
    void PackNode_UnsignedInt(TreeCTX *ctx, unsigned int d);
    void PackNode_UnsignedLong(TreeCTX *ctx, unsigned long d);
    void PackNode_UnsignedLongLong(TreeCTX *ctx, unsigned long long d);
    void PackNode_Nil(TreeCTX *ctx);
    void PackNode_True(TreeCTX *ctx);
    void PackNode_False(TreeCTX *ctx);
    void PackNode_Float(TreeCTX *ctx, float d);
    void PackNode_Double(TreeCTX *ctx, double d);
    void PackNode_Bin(TreeCTX *ctx, ubyte_t * b, size_t len);
    void PackNode_ArrayBegin(TreeCTX *ctx);
    void PackNode_ArrayEnd(TreeCTX *ctx);
    void PackNode_MapBegin(TreeCTX *ctx);
    void PackNode_MapEnd(TreeCTX *ctx);
#ifdef __cplusplus
}
#endif
