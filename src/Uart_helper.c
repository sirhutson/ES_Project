#include "Uart_helper.h"

//Writing this code involved 3 things 
//1 - Looking at the TIVA driver library documentaion
//2 - Looking at the source code for the uart.c in the driver folder
//3 - Doing some google to debug errors

//redirect for printf.
void UART_OutChar(char data);
int fputc(int ch, FILE *f);

//redirect input from serial port
//read info edit by: Sir Hutson
int fgetc(FILE *f);

//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNNNNNNNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM8O+++?7IIII7ZNMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMD+++II7IIIIIII7IIODMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMN+?IIIIIIIIIIIIIIIIINMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMN7IIIIIIIIIDIIIIIIIIII77NMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMDNZI7IIIIIIIIIIIID,.NZ7IIIIIIIZMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMD77IIIIIIIIIIIIIIIDN.,DNNIIIIIIIIIDMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMNOZOIIIIIIIIIIIIIIONNNNNNNOIIIIIIIIZMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMDZZOZIIIIIIIIIIII7NNNNNNNDOIIIIIIIIINMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMN8888ZND7IIIIIIIINZNNNNDD,7IIIIIIIIIDMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMN88888888N$IIIIII7DOZZZZ+N7IIIIIIIIIMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMND88888888DZIIIIIII7ODN$77IIIIIIIINMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMDD88888888O88IIIIIIIIIIIIIIIIIIIINMMMMMMMMMMMMMMM8MMO=MMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMN888888D$$8IIIIIIIIIIIIIIIIII7MMMMMMMMMMMMMMMM7+++++MMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMDN8O8O??$$$D8OIIIIIIIIIIIIIIOMMMMMMMMMMMMMMM$=+++=+7MMMMMM
//MMMMMMMMMMMMMNMMMMMMMMM88N?+???7$$8IIIIIIIIIIIIIIIDMMMMMMMMMMMMMMM=++++++=MMMMMM
//MMMMMMMMMMMMDIINMMMMMNN8D+?++??$NIIIIIIIIIIIIIIII7MMMMMMMMMMMMMMMM=+++++++=MMMMM
//MMMMMMMMMM8IIIIII?OMDD88O??O?IN7IIIIIIIIIIIIIIIIIDMMMMMMMMMMMMMN=+=+++777++OMMMM
//MMMMMMMMMMD7IIIIIII+NN887??D8IIIIIIIIIIIIIIIIIIIINM8DZ7IIIIIDMM=+++++?777777ZMMM
//MMMMMMMMM8$7IIIIIII7DZNND7IIIIIIIII77IIIIIII77NZ=+++IIIIIII$MMM++++++7777777MMMM
//MMMMMMMMMMMD7IIIIIIIIINN$III$ONNNO777IIII7ID=++++IIIIIIIIIIIIM$=+++++?77777ZMMMM
//MMMMMMMMMMMMM7IIIIIIIIIII77?N777777IIIIIID7I77IIIIIIIIIIIIIIDMM8=+???7777777MMMM
//MMMMMMMMMMMMMNIIIIIIIIIIII78NNNO77IIIIIIIIIIIIIIIIIIIIIIIIIZNMMM+=777777777ZMMMM
//MMMMMMMMMMMMMMM87IIIIIIIII$~~~~~=NIIIIIIIIIIIIIIIIIIIIIIIZNMMMMM?7$777I777$MMMMM
//MMMMMMMMMMMMMMMMD77IIIII$+~~~~~~~~I7IIIIIIIIIIIIIIIII77DMMMMMMMMMMMMN7ID7DMMMMMM
//MMMMMMMMMMMMMMMMMD$7III7=~~~~~~~~~~I7IIIIIIIIIIIII7788MMMMMMMMMMMMMMM7I$MMMMMMMM
//MMMMMMMMMMMMMMMMMMMN77IN~~~~~~~~~~~~87IIIIIIII777ONMMMMMMMMMMMMMMMMMM7IIMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMND~~~~~~~~~~~~~~ZIIIIIII8NO7I7MMMMMMMMMMMMMMMMMM7IINMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMM:~~~~~~~~~~~~~~87IIIIIIIIIIIINMMMMMMMMMMMMMMMMN7I$NMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMN~~~~~~~~~~~~~~~+IIIIIIIIIIIIINMMMMMMMMMMMMMMMMNII8NMMMMMMM
//MMMMMMMMMMMMMMMMMMMMM+~~~~~~~~~~~~~~~~Z7IIIIIIIIIIIOMMMMMMMMMMMMMMM87I7NNMMMMMMM
//MMMMMMMMMMMMMMMMMMMMD~~~~~~~~~~~~~~~~~NIIIIIIIIIIIIIDMMMMMMMMMMMMMNIII$~DMMMMMMM
//MMMMMMMMMMMMMMMMMMMMN~~~~~~~~~~~~~~~~~NIIIIIIIIIIIIINMMMMMMMMMMMMD$IIIN~MMMMMMMM
//MMMMMMMMMMMMMMMMMMMMN~~~~~~~~~~~~~~~~~NIIIIIIIIIIIIINMMMMMMMMMMMNIIII8~NMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMN~~~~~~~~~~~~~~~~~Z7IIIIIIIIIIIIDMMMMMMMMMD$7III7?~DMMMMMMMM
//MMMMMMMMMMMMMN=+?IIIN~~~~~~~~~~~~~~~~=IIIIIIIIIIIIIIZMMMMMM8NIIIIIIID~NMMMMMMMMM
//MMMMMMMMMMMN7++IIIII7~~~~~~~~~~~~~~~~Z77IIIIIIIIIIII$NNN87IIIIIIII78~OMMMMMMMMMM
//MMMMMMMMMMM?++IIIIII7D~~~~~~~~~~~~~~~NIIIIIIIIIIIIII$7I7IIIIIIII7Z?+8MMMMMMMMMMM
//MMMMMMMMMMM+?IIIIII777~~~~~~~~~~~~~ZZIIIIIIIIIIIIIII87IIIIIIIII7D++NMMMMMMMMMMMM
//MMMMMMMMMM8IIIII777777D=~~~~~~~~~~D7IIIIIIIIIIIIIII7N777IIIIIID7+?DMMMMMMMMMMMMM
//NNNN777ONNNIII777777777O+~~~~~~~~NIIIIIIIIIIIIIIIII$Z7777778D+++ZDMMMMMMMMMMMMMM
//MD~,.7III7IZII7777777777O+++=~~~N7IIIIIIIIIIIIIIII7N7777ND++++=NMMMMMMMMMMMMMMMM
//MMMNNIIIIIIIII77777777777$D+++++Z777IIIIIIIIIIII777O$?++++++IDMMMMMMMMMMMMMMMMMM
//MMMMMNZ777777I777777777777Z8DI?+$777I7IIIIIIIII777O++++++?OMMMMMMMMMMMMMMMMMMMMM
//MMMMMMM877777777777777DNMMMMMMM8N777777IIIII777777O++?$NMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMN$77777777$NMMMMMMMMMMMM$777777777777777NNDMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMN$777777DMMMMMMMMMMMMMMD7777777777777DMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMN7777NMMMMMMMMMMMMMMMMN7777777777ODMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMNDMMMMMMMMMMMMMMMMMMO$7777777DZMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMD77777777777DMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM7NDN7DN87NND8MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNN=O7?~I7?~NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMOMMM~DNN8MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

