package org.cocos2dx.lib;
import org.cocos2dx.lib.Cocos2dxTypefaces;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.util.FloatMath;
import android.util.Log;

public class GlabelTTFBitmap {

	private static Context sContext;
	private static Paint paint1;
	private static Paint paint2;
	private static Paint paint3;
	private static Paint paint4;
	
	private static native void nativeInitBitmapDC(final int pWidth);
	
	public static void initializeAllFont( final String pFontName, final int pFontSize1, final int pFontSize2, final int pFontSize3, final int pFontSize4 )
	{
		paint1 = GlabelTTFBitmap.newPaint(pFontName, pFontSize1);
		paint2 = GlabelTTFBitmap.newPaint(pFontName, pFontSize2);
		paint3 = GlabelTTFBitmap.newPaint(pFontName, pFontSize3);
		paint4 = GlabelTTFBitmap.newPaint(pFontName, pFontSize4);
	}
	
	public static void createGLabelTTFBitmap(String pString, final int pFontSizeMode, final int pWidth)
	{
		final Paint paint;
		switch( pFontSizeMode )
		{
		case 1:
			paint = paint1;
			break;
		case 2:
			paint = paint2;
			break;
		case 3:
			paint = paint3;
			break;
		case 4:
			paint = paint4;
			break;
		default :
			paint = paint1;
			break;
		}
		//final Paint paint = GlabelTTFBitmap.newPaint(pFontName, pFontSize);
		int tempWidth = (int) FloatMath.ceil(paint.measureText(pString));
		
		GlabelTTFBitmap.nativeInitBitmapDC(tempWidth);
	}
	
	private static Paint newPaint( final String pFontName, final int pFontSize )
	{
		final Paint paint = new Paint();
		paint.setColor(Color.WHITE);
		paint.setTextSize(pFontSize);
		
		if (pFontName.endsWith(".ttf")) {
			try {
				final Typeface typeFace = Cocos2dxTypefaces.get(GlabelTTFBitmap.sContext, pFontName);
				paint.setTypeface(typeFace);
			} catch (final Exception e) {
				Log.e("Cocos2dxBitmap", "error to create ttf type face: " + pFontName);

				/* The file may not find, use system font. */
				paint.setTypeface(Typeface.create(pFontName, Typeface.NORMAL));
			}
		} else {
			paint.setTypeface(Typeface.create(pFontName, Typeface.NORMAL));
		}
		
		return paint;
	}
}
