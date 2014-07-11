#include "CCShaderSprite.h"

CCShaderSprite* CCShaderSprite::create(const char* glslFile)
{
	CCShaderSprite* pobSprite = new CCShaderSprite();
	if (pobSprite && pobSprite->init() && pobSprite->initShader(glslFile))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCShaderSprite* CCShaderSprite::create(const char *pszFileName,const char* glslFile)
{
	CCShaderSprite *pobSprite = new CCShaderSprite();
	if (pobSprite && pobSprite->initWithFile(pszFileName) && pobSprite->initShader(glslFile))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

CCShaderSprite::CCShaderSprite()
{
	shader = NULL;
}

CCShaderSprite::~CCShaderSprite()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, EVENT_COME_TO_FOREGROUND);
}

bool CCShaderSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect, bool rotated)
{
	if(CCSprite::initWithTexture(pTexture,rect,rotated))
	{
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
			callfuncO_selector(CCShaderSprite::listenBackToForeground),
			EVENT_COME_TO_FOREGROUND,
			NULL);

		return true;
	}
	return false;
}

void CCShaderSprite::setTexture(CCTexture2D *texture)
{
	// If batchnode, then texture id should be the same
	CCAssert(! m_pobBatchNode || texture->getName() == m_pobBatchNode->getTexture()->getName(), "CCSprite: Batched sprites should use the same texture as the batchnode");
	// accept texture==nil as argument
	CCAssert( !texture || dynamic_cast<CCTexture2D*>(texture), "setTexture expects a CCTexture2D. Invalid argument");

	// shader program
	if (texture && shader)
	{
		setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(shader));
	}
	else
	{
		setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
	}

	if (!m_pobBatchNode && m_pobTexture != texture)
	{
		CC_SAFE_RETAIN(texture);
		CC_SAFE_RELEASE(m_pobTexture);
		m_pobTexture = texture;
		updateBlendFunc();
	}
}

void CCShaderSprite::listenBackToForeground(CCObject *obj)
{
	setShaderProgram(NULL);
	initShader(shader);
}

bool CCShaderSprite::initShader(const char* glslFile)
{
	if(glslFile == NULL) return false;
	CCGLProgram* pProgram = CCShaderCache::sharedShaderCache()->programForKey(glslFile);
	if(pProgram == NULL)
	{
		GLchar * fragSource = (GLchar*) CCString::createWithContentsOfFile(
			CCFileUtils::sharedFileUtils()->fullPathForFilename(glslFile).c_str())->getCString();
		pProgram = new CCGLProgram();
		pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSource);
		CCShaderCache::sharedShaderCache()->addProgram(pProgram,glslFile);
		setShaderProgram(pProgram);
		pProgram->release();
		CHECK_GL_ERROR_DEBUG();

		getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
		getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
		getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
		CHECK_GL_ERROR_DEBUG();

		getShaderProgram()->link();
		CHECK_GL_ERROR_DEBUG();

		getShaderProgram()->updateUniforms();
		CHECK_GL_ERROR_DEBUG();
	}
	else
		setShaderProgram(pProgram);

	linkLocation();
	shader = glslFile;
	return true;
}

void CCShaderSprite::linkLocation()
{
	if(getScriptHandler()&&m_eScriptType!= kScriptTypeNone)
	{
		CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(getScriptHandler(),"linkLocation",this,"CCShaderSprite");
	}
}

GLuint CCShaderSprite::link(const char* name)
{
	CCAssert(getShaderProgram(),"ShaderSprite must be linking after setShaderProgram successful!");
	if(getShaderProgram())
	{
		GLuint location = glGetUniformLocation(getShaderProgram()->getProgram(),name);
		return location;
	}
	return -1;
}

void CCShaderSprite::setupLocation()
{
	if(getScriptHandler()&&m_eScriptType!= kScriptTypeNone)
	{
		CCScriptEngineManager::sharedManager()->getScriptEngine()->executeEvent(getScriptHandler(),"setupLocation",this,"CCShaderSprite");
	}
}


void CCShaderSprite::draw()
{
	CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCShaderSprite - draw");

	CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");

	CC_NODE_DRAW_SETUP();

	setupLocation();

	ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );

	ccGLBindTexture2D( m_pobTexture->getName() );
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );

