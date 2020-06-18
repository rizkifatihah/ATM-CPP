//***************************************************************
//                   FILE HEADER YANG DIGUNAKAN
//****************************************************************

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//***************************************************************
//                   CLASS YANG DIGUNAKAN
//****************************************************************


class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
	int password;
	int acnotransfer;
public:
	void create_account();	//FUNGSI UNTUK MEMBUAT INPUT DATA USER BARU 
	void show_account() const;	//FUNGSI UNTUK MENAMPILKAN DATA USER
	void modify();	//FUNGSI UNTUK MERUBAH DATA
	void dep(int);	//FUNGSI UNTUK DEPOSIT
	void draw(int);	//FUNGSI UNTUK TARIK TUNAI
	int retacno() const;	//FUNGSI UNTUK MENGEMBALIKAN NILAI DARI NOREK 
	int retdeposit() const;	//FUNGSI UNTUK MENGEMBALIKAN NILAI DARI SALDO
	int retpassword() const;	//FUNGSI UNTUK MENGEMBALIKAN NILAI DARI PASSWORD
	void write_account();	//FUNGSI UNTUK MENYIMPAN DATA AKUN DI FILE
	void display_sp(int,int);	//FUNGSI UNTUK MENAMPILKAN DATA USER SESUAI NOREK DAN PASSWORD
	void modify_account(int,int);	//FUNGSI UNTUK MENGUBAH DATA USER SESUAI NOREK DAN PASSWORD
	void delete_account(int,int);	//FUNGSI UNTUK MENGHAPUS DATA USER SESUAI NOREK DAN PASSWORD
	void deposit_withdraw(int, int,int); // FUNGSI UNTUK TRANSFER/DEPOSIT/PENARIKAN TUNAI
	int intro();	//TAMPILAN AWAL
	int screen(int,int);
};         

void account::create_account()
{
	cout<<"\nMasukan Nomor Rekening. :";
	cin>>acno;
	cout<<"\nMasukan Password. :";
	cin>>password;
	cout<<"\n\nMasukan Nama Pemegang Akun. : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nMasukan Jumlah Deposit Awal. : ";
	cin>>deposit;
	cout<<"\n\n\nAkun Berhasil Dibuat..";
}

void account::show_account() const
{
	cout<<"\nNomor Rekening. : "<<acno;
	cout<<"\nPassword :"<<password;
	cout<<"\nNama Pemegang Akun : ";
	cout<<name;
	cout<<"\nJumlah Saldo : "<<deposit;
}


void account::modify()
{
	cout<<"\nNomor Rekening. : "<<acno;
	cout<<"\nUbah Nama Pemegang Akun. : ";
	cin.ignore();
	cin.getline(name,50);
}

	
void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
	
int account::retacno() const
{
	return acno;
}

