//---------------------------------------------------------------------------

#ifndef frmPrivilegeH
#define frmPrivilegeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfmPrivilege : public TForm
{
__published:	// IDE-managed Components
    TBitBtn *btnOperator;
    TBitBtn *btnEngineer;
    TBitBtn *btnAllring;
    TBitBtn *btnChangePassword;
    TBitBtn *BitBtn1;
private:	// User declarations
public:		// User declarations
    __fastcall TfmPrivilege(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfmPrivilege *fmPrivilege;
//---------------------------------------------------------------------------
#endif
