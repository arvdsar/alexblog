
/*the domotica status is send from the domoticabox as a LONG value. it's not rocket science down here. Each bit in the 4 bytes represents a device
this can be LightA or DoorBack or GardenFront. by doing some logic AND operations you can determine which device is set and upload this value to open.sen.se
Modify it for your own situation.
*/

void ProcessReceivedDomo(long Domo){
  
 
 LampA_Status = ' ';
 LampB_Status = ' ';
 LampC_Status = ' ';
 LampD_Status = ' ';
 LampE_Status = ' ';
 LampF_Status = ' ';
 TuinVoor_Status = ' ';
 TuinMidden_Status = ' ';
 DeurLinks_Status = ' ';
 DeurRechts_Status = ' ';
 DeurAchter_Status = ' ';
 TuinAchter_Status = ' ';

  if((Domo & 0x8000) == 0x8000)
    LampA_Status = 'A';  // 1000.0000.0000.0000
  if((Domo & 0x4000) == 0x4000)
    LampB_Status = 'B'; // 0100.0000.0000.0000
  if((Domo & 0x2000) == 0x2000)
    LampC_Status = 'C'; // 0010.0000.0000.0000
  if((Domo & 0x1000) == 0x1000)
    LampD_Status = 'D'; // 0001.0000.0000.0000
  if((Domo & 0x0800) == 0x0800)
    LampE_Status = 'E'; // 0000.1000.0000.0000
  if((Domo & 0x0400) == 0x0400)
    LampF_Status = 'F'; // 0000.0100.0000.0000
  if((Domo & 0x0200) == 0x0200) 
    TuinVoor_Status = 'V'; // 0000.0010.0000.0000   Tuinvoor
  if((Domo & 0x0100) == 0x0100)
    TuinMidden_Status = 'M'; // 0000.0001.0000.0000   TuinMidden
  if((Domo & 0x0080) == 0x0080)
    DeurLinks_Status = 'L'; // 0000.0000.1000.0000   Deurlinks
  if((Domo & 0x0040) == 0x0040)
    DeurRechts_Status = 'R'; // 0000.0000.0100.0000   Deurrechts
  if((Domo & 0x0020) == 0x0020)
    DeurAchter_Status = 'A'; // 0000.0000.0010.0000    
  if((Domo & 0x0010) == 0x0010)
    TuinAchter_Status = 'S'; // 0000.0000.0001.0000    
  
  
}
