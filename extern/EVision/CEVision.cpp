//---------------------------------------------------------------------------


#pragma hdrstop
#include <vcl>
#include "CEVision.h"
#include "math.h"
#include "dir.h"

CEVision theVision;
//---------------------------------------------------------------------------

#pragma package(smart_init)

__fastcall CEVision::CEVision()
{
        mkdir("c:\\Product Image");
        Euresys::eVision::Initialize();
        ESetAngleUnit(E_ANGLE_UNIT_DEGREES);
        
        m_ImageSizeX=640;
        m_ImageSizeY=480;
        m_PixelSize=8;
       
        m_ImageTmpBW8.SetSize(m_ImageSizeX,m_ImageSizeY);

       // ERectangleGauge1.Attach(&m_frameShape);
        m_frameShape.SetDragable(true,true);
        m_frameShape.SetResizable(true,true);
        m_frameShape.SetRotatable(true,true);

         m_rectAlignment.SetDragable(true,true);
        m_rectAlignment.SetResizable(true,true);
        m_rectAlignment.SetRotatable(true,true);
         m_rectAlignment.SetDraggingMode(INS_DRAG_TO_EDGES);

         for(int nIndex=0;nIndex<3;nIndex++)
         {
                m_roiMark[nIndex].Attach(&m_ImageTmpBW8);
                m_roiMark[nIndex].SetPlacement(10,10,50,50);

                m_roiMarkPattern[nIndex].Attach(&m_ImageTmpBW8);
                m_roiMarkPattern[nIndex].SetPlacement(10,10,50,50);
         }

         for(int nIndex=0;nIndex<4;nIndex++)
         {
                m_roiBlock[nIndex].Attach(&m_ImageTmpBW8);
                m_roiBlock[nIndex].SetPlacement(10,10,50,50);
         }

         m_dMMperPixel=0.0097625;

         m_dScaleSizeX=1.0;
         m_dScaleSizeY=1.0;

         m_bShowLayout=false;

         m_bShowMarkROI[0]=false;
         m_bShowPatternROI[0]=false;
         m_bShowMatchResult[0]=false;

         m_bShowMarkROI[1]=false;
         m_bShowPatternROI[1]=false;
         m_bShowMatchResult[1]=false;

         m_bShowMarkROI[2]=false;
         m_bShowPatternROI[2]=false;
         m_bShowMatchResult[2]=false;

         m_bShowBlockROI[0]=false;
         m_bShowBlockROI[1]=false;
         m_bShowBlockROI[2]=false;
         m_bShowBlockROI[3]=false;

         m_bShowMatchResultAll=false;

         m_nCurrentRoiBlock=0;
}
//---------------------------------------------------------------------------
__fastcall CEVision::~CEVision()
{
        EShape *pShape;
        int nNum=m_frameShape.GetNumDaughters();

        for(int nIndex=0;nIndex<nNum;nIndex++)
        {
                pShape=m_frameShape.GetDaughter(0);
                delete pShape;
        }

        m_frameShape.DetachDaughters();
}
//---------------------------------------------------------------------------
void __fastcall CEVision::Init()
{
        Euresys::eVision::Initialize();
        ESetAngleUnit(E_ANGLE_UNIT_DEGREES);

        INT32 imageSize ;
	imageSize = m_ImageSizeY * m_ImageSizeX * m_PixelSize;
        m_ImageBuffer = (PUINT8)VirtualAlloc(NULL, imageSize, MEM_COMMIT, PAGE_READWRITE);

        m_ImageBW8.SetImagePtr(m_ImageSizeX,m_ImageSizeY,m_ImageBuffer,m_ImageSizeX*m_PixelSize);
  
        //m_roiLeft.Attach(&m_ImageBW8);
        //m_roiLeft.SetPlacement(10,10,50,50);
}

