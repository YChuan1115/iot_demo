//-----------------------
// IoT final project
// Author List: 
//joseph(D05921016@ntu.edu.tw), 
// Version: 1.0
// Date: Jan 1,2017
//---------------------
// Note: 
// LED Pin  on J3-03
//------------------------------

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "autonet.h"

//--------------------
#define MY_DEVICE_ADDR  0x0005
//!!!!! SHOULD set different mac addr  !!!!!!!!
#define NUM_CHILDREN  2        //!!!! SHOULD set correctly !!!!!
#define KING_ID 'A'+NUM_CHILDREN   //'A'~'H' ; note : Target ID is 'C' if the number of children is 2
#define DEBUG 0
//------------------------------


#define PAN_ID  0x0007
#define RADIO_CHANNEL  25
#define TYPE 0x1

#define RCV_BUFSIZE 128
#define MAX 20  //routing table size
//define Packet type
#define WHOAMI_REQ 	0x80
#define WHOAMI_REP 	0x81
#define RREP 			  0x40
#define FLAG   			0x20
#define NORMAL   		0x10
#define NORMAL_ACK  0x11


#define SLEEP_TIME 5000  //unit: ms
#define BLINK_PERIOD 300  //unit: ms

#define T 100 // unit : ms

#define JOSEPH_TEST 0

int debug=DEBUG;

typedef struct _host
{
  uint16_t my_ID;  
	uint16_t my_addr;
		
}Host;

typedef struct _packet
{
  uint8_t type;
  uint16_t dest_id;
  uint16_t dest_mac;
  uint16_t src_id;
  uint16_t src_mac;
  uint8_t length; // data length
  uint8_t data[10];
}Packet;

	  

typedef struct _route {
  
  uint16_t dest_id;
  uint16_t dest_mac;
	uint16_t next_id;
  uint16_t next_mac;
	
}Route;

typedef struct _rtable {
        
  Route table[MAX];
  uint8_t index; 

}Route_Table;

uint16_t ID_LIST[10];

typedef struct {
	
  uint16_t start_time;
  uint16_t end_time;	
	uint16_t packet_count;
	uint8_t  enable;
	uint8_t  num_dev;
}Statistic;

typedef struct {
	
  uint8_t swith_state;
  uint8_t gpio_state;	

}IO;



enum {INIT=0,GET_ID,SEND_DATA,WAIT_ACK,FINISH};
Statistic statistic;
uint8_t State;
Host host;
uint8_t finish=0;
#define PRINT_BUFSIZE 128
char output_array[PRINT_BUFSIZE]={0}; 	
IO io={0};

//Function list
//-------------------
void debug_print(char *s);
void show_myinfo(void);
void show_report(void);
void dump_packet(Packet *p);
void req_whoami(void);
void reply_whoami(uint16_t dest_id,uint16_t macaddr);
void send_message( uint8_t type,uint16_t dest_id,uint16_t dest_mac, uint8_t *data, uint8_t size);
void send_RREP(uint16_t id, uint8_t *data, uint8_t size,Route_Table *tbl);
void send_DATA(uint16_t id, uint8_t *data, uint8_t size,Route_Table *tbl);
void send_DATA_ACK(uint16_t id, uint8_t *data, uint8_t size,Route_Table *tbl);
void send_FLAG(void);
void send_to_KING(Route_Table *tbl);
void init(void);

void update_table(Packet *pkt,Route_Table *tbl);
//---Routing Table Processing-----------

void init_table(Route_Table *tbl);
uint8_t add_route(Route *route,Route_Table *tbl);
void dump_table(Route_Table *tbl);
uint16_t find_mac(uint16_t id, Route_Table *tbl);
Route * find_next_hop(uint16_t id, Route_Table *tbl);
//----Utility function---------------------
void blink_led(int count);
uint8_t  detect_switch(void);
uint8_t detect_input_from_pi(void);
//-----------------------------------------

