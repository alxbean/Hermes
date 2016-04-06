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

    //PackTree
    void PackTree_String(TreeCTX *ctx, string_t str, size_t len);
    void PackTree_Char(TreeCTX *ctx, char d);
    void PackTree_Short(TreeCTX *ctx, short d);
    void PackTree_Int(TreeCTX *ctx, int d);
    void PackTree_Long(TreeCTX *ctx, long d);
    void PackTree_LongLong(TreeCTX *ctx, long long d);
    void PackTree_UnsignedChar(TreeCTX *ctx, unsigned char d);
    void PackTree_UnsignedShort(TreeCTX *ctx, unsigned short d);
    void PackTree_UnsignedInt(TreeCTX *ctx, unsigned int d);
    void PackTree_UnsignedLong(TreeCTX *ctx, unsigned long d);
    void PackTree_UnsignedLongLong(TreeCTX *ctx, unsigned long long d);
    void PackTree_Nil(TreeCTX *ctx);
    void PackTree_True(TreeCTX *ctx);
    void PackTree_False(TreeCTX *ctx);
    void PackTree_Float(TreeCTX *ctx, float d);
    void PackTree_Double(TreeCTX *ctx, double d);
    void PackTree_Bin(TreeCTX *ctx, ubyte_t * b, size_t len);
    void PackTree_ArrayBegin(TreeCTX *ctx);
    void PackTree_ArrayEnd(TreeCTX *ctx);
    void PackTree_MapBegin(TreeCTX *ctx);
    void PackTree_MapEnd(TreeCTX *ctx);

    //PackMap
    void PackMap_String_Int(TreeCTX *ctx, string_t k, size_t len,  int v);
    void PackMap_String_Long(TreeCTX *ctx, string_t k, size_t len,  long v);
    void PackMap_String_LongLong(TreeCTX *ctx, string_t k, size_t len,  long long v);
    void PackMap_String_Float(TreeCTX *ctx, string_t k, size_t len,  float v);
    void PackMap_String_Double(TreeCTX *ctx, string_t k, size_t len, double v);
    void PackMap_String_String(TreeCTX *ctx, string_t k, size_t len,  string_t v, size_t vlen);
    void PackMap_String_Bin(TreeCTX *ctx, string_t k, size_t len, ubyte_t *v, size_t vlen);
    void PackMap_Int_Int(TreeCTX *ctx, int k, int v);
    void PackMap_Int_Long(TreeCTX *ctx, int k, long v);
    void PackMap_Int_LongLong(TreeCTX *ctx, int k, long long v);
    void PackMap_Int_Float(TreeCTX *ctx, int k, float v);
    void PackMap_Int_Double(TreeCTX *ctx, int k, double v);
    void PackMap_Int_String(TreeCTX *ctx, int k, string_t v, size_t vlen);
    void PackMap_Int_Bin(TreeCTX *ctx, int k, ubyte_t *v, size_t vlen);
    
#ifdef __cplusplus
}
#endif