//---------------------------------------------------------------------------
void __fastcall CEVision::AddRectGauge()
{
         ERectangleGauge *pRectGauge;
         pRectGauge=new ERectangleGauge();

         pRectGauge->SetDraggingMode(INS_DRAG_TO_EDGES);
         pRectGauge->Attach(&m_frameShape);

         m_frameShape.SetDragable(true,true);
         m_frameShape.SetResizable(true,true);
         m_frameShape.SetRotatable(true,true);
         m_frameShape.SetLabeled(true,true);

}

//---------------------------------------------------------------------------
void __fastcall CEVision::DeleteGauge(int nIndex)
{
        if(nIndex<0) return;
        EShape *pGauge=m_frameShape.GetDaughter(nIndex);
        pGauge->Detach();
        delete pGauge;
}
//---------------------------------------------------------------------------

void __fastcall CEVision::LoadTool(char *strFileName,AnsiString strSch,bool bFileType)
{
        return; //no need
        //m_frameShape.Load(strFileName,true);
        ESerializer *pSerializer = ESerializer::CreateFileReader( strFileName);

        if(pSerializer==NULL)
        {
                ShowMessage("視覺檔案開啟失敗");
                return;
        }

        AnsiString strName="C:\\Product Image\\"+strSch+".bmp";

        if(!FileExists(strName) ) strName="C:\\Product Image\\Dummy.bmp";

        if(FileExists(strName) && bFileType) m_ImageTmpBW8.Load(strName.c_str());
        else  m_ImageTmpBW8.Load(pSerializer);


        try{
        for(int nIndex=0;nIndex<3;nIndex++)
        {
                m_markMatch[nIndex].Load(pSerializer);
                m_roiMarkPattern[nIndex].Load(pSerializer);
                m_roiMark[nIndex].Load(pSerializer);

                m_roiMark[nIndex].Attach(&m_ImageTmpBW8);
                m_roiMarkPattern[nIndex].Attach(&m_ImageTmpBW8);
        }

        if(!pSerializer->IsEOS())
        {
                for(int nIndex=0;nIndex<4;nIndex++)
                {
                        m_roiBlock[nIndex].Load(pSerializer);
                        m_roiBlock[nIndex].Attach(&m_ImageTmpBW8);
                }
        }

        m_vectPattern.clear();

        while(!pSerializer->IsEOS())
        {
                EMatch tmpX;
                tmpX.Load(pSerializer);
                m_vectPattern.push_back(tmpX);
        }

         }
        catch(const EAccessViolation &e)
        {
                //Application->MessageBox(e.Message.c_str(), "AddLog Exception",MB_OK);
                m_listLog.push_back("Load Tool"+e.Message);
        }
        
        pSerializer->Close();
        delete pSerializer;
}
//---------------------------------------------------------------------------

void __fastcall CEVision::SaveTool(char *strFileNmae,AnsiString strSch)
{

        return; //no need
        //m_frameShape.Save(strFileNmae,true);

        ESerializer *pSerializer = ESerializer::CreateFileWriter( strFileNmae, ESerializer::Overwrite);

        AnsiString strName="C:\\Product Image\\"+strSch+".bmp";
        m_ImageTmpBW8.Save(strName.c_str());

        try{
        //m_ImageTmpBW8.Save(pSerializer);
        for(int nIndex=0;nIndex<3;nIndex++)
        {
                m_markMatch[nIndex].Save(pSerializer);
                m_roiMarkPattern[nIndex].Save(pSerializer);
                m_roiMark[nIndex].Save(pSerializer);
        }

        for(int nIndex=0;nIndex<4;nIndex++)
        {
                m_roiBlock[nIndex].Save(pSerializer);
        }

        for(int nIndex=0;nIndex<m_vectPattern.size();nIndex++)
        {
                m_vectPattern[nIndex].Save(pSerializer);
        }
        }
        catch(const EAccessViolation &e)
        {
                //Application->MessageBox(e.Message.c_str(), "AddLog Exception",MB_OK);
                m_listLog.push_back("Save Tool"+e.Message);
        }

        pSerializer->Close();
        delete pSerializer;
}

