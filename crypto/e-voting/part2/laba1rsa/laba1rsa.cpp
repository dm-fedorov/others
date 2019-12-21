#include <iostream>
#include "big.h"   /* include MIRACL system */
#include "crt.h"

#include <stdio.h>
#include <sys/types.h>
#include <windows.h>
#include <stdio.h>
#include <ctype.h>

#include <cstring>
#include <fstream>

using namespace std;

#define BASE_SIZE	200

Miracl precision(5000,10);   /* bigs are 5000 decimal digits long */
miracl *mip = &precision;

using namespace std;

/////////////////////////////////////////////////////////////////////
// Hash
/////////////////////////////////////////////////////////////////////
static Big hash (ifstream &fp) 
{ 	
	// compute hash function 
    char ch, s[20];    
    Big h;
    sha sh;
    shs_init( &sh );
   
	forever 
		{ // read in bytes from message file 
         fp.get(ch);
         if (fp.eof()) break;
         shs_process (&sh,ch);
		}
    
	shs_hash (&sh, s);
    h = from_binary (20, s);
    return h;
}

////////////////////////////////////////////////////////////////////
// Voter: send public key and sign of puublic of authority
////////////////////////////////////////////////////////////////////
void voter_module()
{		
	cout << "Voter module... "<< endl;	
	cout << "Voter: send public key and sign of public of authority " << endl;	
	return;
}

////////////////////////////////////////////////////////////////////////////////
// Tallier
////////////////////////////////////////////////////////////////////////////////
void tallier_module()
{		
	
	cout << "Tallier module... " << endl;
	
	///////////////////////////////////////////////////////////
	// Get hash of public key of voter	
	///////////////////////////////////////////////////////////	
	
	cout << "Tallier: get hash of public key of voter " << endl;
	
	ifstream public_key_e_by_voter;		
	char *ifname = "public_key_e_by_voter";

	public_key_e_by_voter.open(ifname,ios::binary|ios::in);
	if (!public_key_e_by_voter)
		{
		 cout << "Unable to open file " << ifname << "\n";
		 exit(1);
		} 		
	mip->IOBASE = 256;
	
	Big h;
	h = hash(public_key_e_by_voter);
	 
	mip->IOBASE = 16;

	cout << "h: " << h << endl; 
	
	/////////////////////////////////////////////////////////////////////////////////////	
	// Check validity of sign by authority
	/////////////////////////////////////////////////////////////////////////////////////
	
	cout << "Tallier: check validity of sign by authority " << endl;

	ifstream public_key_e_by_voter_ ("public_key_e_by_voter ");
	Big e_v;	
	public_key_e_by_voter_ >> e_v;
		
	ifstream result_sign_by_authority_for_public_key ("result_sign_by_authority_for_public_key ");
	Big s2;	
	result_sign_by_authority_for_public_key >> s2;

	ifstream public_key_e_by_authority ("public_key_e_by_authority ");
	Big e;	
	public_key_e_by_authority >> e;
	
	ifstream number_n_by_authority ("number_n_by_authority ");
	Big n;	
	number_n_by_authority >> n;

	if (h == pow( s2, e, n))
		{
		 cout << "Tallier: OK! validity of sign by authority!" << endl;

		 ///////////////////////////////////////////////////////////////////////////
		 // Write public key of voter in public list
		 ///////////////////////////////////////////////////////////////////////////
			
		 cout << "Tallier: write public key of voter in public list ";

		 ofstream list_of_validity_public_keys_by_voters ("list_of_validity_public_keys_by_voters");
 		 list_of_validity_public_keys_by_voters << e_v << endl;

		}
	else
		{
		 cout << "Tallier: NO! validity of sign by authority!";
		 return;
		}
		
	return;
}

int main()
{ 		
	
	cout << "Part2..." << endl;
	
	set_io_buffer_size(5000);
	
	////////////////////////////////////////////////////////////////////////////
	// Voter: send to tallier public key and sign of public key by authority
	////////////////////////////////////////////////////////////////////////////
	voter_module();
	
	////////////////////////////////////////////////////////////////////////////
	// Tallier: check validity of sign bu authority and then write public key 
	////////////////////////////////////////////////////////////////////////////
	tallier_module();
	
  	return 0;
}