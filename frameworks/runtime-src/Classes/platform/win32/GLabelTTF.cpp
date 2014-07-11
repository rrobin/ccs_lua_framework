#include "GLabelTTF/GLabelTTF.h"
#include <Windows.h>
#include <string>
#include <ctype.h>
#include "Util.h"

static HFONT s_HFont = NULL;
static std::string s_curFontPath;
static HDC s_hDC;

static CCBMFontConfiguration* lpBMFontConfiguration_s = NULL;
static CCBMFontConfiguration* lpBMFontConfiguration_m = NULL;
static CCBMFontConfiguration* lpBMFontConfiguration_l = NULL;
static CCBMFontConfiguration* lpBMFontConfiguration_xl = NULL;

const char* s_BMF_S	= "fonts/soopafre_s.fnt";
const char* s_BMF_M	= "fonts/soopafre_m.fnt";
const char* s_BMF_L	= "fonts/soopafre_l.fnt";
const char* s_BMF_LX= "fonts/soopafre_lx.fnt";

//bool setFont(const char * pFontName = NULL, int nSize = 0);
wchar_t* utf8ToUtf16(std::string nString)
{
	wchar_t * pwszBuffer = NULL;

	do 
	{
		if (nString.size() < 0)
		{
			break;
		}
		// utf-8 to utf-16
		int nLen = nString.size();
		int nBufLen  = nLen + 1;			
		pwszBuffer = new wchar_t[nBufLen];
		CC_BREAK_IF(! pwszBuffer);
		memset(pwszBuffer,0,nBufLen);
		nLen = MultiByteToWideChar(CP_UTF8, 0, nString.c_str(), nLen, pwszBuffer, nBufLen);		
		pwszBuffer[nLen] = '\0';
	} while (0);	
	return pwszBuffer;
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
	CCSize size = CCSizeMake( 0x7ffffff, 0x7fffffff );
	return initWithString(string,type,fontName,fontSize,lineSpace,size,kCCTextAlignmentLeft);
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
	LONG preWidthTTF = 0;
	float preWidthBMF = 0.0f;
	std::vector<LabelTTFColorSizeInfo>& info = m_xmlStringParse->getColorSizeInfoVec();
	for ( size_t i = 0; i < info.size(); ++i )
	{
		if ( type == GLabel_TTF )
		{
			if ( info[i].str != "" )
				divideOneString( info[i], fontName, dimensions, bPreWrap, preWidthTTF );
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
				}
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
				}
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
			}
			beginPos += node->getContentSize().width;
		}

		totalHeight -= ( labelSize[iter->first].height + m_spaceline );
		beginPos = 0.0f;
	}
}

void GLabelTTF::divideOneString( const LabelTTFColorSizeInfo& info, const char* fontName, const CCSize& dimensions, bool isPreWrap, long& preLineWidth )
{
	if(s_hDC == NULL)
	{
		HDC hdc = GetDC(NULL);
		s_hDC   = CreateCompatibleDC(hdc);
		ReleaseDC(NULL, hdc);
	}

	std::string nString = info.str;
	wchar_t * pwszBuffer = NULL;
	if (nString.size() <= 0)
		return;
	// utf-8 to utf-16
	int nLen = nString.size();
	int nBufLen  = nLen + 1;			
	pwszBuffer = new wchar_t[nBufLen];
	if(!pwszBuffer)
		return;
	memset(pwszBuffer,0,nBufLen);
	nLen = MultiByteToWideChar(CP_UTF8, 0, nString.c_str(), nLen, pwszBuffer, nBufLen);		
	pwszBuffer[nLen] = '\0';
	std::vector<wchar_t*> mutliLine;
	setFont(fontName,(int)(getFontSize( info.sizeMode ) * CC_CONTENT_SCALE_FACTOR()));

	if ( isPreWrap )
	{
		m_lineCounts += 1;
		preLineWidth = 0;
	}

	SIZE tRet = {0};
	int line = 0;
	int i = 0;
	for(; i < nLen; ++i)
	{
		bool breakLine = false;

		RECT rc = {0, 0, 0, 0};
		if(pwszBuffer[i] == '\n')
			breakLine = true;
		else
		{
			DWORD dwCalcFmt = DT_CALCRECT;
			HGDIOBJ hOld = SelectObject(s_hDC, s_HFont);
			DrawTextW(s_hDC,&pwszBuffer[line],i - line + 1,&rc,dwCalcFmt);
			SelectObject(s_hDC, hOld);
			tRet.cx = preLineWidth + rc.right;// 开始的位置可能不是0
			tRet.cy = rc.bottom;
		}
		
		if( ( tRet.cx > (int)dimensions.width ) || breakLine )
		{
			int nLenTemp = i - line;
			wchar_t* pwszText = new wchar_t[nLenTemp+1];
			if ( nLenTemp > 0 )
				memcpy(pwszText,&pwszBuffer[line],nLenTemp*sizeof(wchar_t));
			pwszText[nLenTemp] = '\0';
			mutliLine.push_back(pwszText);

			if ( breakLine )
				line = i + 1;
			else
				line = i;

			preLineWidth = 0;

			if ( line < nLen )
			{
				DWORD dwCalcFmt = DT_CALCRECT;
				HGDIOBJ hOld = SelectObject(s_hDC, s_HFont);
				DrawTextW(s_hDC,&pwszBuffer[line],1,&rc,dwCalcFmt);
				SelectObject(s_hDC, hOld);
				tRet.cx = rc.right;
				tRet.cy = rc.bottom;
			}
		}
	}
	preLineWidth = tRet.cx;

	int nLenTemp = i - line;
	if ( nLenTemp > 0 )
	{
		wchar_t* pwszText = new wchar_t[nLenTemp+1];
		memcpy(pwszText,&pwszBuffer[line],nLenTemp*sizeof(wchar_t));
		pwszText[nLenTemp] = '\0';
		mutliLine.push_back(pwszText);
	}
	

	for( size_t idx = 0; idx < mutliLine.size(); ++idx )
	{
		if ( idx != 0 )
			++m_lineCounts;
		
		// Utf16ToUtf8
		std::string utf8str = "";
		if ( mutliLine[idx][0] != '\0' )
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

		delete [] mutliLine[idx];
	}
	mutliLine.clear();

	delete[] pwszBuffer;
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
	}
	return f;
}

