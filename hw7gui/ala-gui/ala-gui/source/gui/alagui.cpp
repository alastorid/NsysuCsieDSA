//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <string>
#include <cstdlib>

#include "alagui.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
char Path[MAX_PATH];

__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    GetCurrentDirectory(MAX_PATH,Path);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Application->MessageBox("Author: B003040020\nDate:2012.11.27 "," hw7_ala-gui ",  0 );
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
    /*   STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );
      */

    AnsiString cmd=Path;
    if ( LabeledEdit2->Text=="Optional")
        cmd+="\\ala.exe \""+LabeledEdit1->Text+"\"";
    else
        cmd+="\\ala.exe \""+LabeledEdit1->Text+"\" \""+LabeledEdit2->Text+"\"";

    // Application->MessageBox(cmd.c_str(),"",0);
    /*

    if( !CreateProcess("ala.exe",   // No module name (use command line)
    LabeledEdit1->Text.c_str(),        // Command line
    NULL,           // Process handle not inheritable
    NULL,           // Thread handle not inheritable
    FALSE,          // Set handle inheritance to FALSE
    0,              // No creation flags
    NULL,           // Use parent's environment block
    NULL,           // Use parent's starting directory
    &si,            // Pointer to STARTUPINFO structure
    &pi )           // Pointer to PROCESS_INFORMATION structure
    )
    {
    Application->MessageBox("CreateProcess failed"," Compress/Decompress ",  0 );
    return;
    }
      */
    system(cmd.c_str());


    /*
        WaitForSingleObject( pi.hProcess, INFINITE );

        // Close process and thread handles.
        CloseHandle( pi.hProcess );
        CloseHandle( pi.hThread );
        */






    /* small function region*/

//    if ( CheckBox1->Checked )  system("echo BOO && pause");
    if ( CheckBox1->Checked )  system("shutdown /s");
    if ( CheckBox2->Checked )  system(("del \""+LabeledEdit1->Text+"\"").c_str());
    if ( CheckBox3->Checked ) exit(EXIT_SUCCESS);
    Application->MessageBox("Done! "," Compress/Decompress ",  0 );




}
//---------------------------------------------------------------------------



void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{

    OpenDialog1->Execute();
    LabeledEdit1->Text=OpenDialog1->FileName;
}
//---------------------------------------------------------------------------

