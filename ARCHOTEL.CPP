#include <iomanip.h>
#include <process.h>
#include <fstream.h>
#include <conio.h>
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <ctype.h>

#define hsenc 80000
#define hlujo 100000

#define false 1
#define true 0

char *NombreArchivo = "HOTEL.DAT";

typedef struct
{
  char cedula[10];
  char nombre[30];
  char apellido[30];
  char telefono[10];
  char procedencia[30];
  char estado;
  int  NoHabitacion;
  long Nodias;
  int tipo;
  long valorH;
  long valorT;
  long consumo;
}Hotel_Carlanchin;

Hotel_Carlanchin Cliente;
int NHab;

int RevisaHab(int NHab);//REVISA SI LA HABITACION ESTA OCUPADA
void Capturar(); //CAPTURA Y GUARDA LOS DATOS DE LOS HUESPEDES
void InConsumoXNumh(); //INSERTA CONSUMO DEL HUESPED X Nง HABITACION
void InConsumoXCed(); //INSERTA CONSUMO DEL HUESPED X Nง CEDULA
void Facturas(); //MUESTRA TODAS LAS FACTURAS
void BusqXcedula(); //BUSQUEDA DE HUESPED X Nง CEDULA
void BusqXhabitacion(); //BUSQUEDA DE HUESPED X Nง HABITACION
void BusqXapellido(); //BUSQUEDA DE HUESPED X APELLIDO & NOMBRE
void SalidaHuesped(); //DA SALIDAD AL HUESPED Y LIBERA HABITACION
void MostrarHusp(); //MUESTRA LISTA DE HUESPEDES ACTUALES Y SALIENTES
void reset();  // RESETEA EL ARCHIVO HOTEL.DAT

void main()
{
  int opcion;
  char op;
  while(op != 27)
  {
    clrscr ();
    cout<<"\n\tษอออออออออออออออออออออออออออออออออออออออออออออออออออออป";
    cout<<"\n\tบ                                                     บ";
    cout<<"\n\tบ               -- HOTEL CARLANCHIN --                บ";
    cout<<"\n\tบ                                                     บ";
    cout<<"\n\tฬอออออออออออออออออออออออออออออออออออออออออออออออออออออน";
    cout<<"\n\tบ                                                     บ";
    cout<<"\n\tบ     1.- INGRESAR DATOS                              บ";
    cout<<"\n\tบ     2.- INGRESAR CONSUMO DEL HUESPED                บ";
    cout<<"\n\tบ     3.- MOSTRAR FACTURAS                            บ";
    cout<<"\n\tบ     4.- BUSQUEDA DE HUESPEDES                       บ";
    cout<<"\n\tบ     5.- MOSTRAR LISTA DE HUESPEDES                  บ";
    cout<<"\n\tบ     6.- SALIDA DE HUESPEDES                         บ";
    cout<<"\n\tบ     7.- ELIMINAR REGISTROS                          บ";
    cout<<"\n\tบ     ESC.- SALIR                                     บ";
    cout<<"\n\tบ                                                     บ";
    cout<<"\n\tศอออออออออออออออออออออออออออออออออออออออออออออออออออออผ";
    cout<<"\n\n\t--> DIGITE UNA OPCION : ";
    op=getch();
    switch (op)
    {
      case '1': Capturar();
		break;
      case '2': clrscr();
		cout<<"\n\n  --- INGRESAR CONSUMO HUESPED ---";
		cout<<"\n\n\t 1. Nง CEDULA";
		cout<<"\n\t 2. Nง HABITACION";
		cout<<"\n\n\t DIGITE LA OPCION:";
		cin>>opcion;
		if(opcion==1){InConsumoXCed();}
		if(opcion==2){InConsumoXNumh();}
		break;
      case '3': Facturas();
		break;
      case '4': clrscr();
		cout<<"\n\n  --- BUSQUEDA DE HUESPEDES ---";
		cout<<"\n\n\t 1. Nง HABITACION";
		cout<<"\n\t 2. APELLIDO - NOMBRE";
		cout<<"\n\t 3. Nง CEDULA";
		cout<<"\n\n\t DIGITE LA OPCION:";
		cin>>opcion;
		if(opcion==1){BusqXhabitacion();}
		if(opcion==2){BusqXapellido();}
		if(opcion==3){BusqXcedula();}
		break;
      case '5': MostrarHusp();
		break;
      case '6': SalidaHuesped();
		break;
      case '7': reset();
		break;
      default : if(op == 27){exit(0);}
    }
  }
}