#define kQuadSize sizeof(m_sQuad.bl)
#ifdef EMSCRIPTEN
	long offset = 0;
	setGLBufferData(&m_sQuad, 4 * kQuadSize, 0);
#else
	long offset = (long)&m_sQuad;
#endif // EMSCRIPTEN

	// vertex
	int diff = offsetof( ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

	if (m_pobTexture != NULL)
	{
		// texCoods
		diff = offsetof( ccV3F_C4B_T2F, texCoords);
		glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
	}

	// color
	diff = offsetof( ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));


	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	CHECK_GL_ERROR_DEBUG();


#if CC_SPRITE_DEBUG_DRAW == 1
	// draw bounding box
	CCPoint vertices[4]={
		ccp(m_sQuad.tl.vertices.x,m_sQuad.tl.vertices.y),
		ccp(m_sQuad.bl.vertices.x,m_sQuad.bl.vertices.y),
		ccp(m_sQuad.br.vertices.x,m_sQuad.br.vertices.y),
		ccp(m_sQuad.tr.vertices.x,m_sQuad.tr.vertices.y),
	};
	ccDrawPoly(vertices, 4, true);
#elif CC_SPRITE_DEBUG_DRAW == 2
	// draw texture box
	CCSize s = this->getTextureRect().size;
	CCPoint offsetPix = this->getOffsetPosition();
	CCPoint vertices[4] = {
		ccp(offsetPix.x,offsetPix.y), ccp(offsetPix.x+s.width,offsetPix.y),
		ccp(offsetPix.x+s.width,offsetPix.y+s.height), ccp(offsetPix.x,offsetPix.y+s.height)
	};
	ccDrawPoly(vertices, 4, true);
#endif // CC_SPRITE_DEBUG_DRAW

	CC_INCREMENT_GL_DRAWS(1);

	CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCShaderSprite - draw");

	//drawBound();
}

void CCShaderSprite::set1i(GLint location,GLint i1)
{
	CCAssert(getShaderProgram(),"setUniformLocation must be getShaderProgram is not NULL");
	getShaderProgram()->setUniformLocationWith1i(location,i1);
}

void CCShaderSprite::set2i(GLint location, GLint i1, GLint i2)
{
	CCAssert(getShaderProgram(),"setUniformLocation must be getShaderProgram is not NULL");
	getShaderProgram()->setUniformLocationWith2i(location,i1,i2);
}

void CCShaderSprite::set3i(GLint location, GLint i1, GLint i2, GLint i3)
{
	CCAssert(getShaderProgram(),"setUniformLocation must be getShaderProgram is not NULL");
	getShaderProgram()->setUniformLocationWith3i(location,i1,i2,i3);
}

void CCShaderSprite::set4i(GLint location, GLint i1, GLint i2, GLint i3, GLint i4)
{
	CCAssert(getShaderProgram(),"setUniformLocation must be getShaderProgram is not NULL");
	getShaderProgram()->setUniformLocationWith4i(location,i1,i2,i3,i4);
}

void CCShaderSprite::set1f(GLint location, GLfloat f1)
{
	CCAssert(getShaderProgram(),"setUniformLocation must be getShaderProgram is not NULL");
	getShaderProgram()->setUniformLocationWith1f(location,f1);
}

void CCShaderSprite::set2f(GLint location, GLfloat f1, GLfloat f2)
{
	CCAssert(getShaderProgram(),"setUniformLocation must be getShaderProgram is not NULL");
	getShaderProgram()->setUniformLocationWith2f(location,f1,f2);
}

void CCShaderSprite::set3f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3)
{
	CCAssert(getShaderProgram(),"setUniformLocation must be getShaderProgram is not NULL");
	getShaderProgram()->setUniformLocationWith3f(location,f1,f2,f3);
}

void CCShaderSprite::set4f(GLint location, GLfloat f1, GLfloat f2, GLfloat f3, GLfloat f4)
{
	CCAssert(getShaderProgram(),"setUniformLocation must be getShaderProgram is not NULL");
	getShaderProgram()->setUniformLocationWith4f(location,f1,f2,f3,f4);
}