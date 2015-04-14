#pragma once
#ifndef OOX_CELLANCHOR_FILE_INCLUDE_H_
#define OOX_CELLANCHOR_FILE_INCLUDE_H_

#include "../CommonInclude.h"

#include "FromTo.h"
#include "Pic.h"
#include "GraphicFrame.h"
#include "Pos.h"
#include "Shape.h"

namespace OOX
{
	namespace Spreadsheet
	{
		class CCellAnchor : public WritingElement
		{
		public:
			WritingElementSpreadsheet_AdditionConstructors(CCellAnchor)
            CCellAnchor(const SimpleTypes::Spreadsheet::CCellAnchorType<>& oAnchorType/* = SimpleTypes::Spreadsheet::CCellAnchorType<>()*/):m_oAnchorType(oAnchorType)
			{
			}
			virtual ~CCellAnchor()
			{
			}

		public:
			virtual CString      toXML() const
			{
				return _T("");
			}
			virtual void toXML(XmlUtils::CStringWriter& writer) const
			{
				if(isValid())
				{
					CString sStart;
					CString sEnd;
					if(m_oFrom.IsInit() && m_oTo.IsInit())
					{
						sStart.Format(_T("<xdr:twoCellAnchor editAs=\"%ls\">"), m_oAnchorType.ToString());
						sEnd = _T("</xdr:twoCellAnchor>");
						writer.WriteString(sStart);
						if(m_oFrom.IsInit())
							m_oFrom->toXML2(writer, _T("xdr:from"));
						if(m_oTo.IsInit())
							m_oTo->toXML2(writer, _T("xdr:to"));
					}
					else if(m_oFrom.IsInit() && m_oExt.IsInit())
					{
						sStart.Append(_T("<xdr:oneCellAnchor>"));
						sEnd = _T("</xdr:oneCellAnchor>");
						writer.WriteString(sStart);
						if(m_oFrom.IsInit())
							m_oFrom->toXML2(writer, _T("xdr:from"));
						if(m_oExt.IsInit())
							m_oExt->toXML(writer);
					}
					else if(m_oPos.IsInit() && m_oExt.IsInit())
					{
						sStart.Append(_T("<xdr:absoluteAnchor>"));
						sEnd = _T("</xdr:absoluteAnchor>");
						writer.WriteString(sStart);
						if(m_oPos.IsInit())
						m_oPos->toXML(writer);
						if(m_oExt.IsInit())
							m_oExt->toXML(writer);
					}
					else
						return;
					if(m_oXml.IsInit())
						writer.WriteString(m_oXml.get());	
					if(m_oGraphicFrame.IsInit())
						m_oGraphicFrame->toXML(writer);
					writer.WriteString(sEnd);	
				}
			}
			virtual void         fromXML(XmlUtils::CXmlLiteReader& oReader)
			{
				ReadAttributes( oReader );

				if ( oReader.IsEmptyNode() )
					return;

				int nCurDepth = oReader.GetDepth();
				while( oReader.ReadNextSiblingNode( nCurDepth ) )
				{
					CString sName = XmlUtils::GetNameNoNS(oReader.GetName());

					if ( _T("from") == sName )
						m_oFrom = oReader;
					else if ( _T("to") == sName )
						m_oTo = oReader;
					else if ( _T("pos") == sName )
						m_oPos = oReader;
					else if ( _T("ext") == sName )
						m_oExt = oReader;
					else if ( _T("graphicFrame") == sName )
					{
						m_oGraphicFrame = oReader;
						if ((m_oGraphicFrame.IsInit())  &&	(m_oGraphicFrame->m_oChartGraphic.IsInit()) && 
															(m_oGraphicFrame->m_oChartGraphic->m_oGraphicData.IsInit()))
						{
							//������� ���� ������ �� ������ (��� ��������)
							m_sSpId = m_oGraphicFrame->m_oChartGraphic->m_oGraphicData->m_sSpId;
						}
					}
	//��� ������ ���������� ... �� ��� ������������� ����� ������� � ��� xml !!!!
					//else if (_T("pic") == sName )
					//	m_oPicture = oReader;
					//else if (_T("sp") == sName)
					//	m_oShape = oReader;
					//else if (_T("cxnSp") == sName)
					//	m_oConnShape = oReader;
					//else if (_T("grpSp") == sName || _T("AlternateContent") == sName)
					//	m_oXml = oReader.GetOuterXml();
/////////////////////////////////
					//
					else if ( _T("pic") == sName || _T("sp") == sName || _T("grpSp") == sName || _T("cxnSp") == sName)
					{			
						m_oXml = oReader.GetOuterXml();
						{
							XmlUtils::CXmlLiteReader oShapeReader;
							//���������� ����������� xml-������
                            CString xmlString;// = L"<?xml version=\"1.0\"?>";// encoding=\"UTF-8\"
							xmlString += L"<root ";
								xmlString += L"xmlns:a=\"http://schemas.openxmlformats.org/drawingml/2006/main\" ";
								xmlString += L"xmlns:a14=\"http://schemas.microsoft.com/office/drawing/2010/main\" ";	
								xmlString += L"xmlns:xdr=\"http://schemas.openxmlformats.org/drawingml/2006/spreadsheetDrawing\" ";
								xmlString += L"xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\" ";
							xmlString += L">";
							xmlString += *m_oXml;
							xmlString += L"</root>";
                                                        bool result =oShapeReader.FromString(xmlString);

							result = oShapeReader.ReadNextNode();//root
							result = oShapeReader.ReadNextNode();

							CString sName = XmlUtils::GetNameNoNS(oShapeReader.GetName());
							
							if (_T("pic") == sName)
								m_oPicture = oShapeReader;
							else if (_T("sp") == sName)
							{	//��� ����� ���� �� ����������� ������, � ������ �� ����, ������������� � xml ��� ���� ���
								// pptx:DrawingObjectConverter ����� �� ���������� - ������ ��
								m_oShape = oShapeReader;
								if ((m_oShape.IsInit()) && (m_oShape->m_oNvSpPr.IsInit()) && 
									(m_oShape->m_oNvSpPr->m_oCNvPr.IsInit()) && (m_oShape->m_oNvSpPr->m_oCNvPr->m_oExtLst.IsInit()))
								{
									for (int i=0; i < m_oShape->m_oNvSpPr->m_oCNvPr->m_oExtLst->m_arrExt.size();i++)
									{
										if (m_oShape->m_oNvSpPr->m_oCNvPr->m_oExtLst->m_arrExt[i]->m_sSpId.IsInit())
										{
											//���������� ��� � ���� ������ �� ������� -> ��������� �� "������" (��� ��������)
											m_oXml.reset();
											m_sSpId = m_oShape->m_oNvSpPr->m_oCNvPr->m_oExtLst->m_arrExt[i]->m_sSpId;
										}
									}
								}
							}
							else if (_T("cxnSp") == sName)
								m_oConnShape = oShapeReader;
							else if (_T("grpSp") == sName)
								m_oGroupShape = oShapeReader;
						}
					}
					else if ( _T("AlternateContent") == sName)
					{			
						//Demo-2010WinterOlympics2.xlsx
						//������������� �� ������ ������ ����� ����� ���������� - ������ ... ��� ����� ����������� � ����� ����� 
						//todooo ������� ������ �� ����������� fallback, �� ������ ������ ������ ��� (a14, ..)
						{
							nCurDepth++;
							while( oReader.ReadNextSiblingNode( nCurDepth ) )
							{
								CString sName = XmlUtils::GetNameNoNS(oReader.GetName());
								if ( _T("Fallback") == sName )
								{
									CString xmlString;// = L"<?xml version=\"1.0\"?>"; //encoding=\"UTF-8\"
									xmlString += L"<root ";
										xmlString += L"xmlns:mc=\"http://schemas.openxmlformats.org/markup-compatibility/2006\" ";
										xmlString += L"xmlns:a=\"http://schemas.openxmlformats.org/drawingml/2006/main\" ";
										xmlString += L"xmlns:a14=\"http://schemas.microsoft.com/office/drawing/2010/main\" ";	
										xmlString += L"xmlns:xdr=\"http://schemas.openxmlformats.org/drawingml/2006/spreadsheetDrawing\" ";
										xmlString += L"xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\" ";
									xmlString += L">";
									xmlString += oReader.GetOuterXml();
									xmlString += L"</root>";										
									XmlUtils::CXmlLiteReader oSubReader;
									
									if (oSubReader.FromString(xmlString))
									{
										oSubReader.ReadNextNode();//root

										oSubReader.ReadNextNode();//fallback
										fromXML(oSubReader);	
									}
									break;
								}
							}
							nCurDepth--;
						}
					}
				}
			}