char UART_InChar(); // This function should really be called "char Mander"

void UartSetup()
{
		//
		// Enable the UART0 module.
		//
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
		//
		// Wait for the UART0 module to be ready.
		//
		while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
		{
		}
		
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); // activate port A
		GPIOPinConfigure(GPIO_PA0_U0RX); //Pin 0 is configured as receive
	
		GPIOPinConfigure(GPIO_PA1_U0TX); //Pin 1 is configured as transmit
		
		// enable alt funct on PA1-0 and enable digital I/O on PA1-0
		GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);
		
		// Initialize the UART. Set the baud rate, number of data bits, turn off
		// parity, number of stop bits, and stick mode. The UART is enabled by the
		SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);   //This will be moved to a different module eventually but clock is important for UART
		//
		UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 38400,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
		//
		// Check for characters. Spin here until a character is placed
}

void UART_OutChar(char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

// Print a character to UART.
int fputc(int ch, FILE *f){
  if((ch == 10) || (ch == 13) || (ch == 27)){
    UART_OutChar(13);
    UART_OutChar(10);
    return 1;
  }
  UART_OutChar(ch);
  return 1;
}

char UART_InChar(){
	while((UART0_FR_R&UART_FR_RXFE) !=0)
	return ((char)(UART0_DR_R&0xFF)); //returns the character from the port
}
// Get a character from UART.
int fgetc(FILE *f){
  return UART_InChar();
}

// Function called when file error occurs.
int ferror(FILE *f){
  /* Your implementation of ferror */
  return 1;
}
// this function does the same thing as UartSetup(), but uses direct register access method

// This function involved 2 things
// 1 - Reading the appropriate chapters in the data sheet
// 2 - Looking at the 
void UartSetup2()
{
	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 27;                    // IBRD = int(50,000,000 / (16 * 115,200)) = int(27.1267)
  UART0_FBRD_R = 8;                     // FBRD = int(0.1267 * 64 + 0.5) = 8
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1-0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1-0
}