int main(void)
{
	
	uint8_t rcvd_msg[RCV_BUFSIZE];
	uint8_t rcvd_payload[RCV_BUFSIZE];
	uint8_t rcvd_length;
 

	uint8_t rcvd_payloadLength;
	uint8_t rcvd_rssi;
	Packet * pkt;
	Route r_entry;	
	uint16_t timer_count=0;
	Host host_info;
	Route_Table rtable;
	uint8_t blink_count=0;
	uint16_t prev_ID;
  uint8_t flag=0;
	uint8_t on; 
	int8_t prev=-1;

  //Packet packet={0x1,'A',0x10,'B',0x11,0,{0}};

	init();  //init all
  prev_ID=host.my_ID;
  init_table(&rtable);
	
   debug_print("Starting .....\r\n");
	 show_myinfo();


  	setTimer(1, T, UNIT_MS);  // T ms
    //send WHOAMI packet in ordet to recognize the who i am (ID)
		debug_print("send WHOAMI packet .....\r\n");	 
		
		
		req_whoami();
		timer_count=0;

	
	while(1){
		

			

		 if(checkTimer(1)) { //timer
        	 

			     timer_count++;
				
	

//---------------------------------------
// Device  A is the device connect raspberry pi directly			 
			 
			 if(host.my_ID=='A') {

				on=detect_input_from_pi();
				 
				 if (State==FINISH && prev!=on) {
					 debug_print("send to relay node\r\n");	
					 io.gpio_state=on;
					 send_to_KING(&rtable);
					 
					 prev=on;
				 }
				
			}
			 
//-------------------------------------
// Device 'KING' is the last one device and have a relay		
  			 
			 if(host.my_ID==KING_ID) {
				on=detect_switch();
				 if (prev!=on) {
					  uint8_t data[10];
					 	data[0]='A'; //src ID
						data[1]=0; //seq no.
						data[2]=on; // switch state.
					  debug_print("send to pi ('A')\r\n");	
					  io.swith_state=on;
						send_DATA_ACK(host.my_ID-1,data,3,&rtable);
					  prev=on;
				 }
				
			}


			sprintf((char *)output_array,"%c->gpio_state=%d,switch_state=%d\r\n",host.my_ID,io.gpio_state,io.swith_state);
	    debug_print(output_array);
			
		 } 	//end if time_count	
	//--------------------------------------------
			if(RF_Rx(rcvd_msg, &rcvd_length, &rcvd_rssi)){
			
			getPayloadLength(&rcvd_payloadLength, rcvd_msg);
			getPayload(rcvd_payload, rcvd_msg, rcvd_payloadLength);
					
		 pkt=(Packet *)rcvd_payload;
			
     if (debug) dump_packet(pkt);
			
			if (statistic.enable)
				   statistic.packet_count++;
			
			//packet handling
			switch (pkt->type) {
			
				case WHOAMI_REQ:
					Delay((uint8_t)('H'-host.my_ID)*10); 
					reply_whoami(pkt->src_id,pkt->src_mac);
				
		
					break;
			 case WHOAMI_REP:
				 
			 		// ID sequence is determined by boot sequence 				    
					if (pkt->src_id >= host.my_ID) {
						  host.my_ID=pkt->src_id+1;
						  blink_count=(host.my_ID-prev_ID);
						  blink_led(blink_count); 
						  prev_ID=host.my_ID;
					}						
					 show_myinfo();
				   update_table(pkt,&rtable);
				 
					if (host.my_ID==KING_ID && flag==0) {
						
						uint8_t data[10];
						
						//broadcast 'FLAG'  
					  debug_print("broadcast 'FLAG' and go to sleep zzzzzzz\r\n");
						send_FLAG();						
					  // sleep for 5 seconds
						setGPIO(2,1);
						Delay(1000);
						setGPIO(2,0);
						//send RREP back to notify others that I just waking up
						memcpy(data,&host,sizeof(Host));
		        send_RREP(host.my_ID-1,data,sizeof(Host),&rtable);	//H-->G-->E-->C-->A
						/*20161206: joseph modified , add the follwing for two hops 
						 but it is possible to cause collision when replying RREP
				
						send_RREP(host.my_ID-2,data,sizeof(Host),&rtable);	//H-->F-->D-->B
								*/
						statistic.start_time=timer_count;				
			      statistic.enable=1;
					  flag=1;
						
						
						
					}

					break;				

				
				case RREP:
				 //update routing table 	
            debug_print("Get RREP....\r\n");
						memcpy(&host_info,pkt->data,pkt->length);
						r_entry.dest_id=host_info.my_ID;   
						r_entry.dest_mac=host_info.my_addr;
						r_entry.next_id=pkt->src_id;
						r_entry.next_mac=pkt->src_mac;
				  	add_route(&r_entry,&rtable);						
						//dump_table(&rtable);
				    
				   	 //in fact , you will get RREP, meaning that the KING is alive, so send data(type=NORMAL) to KING
				    send_to_KING(&rtable);	
			    	
				   
				    //send RREP back to hop by hop 
				    send_RREP(host.my_ID-1,pkt->data,pkt->length,&rtable);
				   //20161206: jospeh modified , send RREP back by two hops 
				   // send_RREP(host.my_ID-2,pkt->data,pkt->length,&rtable);
				
			
				
	        break;			
  
				case NORMAL:			
				
						//debug_print("Get NORMAL data\r\n");
					 					 
						if (pkt->data[0]==host.my_ID) { 
							  
						   	Host *h;
							  uint8_t data[10],on;
							  //debug_print("I Got you: ");
							  h=(Host *)&pkt->data[1];
							  on=pkt->data[6];
							  io.gpio_state=on;
							
							   sprintf((char *)output_array,"<<<Time=%d: ID=%c/%#x seq=%d, pi'gpio=%d>>>\r\n",timer_count,h->my_ID,h->my_addr,pkt->data[5],on);
				         debug_print(output_array);
							  //relay action
							  setOnOffDeviceState(on);
							
							  if (ID_LIST[h->my_ID-'A']==0) {
									ID_LIST[h->my_ID-'A']=1;
							    sprintf((char *)output_array,"<<<Time=%d: ID=%c/%#x seq=%d, pi'gpio=%d>>>\r\n",timer_count,h->my_ID,h->my_addr,pkt->data[5],pkt->data[6]);
				          debug_print(output_array);
									
									
									statistic.num_dev++;
									if (statistic.num_dev==NUM_CHILDREN) {
									   statistic.end_time=timer_count;
										 show_report();
									}
									
								}
								//debug_print("Send Data ACK\r\n");
								//on=detect_switch();
							 data[0]=pkt->data[1]; //data[0]: sent to whom
							 data[1]=pkt->data[5]; //seq no.
							 data[2]=io.swith_state; // switch state.
							// pkt->data[1]--> //src ID, send ACK to him 
							  send_DATA_ACK(host.my_ID-1,data,3,&rtable);
						} else { //not owner , so just forward
									debug_print("Forward\r\n");
						      send_DATA(pkt->data[0],pkt->data,pkt->length,&rtable);
							    
				    }
				  break;

				case NORMAL_ACK:			// Device A which connects to pi
					 					 
						if (pkt->data[0]==host.my_ID) { 
						sprintf((char *)output_array,"ACK from KING <---- %c,# %d,switch=%d\r\n",pkt->data[0],pkt->data[1],pkt->data[2]);
						   debug_print(output_array);
						  	io.swith_state=pkt->data[2];
							  State=FINISH;
							  setGPIO(2,io.swith_state);
						} else {
								//	debug_print("Forward to the previous node\r\n");
						      send_DATA_ACK(host.my_ID-1,pkt->data,pkt->length,&rtable);
				    }
				  break;

						
					
					default:
						//unknown type
					  break;
						
			 } //end switch
	   }  //if rx available
		
		if (timer_count==(3000/T) && host.my_ID=='@') {  // wait for 1 second and nobody reply ,myID is 'A' (first one)
		    host.my_ID='A';			
		    timer_count=0;
		    blink_led(1); 
			  show_myinfo();
		}
		
		if (State==WAIT_ACK) {
			 //Delay((uint8_t)host.my_ID/10);  //Maybe good , if we use different delay time
       send_to_KING(&rtable);	
			 
		}
		
		
		
		
		
		
	}  //edn while(1)



		

} //end main