//---------------------------------------------------------------------------
int __fastcall CEVision::DoMeasure(double *dGlueWidth,double dCCDRes,double dGlueWidthAccuracy,int nAllowLoseSamplePoint)
{
        int nRetNG=0;
        int nRetOK=0;
        ERectangleGauge *pGauge;

        m_rectAlignment.Process(&m_ImageTmpBW8);
        if(m_rectAlignment.GetNumValidSamples())
        {

                m_frameShape.SetCenter(m_rectAlignment.GetMeasuredRectangle().GetCenter());
                m_frameShape.SetAngle(m_rectAlignment.GetMeasuredRectangle().GetAngle());

                m_frameShape.Process(&m_ImageTmpBW8);

                for(int nIndex=0;nIndex<m_frameShape.GetNumDaughters();nIndex++)
                {
                        pGauge=(ERectangleGauge *)m_frameShape.GetDaughter(nIndex);
                        if(pGauge->GetNumValidSamples())
                        {
                                double dWidth=0;
                                if(pGauge->GetActiveEdges() &( INS_HANDLE_EDGE_x | INS_HANDLE_EDGE_X) )
                                        dWidth=pGauge->GetMeasuredRectangle().GetSizeX();
                                if(pGauge->GetActiveEdges() &( INS_HANDLE_EDGE_y | INS_HANDLE_EDGE_Y) )
                                        dWidth=pGauge->GetMeasuredRectangle().GetSizeY();

                                int nLostPoint=pGauge->GetNumSamples()-pGauge->GetNumValidSamples();

                                if(fabs(dWidth) < (dGlueWidth[nIndex]/dCCDRes+dGlueWidthAccuracy) &&
                                        fabs(dWidth) > (dGlueWidth[nIndex]/dCCDRes-dGlueWidthAccuracy) &&
                                        nLostPoint<=nAllowLoseSamplePoint)
                                        nRetOK++;
                                else nRetNG++;
                        }
                        else nRetNG++;

                }
        }
        else nRetNG++;

        return nRetNG>0 ? 0: 1;


}
//---------------------------------------------------------------------------
void __fastcall CEVision::RotateImage(double dDegree)
{
        try
        {
                if(dDegree==180)
                {
                        ImgScaleRotate(&m_ImageBW8,m_ImageBW8.GetWidth()/2,
                                m_ImageBW8.GetHeight()/2,m_ImageBW8.GetWidth()/2,
                                m_ImageBW8.GetHeight()/2, 1.f, 1.f, dDegree, &m_ImageTmpBW8, 0);
                }
                else if(dDegree!=0)        //---for center rotate
                {
                       ImgScaleRotate(&m_ImageBW8,m_ImageBW8.GetWidth()/2,
                                m_ImageBW8.GetHeight()/2,m_ImageTmpBW8.GetWidth()/2,
                                m_ImageTmpBW8.GetHeight()/2, 1.f, 1.f, dDegree, &m_ImageTmpBW8, 0);


                }
                else ImgScaleRotate(&m_ImageBW8,0,0,0,0, 1.f, 1.f, dDegree, &m_ImageTmpBW8, 0);
        }
        catch(const EAccessViolation &e)
        {
                //Application->MessageBox(e.Message.c_str(), "AddLog Exception",MB_OK);
                m_listLog.push_back("RotateImage"+e.Message);
        }
}

//---------------------------------------------------------
void __fastcall CEVision::LearnPattern(EROIBW8 &theROI)
{
 m_PatternFinder.Learn(theROI);

}
//---------------------------------------------------------
int __fastcall CEVision::FindPattern(EROIBW8 &theROI,double dScore,double dCount,double dAngle)
{
        m_PatternFinder.MinScore=dScore;
        m_PatternFinder.MaxInstances=dCount;
        m_PatternFinder.AngleTolerance=dAngle;
        m_PatternFound=m_PatternFinder.Find(theROI);

        return m_PatternFound.NbItems();
}
//---------------------------------------------------------
void __fastcall CEVision::DrawFoundPattern(HDC hDC)
{
        if( m_PatternFound.NbItems()>0)
        {
                for(int nIndex=0;nIndex<m_PatternFound.NbItems();nIndex++)
                        m_PatternFound[nIndex].Draw(hDC);
        }
}

