/*
** Lua binding: game
** Generated automatically by tolua++-1.0.92 on 07/04/14 16:43:29.
*/

/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "tolua_fix.h"

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "gameEngine.h"

using namespace cocos2d;




#include "gameEngine.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_uint64 (lua_State* tolua_S)
{
 uint64* self = (uint64*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ByteBuffer (lua_State* tolua_S)
{
 ByteBuffer* self = (ByteBuffer*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Guid (lua_State* tolua_S)
{
 Guid* self = (Guid*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_U8Ptr (lua_State* tolua_S)
{
 U8Ptr* self = (U8Ptr*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_InAppPurchaseDelegate (lua_State* tolua_S)
{
 InAppPurchaseDelegate* self = (InAppPurchaseDelegate*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_WorldPacket (lua_State* tolua_S)
{
 WorldPacket* self = (WorldPacket*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ByteBufferException (lua_State* tolua_S)
{
 ByteBufferException* self = (ByteBufferException*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_HeroPacketHeader (lua_State* tolua_S)
{
 HeroPacketHeader* self = (HeroPacketHeader*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"PlatformUtility");
 tolua_usertype(tolua_S,"Guid");
 tolua_usertype(tolua_S,"uint8");
 tolua_usertype(tolua_S,"InAppPurchaseDelegate");
 tolua_usertype(tolua_S,"WorldPacket");
 tolua_usertype(tolua_S,"uint64");
 tolua_usertype(tolua_S,"CNetConnection");
 tolua_usertype(tolua_S,"InAppPurchaseInterface");
 tolua_usertype(tolua_S,"CCScriptAction");
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"uint16");
 tolua_usertype(tolua_S,"U8Ptr");
 tolua_usertype(tolua_S,"ByteBuffer");
 tolua_usertype(tolua_S,"CCActionInterval");
 tolua_usertype(tolua_S,"ProductInfo");
 
 tolua_usertype(tolua_S,"FileIO");
 tolua_usertype(tolua_S,"ByteBufferException");
 tolua_usertype(tolua_S,"HeroPacketHeader");
}

/* method: new of class  U8Ptr */
#ifndef TOLUA_DISABLE_tolua_game_U8Ptr_new00
static int tolua_game_U8Ptr_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"U8Ptr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int len = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   U8Ptr* tolua_ret = (U8Ptr*)  Mtolua_new((U8Ptr)(len));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"U8Ptr");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  U8Ptr */
#ifndef TOLUA_DISABLE_tolua_game_U8Ptr_new00_local
static int tolua_game_U8Ptr_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"U8Ptr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int len = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   U8Ptr* tolua_ret = (U8Ptr*)  Mtolua_new((U8Ptr)(len));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"U8Ptr");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  U8Ptr */
#ifndef TOLUA_DISABLE_tolua_game_U8Ptr_new01
static int tolua_game_U8Ptr_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"U8Ptr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* p = ((const char*)  tolua_tostring(tolua_S,2,0));
  int len = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   U8Ptr* tolua_ret = (U8Ptr*)  Mtolua_new((U8Ptr)(p,len));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"U8Ptr");
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_U8Ptr_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  U8Ptr */
#ifndef TOLUA_DISABLE_tolua_game_U8Ptr_new01_local
static int tolua_game_U8Ptr_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"U8Ptr",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* p = ((const char*)  tolua_tostring(tolua_S,2,0));
  int len = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   U8Ptr* tolua_ret = (U8Ptr*)  Mtolua_new((U8Ptr)(p,len));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"U8Ptr");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_U8Ptr_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  U8Ptr */
#ifndef TOLUA_DISABLE_tolua_game_U8Ptr_delete00
static int tolua_game_U8Ptr_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"U8Ptr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  U8Ptr* self = (U8Ptr*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Guid */
#ifndef TOLUA_DISABLE_tolua_game_Guid_new00
static int tolua_game_Guid_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Guid",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Guid* tolua_ret = (Guid*)  Mtolua_new((Guid)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Guid");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Guid */
#ifndef TOLUA_DISABLE_tolua_game_Guid_new00_local
static int tolua_game_Guid_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Guid",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Guid* tolua_ret = (Guid*)  Mtolua_new((Guid)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Guid");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: printDebug of class  Guid */
#ifndef TOLUA_DISABLE_tolua_game_Guid_printDebug00
static int tolua_game_Guid_printDebug00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Guid",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Guid* self = (Guid*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'printDebug'", NULL);
#endif
  {
   self->printDebug();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'printDebug'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: equals of class  Guid */
#ifndef TOLUA_DISABLE_tolua_game_Guid_equals00
static int tolua_game_Guid_equals00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Guid",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Guid",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Guid* self = (Guid*)  tolua_tousertype(tolua_S,1,0);
  Guid* guid = ((Guid*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'equals'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->equals(guid);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'equals'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ByteBufferException */
#ifndef TOLUA_DISABLE_tolua_game_ByteBufferException_new00
static int tolua_game_ByteBufferException_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ByteBufferException",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool _add = ((bool)  tolua_toboolean(tolua_S,2,0));
  unsigned int _pos = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int _esize = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
  unsigned int _size = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
  {
   ByteBufferException* tolua_ret = (ByteBufferException*)  Mtolua_new((ByteBufferException)(_add,_pos,_esize,_size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ByteBufferException");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ByteBufferException */
#ifndef TOLUA_DISABLE_tolua_game_ByteBufferException_new00_local
static int tolua_game_ByteBufferException_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ByteBufferException",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool _add = ((bool)  tolua_toboolean(tolua_S,2,0));
  unsigned int _pos = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  unsigned int _esize = (( unsigned int)  tolua_tonumber(tolua_S,4,0));
  unsigned int _size = (( unsigned int)  tolua_tonumber(tolua_S,5,0));
  {
   ByteBufferException* tolua_ret = (ByteBufferException*)  Mtolua_new((ByteBufferException)(_add,_pos,_esize,_size));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ByteBufferException");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PrintPosError of class  ByteBufferException */
#ifndef TOLUA_DISABLE_tolua_game_ByteBufferException_PrintPosError00
static int tolua_game_ByteBufferException_PrintPosError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ByteBufferException",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ByteBufferException* self = (const ByteBufferException*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PrintPosError'", NULL);
#endif
  {
   self->PrintPosError();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrintPosError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DEFAULT_SIZE of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_get_ByteBuffer_unsigned_DEFAULT_SIZE
static int tolua_get_ByteBuffer_unsigned_DEFAULT_SIZE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)ByteBuffer::DEFAULT_SIZE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_new00
static int tolua_game_ByteBuffer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ByteBuffer* tolua_ret = (ByteBuffer*)  Mtolua_new((ByteBuffer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ByteBuffer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_new00_local
static int tolua_game_ByteBuffer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ByteBuffer* tolua_ret = (ByteBuffer*)  Mtolua_new((ByteBuffer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ByteBuffer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_new01
static int tolua_game_ByteBuffer_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned int res = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   ByteBuffer* tolua_ret = (ByteBuffer*)  Mtolua_new((ByteBuffer)(res));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ByteBuffer");
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_ByteBuffer_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_new01_local
static int tolua_game_ByteBuffer_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned int res = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  {
   ByteBuffer* tolua_ret = (ByteBuffer*)  Mtolua_new((ByteBuffer)(res));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ByteBuffer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_ByteBuffer_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_new02
static int tolua_game_ByteBuffer_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ByteBuffer",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ByteBuffer* buf = ((const ByteBuffer*)  tolua_tousertype(tolua_S,2,0));
  {
   ByteBuffer* tolua_ret = (ByteBuffer*)  Mtolua_new((ByteBuffer)(*buf));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ByteBuffer");
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_ByteBuffer_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_new02_local
static int tolua_game_ByteBuffer_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ByteBuffer",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ByteBuffer* buf = ((const ByteBuffer*)  tolua_tousertype(tolua_S,2,0));
  {
   ByteBuffer* tolua_ret = (ByteBuffer*)  Mtolua_new((ByteBuffer)(*buf));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ByteBuffer");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_ByteBuffer_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_clear00
static int tolua_game_ByteBuffer_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rpos of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_rpos00
static int tolua_game_ByteBuffer_rpos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ByteBuffer* self = (const ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rpos'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->rpos();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rpos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rpos of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_rpos01
static int tolua_game_ByteBuffer_rpos01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int rpos_ = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rpos'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->rpos(rpos_);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_ByteBuffer_rpos00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: wpos of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_wpos00
static int tolua_game_ByteBuffer_wpos00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ByteBuffer* self = (const ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'wpos'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->wpos();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'wpos'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: wpos of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_wpos01
static int tolua_game_ByteBuffer_wpos01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int wpos_ = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'wpos'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->wpos(wpos_);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_ByteBuffer_wpos00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: readPackGUID of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_readPackGUID00
static int tolua_game_ByteBuffer_readPackGUID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'readPackGUID'", NULL);
#endif
  {
   uint64 tolua_ret = (uint64)  self->readPackGUID();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint64));
     tolua_pushusertype(tolua_S,tolua_obj,"uint64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readPackGUID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: contents of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_contents00
static int tolua_game_ByteBuffer_contents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ByteBuffer* self = (const ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'contents'", NULL);
#endif
  {
   const uint8* tolua_ret = (const uint8*)  self->contents();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const uint8");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'contents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: size of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_size00
static int tolua_game_ByteBuffer_size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ByteBuffer* self = (const ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->size();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: empty of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_empty00
static int tolua_game_ByteBuffer_empty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ByteBuffer* self = (const ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'empty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->empty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'empty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: appendPackXYZ of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_appendPackXYZ00
static int tolua_game_ByteBuffer_appendPackXYZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'appendPackXYZ'", NULL);
#endif
  {
   self->appendPackXYZ(x,y,z);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'appendPackXYZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: appendPackGUID of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_appendPackGUID00
static int tolua_game_ByteBuffer_appendPackGUID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint64",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  uint64 guid = *((uint64*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'appendPackGUID'", NULL);
#endif
  {
   self->appendPackGUID(guid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'appendPackGUID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: append of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_append00
static int tolua_game_ByteBuffer_append00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const U8Ptr",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  const U8Ptr* str = ((const U8Ptr*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'append'", NULL);
#endif
  {
   self->append(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'append'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: put of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_put00
static int tolua_game_ByteBuffer_put00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  unsigned int pos = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'put'", NULL);
#endif
  {
   self->put(pos,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'put'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setU8 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_setU800
static int tolua_game_ByteBuffer_setU800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setU8'", NULL);
#endif
  {
   self->setU8(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setU8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getU8 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_getU800
static int tolua_game_ByteBuffer_getU800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getU8'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getU8();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getU8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setU16 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_setU1600
static int tolua_game_ByteBuffer_setU1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setU16'", NULL);
#endif
  {
   self->setU16(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setU16'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getU16 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_getU1600
static int tolua_game_ByteBuffer_getU1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getU16'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getU16();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getU16'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setU32 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_setU3200
static int tolua_game_ByteBuffer_setU3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setU32'", NULL);
#endif
  {
   self->setU32(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setU32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getU32 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_getU3200
static int tolua_game_ByteBuffer_getU3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getU32'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getU32();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getU32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setI8 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_setI800
static int tolua_game_ByteBuffer_setI800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setI8'", NULL);
#endif
  {
   self->setI8(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setI8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getI8 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_getI800
static int tolua_game_ByteBuffer_getI800(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getI8'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getI8();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getI8'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setI16 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_setI1600
static int tolua_game_ByteBuffer_setI1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setI16'", NULL);
#endif
  {
   self->setI16(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setI16'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getI16 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_getI1600
static int tolua_game_ByteBuffer_getI1600(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getI16'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getI16();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getI16'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setI32 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_setI3200
static int tolua_game_ByteBuffer_setI3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setI32'", NULL);
#endif
  {
   self->setI32(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setI32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getI32 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_getI3200
static int tolua_game_ByteBuffer_getI3200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getI32'", NULL);
#endif
  {
   int tolua_ret = (int)  self->getI32();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getI32'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFloat of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_setFloat00
static int tolua_game_ByteBuffer_setFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFloat'", NULL);
#endif
  {
   self->setFloat(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFloat of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_getFloat00
static int tolua_game_ByteBuffer_getFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFloat'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getFloat();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStr of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_setStr00
static int tolua_game_ByteBuffer_setStr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStr'", NULL);
#endif
  {
   self->setStr(str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStr of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_getStr00
static int tolua_game_ByteBuffer_getStr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStr'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getStr();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setU64 of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_setU6400
static int tolua_game_ByteBuffer_setU6400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Guid",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  Guid* guid = ((Guid*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setU64'", NULL);
#endif
  {
   self->setU64(guid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setU64'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPackGuid of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_setPackGuid00
static int tolua_game_ByteBuffer_setPackGuid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Guid",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  Guid* guid = ((Guid*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setPackGuid'", NULL);
#endif
  {
   self->setPackGuid(guid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPackGuid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: read of class  ByteBuffer */
#ifndef TOLUA_DISABLE_tolua_game_ByteBuffer_read00
static int tolua_game_ByteBuffer_read00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ByteBuffer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"U8Ptr",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ByteBuffer* self = (ByteBuffer*)  tolua_tousertype(tolua_S,1,0);
  U8Ptr* p = ((U8Ptr*)  tolua_tousertype(tolua_S,2,0));
  unsigned int t = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'read'", NULL);
#endif
  {
   self->read(p,t);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'read'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_new00
static int tolua_game_WorldPacket_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   WorldPacket* tolua_ret = (WorldPacket*)  Mtolua_new((WorldPacket)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WorldPacket");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_new00_local
static int tolua_game_WorldPacket_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   WorldPacket* tolua_ret = (WorldPacket*)  Mtolua_new((WorldPacket)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WorldPacket");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_new01
static int tolua_game_WorldPacket_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int opcode = ((int)  tolua_tonumber(tolua_S,2,0));
  int res = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   WorldPacket* tolua_ret = (WorldPacket*)  Mtolua_new((WorldPacket)(opcode,res));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WorldPacket");
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_WorldPacket_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_new01_local
static int tolua_game_WorldPacket_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int opcode = ((int)  tolua_tonumber(tolua_S,2,0));
  int res = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   WorldPacket* tolua_ret = (WorldPacket*)  Mtolua_new((WorldPacket)(opcode,res));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WorldPacket");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_WorldPacket_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_new02
static int tolua_game_WorldPacket_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"uint64",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int opcode = ((int)  tolua_tonumber(tolua_S,2,0));
  uint64 guid = *((uint64*)  tolua_tousertype(tolua_S,3,0));
  int res = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   WorldPacket* tolua_ret = (WorldPacket*)  Mtolua_new((WorldPacket)(opcode,guid,res));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WorldPacket");
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_WorldPacket_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_new02_local
static int tolua_game_WorldPacket_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"uint64",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int opcode = ((int)  tolua_tonumber(tolua_S,2,0));
  uint64 guid = *((uint64*)  tolua_tousertype(tolua_S,3,0));
  int res = ((int)  tolua_tonumber(tolua_S,4,0));
  {
   WorldPacket* tolua_ret = (WorldPacket*)  Mtolua_new((WorldPacket)(opcode,guid,res));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WorldPacket");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_WorldPacket_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_new03
static int tolua_game_WorldPacket_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const WorldPacket",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const WorldPacket* packet = ((const WorldPacket*)  tolua_tousertype(tolua_S,2,0));
  {
   WorldPacket* tolua_ret = (WorldPacket*)  Mtolua_new((WorldPacket)(*packet));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WorldPacket");
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_WorldPacket_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_new03_local
static int tolua_game_WorldPacket_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const WorldPacket",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const WorldPacket* packet = ((const WorldPacket*)  tolua_tousertype(tolua_S,2,0));
  {
   WorldPacket* tolua_ret = (WorldPacket*)  Mtolua_new((WorldPacket)(*packet));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WorldPacket");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_game_WorldPacket_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Initialize of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_Initialize00
static int tolua_game_WorldPacket_Initialize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  WorldPacket* self = (WorldPacket*)  tolua_tousertype(tolua_S,1,0);
  int opcode = ((int)  tolua_tonumber(tolua_S,2,0));
  int newres = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Initialize'", NULL);
#endif
  {
   self->Initialize(opcode,newres);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Initialize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Initialize of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_Initialize01
static int tolua_game_WorldPacket_Initialize01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"uint64",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  WorldPacket* self = (WorldPacket*)  tolua_tousertype(tolua_S,1,0);
  int opcode = ((int)  tolua_tonumber(tolua_S,2,0));
  uint64 guid = *((uint64*)  tolua_tousertype(tolua_S,3,0));
  int newres = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Initialize'", NULL);
#endif
  {
   self->Initialize(opcode,guid,newres);
  }
 }
 return 0;
tolua_lerror:
 return tolua_game_WorldPacket_Initialize00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOpcode of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_GetOpcode00
static int tolua_game_WorldPacket_GetOpcode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  WorldPacket* self = (WorldPacket*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOpcode'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetOpcode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOpcode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOpcode of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_SetOpcode00
static int tolua_game_WorldPacket_SetOpcode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  WorldPacket* self = (WorldPacket*)  tolua_tousertype(tolua_S,1,0);
  int opcode = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOpcode'", NULL);
#endif
  {
   self->SetOpcode(opcode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOpcode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGuid of class  WorldPacket */
#ifndef TOLUA_DISABLE_tolua_game_WorldPacket_SetGuid00
static int tolua_game_WorldPacket_SetGuid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"WorldPacket",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Guid",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  WorldPacket* self = (WorldPacket*)  tolua_tousertype(tolua_S,1,0);
  Guid* guid = ((Guid*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGuid'", NULL);
#endif
  {
   self->SetGuid(guid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGuid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: packetLength of class  HeroPacketHeader */
#ifndef TOLUA_DISABLE_tolua_get_HeroPacketHeader_unsigned_packetLength
static int tolua_get_HeroPacketHeader_unsigned_packetLength(lua_State* tolua_S)
{
  HeroPacketHeader* self = (HeroPacketHeader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'packetLength'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->packetLength);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: packetLength of class  HeroPacketHeader */
#ifndef TOLUA_DISABLE_tolua_set_HeroPacketHeader_unsigned_packetLength
static int tolua_set_HeroPacketHeader_unsigned_packetLength(lua_State* tolua_S)
{
  HeroPacketHeader* self = (HeroPacketHeader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'packetLength'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->packetLength = (( unsigned int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: version of class  HeroPacketHeader */
#ifndef TOLUA_DISABLE_tolua_get_HeroPacketHeader_version
static int tolua_get_HeroPacketHeader_version(lua_State* tolua_S)
{
  HeroPacketHeader* self = (HeroPacketHeader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'version'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->version,"uint8");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: version of class  HeroPacketHeader */
#ifndef TOLUA_DISABLE_tolua_set_HeroPacketHeader_version
static int tolua_set_HeroPacketHeader_version(lua_State* tolua_S)
{
  HeroPacketHeader* self = (HeroPacketHeader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'version'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint8",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->version = *((uint8*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: flag of class  HeroPacketHeader */
#ifndef TOLUA_DISABLE_tolua_get_HeroPacketHeader_flag
static int tolua_get_HeroPacketHeader_flag(lua_State* tolua_S)
{
  HeroPacketHeader* self = (HeroPacketHeader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flag'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->flag,"uint8");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: flag of class  HeroPacketHeader */
#ifndef TOLUA_DISABLE_tolua_set_HeroPacketHeader_flag
static int tolua_set_HeroPacketHeader_flag(lua_State* tolua_S)
{
  HeroPacketHeader* self = (HeroPacketHeader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'flag'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint8",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->flag = *((uint8*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: cmd of class  HeroPacketHeader */
#ifndef TOLUA_DISABLE_tolua_get_HeroPacketHeader_cmd
static int tolua_get_HeroPacketHeader_cmd(lua_State* tolua_S)
{
  HeroPacketHeader* self = (HeroPacketHeader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cmd'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->cmd,"uint16");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: cmd of class  HeroPacketHeader */
#ifndef TOLUA_DISABLE_tolua_set_HeroPacketHeader_cmd
static int tolua_set_HeroPacketHeader_cmd(lua_State* tolua_S)
{
  HeroPacketHeader* self = (HeroPacketHeader*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'cmd'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint16",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->cmd = *((uint16*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  HeroPacketHeader */
#ifndef TOLUA_DISABLE_tolua_game_HeroPacketHeader_new00
static int tolua_game_HeroPacketHeader_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HeroPacketHeader",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint16",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  uint16 _cmd = *((uint16*)  tolua_tousertype(tolua_S,2,0));
  unsigned int _length = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   HeroPacketHeader* tolua_ret = (HeroPacketHeader*)  Mtolua_new((HeroPacketHeader)(_cmd,_length));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HeroPacketHeader");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  HeroPacketHeader */
#ifndef TOLUA_DISABLE_tolua_game_HeroPacketHeader_new00_local
static int tolua_game_HeroPacketHeader_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"HeroPacketHeader",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"uint16",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  uint16 _cmd = *((uint16*)  tolua_tousertype(tolua_S,2,0));
  unsigned int _length = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   HeroPacketHeader* tolua_ret = (HeroPacketHeader*)  Mtolua_new((HeroPacketHeader)(_cmd,_length));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"HeroPacketHeader");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NetThreadBody */
#ifndef TOLUA_DISABLE_tolua_game_NetThreadBody00
static int tolua_game_NetThreadBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* param = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   void* tolua_ret = (void*)  NetThreadBody(param);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NetThreadBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Instance of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_Instance00
static int tolua_game_CNetConnection_Instance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CNetConnection& tolua_ret = (CNetConnection&)  CNetConnection::Instance();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"CNetConnection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Instance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsConnected of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_IsConnected00
static int tolua_game_CNetConnection_IsConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
   int state = ((  int)  tolua_tonumber(tolua_S,2,-1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsConnected'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsConnected(state);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsConnected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CloseSocket of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_CloseSocket00
static int tolua_game_CNetConnection_CloseSocket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CloseSocket'", NULL);
#endif
  {
   self->CloseSocket();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CloseSocket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAuthed of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_IsAuthed00
static int tolua_game_CNetConnection_IsAuthed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAuthed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsAuthed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAuthed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ConnectLoginServer of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_ConnectLoginServer00
static int tolua_game_CNetConnection_ConnectLoginServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  const char* address = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ConnectLoginServer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ConnectLoginServer(address);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ConnectLoginServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ConnectGameServer of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_ConnectGameServer00
static int tolua_game_CNetConnection_ConnectGameServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ConnectGameServer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ConnectGameServer();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ConnectGameServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DisConnect of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_DisConnect00
static int tolua_game_CNetConnection_DisConnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  bool force = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DisConnect'", NULL);
#endif
  {
   self->DisConnect(force);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DisConnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_Update00
static int tolua_game_CNetConnection_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'", NULL);
#endif
  {
   self->Update();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendPacket of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_SendPacket00
static int tolua_game_CNetConnection_SendPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"WorldPacket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  WorldPacket* pkt = ((WorldPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendPacket'", NULL);
#endif
  {
   self->SendPacket(pkt);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendPacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRecv of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_OnRecv00
static int tolua_game_CNetConnection_OnRecv00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  unsigned int Bytes = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRecv'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OnRecv(Bytes);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRecv'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FlushData of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_FlushData00
static int tolua_game_CNetConnection_FlushData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FlushData'", NULL);
#endif
  {
   self->FlushData();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FlushData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnFirstChallenge of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_OnFirstChallenge00
static int tolua_game_CNetConnection_OnFirstChallenge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnFirstChallenge'", NULL);
#endif
  {
   self->OnFirstChallenge();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnFirstChallenge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetConnectType of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_GetConnectType00
static int tolua_game_CNetConnection_GetConnectType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetConnectType'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->GetConnectType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetConnectType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetConnectType of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_SetConnectType00
static int tolua_game_CNetConnection_SetConnectType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  unsigned int type = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetConnectType'", NULL);
#endif
  {
   self->SetConnectType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetConnectType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPingCode of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_SetPingCode00
static int tolua_game_CNetConnection_SetPingCode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  int opcode = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPingCode'", NULL);
#endif
  {
   self->SetPingCode(opcode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPingCode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnSendPing of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_OnSendPing00
static int tolua_game_CNetConnection_OnSendPing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnSendPing'", NULL);
#endif
  {
   self->OnSendPing();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnSendPing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OnRecvPong of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_OnRecvPong00
static int tolua_game_CNetConnection_OnRecvPong00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  unsigned int pingTime = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OnRecvPong'", NULL);
#endif
  {
   self->OnRecvPong(pingTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OnRecvPong'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAvgPing of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_GetAvgPing00
static int tolua_game_CNetConnection_GetAvgPing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAvgPing'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->GetAvgPing();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAvgPing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearPingStatistics of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_ClearPingStatistics00
static int tolua_game_CNetConnection_ClearPingStatistics00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearPingStatistics'", NULL);
#endif
  {
   self->ClearPingStatistics();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearPingStatistics'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setVersion of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_setVersion00
static int tolua_game_CNetConnection_setVersion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  unsigned int version = (( unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setVersion'", NULL);
#endif
  {
   self->setVersion(version);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setVersion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClientMd5 of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_getClientMd500
static int tolua_game_CNetConnection_getClientMd500(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClientMd5'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getClientMd5();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClientMd5'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getClientSeed of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_getClientSeed00
static int tolua_game_CNetConnection_getClientSeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getClientSeed'", NULL);
#endif
  {
   unsigned int tolua_ret = ( unsigned int)  self->getClientSeed();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getClientSeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUserName of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_getUserName00
static int tolua_game_CNetConnection_getUserName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUserName'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->getUserName();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUserName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUserNameAndPassWord of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_SetUserNameAndPassWord00
static int tolua_game_CNetConnection_SetUserNameAndPassWord00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  std::string uName = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::string pWord = ((std::string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUserNameAndPassWord'", NULL);
#endif
  {
   self->SetUserNameAndPassWord(uName,pWord);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUserNameAndPassWord'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetClientMd5Str of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_GetClientMd5Str00
static int tolua_game_CNetConnection_GetClientMd5Str00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"U8Ptr",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,4,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  U8Ptr* loginSeed = ((U8Ptr*)  tolua_tousertype(tolua_S,2,0));
  std::string rClientSeed = ((std::string)  tolua_tocppstring(tolua_S,3,0));
  std::string rClientMd5Str = ((std::string)  tolua_tocppstring(tolua_S,4,0));
  std::string rClientUnk = ((std::string)  tolua_tocppstring(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClientMd5Str'", NULL);
#endif
  {
   self->GetClientMd5Str(loginSeed,rClientSeed,rClientMd5Str,rClientUnk);
   tolua_pushcppstring(tolua_S,(const char*)rClientSeed);
   tolua_pushcppstring(tolua_S,(const char*)rClientMd5Str);
   tolua_pushcppstring(tolua_S,(const char*)rClientUnk);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClientMd5Str'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendLoginPacket of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_SendLoginPacket00
static int tolua_game_CNetConnection_SendLoginPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"WorldPacket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  WorldPacket* packet = ((WorldPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendLoginPacket'", NULL);
#endif
  {
   self->SendLoginPacket(packet);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendLoginPacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendSignInPacket of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_SendSignInPacket00
static int tolua_game_CNetConnection_SendSignInPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendSignInPacket'", NULL);
#endif
  {
   self->SendSignInPacket();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendSignInPacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ConnectFailed of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_ConnectFailed00
static int tolua_game_CNetConnection_ConnectFailed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ConnectFailed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ConnectFailed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ConnectFailed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Next of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_Next00
static int tolua_game_CNetConnection_Next00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Next'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Next();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Next'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReleasePacket of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_ReleasePacket00
static int tolua_game_CNetConnection_ReleasePacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"WorldPacket",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  WorldPacket* recv = ((WorldPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReleasePacket'", NULL);
#endif
  {
   self->ReleasePacket(recv);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReleasePacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPacket of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_GetPacket00
static int tolua_game_CNetConnection_GetPacket00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPacket'", NULL);
#endif
  {
   WorldPacket* tolua_ret = (WorldPacket*)  self->GetPacket();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"WorldPacket");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPacket'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsLoginState of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_IsLoginState00
static int tolua_game_CNetConnection_IsLoginState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  int state = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsLoginState'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsLoginState(state);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsLoginState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLoginState of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_setLoginState00
static int tolua_game_CNetConnection_setLoginState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  int state = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLoginState'", NULL);
#endif
  {
   self->setLoginState(state);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLoginState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HandleNull of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_HandleNull00
static int tolua_game_CNetConnection_HandleNull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"WorldPacket",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  WorldPacket* recvPacket = ((WorldPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HandleNull'", NULL);
#endif
  {
   self->HandleNull(*recvPacket);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HandleNull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HandleClientSide of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_HandleClientSide00
static int tolua_game_CNetConnection_HandleClientSide00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"WorldPacket",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  WorldPacket* recvPacket = ((WorldPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HandleClientSide'", NULL);
#endif
  {
   self->HandleClientSide(*recvPacket);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HandleClientSide'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HandleLoginRealmListResponse of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_HandleLoginRealmListResponse00
static int tolua_game_CNetConnection_HandleLoginRealmListResponse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"WorldPacket",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  WorldPacket* recvPacket = ((WorldPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HandleLoginRealmListResponse'", NULL);
#endif
  {
   self->HandleLoginRealmListResponse(*recvPacket);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HandleLoginRealmListResponse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HandleGameAuthChallengeResponse of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_HandleGameAuthChallengeResponse00
static int tolua_game_CNetConnection_HandleGameAuthChallengeResponse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"WorldPacket",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  WorldPacket* recvPacket = ((WorldPacket*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HandleGameAuthChallengeResponse'", NULL);
#endif
  {
   self->HandleGameAuthChallengeResponse(*recvPacket);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HandleGameAuthChallengeResponse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sendAuthSessionMessage of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_sendAuthSessionMessage00
static int tolua_game_CNetConnection_sendAuthSessionMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sendAuthSessionMessage'", NULL);
#endif
  {
   self->sendAuthSessionMessage();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sendAuthSessionMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptFunc of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_registerScriptFunc00
static int tolua_game_CNetConnection_registerScriptFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION handleId = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptFunc'", NULL);
#endif
  {
   self->registerScriptFunc(handleId);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptHandler of class  CNetConnection */
#ifndef TOLUA_DISABLE_tolua_game_CNetConnection_unregisterScriptHandler00
static int tolua_game_CNetConnection_unregisterScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CNetConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CNetConnection* self = (CNetConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptHandler'", NULL);
#endif
  {
   self->unregisterScriptHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: productId of class  ProductInfo */
#ifndef TOLUA_DISABLE_tolua_get_ProductInfo_productId
static int tolua_get_ProductInfo_productId(lua_State* tolua_S)
{
  ProductInfo* self = (ProductInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'productId'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->productId);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: productId of class  ProductInfo */
#ifndef TOLUA_DISABLE_tolua_set_ProductInfo_productId
static int tolua_set_ProductInfo_productId(lua_State* tolua_S)
{
  ProductInfo* self = (ProductInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'productId'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->productId = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: price of class  ProductInfo */
#ifndef TOLUA_DISABLE_tolua_get_ProductInfo_price
static int tolua_get_ProductInfo_price(lua_State* tolua_S)
{
  ProductInfo* self = (ProductInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'price'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->price);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: price of class  ProductInfo */
#ifndef TOLUA_DISABLE_tolua_set_ProductInfo_price
static int tolua_set_ProductInfo_price(lua_State* tolua_S)
{
  ProductInfo* self = (ProductInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'price'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->price = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_new00
static int tolua_game_InAppPurchaseDelegate_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   InAppPurchaseDelegate* tolua_ret = (InAppPurchaseDelegate*)  Mtolua_new((InAppPurchaseDelegate)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"InAppPurchaseDelegate");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_new00_local
static int tolua_game_InAppPurchaseDelegate_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   InAppPurchaseDelegate* tolua_ret = (InAppPurchaseDelegate*)  Mtolua_new((InAppPurchaseDelegate)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"InAppPurchaseDelegate");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_delete00
static int tolua_game_InAppPurchaseDelegate_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addProduct of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_addProduct00
static int tolua_game_InAppPurchaseDelegate_addProduct00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
  const char* productId = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* price = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addProduct'", NULL);
#endif
  {
   self->addProduct(productId,price);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addProduct'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: queryProducts of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_queryProducts00
static int tolua_game_InAppPurchaseDelegate_queryProducts00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'queryProducts'", NULL);
#endif
  {
   self->queryProducts();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'queryProducts'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: purchase of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_purchase00
static int tolua_game_InAppPurchaseDelegate_purchase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'purchase'", NULL);
#endif
  {
   self->purchase(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'purchase'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPrice of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_getPrice00
static int tolua_game_InAppPurchaseDelegate_getPrice00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
  unsigned int index = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getPrice'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->getPrice(index);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPrice'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: queryProductFinish of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_queryProductFinish00
static int tolua_game_InAppPurchaseDelegate_queryProductFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'queryProductFinish'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->queryProductFinish();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'queryProductFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onQueryProductFinish of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_onQueryProductFinish00
static int tolua_game_InAppPurchaseDelegate_onQueryProductFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onQueryProductFinish'", NULL);
#endif
  {
   self->onQueryProductFinish();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onQueryProductFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onPurchaseFinish of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_onPurchaseFinish00
static int tolua_game_InAppPurchaseDelegate_onPurchaseFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
  void* content = ((void*)  tolua_touserdata(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onPurchaseFinish'", NULL);
#endif
  {
   self->onPurchaseFinish(content);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onPurchaseFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onPurchaseFailed of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_onPurchaseFailed00
static int tolua_game_InAppPurchaseDelegate_onPurchaseFailed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
  const char* desc = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onPurchaseFailed'", NULL);
#endif
  {
   self->onPurchaseFailed(desc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onPurchaseFailed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptHandler of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_registerScriptHandler00
static int tolua_game_InAppPurchaseDelegate_registerScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION nHandler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptHandler'", NULL);
#endif
  {
   self->registerScriptHandler(nHandler);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterScriptHandler of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_unregisterScriptHandler00
static int tolua_game_InAppPurchaseDelegate_unregisterScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterScriptHandler'", NULL);
#endif
  {
   self->unregisterScriptHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearProduct of class  InAppPurchaseDelegate */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseDelegate_clearProduct00
static int tolua_game_InAppPurchaseDelegate_clearProduct00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* self = (InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearProduct'", NULL);
#endif
  {
   self->clearProduct();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearProduct'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initStore of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseInterface_initStore00
static int tolua_game_InAppPurchaseInterface_initStore00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InAppPurchaseInterface",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"InAppPurchaseDelegate",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  InAppPurchaseDelegate* delegate = ((InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  InAppPurchaseInterface::initStore(delegate);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initStore'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: canMakePurchases of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseInterface_canMakePurchases00
static int tolua_game_InAppPurchaseInterface_canMakePurchases00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InAppPurchaseInterface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  InAppPurchaseInterface::canMakePurchases();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'canMakePurchases'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: queryProductInfo of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseInterface_queryProductInfo00
static int tolua_game_InAppPurchaseInterface_queryProductInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InAppPurchaseInterface",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* productIdArray = ((const char*)  tolua_tostring(tolua_S,2,0));
   int size = ((  int)  tolua_tonumber(tolua_S,3,0));
  {
   InAppPurchaseInterface::queryProductInfo(&productIdArray,size);
   tolua_pushstring(tolua_S,(const char*)productIdArray);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'queryProductInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onQueryProductBack of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseInterface_onQueryProductBack00
static int tolua_game_InAppPurchaseInterface_onQueryProductBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InAppPurchaseInterface",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* productId = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* price = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   InAppPurchaseInterface::onQueryProductBack(productId,price);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onQueryProductBack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onQueryProductFinish of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseInterface_onQueryProductFinish00
static int tolua_game_InAppPurchaseInterface_onQueryProductFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InAppPurchaseInterface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   InAppPurchaseInterface::onQueryProductFinish();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onQueryProductFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: makePurchase of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseInterface_makePurchase00
static int tolua_game_InAppPurchaseInterface_makePurchase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InAppPurchaseInterface",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* productId = ((const char*)  tolua_tostring(tolua_S,2,0));
   int quantity = ((  int)  tolua_tonumber(tolua_S,3,0));
  {
   InAppPurchaseInterface::makePurchase(productId,quantity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'makePurchase'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onPurchaseFinish of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseInterface_onPurchaseFinish00
static int tolua_game_InAppPurchaseInterface_onPurchaseFinish00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InAppPurchaseInterface",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* backData = ((void*)  tolua_touserdata(tolua_S,2,0));
   int size = ((  int)  tolua_tonumber(tolua_S,3,0));
  {
   InAppPurchaseInterface::onPurchaseFinish(backData,size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onPurchaseFinish'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onPurchaseFailed of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_game_InAppPurchaseInterface_onPurchaseFailed00
static int tolua_game_InAppPurchaseInterface_onPurchaseFailed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"InAppPurchaseInterface",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* desc = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   InAppPurchaseInterface::onPurchaseFailed(desc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onPurchaseFailed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hasInit of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_get_InAppPurchaseInterface_hasInit
static int tolua_get_InAppPurchaseInterface_hasInit(lua_State* tolua_S)
{
  tolua_pushboolean(tolua_S,(bool)InAppPurchaseInterface::hasInit);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hasInit of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_set_InAppPurchaseInterface_hasInit
static int tolua_set_InAppPurchaseInterface_hasInit(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  InAppPurchaseInterface::hasInit = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: _delegate of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_get_InAppPurchaseInterface__delegate_ptr
static int tolua_get_InAppPurchaseInterface__delegate_ptr(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)InAppPurchaseInterface::_delegate,"InAppPurchaseDelegate");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: _delegate of class  InAppPurchaseInterface */
#ifndef TOLUA_DISABLE_tolua_set_InAppPurchaseInterface__delegate_ptr
static int tolua_set_InAppPurchaseInterface__delegate_ptr(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!tolua_isusertype(tolua_S,2,"InAppPurchaseDelegate",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  InAppPurchaseInterface::_delegate = ((InAppPurchaseDelegate*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: OpenRate of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_OpenRate00
static int tolua_game_PlatformUtility_OpenRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlatformUtility::OpenRate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OpenRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OpenFullLink of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_OpenFullLink00
static int tolua_game_PlatformUtility_OpenFullLink00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* link = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   PlatformUtility::OpenFullLink(link);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OpenFullLink'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNetUseable of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_IsNetUseable00
static int tolua_game_PlatformUtility_IsNetUseable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  PlatformUtility::IsNetUseable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNetUseable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDeviceMacAddress of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_GetDeviceMacAddress00
static int tolua_game_PlatformUtility_GetDeviceMacAddress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  PlatformUtility::GetDeviceMacAddress();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDeviceMacAddress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLockScreen of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_SetLockScreen00
static int tolua_game_PlatformUtility_SetLockScreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool canLock = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   PlatformUtility::SetLockScreen(canLock);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLockScreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsTheseProcessRunning of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_IsTheseProcessRunning00
static int tolua_game_PlatformUtility_IsTheseProcessRunning00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* checkProcesses = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned int size = (( unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  PlatformUtility::IsTheseProcessRunning(&checkProcesses,size);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushstring(tolua_S,(const char*)checkProcesses);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsTheseProcessRunning'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPhysicalMemory of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_GetPhysicalMemory00
static int tolua_game_PlatformUtility_GetPhysicalMemory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   uint64 tolua_ret = (uint64)  PlatformUtility::GetPhysicalMemory();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint64));
     tolua_pushusertype(tolua_S,tolua_obj,"uint64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPhysicalMemory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSystemUptime of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_GetSystemUptime00
static int tolua_game_PlatformUtility_GetSystemUptime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   uint64 tolua_ret = (uint64)  PlatformUtility::GetSystemUptime();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((uint64)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"uint64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(uint64));
     tolua_pushusertype(tolua_S,tolua_obj,"uint64");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSystemUptime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetKeychain of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_GetKeychain00
static int tolua_game_PlatformUtility_GetKeychain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  PlatformUtility::GetKeychain();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetKeychain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnonymAccount of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_getAnonymAccount00
static int tolua_game_PlatformUtility_getAnonymAccount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  PlatformUtility::getAnonymAccount();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnonymAccount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAccount of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_getAccount00
static int tolua_game_PlatformUtility_getAccount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  PlatformUtility::getAccount();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAccount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getPassword of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_getPassword00
static int tolua_game_PlatformUtility_getPassword00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  PlatformUtility::getPassword();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getPassword'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnonymAccount of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_setAnonymAccount00
static int tolua_game_PlatformUtility_setAnonymAccount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* account = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   PlatformUtility::setAnonymAccount(account);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnonymAccount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAccount of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_setAccount00
static int tolua_game_PlatformUtility_setAccount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* account = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   PlatformUtility::setAccount(account);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAccount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setPassword of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_setPassword00
static int tolua_game_PlatformUtility_setPassword00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* password = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   PlatformUtility::setPassword(password);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setPassword'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SaveMacToKeychain of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_SaveMacToKeychain00
static int tolua_game_PlatformUtility_SaveMacToKeychain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* mac_address = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  PlatformUtility::SaveMacToKeychain(mac_address);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SaveMacToKeychain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDeviceIfa of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_GetDeviceIfa00
static int tolua_game_PlatformUtility_GetDeviceIfa00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  PlatformUtility::GetDeviceIfa();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDeviceIfa'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CallTrackingIFA of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_CallTrackingIFA00
static int tolua_game_PlatformUtility_CallTrackingIFA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlatformUtility::CallTrackingIFA();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CallTrackingIFA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDeviceIdentify of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_GetDeviceIdentify00
static int tolua_game_PlatformUtility_GetDeviceIdentify00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::string tolua_ret = (std::string)  PlatformUtility::GetDeviceIdentify();
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDeviceIdentify'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initTapjoy of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_initTapjoy00
static int tolua_game_PlatformUtility_initTapjoy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlatformUtility::initTapjoy();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initTapjoy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initLimeiCPC of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_initLimeiCPC00
static int tolua_game_PlatformUtility_initLimeiCPC00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PlatformUtility::initLimeiCPC();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initLimeiCPC'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showiAd of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_showiAd00
static int tolua_game_PlatformUtility_showiAd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  bool bshow = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   PlatformUtility::showiAd(bshow);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showiAd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDeviceValue of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_getDeviceValue00
static int tolua_game_PlatformUtility_getDeviceValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int flag = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   bool tolua_ret = (bool)  PlatformUtility::getDeviceValue(flag);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDeviceValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDeviceValue of class  PlatformUtility */
#ifndef TOLUA_DISABLE_tolua_game_PlatformUtility_setDeviceValue00
static int tolua_game_PlatformUtility_setDeviceValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PlatformUtility",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int flag = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   PlatformUtility::setDeviceValue(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDeviceValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  FileIO */
#ifndef TOLUA_DISABLE_tolua_game_FileIO_create00
static int tolua_game_FileIO_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"FileIO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   FileIO* tolua_ret = (FileIO*)  FileIO::create();
    int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"FileIO");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: init of class  FileIO */
#ifndef TOLUA_DISABLE_tolua_game_FileIO_init00
static int tolua_game_FileIO_init00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileIO",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileIO* self = (FileIO*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'init'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->init();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'init'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFileData of class  FileIO */
#ifndef TOLUA_DISABLE_tolua_game_FileIO_getFileData00
static int tolua_game_FileIO_getFileData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileIO",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileIO* self = (FileIO*)  tolua_tousertype(tolua_S,1,0);
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFileData'", NULL);
#endif
  {
   ByteBuffer* tolua_ret = (ByteBuffer*)  self->getFileData(filename);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ByteBuffer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFileData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCScriptAction */
#ifndef TOLUA_DISABLE_tolua_game_CCScriptAction_create00
static int tolua_game_CCScriptAction_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCScriptAction",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float d = ((float)  tolua_tonumber(tolua_S,2,0));
  LUA_FUNCTION nScriptHandler = (  toluafix_ref_function(tolua_S,3,0));
  {
   CCScriptAction* tolua_ret = (CCScriptAction*)  CCScriptAction::create(d,nScriptHandler);
    int nID = (tolua_ret) ? (int)tolua_ret->_ID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->_luaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCScriptAction");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_game_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"U8Ptr","U8Ptr","",tolua_collect_U8Ptr);
  #else
  tolua_cclass(tolua_S,"U8Ptr","U8Ptr","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"U8Ptr");
   tolua_function(tolua_S,"new",tolua_game_U8Ptr_new00);
   tolua_function(tolua_S,"new_local",tolua_game_U8Ptr_new00_local);
   tolua_function(tolua_S,".call",tolua_game_U8Ptr_new00_local);
   tolua_function(tolua_S,"new",tolua_game_U8Ptr_new01);
   tolua_function(tolua_S,"new_local",tolua_game_U8Ptr_new01_local);
   tolua_function(tolua_S,".call",tolua_game_U8Ptr_new01_local);
   tolua_function(tolua_S,"delete",tolua_game_U8Ptr_delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Guid","Guid","",tolua_collect_Guid);
  #else
  tolua_cclass(tolua_S,"Guid","Guid","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Guid");
   tolua_function(tolua_S,"new",tolua_game_Guid_new00);
   tolua_function(tolua_S,"new_local",tolua_game_Guid_new00_local);
   tolua_function(tolua_S,".call",tolua_game_Guid_new00_local);
   tolua_function(tolua_S,"printDebug",tolua_game_Guid_printDebug00);
   tolua_function(tolua_S,"equals",tolua_game_Guid_equals00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"LOCALE_enUS",LOCALE_enUS);
  tolua_constant(tolua_S,"LOCALE_koKR",LOCALE_koKR);
  tolua_constant(tolua_S,"LOCALE_frFR",LOCALE_frFR);
  tolua_constant(tolua_S,"LOCALE_deDE",LOCALE_deDE);
  tolua_constant(tolua_S,"LOCALE_zhCN",LOCALE_zhCN);
  tolua_constant(tolua_S,"LOCALE_zhTW",LOCALE_zhTW);
  tolua_constant(tolua_S,"LOCALE_esES",LOCALE_esES);
  tolua_constant(tolua_S,"LOCALE_esMX",LOCALE_esMX);
  tolua_constant(tolua_S,"LOCALE_ruRU",LOCALE_ruRU);
  tolua_constant(tolua_S,"MAX_LOCALE",MAX_LOCALE);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ByteBufferException","ByteBufferException","",tolua_collect_ByteBufferException);
  #else
  tolua_cclass(tolua_S,"ByteBufferException","ByteBufferException","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ByteBufferException");
   tolua_function(tolua_S,"new",tolua_game_ByteBufferException_new00);
   tolua_function(tolua_S,"new_local",tolua_game_ByteBufferException_new00_local);
   tolua_function(tolua_S,".call",tolua_game_ByteBufferException_new00_local);
   tolua_function(tolua_S,"PrintPosError",tolua_game_ByteBufferException_PrintPosError00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ByteBuffer","ByteBuffer","",tolua_collect_ByteBuffer);
  #else
  tolua_cclass(tolua_S,"ByteBuffer","ByteBuffer","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ByteBuffer");
   tolua_variable(tolua_S,"DEFAULT_SIZE",tolua_get_ByteBuffer_unsigned_DEFAULT_SIZE,NULL);
   tolua_function(tolua_S,"new",tolua_game_ByteBuffer_new00);
   tolua_function(tolua_S,"new_local",tolua_game_ByteBuffer_new00_local);
   tolua_function(tolua_S,".call",tolua_game_ByteBuffer_new00_local);
   tolua_function(tolua_S,"new",tolua_game_ByteBuffer_new01);
   tolua_function(tolua_S,"new_local",tolua_game_ByteBuffer_new01_local);
   tolua_function(tolua_S,".call",tolua_game_ByteBuffer_new01_local);
   tolua_function(tolua_S,"new",tolua_game_ByteBuffer_new02);
   tolua_function(tolua_S,"new_local",tolua_game_ByteBuffer_new02_local);
   tolua_function(tolua_S,".call",tolua_game_ByteBuffer_new02_local);
   tolua_function(tolua_S,"clear",tolua_game_ByteBuffer_clear00);
   tolua_function(tolua_S,"rpos",tolua_game_ByteBuffer_rpos00);
   tolua_function(tolua_S,"rpos",tolua_game_ByteBuffer_rpos01);
   tolua_function(tolua_S,"wpos",tolua_game_ByteBuffer_wpos00);
   tolua_function(tolua_S,"wpos",tolua_game_ByteBuffer_wpos01);
   tolua_function(tolua_S,"readPackGUID",tolua_game_ByteBuffer_readPackGUID00);
   tolua_function(tolua_S,"contents",tolua_game_ByteBuffer_contents00);
   tolua_function(tolua_S,"size",tolua_game_ByteBuffer_size00);
   tolua_function(tolua_S,"empty",tolua_game_ByteBuffer_empty00);
   tolua_function(tolua_S,"appendPackXYZ",tolua_game_ByteBuffer_appendPackXYZ00);
   tolua_function(tolua_S,"appendPackGUID",tolua_game_ByteBuffer_appendPackGUID00);
   tolua_function(tolua_S,"append",tolua_game_ByteBuffer_append00);
   tolua_function(tolua_S,"put",tolua_game_ByteBuffer_put00);
   tolua_function(tolua_S,"setU8",tolua_game_ByteBuffer_setU800);
   tolua_function(tolua_S,"getU8",tolua_game_ByteBuffer_getU800);
   tolua_function(tolua_S,"setU16",tolua_game_ByteBuffer_setU1600);
   tolua_function(tolua_S,"getU16",tolua_game_ByteBuffer_getU1600);
   tolua_function(tolua_S,"setU32",tolua_game_ByteBuffer_setU3200);
   tolua_function(tolua_S,"getU32",tolua_game_ByteBuffer_getU3200);
   tolua_function(tolua_S,"setI8",tolua_game_ByteBuffer_setI800);
   tolua_function(tolua_S,"getI8",tolua_game_ByteBuffer_getI800);
   tolua_function(tolua_S,"setI16",tolua_game_ByteBuffer_setI1600);
   tolua_function(tolua_S,"getI16",tolua_game_ByteBuffer_getI1600);
   tolua_function(tolua_S,"setI32",tolua_game_ByteBuffer_setI3200);
   tolua_function(tolua_S,"getI32",tolua_game_ByteBuffer_getI3200);
   tolua_function(tolua_S,"setFloat",tolua_game_ByteBuffer_setFloat00);
   tolua_function(tolua_S,"getFloat",tolua_game_ByteBuffer_getFloat00);
   tolua_function(tolua_S,"setStr",tolua_game_ByteBuffer_setStr00);
   tolua_function(tolua_S,"getStr",tolua_game_ByteBuffer_getStr00);
   tolua_function(tolua_S,"setU64",tolua_game_ByteBuffer_setU6400);
   tolua_function(tolua_S,"setPackGuid",tolua_game_ByteBuffer_setPackGuid00);
   tolua_function(tolua_S,"read",tolua_game_ByteBuffer_read00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"WorldPacket","WorldPacket","ByteBuffer",tolua_collect_WorldPacket);
  #else
  tolua_cclass(tolua_S,"WorldPacket","WorldPacket","ByteBuffer",NULL);
  #endif
  tolua_beginmodule(tolua_S,"WorldPacket");
   tolua_function(tolua_S,"new",tolua_game_WorldPacket_new00);
   tolua_function(tolua_S,"new_local",tolua_game_WorldPacket_new00_local);
   tolua_function(tolua_S,".call",tolua_game_WorldPacket_new00_local);
   tolua_function(tolua_S,"new",tolua_game_WorldPacket_new01);
   tolua_function(tolua_S,"new_local",tolua_game_WorldPacket_new01_local);
   tolua_function(tolua_S,".call",tolua_game_WorldPacket_new01_local);
   tolua_function(tolua_S,"new",tolua_game_WorldPacket_new02);
   tolua_function(tolua_S,"new_local",tolua_game_WorldPacket_new02_local);
   tolua_function(tolua_S,".call",tolua_game_WorldPacket_new02_local);
   tolua_function(tolua_S,"new",tolua_game_WorldPacket_new03);
   tolua_function(tolua_S,"new_local",tolua_game_WorldPacket_new03_local);
   tolua_function(tolua_S,".call",tolua_game_WorldPacket_new03_local);
   tolua_function(tolua_S,"Initialize",tolua_game_WorldPacket_Initialize00);
   tolua_function(tolua_S,"Initialize",tolua_game_WorldPacket_Initialize01);
   tolua_function(tolua_S,"GetOpcode",tolua_game_WorldPacket_GetOpcode00);
   tolua_function(tolua_S,"SetOpcode",tolua_game_WorldPacket_SetOpcode00);
   tolua_function(tolua_S,"SetGuid",tolua_game_WorldPacket_SetGuid00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"HERO_PACKET_LARGE",HERO_PACKET_LARGE);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"HeroPacketHeader","HeroPacketHeader","",tolua_collect_HeroPacketHeader);
  #else
  tolua_cclass(tolua_S,"HeroPacketHeader","HeroPacketHeader","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"HeroPacketHeader");
   tolua_variable(tolua_S,"packetLength",tolua_get_HeroPacketHeader_unsigned_packetLength,tolua_set_HeroPacketHeader_unsigned_packetLength);
   tolua_variable(tolua_S,"version",tolua_get_HeroPacketHeader_version,tolua_set_HeroPacketHeader_version);
   tolua_variable(tolua_S,"flag",tolua_get_HeroPacketHeader_flag,tolua_set_HeroPacketHeader_flag);
   tolua_variable(tolua_S,"cmd",tolua_get_HeroPacketHeader_cmd,tolua_set_HeroPacketHeader_cmd);
   tolua_function(tolua_S,"new",tolua_game_HeroPacketHeader_new00);
   tolua_function(tolua_S,"new_local",tolua_game_HeroPacketHeader_new00_local);
   tolua_function(tolua_S,".call",tolua_game_HeroPacketHeader_new00_local);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"MAX_HERO_PACKET_SIZE",MAX_HERO_PACKET_SIZE);
  tolua_constant(tolua_S,"CLIENT_RECV_BUFFER_SIZE",CLIENT_RECV_BUFFER_SIZE);
  tolua_constant(tolua_S,"CLIENT_SEND_BUFFER_SIZE",CLIENT_SEND_BUFFER_SIZE);
  tolua_function(tolua_S,"NetThreadBody",tolua_game_NetThreadBody00);
  tolua_constant(tolua_S,"NLS_LOGINSERVER",NLS_LOGINSERVER);
  tolua_constant(tolua_S,"NLS_GAMESERVER",NLS_GAMESERVER);
  tolua_cclass(tolua_S,"CNetConnection","CNetConnection","",NULL);
  tolua_beginmodule(tolua_S,"CNetConnection");
   tolua_function(tolua_S,"Instance",tolua_game_CNetConnection_Instance00);
   tolua_function(tolua_S,"IsConnected",tolua_game_CNetConnection_IsConnected00);
   tolua_function(tolua_S,"CloseSocket",tolua_game_CNetConnection_CloseSocket00);
   tolua_function(tolua_S,"IsAuthed",tolua_game_CNetConnection_IsAuthed00);
   tolua_function(tolua_S,"ConnectLoginServer",tolua_game_CNetConnection_ConnectLoginServer00);
   tolua_function(tolua_S,"ConnectGameServer",tolua_game_CNetConnection_ConnectGameServer00);
   tolua_function(tolua_S,"DisConnect",tolua_game_CNetConnection_DisConnect00);
   tolua_function(tolua_S,"Update",tolua_game_CNetConnection_Update00);
   tolua_function(tolua_S,"SendPacket",tolua_game_CNetConnection_SendPacket00);
   tolua_function(tolua_S,"OnRecv",tolua_game_CNetConnection_OnRecv00);
   tolua_function(tolua_S,"FlushData",tolua_game_CNetConnection_FlushData00);
   tolua_function(tolua_S,"OnFirstChallenge",tolua_game_CNetConnection_OnFirstChallenge00);
   tolua_function(tolua_S,"GetConnectType",tolua_game_CNetConnection_GetConnectType00);
   tolua_function(tolua_S,"SetConnectType",tolua_game_CNetConnection_SetConnectType00);
   tolua_function(tolua_S,"SetPingCode",tolua_game_CNetConnection_SetPingCode00);
   tolua_function(tolua_S,"OnSendPing",tolua_game_CNetConnection_OnSendPing00);
   tolua_function(tolua_S,"OnRecvPong",tolua_game_CNetConnection_OnRecvPong00);
   tolua_function(tolua_S,"GetAvgPing",tolua_game_CNetConnection_GetAvgPing00);
   tolua_function(tolua_S,"ClearPingStatistics",tolua_game_CNetConnection_ClearPingStatistics00);
   tolua_function(tolua_S,"setVersion",tolua_game_CNetConnection_setVersion00);
   tolua_function(tolua_S,"getClientMd5",tolua_game_CNetConnection_getClientMd500);
   tolua_function(tolua_S,"getClientSeed",tolua_game_CNetConnection_getClientSeed00);
   tolua_function(tolua_S,"getUserName",tolua_game_CNetConnection_getUserName00);
   tolua_function(tolua_S,"SetUserNameAndPassWord",tolua_game_CNetConnection_SetUserNameAndPassWord00);
   tolua_function(tolua_S,"GetClientMd5Str",tolua_game_CNetConnection_GetClientMd5Str00);
   tolua_function(tolua_S,"SendLoginPacket",tolua_game_CNetConnection_SendLoginPacket00);
   tolua_function(tolua_S,"SendSignInPacket",tolua_game_CNetConnection_SendSignInPacket00);
   tolua_function(tolua_S,"ConnectFailed",tolua_game_CNetConnection_ConnectFailed00);
   tolua_function(tolua_S,"Next",tolua_game_CNetConnection_Next00);
   tolua_function(tolua_S,"ReleasePacket",tolua_game_CNetConnection_ReleasePacket00);
   tolua_function(tolua_S,"GetPacket",tolua_game_CNetConnection_GetPacket00);
   tolua_function(tolua_S,"IsLoginState",tolua_game_CNetConnection_IsLoginState00);
   tolua_function(tolua_S,"setLoginState",tolua_game_CNetConnection_setLoginState00);
   tolua_function(tolua_S,"HandleNull",tolua_game_CNetConnection_HandleNull00);
   tolua_function(tolua_S,"HandleClientSide",tolua_game_CNetConnection_HandleClientSide00);
   tolua_function(tolua_S,"HandleLoginRealmListResponse",tolua_game_CNetConnection_HandleLoginRealmListResponse00);
   tolua_function(tolua_S,"HandleGameAuthChallengeResponse",tolua_game_CNetConnection_HandleGameAuthChallengeResponse00);
   tolua_function(tolua_S,"sendAuthSessionMessage",tolua_game_CNetConnection_sendAuthSessionMessage00);
   tolua_function(tolua_S,"registerScriptFunc",tolua_game_CNetConnection_registerScriptFunc00);
   tolua_function(tolua_S,"unregisterScriptHandler",tolua_game_CNetConnection_unregisterScriptHandler00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"IAP_EVENT_QUERY_FINISH",IAP_EVENT_QUERY_FINISH);
  tolua_constant(tolua_S,"IAP_EVENT_PURCHASE_FINISH",IAP_EVENT_PURCHASE_FINISH);
  tolua_constant(tolua_S,"IAP_EVENT_PURCHASE_FAILED",IAP_EVENT_PURCHASE_FAILED);
  tolua_cclass(tolua_S,"ProductInfo","ProductInfo","",NULL);
  tolua_beginmodule(tolua_S,"ProductInfo");
   tolua_variable(tolua_S,"productId",tolua_get_ProductInfo_productId,tolua_set_ProductInfo_productId);
   tolua_variable(tolua_S,"price",tolua_get_ProductInfo_price,tolua_set_ProductInfo_price);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"InAppPurchaseDelegate","InAppPurchaseDelegate","",tolua_collect_InAppPurchaseDelegate);
  #else
  tolua_cclass(tolua_S,"InAppPurchaseDelegate","InAppPurchaseDelegate","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"InAppPurchaseDelegate");
   tolua_function(tolua_S,"new",tolua_game_InAppPurchaseDelegate_new00);
   tolua_function(tolua_S,"new_local",tolua_game_InAppPurchaseDelegate_new00_local);
   tolua_function(tolua_S,".call",tolua_game_InAppPurchaseDelegate_new00_local);
   tolua_function(tolua_S,"delete",tolua_game_InAppPurchaseDelegate_delete00);
   tolua_function(tolua_S,"addProduct",tolua_game_InAppPurchaseDelegate_addProduct00);
   tolua_function(tolua_S,"queryProducts",tolua_game_InAppPurchaseDelegate_queryProducts00);
   tolua_function(tolua_S,"purchase",tolua_game_InAppPurchaseDelegate_purchase00);
   tolua_function(tolua_S,"getPrice",tolua_game_InAppPurchaseDelegate_getPrice00);
   tolua_function(tolua_S,"queryProductFinish",tolua_game_InAppPurchaseDelegate_queryProductFinish00);
   tolua_function(tolua_S,"onQueryProductFinish",tolua_game_InAppPurchaseDelegate_onQueryProductFinish00);
   tolua_function(tolua_S,"onPurchaseFinish",tolua_game_InAppPurchaseDelegate_onPurchaseFinish00);
   tolua_function(tolua_S,"onPurchaseFailed",tolua_game_InAppPurchaseDelegate_onPurchaseFailed00);
   tolua_function(tolua_S,"registerScriptHandler",tolua_game_InAppPurchaseDelegate_registerScriptHandler00);
   tolua_function(tolua_S,"unregisterScriptHandler",tolua_game_InAppPurchaseDelegate_unregisterScriptHandler00);
   tolua_function(tolua_S,"clearProduct",tolua_game_InAppPurchaseDelegate_clearProduct00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"InAppPurchaseInterface","InAppPurchaseInterface","",NULL);
  tolua_beginmodule(tolua_S,"InAppPurchaseInterface");
   tolua_function(tolua_S,"initStore",tolua_game_InAppPurchaseInterface_initStore00);
   tolua_function(tolua_S,"canMakePurchases",tolua_game_InAppPurchaseInterface_canMakePurchases00);
   tolua_function(tolua_S,"queryProductInfo",tolua_game_InAppPurchaseInterface_queryProductInfo00);
   tolua_function(tolua_S,"onQueryProductBack",tolua_game_InAppPurchaseInterface_onQueryProductBack00);
   tolua_function(tolua_S,"onQueryProductFinish",tolua_game_InAppPurchaseInterface_onQueryProductFinish00);
   tolua_function(tolua_S,"makePurchase",tolua_game_InAppPurchaseInterface_makePurchase00);
   tolua_function(tolua_S,"onPurchaseFinish",tolua_game_InAppPurchaseInterface_onPurchaseFinish00);
   tolua_function(tolua_S,"onPurchaseFailed",tolua_game_InAppPurchaseInterface_onPurchaseFailed00);
   tolua_variable(tolua_S,"hasInit",tolua_get_InAppPurchaseInterface_hasInit,tolua_set_InAppPurchaseInterface_hasInit);
   tolua_variable(tolua_S,"_delegate",tolua_get_InAppPurchaseInterface__delegate_ptr,tolua_set_InAppPurchaseInterface__delegate_ptr);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PlatformUtility","PlatformUtility","",NULL);
  tolua_beginmodule(tolua_S,"PlatformUtility");
   tolua_function(tolua_S,"OpenRate",tolua_game_PlatformUtility_OpenRate00);
   tolua_function(tolua_S,"OpenFullLink",tolua_game_PlatformUtility_OpenFullLink00);
   tolua_function(tolua_S,"IsNetUseable",tolua_game_PlatformUtility_IsNetUseable00);
   tolua_function(tolua_S,"GetDeviceMacAddress",tolua_game_PlatformUtility_GetDeviceMacAddress00);
   tolua_function(tolua_S,"SetLockScreen",tolua_game_PlatformUtility_SetLockScreen00);
   tolua_function(tolua_S,"IsTheseProcessRunning",tolua_game_PlatformUtility_IsTheseProcessRunning00);
   tolua_function(tolua_S,"GetPhysicalMemory",tolua_game_PlatformUtility_GetPhysicalMemory00);
   tolua_function(tolua_S,"GetSystemUptime",tolua_game_PlatformUtility_GetSystemUptime00);
   tolua_function(tolua_S,"GetKeychain",tolua_game_PlatformUtility_GetKeychain00);
   tolua_function(tolua_S,"getAnonymAccount",tolua_game_PlatformUtility_getAnonymAccount00);
   tolua_function(tolua_S,"getAccount",tolua_game_PlatformUtility_getAccount00);
   tolua_function(tolua_S,"getPassword",tolua_game_PlatformUtility_getPassword00);
   tolua_function(tolua_S,"setAnonymAccount",tolua_game_PlatformUtility_setAnonymAccount00);
   tolua_function(tolua_S,"setAccount",tolua_game_PlatformUtility_setAccount00);
   tolua_function(tolua_S,"setPassword",tolua_game_PlatformUtility_setPassword00);
   tolua_function(tolua_S,"SaveMacToKeychain",tolua_game_PlatformUtility_SaveMacToKeychain00);
   tolua_function(tolua_S,"GetDeviceIfa",tolua_game_PlatformUtility_GetDeviceIfa00);
   tolua_function(tolua_S,"CallTrackingIFA",tolua_game_PlatformUtility_CallTrackingIFA00);
   tolua_function(tolua_S,"GetDeviceIdentify",tolua_game_PlatformUtility_GetDeviceIdentify00);
   tolua_function(tolua_S,"initTapjoy",tolua_game_PlatformUtility_initTapjoy00);
   tolua_function(tolua_S,"initLimeiCPC",tolua_game_PlatformUtility_initLimeiCPC00);
   tolua_function(tolua_S,"showiAd",tolua_game_PlatformUtility_showiAd00);
   tolua_function(tolua_S,"getDeviceValue",tolua_game_PlatformUtility_getDeviceValue00);
   tolua_function(tolua_S,"setDeviceValue",tolua_game_PlatformUtility_setDeviceValue00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"FileIO","FileIO","CCObject",NULL);
  tolua_beginmodule(tolua_S,"FileIO");
   tolua_function(tolua_S,"create",tolua_game_FileIO_create00);
   tolua_function(tolua_S,"init",tolua_game_FileIO_init00);
   tolua_function(tolua_S,"getFileData",tolua_game_FileIO_getFileData00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCScriptAction","CCScriptAction","CCActionInterval",NULL);
  tolua_beginmodule(tolua_S,"CCScriptAction");
   tolua_function(tolua_S,"create",tolua_game_CCScriptAction_create00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_game (lua_State* tolua_S) {
 return tolua_game_open(tolua_S);
};
#endif

