#include "GLabelTTF/GLabelTTF.h"
#include <string>
#include <ctype.h>
#include "Util.h"

#include "jni/JniHelper.h"

#include <android/log.h>
#include <string.h>
#include <jni.h>

// prototype
void my_swapAlphaChannel(unsigned int *pImageMemory, unsigned int numPixels);

static CCBMFontConfiguration* lpBMFontConfiguration_s = NULL;
static CCBMFontConfiguration* lpBMFontConfiguration_m = NULL;
static CCBMFontConfiguration* lpBMFontConfiguration_l = NULL;
static CCBMFontConfiguration* lpBMFontConfiguration_xl = NULL;

const char* s_BMF_S	= "fonts/soopafre_s.fnt";
const char* s_BMF_M	= "fonts/soopafre_m.fnt";
const char* s_BMF_L	= "fonts/soopafre_l.fnt";
const char* s_BMF_LX= "fonts/soopafre_lx.fnt";

class my_BitmapDC
{
public:

	my_BitmapDC()
    : m_pData(NULL)
    , m_nWidth(0)
    , m_nHeight(0)
    {
    }

    ~my_BitmapDC(void)
    {
        if (m_pData)
        {
            delete [] m_pData;
        }
    }

    bool getBitmapFromJavaShadowStroke(	const char *text,
    									int nWidth,
    									int nHeight,
    									CCImage::ETextAlign eAlignMask,
    									const char * pFontName,
    									float fontSize,
    									float textTintR 		= 1.0,
    									float textTintG 		= 1.0,
    									float textTintB 		= 1.0,
    									bool shadow 			= false,
    									float shadowDeltaX 		= 0.0,
    									float shadowDeltaY 		= 0.0,
    									float shadowBlur 		= 0.0,
    									float shadowIntensity 	= 0.0,
    									bool stroke 			= false,
    									float strokeColorR 		= 0.0,
    									float strokeColorG 		= 0.0,
    									float strokeColorB 		= 0.0,
    									float strokeSize 		= 0.0 )
    {
           JniMethodInfo methodInfo;
           if (! JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/lib/Cocos2dxBitmap", "createTextBitmapShadowStroke",
               "(Ljava/lang/String;Ljava/lang/String;IFFFIIIZFFFZFFFF)V"))
           {
               CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
               return false;
           }



           // Do a full lookup for the font path using CCFileUtils in case the given font name is a relative path to a font file asset,
           // or the path has been mapped to a different location in the app package:
           std::string fullPathOrFontName = CCFileUtils::sharedFileUtils()->fullPathForFilename(pFontName);

		   // If the path name returned includes the 'assets' dir then that needs to be removed, because the android.content.Context
		   // requires this portion of the path to be omitted for assets inside the app package.
		   if (fullPathOrFontName.find("assets/") == 0)
		   {
               fullPathOrFontName = fullPathOrFontName.substr(strlen("assets/"));	// Chop out the 'assets/' portion of the path.
           }

           /**create bitmap
            * this method call Cococs2dx.createBitmap()(java code) to create the bitmap, the java code
            * will call Java_org_cocos2dx_lib_Cocos2dxBitmap_nativeInitBitmapDC() to init the width, height
            * and data.
            * use this approach to decrease the jni call number
           */
           jstring jstrText = methodInfo.env->NewStringUTF(text);
           jstring jstrFont = methodInfo.env->NewStringUTF(fullPathOrFontName.c_str());

           methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jstrText,
               jstrFont, (int)fontSize, textTintR, textTintG, textTintB, eAlignMask, nWidth, nHeight, shadow, shadowDeltaX, -shadowDeltaY, shadowBlur, stroke, strokeColorR, strokeColorG, strokeColorB, strokeSize);

           methodInfo.env->DeleteLocalRef(jstrText);
           methodInfo.env->DeleteLocalRef(jstrFont);
           methodInfo.env->DeleteLocalRef(methodInfo.classID);

           return true;
    }


    bool getBitmapFromJava(const char *text, int nWidth, int nHeight, CCImage::ETextAlign eAlignMask, const char * pFontName, float fontSize)
    {
    	return  getBitmapFromJavaShadowStroke(	text, nWidth, nHeight, eAlignMask, pFontName, fontSize );
    }

    // ARGB -> RGBA
    inline unsigned int swapAlpha(unsigned int value)
    {
        return ((value << 8 & 0xffffff00) | (value >> 24 & 0x000000ff));
    }

public:
    int m_nWidth;
    int m_nHeight;
    unsigned char *m_pData;
    JNIEnv *env;
};

static my_BitmapDC& sharedBitmapDC()
{
    static my_BitmapDC s_BmpDC;
    return s_BmpDC;
}

GLabelTTF::GLabelTTF()
	:m_xmlStringParse( NULL )
	,m_lineCounts( 1 )
{

}

GLabelTTF::~GLabelTTF()
{
	CCLog( "GLabelTTF Release!" );
	CC_SAFE_DELETE( m_xmlStringParse );
}


GLabelTTF * GLabelTTF::create(const char *string, GameLabelType type, const char *fontName, float fontSize, float lineSpace)
{
	GLabelTTF* pRet = new GLabelTTF;
	if(pRet && pRet->initWithString(string,type,fontName,fontSize,lineSpace))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}
    
 