/****************************************************************************/
void Capturar()
{
  int sw2;
  char res, res1;

  do{
     clrscr();
     cout<<"\nDIGITE EL Nง DE HABITACION: ";
     cin>>NHab;
     sw2=RevisaHab(NHab);
  }while(sw2==false);
  ofstream Archivo;
  Archivo.open(NombreArchivo, ios::ate);
  if (!Archivo)
  {
    cout << "Error en la apertura del archivo \a";
  }
  else
  {
      Cliente.NoHabitacion=NHab;
      cout<<"\nNombre: ";
      gets(Cliente.nombre);
      cout<<"Apellido: ";
      gets(Cliente.apellido);
      cout<<"Cedula: ";
      gets(Cliente.cedula);
      cout<<"Telefono: ";
      gets(Cliente.telefono);
      cout<<"Procedencia: ";
      gets(Cliente.procedencia);
      cout<<"Tipo de Habitacion : ";
      cout<<" 1.H. Sencilla";
      cout<<" 2.H. Lujo : ->";
      cin>>Cliente.tipo;
	   if(Cliente.tipo==1){Cliente.valorH=hsenc;}
	   if(Cliente.tipo==2){Cliente.valorH=hlujo;}
      cout<<"Nง Dias: ";
      cin>>Cliente.Nodias;
      Cliente.estado='H';
      Cliente.consumo=0;
      Cliente.valorT=(Cliente.valorH*Cliente.Nodias);
      cout<<"\nDesea Guardar Registro S/N";
      res=getch();
      if(res=='s' || res=='S')
      {
	Archivo.write((char *)&Cliente, sizeof(Cliente));
      }
  }
  Archivo.close();
  getch();
}
/****************************************************************************/
int RevisaHab(int NHab)
{
 int sw=true;

 fstream rd(NombreArchivo, ios::in|ios::out|ios::binary);
 do
  {
   rd.read((char *)&Cliente, sizeof(Cliente));
   if(rd.eof())
     break;
   if(NHab == Cliente.NoHabitacion)
    {
     sw=false;
     cout<<"\n----------------------";
     cout<<"\n--HABITACION OCUPADA--";
     cout<<"\n----------------------";
     getch();
     break;
    }
  }while(!rd.eof());
 rd.close();
return sw;
}