			virtual EElementType getType () const
			{
				return et_CellAnchor;
			}

			virtual void setAnchorType (SimpleTypes::Spreadsheet::ECellAnchorType eType)
			{
				m_oAnchorType.SetValue(eType);
			}
			virtual SimpleTypes::Spreadsheet::ECellAnchorType getAnchorType () const
			{
				return m_oAnchorType.GetValue();
			}
			bool isValid() const
			{
				SimpleTypes::Spreadsheet::ECellAnchorType eAnchorType = m_oAnchorType.GetValue();
				if(!((m_oFrom.IsInit() && m_oTo.IsInit()) || (m_oFrom.IsInit() && m_oExt.IsInit()) || (m_oPos.IsInit() && m_oExt.IsInit())))
					return false;
				if(false == m_oXml.IsInit() && false == m_oGraphicFrame.IsInit() && false == m_sSpId.IsInit())
					return false;
				return true;
			}
		private:
			void ReadAttributes(XmlUtils::CXmlLiteReader& oReader)
			{
			}
		public:
			SimpleTypes::Spreadsheet::CCellAnchorType<>		m_oAnchorType;
			nullable<OOX::Spreadsheet::CFromTo>				m_oFrom;
			nullable<OOX::Spreadsheet::CFromTo>				m_oTo;
			nullable<OOX::Spreadsheet::CPos>				m_oPos;
			nullable<OOX::Spreadsheet::CExt>				m_oExt;
			nullable<OOX::Spreadsheet::CGraphicFrame>		m_oGraphicFrame;
			nullable<OOX::Spreadsheet::CPic>				m_oPicture;
			nullable<OOX::Spreadsheet::CGroupShape>			m_oGroupShape;
			nullable<OOX::Spreadsheet::CShape>				m_oShape;
			nullable<OOX::Spreadsheet::CConnShape>			m_oConnShape;

			// ��� pptx:ObjectDrawingConverter
			nullable<CString>								m_oXml;

			//��� ��������
			nullable<CString>								m_sSpId;
		};
	} //Spreadsheet
} // namespace OOX

#endif // OOX_CELLANCHOR_FILE_INCLUDE_H_
