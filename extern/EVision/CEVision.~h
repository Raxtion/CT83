//---------------------------------------------------------------------------

#ifndef CEVisionH
#define CEVisionH
//---------------------------------------------------------------------------
#include "Easy.h"
#include "EMatch.h"
#include "EFind.h"
#include "EGauge.h"
#include "EMatrixCode.h"
#include <vector>
#include <list>
//#include "EImage.h"  

//---------------------------------------------------------------------------
class CEVision
{
public:
        __fastcall CEVision();
        __fastcall ~CEVision();

        void __fastcall Init();
        void __fastcall AddRectGauge();
        void __fastcall DeleteGauge(int nIndex);

        void __fastcall SaveTool(char *strFileNmae,AnsiString strSch);
        void __fastcall LoadTool(char *strFileName,AnsiString strSch,bool bFileType=false);     //false: image include true: image not include

        int __fastcall DoMeasure(double *dGlueWidth,double dCCDRes,double dGlueWidthAccuracy,int nAllowLoseSamplePoint); //pixel

         void __fastcall RotateImage(double dDegree);

          //eVision
        void __fastcall LearnPattern(EROIBW8 &theROI);
        int __fastcall FindPattern(EROIBW8 &theROI,double dScore,double dCount,double dAngle);
        void __fastcall DrawFoundPattern(HDC hDC);
        //void __fastcall SavePattern(char *);

        void __fastcall LearnPatMatch(EROIBW8 &theROI,EMatch &theMatch);
        int __fastcall FindPatMatch(EROIBW8 &theROI,EMatch &theMatch);
        void __fastcall DrawPatMatch(HDC hDC,EMatch &theMatch);
        void __fastcall SavePatMatch(char *strFileName,int nIndex,EMatch &theMatch);
        void __fastcall LoadPatMatch(char *strFileName,int nindex,EMatch &theMatch);
        double __fastcall GetMatchPosX(int nIndex=0);         //m_markMatch[0]
        double __fastcall GetMatchPosY(int nIndex=0);
        double __fastcall GetMatchScore(int nIndex=0);
        double __fastcall GetMatchPosX(EMatch &theMatch,EROIBW8 &theROI,int nIndex=0);
        double __fastcall GetMatchPosY(EMatch &theMatch,EROIBW8 &theROI,int nIndex=0);
        double __fastcall GetMatchScore(EMatch &theMatch,int nIndex=0);

        void __fastcall SetScaleSize(double dX,double dY){m_dScaleSizeX=dX;m_dScaleSizeY=dY;};
        void __fastcall IncScaleSize(){m_dScaleSizeX+=0.1;m_dScaleSizeY+=0.1;};
        void __fastcall DecScaleSize(){m_dScaleSizeX-=0.1;m_dScaleSizeY-=0.1;};
        void __fastcall DrawAll(HDC hDC,int nGuideLineOffset);

        void __fastcall CreateMapArray(TRect &rect,int nPackageX,int nPackageY,int nDeviceGap,int nSectX,int nSectY);
        void __fastcall MergeImage(int nIndex,int nGrabWidth,double m_dAngle); //start fron 0

public:
        double m_dMMperPixel;
        //Euresys
        INT32 m_ImageSizeX;
        INT32 m_ImageSizeY;
        INT32 m_PixelSize;
        PUINT8 m_ImageBuffer;   //for painting
        //eVision
        EImageBW8 m_ImageBW8;
        EImageBW8 m_ImageTmpBW8;         // m_ImageBW8-->rotate--> m_ImageTmpBW8-->process
        EImageBW8 m_ImageADD;
        //EROIBW8 m_roiLeft;
        EROIBW8 m_roiMark[3];              //Save 1       0:NG Mark 1:FlipFlop 2:Fiducial Mark for Laser
        EROIBW8 m_roiMarkPattern[3];       //Save 2
        EMatch m_markMatch[3];             //Save 3
        EROIBW8 m_roiBlock[4];

        int m_nCurrentRoiBlock;




        EROIBW8 m_roiADD;              //for Merge Image


        enum E_HANDLES m_eHandle;

        double m_dScaleSizeX;
        double m_dScaleSizeY;

        bool m_bShowLayout;
        bool m_bShowMarkROI[3];
        bool m_bShowBlockROI[4];
        bool m_bShowPatternROI[3];
        bool m_bShowMatchResult[3];
        bool m_bShowMatchResultAll;


        PatternFinder m_PatternFinder;  //PatternFinder class instance
        Utils::Vector<FoundPattern> m_PatternFound;

        EMatchPosition *m_pMatchPos;

        std::vector<EMatch> m_vectPattern;



        //----------
        //EWorldShape m_WorldShape;
        EFrameShape m_frameShape;
        ERectangleGauge m_rectAlignment;

        //---------
        MatrixCodeReader m_MatrixCodeReader;  // MatrixCodeReader class instance
        MatrixCode m_MatrixCode;  // MatrixCode class instance

        bool bInitial;

        std::vector<TRect> m_vectRect;  //for package  ROI
        std::list<AnsiString> m_listLog;
};
#endif
