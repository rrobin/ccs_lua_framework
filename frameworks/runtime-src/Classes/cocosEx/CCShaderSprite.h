#pragma once
#include "cocos2d.h"
USING_NS_CC;

class CCShaderSprite : public Sprite
{
public:
	CREATE_FUNC(CCShaderSprite);
	static CCShaderSprite* create(const char* glslFile);
	static CCShaderSprite* create(const char *pszFileName,const char* glslFile);
	CCShaderSprite();
	virtual ~CCShaderSprite();

	virtual bool initWithTexture(Texture2D *pTexture, const CCRect& rect, bool rotated);
	virtual void setTexture(Texture2D *texture);
	virtual void draw();

	virtual void listenBackToForeground(CCObject *obj);
	bool		 initShader(const char* glslFile);
	virtual GLuint link(const char* name);

	virtual void linkLocationC(){ linkLocation(); }

	virtual void set1i(GLint location,GLint i1);
	virtual void set2i(GLint location, GLint i1, GLint i2);
	virtual void set3i(GLint location, GLint i1, GLint i2, GLint i3);
	virtual void set4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4);
	virtual void set1f(GLint location, GLfloat f1);
	virtual void set2f(GLint location, GLfloat f1, GLfloat f2);
	virtual void set3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3);
	virtual void set4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4);

protected:
	virtual void linkLocation();
	virtual void setupLocation();
private:
	const char*		shader;
	
};