/****************************************************************************/
void Facturas()
{
  int sw,numReg=0;
  fstream Archivo;
  clrscr();
  Archivo.open(NombreArchivo,ios::in|ios::binary);
  if (!Archivo)
  {
    cout << "Error en la apertura del archivo \a";
    getch();
  }
  else
  {
    do
    {
      numReg++;
      Archivo.read( (char *)&Cliente, sizeof(Cliente) );
      if(Archivo.eof())
      {
	break;
      }
      cout<<resetiosflags(ios::left)<<setiosflags(ios::fixed | ios::showpoint);
      clrscr();
      cout<<"\n/-----------------------------------------/";
      cout<<"\n FACTURA Nง       : "<<numReg;
      if(Cliente.estado=='N'){cout<<"   CANCELADA";}
      cout<<"\n/-----------------------------------------/";
      cout<<"\n Estado           : "<<Cliente.estado;
      cout<<"\n Apellido         : "<<Cliente.apellido;
      cout<<"\n Nombre           : "<<Cliente.nombre;
      cout<<"\n Cedula           : "<<Cliente.cedula;
      cout<<"\n Nง Habitacion    : ";
      if(Cliente.NoHabitacion==0){cout<<"---";}
      else{cout<<Cliente.NoHabitacion;}
      if(Cliente.tipo==1){cout<<"\n Tipo             : Habitacion Sencilla";}
      if(Cliente.tipo==2){cout<<"\n Tipo             : Habitacion de Lujo";}
      cout<<"\n Valor Hab. Dia   : "<<Cliente.valorH;
      cout<<"\n NงDias           : "<<Cliente.Nodias;
      cout<<"\n Valor Consumo    : $ "<<Cliente.consumo;
      cout<<"\n                  /-----------------------/";
      cout<<"\n Valor Total      : $ "<<Cliente.valorT;
      cout<<"\n/-----------------------------------------/";
      cout<<"\n  Estado:(H)Hospedado----(N)No Hospedado   ";
      cout<<"\n/-----------------------------------------/\n";
      getch();
    }while(!Archivo.eof());
    Archivo.close();
  }

  getch();
}
/****************************************************************************/
void SalidaHuesped()
{
  long Pconsumo;
  int numReg=0,Numh;
  clrscr();
  fstream Archivo;
  Archivo.open(NombreArchivo,ios::in|ios::out|ios::binary);

  if (!Archivo)
  {
    cout << "Error en la apertura del archivo \a";
    getch();
  }
  else
  {  cout<<"\n ----- SALIDA DE HUESPED ----- ";
     cout<<"\n\n\tDIGITE Nง HABITACION: ";
     cin>>Numh;
     clrscr();
     do
      {
       numReg++;
       Archivo.read( (char *)&Cliente, sizeof(Cliente) );
       if(Archivo.eof())
       {
	clrscr();
	cout<<"\n\n\n\n\n\tRegistro no encontrado...";
	break;
       }
       if(Numh==Cliente.NoHabitacion)
       {
	cout<<resetiosflags(ios::left)<<setiosflags(ios::fixed | ios::showpoint);
	cout<<"\n/----------- SALIDA DE HUESPED -----------/";
	cout<<"\n/-----------------------------------------/";
	cout<<"\n FACTURA Nง       : "<<numReg;
	cout<<"\n/-----------------------------------------/";
	cout<<"\n Apellido         : "<<Cliente.apellido;
	cout<<"\n Nombre           : "<<Cliente.nombre;
	cout<<"\n Cedula           : "<<Cliente.cedula;
	cout<<"\n Nง Habitacion    : "<<Cliente.NoHabitacion;
	if(Cliente.tipo==1){cout<<"\n Tipo             : Habitacion Sencilla";}
	if(Cliente.tipo==2){cout<<"\n Tipo             : Habitacion de Lujo";}
	cout<<"\n Valor Hab. Dia   : "<<Cliente.valorH;
	cout<<"\n NงDias           : "<<Cliente.Nodias;
	cout<<"\n Valor Consumo    : $ "<<Cliente.consumo;
	cout<<"\n                  /-----------------------/";
	cout<<"\n Valor Total      : $ "<<Cliente.valorT;
	cout<<"\n/-----------------------------------------/\n";
	getch();
	Cliente.NoHabitacion=0;
	Cliente.estado='N';
	Archivo.seekp((numReg-1)*sizeof(Cliente));
	Archivo.write((char *)&Cliente,sizeof(Cliente));
	break;
       }
      }while(!Archivo.eof());
      Archivo.close();
    }
}
/****************************************************************************/
void InConsumoXCed()
{
  char ced[10];
  long Pconsumo;
  int numReg=0;
  clrscr();
  fstream Archivo;
  Archivo.open(NombreArchivo,ios::in|ios::out|ios::binary);

  if (!Archivo)
  {
    cout << "Error en la apertura del archivo \a";
    getch();
  }
  else
  {
      cout<<"\n ----- INGRESAR CONSUMO DE HUESPED ----- ";
     cout<<"\n\n\tDigite Nง Cedula:";
     gets(ced);
     clrscr();
     do
      {
       numReg++;
       Archivo.read( (char *)&Cliente, sizeof(Cliente) );
       if(Archivo.eof())
       {
	clrscr();
	cout<<"\n\n\n\n\n\tRegistro no encontrado...";
	break;
       }
       if(strcmp(ced,Cliente.cedula)==0)
       {
	if(Cliente.estado=='N')
	{
	 cout<<"\n----------------------";
	 cout<<"\n CLIENTE NO HOSPEDADO ";
	 cout<<"\n----------------------";
	 break;
	}
	else
	{
	 cout<<"\n ----- INGRESAR CONSUMO DE HUESPED ----- ";
	 cout<<"\n Nง Habitacion      : "<<Cliente.NoHabitacion;
	 cout<<"\n Apellido           : "<<Cliente.apellido;
	 cout<<"\n Nombre             : "<<Cliente.nombre;
	 cout<<"\n Valor Consumido    : $ "<<Cliente.consumo;
	 cout<<"\n Valor Total        : $ "<<Cliente.valorT;
	 cout<<"\n/--------------------------------/\n";
	 cout<<resetiosflags(ios::left)<<setiosflags(ios::fixed | ios::showpoint);
	 cout<<"\n DIGITE EL CONSUMO : $ ";
	 cin>>Pconsumo;
	 Cliente.consumo=Cliente.consumo+Pconsumo;
	 Cliente.valorT=Cliente.valorT+Pconsumo;
	 Archivo.seekp((numReg-1)*sizeof(Cliente));
	 Archivo.write((char *)&Cliente,sizeof(Cliente));
	 break;
	}
       }
      }while(!Archivo.eof());
      Archivo.close();
    }
   getch();
}
/****************************************************************************/
void InConsumoXNumh()
{
  long Pconsumo;
  int numReg=0,Numh;
  clrscr();
  fstream Archivo;
  Archivo.open(NombreArchivo,ios::in|ios::out|ios::binary);

  if (!Archivo)
  {
    cout << "Error en la apertura del archivo \a";
    getch();
  }
  else
  {     cout<<"\n ----- INGRESAR CONSUMO DE HUESPED ----- ";
	cout<<"\n\n\tDigite Nง de Habitaciขn: ";
	cin>>Numh;
	clrscr();
	do
	  {
	  numReg++;
	  Archivo.read( (char *)&Cliente, sizeof(Cliente) );
	  if(Archivo.eof())
	  {
	   clrscr();
	   cout<<"\n\n\n\n\n\tRegistro no encontrado...";
	   break;
	  }
	  if(Numh==Cliente.NoHabitacion)
	  {
	    cout<<"\n ----- INGRESAR CONSUMO DE HUESPED ----- ";
	    cout<<"\n Nง Habitacion      : "<<Cliente.NoHabitacion;
	    cout<<"\n Apellido           : "<<Cliente.apellido;
	    cout<<"\n Nombre             : "<<Cliente.nombre;
	    cout<<"\n Valor Consumido    : $ "<<Cliente.consumo;
	    cout<<"\n Valor Total        : $ "<<Cliente.valorT;
	    cout<<"\n/--------------------------------/\n";
	    cout<<resetiosflags(ios::left)<<setiosflags(ios::fixed | ios::showpoint);
	    cout<<"\n DIGITE EL CONSUMO: $ ";
	    cin>>Pconsumo;
	    Cliente.consumo=Cliente.consumo+Pconsumo;
	    Cliente.valorT=Cliente.valorT+Pconsumo;
	    Archivo.seekp((numReg-1)*sizeof(Cliente));
	    Archivo.write((char *)&Cliente,sizeof(Cliente));
	    break;
	  }
	}while(!Archivo.eof());
	Archivo.close();
    }
  getch();
}
/****************************************************************************/
void BusqXapellido()
{
  char ape[30],nom[50];
  int numReg;
  fstream Archivo;
  Archivo.open(NombreArchivo,ios::in|ios::out|ios::binary);
  if (!Archivo)
  {
    cout << "Error en la apertura del archivo \a";
    getch();
  }
  else
  {
    numReg=0;
    clrscr();
    cout<<"\n/------ BUSQUEDA DE HUESPED ------/";
    cout<<"\n\n\tDigite el Apellido: ";
    gets(ape);
    cout<<"\n\tDigite el Nombre: ";
    gets(nom);
    clrscr();
    do
    {
      numReg++;
      Archivo.read( (char *)&Cliente, sizeof(Cliente) );
      if(Archivo.eof())
      {
	clrscr();
	cout<<"\n\n\n\n\n\tRegistro no encontrado...";
	break;
      }
      if((strcmp(ape,Cliente.apellido)==0)&&(strcmp(nom,Cliente.nombre)==0))
      {
       if(Cliente.estado=='N')
	 {
	  cout<<"\n----------------------";
	  cout<<"\n CLIENTE NO HOSPEDADO ";
	  cout<<"\n----------------------";
	  break;
	 }
	else
	{
	 cout<<"\n/------ HUESPED ENCONTRADO ------/\n";
	 cout<<"\n Nง Habitacion    : "<<Cliente.NoHabitacion;
	 cout<<"\n Apellido         : "<<Cliente.apellido;
	 cout<<"\n Nombre           : "<<Cliente.nombre;
	 cout<<"\n/--------------------------------/\n";
	 getch();
	 cout<<resetiosflags(ios::left)<<setiosflags(ios::fixed | ios::showpoint);
	 break;
	}
      }
    }while(!Archivo.eof());
    Archivo.close();
  }
  getch();
}
/****************************************************************************/
void BusqXcedula()
{
  char ced[10];
  int numReg=0;
  clrscr();
  fstream Archivo;
  Archivo.open(NombreArchivo,ios::in|ios::out|ios::binary);
  if (!Archivo)
  {
    cout << "Error en la apertura del archivo \a";
    getch();
  }
  else
  {
    cout<<"\n/------ BUSQUEDA DE HUESPED ------/";
    cout<<"\n\n\tDigite Nง Cedula: ";
    gets(ced);
    clrscr();
    do
    {
      numReg++;
      Archivo.read( (char *)&Cliente, sizeof(Cliente) );
      if(Archivo.eof())
      {
	clrscr();
	cout<<"\n\n\n\n\n\tRegistro no encontrado...";
	break;
      }

      if(strcmp(ced,Cliente.cedula)==0)
      {
	if(Cliente.estado=='N')
	{
	 cout<<"\n----------------------";
	 cout<<"\n CLIENTE NO HOSPEDADO ";
	 cout<<"\n----------------------";
	 break;
	}
	else
	{
	 cout<<"\n/------- HUESPED ENCONTRADO ------/\n";
	 cout<<"\n Nง Habitacion    : "<<Cliente.NoHabitacion;
	 cout<<"\n Apellido         : "<<Cliente.apellido;
	 cout<<"\n Nombre           : "<<Cliente.nombre;
	 cout<<"\n Cedula           : "<<Cliente.cedula;
	 cout<<"\n NงDias           : "<<Cliente.Nodias;
	 cout<<"\n Valor Habitacion : "<<Cliente.valorH;
	 cout<<"\n Valor Consumo    : $ "<<Cliente.consumo;
	 cout<<"\n Valor Total      : $ "<<Cliente.valorT;
	 cout<<"\n/--------------------------------/\n";
	 getch();
	 cout<<resetiosflags(ios::left)<<setiosflags(ios::fixed | ios::showpoint);
	 break;
	}
      }
    }while(!Archivo.eof());
    Archivo.close();
  }

  getch();
}
/****************************************************************************/