int account::retpassword() const
{
	return password;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


//***************************************************************
//    	DEKLARASI FUNGSI
//****************************************************************


//***************************************************************
//    	FUNGSI UTAMA PROGRAM
//****************************************************************

int main(){
	account ATM;
	ATM.intro();
	
	return 0;
}

int account::screen(int acno,int password)
{
	char ch;
	int num;
	do
	{
		system("cls");
		cout<<"\n\n\n\tMENU UTAMA";
		cout<<"\n\n\t01. DEPOSIT";
		cout<<"\n\n\t02. TARIK TUNAI";
		cout<<"\n\n\t03. CEK SALDO";
		cout<<"\n\n\t04. TRANSFER";
		cout<<"\n\n\t05. TUTUP AKUN";
		cout<<"\n\n\t06. UBAH AKUN";
		cout<<"\n\n\t07. KELUAR";
		cout<<"\n\n\tPilih Menu (1-7) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			deposit_withdraw(acno,password, 1);
			break;
		case '2':
			deposit_withdraw(acno,password, 2);
			break;
		case '3': 
			display_sp(acno,password);
			break;
		case '4':
			deposit_withdraw(acno,password, 3);
			break;
		case '5':
			delete_account(acno,password);
			break;
		 case '6':
			modify_account(acno,password);
			break;
		 case '7':
			cout<<"\n\n\tTERIMA KASIH TELAH MENGGUNAKAN SISTEM KAMI";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='7');
	return 0 ;
}


//***************************************************************
//    	FUNGSI UNTUK MENULIS FILE
//****************************************************************

void account::write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("akun.txt",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	FUNGSI UNTUK MEMBACA DATA DI FILE
//****************************************************************

void account::display_sp(int acno,int password)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("akun.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File tidak bisa dibuka !! Silahkan tekan apa saja...";
		return;
	}
	cout<<"\nDATA SALDO\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==acno and ac.retpassword() == password)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nNomor Rekening tidak ada";
}


//***************************************************************
//    	FUNGSI UNTUK MERUBAH DATA AKUN
//****************************************************************

void account::modify_account(int acno,int password)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("akun.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File tidak bisa dibuka !! Silahkan tekan apa saja...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()== acno and ac.retpassword()==password)
		{
			ac.show_account();
			cout<<"\n\nMasukan Detail Terbaru"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Berhasil Diubah";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Data tidak ditemukan ";
}

//***************************************************************
//    	FUNGSI UNTUK MENGHAPUS DATA DI FILE
//****************************************************************


void account::delete_account(int acno,int password)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("akun.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File tidak bisa dibuka !! Silahkan tekan apa saja...";
		return;
	}
	outFile.open("Temp.txt",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==acno and ac.retpassword()==password)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("akun.txt");
	rename("Temp.txt","akun.txt");
	cout<<"\n\n\t Data Dihapus ..";
}

//***************************************************************
//    	FUNGSI UNTUK DEPOSIT, TARIK TUNAI DAN TRANSFER
//****************************************************************

void account::deposit_withdraw(int acno,int password, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("akun.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File tidak bisa dibuka !! Silahkan tekan apa saja...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()== acno and ac.retpassword()==password)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tMENU DEPOSIT ";
				cout<<"\n\nMasukan Jumlah Yang Ingin Di Deposit Kan";
				cin>>amt;
				ac.dep(amt);
				int pos=(-1)*static_cast<int>(sizeof(ac));
				File.seekp(pos,ios::cur);
				File.write(reinterpret_cast<char *> (&ac), sizeof(account));
				cout<<"\n\n\t Berhasil Dimasukan";
				found=true;
			}
			if(option==2)
			{
				cout<<"\n\n\tMENU TARIK TUNAI ";
				cout<<"\n\nMasukan Jumlah Yang Ingin Di Tarik";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(ac.retdeposit() < amt)
					cout<<"Saldo Tidak Cukup";
				else
					ac.draw(amt);
					int pos=(-1)*static_cast<int>(sizeof(ac));
					File.seekp(pos,ios::cur);
					File.write(reinterpret_cast<char *> (&ac), sizeof(account));
					cout<<"\n\n\t Berhasil Di Tarik";
					found=true;
			}
			
			if(option==3)
			{
				cout<<"\n\n\tTRANSFER";
				cout<<"\n\nMasukan Jumlah ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(ac.retdeposit() < amt)
					cout<<"Saldo Tidak Cukup";
				else
					ac.draw(amt);
					int pos=(-1)*static_cast<int>(sizeof(ac));
					File.seekp(pos,ios::cur);
					File.write(reinterpret_cast<char *> (&ac), sizeof(account));
					File.close();
					cout<<"\n\nMasukan Nomor Rekening Yang Ingin Di Transfer";
					cin>>acnotransfer;
					File.open("akun.txt", ios::binary|ios::in|ios::out);
					if(!File)
					{
						cout<<"File tidak bisa dibuka !! Silahkan tekan apa saja...";
						return;
					}
					while(!File.eof() && found==false)
					{
						File.read(reinterpret_cast<char *> (&ac), sizeof(account));
						if(ac.retacno()== acnotransfer)
						{
							ac.dep(amt);
							int pos=(-1)*static_cast<int>(sizeof(ac));
							File.seekp(pos,ios::cur);
							File.write(reinterpret_cast<char *> (&ac), sizeof(account));
							cout<<"\n\n\t Berhasil Mentrasfer";
							found=true;
						}
					}
				
			}
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Data tidak ditemukan ";
}

void login(int acno,int password)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("akun.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File tidak bisa dibuka !! Silahkan tekan apa saja......";
		return;
	}
	cout<<"\nDATA SALDO\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==acno and ac.retpassword() == password)
		{
			ac.screen(acno,password);
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nGagal,Silahkan Coba Lagi";
	
}

//***************************************************************
//    	FUNGSI INTRO
//****************************************************************


int account::intro()
{
   account ac;
   int opsi;
   cout << "\nPilihan : \n";
   cout << "\t1. Buat Akun\n";
   cout << "\t2. Login\n";
   cout << "Opsi: ";
   cin  >> opsi;
   switch(opsi){
         case 1:
            ac.write_account();
         case 2:
         	cout  << "Masukkan Norek User: ";
            cin   >> acno;
            cout  << "Masukkan Password: ";
            cin   >> password;
         	login(acno,password);
         default:
            cout << "\nTerima Kasih\n";
         break;
      }
}

//***************************************************************
//    			AKHIR PROGRAM
//***************************************************************
		   