GLabelTTF * GLabelTTF::create(const char *string, GameLabelType type, const char *fontName, float fontSize, float lineSpace, CCSize dimensions, int hAlignment)
{
	GLabelTTF* pRet = new GLabelTTF;
	if(pRet && pRet->initWithString(string,type,fontName,fontSize,lineSpace,dimensions,hAlignment))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

GLabelTTF * GLabelTTF::create(const char *string, GameLabelType type, const char *fontName, float fontSize, float lineSpace, CCSize dimensions, int hAlignment, int vAlignment)
{
	GLabelTTF* pRet = new GLabelTTF;
	if(pRet && pRet->initWithString(string,type,fontName,fontSize,lineSpace,dimensions,hAlignment,vAlignment))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool GLabelTTF::initWithString(const char *string, GameLabelType type, const char *fontName, float fontSize, float lineSpace)
{
	return initWithString(string,type,fontName,fontSize,lineSpace,CCSizeZero,kCCTextAlignmentLeft);
}
    
bool GLabelTTF::initWithString(const char *string, GameLabelType type, const char *fontName, float fontSize, float lineSpace,CCSize dimensions, int hAlignment)
{
	return initWithString(string,type,fontName,fontSize,lineSpace,dimensions,hAlignment,kCCVerticalTextAlignmentTop);
}
   
bool GLabelTTF::initWithString(const char *string, GameLabelType type, const char *fontName, float fontSize, float lineSpace,CCSize dimensions, int hAlignment, int vAlignment)
{
	m_spaceline = lineSpace;

	m_xmlStringParse = new XMLStringParser( string );
	if ( !m_xmlStringParse )
	{
		assert( false );
		return false;
	}

	std::vector<LabelTTFColorSizeInfo>& ttfVec = m_xmlStringParse->getColorSizeInfoVec();

	std::string totalString;
	for ( size_t i = 0; i < ttfVec.size(); ++i )
		totalString += ttfVec[i].str;

	_calcMultiLabel(string,type,fontName,fontSize,dimensions,(CCTextAlignment)hAlignment,(CCVerticalTextAlignment)vAlignment);

	return true;
}

void GLabelTTF::_calcMultiLabel(const char* str,GameLabelType type,const char *fontName, float fontSize, const CCSize& dimensions, CCTextAlignment hAlignment, CCVerticalTextAlignment vAlignment)
{
	if ( !m_xmlStringParse )
	{
		assert( false );
		return ;
	}

	if ( type == GLabel_BMF )
	{
		lpBMFontConfiguration_s = CCBMFontConfiguration::create( s_BMF_S );
		lpBMFontConfiguration_m = CCBMFontConfiguration::create( s_BMF_M );
		lpBMFontConfiguration_l = CCBMFontConfiguration::create( s_BMF_L );
		lpBMFontConfiguration_xl = CCBMFontConfiguration::create( s_BMF_LX );
	}

	bool bPreWrap = false;
	int preWidthTTF = 0;
	float preWidthBMF = 0.0f;
	std::vector<LabelTTFColorSizeInfo>& info = m_xmlStringParse->getColorSizeInfoVec();
	for ( size_t i = 0; i < info.size(); ++i )
	{
		if ( type == GLabel_TTF )
		{
			if ( info[i].str != "" )
				divideOneStringAndroid( info[i], fontName, dimensions, bPreWrap, preWidthTTF );
			else
				assert( false );
		}
		else if ( type == GLabel_BMF )
		{
			if ( info[i].str != "" )
			{
				const char * fontNameBMF = getFontName( info[i].sizeMode );
				divideOneString( info[i], fontNameBMF, dimensions, bPreWrap, preWidthBMF );
			}
			else
				assert( false );
		}
		bPreWrap = info[i].wrap;

	}

	// 创建Label
	std::map< uint32, std::vector< CCNode* > > labelMap;	// 以行号为key
	std::map< uint32, CCSize > labelSize;					// 以行号为key, value 为字符总长度

	for ( divideStringInfoMapIter iter = m_DivideStringInfoMap.begin(); iter != m_DivideStringInfoMap.end(); ++ iter )
	{
		std::vector< CCNode* > labelVec;
		CCSize lineSize;
		CellStringInfoVec& info = iter->second;
		for ( CellStringInfoVec::iterator it = info.begin(); it != info.end(); ++it )
		{
			CCNode* node = NULL;
			if ( type == GLabel_TTF )
			{
				if ( it->str != "" )
				{
					GameLabel* ttf = GameLabel::create( it->str.c_str(), type, fontName, getFontSize( it->fontMode ), CCSizeZero, hAlignment, vAlignment,getFontStroke(it->fontMode) );
					ttf->setColor( it->color );
					ttf->setOpacity( it->alpha );

					node = ttf;
				}
				else if ( it->iconPath != "" )
				{
					node = CCSprite::create( it->iconPath.c_str() );
					//node->setAnchorPoint( CCPointZero );
				}
// 				else
// 					assert( false );
			}
			else if ( type == GLabel_BMF )
			{
				if ( it->str != "" )
				{
					const char * fontNameBMF = getFontName( it->fontMode );
					GameLabel* ttf = GameLabel::create( it->str.c_str(), type, fontNameBMF, getFontSize( it->fontMode ), CCSizeZero, hAlignment, vAlignment,getFontStroke(it->fontMode) );
					ttf->setColor( it->color );
					ttf->setOpacity( it->alpha );

					node = ttf;
				}
				else if ( it->iconPath != "" )
				{
					node = CCSprite::create( it->iconPath.c_str() );
					//node->setAnchorPoint( CCPointZero );
				}
// 				else
// 					assert( false );
			}
			if ( node )
			{
				lineSize.width += node->getContentSize().width;
			
				if ( node->getContentSize().height > lineSize.height )
				lineSize.height = node->getContentSize().height;

				labelVec.push_back( node );
			}
			labelSize[iter->first] = lineSize;
		}

		labelMap[iter->first] = labelVec ;
	}

	// 计算总体大小
	float totalHeight = 0.0f;
	for ( std::map< uint32, CCSize >::iterator iter = labelSize.begin(); iter != labelSize.end(); ++iter )
	{
		totalHeight += ( iter->second.height + (float)m_spaceline );
	}
	CCSize size = CCSizeMake( dimensions.width, totalHeight );
	setContentSize( size );

	// 下面是设置位置,对齐方式
	for ( std::map< uint32, std::vector< CCNode* > >::iterator iter = labelMap.begin(); iter != labelMap.end(); ++iter )
	{
		std::vector< CCNode* >& labelVec = iter->second;

		float beginPos = 0.0f;

		switch ( hAlignment )
		{
		case kCCTextAlignmentLeft:
			// 默认是左对齐的, 什么事都不用做了
			break;
		case kCCTextAlignmentCenter:
			beginPos = ( dimensions.width - labelSize[iter->first].width )/2;
			break;
		case kCCTextAlignmentRight:
			beginPos = dimensions.width - labelSize[iter->first].width;
			break;
		default:
			assert( false );
			break;
		}

		for ( std::vector< CCNode* >::iterator it = labelVec.begin(); it != labelVec.end(); ++it  )
		{
			CCNode* node = *it;
			addChild( node, 0 );
			node->setPosition( ccp( beginPos + node->getContentSize().width/2 , totalHeight - labelSize[iter->first].height + node->getContentSize().height/2 ) );

			switch ( vAlignment )
			{
			case kCCVerticalTextAlignmentTop:
				node->setPosition( ccp( beginPos + node->getContentSize().width/2 , totalHeight - node->getContentSize().height/2 ) );
				break;
			case kCCVerticalTextAlignmentCenter:
				node->setPosition( ccp( beginPos + node->getContentSize().width/2 , totalHeight - labelSize[iter->first].height/2 ) );
				break;
			case kCCVerticalTextAlignmentBottom:
				node->setPosition( ccp( beginPos + node->getContentSize().width/2 , totalHeight - labelSize[iter->first].height + node->getContentSize().height/2 ) );
				break;
			default:
				assert( false );
				break;
			}
			beginPos += node->getContentSize().width;
		}

		totalHeight -= ( labelSize[iter->first].height + m_spaceline );
		beginPos = 0.0f;
	}
}

void GLabelTTF::divideOneString( const LabelTTFColorSizeInfo& info, const char* fontName, const CCSize& dimensions, bool isPreWrap, long& preLineWidth )
{
	
}

void GLabelTTF::divideOneStringIOS( const LabelTTFColorSizeInfo& info, const char* fontName, const CCSize& dimensions, bool isPreWrap, float& preLineWidth )
{

}

void GLabelTTF::divideOneStringAndroid( const LabelTTFColorSizeInfo& info, const char* fontName, const CCSize& dimensions, bool isPreWrap, int& preLineWidth )
{
	wstring wstrTemp;
	Utf8toWStr( info.str, wstrTemp );
	int nLen = wstrTemp.size();

	if ( nLen <= 0 )
		return;

	std::vector<wstring> mutliLine;

	if ( isPreWrap )
	{
		m_lineCounts += 1;
		preLineWidth = 0;
	}

	int totalWidth = preLineWidth;
	int line = 0;
	int i = 0;
	for(; i < nLen; ++i)
	{
		bool breakLine = false;

		if ( wstrTemp.at( i ) == '\n' )
		{
			breakLine = true;
		}
		else
		{
			wstring subStr = wstrTemp.substr( line, i - line + 1 );
			string utf8Str;
			WStrToUtf8( subStr, utf8Str );

			int nWidth = 0;
			int nHeight = 0;
			my_BitmapDC &dc = sharedBitmapDC();
			CC_BREAK_IF( !dc.getBitmapFromJava( utf8Str.c_str(), nWidth, nHeight, CCImage::kAlignLeft, fontName, getFontSize( info.sizeMode ) ) );

			totalWidth = preLineWidth + nWidth;

			if( ( totalWidth > (int)dimensions.width ) || breakLine )
			{
				wstring subString = wstrTemp.substr( line, i - line + 1 );
				mutliLine.push_back( subString );

				if ( breakLine )
					line = i + 1;
				else
					line = i;

				preLineWidth = 0;
				totalWidth = 0;
			}
		}
	}
	preLineWidth = totalWidth;
	if ( line < nLen )
	{
		wstring subString = wstrTemp.substr( line, nLen - line );
		mutliLine.push_back( subString );
	}


	for( size_t idx = 0; idx < mutliLine.size(); ++idx )
	{
		if ( idx != 0 )
			++m_lineCounts;

		// Utf16ToUtf8
		std::string utf8str = "";
		WStrToUtf8(mutliLine[idx],utf8str);

		CellStringInfo cellStringInfo;
		cellStringInfo.str = utf8str;
		cellStringInfo.fontMode = info.sizeMode;
		cellStringInfo.color = info.color;
		cellStringInfo.alpha = info.alpha;

		divideStringInfoMapIter iter = m_DivideStringInfoMap.find( m_lineCounts );
		if ( iter != m_DivideStringInfoMap.end() )
			iter->second.push_back( cellStringInfo );
		else
		{
			CellStringInfoVec cellStringInfoVec;
			cellStringInfoVec.push_back( cellStringInfo );
			m_DivideStringInfoMap[m_lineCounts] = cellStringInfoVec;
		}
	}
	mutliLine.clear();
}

void GLabelTTF::divideOneString( const LabelTTFColorSizeInfo& info, const char* fontName, const CCSize& dimensions, bool isPreWrap, float& preLineWidth )
{
	//CCBMFontConfiguration* lpBMFontConfiguration = CCBMFontConfiguration::create( fontName );
	CCBMFontConfiguration* lpBMFontConfiguration = NULL;
	switch ( info.sizeMode )
	{
	case 1:
		lpBMFontConfiguration = lpBMFontConfiguration_s;
		break;
	case 2:
		lpBMFontConfiguration = lpBMFontConfiguration_m;
		break;
	case 3:
		lpBMFontConfiguration = lpBMFontConfiguration_l;
		break;
	case 4:
		lpBMFontConfiguration = lpBMFontConfiguration_xl;
		break;
	default:
		assert( false );
		break;
	}
	
	if ( !lpBMFontConfiguration )
	{
		CCLog( "Can not find the font : %s", fontName );
		assert( false );
		return ;
	}

	set<unsigned int> *charSet = lpBMFontConfiguration->getCharacterSet();

	std::string nString = info.str;
	uint32 stringLen = nString.size();
	if ( stringLen <= 0 )
		return;

	std::vector< std::string > mutliLine;

	if ( isPreWrap )
	{
		m_lineCounts += 1;
		preLineWidth = 0;
	}

	int nextFontPositionX = (int)preLineWidth;
	unsigned short prev = -1;
	int kerningAmount = 0;

	CCRect rect;
	ccBMFontDef fontDef;

	uint32 beginPos = 0;
	for (uint32 i= 0; i < stringLen; i++)
	{
		unsigned short c = nString[i];

		bool breakLine = false;
		if ( c == '\n' )
			breakLine = true;
		else
		{
			if (charSet->find(c) == charSet->end())
			{
				CCLOGWARN("cocos2d::CCLabelBMFont: Attempted to use character not defined in this bitmap: %d", c);
				continue;      
			}

			kerningAmount = this->kerningAmountForFirst(lpBMFontConfiguration,prev, c);

			tCCFontDefHashElement *element = NULL;

			// unichar is a short, and an int is needed on HASH_FIND_INT
			unsigned int key = c;
			HASH_FIND_INT(lpBMFontConfiguration->m_pFontDefDictionary, &key, element);
			if (! element)
			{
				CCLOGWARN("cocos2d::CCLabelBMFont: characer not found %d", c);
				continue;
			}

			fontDef = element->fontDef;
			kerningAmount = lpBMFontConfiguration->m_tPadding.right;

			nextFontPositionX += fontDef.xAdvance + kerningAmount;
			prev = c;
		}

		if ( nextFontPositionX > (int)dimensions.width || breakLine )
		{
			std::string subString = nString.substr( beginPos, i - beginPos );
			mutliLine.push_back( subString );

			if ( breakLine )
				beginPos = i + 1;
			else
				beginPos = i;

			preLineWidth = 0.0f;
			nextFontPositionX = 0;
		}
	}

	preLineWidth = (float)nextFontPositionX;
	if ( beginPos < stringLen )
	{
		std::string subString = nString.substr( beginPos, stringLen - beginPos );
		mutliLine.push_back( subString );
	}

	for( size_t idx = 0; idx < mutliLine.size(); ++idx )
	{
		if ( idx != 0 )
			++m_lineCounts;

		CellStringInfo cellStringInfo;
		cellStringInfo.str = mutliLine[idx];
		cellStringInfo.fontMode = info.sizeMode;
		cellStringInfo.color = info.color;
		cellStringInfo.alpha = info.alpha;

		divideStringInfoMapIter iter = m_DivideStringInfoMap.find( m_lineCounts );
		if ( iter != m_DivideStringInfoMap.end() )
			iter->second.push_back( cellStringInfo );
		else
		{
			CellStringInfoVec cellStringInfoVec;
			cellStringInfoVec.push_back( cellStringInfo );
			m_DivideStringInfoMap[m_lineCounts] = cellStringInfoVec;
		}
	}
	mutliLine.clear();
}

int GLabelTTF::kerningAmountForFirst(CCBMFontConfiguration* lpBMFontConf,unsigned short first, unsigned short second)
{
	int ret = 0;
	unsigned int key = (first<<16) | (second & 0xffff);

	if( lpBMFontConf->m_pKerningDictionary ) {
		tCCKerningHashElement *element = NULL;
		HASH_FIND_INT(lpBMFontConf->m_pKerningDictionary, &key, element);        
		if(element)
			ret = element->amount;
	}
	return ret;
}

float GLabelTTF::getFontSize(uint32 fontSize)
{
	float f = FONTSIZE(22);
	switch(fontSize)
	{
	case 1:
		f = FONTSIZE(16);
		break;
	case 2:
		f = FONTSIZE(22);
		break;
	case 3:
		f = FONTSIZE(28);
		break;
	case 4:
		f = FONTSIZE(34);
		break;
	default:
		assert( false );
		break;
	}
	return f;
}

float GLabelTTF::getFontStroke(uint32 fontSize)
{
	float f = FONTSIZE(2);
	switch(fontSize)
	{
	case 1:
		f = FONTSIZE(1);
		break;
	case 2:
		f = FONTSIZE(2);
		break;
	case 3:
		f = FONTSIZE(3);
		break;
	case 4:
		f = FONTSIZE(4);
		break;
	default:
		assert( false );
		break;
	}
	return f;
}

const char * GLabelTTF::getFontName(uint32 fontSize)
{
	const char * f;
	switch(fontSize)
	{
	case 1:
		f = s_BMF_S;
		break;
	case 2:
		f = s_BMF_M;
		break;
	case 3:
		f = s_BMF_L;
		break;
	case 4:
		f = s_BMF_LX;
		break;
	default:
		assert( false );
		break;
	}
	return f;
}

bool setFont(const char * pFontName, int nSize)
{
	return true;
}

// swap the alpha channel in an 32 bit image (from ARGB to RGBA)
void my_swapAlphaChannel(unsigned int *pImageMemory, unsigned int numPixels)
{
	for(int c = 0; c < numPixels; ++c, ++pImageMemory)
	{
		// copy the current pixel
		unsigned int currenPixel =  (*pImageMemory);
		// swap channels and store back
		char *pSource = (char *) 	&currenPixel;
		*pImageMemory = (pSource[0] << 24) | (pSource[3]<<16) | (pSource[2]<<8) | pSource[1];
	}
}
