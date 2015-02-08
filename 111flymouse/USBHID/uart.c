#include "lpc17xx.h"
#include "uart.h"
#define UART0 LPC_UART0
#define UART1 LPC_UART1
#define PINCON LPC_PINCON
	volatile uint32_t UART0Status, UART1Status;
	volatile uint8_t UART0TxEmpty = 1, UART1TxEmpty = 1;
	volatile uint8_t UART0Buffer[BUFSIZE], UART1Buffer[BUFSIZE];
	volatile uint32_t UART0Count = 0, UART1Count = 0;
	volatile uint8_t sign0 =0;
/*******************************************************************
*
Function name: UART0Handler
** Descriptions: UART0 interrupt handler
** parameters: None
** Returned value: None
********************************************************************/
void UART0_IRQHandler (void)
	{
		uint8_t IIRValue, LSRValue;
		uint8_t Dummy = Dummy;
		IIRValue = UART0->IIR;
		IIRValue >>= 1; /* skip pending bit in IIR */
		IIRValue &= 0x07;  /* check bit 1~3, interruptidentification */
		if ( IIRValue == IIR_RLS ) /* Receive Line Status */
			{
				LSRValue = UART0->LSR;		/* Receive Line Status */
				if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
					{
							/* There are errors or break interrupt */
							/* Read LSR will clear the interrupt */
						UART0Status = LSRValue;
						Dummy = UART0->RBR; /* Dummy read on RX to clear interrupt, then bail out */
						return;
					}
				if ( LSRValue & LSR_RDR ) /* Receive Data Ready */
					{
					/* If no error on RLS, normal ready, save into the data buffer. */
					/* Note: read RBR will clear the interrupt */
						UART0Buffer[UART0Count] = UART0->RBR;
						if(UART0Count==0 && UART0Buffer[0]!=0x55)return;
						UART0Count++;
						if ( UART0Count == 11 )
							{
								UART0Count = 0; /* buffer overflow */
								sign0=1;
							}
					}
				}
	else if ( IIRValue == IIR_RDA ) /* Receive Data Available */
		{	
			/* Receive Data Available */
			UART0Buffer[UART0Count] = UART0->RBR;
			if(UART0Count==0 && UART0Buffer[0]!=0x55)return;
			UART0Count++;
			if ( UART0Count == 11 )
				{
					UART0Count = 0; /* buffer overflow */
					sign0=1;
				}
		}
	else if ( IIRValue == IIR_CTI ) /* Character timeout indicator */
		{
			/* Character Time-out indicator */
			UART0Status |= 0x100; /* Bit 9 as the CTI error */
		}
	else if ( IIRValue == IIR_THRE ) /* THRE, transmit holding registerempty */
		{
			/* THRE interrupt */
			LSRValue = UART0->LSR; /* Check status in the LSR to see if valid data in U0THR or not */
			if ( LSRValue & LSR_THRE )
				{
					UART0TxEmpty = 1;
				}
			else
				{
					UART0TxEmpty = 0;
				}
		}
	}
/*******************************************************************
*
** Function name: UART1Handler
** Descriptions: UART1 interrupt handler
** parameters: None
** Returned value: None
******************************************************************/
void UART1_IRQHandler (void)
	{
		uint8_t IIRValue, LSRValue;
		uint8_t Dummy = Dummy;
		IIRValue = UART1->IIR;
		IIRValue >>= 1; /* skip pending bit in IIR */
		IIRValue &= 0x07; /* check bit 1~3, interrupt identification */
		if ( IIRValue == IIR_RLS ) /* Receive Line Status */
			{
				LSRValue = UART1->LSR;
				/* Receive Line Status */
				if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
					{
						/* There are errors or break interrupt */
						/* Read LSR will clear the interrupt */
						UART1Status = LSRValue;
						Dummy = UART1->RBR; /* Dummy read on RX to clear interrupt, then bail out */
						return;
					}	
				if ( LSRValue & LSR_RDR ) /* Receive Data Ready */
					{					
							/* If no error on RLS, normal ready, save into the data buffer. */
							/* Note: read RBR will clear the interrupt */
						UART1Buffer[UART1Count] = UART1->RBR;
						UART1Count++;
						if ( UART1Count == BUFSIZE )
							{
								UART1Count = 0; /* buffer overflow */
							}
					}				
			}
		else if ( IIRValue == IIR_RDA ) /* Receive Data Available */
			{
			/* Receive Data Available */
			UART1Buffer[UART1Count] = UART1->RBR;
			UART1Count++;
			if ( UART1Count == BUFSIZE )
			{
			UART1Count = 0; /* buffer overflow */
			}
			}
			else if ( IIRValue == IIR_CTI ) /* Character timeout indicator */
			{
			/* Character Time-out indicator */
			UART1Status |= 0x100; /* Bit 9 as the CTI error */
			}
			else if ( IIRValue == IIR_THRE ) /* THRE, transmit holding register empty */
			{
			/* THRE interrupt */
				LSRValue = UART1->LSR; /* Check status in the LSR to see if valid data in U0THR or not */
					if ( LSRValue & LSR_THRE )
						{
							UART1TxEmpty = 1;
						}
					else
						{
							UART1TxEmpty = 0;
						}
			}
	}