//---------------------------------------------
//Packet Handling
//---------------------------------------------
void init()
{
	Initial(MY_DEVICE_ADDR,TYPE, RADIO_CHANNEL, PAN_ID);
	
  host.my_addr=MY_DEVICE_ADDR;
	host.my_ID='@'; //init to '@':0x40  
	memset(&statistic,0,sizeof(Statistic));
	State=INIT;
	
}



void debug_print(char *s)
{
	  int len=strlen(s);
	  COM2_Tx((uint8_t *)s,len);
	


}


void show_report(void)
{
 
	sprintf((char *)output_array,"----Statistics --------------\r\n");
	debug_print(output_array);
	sprintf((char *)output_array,"Start Time\tEnd Time\tPackets\r\n");
	debug_print(output_array);
	sprintf((char *)output_array,"%d\t\t%d\t\t%d\r\n",statistic.start_time, statistic.end_time,statistic.packet_count);
	debug_print(output_array);
}

void req_whoami()
{  	
	
	 Packet packet;
	 packet.type=WHOAMI_REQ; //whoami
	 packet.dest_id='0';
	 packet.dest_mac=0xFFFF;
	 packet.src_id=host.my_ID;
	 packet.src_mac=host.my_addr;	
	
	//broadcst
  RF_Tx(0xFFFF,(uint8_t *)&packet,sizeof(Packet));

}

