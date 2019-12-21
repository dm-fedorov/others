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
// Voter: 
////////////////////////////////////////////////////////////////////
void voter_module( int flag_state )
{			
	if( flag_state == 0 ) 
		{		 
		 cout << "Voter module (stage 1)... " << endl;
		
		 ////////////////////////////////////////////////////////////////	
		 // Get AES-ciphertext (Kv(Bv)) of voter's ballot on (Kv) key
		 ////////////////////////////////////////////////////////////////

		 ofstream aes_ballot ("aes_ballot"); 	
		 mip->IOBASE = 256;
		 // get AES-key		 		 
		 // get AES-ciphertext
		 Big kv_bv = "A38E3080CE4A7630E5C1EFCA48A3DF116DE277C574A259498E772BCDCFA0AA798011259374B";
		 mip->IOBASE = 16;
		 aes_ballot << kv_bv << endl;
	
		 cout << "Voter: AES-ciphertext of voter's ballot: " << kv_bv << endl;

		 ///////////////////////////////////////////////////////////
		 // Get hash of AES-ciphertext rof voter's ballot	
		 ///////////////////////////////////////////////////////////
		 
		 ifstream aes_ballot_;		
		 char *ifname = "aes_ballot";

		 aes_ballot_.open(ifname,ios::binary|ios::in);
		 if (!aes_ballot_)
			{
			 cout << "Unable to open file " << ifname << "\n";
			 exit(1);
			} 		
		 mip->IOBASE = 256;
		
	 	 Big h;
		 h = hash(aes_ballot_);
		 
	 	 mip->IOBASE = 16;
		 
		 cout << "Voter: hash of AES-ciphertext of voter's ballot: " << h << endl;
			
		 ///////////////////////////////////////////////////////////
		 // Sign of hash of AES-ciphertext	
		 ///////////////////////////////////////////////////////////

		 ifstream private_key_d_by_voter ("private_key_d_by_voter");
		 Big d_v;	
		 private_key_d_by_voter >> d_v;

	 	 ifstream number_n_by_voter ("number_n_by_voter");
		 Big n_v;	
		 number_n_by_voter >> n_v;
		
		 Big sign_hash_aes = pow (h, d_v, n_v);

		 cout << "Voter: Sign hash of AES-ciphertext of voter's ballot: " << sign_hash_aes << endl;		 

		 mip->IOBASE = 16;		

		 ofstream sign_hash_aes_by_voter ("sign_hash_aes_by_voter");
 		 sign_hash_aes_by_voter << sign_hash_aes << endl;
	
		 return;
		}
	else
		{		 
		 cout << "Voter module (stage 2)... " << endl;
		
		 ifstream list_with_ballots_voters ("list_with_ballots_voters");
		 Big list_e_v;	
		 list_with_ballots_voters >> list_e_v;
		
		 ifstream private_key_d_by_voter ("public_key_e_by_voter");
		 Big e_v;	
		 private_key_d_by_voter >> e_v;

		 ///////////////////////////////////////////////////////////
		 // Check data of voter in public list 	
		 ///////////////////////////////////////////////////////////

		 cout << "Voter: check data of voter in public list " << endl;
		 		 
		 if (list_e_v == e_v)
			{
			 cout << "Voter: OK! take info about voter!" << endl;

			 ///////////////////////////////////////////////////////////
			 // Get hash of AES key	
			 ///////////////////////////////////////////////////////////
		 
			 cout << "Voter: get hash of AES key..." << endl;

			 ifstream symmetric_key_by_voter;		
			 char *ifname = "symmetric_key_by_voter";

			 symmetric_key_by_voter.open(ifname,ios::binary|ios::in);
			 if (!symmetric_key_by_voter)
				{
				 cout << "Unable to open file " << ifname << "\n";
				 exit(1);
				} 		
			 mip->IOBASE = 256;
	 		
			 Big h;
			 h = hash( symmetric_key_by_voter );
		 
	 		 mip->IOBASE = 16;
				
			 ///////////////////////////////////////////////////////////
			 // Sign of hash of AES-key	
			 ///////////////////////////////////////////////////////////

			 cout << "Voter: sign of hash of AES-key..." << endl;			 

			 ifstream private_key_d_by_voter ("private_key_d_by_voter");
			 Big d_v;	
			 private_key_d_by_voter >> d_v;

	 		 ifstream number_n_by_voter ("number_n_by_voter");
			 Big n_v;	
			 number_n_by_voter >> n_v;
		
			 Big sign_key_hash_aes = pow (h, d_v, n_v);

			 ofstream sign_hash_key_aes_by_voter ("sign_hash_key_aes_by_voter");
 			 sign_hash_key_aes_by_voter << sign_key_hash_aes << endl;
			 			 			 
			 return;
			}
			else
			{
			 cout << "Voter: NO! take info about voter!" << endl;
			 return;
			}
		 return;
		}	
}

