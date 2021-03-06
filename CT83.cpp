//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("fmMain.cpp", frmMain);
USEFORM("fmChoiceMotor.cpp", frmChoiceMotor);
USEFORM("fmIOCheck.cpp", IOCheckDlg);
USEFORM("fmMotorCheck.cpp", frmMotorCheck);
USEFORM("fmPassword.cpp", frmPassword);
USEFORM("frmPrivilege.cpp", fmPrivilege);
USEFORM("fmMachinParam.cpp", frmMachineParam);
USEFORM("fmProductParam.cpp", frmProductParam);
USEFORM("frmManual.cpp", fmManual);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->CreateForm(__classid(TfmManual), &fmManual);
         Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