/*******************************************************************
*
** Function name: UARTInit
** Descriptions: Initialize UART0 port, setup pin select,
** clock, parity, stop bits, FIFO, etc.
** parameters: portNum(0 or 1) and UART baudrate
** Returned value: true or false, return false only if the
** interrupt handler can't be installed to the
** VIC table
********************************************************************/
uint32_t UARTInit( uint32_t PortNum, uint32_t baudrate )
	{
		uint32_t Fdiv;
			if ( PortNum == 0 )
				{
					PINCON->PINSEL0 = 0x00000050; /* RxD0 is P0.3 and TxD0 is P0.2 */
					UART0->LCR = 0x83; /* 8 bits, no Parity, 1 Stop bit */
					/* By default, the PCLKSELx value is zero, thus, the PCLK for all the peripherals is 1/4 of the SystemFrequency. */
					// Fdiv = ( SystemFrequency/4/16 ) / baudrate ; /*baud rate, Fpclk:18MHz */
					Fdiv =(100000000 /*SystemCoreClock*//4/16 ) / baudrate ;
					UART0->DLM = 0;//Fdiv / 256;
					UART0->DLL = 13;//Fdiv % 256;
					UART0->FDR = 0XC1;//(0X0F & 0X01)|(0XF0 & 0XC0);
					UART0->LCR = 0x03; /* DLAB = 0 */
					UART0->FCR = 0x07; /* Enable and reset TX and RX FIFO. */
					NVIC_EnableIRQ(UART0_IRQn);
					UART0->IER =IER_RBR | IER_THRE | IER_RLS; /* Enable UART0 interrupt */
					return (TRUE);
				}
			else if ( PortNum == 1 )
				{
					PINCON->PINSEL4 |= 0x0000000A; /* Enable RxD1 P2.1, TxD1 P2.0 */
					UART1->LCR = 0x83; /* 8 bits, no Parity, 1 Stop bit */
					/* By default, the PCLKSELx value is zero, thus, the PCLK for all the peripherals is 1/4 of the SystemFrequency. */
					// Fdiv = ( SystemFrequency/4/16 ) / baudrate ; /*baud rate */
					Fdiv = ( 100000000 /*SystemCoreClock*//4/16 ) / baudrate ;
					UART1->DLM = Fdiv / 256;
					UART1->DLL = Fdiv % 256;
					UART1->LCR = 0x03; /* DLAB = 0 */
					UART1->FCR = 0x07; /* Enable and reset TX and RX FIFO. */
					NVIC_EnableIRQ(UART1_IRQn);
					UART1->IER = IER_RBR | IER_THRE | IER_RLS; /* Enable UART1
					interrupt */
					return (TRUE);
				}
			return( FALSE );
	}
/*******************************************************************
*
** Function name: UARTSend
????????
????(????)????????? 5 6
**
** Descriptions: Send a block of data to the UART 0 port based
** on the data length
**
** parameters: portNum, buffer pointer, and data length
** Returned value: None
*************************************************************/
void UARTSend( uint32_t portNum, uint8_t *BufferPtr, uint32_t Length )
	{
	if ( portNum == 0 )
		{
			while ( Length != 0 )
				{
					/* THRE status, contain valid data */
					while ( !(UART0TxEmpty & 0x01) );
					UART0->THR = *BufferPtr;
					UART0TxEmpty = 0; /* not empty in the THR until it shifts out */
					BufferPtr++;
					Length--;
				}
		}
	else
		{
			while ( Length != 0 )
			{
				/* THRE status, contain valid data */
				while ( !(UART1TxEmpty & 0x01) );
				UART1->THR = *BufferPtr;
				UART1TxEmpty = 0; /* not empty in the THR until it shifts out */
				BufferPtr++;
				Length--;
			}
		}
		return;
	}
/********************************************************************** End Of File******************************************************************/
