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

///////////////////////////////////////////////////////////////////////
// Mask
///////////////////////////////////////////////////////////////////////
Big doC1 (Big e, Big n, Big m) 
{	
	ofstream random_number_by_voter ("secret_random_number_by_voter");
	
	Big al; // random number
	
	do {
		al = rand();
	}while ( gcd(al, n) != 1 );
	
	random_number_by_voter << al << endl;
	
	Big ll = pow( al, e, n );
	Big lll = ll * m;
		
	return pow(lll, 1, n);
}

Big doB (Big d, Big n, Big m1) 
{
	return pow(m1, d, n);
}

Big doC2 (Big n, Big s1) 
{
	Big al; // random number
	
	ifstream random_number_by_voter ("secret_random_number_by_voter");

	random_number_by_voter >> al;
	
	return pow(s1*inverse(al, n), 1, n);
}

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
// Voter
////////////////////////////////////////////////////////////////////
void voter_module( int state_flag )
{			
	// State 1
	if( state_flag == 0)
		{		 
		 
		 cout << "Voter module (state 1)..." << endl;
		
		 ///////////////////////////////////////////////////////////
		 // Get hash of public key of voter	
		 ///////////////////////////////////////////////////////////
		 
		 cout << "Voter: get hash of public key of voter... " << endl;
		 
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
		 		 
		 ////////////////////////////////////////////////////////////////
		 // Mask public key of voter for send to authority
		 ////////////////////////////////////////////////////////////////
		 
		 cout << "Voter: mask public key of voter for send to authority... " << endl;
		 
		 ifstream number_n_by_authority ("number_n_by_authority");	
		 ifstream public_key_e_by_authority ("public_key_e_by_authority");	
	 			
		 Big s, n, e;
	 
	 	 number_n_by_authority >> n;
		 public_key_e_by_authority >> e;
		 
		 mip->IOBASE = 16;
		 
		 //cout << "n = " << n << endl;
		 //cout << "e = " << e << endl;
	 	
		 s = doC1 (e, n, h);	

		 ofstream mask_public_key_of_voter_tmp ("mask_public_key_of_voter_tmp");
		 mask_public_key_of_voter_tmp << s << endl;
		 
		 cout << "s: " << s << endl;

		 return;
		}
	// State 2	
	else
		{	 
		 cout << "Voter module (state 2)..." << endl;	
		
		 Big n, e;

		 ifstream number_n_by_authority ("number_n_by_authority");	
		 ifstream public_key_e_by_authority ("public_key_e_by_authority");	
	 	 
	 	 mip->IOBASE = 16;
		 
		 number_n_by_authority >> n;
		 public_key_e_by_authority >> e;
		 				
		 Big s, s1, s2;
		 
		 ifstream mask_public_key_of_voter_tmp ("mask_public_key_of_voter_tmp");		 	
		 ifstream sign_mask_public_key_by_authority_tmp ("sign_mask_public_key_by_authority_tmp");
				 
		 mask_public_key_of_voter_tmp >> s;
		 sign_mask_public_key_by_authority_tmp >> s1;
		 
		 ////////////////////////////////////////////////////////////////
		 // Check sign bu authority
		 ////////////////////////////////////////////////////////////////

		 cout << "Voter: Check sign bu authority" << endl;	

		 if (pow (s1, e, n) == pow (s, 1, n))
			cout << "Voter: OK! sign by Authority!" << endl;
		 else 
			{
			 cout << "Voter: NO! sign by Authority!" << endl;
			 return;
			}
		 
		 ///////////////////////////////////////////////////////////////////////
		 // Remove mask and get sign of authority for public key by voter	
		 ///////////////////////////////////////////////////////////////////////
	 	 
		 cout << "Voter: remove mask and get sign of authority for public key by voter" << endl;
		 
		 s2 = doC2( n, s1 );
		 
		 cout << "s2: " << s2 << endl;

		 ofstream result_sign_by_authority_for_public_key ("result_sign_by_authority_for_public_key"); 
		 result_sign_by_authority_for_public_key << s2 << endl;

		 return;
		}
}

////////////////////////////////////////////////////////////////////////////////
// Authority
////////////////////////////////////////////////////////////////////////////////
void authority_module()
{
	
	cout << "Authority module... " << endl;
	
	ifstream number_n_by_authority ("number_n_by_authority");	
	ifstream private_key_d_by_authority ("private_key_d_by_authority");	
	
    Big n, d;
	
 	number_n_by_authority >> n;
	private_key_d_by_authority >> d;
		 
	mip->IOBASE = 16;
		
	////////////////////////////////////////////////////////////////////////////
	// Check validity of voter (not declare!)
	////////////////////////////////////////////////////////////////////////////
	cout << "Authority: check validity of voter (not declare!) " << endl;
	
	Big s;
	ifstream mask_public_key_of_voter_tmp ("mask_public_key_of_voter_tmp");	    			 
	mask_public_key_of_voter_tmp >> s;
	
	////////////////////////////////////////////////////////////////////////////
	// Sign of mask public key by voter
	////////////////////////////////////////////////////////////////////////////
	
	cout << "Authority: sign of mask public key by voter " << endl;

	ofstream sign_mask_public_key_by_authority_tmp ("sign_mask_public_key_by_authority_tmp");	
	Big s2 = doB (d, n, s);	
	sign_mask_public_key_by_authority_tmp << s2 << endl;
	
	cout << "s2: " << s2 << endl;	

	return;
}

int main()
{ 		
	cout << endl << "Part1..." << endl;
	
	int state_flag = 0;

	set_io_buffer_size(5000);
	
	////////////////////////////////////////////////////////////////////////////
	// Voter: mask public key of voter
	////////////////////////////////////////////////////////////////////////////
	voter_module( state_flag );
	state_flag++;

	////////////////////////////////////////////////////////////////////////////
	// Authority: sign mask public key of voter
	////////////////////////////////////////////////////////////////////////////
	authority_module();

	////////////////////////////////////////////////////////////////////////////
	// Voter: remove mask and get sign public key of voter
	////////////////////////////////////////////////////////////////////////////
	voter_module( state_flag );

  	return 0;
}