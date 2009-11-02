#include <sys/types.h>
#include <string.h>
#include <stdint.h>
#include <dlfcn.h>

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

class CSharedLib
{

    void* m_Handle;
public:

    CSharedLib( const std::string& strFileName )
        {
            m_Handle = ::dlopen( strFileName.c_str(), RTLD_LAZY );
        }

    ~CSharedLib()
        {
            if( NULL != m_Handle )
                ::dlclose( m_Handle );
        }
    
    void* Get( const std::string& strFuncName )
        {
            if( NULL == m_Handle )
                throw std::runtime_error( "CSharedLib::Get: " + std::string( ::dlerror() ) );
            
            return ::dlsym( m_Handle, strFuncName.c_str() );
        }
};

#define kgERROR_SUCCESS             0
#define kgERROR_KG_ERROR            2
#define kgERROR_MODE_UNKNOWN        3
#define kgERROR_REGNAME_ERROR       4
#define kgERROR_SIGNATURE_ERROR     5
#define kgERROR_BUFFER_TOO_SMALL    6
#define kgERROR_CONSTANTS_UNDEFINED 7
#define kgERROR_HARDWAREID_ERROR    8

typedef unsigned char BYTE;
typedef uint16_t WORD;
typedef char* LPSTR;
typedef uint32_t DWORD;

typedef struct _KEYDATE {
	BYTE	Day;
	BYTE	Month;
	WORD	Year;
} KEYDATE, *PKEYDATE;

typedef struct _PARAMS {
    LPSTR   RegName;            // Registration name buffer

    LPSTR   HardwareID;         // HardwareID
    KEYDATE ExpirationDate;     // Expiration date
    DWORD   EncryptionConst;    // Constant for encryption

    BYTE    ModeID;             // Mode number (1..15)
    BYTE    SignatureBits;      // Signature size in bits

	BYTE	Reserved1;
	BYTE	Reserved2;

    LPSTR   C1;                 // Constants from project file
    LPSTR   C3;		    // (Activation Keys section)
    LPSTR   C6;
    LPSTR   C7;

	LPSTR   RegKey;             // Registration key buffer
	DWORD   RegKeySize;         // Key buffer size
	DWORD   RealKeySize;        // Registration key size
} PARAMS, *PPARAMS;

typedef DWORD( *ASPRegistrationKeyGenerate)(PARAMS *Params);

int main( int argc, char** argv )
{
    try
    {
        if( argc != 3 )
            throw std::runtime_error( "Wrong number of arguments, should be 2" );

        CSharedLib lib( "./libkeygen.so" );

        ASPRegistrationKeyGenerate RegFunc = (ASPRegistrationKeyGenerate)lib.Get( "RegistrationKeyGenerate" );

        PARAMS Params;
        ::memset( &Params, 0, sizeof(PARAMS) );
        Params.RegName = argv[1];
        Params.ModeID  = 1;
        Params.EncryptionConst = 617478370;
        Params.HardwareID      = argv[2];
        Params.SignatureBits   = 160;
        Params.C1 = (char*)"9EE9098E3E6D9709B4673A89C7";
        Params.C3 = (char*)"360EDD8422DE272D2FF684C203D";
        Params.C6 = (char*)"4AD5C817ED8EEC6DAF04567D63F720B8AA08B20CD3690B879F62B40EB64C9E76982D90D6E6C071A34D2FC99C9DE7079E35C12ECF9F1BAF6B858DF48993001DD7D52F71D4C9EAAD503B611E7DFC11F4C753C1756F26F85554F50DE7FFFD35F4F3F02F6D39D1E48C555C812E38E83E328E015264B5C9860A7F1CB32B9E40AF3384";
        Params.C7 = (char*)"8D5238B995880F81722AE0853E3C6B6C59B74206B284C254BE01F59A4D098C939171C531EAEC2FA7AC0FAA1B08CDC4EFA7A4898BB14B2B11AE2970656D1A766237ED2BFB208267E20CBE74EE7D3549EE37DB594052DDA64D8A0BFB1803BF6000E3DAD4ED048DDF1DFBBD5581B57DE36F27ECCC1BE9D906742A753251770294D7";

        std::vector<unsigned char> vecKey(256);
        Params.RegKey = (LPSTR)&vecKey[0];
        Params.RegKeySize = vecKey.size();

        if( RegFunc(&Params) != kgERROR_SUCCESS )
            throw std::runtime_error( "Registration failed" );

        std::string strKey( vecKey.begin(), vecKey.begin() + Params.RealKeySize );
        std::cout << strKey << std::endl;
    }
    catch( std::exception& e )
    {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