void reply_whoami(uint16_t dest_id,uint16_t macaddr)
{
	  	
	 Packet packet;
	 packet.type=WHOAMI_REP; 
	 packet.dest_id=dest_id;
	 packet.dest_mac=macaddr;
	 packet.src_id=host.my_ID;
	 packet.src_mac=host.my_addr;	
	
	//unicast to sender
  RF_Tx(macaddr,(uint8_t *)&packet,sizeof(Packet));

}




void send_message( uint8_t type,uint16_t dest_id,uint16_t dest_mac, uint8_t *data, uint8_t size)
{
 
	 Packet packet;
	 packet.type=type; 
	 packet.dest_id=dest_id;
	 packet.dest_mac=dest_mac; 
	 packet.src_id=host.my_ID;
	 packet.src_mac=host.my_addr;	
	 memcpy(&packet.data,data,size);
	 packet.length=size;
	
  //unicast
  RF_Tx(packet.dest_mac,(uint8_t *)&packet,sizeof(Packet));
 
 

}


void send_FLAG()
{
  send_message(FLAG,0,0xFFFF,(uint8_t *)"FLAG",4);

}
void send_to_KING(Route_Table *tbl)
{  
	  static uint8_t seq=1;
		uint8_t data[10];
		data[0]=KING_ID;
		memcpy(&data[1],&host,sizeof(Host));
	//	sprintf((char *)output_array,"send DATA to king ---->(# %d)\r\n",seq);
	//	debug_print(output_array);
	  data[5]=seq++;
	  data[6]=io.gpio_state;
	  State=WAIT_ACK;
		send_DATA(KING_ID,data,sizeof(Host)+3,tbl);
	 
}


void send_DATA(uint16_t id, uint8_t *data, uint8_t size,Route_Table *tbl)
{

	 Route *r;
	
  r=find_next_hop(id,tbl);   
 	if (r)
	   send_message(NORMAL,id,r->next_mac ,data,size);

}