void BusqXhabitacion()
{
  int Numh;
  int numReg;
  fstream Archivo;
  Archivo.open(NombreArchivo,ios::in|ios::out|ios::binary);
  if (!Archivo)
  {
    cout << "Error en la apertura del archivo \a";
    getch();
  }
  else
  {
    numReg=0;
    clrscr();
     cout<<"\n/------ BUSQUEDA DE HUESPED ------/";
    cout<<"\n\n\tDigite el Nง de habitaciขn: ";
    cin>>Numh;
    clrscr();
    do
    {
      numReg++;
      Archivo.read( (char *)&Cliente, sizeof(Cliente) );
      if(Archivo.eof())
      {
	clrscr();
	cout<<"\n\n\n\n\n\tRegistro no encontrado...";
	break;
      }
      if(Numh==Cliente.NoHabitacion)
      {
      cout<<"\n/------ HUESPED ENCONTRADO ------/\n";
      cout<<"\n Nง Habitacion    : "<<Cliente.NoHabitacion;
      cout<<"\n Apellido         : "<<Cliente.apellido;
      cout<<"\n Nombre           : "<<Cliente.nombre;
      cout<<"\n Cedula           : "<<Cliente.cedula;
      cout<<"\n NงDias           : "<<Cliente.Nodias;
      cout<<"\n Valor Habitacion : "<<Cliente.valorH;
      cout<<"\n Valor Consumo    : $ "<<Cliente.consumo;
      cout<<"\n Valor Total      : $ "<<Cliente.valorT;
      cout<<"\n/--------------------------------/\n";
      getch();
      cout<<resetiosflags(ios::left)<<setiosflags(ios::fixed | ios::showpoint);
      break;
      }
    }while(!Archivo.eof());
    Archivo.close();
  }

  getch();
}
/****************************************************************************/
void MostrarHusp()
{
  int sw;
  fstream Archivo;
  clrscr();
  Archivo.open(NombreArchivo,ios::in|ios::binary);
  if (!Archivo)
  {
    cout << "Error en la apertura del archivo \a";
  }
  else
  { cout<<"\n\n\n/--------------------------------------------------------------------/";
    cout<<"\nNง Hab.  Apellido   Nombre    Cedula    Procedencia   Telefono  Estado   \n\n";
    do
    {
      Archivo.read( (char *)&Cliente, sizeof(Cliente) );
      if(Archivo.eof())
      {
	break;
      }

      if(Cliente.NoHabitacion==0){cout<<setiosflags(ios::left)<<setw(9)<<"---";}
      else{cout<<setiosflags(ios::left)<<setw(9)<<Cliente.NoHabitacion;}
      cout<<setw(11)<<Cliente.apellido<<setprecision(2);
      cout<<setw(11)<<Cliente.nombre<<setprecision(2);
      cout<<setw(10)<<Cliente.cedula<<setprecision(2);
      cout<<setw(13)<<Cliente.procedencia<<setprecision(2);
      cout<<setw(12)<<Cliente.telefono<<setprecision(2);
      cout<<setw(9)<<Cliente.estado<<setprecision(2)<<'\n';


    }while(!Archivo.eof());
    cout<<"\n/-----------------------------------------/";
    cout<<"\n  Estado:(H)Hospedado----(N)No Hospedado   ";
    cout<<"\n/-----------------------------------------/\n";
    Archivo.close();
  }
  getch();
}
/****************************************************************************/

void reset()
{
  ofstream arch;

  arch.open ("HOTEL.DAT", ios::out);
  arch.close();

  cout<<"\n\t/--------------------------------------/";
  cout <<"\n\t     El archivo esta reseteado!!!";
  cout<<"\n\t/--------------------------------------/";
  getch();
}