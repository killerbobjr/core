#ifndef CXMLELEMENT_H
#define CXMLELEMENT_H

#include <string>

class CXmlElement
{
    std::wstring m_sType;
    std::wstring m_sStyleId;
    std::wstring m_sDefault;
    std::wstring m_sCustomStyle;
    std::wstring m_sS;

    std::wstring m_sName;
    std::wstring m_sBasedOn;
    std::wstring m_sLink;
    std::wstring m_sUiPriority;
    bool m_bQFormat = false;
    bool m_bSemiHidden = false;
    bool m_bUnhideWhenUsed = false;

    // <rPr>
        bool m_bB = false;
        bool m_bI = false;
        std::wstring m_sU;
        std::wstring m_sRFonts;
        std::wstring m_sColor;
        std::wstring m_sSz;
    // </rPr>

    // <pPr>
        bool m_bKeepLines = false;
        bool m_bKeepNext = false;
        bool m_bContextualSpacing = false;
        std::wstring m_sSpacing;
        std::wstring m_sOutlineLvl;
        std::wstring m_sInd;
        std::wstring m_sJc;
        std::wstring m_sShd;

        // <pBdr>
            std::wstring m_sTopBorder;
            std::wstring m_sLeftBorder;
            std::wstring m_sBottomBorder;
            std::wstring m_sRightBorder;
        // </pBdr>

    // </pPr>

    // <tblPr>
        std::wstring m_sTblInd;
        // <tblCellMar>
            std::wstring m_sCellTop;
            std::wstring m_sCellLeft;
            std::wstring m_sCellBottom;
            std::wstring m_sCellRight;
        // <tblCellMar>

        // <tblBorders>
            std::wstring m_sBorderTop;
            std::wstring m_sBorderLeft;
            std::wstring m_sBorderBottom;
            std::wstring m_sBorderRight;
            std::wstring m_sBorderInsideH;
            std::wstring m_sBorderInsideV;
        // </tblBorders>
    // </tblPr>

    std::wstring ConvertPStyle() const;
    std::wstring ConvertRStyle() const;
    std::wstring ConvertBasicInfoStyle() const;

public:
    CXmlElement();
    CXmlElement(const std::wstring sNameDefaultElement);

    bool Empty() const;

    void CreateDefaultElement(const std::wstring sNameDefaultElement);
    void Clear();

    void SetType(std::wstring sType);
    void SetStyleId(std::wstring sStyleId);
    void SetDefault(std::wstring sDefault);
    void SetCustomStyle(std::wstring sCustomStyle);
    void SetS(std::wstring sS);

    void SetName(std::wstring sName);
    void SetBasedOn(std::wstring sBasedOn);
    void SetLink(std::wstring sLink);
    void SetUiPriority(std::wstring sUiPriority);
    void SetQFormat(bool bQFormat);
    void SetUnhideWhenUsed(bool bUnhideWhenUsed);

    // <rPr>
        void SetB(bool bB);
        void SetI(bool bI);
        void SetU(std::wstring sU);
        void SetRFonts(std::wstring sRFonts);
        void SetColor(std::wstring sColor);
        void SetSz(std::wstring sSz);
    // </rPr>

    // <pPr>
        void SetKeepLines(bool bKeepLines);
        void SetKeepNext(bool bKeepNext);
        void SetContextualSpacing(bool bContextualSpacing);
        void SetSpacing(std::wstring sSpacing);
        void SetOutlineLvl(std::wstring sOutlineLvl);
        void SetInd(std::wstring sInd);
        void SetJc(std::wstring sJc);
        void SetShd(std::wstring sShd);

        // <pBdr>
            void SetTopBorder(std::wstring sTopBorder);
            void SetLeftBorder(std::wstring sLeftBorder);
            void SetBottomBorder(std::wstring sBottomBorder);
            void SetRightBorder(std::wstring sRightBorder);
        // </pBdr>
    // </pPr>

    // <tblPr>
        void SetTblInd(std::wstring sTblInd);
        // <tblCellMar>
            void SetCellTop(std::wstring sCellTop);
            void SetCellLeft(std::wstring sCellLeft);
            void SetCellBottom(std::wstring sCellBottom);
            void SetCellRight(std::wstring sCellRight);
        // <tblCellMar>

        // <tblBorders>
            void SetBorderTop(std::wstring sBorderTop);
            void SetBorderLeft(std::wstring sBorderLeft);
            void SetBorderBottom(std::wstring sBorderBottom);
            void SetBorderRight(std::wstring sBorderRight);
            void SetBorderInsideH(std::wstring sBorderInsideH);
            void SetBorderInsideV(std::wstring sBorderInsideV);
        // </tblBorders>
    // </tblPr>

    std::wstring GetPStyle() const;
    std::wstring GetRStyle() const;
    std::wstring GetStyle() const;

    const std::wstring& GetBasedOn() const;
    const std::wstring& GetStyleId() const;
    const std::wstring& GetName() const;

    CXmlElement& operator+=(const CXmlElement& oElement);
    CXmlElement& operator= (const CXmlElement& oelement);
    bool operator== (const CXmlElement& oElement);
};

#endif // CXMLELEMENT_H