////////////////////////////////////////////////////////////////////////////////
// Tallier
////////////////////////////////////////////////////////////////////////////////
void tallier_module( int flag_state )
{	
	if (flag_state == 0)
		{
		 cout << "Tallier module (stage 1)... " << endl; 	
		 
		 ifstream list_of_validity_public_keys_by_voters ("list_of_validity_public_keys_by_voters");
		 Big list_e_v;	
		 list_of_validity_public_keys_by_voters >> list_e_v;
		 
	 	 ifstream public_key_e_by_voter ("public_key_e_by_voter");
		 Big e_v;	
		 public_key_e_by_voter >> e_v;

		 /////////////////////////////////////////////////////////////////////////////////
		 // Check validity of public key
		 /////////////////////////////////////////////////////////////////////////////////

		 cout << "Tallier: check validity of public key " << endl; 

		 if (list_e_v == e_v) 
			{
			 cout << "Tallier: OK! Validity public key and validity voter!" << endl;
			 			 
			 ///////////////////////////////////////////////////////////
			 // Get hash of AES-ciphertext of voter's ballot	
			 ///////////////////////////////////////////////////////////	

			 cout << "Tallier: get hash of AES-ciphertext of voter's ballot... " << endl; 

			 ifstream aes_ballot_;		
			 char *ifname = "aes_ballot";

			 aes_ballot_.open(ifname,ios::binary|ios::in);
			 if (!aes_ballot_)
				{
				 cout << "Unable to open file " << ifname << "\n";
				 exit(1);
				} 		
			 mip->IOBASE = 256;
	 		
	 		 Big h;
			 h = hash(aes_ballot_);
		 
	 		 mip->IOBASE = 16;	
			
			 cout << "Tallier: hash of AES-ciphertext of voter's ballot: " << h << endl; 
			 
			 /////////////////////////////////////////////////////////////////////////////////
			 // Check validity of sign by voter
			 ///////////////////////////////////////////////////////////////////////////////// 	
			 
			 cout << "Tallier: check validity of sign by voter... " << endl; 
			 
			 ifstream sign_hash_aes_by_voter ("sign_hash_aes_by_voter");
			 Big sign_aes;	
			 sign_hash_aes_by_voter >> sign_aes;
	 		 
			 ifstream public_key_e_by_voter ("public_key_e_by_voter");
			 Big e_v;	
			 public_key_e_by_voter >> e_v;

	 		 ifstream number_n_by_voter ("number_n_by_voter");
			 Big n_v;	
			 number_n_by_voter >> n_v;

			 mip->IOBASE = 16;

			 if (h == pow( sign_aes, e_v, n_v ))
				{
				 cout << "Tallier: OK! Validity sign of voter!" << endl;

				 //////////////////////////////////////////////////////////
				 // Write data about voter in public list
				 //////////////////////////////////////////////////////////		
				 
				 cout << "Tallier: write data about voter in public list... " << endl; 

				 ifstream _aes_ballot_ ("aes_ballot");
				 Big aes_ballot_voter;	
				 _aes_ballot_ >> aes_ballot_voter;								 
						 
				 ofstream list_with_ballots_voters ("list_with_ballots_voters");
 				 list_with_ballots_voters << e_v << endl << aes_ballot_voter << endl << sign_aes << endl;
			 		
				 return;
				}
			 else
				{
				 cout << "Tallier: NO! validity sign of voter!" << endl;	
				 cout << "Dump:" << endl;
				 cout << "h: " << h << endl;
				 cout << "sign_aes: " << sign_aes << endl;
				 cout << "e_v: " << e_v << endl;
				 cout << "n_v: " << n_v << endl;
				 cout << "pow( sign_aes, e_v, n_v ) " << pow( sign_aes, e_v, n_v ) << endl;
				 					
				 return;
				}		 
			}
		 else
			{
			 cout << "Tallier: NO! validity public key!" << endl;
			 return;
			}
		
		 return;
		}
	else
		{
		 cout << "Tallier module (stage 2)... " << endl;
		
		 ///////////////////////////////////////////////////////////
		 // Get hash of AES key	
		 ///////////////////////////////////////////////////////////
		 
		 cout << "Tallier: get hash of AES key..." << endl;

		 ifstream symmetric_key_by_voter;		
		 char *ifname = "symmetric_key_by_voter";

		 symmetric_key_by_voter.open(ifname,ios::binary|ios::in);
		 if (!symmetric_key_by_voter)
			{
			 cout << "Unable to open file " << ifname << "\n";
			 exit(1);
			} 		
		 mip->IOBASE = 256;
	 	 
		 Big h;
		 h = hash( symmetric_key_by_voter );
		 
	 	 mip->IOBASE = 16;
				
		 /////////////////////////////////////////////////////////////////////////////////
		 // Check validity of sign by voter
		 ///////////////////////////////////////////////////////////////////////////////// 	
		 
		 cout << "Tallier: check validity of sign by voter..." << endl;

		 ifstream sign_hash_key_aes_by_voter ("sign_hash_key_aes_by_voter");
		 Big sign_aes_key;	
		 sign_hash_key_aes_by_voter >> sign_aes_key;	
				 
		 ifstream public_key_e_by_voter ("public_key_e_by_voter");
		 Big e_v;	
		 public_key_e_by_voter >> e_v;

	 	 ifstream number_n_by_voter ("number_n_by_voter");
		 Big n_v;	
		 number_n_by_voter >> n_v;		 
		 
		 if (h == pow( sign_aes_key, e_v, n_v))		 
			{
			 cout << "Tallier: validity sign of aes key by voter!" << endl;	

			 // Decode AES-ciphertext and write in public list!
			 return;

			}
		 else
			{
		     cout << "Tallier: NO! validity sign of aes key by voter!" << endl;
			 return; 
			}

		 return;
		}
}

int main()
{ 		
	int state = 0;
	
	set_io_buffer_size(5000);
	
	cout << "Part3... " << endl;
	
	////////////////////////////////////////////////////////////////////////////
	// Voter: 
	////////////////////////////////////////////////////////////////////////////
	voter_module( state );
	
	////////////////////////////////////////////////////////////////////////////
	// Tallier: 
	////////////////////////////////////////////////////////////////////////////
	tallier_module( state );
	state++;

	////////////////////////////////////////////////////////////////////////////
	// Voter: 
	////////////////////////////////////////////////////////////////////////////
	voter_module( state );
	
	////////////////////////////////////////////////////////////////////////////
	// Tallier: 
	////////////////////////////////////////////////////////////////////////////
	tallier_module( state );

  	return 0;
}