bool setFont(const char * pFontName, int nSize)
{
	bool bRet = false;
	do 
	{
		std::string fontName = pFontName;
		std::string fontPath;
		HFONT       hDefFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		LOGFONTA    tNewFont = {0};
		LOGFONTA    tOldFont = {0};
		GetObjectA(hDefFont, sizeof(tNewFont), &tNewFont);
		if (fontName.c_str())
		{    
			// create font from ttf file
			int nFindttf = fontName.find(".ttf");
			int nFindTTF = fontName.find(".TTF");
			if (nFindttf >= 0 || nFindTTF >= 0)
			{
				fontPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(fontName.c_str());
				int nFindPos = fontName.rfind("/");
				fontName = &fontName[nFindPos+1];
				nFindPos = fontName.rfind(".");
				fontName = fontName.substr(0,nFindPos);                
			}
			tNewFont.lfCharSet = DEFAULT_CHARSET;
			strcpy_s(tNewFont.lfFaceName, LF_FACESIZE, fontName.c_str());
		}
		if (nSize)
		{
			tNewFont.lfHeight = -nSize;
		}
		GetObjectA(s_HFont,  sizeof(tOldFont), &tOldFont);

		if (tOldFont.lfHeight == tNewFont.lfHeight
			&& ! strcpy(tOldFont.lfFaceName, tNewFont.lfFaceName))
		{
			// already has the font 
			bRet = true;
			break;
		}

		// delete old font
		if (s_HFont != hDefFont)
		{
			DeleteObject(s_HFont);
			// release old font register
			if (s_curFontPath.size() > 0)
			{
				wchar_t * pwszBuffer = utf8ToUtf16(s_curFontPath);
				if (pwszBuffer)
				{
					if(RemoveFontResource(pwszBuffer))
					{
						SendMessage( NULL, WM_FONTCHANGE, 0, 0);
					}						
					delete [] pwszBuffer;
					pwszBuffer = NULL;
				}
			}
			if (fontPath.size() > 0)
				s_curFontPath = fontPath;
			else
				s_curFontPath.clear();
			// register temp font
			if (s_curFontPath.size() > 0)
			{
				wchar_t * pwszBuffer = utf8ToUtf16(s_curFontPath);
				if (pwszBuffer)
				{
					if(AddFontResource(pwszBuffer))
					{
						SendMessage( NULL, WM_FONTCHANGE, 0, 0);
					}						
					delete [] pwszBuffer;
					pwszBuffer = NULL;
				}
			}
		}
		s_HFont = NULL;

		// disable Cleartype
		tNewFont.lfQuality = ANTIALIASED_QUALITY;

		// create new font
		s_HFont = CreateFontIndirectA(&tNewFont);
		if (!s_HFont)
		{
			// create failed, use default font
			s_HFont = hDefFont;
			break;
		}

		bRet = true;
	} while (0);
	return bRet;
}
