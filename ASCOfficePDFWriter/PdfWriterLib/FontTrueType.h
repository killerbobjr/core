﻿#ifndef _FONT_TRUE_TYPE_H
#define _FONT_TRUE_TYPE_H


#include "Utils.h"
#include "Font.h"
#include "FontTrueTypeWriter.h"

//----- TrueType Fonts ------------------------------------------------------------------------------


unsigned short TTFontDefGetGlyphID  (FontDef pFontDef, unsigned short nUnicode);


//----- ќсновные функции ----------------------------------------------------------------------------

FontDef        TTFontDefNew         (MMgr oMMgr);
FontDef        TTFontDefLoad        (MMgr oMMgr, std::wstring & wsFilePath, bool bEmbedding, const char *sEncodingName = NULL, bool bEncoding = false, bool bSymbolic = false, bool bUsesMacRomanEncoding = false, bool bFastParse = false);
FontDef        TTFontDefLoad2       (MMgr oMMgr, std::wstring & wsFilePath, unsigned int nIndex, bool bEmbedding, const char *sEncodingName = NULL, bool bEncoding = false, bool bSymbolic = false, bool bUsesMacRomanEncoding = false);

unsigned short TTFontDefGetGlyphID  (FontDef pFontDef, unsigned short nUnicode);
Box            TTFontDefGetCharBBox (FontDef pFontDef, unsigned short nUnicode);
short          TTFontDefGetCharWidth(FontDef pFontDef, unsigned short nUnicode);
short          TTFontDefGetGidWidth (FontDef pFontDef, unsigned short nGid);

unsigned long  TTFontDefSaveFontData(FontDef pFontDef, StreamRecPtr pStream, FontAttr *ppFontAttr = NULL, PToUnicode pToUnicode = NULL);

void           TTFontDefSetTagName  (FontDef pFontDef, char *sTag);

FontDict TTFontNew  (MMgr oMMgr, FontDef pFontDef, EncoderRecPtr pEncoder, Xref pXref, PToUnicode pToUnicode = NULL);
#endif /* _FONT_TRUE_TYPE_H */