void send_DATA_ACK(uint16_t id, uint8_t *data, uint8_t size,Route_Table *tbl)
{

	 Route *r;
	
  r=find_next_hop(id,tbl);   
 	if (r)
	   send_message(NORMAL_ACK,id,r->next_mac ,data,size);

}


	
void send_RREP(uint16_t id, uint8_t *data, uint8_t size,Route_Table *tbl)
{

	 Route *r;

  r=find_next_hop(id,tbl);

 	if (r)
	   send_message(RREP,id,r->next_mac ,data,size);

}

void dump_packet(Packet *p)
{
	
	 uint8_t i;
  
	if (debug) {
		sprintf((char *)output_array,"Receiving: %#x\t%c\t%#x\t%c\t%#x \t%d\r\n==>",p->type,p->dest_id,p->dest_mac,p->src_id,p->src_mac,p->length);
	   	debug_print(output_array);
	     for (i=0;i<p->length;i++) {
	       	sprintf((char *)output_array,"%#x ",p->data[i]);
				  debug_print(output_array);
	 
			 }
    debug_print("\r\n");
		 }
}



void show_myinfo()
{

  sprintf((char *)output_array,"My Info: ID=%c,MAC Addr=%#x\r\n",host.my_ID,host.my_addr);
	debug_print(output_array);
	
}

void update_table(Packet *pkt,Route_Table *tbl)
{
	 //update routing table 	

	  Route r_entry;	
		r_entry.dest_id=pkt->src_id;
		r_entry.dest_mac=pkt->src_mac;
		r_entry.next_id=pkt->src_id;
		r_entry.next_mac=pkt->src_mac;
		add_route(&r_entry,tbl);						
	  //dump_table(tbl);

}
//------------------------------
//Utility function
//--------------------------------

//blinking LED
void blink_led(int count)
{
	uint8_t i;
	for (i=0;i<count;i++) {		
	    setGPIO(2,1);
		  Delay(BLINK_PERIOD);
	  	setGPIO(2,0);
		  Delay(BLINK_PERIOD);
		
  }		
}




//---------------------------------------------
//Table Handling
//---------------------------------------------
void init_table(Route_Table *tbl)
{
 
   memset(tbl,0,sizeof(Route_Table));
   tbl->index=0;

}

uint8_t add_route(Route *route,Route_Table *tbl)
{
   
   //printf("%c %#x %c %#x\n",route->dest_id,route->dest_mac,route->next_id,route->next_mac);

   memcpy(&tbl->table[tbl->index],route,sizeof(Route));
   tbl->index++;
   return tbl->index;
  

}


uint16_t find_mac(uint16_t id, Route_Table *tbl)
{
   uint8_t i;

   for (i=0;i<tbl->index;i++)
   {
       
       if (id==tbl->table[i].dest_id) 
          return tbl->table[i].dest_mac;    
   }

   return 0;

}


Route * find_next_hop(uint16_t id, Route_Table *tbl)
{
   uint8_t i;

   for (i=0;i<tbl->index;i++)
   {
       
       if (id==tbl->table[i].dest_id) 
          return &tbl->table[i];    
   }

   return NULL;

}



void dump_table(Route_Table *tbl)
{
   uint8_t i;
   debug_print("dest_id\tdest_mac  next_id\tnext_mac\r\n");    
	
   for (i=0;i<tbl->index;i++)
   {
		 	sprintf((char *)output_array,"%c\t0x%x\t\t%c\t\t0x%x\r\n",tbl->table[i].dest_id,tbl->table[i].dest_mac,tbl->table[i].next_id,tbl->table[i].next_mac);
	   	debug_print(output_array);
     
  
   }

}

uint8_t  detect_switch(void)
{
	
	  uint8_t on;
  	on=getSwitchState();
	  return on;
  
}	


uint8_t detect_input_from_pi(void)
{
	    uint8_t gpio_input;
	    gpio_input=getGPIO(3); //PB1 J3-18, received from Pi 
	  	return gpio_input;
}


/*

 if (on==1) {
			    setGPIO(2,1); //inform relay state to pi
			    //send packet>relay on
			}else {
			     setGPIO(2,0);
				  //send packet>relay off
			}
*/