//---------------------------------------------------------
void __fastcall CEVision::LearnPatMatch(EROIBW8 &theROI,EMatch &theMatch)
{
 theMatch.LearnPattern(&theROI);

}
//---------------------------------------------------------
int __fastcall CEVision::FindPatMatch(EROIBW8 &theROI,EMatch &theMatch)
{
        theMatch.Match(&theROI);
        return theMatch.GetNumPositions();
}
//---------------------------------------------------------
void __fastcall CEVision::DrawPatMatch(HDC hDC,EMatch &theMatch)
{
        theMatch.DrawPositions(hDC);
}
//---------------------------------------------------------
void __fastcall CEVision::SavePatMatch(char *strFileName,int nIndex,EMatch &theMatch)
{
         char drive[MAXDRIVE];
        char dir[MAXDIR];
        char file[MAXFILE];
        char ext[MAXEXT];
        int flags;

        flags=fnsplit(strFileName,drive,dir,file,ext);
        AnsiString strName;
        strName.sprintf("%s%s%s_%d.mch",drive,dir,file,nIndex);

        theMatch.Save( strName.c_str());
}
//---------------------------------------------------------
void __fastcall CEVision::LoadPatMatch(char *strFileName,int nIndex,EMatch &theMatch)
{
        char drive[MAXDRIVE];
        char dir[MAXDIR];
        char file[MAXFILE];
        char ext[MAXEXT];
        int flags;

        flags=fnsplit(strFileName,drive,dir,file,ext);
        AnsiString strName;
        strName.sprintf("%s%s%s_%d.mch",drive,dir,file,nIndex);

        theMatch.Load( strName.c_str());
}
//---------------------------------------------------------
double __fastcall CEVision::GetMatchPosX(int nIndex)
{
         if(m_markMatch[0].GetNumPositions()>0)
         {
                m_pMatchPos=m_markMatch[0].GetPosition(nIndex);
                return m_roiMark[0].GetOrgX()+m_pMatchPos->m_f32CenterX;
         }
         else return 0;
}
//---------------------------------------------------------
double __fastcall CEVision::GetMatchPosY(int nIndex)
{
         if(m_markMatch[0].GetNumPositions()>0)
         {
                m_pMatchPos=m_markMatch[0].GetPosition(nIndex);
                return m_roiMark[0].GetOrgY()+m_pMatchPos->m_f32CenterY;
         }
         else return 0;
}
//---------------------------------------------------------
double __fastcall CEVision::GetMatchPosX(EMatch &theMatch,EROIBW8 &theROI,int nIndex)
{
         if(theMatch.GetNumPositions()>0)
         {
                m_pMatchPos=theMatch.GetPosition(nIndex);
                return theROI.GetOrgX()+m_pMatchPos->m_f32CenterX;
         }
         else return 0;
}
//---------------------------------------------------------
double __fastcall CEVision::GetMatchPosY(EMatch &theMatch,EROIBW8 &theROI,int nIndex)
{
         if(theMatch.GetNumPositions()>0)
         {
                m_pMatchPos=theMatch.GetPosition(nIndex);
                return theROI.GetOrgY()+m_pMatchPos->m_f32CenterY;
         }
         else return 0;
}
//---------------------------------------------------------
double __fastcall CEVision::GetMatchScore(int nIndex)
{
         if(m_markMatch[0].GetNumPositions()>0)
         {
                m_pMatchPos=m_markMatch[0].GetPosition(nIndex);
                return m_pMatchPos->m_f32Score;
         }
         else return 0;
}
//---------------------------------------------------------
double __fastcall CEVision::GetMatchScore(EMatch &theMatch,int nIndex)
{
         if(theMatch.GetNumPositions()>0)
         {
                m_pMatchPos=theMatch.GetPosition(nIndex);
                return m_pMatchPos->m_f32Score;
         }
         else return 0;
}
//---------------------------------------------------------
void __fastcall CEVision::DrawAll(HDC hDC,int nGuideLineOffset)
{
        TCanvas *tempCanvas = new TCanvas;
        tempCanvas->Handle=hDC;

       m_ImageTmpBW8.Draw(tempCanvas->Handle,m_dScaleSizeX,m_dScaleSizeY);
       tempCanvas->Pen->Width=2;
       tempCanvas->Pen->Style=psSolid;
       tempCanvas->Pen->Color= clRed;

       if(m_bShowLayout)
          for(int nIndex=0;nIndex<m_vectRect.size();nIndex++)
          {
                tempCanvas->FrameRect(Rect(m_vectRect[nIndex].Left*m_dScaleSizeX,m_vectRect[nIndex].Top*m_dScaleSizeY,
                        m_vectRect[nIndex].Right*m_dScaleSizeX,m_vectRect[nIndex].Bottom*m_dScaleSizeY));
                tempCanvas->TextOutA( m_vectRect[nIndex].left*m_dScaleSizeX, m_vectRect[nIndex].top*m_dScaleSizeY ,IntToStr(nIndex+1));
          }

       tempCanvas->Pen->Color= clRed;
        if(m_bShowBlockROI[m_nCurrentRoiBlock])
        {
                m_roiBlock[m_nCurrentRoiBlock].DrawFrame(tempCanvas->Handle,E_FRAME_ON, TRUE,m_dScaleSizeX,m_dScaleSizeY);
                if(m_nCurrentRoiBlock>0)
                {
                        int nXXX=m_roiBlock[m_nCurrentRoiBlock-1].GetOrgX()+m_roiBlock[m_nCurrentRoiBlock-1].GetWidth()-nGuideLineOffset ;          //g_IniFile.m_nImageWidth
                        tempCanvas->MoveTo(nXXX*m_dScaleSizeX,0*m_dScaleSizeY);
                        tempCanvas->LineTo(nXXX*m_dScaleSizeX,m_ImageTmpBW8.GetHeight()*m_dScaleSizeY);
                }
        }

        for(int nIndex=0;nIndex<3;nIndex++)
        {
                tempCanvas->Pen->Color= clRed;
                if(m_bShowMarkROI[nIndex]) m_roiMark[nIndex].DrawFrame(tempCanvas->Handle,E_FRAME_ON, TRUE,m_dScaleSizeX,m_dScaleSizeY);

                tempCanvas->Pen->Color= clLime;
                if(m_bShowPatternROI[nIndex]) m_roiMarkPattern[nIndex].DrawFrame(tempCanvas->Handle,E_FRAME_ON, TRUE,m_dScaleSizeX,m_dScaleSizeY);

                if(m_bShowMatchResult[nIndex]) m_markMatch[nIndex].DrawPositions(tempCanvas->Handle,m_dScaleSizeX,m_dScaleSizeY);
        }
       
       if(m_bShowMatchResultAll)
       for(int nIndex=0;nIndex<m_vectPattern.size();nIndex++)
       {
               m_vectPattern[nIndex].DrawPositions(tempCanvas->Handle,m_dScaleSizeX,m_dScaleSizeY);
       }

       if(m_bShowMarkROI[2])
       {
        tempCanvas->Pen->Width=1;
        tempCanvas->Pen->Style=psDot;
        tempCanvas->Pen->Color=clRed;

        tempCanvas->MoveTo(320*m_dScaleSizeX,230*m_dScaleSizeY);
        tempCanvas->LineTo(320*m_dScaleSizeX,250*m_dScaleSizeY);
        tempCanvas->MoveTo(310*m_dScaleSizeX,240*m_dScaleSizeY);
        tempCanvas->LineTo(330*m_dScaleSizeX,240*m_dScaleSizeY);
        }

        
       delete tempCanvas;
}
//---------------------------------------------------------
void __fastcall CEVision::CreateMapArray(TRect &rect,int nPackageX,int nPackageY,int nDeviceGap,int nSectX,int nSectY)
{
        const int nGap=0;

        if(nSectX<=0 || nPackageX<=0 || nSectY<=0 || nPackageY<=0) return;

        //m_nLeftColCnt=nPackageX*nSectX;
        //m_nLeftRowCnt=nPackageY*nSectY;
        int nPitchX;
        int nPitchY;

        nPitchX=(rect.Width()-nDeviceGap*(nPackageX-1))/(nSectX*nPackageX);
        nPitchY=(rect.Height()-nDeviceGap*(nPackageY-1))/(nSectY*nPackageY);


        m_vectRect.clear();

        for(int nY=0;nY<nSectY*nPackageY;nY++)
        //for(int nX=0;nX<nSectX*nPackageX;nX++)
        for(int nX=nSectX*nPackageX-1;nX>=0;nX--)
        {
               m_vectRect.push_back(TRect(rect.right-nPitchX*nX-nPitchX-nGap-(nX/nSectX)*nDeviceGap ,rect.top+nPitchY*nY+nGap+(nY/nSectY)*nDeviceGap,
                        rect.right-nPitchX*nX-nGap-(nX/nSectX)*nDeviceGap,rect.top+nPitchY*nY+nPitchY-nGap+(nY/nSectY)*nDeviceGap));
        }
        
}
//---------------------------------------------------------
void __fastcall CEVision::MergeImage(int nIndex,int nGrabWidth,double m_dAngle)
{
        /*
        EImageBW8 A(748,484),B(748*2,484),B1(748*2,484),B2(748*2,484);
        //A.Load("C:\\Documents and Settings\\Administrator\\桌面\\Work\\20130528 C11 Image\\102418_1.bmp");
        A.Load("F:\\AAA.TIF");

        ImgScaleRotate(&A,324,242,324,242,1.f,1.f,0.0,&B1,0);
        ImgScaleRotate(&A,324,242,748+324,242,1.f,1.f,0.0,&B2,0);
        ImgOper(IMG_ADD,&B1,&B2,&B2);

        theVision.m_ImageTmpBW8.SetSize(748*2,484);
        ImgCopy(&B2,&theVision.m_ImageTmpBW8);
        */

        int nWidth=nGrabWidth;//400;
        int nHeight=m_ImageSizeY;
        int nOrgX=(m_ImageSizeX-nWidth)/2;    //124
        int nImageCount=4;

        //if(nIndex==0) ImgOper(IMG_XOR,&m_ImageADD,&m_ImageADD,&m_ImageADD);      //Clear Image

        m_roiADD.Attach(&m_ImageTmpBW8);    //m_ImageBW8
        m_roiADD.SetPlacement(nOrgX,0,nWidth,nHeight);

        m_ImageADD.SetSize(nWidth*nImageCount,nHeight);
        EImageBW8 Dest(nWidth*nImageCount,nHeight);
        ImgScaleRotate(&m_roiADD,nWidth/2,nHeight/2,nWidth/2+nWidth*nIndex,nHeight/2,1.f,1.f,m_dAngle,&Dest,4);  //0.5 degree

        if(nIndex==0) ImgOper(IMG_XOR,&m_ImageADD,&m_ImageADD,&m_ImageADD);      //Clear Image
        ImgOper(IMG_ADD,&Dest,&m_ImageADD,&m_ImageADD);

        if(nIndex==3)
        {

                //m_ImageTmpBW8.SetSize(nWidth*nImageCount,nHeight);
                //ImgCopy(&m_ImageADD,&m_ImageTmpBW8);
                ImgScaleRotate(&m_ImageADD,0,0,0,0, 1.f, 1.f, 0.0, &m_ImageTmpBW8, 0);
        }

        m_roiADD.Detach();

        //m_ImageADD,clear

}


