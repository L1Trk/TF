//This class implementes the tracklet engine
#ifndef FPGATRACKLETCALCULATOR_H
#define FPGATRACKLETCALCULATOR_H

#include "IMATH_TrackletCalculator.hh"
#include "IMATH_TrackletCalculatorDisk.hh"
#include "IMATH_TrackletCalculatorOverlap.hh"

#include "FPGAProcessBase.hh"
#include "FPGATrackletProjections.hh"

using namespace std;

class FPGATrackletCalculator:public FPGAProcessBase{

public:

  FPGATrackletCalculator(string name, unsigned int iSector):
    FPGAProcessBase(name,iSector){
    double dphi=two_pi/NSector;
    double dphiHG=0.0;
    if (hourglass) {
      dphiHG=0.5*(dphisectorHG-two_pi/NSector);
    }
    phimin_=iSector_*dphi-dphiHG;
    phimax_=phimin_+dphi+2*dphiHG;
    if (hourglass) {
      phimin_-=0.5*two_pi/NSector;
      phimax_-=0.5*two_pi/NSector;
    }
    if (phimin_>0.5*two_pi) phimin_-=two_pi;
    if (phimax_>0.5*two_pi) phimax_-=two_pi;
    if (phimin_>phimax_)  phimin_-=two_pi;
    if (hourglass) {
      phioffset_=phimin_;
    } else {
      phioffset_=phimin_-dphi/6.0;
    }

    maxtracklet_=63;
    if (hourglass) maxtracklet_=127;
    
   trackletproj_L1PHI1_=0;
   trackletproj_L1PHI2_=0;
   trackletproj_L1PHI3_=0;
   trackletproj_L1PHI4_=0;
   trackletproj_L1PHI5_=0;
   trackletproj_L1PHI6_=0;
   trackletproj_L1PHI7_=0;
   trackletproj_L1PHI8_=0;
   

   trackletproj_L2PHI1_=0;
   trackletproj_L2PHI2_=0;
   trackletproj_L2PHI3_=0;
   trackletproj_L2PHI4_=0;

   trackletproj_L3PHI1_=0;
   trackletproj_L3PHI2_=0;
   trackletproj_L3PHI3_=0;
   trackletproj_L3PHI4_=0;

   trackletproj_L4PHI1_=0;
   trackletproj_L4PHI2_=0;
   trackletproj_L4PHI3_=0;
   trackletproj_L4PHI4_=0;

   trackletproj_L5PHI1_=0;
   trackletproj_L5PHI2_=0;
   trackletproj_L5PHI3_=0;
   trackletproj_L5PHI4_=0;

   trackletproj_L6PHI1_=0;
   trackletproj_L6PHI2_=0;
   trackletproj_L6PHI3_=0;
   trackletproj_L6PHI4_=0;

   trackletproj_L1Plus_=0; 
   trackletproj_L1Minus_=0;
                         
   trackletproj_L2Plus_=0; 
   trackletproj_L2Minus_=0;
                         
   trackletproj_L3Plus_=0; 
   trackletproj_L3Minus_=0;
                         
   trackletproj_L4Plus_=0; 
   trackletproj_L4Minus_=0;
                         
   trackletproj_L5Plus_=0; 
   trackletproj_L5Minus_=0;
                         
   trackletproj_L6Plus_=0; 
   trackletproj_L6Minus_=0;

   trackletproj_D1PHI1_=0;
   trackletproj_D1PHI2_=0;
   trackletproj_D1PHI3_=0;
   trackletproj_D1PHI4_=0;

   trackletproj_D2PHI1_=0;
   trackletproj_D2PHI2_=0;
   trackletproj_D2PHI3_=0;
   trackletproj_D2PHI4_=0;

   trackletproj_D3PHI1_=0;
   trackletproj_D3PHI2_=0;
   trackletproj_D3PHI3_=0;
   trackletproj_D3PHI4_=0;

   trackletproj_D4PHI1_=0;
   trackletproj_D4PHI2_=0;
   trackletproj_D4PHI3_=0;
   trackletproj_D4PHI4_=0;

   trackletproj_D5PHI1_=0;
   trackletproj_D5PHI2_=0;
   trackletproj_D5PHI3_=0;
   trackletproj_D5PHI4_=0;

   trackletproj_D1Plus_=0; 
   trackletproj_D1Minus_=0;
                         
   trackletproj_D2Plus_=0; 
   trackletproj_D2Minus_=0;
                         
   trackletproj_D3Plus_=0; 
   trackletproj_D3Minus_=0;
                         
   trackletproj_D4Plus_=0; 
   trackletproj_D4Minus_=0;
                         
   trackletproj_D5Plus_=0; 
   trackletproj_D5Minus_=0;

  
   layer_=0;
   disk_=0;

   if (name_[3]=='L') layer_=name_[4]-'0';    
   if (name_[3]=='D') disk_=name_[4]-'0';    


   // set TC index
   int iTC = -1;
   int iSeed = -1;
   
   if      (name_[7]=='A') iTC =0;
   else if (name_[7]=='B') iTC =1;
   else if (name_[7]=='C') iTC =2;
   else if (name_[7]=='D') iTC =3;
   else if (name_[7]=='E') iTC =4;
   else if (name_[7]=='F') iTC =5;
   else if (name_[7]=='G') iTC =6;
   else if (name_[7]=='H') iTC =7;
   else if (name_[7]=='I') iTC =8;
   else if (name_[7]=='J') iTC =9;
   else if (name_[7]=='K') iTC =10;
   else if (name_[7]=='L') iTC =11;
   else if (name_[7]=='M') iTC =12;
   else if (name_[7]=='N') iTC =13;
   else if (name_[7]=='O') iTC =14;

   assert(iTC!=-1);
   
   if (name_.substr(3,4)=="L1L2") iSeed = 0;
   else if (name_.substr(3,4)=="L3L4") iSeed = 2;
   else if (name_.substr(3,4)=="L5L6") iSeed = 3;
   else if (name_.substr(3,4)=="D1D2") iSeed = 4;
   else if (name_.substr(3,4)=="D3D4") iSeed = 5;
   else if (name_.substr(3,4)=="D1L1") iSeed = 6;
   else if (name_.substr(3,4)=="D1L2") iSeed = 7;
   else if (name_.substr(3,4)=="L1D1") iSeed = 6;
   else if (name_.substr(3,4)=="L2D1") iSeed = 7;
   else if (name_.substr(3,4)=="L2L3") iSeed = 1;

   assert(iSeed!=-1);

   if (hourglass) {
     TCIndex_ = (iSeed<<4) + iTC;
     assert(TCIndex_>=0 && TCIndex_<128);
   } else {
     TCIndex_ = (iSeed<<3) + iTC;
     assert(TCIndex_>=0 && TCIndex_<64);
   }
     
   //if (hourglass) {
   //if (iSeed!=0)  TCIndex_+=8;
     //cout << "iTC iSeed TCIndex_ "<<iTC<<" "<<iSeed<<" "<<TCIndex_<<endl;
   //}
   
   
   assert((layer_!=0)||(disk_!=0));

   
   if (iSeed==0||iSeed==1||iSeed==2||iSeed==3) {
     if (layer_==1) {
       rproj_[0]=rmeanL3;
       rproj_[1]=rmeanL4;
       rproj_[2]=rmeanL5;
       rproj_[3]=rmeanL6;
       lproj_[0]=3;
       lproj_[1]=4;
       lproj_[2]=5;
       lproj_[3]=6;
     }

     if (layer_==2) {
       rproj_[0]=rmeanL1;
       rproj_[1]=rmeanL4;
       rproj_[2]=rmeanL5;
       rproj_[3]=rmeanL6;
       lproj_[0]=1;
       lproj_[1]=4;
       lproj_[2]=5;
       lproj_[3]=6;
     }
      
     if (layer_==3) {
       rproj_[0]=rmeanL1;
       rproj_[1]=rmeanL2;
       rproj_[2]=rmeanL5;
       rproj_[3]=rmeanL6;
       lproj_[0]=1;
       lproj_[1]=2;
       lproj_[2]=5;
       lproj_[3]=6;
     }
	  
     if (layer_==5) {
       rproj_[0]=rmeanL1;
       rproj_[1]=rmeanL2;
       rproj_[2]=rmeanL3;
       rproj_[3]=rmeanL4;
       lproj_[0]=1;
       lproj_[1]=2;
       lproj_[2]=3;
       lproj_[3]=4;
     }
   }

   if (iSeed==4||iSeed==5) {
     if (disk_==1) {
       zproj_[0]=zmeanD3;
       zproj_[1]=zmeanD4;
       zproj_[2]=zmeanD5;
       dproj_[0]=3;
       dproj_[1]=4;
       dproj_[2]=5;
     }
     
     if (disk_==3) {
       zproj_[0]=zmeanD1;
       zproj_[1]=zmeanD2;
       zproj_[2]=zmeanD5;
       dproj_[0]=1;
       dproj_[1]=2;
       dproj_[2]=5;
     }
   }


   if (iSeed==6||iSeed==7) {
     zprojoverlap_[0]=zmeanD2;
     zprojoverlap_[1]=zmeanD3;
     zprojoverlap_[2]=zmeanD4;
     zprojoverlap_[3]=zmeanD5;
   }
      
  }

  void addOutputProjection(FPGATrackletProjections* &outputProj, FPGAMemoryBase* memory){
      outputProj=dynamic_cast<FPGATrackletProjections*>(memory);
      assert(outputProj!=0);
  }
  
  void addOutput(FPGAMemoryBase* memory,string output){
    if (writetrace) {
      cout << "In "<<name_<<" adding output to "<<memory->getName()
	   << " to output "<<output<<endl;
    }
    if (output=="trackpar"){
      FPGATrackletParameters* tmp=dynamic_cast<FPGATrackletParameters*>(memory);
      assert(tmp!=0);
      trackletpars_=tmp;
      return;
    }


    if (output=="projoutL1PHI1"||output=="projoutL1PHIA") {
      addOutputProjection(trackletproj_L1PHI1_,memory);
      return;
    }
    
    if (output=="projoutL1PHI2"||output=="projoutL1PHIB") {
      addOutputProjection(trackletproj_L1PHI2_,memory);
      return;
    }

    if (output=="projoutL1PHI3"||output=="projoutL1PHIC"){
      addOutputProjection(trackletproj_L1PHI3_,memory);
      return;
    }

    if (output=="projoutL1PHID"){
      addOutputProjection(trackletproj_L1PHI4_,memory);
      return;
    }

    if (output=="projoutL1PHIE"){
      addOutputProjection(trackletproj_L1PHI5_,memory);
      return;
    }

    if (output=="projoutL1PHIF"){
      addOutputProjection(trackletproj_L1PHI6_,memory);
      return;
    }

    if (output=="projoutL1PHIG"){
      addOutputProjection(trackletproj_L1PHI7_,memory);
      return;
    }

    if (output=="projoutL1PHIH"){
      addOutputProjection(trackletproj_L1PHI8_,memory);
      return;
    }

    if (output=="projoutL2PHI1"||output=="projoutL2PHIA"){
      addOutputProjection(trackletproj_L2PHI1_,memory);
      return;
    }

    if (output=="projoutL2PHI2"||output=="projoutL2PHIB"){
      addOutputProjection(trackletproj_L2PHI2_,memory);
      return;
    }

    if (output=="projoutL2PHI3"||output=="projoutL2PHIC"){
      addOutputProjection(trackletproj_L2PHI3_,memory);
      return;
    }

    if (output=="projoutL2PHI4"||output=="projoutL2PHID"){
      addOutputProjection(trackletproj_L2PHI4_,memory);
      return;
    }

    if (output=="projoutL3PHI1"||output=="projoutL3PHIA"){
      addOutputProjection(trackletproj_L3PHI1_,memory);
      return;
    }

    if (output=="projoutL3PHI2"||output=="projoutL3PHIB"){
      addOutputProjection(trackletproj_L3PHI2_,memory);
      return;
    }

    if (output=="projoutL3PHI3"||output=="projoutL3PHIC"){
      addOutputProjection(trackletproj_L3PHI3_,memory);
      return;
    }

    if (output=="projoutL3PHI4"||output=="projoutL3PHID"){
      addOutputProjection(trackletproj_L3PHI4_,memory);
      return;
    }

    if (output=="projoutL4PHI1"||output=="projoutL4PHIA"){
      addOutputProjection(trackletproj_L4PHI1_,memory);
      return;
    }

    if (output=="projoutL4PHI2"||output=="projoutL4PHIB"){
      addOutputProjection(trackletproj_L4PHI2_,memory);
      return;
    }

    if (output=="projoutL4PHI3"||output=="projoutL4PHIC"){
      addOutputProjection(trackletproj_L4PHI3_,memory);
      return;
    }

    if (output=="projoutL4PHI4"||output=="projoutL4PHID"){
      addOutputProjection(trackletproj_L4PHI4_,memory);
      return;
    }

    if (output=="projoutL5PHI1"||output=="projoutL5PHIA"){
      addOutputProjection(trackletproj_L5PHI1_,memory);
      return;
    }

    if (output=="projoutL5PHI2"||output=="projoutL5PHIB"){
      addOutputProjection(trackletproj_L5PHI2_,memory);
      return;
    }

    if (output=="projoutL5PHI3"||output=="projoutL5PHIC"){
      addOutputProjection(trackletproj_L5PHI3_,memory);
      return;
    }

    if (output=="projoutL5PHI4"||output=="projoutL5PHID"){
      addOutputProjection(trackletproj_L5PHI4_,memory);
      return;
    }

    if (output=="projoutL6PHI1"||output=="projoutL6PHIA"){
      addOutputProjection(trackletproj_L6PHI1_,memory);
      return;
    }

    if (output=="projoutL6PHI2"||output=="projoutL6PHIB"){
      addOutputProjection(trackletproj_L6PHI2_,memory);
      return;
    }

    if (output=="projoutL6PHI3"||output=="projoutL6PHIC"){
      addOutputProjection(trackletproj_L6PHI3_,memory);
      return;
    }

    if (output=="projoutL6PHI4"||output=="projoutL6PHID"){
      addOutputProjection(trackletproj_L6PHI4_,memory);
      return;
    }

    if (output=="projoutD1PHI1"||output=="projoutD1PHIA"){
      addOutputProjection(trackletproj_D1PHI1_,memory);
      return;
    }

    if (output=="projoutD1PHI2"||output=="projoutD1PHIB"){
      addOutputProjection(trackletproj_D1PHI2_,memory);
      return;
    }

    if (output=="projoutD1PHI3"||output=="projoutD1PHIC"){
      addOutputProjection(trackletproj_D1PHI3_,memory);
      return;
    }

    if (output=="projoutD1PHI4"||output=="projoutD1PHID"){
      addOutputProjection(trackletproj_D1PHI4_,memory);
      return;
    }

    if (output=="projoutD2PHI1"||output=="projoutD2PHIA"){
      addOutputProjection(trackletproj_D2PHI1_,memory);
      return;
    }

    if (output=="projoutD2PHI2"||output=="projoutD2PHIB"){
      addOutputProjection(trackletproj_D2PHI2_,memory);
      return;
    }

    if (output=="projoutD2PHI3"||output=="projoutD2PHIC"){
      addOutputProjection(trackletproj_D2PHI3_,memory);
      return;
    }

    if (output=="projoutD2PHI4"||output=="projoutD2PHID"){
      addOutputProjection(trackletproj_D2PHI4_,memory);
      return;
    }



    if (output=="projoutD3PHI1"||output=="projoutD3PHIA"){
      addOutputProjection(trackletproj_D3PHI1_,memory);
      return;
    }

    if (output=="projoutD3PHI2"||output=="projoutD3PHIB"){
      addOutputProjection(trackletproj_D3PHI2_,memory);
      return;
    }

    if (output=="projoutD3PHI3"||output=="projoutD3PHIC"){
      addOutputProjection(trackletproj_D3PHI3_,memory);
      return;
    }
    
    if (output=="projoutD3PHI4"||output=="projoutD3PHID"){
      addOutputProjection(trackletproj_D3PHI4_,memory);
      return;
    }


    if (output=="projoutD4PHI1"||output=="projoutD4PHIA"){
      addOutputProjection(trackletproj_D4PHI1_,memory);
      return;
    }

    if (output=="projoutD4PHI2"||output=="projoutD4PHIB"){
      addOutputProjection(trackletproj_D4PHI2_,memory);
      return;
    }

    if (output=="projoutD4PHI3"||output=="projoutD4PHIC"){
      addOutputProjection(trackletproj_D4PHI3_,memory);
      return;
    }

    if (output=="projoutD4PHI4"||output=="projoutD4PHID"){
      addOutputProjection(trackletproj_D4PHI4_,memory);
      return;
    }
    


    if (output=="projoutD5PHI1"||output=="projoutD5PHIA"){
      addOutputProjection(trackletproj_D5PHI1_,memory);
      return;
    }

    if (output=="projoutD5PHI2"||output=="projoutD5PHIB"){
      addOutputProjection(trackletproj_D5PHI2_,memory);
      return;
    }

    if (output=="projoutD5PHI3"||output=="projoutD5PHIC"){
      addOutputProjection(trackletproj_D5PHI3_,memory);
      return;
    }

    if (output=="projoutD5PHI4"||output=="projoutD5PHID"){
      addOutputProjection(trackletproj_D5PHI4_,memory);
      return;
    }


    
    if (output=="projoutL1ToMinus"){
      addOutputProjection(trackletproj_L1Minus_,memory);
      return;
    }

    if (output=="projoutL1ToPlus"){
      addOutputProjection(trackletproj_L1Plus_,memory);
      return;
    }

    if (output=="projoutL2ToMinus"){
      addOutputProjection(trackletproj_L2Minus_,memory);
      return;
    }

    if (output=="projoutL2ToPlus"){
      addOutputProjection(trackletproj_L2Plus_,memory);
      return;
    }

    if (output=="projoutL3ToMinus"){
      addOutputProjection(trackletproj_L3Minus_,memory);
      return;
    }

    if (output=="projoutL3ToPlus"){
      addOutputProjection(trackletproj_L3Plus_,memory);
      return;
    }

    if (output=="projoutL4ToMinus"){
      addOutputProjection(trackletproj_L4Minus_,memory);
      return;
    }

    if (output=="projoutL4ToPlus"){
      addOutputProjection(trackletproj_L4Plus_,memory);
      return;
    }

    if (output=="projoutL5ToMinus"){
      addOutputProjection(trackletproj_L5Minus_,memory);
      return;
    }

    if (output=="projoutL5ToPlus"){
      addOutputProjection(trackletproj_L5Plus_,memory);
      return;
    }

    if (output=="projoutL6ToMinus"){
      addOutputProjection(trackletproj_L6Minus_,memory);
      return;
    }

    if (output=="projoutL6ToPlus"){
      addOutputProjection(trackletproj_L6Plus_,memory);
      return;
    }

    if (output=="projoutL3D4ToMinus"){
      addOutputProjection(trackletproj_L3Minus_,memory);
      return;
    }

    if (output=="projoutL3D4ToPlus"){
      addOutputProjection(trackletproj_L3Plus_,memory);
      return;
    }

    if (output=="projoutL4D3ToMinus"){
      addOutputProjection(trackletproj_L4Minus_,memory);
      return;
    }

    if (output=="projoutL4D3ToPlus"){
      addOutputProjection(trackletproj_L4Plus_,memory);
      return;
    }

    if (output=="projoutL5D2ToMinus"){
      addOutputProjection(trackletproj_L5Minus_,memory);
      return;
    }

    if (output=="projoutL5D2ToPlus"){
      addOutputProjection(trackletproj_L5Plus_,memory);
      return;
    }

    if (output=="projoutL6D1ToMinus"){
      addOutputProjection(trackletproj_L6Minus_,memory);
      return;
    }

    if (output=="projoutL6D1ToPlus"){
      addOutputProjection(trackletproj_L6Plus_,memory);
      return;
    }


    if (output=="projoutD1ToPlus"){
      addOutputProjection(trackletproj_D1Plus_,memory);
      return;
    }

    if (output=="projoutD2ToPlus"){
      addOutputProjection(trackletproj_D2Plus_,memory);
      return;
    }

    if (output=="projoutD3ToPlus"){
      addOutputProjection(trackletproj_D3Plus_,memory);
      return;
    }

    if (output=="projoutD4ToPlus"){
      addOutputProjection(trackletproj_D4Plus_,memory);
      return;
    }

    if (output=="projoutD5ToPlus"){
      addOutputProjection(trackletproj_D5Plus_,memory);
      return;
    }    
    

    if (output=="projoutD1ToMinus"){
      addOutputProjection(trackletproj_D1Minus_,memory);
      return;
    }

    if (output=="projoutD2ToMinus"){
      addOutputProjection(trackletproj_D2Minus_,memory);
      return;
    }

    if (output=="projoutD3ToMinus"){
      addOutputProjection(trackletproj_D3Minus_,memory);
      return;
    }

    if (output=="projoutD4ToMinus"){
      addOutputProjection(trackletproj_D4Minus_,memory);
      return;
    }

    if (output=="projoutD5ToMinus"){
      addOutputProjection(trackletproj_D5Minus_,memory);
      return;
    }    
    

    cout << "Could not find output : "<<output<<endl;
    assert(0);
  }

  void addInput(FPGAMemoryBase* memory,string input){
    if (writetrace) {
      cout << "In "<<name_<<" adding input from "<<memory->getName()
	   << " to input "<<input<<endl;
    }
    if (input=="innerallstubin"){
      FPGAAllStubs* tmp=dynamic_cast<FPGAAllStubs*>(memory);
      assert(tmp!=0);
      innerallstubs_.push_back(tmp);
      return;
    }
    if (input=="outerallstubin"){
      FPGAAllStubs* tmp=dynamic_cast<FPGAAllStubs*>(memory);
      assert(tmp!=0);
      outerallstubs_.push_back(tmp);
      return;
    }
    if (input=="stubpair1in"||
	input=="stubpair2in"||
	input=="stubpair3in"||
	input=="stubpair4in"||
	input=="stubpair5in"||
	input=="stubpair6in"||
	input=="stubpair7in"||
	input=="stubpair8in"||
	input=="stubpair9in"||
	input=="stubpair10in"||
	input=="stubpair11in"||
	input=="stubpair12in"||
	input=="stubpair13in"||
	input=="stubpair14in"||
	input=="stubpair15in"||
	input=="stubpair16in"||
	input=="stubpair17in"||
	input=="stubpair18in"||
	input=="stubpair19in"||
	input=="stubpair20in"||
	input=="stubpair21in"||
	input=="stubpair22in"||
	input=="stubpair23in"||
	input=="stubpair24in"||
	input=="stubpair25in"||
	input=="stubpair26in"||
	input=="stubpair27in"||
	input=="stubpair28in"||
	input=="stubpair29in"||
	input=="stubpair30in"||
	input=="stubpair31in"||
	input=="stubpair32in"||
	input=="stubpair33in"||
	input=="stubpair34in"||
	input=="stubpair35in"||
	input=="stubpair36in"||
	input=="stubpair37in"||
	input=="stubpair38in"||
	input=="stubpair39in"||
	input=="stubpair40in"||
	input=="stubpair41in"||
	input=="stubpair42in"){
      FPGAStubPairs* tmp=dynamic_cast<FPGAStubPairs*>(memory);
      assert(tmp!=0);
      stubpairs_.push_back(tmp);
      return;
    }
    assert(0);
  }


  void exacttracklet(double r1, double z1, double phi1,
		     double r2, double z2, double phi2, double sigmaz,
		     double& rinv, double& phi0,
		     double& t, double& z0,
		     double phiproj[4], double zproj[4], 
		     double phider[4], double zder[4],
		     double phiprojdisk[5], double rprojdisk[5], 
		     double phiderdisk[5], double rderdisk[5]) {

    double deltaphi=phi1-phi2;

    if (deltaphi>0.5*two_pi) deltaphi-=two_pi;
    if (deltaphi<-0.5*two_pi) deltaphi+=two_pi;
    assert(fabs(deltaphi)<0.5*two_pi);

    
    if (sigmaz<-10.0) {
      cout << "Negative sigmaz"<<endl;
    }

    double dist=sqrt(r2*r2+r1*r1-2*r1*r2*cos(deltaphi));
    
    rinv=2*sin(deltaphi)/dist;

    double phi1tmp=phi1-phimin_+(phimax_-phimin_)/6.0;    

    phi0=phi1tmp+asin(0.5*r1*rinv);
    
    if (phi0>0.5*two_pi) phi0-=two_pi;
    if (phi0<-0.5*two_pi) phi0+=two_pi;
    assert(fabs(phi0)<0.5*two_pi);
    
    double rhopsi1=2*asin(0.5*r1*rinv)/rinv;
	    
    double rhopsi2=2*asin(0.5*r2*rinv)/rinv;
    
    t=(z1-z2)/(rhopsi1-rhopsi2);
    
    z0=z1-t*rhopsi1;

    for (int i=0;i<4;i++) {
      exactproj(rproj_[i],rinv,phi0,t,z0,
		phiproj[i],zproj[i],phider[i],zder[i]);
    }

    for (int i=0;i<5;i++) {
      //int sign=1;
      //if (t<0) sign=-1;
      exactprojdisk(zmean[i],rinv,phi0,t,z0,
		phiprojdisk[i],rprojdisk[i],phiderdisk[i],rderdisk[i]);
    }



  }


  void exacttrackletdisk(double r1, double z1, double phi1,
			 double r2, double z2, double phi2, double sigmaz,
			 double& rinv, double& phi0,
			 double& t, double& z0,
			 double phiprojLayer[3], double zprojLayer[3], 
			 double phiderLayer[3], double zderLayer[3],
			 double phiproj[3], double rproj[3], 
			 double phider[3], double rder[3]) {

    double deltaphi=phi1-phi2;

    if (deltaphi>0.5*two_pi) deltaphi-=two_pi;
    if (deltaphi<-0.5*two_pi) deltaphi+=two_pi;
    assert(fabs(deltaphi)<0.5*two_pi);

    if (sigmaz<-10.0) {
      cout << "Negative sigmaz"<<endl;
    }

    double dist=sqrt(r2*r2+r1*r1-2*r1*r2*cos(deltaphi));
    
    rinv=2*sin(deltaphi)/dist;

    double phi1tmp=phi1-phimin_+(phimax_-phimin_)/6.0;    

    //cout << "phi1 phi2 phi1tmp : "<<phi1<<" "<<phi2<<" "<<phi1tmp<<endl;

    phi0=phi1tmp+asin(0.5*r1*rinv);
    
    if (phi0>0.5*two_pi) phi0-=two_pi;
    if (phi0<-0.5*two_pi) phi0+=two_pi;
    if (!(fabs(phi0)<0.5*two_pi)) {
      cout << "phi1tmp r1 rinv phi0 deltaphi dist: "
	   <<phi1tmp<<" "<<r1<<" "<<rinv<<" "<<phi0
	   <<" "<<deltaphi<<" "<<dist<<endl;
      exit(1);
    }
    
    double rhopsi1=2*asin(0.5*r1*rinv)/rinv;
	    
    double rhopsi2=2*asin(0.5*r2*rinv)/rinv;
    
    t=(z1-z2)/(rhopsi1-rhopsi2);
    
    z0=z1-t*rhopsi1;

    if (disk_==1) {
      if (dumppars) {
	cout << "------------------------------------------------"<<endl;
	cout << "DUMPPARS0:" 
	     <<" dz= "<<z2-z1
	     <<" rinv= "<<rinv
	     <<" phi0= "<<phi0
	     <<" t= "<<t
	     <<" z0= "<<z0
	     <<endl;
      }
    }


    for (int i=0;i<3;i++) {
      exactprojdisk(zproj_[i],rinv,phi0,t,z0,
		    phiproj[i],rproj[i],
		    phider[i],rder[i]);
    }


    for (int i=0;i<3;i++) {
      exactproj(rmean[i],rinv,phi0,t,z0,
		    phiprojLayer[i],zprojLayer[i],
		    phiderLayer[i],zderLayer[i]);
    }


  }

  void exacttrackletOverlap(double r1, double z1, double phi1,
			    double r2, double z2, double phi2, double sigmaz,
			    double& rinv, double& phi0,
			    double& t, double& z0,
			    double phiprojLayer[3], double zprojLayer[3], 
			    double phiderLayer[3], double zderLayer[3],
			    double phiproj[3], double rproj[3], 
			    double phider[3], double rder[3]) {

    double deltaphi=phi1-phi2;

    if (deltaphi>0.5*two_pi) deltaphi-=two_pi;
    if (deltaphi<-0.5*two_pi) deltaphi+=two_pi;
    assert(fabs(deltaphi)<0.5*two_pi);

    if (sigmaz<-10.0) {
      cout << "Negative sigmaz"<<endl;
    }

    double dist=sqrt(r2*r2+r1*r1-2*r1*r2*cos(deltaphi));
    
    rinv=2*sin(deltaphi)/dist;

    if (r1>r2) rinv=-rinv;

    double phi1tmp=phi1-phimin_+(phimax_-phimin_)/6.0;    

    //cout << "phi1 phi2 phi1tmp : "<<phi1<<" "<<phi2<<" "<<phi1tmp<<endl;

    phi0=phi1tmp+asin(0.5*r1*rinv);
    
    if (phi0>0.5*two_pi) phi0-=two_pi;
    if (phi0<-0.5*two_pi) phi0+=two_pi;
    if (!(fabs(phi0)<0.5*two_pi)) {
      cout << "phi1tmp r1 rinv phi0 deltaphi dist: "
	   <<phi1tmp<<" "<<r1<<" "<<rinv<<" "<<phi0
	   <<" "<<deltaphi<<" "<<dist<<endl;
      exit(1);
    }
    
    double rhopsi1=2*asin(0.5*r1*rinv)/rinv;
	    
    double rhopsi2=2*asin(0.5*r2*rinv)/rinv;
    
    t=(z1-z2)/(rhopsi1-rhopsi2);
    
    z0=z1-t*rhopsi1;


    if (disk_==1) {
      if (dumppars) {
	cout << "------------------------------------------------"<<endl;
	cout << "DUMPPARS0:" 
	     <<" dz= "<<z2-z1
	     <<" rinv= "<<rinv
	     <<" phi0= "<<phi0
	     <<" t= "<<t
	     <<" z0= "<<z0
	     <<endl;
      }
    }


    for (int i=0;i<4;i++) {
      exactprojdisk(zprojoverlap_[i],rinv,phi0,t,z0,
		    phiproj[i],rproj[i],
		    phider[i],rder[i]);
    }


    for (int i=0;i<1;i++) {
      exactproj(rmean[i],rinv,phi0,t,z0,
		    phiprojLayer[i],zprojLayer[i],
		    phiderLayer[i],zderLayer[i]);
    }


  }


  void exactproj(double rproj,double rinv,double phi0,
		  double t, double z0,
		  double &phiproj, double &zproj,
		  double &phider, double &zder) {

    phiproj=phi0-asin(0.5*rproj*rinv);
    zproj=z0+(2*t/rinv)*asin(0.5*rproj*rinv);

    phider=-0.5*rinv/sqrt(1-pow(0.5*rproj*rinv,2));
    zder=t/sqrt(1-pow(0.5*rproj*rinv,2));

  }


  void exactprojdisk(double zproj,double rinv,double phi0,
		     double t, double z0,
		     double &phiproj, double &rproj,
		     double &phider, double &rder) {

    if (t<0) zproj=-zproj;
    
    double tmp=rinv*(zproj-z0)/(2.0*t);
    rproj=(2.0/rinv)*sin(tmp);
    phiproj=phi0-tmp;


    //if (fabs(1.0/rinv)>180.0&&fabs(z0)<15.0) {
    //  cout << "phiproj phi0 tmp zproj z0 t: "<<phiproj<<" "<<phi0
    //	   <<" "<<tmp<<" "<<zproj<<" "<<z0<<" "<<t<<endl;
    //}

    if (dumpproj) {
      if (fabs(zproj+300.0)<10.0) {
	cout << "DUMPPROJDISK1: "
	       << " phi="<<phiproj
	       << " r="<<rproj
	       << endl;
	}
      }


    phider=-rinv/(2*t);
    rder=cos(tmp)/t;

    //assert(fabs(phider)<0.1);

  } 

  void execute() {

    unsigned int countall=0;
    unsigned int countsel=0;

    //cout << "FPGATrackletCalculator execute "<<getName()<<" "<<stubpairs_.size()<<endl;
    
    for(unsigned int l=0;l<stubpairs_.size();l++){
      if (trackletpars_->nTracklets()>=maxtracklet_) {
	cout << "Will break on too many tracklets in "<<getName()<<endl;
	break;
      }
      for(unsigned int i=0;i<stubpairs_[l]->nStubPairs();i++){

	countall++;
	L1TStub* innerStub=stubpairs_[l]->getL1TStub1(i);
	FPGAStub* innerFPGAStub=stubpairs_[l]->getFPGAStub1(i);

	L1TStub* outerStub=stubpairs_[l]->getL1TStub2(i);
	FPGAStub* outerFPGAStub=stubpairs_[l]->getFPGAStub2(i);

	if (debug1) {
	  cout << "FPGATrackletCalculator execute "<<getName()<<"["<<iSector_<<"]"<<endl;
	}
	
	if (innerFPGAStub->isBarrel()&&(getName()!="TC_D1L2A"&&getName()!="TC_D1L2B")){


          if (outerFPGAStub->isDisk()) {

            //overlap seeding                                              
            bool accept = overlapSeeding(outerFPGAStub,outerStub,innerFPGAStub,innerStub);
            if (accept) countsel++;

          } else {
	  
	    //barrel+barrel seeding	  
	    bool accept = barrelSeeding(innerFPGAStub,innerStub,outerFPGAStub,outerStub);
	    
	    if (accept) countsel++;

	  }
	  
	}  else {

	  if (outerFPGAStub->isDisk()) {

	    //disk+disk seeding

	    bool accept = diskSeeding(innerFPGAStub,innerStub,outerFPGAStub,outerStub);

	    if (accept) countsel++;
	    

	  } else if (innerFPGAStub->isDisk()) {


	    //layer+disk seeding
	    
	    bool accept = overlapSeeding(innerFPGAStub,innerStub,outerFPGAStub,outerStub);

	    if (accept) countsel++;


	  } else {

	    assert(0);
	    
	  }
	}

	if (trackletpars_->nTracklets()>=maxtracklet_) {
	  cout << "Will break on number of tracklets in "<<getName()<<endl;
	  break;
	}
	
	if (countall>=MAXTC) {
	  if (debug1) cout << "Will break on MAXTC 1"<<endl;
	  break;
	}
	if (debug1) {
	  cout << "FPGATrackletCalculator execute done"<<endl;
	}

      }
      if (countall>=MAXTC) {
	if (debug1) cout << "Will break on MAXTC 2"<<endl;
	break;
      }
    }

    if (writeTrackletCalculator) {
      static ofstream out("trackletcalculator.txt");
      out << getName()<<" "<<countall<<" "<<countsel<<endl;
    }


  }


  void addDiskProj(FPGATracklet* tracklet, int disk){

    
    FPGAWord fpgar=tracklet->fpgarprojdisk(disk);

    if (fpgar.value()*krprojshiftdisk<12.0) return;
    if (fpgar.value()*krprojshiftdisk>112.0) return;

    //cout << "addDiskProj neighbor: "<<tracklet->plusNeighborDisk(disk)<<" "<<tracklet->minusNeighborDisk(disk)<<endl;

    if (tracklet->plusNeighborDisk(disk)) {
      if (getName().find("L1L2")!=std::string::npos) {
	if (abs(disk)==1) addNeighborProjectionDisk(disk,trackletproj_L6Plus_,tracklet);
	if (abs(disk)==2) addNeighborProjectionDisk(disk,trackletproj_L5Plus_,tracklet);
	if (abs(disk)==3) addNeighborProjectionDisk(disk,trackletproj_L4Plus_,tracklet);
	if (abs(disk)==4) addNeighborProjectionDisk(disk,trackletproj_L3Plus_,tracklet);
	return;
      }
      if (getName().find("L3L4")!=std::string::npos) {
	if (abs(disk)==1) addNeighborProjectionDisk(disk,trackletproj_L6Plus_,tracklet);
	if (abs(disk)==2) addNeighborProjectionDisk(disk,trackletproj_L5Plus_,tracklet);
	return;
      }
      if (abs(disk)==1) addNeighborProjectionDisk(disk,trackletproj_D1Plus_,tracklet);
      if (abs(disk)==2) addNeighborProjectionDisk(disk,trackletproj_D2Plus_,tracklet);
      if (abs(disk)==3) addNeighborProjectionDisk(disk,trackletproj_D3Plus_,tracklet);
      if (abs(disk)==4) addNeighborProjectionDisk(disk,trackletproj_D4Plus_,tracklet);
      if (abs(disk)==5) addNeighborProjectionDisk(disk,trackletproj_D5Plus_,tracklet);
      return;
    }
      
    if (tracklet->minusNeighborDisk(disk)) {
      if (getName().find("L1L2")!=std::string::npos) {
	if (abs(disk)==1) addNeighborProjectionDisk(disk,trackletproj_L6Minus_,tracklet);
	if (abs(disk)==2) addNeighborProjectionDisk(disk,trackletproj_L5Minus_,tracklet);
	if (abs(disk)==3) addNeighborProjectionDisk(disk,trackletproj_L4Minus_,tracklet);
	if (abs(disk)==4) addNeighborProjectionDisk(disk,trackletproj_L3Minus_,tracklet);
	return;
      }
      if (getName().find("L3L4")!=std::string::npos) {
	if (abs(disk)==1) addNeighborProjectionDisk(disk,trackletproj_L6Minus_,tracklet);
	if (abs(disk)==2) addNeighborProjectionDisk(disk,trackletproj_L5Minus_,tracklet);
	return;
      }

      if (abs(disk)==1) addNeighborProjectionDisk(disk,trackletproj_D1Minus_,tracklet);
      if (abs(disk)==2) addNeighborProjectionDisk(disk,trackletproj_D2Minus_,tracklet);
      if (abs(disk)==3) addNeighborProjectionDisk(disk,trackletproj_D3Minus_,tracklet);
      if (abs(disk)==4) addNeighborProjectionDisk(disk,trackletproj_D4Minus_,tracklet);
      if (abs(disk)==5) addNeighborProjectionDisk(disk,trackletproj_D5Minus_,tracklet);
      return;
    }
      
    
    FPGAWord fpgaphi=tracklet->fpgaphiprojdisk(disk);
    
    int iphivmRaw=fpgaphi.value()>>(fpgaphi.nbits()-5);

    int iphi=-1;


    if (hourglass) {

      iphi=iphivmRaw/(32/nallstubsdisks[abs(disk)-1]);
      
    } else {
    
      assert(iphivmRaw>=4);
      assert(iphivmRaw<=27);

      iphi=(iphivmRaw-4)>>3;

      assert(iphi>=0);
      assert(iphi<=2);

    }
    
    if (abs(disk)==1) {
      if (iphi==0) addProjectionDisk(disk,iphi,trackletproj_D1PHI1_,tracklet);
      if (iphi==1) addProjectionDisk(disk,iphi,trackletproj_D1PHI2_,tracklet);
      if (iphi==2) addProjectionDisk(disk,iphi,trackletproj_D1PHI3_,tracklet);
      if (iphi==3) addProjectionDisk(disk,iphi,trackletproj_D1PHI4_,tracklet);
    }
    
    if (abs(disk)==2) {
      if (iphi==0) addProjectionDisk(disk,iphi,trackletproj_D2PHI1_,tracklet);
      if (iphi==1) addProjectionDisk(disk,iphi,trackletproj_D2PHI2_,tracklet);
      if (iphi==2) addProjectionDisk(disk,iphi,trackletproj_D2PHI3_,tracklet);
      if (iphi==3) addProjectionDisk(disk,iphi,trackletproj_D2PHI4_,tracklet);
    }

    if (abs(disk)==3) {
      if (iphi==0) addProjectionDisk(disk,iphi,trackletproj_D3PHI1_,tracklet);
      if (iphi==1) addProjectionDisk(disk,iphi,trackletproj_D3PHI2_,tracklet);
      if (iphi==2) addProjectionDisk(disk,iphi,trackletproj_D3PHI3_,tracklet);
      if (iphi==3) addProjectionDisk(disk,iphi,trackletproj_D3PHI4_,tracklet);
    }

    if (abs(disk)==4) {
      if (iphi==0) addProjectionDisk(disk,iphi,trackletproj_D4PHI1_,tracklet);
      if (iphi==1) addProjectionDisk(disk,iphi,trackletproj_D4PHI2_,tracklet);
      if (iphi==2) addProjectionDisk(disk,iphi,trackletproj_D4PHI3_,tracklet);
      if (iphi==3) addProjectionDisk(disk,iphi,trackletproj_D4PHI4_,tracklet);
    }

    if (abs(disk)==5) {
      if (iphi==0) addProjectionDisk(disk,iphi,trackletproj_D5PHI1_,tracklet);
      if (iphi==1) addProjectionDisk(disk,iphi,trackletproj_D5PHI2_,tracklet);
      if (iphi==2) addProjectionDisk(disk,iphi,trackletproj_D5PHI3_,tracklet);
      if (iphi==3) addProjectionDisk(disk,iphi,trackletproj_D5PHI4_,tracklet);
    }

    
  }


  bool addLayerProj(FPGATracklet* tracklet, int layer){

    
    assert(layer>0);

    FPGAWord fpgaz=tracklet->fpgazproj(layer);
    FPGAWord fpgaphi=tracklet->fpgaphiproj(layer);


    if(fpgaphi.atExtreme()) cout<<"at extreme! "<<fpgaphi.value()<<"\n";

    assert(!fpgaphi.atExtreme());
    
    if (fpgaz.atExtreme()) return false;

    if (fabs(fpgaz.value()*kz)>zlength) return false;

    if (hourglass) {
      assert(!tracklet->plusNeighbor(layer));
      assert(!tracklet->minusNeighbor(layer));
    }
    
    if (tracklet->plusNeighbor(layer)) {
      if (layer==1) addNeighborProjection(layer,trackletproj_L1Plus_,tracklet);
      if (layer==2) addNeighborProjection(layer,trackletproj_L2Plus_,tracklet);
      if (layer==3) addNeighborProjection(layer,trackletproj_L3Plus_,tracklet);
      if (layer==4) addNeighborProjection(layer,trackletproj_L4Plus_,tracklet);
      if (layer==5) addNeighborProjection(layer,trackletproj_L5Plus_,tracklet);
      if (layer==6) addNeighborProjection(layer,trackletproj_L6Plus_,tracklet);
      return true;
    }
      
    if (tracklet->minusNeighbor(layer)) {
      if (layer==1) addNeighborProjection(layer,trackletproj_L1Minus_,tracklet);
      if (layer==2) addNeighborProjection(layer,trackletproj_L2Minus_,tracklet);
      if (layer==3) addNeighborProjection(layer,trackletproj_L3Minus_,tracklet);
      if (layer==4) addNeighborProjection(layer,trackletproj_L4Minus_,tracklet);
      if (layer==5) addNeighborProjection(layer,trackletproj_L5Minus_,tracklet);
      if (layer==6) addNeighborProjection(layer,trackletproj_L6Minus_,tracklet);
      return true;
    }
      


    int iphivmRaw=fpgaphi.value()>>(fpgaphi.nbits()-5);

    int iphi=-1;
    
    if (hourglass) {
      
      iphi=iphivmRaw/(32/nallstubslayers[layer-1]);
      
    } else {

      assert(iphivmRaw>=4);
      assert(iphivmRaw<=27);

      iphi=(iphivmRaw-4)>>3;

      if (layer==2||layer==4||layer==6) {
	iphi=(iphivmRaw>>3);
      }
      assert(iphi>=0);
      assert(iphi<=7);
      

    }
      
 
    //cout << "layer fpgaphi iphivmRaw iphi : "<<layer<<" "<<fpgaphi.value()<<" "<<iphivmRaw<<" "<<iphi<<endl;

    

    if (layer==1) {
      if (iphi==0) addProjection(layer,iphi,trackletproj_L1PHI1_,tracklet);
      if (iphi==1) addProjection(layer,iphi,trackletproj_L1PHI2_,tracklet);
      if (iphi==2) addProjection(layer,iphi,trackletproj_L1PHI3_,tracklet);
      if (iphi==3) addProjection(layer,iphi,trackletproj_L1PHI4_,tracklet);
      if (iphi==4) addProjection(layer,iphi,trackletproj_L1PHI5_,tracklet);
      if (iphi==5) addProjection(layer,iphi,trackletproj_L1PHI6_,tracklet);
      if (iphi==6) addProjection(layer,iphi,trackletproj_L1PHI7_,tracklet);
      if (iphi==7) addProjection(layer,iphi,trackletproj_L1PHI8_,tracklet);
    }
    
    if (layer==2) {
      if (iphi==0) addProjection(layer,iphi,trackletproj_L2PHI1_,tracklet);
      if (iphi==1) addProjection(layer,iphi,trackletproj_L2PHI2_,tracklet);
      if (iphi==2) addProjection(layer,iphi,trackletproj_L2PHI3_,tracklet);
      if (iphi==3) addProjection(layer,iphi,trackletproj_L2PHI4_,tracklet);
    }

    if (layer==3) {
      if (iphi==0) addProjection(layer,iphi,trackletproj_L3PHI1_,tracklet);
      if (iphi==1) addProjection(layer,iphi,trackletproj_L3PHI2_,tracklet);
      if (iphi==2) addProjection(layer,iphi,trackletproj_L3PHI3_,tracklet);
      if (iphi==3) addProjection(layer,iphi,trackletproj_L3PHI4_,tracklet);
    }

    if (layer==4) {
      if (iphi==0) addProjection(layer,iphi,trackletproj_L4PHI1_,tracklet);
      if (iphi==1) addProjection(layer,iphi,trackletproj_L4PHI2_,tracklet);
      if (iphi==2) addProjection(layer,iphi,trackletproj_L4PHI3_,tracklet);
      if (iphi==3) addProjection(layer,iphi,trackletproj_L4PHI4_,tracklet);
    }

    if (layer==5) {
      if (iphi==0) addProjection(layer,iphi,trackletproj_L5PHI1_,tracklet);
      if (iphi==1) addProjection(layer,iphi,trackletproj_L5PHI2_,tracklet);
      if (iphi==2) addProjection(layer,iphi,trackletproj_L5PHI3_,tracklet);
      if (iphi==3) addProjection(layer,iphi,trackletproj_L5PHI4_,tracklet);
    }

    if (layer==6) {
      if (iphi==0) addProjection(layer,iphi,trackletproj_L6PHI1_,tracklet);
      if (iphi==1) addProjection(layer,iphi,trackletproj_L6PHI2_,tracklet);
      if (iphi==2) addProjection(layer,iphi,trackletproj_L6PHI3_,tracklet);
      if (iphi==3) addProjection(layer,iphi,trackletproj_L6PHI4_,tracklet);
    }

    return true;

  }

  void addProjection(int layer,int iphi,FPGATrackletProjections* trackletprojs, FPGATracklet* tracklet){
    if (trackletprojs==0) {
      if (warnNoMem) {
	cout << "No projection memory exists in "<<getName()<<" for layer = "<<layer<<" iphi = "<<iphi+1<<endl;
      }
      return;
    }
    assert(trackletprojs!=0);
    trackletprojs->addProj(tracklet);
  }

  void addProjectionDisk(int disk,int iphi,FPGATrackletProjections* trackletprojs, FPGATracklet* tracklet){
    if (trackletprojs==0) {
      if (layer_==3&&abs(disk)==3) return; //L3L4 projections to D3 are not used.
      if (warnNoMem) {       
	cout << "No projection memory exists in "<<getName()<<" for disk = "<<abs(disk)<<" iphi = "<<iphi+1<<endl;
      }
      return;
    }
    assert(trackletprojs!=0);
    trackletprojs->addProj(tracklet);
  }

  void addNeighborProjection(int layer, FPGATrackletProjections* trackletprojs,FPGATracklet* tracklet){
    if (trackletprojs==0) {
      if (warnNoMem) {
	string str="";
	if (tracklet->minusNeighbor(layer)){
	  str="Minus";
	}
	if (tracklet->plusNeighbor(layer)){
	  str="Plus";
	}
	assert(str!="");
	cout << "Error no projection memory exists in "<<getName()<<" for layer = "<<layer<<" to "
	     <<str<<" neighbor"<<endl;
      }
      return;
    }
    assert(trackletprojs!=0);
    trackletprojs->addProj(tracklet);
  

  }

  
  void addNeighborProjectionDisk(int disk, FPGATrackletProjections* trackletprojs,FPGATracklet* tracklet){

    if (trackletprojs==0) {
      if (warnNoMem) {
	string str="";
	if (tracklet->minusNeighborDisk(disk)){
	  str="Minus";
	}
	if (tracklet->plusNeighborDisk(disk)){
	  str="Plus";
	}
	assert(str!="");
	cout << "Error no projection memory exists in "<<getName()<<" for disk = "<<abs(disk)<<" to "
	     <<str<<" neighbor"<<endl;
      }
      return;
    }
    assert(trackletprojs!=0);

    trackletprojs->addProj(tracklet);

    
  }


  bool barrelSeeding(FPGAStub* innerFPGAStub, L1TStub* innerStub, FPGAStub* outerFPGAStub, L1TStub* outerStub){
	  
    if (debug1) {
      cout << "FPGATrackletCalculator "<<getName()<<" "<<layer_<<" trying stub pair in layer (inner outer): "
	   <<innerFPGAStub->layer().value()<<" "<<outerFPGAStub->layer().value()<<endl;
    }
	    
    assert(outerFPGAStub->isBarrel());
    
    assert(layer_==innerFPGAStub->layer().value()+1);
    
    assert(layer_==1||layer_==2||layer_==3||layer_==5);

    	  
    double r1=innerStub->r();
    double z1=innerStub->z();
    double phi1=innerStub->phi();
    
    double r2=outerStub->r();
    double z2=outerStub->z();
    double phi2=outerStub->phi();
    
    
    double rinv,phi0,t,z0;
    
    double phiproj[4],zproj[4],phider[4],zder[4];
    double phiprojdisk[5],rprojdisk[5],phiderdisk[5],rderdisk[5];
    
    exacttracklet(r1,z1,phi1,r2,z2,phi2,outerStub->sigmaz(),
		  rinv,phi0,t,z0,
		  phiproj,zproj,phider,zder,
		  phiprojdisk,rprojdisk,phiderdisk,rderdisk);

    if (useapprox) {
      phi1=innerFPGAStub->phiapprox(phimin_,phimax_);
      z1=innerFPGAStub->zapprox();
      r1=innerFPGAStub->rapprox();

      phi2=outerFPGAStub->phiapprox(phimin_,phimax_);
      z2=outerFPGAStub->zapprox();
      r2=outerFPGAStub->rapprox();
    }
    
    double rinvapprox,phi0approx,tapprox,z0approx;
    double phiprojapprox[4],zprojapprox[4],phiderapprox[4],zderapprox[4];
    double phiprojdiskapprox[5],rprojdiskapprox[5];
    double phiderdiskapprox[5],rderdiskapprox[5];
    
    IMATH_TrackletCalculator *ITC;
    if(layer_==1)      ITC = &ITC_L1L2;
    else if(layer_==2) ITC = &ITC_L2L3;
    else if(layer_==3) ITC = &ITC_L3L4;
    else               ITC = &ITC_L5L6;
    
    ITC->r1.set_fval(r1-rmean[layer_-1]);
    ITC->r2.set_fval(r2-rmean[layer_]);
    ITC->z1.set_fval(z1);
    ITC->z2.set_fval(z2);
    double sphi1 = phi1 - phioffset_;
    if(sphi1<0) sphi1 += 8*atan(1.);
    if(sphi1>8*atan(1.)) sphi1 -= 8*atan(1.);
    double sphi2 = phi2 - phioffset_;
    if(sphi2<0) sphi2 += 8*atan(1.);
    if(sphi2>8*atan(1.)) sphi2 -= 8*atan(1.);
    ITC->phi1.set_fval(sphi1);
    ITC->phi2.set_fval(sphi2);

    ITC->rproj0.set_fval(rproj_[0]);
    ITC->rproj1.set_fval(rproj_[1]);
    ITC->rproj2.set_fval(rproj_[2]);
    ITC->rproj3.set_fval(rproj_[3]);

    ITC->zproj0.set_fval(t>0? zmean[0] : -zmean[0]);
    ITC->zproj1.set_fval(t>0? zmean[1] : -zmean[1]);
    ITC->zproj2.set_fval(t>0? zmean[2] : -zmean[2]);
    ITC->zproj3.set_fval(t>0? zmean[3] : -zmean[3]);
    ITC->zproj4.set_fval(t>0? zmean[4] : -zmean[4]);

    ITC->rinv_final.calculate();
    ITC->phi0_final.calculate();
    ITC->t_final.calculate();
    ITC->z0_final.calculate();

    ITC->phiL_0_final.calculate();
    ITC->phiL_1_final.calculate();
    ITC->phiL_2_final.calculate();
    ITC->phiL_3_final.calculate();

    ITC->zL_0_final.calculate();
    ITC->zL_1_final.calculate();
    ITC->zL_2_final.calculate();
    ITC->zL_3_final.calculate();

    ITC->phiD_0_final.calculate();
    ITC->phiD_1_final.calculate();
    ITC->phiD_2_final.calculate();
    ITC->phiD_3_final.calculate();
    ITC->phiD_4_final.calculate();

    ITC->rD_0_final.calculate();
    ITC->rD_1_final.calculate();
    ITC->rD_2_final.calculate();
    ITC->rD_3_final.calculate();
    ITC->rD_4_final.calculate();

    ITC->der_phiL_final.calculate();
    ITC->der_zL_final.calculate();
    ITC->der_phiD_final.calculate();
    ITC->der_rD_final.calculate();

    //store the approcximate results
    rinvapprox = ITC->rinv_final.get_fval();
    phi0approx = ITC->phi0_final.get_fval();
    tapprox    = ITC->t_final.get_fval();
    z0approx   = ITC->z0_final.get_fval();
    
    /*
    cout << "texact:"<<t<<" tapprox:"<<tapprox<<endl;
    cout << "z0exact:"<<z0<<" z0approx:"<<z0approx<<" "
	 <<" zeroth order:"<<z1-tapprox*r1
	 <<" first order:"
	 <<z1-tapprox*r1*(1+r1*r1*rinvapprox*rinvapprox/24.0)
	 <<" wrong first order:"
	 <<z1-tapprox*r1*(1+r1*r1*rinvapprox*rinvapprox/6.0)
	 <<endl;
    */
    
    phiprojapprox[0] = ITC->phiL_0_final.get_fval();
    phiprojapprox[1] = ITC->phiL_1_final.get_fval();
    phiprojapprox[2] = ITC->phiL_2_final.get_fval();
    phiprojapprox[3] = ITC->phiL_3_final.get_fval();

    zprojapprox[0]   = ITC->zL_0_final.get_fval();
    zprojapprox[1]   = ITC->zL_1_final.get_fval();
    zprojapprox[2]   = ITC->zL_2_final.get_fval();
    zprojapprox[3]   = ITC->zL_3_final.get_fval();


    for(int i=0; i<4; ++i){
      phiderapprox[i] = ITC->der_phiL_final.get_fval();
      zderapprox[i]   = ITC->der_zL_final.get_fval();
    }

    phiprojdiskapprox[0] = ITC->phiD_0_final.get_fval();
    phiprojdiskapprox[1] = ITC->phiD_1_final.get_fval();
    phiprojdiskapprox[2] = ITC->phiD_2_final.get_fval();
    phiprojdiskapprox[3] = ITC->phiD_3_final.get_fval();
    phiprojdiskapprox[4] = ITC->phiD_4_final.get_fval();

    rprojdiskapprox[0] = ITC->rD_0_final.get_fval();
    rprojdiskapprox[1] = ITC->rD_1_final.get_fval();
    rprojdiskapprox[2] = ITC->rD_2_final.get_fval();
    rprojdiskapprox[3] = ITC->rD_3_final.get_fval();
    rprojdiskapprox[4] = ITC->rD_4_final.get_fval();

    for(int i=0; i<5; ++i){
      phiderdiskapprox[i] = ITC->der_phiD_final.get_fval();
      rderdiskapprox[i]   = ITC->der_rD_final.get_fval();
    }

    //now binary
    
    int irinv,iphi0,it,iz0;
    bool validproj[4];
    int iphiproj[4],izproj[4],iphider[4],izder[4];
    bool minusNeighbor[4],plusNeighbor[4];
    bool validprojdisk[5];
    int iphiprojdisk[5],irprojdisk[5],iphiderdisk[5],irderdisk[5];
    bool minusNeighborDisk[5],plusNeighborDisk[5];
    
    int ir1=innerFPGAStub->ir();
    int iphi1=innerFPGAStub->iphi();
    int iz1=innerFPGAStub->iz();
      
    int ir2=outerFPGAStub->ir();
    int iphi2=outerFPGAStub->iphi();
    int iz2=outerFPGAStub->iz();
    
    if (layer_<4) iphi1<<=(nbitsphistubL456-nbitsphistubL123);
    if (layer_<3) iphi2<<=(nbitsphistubL456-nbitsphistubL123);
    if (layer_<4) {
      ir1<<=(8-nbitsrL123);
    } else {
      ir1<<=(8-nbitsrL456);
    }
    if (layer_<3) {
      ir2<<=(8-nbitsrL123);
    } else {
      ir2<<=(8-nbitsrL456);
    }
    if (layer_>3) iz1<<=(nbitszL123-nbitszL456);
    if (layer_>2) iz2<<=(nbitszL123-nbitszL456);  
      
    ITC->r1.set_ival(ir1);
    ITC->r2.set_ival(ir2);
    ITC->z1.set_ival(iz1);
    ITC->z2.set_ival(iz2);
    ITC->phi1.set_ival(iphi1);
    ITC->phi2.set_ival(iphi2);
    
    ITC->rinv_final.calculate();
    ITC->phi0_final.calculate();
    ITC->t_final.calculate();
    ITC->z0_final.calculate();

    ITC->phiL_0_final.calculate();
    ITC->phiL_1_final.calculate();
    ITC->phiL_2_final.calculate();
    ITC->phiL_3_final.calculate();

    ITC->zL_0_final.calculate();
    ITC->zL_1_final.calculate();
    ITC->zL_2_final.calculate();
    ITC->zL_3_final.calculate();

    ITC->phiD_0_final.calculate();
    ITC->phiD_1_final.calculate();
    ITC->phiD_2_final.calculate();
    ITC->phiD_3_final.calculate();
    ITC->phiD_4_final.calculate();

    ITC->rD_0_final.calculate();
    ITC->rD_1_final.calculate();
    ITC->rD_2_final.calculate();
    ITC->rD_3_final.calculate();
    ITC->rD_4_final.calculate();

    ITC->der_phiL_final.calculate();
    ITC->der_zL_final.calculate();
    ITC->der_phiD_final.calculate();
    ITC->der_rD_final.calculate();

    //store the binary results
    irinv = ITC->rinv_final.get_ival();
    iphi0 = ITC->phi0_final.get_ival();
    it    = ITC->t_final.get_ival();
    iz0   = ITC->z0_final.get_ival();

    iphiproj[0] = ITC->phiL_0_final.get_ival();
    iphiproj[1] = ITC->phiL_1_final.get_ival();
    iphiproj[2] = ITC->phiL_2_final.get_ival();
    iphiproj[3] = ITC->phiL_3_final.get_ival();
    
    izproj[0]   = ITC->zL_0_final.get_ival();
    izproj[1]   = ITC->zL_1_final.get_ival();
    izproj[2]   = ITC->zL_2_final.get_ival();
    izproj[3]   = ITC->zL_3_final.get_ival();

    for(int i=0; i<4; ++i){
      iphider[i] = ITC->der_phiL_final.get_ival();
      izder[i]   = ITC->der_zL_final.get_ival();

      validproj[i] = true;
      if (izproj[i]<-(1<<(nbitszprojL123-1))) validproj[i]=false;
      if (izproj[i]>=(1<<(nbitszprojL123-1))) validproj[i]=false;
      
      minusNeighbor[i]=false;
      plusNeighbor[i]=false;
      if (!hourglass) {
	if (iphiproj[i]<(1<<nbitsphistubL456)/8) {
	  minusNeighbor[i]=true;
	  iphiproj[i]+=3*(1<<nbitsphistubL456)/4;
	}
	if (iphiproj[i]>=7*(1<<nbitsphistubL456)/8) {
	  plusNeighbor[i]=true;
	  iphiproj[i]-=3*(1<<nbitsphistubL456)/4;
	}
      }

      //this is left from the original....
      if (iphiproj[i]>=(1<<nbitsphistubL456)-1) {
	iphiproj[i]=(1<<nbitsphistubL456)-2; //-2 not to hit atExtreme
	validproj[i] = false;
      }
      
      if (rproj_[i]<60.0) {
	iphiproj[i]>>=(nbitsphistubL456-nbitsphistubL123);
	if (iphiproj[i]>=(1<<nbitsphistubL123)-1) iphiproj[i]=(1<<nbitsphistubL123)-2; //-2 not to hit atExtreme
      }
      else {
	izproj[i]>>=(nbitszprojL123-nbitszprojL456);
      }

      if (iphiproj[i]<=0) {
	iphiproj[i]=1;
	validproj[i] = false;
      }

      
    }

    iphiprojdisk[0] = ITC->phiD_0_final.get_ival();
    iphiprojdisk[1] = ITC->phiD_1_final.get_ival();
    iphiprojdisk[2] = ITC->phiD_2_final.get_ival();
    iphiprojdisk[3] = ITC->phiD_3_final.get_ival();
    iphiprojdisk[4] = ITC->phiD_4_final.get_ival();

    irprojdisk[0]   = ITC->rD_0_final.get_ival();
    irprojdisk[1]   = ITC->rD_1_final.get_ival();
    irprojdisk[2]   = ITC->rD_2_final.get_ival();
    irprojdisk[3]   = ITC->rD_3_final.get_ival();
    irprojdisk[4]   = ITC->rD_4_final.get_ival();

    if(fabs(it * ITC->t_final.get_K())<1.0) {
      for(int i=0; i<5; ++i) {
	//do not bother with central tracks; the calculation there is wrong anyway.
	validprojdisk[i]=false;
      }
    } else {
      for(int i=0; i<5; ++i){
	validprojdisk[i]=true;
	iphiderdisk[i] = ITC->der_phiD_final.get_ival();
	irderdisk[i]   = ITC->der_rD_final.get_ival();
      
	minusNeighborDisk[i]=false;
	plusNeighborDisk[i]=false;
	if (!hourglass) {
	  if (iphiprojdisk[i]<(1<<nbitsphistubL123)/8) {
	    minusNeighborDisk[i]=true;
	    iphiprojdisk[i]+=3*(1<<nbitsphistubL123)/4;
	  }
	  if (iphiprojdisk[i]>=7*(1<<nbitsphistubL123)/8) {
	    plusNeighborDisk[i]=true;
	    iphiprojdisk[i]-=3*(1<<nbitsphistubL123)/4;
	  }
	}
     
	if (iphiprojdisk[i]<0) {
	  iphiprojdisk[i]=0;
	  validprojdisk[i]=false;
	}
	if (iphiprojdisk[i]>=(1<<nbitsphistubL123)) {
	  iphiprojdisk[i]=(1<<nbitsphistubL123)-1;
	  validprojdisk[i]=false;
	}
      
	//"protection" from the original
	if (iphiprojdisk[i]<0) {
	  iphiprojdisk[i]=0;
	  validprojdisk[i]=false;
	}
	if (iphiprojdisk[i]>=(1<<nbitsphistubL123)) {
	  iphiprojdisk[i]=(1<<nbitsphistubL123)-1;
	  validprojdisk[i]=false;
	}
	
	if(irprojdisk[i]< 20. / ITC->rD_0_final.get_K() || irprojdisk[i] > 120. / ITC->rD_0_final.get_K() ){
	  validprojdisk[i]=false;
	  irprojdisk[i] = 0;
	  iphiprojdisk[i] = 0;
	  iphiderdisk[i]  = 0;
	  irderdisk[i]    = 0;
	}
      }
    }

    bool success = true;
    if(!ITC->rinv_final.local_passes()){
      if (debug1) 
	cout << "FPGATrackletCalculator::BarrelSeeding irinv too large: "
	     <<ITC->rinv_final.get_fval()<<"("<<ITC->rinv_final.get_ival()<<")\n";
      success = false;
    }
    if (!ITC->z0_final.local_passes()){
      if (debug1) cout << "Failed tracklet z0 cut "<<ITC->z0_final.get_fval()<<" in layer "<<layer_<<endl;
      success = false;
    }
    success = success && ITC->valid_trackpar.passes();
    
    if (!success) return false;

    if (hourglass) {
      double phicrit=phi0approx-asin(0.5*rcrit*rinvapprox);
      //cout << "phicrit phicritminmc phicritmaxmc : "<<phicrit<<" "<<phicritminmc<<" "<<phicritmaxmc<<endl;
      bool keep=(phicrit>phicritminmc)&&(phicrit<phicritmaxmc);
      if (!keep) return false;
    }
    
    for(unsigned int j=0;j<5;j++){
      if (minusNeighborDisk[j]) {
	phiprojdiskapprox[j]+=dphisector;
	phiprojdisk[j]+=dphisector;
      }
      if (plusNeighborDisk[j]) {
	phiprojdiskapprox[j]-=dphisector;
	phiprojdisk[j]-=dphisector;
      }
    }
	  
    for(unsigned int j=0;j<4;j++){
      if (minusNeighbor[j]) {
	phiprojapprox[j]+=dphisector;
	phiproj[j]+=dphisector;
      }
      if (plusNeighbor[j]) {
	phiprojapprox[j]-=dphisector;
	phiproj[j]-=dphisector;
      }	    
    }
    
    
    if (writeTrackletPars) {
      static ofstream out("trackletpars.txt");
      out <<"Trackpars "<<layer_
	  <<"   "<<rinv<<" "<<rinvapprox<<" "<<ITC->rinv_final.get_fval()
	  <<"   "<<phi0<<" "<<phi0approx<<" "<<ITC->phi0_final.get_fval()
	  <<"   "<<t<<" "<<tapprox<<" "<<ITC->t_final.get_fval()
	  <<"   "<<z0<<" "<<z0approx<<" "<<ITC->z0_final.get_fval()
	  <<endl;
    }	        
        
    FPGATracklet* tracklet=new FPGATracklet(innerStub,NULL,outerStub,
					    innerFPGAStub,NULL,outerFPGAStub,
					    iSector_,
					    phioffset_,
					    rinv,phi0,0.0,z0,t,
					    rinvapprox,phi0approx,0.0,
					    z0approx,tapprox,
					    irinv,iphi0,0,iz0,it,validproj,
					    iphiproj,izproj,iphider,izder,
					    minusNeighbor,plusNeighbor,
					    phiproj,zproj,phider,zder,
					    phiprojapprox,zprojapprox,
					    phiderapprox,zderapprox,
					    validprojdisk,
					    iphiprojdisk,irprojdisk,
					    iphiderdisk,irderdisk,
					    minusNeighborDisk,
					    plusNeighborDisk,
					    phiprojdisk,rprojdisk,
					    phiderdisk,rderdisk,
					    phiprojdiskapprox,
					    rprojdiskapprox,
					    phiderdiskapprox,
					    rderdiskapprox,
					    false);
    
    if (debug1) {
      cout << "FPGATrackletCalculator "<<getName()<<" Found tracklet in layer = "<<layer_<<" "
	   <<iSector_<<" phi0 = "<<phi0<<endl;
    }
        

    tracklet->setTrackletIndex(trackletpars_->nTracklets());
    tracklet->setTCIndex(TCIndex_);

    if(writeSeeds){
        ofstream fout("seeds.txt", ofstream::app);
        fout << __FILE__ << ":" << __LINE__ << " " << name_ << "_" << iSector_ << " " << tracklet->getISeed() << endl;
        fout.close();
      }
    trackletpars_->addTracklet(tracklet);
    
    bool addL3=false;
    bool addL4=false;
    bool addL5=false;
    bool addL6=false;
    for(unsigned int j=0;j<4;j++){
      //	    cout<<" LL to L "<<lproj[j]<<"\n";
      bool added=false;
      if (tracklet->validProj(lproj_[j])) {
	added=addLayerProj(tracklet,lproj_[j]);
	//cout << "Add tracklet proj for layer "<<lproj_[j]<<": "<<phiproj[j]<<" "<<iphiproj[j]<<" added = "
	//     <<added<<endl;
	if (added&&lproj_[j]==3) addL3=true;
	if (added&&lproj_[j]==4) addL4=true;
	if (added&&lproj_[j]==5) addL5=true;
	if (added&&lproj_[j]==6) addL6=true;
      }
    }
    
    
    for(unsigned int j=0;j<4;j++){ //no projections to 5th disk!!
      int disk=j+1;
      if (disk==4&&addL3) continue;
      if (disk==3&&addL4) continue;
      if (disk==2&&addL5) continue;
      if (disk==1&&addL6) continue;
      if (it<0) disk=-disk;
      //	    cout<<" LL to disk "<<disk<<"\n";
      if (tracklet->validProjDisk(abs(disk))) {
	//cout << "Add tracklet "<<tracklet<<" for disk "<<disk<<endl;
	addDiskProj(tracklet,disk);
      }
    }
    
    return true;

  }
    

  bool diskSeeding(FPGAStub* innerFPGAStub,L1TStub* innerStub,FPGAStub* outerFPGAStub,L1TStub* outerStub){

	    
    if (debug1) {
      cout <<  "FPGATrackletCalculator::execute calculate disk seeds" << endl;
    }
	      
    int sign=1;
    if (innerFPGAStub->disk().value()<0) sign=-1;
    
    disk_=innerFPGAStub->disk().value();
    assert(abs(disk_)==1||abs(disk_)==3);
    
    
    assert(innerStub->isPSmodule());
    assert(outerStub->isPSmodule());
	    
    double r1=innerStub->r();
    double z1=innerStub->z();
    double phi1=innerStub->phi();
    
    double r2=outerStub->r();
    double z2=outerStub->z();
    double phi2=outerStub->phi();
	    
    
    if (r2<r1+2.0) {
      //assert(0);
      return false; //Protection... Should be handled cleaner
      //to avoid problem with floating point 
      //calculation
    }
    
    double rinv,phi0,t,z0;
    
    double phiproj[3],zproj[3],phider[3],zder[3];
    double phiprojdisk[3],rprojdisk[3],phiderdisk[3],rderdisk[3];
    
    exacttrackletdisk(r1,z1,phi1,r2,z2,phi2,outerStub->sigmaz(),
		      rinv,phi0,t,z0,
		      phiproj,zproj,phider,zder,
		      phiprojdisk,rprojdisk,phiderdisk,rderdisk);


    //Truncates floating point positions to integer
    //representation precision
    if (useapprox) {
      phi1=innerFPGAStub->phiapprox(phimin_,phimax_);
      z1=innerFPGAStub->zapprox();
      r1=innerFPGAStub->rapprox();
      
      phi2=outerFPGAStub->phiapprox(phimin_,phimax_);
      z2=outerFPGAStub->zapprox();
      r2=outerFPGAStub->rapprox();
    }
    
    double rinvapprox,phi0approx,tapprox,z0approx;
    double phiprojapprox[3],zprojapprox[3],phiderapprox[3],zderapprox[3];
    double phiprojdiskapprox[3],rprojdiskapprox[3],
      phiderdiskapprox[3],rderdiskapprox[3];
	    
    IMATH_TrackletCalculatorDisk *ITC;
    if(disk_==1)       ITC = &ITC_F1F2;
    else if(disk_==3)  ITC = &ITC_F3F4;
    else if(disk_==-1) ITC = &ITC_B1B2;
    else               ITC = &ITC_B3B4;
    
    ITC->r1.set_fval(r1);
    ITC->r2.set_fval(r2);
    int signt = t>0? 1 : -1;
    ITC->z1.set_fval(z1-signt*zmean[abs(disk_)-1]);
    ITC->z2.set_fval(z2-signt*zmean[abs(disk_)]);
    double sphi1 = phi1 - phioffset_;
    if(sphi1<0) sphi1 += 8*atan(1.);
    if(sphi1>8*atan(1.)) sphi1 -= 8*atan(1.);
    double sphi2 = phi2 - phioffset_;
    if(sphi2<0) sphi2 += 8*atan(1.);
    if(sphi2>8*atan(1.)) sphi2 -= 8*atan(1.);
    ITC->phi1.set_fval(sphi1);
    ITC->phi2.set_fval(sphi2);
	    
    ITC->rproj0.set_fval(rmean[0]);
    ITC->rproj1.set_fval(rmean[1]);
    ITC->rproj2.set_fval(rmean[2]);

    ITC->zproj0.set_fval(t>0? zproj_[0] : -zproj_[0]);
    ITC->zproj1.set_fval(t>0? zproj_[1] : -zproj_[1]);
    ITC->zproj2.set_fval(t>0? zproj_[2] : -zproj_[2]);

    ITC->rinv_final.calculate();
    ITC->phi0_final.calculate();
    ITC->t_final.calculate();
    ITC->z0_final.calculate();

    ITC->phiL_0_final.calculate();
    ITC->phiL_1_final.calculate();
    ITC->phiL_2_final.calculate();

    ITC->zL_0_final.calculate();
    ITC->zL_1_final.calculate();
    ITC->zL_2_final.calculate();

    ITC->phiD_0_final.calculate();
    ITC->phiD_1_final.calculate();
    ITC->phiD_2_final.calculate();

    ITC->rD_0_final.calculate();
    ITC->rD_1_final.calculate();
    ITC->rD_2_final.calculate();

    ITC->der_phiL_final.calculate();
    ITC->der_zL_final.calculate();
    ITC->der_phiD_final.calculate();
    ITC->der_rD_final.calculate();

    //store the approximate results
    rinvapprox = ITC->rinv_final.get_fval();
    phi0approx = ITC->phi0_final.get_fval();
    tapprox    = ITC->t_final.get_fval();
    z0approx   = ITC->z0_final.get_fval();

    /*
    cout << "texact:"<<t<<" tapprox:"<<tapprox<<endl;
    cout << "z0exact:"<<z0<<" z0approx:"<<z0approx<<" "
	 <<" zeroth order:"<<z1-tapprox*r1
	 <<" first order:"
	 <<z1-tapprox*r1*(1+r1*r1*rinvapprox*rinvapprox/24.0)
	 <<" wrong first order:"
	 <<z1-tapprox*r1*(1+r1*r1*rinvapprox*rinvapprox/6.0)
	 <<endl;
    */
    
    
    phiprojapprox[0] = ITC->phiL_0_final.get_fval();
    phiprojapprox[1] = ITC->phiL_1_final.get_fval();
    phiprojapprox[2] = ITC->phiL_2_final.get_fval();

    zprojapprox[0]   = ITC->zL_0_final.get_fval();
    zprojapprox[1]   = ITC->zL_1_final.get_fval();
    zprojapprox[2]   = ITC->zL_2_final.get_fval();

    for(int i=0; i<3; ++i){
      phiderapprox[i] = ITC->der_phiL_final.get_fval();
      zderapprox[i]   = ITC->der_zL_final.get_fval();
    }

    phiprojdiskapprox[0] = ITC->phiD_0_final.get_fval();
    phiprojdiskapprox[1] = ITC->phiD_1_final.get_fval();
    phiprojdiskapprox[2] = ITC->phiD_2_final.get_fval();

    rprojdiskapprox[0] = ITC->rD_0_final.get_fval();
    rprojdiskapprox[1] = ITC->rD_1_final.get_fval();
    rprojdiskapprox[2] = ITC->rD_2_final.get_fval();

    for(int i=0; i<3; ++i){
      phiderdiskapprox[i] = ITC->der_phiD_final.get_fval();
      rderdiskapprox[i]   = ITC->der_rD_final.get_fval();
    }

    //now binary
    
    int irinv,iphi0,it,iz0;
    bool validproj[3];
    int iphiproj[3],izproj[3],iphider[3],izder[3];
    bool minusNeighbor[3],plusNeighbor[3];
    
    bool validprojdisk[3];
    int iphiprojdisk[3],irprojdisk[3],iphiderdisk[3],irderdisk[3];
    bool minusNeighborDisk[3],plusNeighborDisk[3];

    int ir1=innerFPGAStub->ir();
    int iphi1=innerFPGAStub->iphi();
    int iz1=innerFPGAStub->iz();
    
    int ir2=outerFPGAStub->ir();
    int iphi2=outerFPGAStub->iphi();
    int iz2=outerFPGAStub->iz();
    
    //To get same precission as for layers.
    iphi1<<=(nbitsphistubL456-nbitsphistubL123);
    iphi2<<=(nbitsphistubL456-nbitsphistubL123);
    
    ITC->r1.set_ival(ir1);
    ITC->r2.set_ival(ir2);
    ITC->z1.set_ival(iz1);
    ITC->z2.set_ival(iz2);
    ITC->phi1.set_ival(iphi1);
    ITC->phi2.set_ival(iphi2);

    ITC->rinv_final.calculate();
    ITC->phi0_final.calculate();
    ITC->t_final.calculate();
    ITC->z0_final.calculate();

    ITC->phiL_0_final.calculate();
    ITC->phiL_1_final.calculate();
    ITC->phiL_2_final.calculate();

    ITC->zL_0_final.calculate();
    ITC->zL_1_final.calculate();
    ITC->zL_2_final.calculate();

    ITC->phiD_0_final.calculate();
    ITC->phiD_1_final.calculate();
    ITC->phiD_2_final.calculate();

    ITC->rD_0_final.calculate();
    ITC->rD_1_final.calculate();
    ITC->rD_2_final.calculate();

    ITC->der_phiL_final.calculate();
    ITC->der_zL_final.calculate();
    ITC->der_phiD_final.calculate();
    ITC->der_rD_final.calculate();

    //store the binary results
    irinv = ITC->rinv_final.get_ival();
    iphi0 = ITC->phi0_final.get_ival();
    it    = ITC->t_final.get_ival();
    iz0   = ITC->z0_final.get_ival();

    iphiproj[0] = ITC->phiL_0_final.get_ival();
    iphiproj[1] = ITC->phiL_1_final.get_ival();
    iphiproj[2] = ITC->phiL_2_final.get_ival();
    
    izproj[0]   = ITC->zL_0_final.get_ival();
    izproj[1]   = ITC->zL_1_final.get_ival();
    izproj[2]   = ITC->zL_2_final.get_ival();

    for(int i=0; i<3; ++i){
      iphider[i] = ITC->der_phiL_final.get_ival();
      izder[i]   = ITC->der_zL_final.get_ival();

      validproj[i] = true;
      if (izproj[i]<-(1<<(nbitszprojL123-1))) validproj[i]=false;
      if (izproj[i]>=(1<<(nbitszprojL123-1))) validproj[i]=false;
      
      minusNeighbor[i]=false;
      plusNeighbor[i]=false;
      if (!hourglass) {
	if (iphiproj[i]<(1<<nbitsphistubL456)/8) {
	  minusNeighbor[i]=true;
	  iphiproj[i]+=3*(1<<nbitsphistubL456)/4;
	}
	if (iphiproj[i]>=7*(1<<nbitsphistubL456)/8) {
	  plusNeighbor[i]=true;
	  iphiproj[i]-=3*(1<<nbitsphistubL456)/4;
	}
      }

      //this is left from the original....
      if (iphiproj[i]>=(1<<nbitsphistubL456)-1){
	iphiproj[i]=(1<<nbitsphistubL456)-2; //-2 not to hit atExtreme
	validproj[i] = false;
      }

      if (rproj_[i]<60.0)
	iphiproj[i]>>=(nbitsphistubL456-nbitsphistubL123);
      else {
	izproj[i]>>=(nbitszprojL123-nbitszprojL456);
      }
      
      if (iphiproj[i]<=0) {
	iphiproj[i]=1;
	validproj[i] = false;
      }

    }

    iphiprojdisk[0] = ITC->phiD_0_final.get_ival();
    iphiprojdisk[1] = ITC->phiD_1_final.get_ival();
    iphiprojdisk[2] = ITC->phiD_2_final.get_ival();

    irprojdisk[0]   = ITC->rD_0_final.get_ival();
    irprojdisk[1]   = ITC->rD_1_final.get_ival();
    irprojdisk[2]   = ITC->rD_2_final.get_ival();

    for(int i=0; i<3; ++i){
      iphiderdisk[i] = ITC->der_phiD_final.get_ival();
      irderdisk[i]   = ITC->der_rD_final.get_ival();
      
      minusNeighborDisk[i]=false;
      plusNeighborDisk[i]=false;
      if (!hourglass) {
	if (iphiprojdisk[i]<(1<<nbitsphistubL123)/8) {
	  minusNeighborDisk[i]=true;
	  iphiprojdisk[i]+=3*(1<<nbitsphistubL123)/4;
	}
	if (iphiprojdisk[i]>=7*(1<<nbitsphistubL123)/8) {
	  plusNeighborDisk[i]=true;
	  iphiprojdisk[i]-=3*(1<<nbitsphistubL123)/4;
	}
      }
      
      //"protection" from the original
      if (iphiprojdisk[i]<0) iphiprojdisk[i]=0;
      if (iphiprojdisk[i]>=(1<<nbitsphistubL123)) iphiprojdisk[i]=(1<<nbitsphistubL123)-1;
      
      validprojdisk[i]=true;
      if(irprojdisk[i]<=0 || irprojdisk[i] > 120. / ITC->rD_0_final.get_K() ){
	validprojdisk[i]=false;
	irprojdisk[i] = 0;
	iphiprojdisk[i] = 0;
	iphiderdisk[i]  = 0;
	irderdisk[i]    = 0;
      }
    }

    bool success = true;
    if(!ITC->rinv_final.local_passes()){
      if (debug1) 
	cout << "FPGATrackletCalculator::DiskSeeding irinv too large: "<<ITC->rinv_final.get_fval()<<endl;
      success = false;
    }
    if (!ITC->z0_final.local_passes()) {
      if (debug1) cout << "Failed tracklet z0 cut "<<ITC->z0_final.get_fval()<<" in layer 1"<<endl;
      success = false;
    }
    success = success && ITC->valid_trackpar.passes();
   
    if (!success) return false;

    if (hourglass) {
      double phicrit=phi0approx-asin(0.5*rcrit*rinvapprox);
      bool keep=(phicrit>phicritminmc)&&(phicrit<phicritmaxmc);
      if (!keep) return false;
    }
    
    for(unsigned int j=0;j<3;j++){
      if (minusNeighborDisk[j]) {
	phiprojdiskapprox[j]+=dphisector;
	phiprojdisk[j]+=dphisector;
      }
      if (plusNeighborDisk[j]) {
	phiprojdiskapprox[j]-=dphisector;
	phiprojdisk[j]-=dphisector;
      }	    
    }
	    
    for(unsigned int j=0;j<3;j++){
      if (minusNeighbor[j]) {
	phiprojapprox[j]+=dphisector;
	phiproj[j]+=dphisector;
      }
      if (plusNeighbor[j]) {
	phiprojapprox[j]-=dphisector;
	phiproj[j]-=dphisector;
      }
    }
	    
    
    if (writeTrackletParsDisk) {
      static ofstream out("trackletparsdisk.txt");
      out <<"Trackpars         "<<disk_
	  <<"   "<<rinv<<" "<<rinvapprox<<" "<<ITC->rinv_final.get_fval()
	  <<"   "<<phi0<<" "<<phi0approx<<" "<<ITC->phi0_final.get_fval()
	  <<"   "<<t<<" "<<tapprox<<" "<<ITC->t_final.get_fval()
	  <<"   "<<z0<<" "<<z0approx<<" "<<ITC->z0_final.get_fval()
	  <<endl;
    }
	    
    FPGATracklet* tracklet=new FPGATracklet(innerStub,NULL,outerStub,
					    innerFPGAStub,NULL,outerFPGAStub,
					    iSector_,
					    phioffset_,
					    rinv,phi0,0.0,z0,t,
					    rinvapprox,phi0approx,0.0,
					    z0approx,tapprox,
					    irinv,iphi0,0,iz0,it,
					    validproj,
					    iphiproj,izproj,iphider,izder,
					    minusNeighbor,plusNeighbor,	
					    phiproj,zproj,phider,zder,
					    phiprojapprox,zprojapprox,
					    phiderapprox,zderapprox,
					    validprojdisk,
					    iphiprojdisk,irprojdisk,
					    iphiderdisk,irderdisk,
					    minusNeighborDisk,
					    plusNeighborDisk,
					    phiprojdisk,rprojdisk,
					    phiderdisk,rderdisk,
					    phiprojdiskapprox,
					    rprojdiskapprox,
					    phiderdiskapprox,
					    rderdiskapprox,
					    true);
    
    if (debug1) {
      cout << "Found tracklet in disk = "<<disk_<<" "<<tracklet
	   <<" "<<iSector_<<endl;
    }
        
    tracklet->setTrackletIndex(trackletpars_->nTracklets());
    tracklet->setTCIndex(TCIndex_);

    if(writeSeeds){
        ofstream fout("seeds.txt", ofstream::app);
        fout << __FILE__ << ":" << __LINE__ << " " << name_ << "_" << iSector_ << " " << tracklet->getISeed() << endl;
        fout.close();
      }
    trackletpars_->addTracklet(tracklet);
    
    if (tracklet->validProj(1)) {
      addLayerProj(tracklet,1);
    }
    
    if (tracklet->validProj(2)) {
      addLayerProj(tracklet,2);
    }
    
    for(unsigned int j=0;j<3;j++){
      if (tracklet->validProjDisk(sign*dproj_[j])) {
	addDiskProj(tracklet,sign*dproj_[j]);
      }
    }

    return true;
    
  }
  

  bool overlapSeeding(FPGAStub* innerFPGAStub, L1TStub* innerStub, FPGAStub* outerFPGAStub, L1TStub* outerStub){
    
    //Deal with overlap stubs here
    assert(outerFPGAStub->isBarrel());
    
    assert(innerFPGAStub->isDisk());
    
    disk_=innerFPGAStub->disk().value();
    
    if (debug1) {
      cout << "trying to make overlap tracklet disk_ = "<<disk_<<" "<<getName()<<endl;
    }
    
    //int sign=1;
    //if (disk_<0) sign=-1;
    
    double r1=innerStub->r();
    double z1=innerStub->z();
    double phi1=innerStub->phi();
    
    double r2=outerStub->r();
    double z2=outerStub->z();
    double phi2=outerStub->phi();
    
    //Protection... Should be handled cleaner
    //to avoid problem with floating point 
    //calculation and with overflows
    //in the integer calculation
    if (r1<r2+1.5) {
      //cout << "in overlap tracklet: radii wrong"<<endl;
      return false;
    }
    

    double rinv,phi0,t,z0;
	    
    double phiproj[3],zproj[3],phider[3],zder[3];
    double phiprojdisk[4],rprojdisk[4],phiderdisk[4],rderdisk[4];
    
    exacttrackletOverlap(r1,z1,phi1,r2,z2,phi2,outerStub->sigmaz(),
			 rinv,phi0,t,z0,
			 phiproj,zproj,phider,zder,
			 phiprojdisk,rprojdisk,phiderdisk,rderdisk);
    
    
    //Truncates floating point positions to integer
    //representation precision
    if (useapprox) {
      phi1=innerFPGAStub->phiapprox(phimin_,phimax_);
      z1=innerFPGAStub->zapprox();
      r1=innerFPGAStub->rapprox();
	      
      phi2=outerFPGAStub->phiapprox(phimin_,phimax_);
      z2=outerFPGAStub->zapprox();
      r2=outerFPGAStub->rapprox();
    }

    double rinvapprox,phi0approx,tapprox,z0approx;
    double phiprojapprox[3],zprojapprox[3],phiderapprox[3],zderapprox[3];
    double phiprojdiskapprox[4],rprojdiskapprox[4],
      phiderdiskapprox[4],rderdiskapprox[4];
    

    IMATH_TrackletCalculatorOverlap *ITC;
    int ll = outerFPGAStub->layer().value()+1;
    if     (ll==1 && disk_==1)  ITC = &ITC_L1F1;
    else if(ll==2 && disk_==1)  ITC = &ITC_L2F1;
    else if(ll==1 && disk_==-1) ITC = &ITC_L1B1;
    else if(ll==2 && disk_==-1) ITC = &ITC_L2B1;
    else assert(0);
    
    ITC->r1.set_fval(r2-rmean[ll-1]);
    ITC->r2.set_fval(r1);
    int signt = t>0? 1 : -1;
    ITC->z1.set_fval(z2);
    ITC->z2.set_fval(z1-signt*zmean[abs(disk_)-1]);
    double sphi1 = phi1 - phioffset_;
    if(sphi1<0) sphi1 += 8*atan(1.);
    if(sphi1>8*atan(1.)) sphi1 -= 8*atan(1.);
    double sphi2 = phi2 - phioffset_;
    if(sphi2<0) sphi2 += 8*atan(1.);
    if(sphi2>8*atan(1.)) sphi2 -= 8*atan(1.);
    ITC->phi1.set_fval(sphi2);
    ITC->phi2.set_fval(sphi1);

    ITC->rproj0.set_fval(rmean[0]);
    ITC->rproj1.set_fval(rmean[1]);
    ITC->rproj2.set_fval(rmean[2]);
    
    ITC->zproj0.set_fval(t>0? zprojoverlap_[0] : -zprojoverlap_[0]);
    ITC->zproj1.set_fval(t>0? zprojoverlap_[1] : -zprojoverlap_[1]);
    ITC->zproj2.set_fval(t>0? zprojoverlap_[2] : -zprojoverlap_[2]);
    ITC->zproj3.set_fval(t>0? zprojoverlap_[3] : -zprojoverlap_[3]);
    
    ITC->rinv_final.calculate();
    ITC->phi0_final.calculate();
    ITC->t_final.calculate();
    ITC->z0_final.calculate();

    ITC->phiL_0_final.calculate();
    ITC->phiL_1_final.calculate();
    ITC->phiL_2_final.calculate();

    ITC->zL_0_final.calculate();
    ITC->zL_1_final.calculate();
    ITC->zL_2_final.calculate();

    ITC->phiD_0_final.calculate();
    ITC->phiD_1_final.calculate();
    ITC->phiD_2_final.calculate();
    ITC->phiD_3_final.calculate();

    ITC->rD_0_final.calculate();
    ITC->rD_1_final.calculate();
    ITC->rD_2_final.calculate();
    ITC->rD_3_final.calculate();

    ITC->der_phiL_final.calculate();
    ITC->der_zL_final.calculate();
    ITC->der_phiD_final.calculate();
    ITC->der_rD_final.calculate();

    //store the approximate results
    rinvapprox = ITC->rinv_final.get_fval();
    phi0approx = ITC->phi0_final.get_fval();
    tapprox    = ITC->t_final.get_fval();
    z0approx   = ITC->z0_final.get_fval();

    phiprojapprox[0] = ITC->phiL_0_final.get_fval();
    phiprojapprox[1] = ITC->phiL_1_final.get_fval();
    phiprojapprox[2] = ITC->phiL_2_final.get_fval();

    zprojapprox[0]   = ITC->zL_0_final.get_fval();
    zprojapprox[1]   = ITC->zL_1_final.get_fval();
    zprojapprox[2]   = ITC->zL_2_final.get_fval();

    for(int i=0; i<3; ++i){
      phiderapprox[i] = ITC->der_phiL_final.get_fval();
      zderapprox[i]   = ITC->der_zL_final.get_fval();
    }

    phiprojdiskapprox[0] = ITC->phiD_0_final.get_fval();
    phiprojdiskapprox[1] = ITC->phiD_1_final.get_fval();
    phiprojdiskapprox[2] = ITC->phiD_2_final.get_fval();
    phiprojdiskapprox[3] = ITC->phiD_3_final.get_fval();

    rprojdiskapprox[0] = ITC->rD_0_final.get_fval();
    rprojdiskapprox[1] = ITC->rD_1_final.get_fval();
    rprojdiskapprox[2] = ITC->rD_2_final.get_fval();
    rprojdiskapprox[3] = ITC->rD_3_final.get_fval();

    for(int i=0; i<4; ++i){
      phiderdiskapprox[i] = ITC->der_phiD_final.get_fval();
      rderdiskapprox[i]   = ITC->der_rD_final.get_fval();
    }

    //now binary

    int irinv,iphi0,it,iz0;
    bool validproj[3];
    int iphiproj[3],izproj[3],iphider[3],izder[3];
    bool minusNeighbor[3],plusNeighbor[3];
    
    bool validprojdisk[4];
    int iphiprojdisk[4],irprojdisk[4],iphiderdisk[4],irderdisk[4];
    bool minusNeighborDisk[4],plusNeighborDisk[4];
    
    int ir2=innerFPGAStub->ir();
    int iphi2=innerFPGAStub->iphi();
    int iz2=innerFPGAStub->iz();
      
    int ir1=outerFPGAStub->ir();
    int iphi1=outerFPGAStub->iphi();
    int iz1=outerFPGAStub->iz();
      
    //To get global precission
    ir1<<=(8-nbitsrL123);
    iphi1<<=(nbitsphistubL456-nbitsphistubL123);
    iphi2<<=(nbitsphistubL456-nbitsphistubL123);

    ITC->r1.set_ival(ir1);
    ITC->r2.set_ival(ir2);
    ITC->z1.set_ival(iz1);
    ITC->z2.set_ival(iz2);
    ITC->phi1.set_ival(iphi1);
    ITC->phi2.set_ival(iphi2);
      
    ITC->rinv_final.calculate();
    ITC->phi0_final.calculate();
    ITC->t_final.calculate();
    ITC->z0_final.calculate();

    ITC->phiL_0_final.calculate();
    ITC->phiL_1_final.calculate();
    ITC->phiL_2_final.calculate();

    ITC->zL_0_final.calculate();
    ITC->zL_1_final.calculate();
    ITC->zL_2_final.calculate();

    ITC->phiD_0_final.calculate();
    ITC->phiD_1_final.calculate();
    ITC->phiD_2_final.calculate();
    ITC->phiD_3_final.calculate();

    ITC->rD_0_final.calculate();
    ITC->rD_1_final.calculate();
    ITC->rD_2_final.calculate();
    ITC->rD_3_final.calculate();

    ITC->der_phiL_final.calculate();
    ITC->der_zL_final.calculate();
    ITC->der_phiD_final.calculate();
    ITC->der_rD_final.calculate();

    //store the binary results
    irinv = ITC->rinv_final.get_ival();
    iphi0 = ITC->phi0_final.get_ival();
    it    = ITC->t_final.get_ival();
    iz0   = ITC->z0_final.get_ival();

    //"protection" from the original, reinterpreted
    if (iz0>= 1<<(ITC->z0_final.get_nbits()-1)) iz0=(1<<(ITC->z0_final.get_nbits()-1))-1;
    if (iz0<=-(1<<(ITC->z0_final.get_nbits()-1))) iz0=1-(1<<(ITC->z0_final.get_nbits()-1))-1; 
    if (irinv>= (1<<(ITC->rinv_final.get_nbits()-1))) irinv=(1<<(ITC->rinv_final.get_nbits()-1))-1;
    if (irinv<=-(1<<(ITC->rinv_final.get_nbits()-1))) irinv=1-(1<<(ITC->rinv_final.get_nbits()-1))-1; 

    iphiproj[0] = ITC->phiL_0_final.get_ival();
    iphiproj[1] = ITC->phiL_1_final.get_ival();
    iphiproj[2] = ITC->phiL_2_final.get_ival();
    
    izproj[0]   = ITC->zL_0_final.get_ival();
    izproj[1]   = ITC->zL_1_final.get_ival();
    izproj[2]   = ITC->zL_2_final.get_ival();

    for(int i=0; i<3; ++i){
      iphider[i] = ITC->der_phiL_final.get_ival();
      izder[i]   = ITC->der_zL_final.get_ival();

      validproj[i] = true;
      if (izproj[i]<-(1<<(nbitszprojL123-1))) validproj[i]=false;
      if (izproj[i]>=(1<<(nbitszprojL123-1))) validproj[i]=false;
      
      minusNeighbor[i]=false;
      plusNeighbor[i]=false;
      if (!hourglass) {
	if (iphiproj[i]<(1<<nbitsphistubL456)/8) {
	  minusNeighbor[i]=true;
	  iphiproj[i]+=3*(1<<nbitsphistubL456)/4;
	}
	if (iphiproj[i]>=7*(1<<nbitsphistubL456)/8) {
	  plusNeighbor[i]=true;
	  iphiproj[i]-=3*(1<<nbitsphistubL456)/4;
	}
      }

      //this is left from the original....
      if (iphiproj[i]>=(1<<nbitsphistubL456)) {
	iphiproj[i]=(1<<nbitsphistubL456)-2; //-2 not to hit atExtreme
	validproj[i] = false;
      }

      if (rproj_[i]<60.0)
	iphiproj[i]>>=(nbitsphistubL456-nbitsphistubL123);
      else {
	izproj[i]>>=(nbitszprojL123-nbitszprojL456);
      }

      if (iphiproj[i]<=0) {
	iphiproj[i]=1;
	validproj[i] = false;
      }

      
    }

    iphiprojdisk[0] = ITC->phiD_0_final.get_ival();
    iphiprojdisk[1] = ITC->phiD_1_final.get_ival();
    iphiprojdisk[2] = ITC->phiD_2_final.get_ival();
    iphiprojdisk[3] = ITC->phiD_3_final.get_ival();

    irprojdisk[0]   = ITC->rD_0_final.get_ival();
    irprojdisk[1]   = ITC->rD_1_final.get_ival();
    irprojdisk[2]   = ITC->rD_2_final.get_ival();
    irprojdisk[3]   = ITC->rD_3_final.get_ival();

    for(int i=0; i<4; ++i){
      iphiderdisk[i] = ITC->der_phiD_final.get_ival();
      irderdisk[i]   = ITC->der_rD_final.get_ival();

      minusNeighborDisk[i]=false;
      plusNeighborDisk[i]=false;
      if (!hourglass) {
	if (iphiprojdisk[i]<(1<<nbitsphistubL123)/8) {
	  minusNeighborDisk[i]=true;
	  iphiprojdisk[i]+=3*(1<<nbitsphistubL123)/4;
	}
	if (iphiprojdisk[i]>=7*(1<<nbitsphistubL123)/8) {
	  plusNeighborDisk[i]=true;
	  iphiprojdisk[i]-=3*(1<<nbitsphistubL123)/4;
	}
      }
	
      //"protection" from the original
      if (iphiprojdisk[i]<0) iphiprojdisk[i]=0;
      if (iphiprojdisk[i]>=(1<<nbitsphistubL123)) iphiprojdisk[i]=(1<<nbitsphistubL123)-1;
      
      validprojdisk[i]=true;
      if(irprojdisk[i]<=0 || irprojdisk[i] > 120. / ITC->rD_0_final.get_K() ){
	validprojdisk[i]=false;
	irprojdisk[i] = 0;
	iphiprojdisk[i] = 0;
	iphiderdisk[i]  = 0;
	irderdisk[i]    = 0;
      }
    }

    bool success = true;
    if(!ITC->t_final.local_passes()) {
      if (debug1) {
	cout << "FPGATrackletCalculator::OverlapSeeding t too large: "<<ITC->t_final.get_fval()<<endl;
      }
      success = false;
    }
    if(!ITC->rinv_final.local_passes()){
      if (debug1) {
	cout << "FPGATrackletCalculator::OverlapSeeding irinv too large: "<<ITC->rinv_final.get_fval()<<endl;
      }
      success = false;
    }
    if (!ITC->z0_final.local_passes()) {
      if (debug1) {
	cout << "Failed tracklet z0 cut "<<ITC->z0_final.get_fval()<<" in layer 1"<<endl;
      }
      success = false;
    }

    success = success && ITC->valid_trackpar.passes();

    if (!success) {
      if (debug1) {
	
	cout << "FPGATrackletCalculator::OverlapSeeding rejected no success: "
	     <<ITC->valid_trackpar.passes()<<" rinv="
	     <<ITC->rinv_final.get_ival()*ITC->rinv_final.get_K()<<" eta="
	     <<asinh(ITC->t_final.get_ival()*ITC->t_final.get_K())<<" z0="
	     <<ITC->z0_final.get_ival()*ITC->z0_final.get_K()<<" phi0="
	     <<ITC->phi0_final.get_ival()*ITC->phi0_final.get_K()<<endl;
      }
      return false;
    }

    if (hourglass) {
      double phicrit=phi0approx-asin(0.5*rcrit*rinvapprox);
      bool keep=(phicrit>phicritminmc)&&(phicrit<phicritmaxmc);
      if (!keep) {
	if (debug1) {
	  cout << "FPGATrackletCalculator::OverlapSeeding fail phicrit "<<endl;
	}
	return false;
      }
    }
    

    for(unsigned int j=0;j<3;j++){
      if (minusNeighborDisk[j]) {
	phiprojdiskapprox[j]+=dphisector;
	phiprojdisk[j]+=dphisector;
      }
      if (plusNeighborDisk[j]) {
	phiprojdiskapprox[j]-=dphisector;
	phiprojdisk[j]-=dphisector;
      }	    
    }
    
    for(unsigned int j=0;j<3;j++){
      if (minusNeighbor[j]) {
	phiprojapprox[j]+=dphisector;
	phiproj[j]+=dphisector;
      }
      if (plusNeighbor[j]) {
	phiprojapprox[j]-=dphisector;
	phiproj[j]-=dphisector;
      }
    }
    
    
    if (writeTrackletParsOverlap) {
      static ofstream out("trackletparsoverlap.txt");
      out <<"Trackpars "<<disk_
	  <<"   "<<rinv<<" "<<irinv<<" "<<ITC->rinv_final.get_fval()
	  <<"   "<<phi0<<" "<<iphi0<<" "<<ITC->phi0_final.get_fval()
	  <<"   "<<t<<" "<<it<<" "<<ITC->t_final.get_fval()
	  <<"   "<<z0<<" "<<iz0<<" "<<ITC->z0_final.get_fval()
	  <<endl;
    }
	      
    FPGATracklet* tracklet=new FPGATracklet(innerStub,NULL,outerStub,
					    innerFPGAStub,NULL,outerFPGAStub,
					    iSector_,
					    phioffset_,
					    rinv,phi0,0.0,z0,t,
					    rinvapprox,phi0approx,0.0,
					    z0approx,tapprox,
					    irinv,iphi0,0,iz0,it,
					    validproj,
					    iphiproj,izproj,iphider,izder,
					    minusNeighbor,plusNeighbor,
					    
					    
					    phiproj,zproj,phider,zder,
					    phiprojapprox,zprojapprox,
					    phiderapprox,zderapprox,
					    validprojdisk,
					    iphiprojdisk,irprojdisk,
					    iphiderdisk,irderdisk,
					    minusNeighborDisk,
					    plusNeighborDisk,
					    phiprojdisk,rprojdisk,
					    phiderdisk,rderdisk,
					    phiprojdiskapprox,
					    rprojdiskapprox,
					    phiderdiskapprox,
					    rderdiskapprox,
					    false,true);
    
    if (debug1) {
      cout << "Found tracklet in overlap = "<<layer_<<" "<<disk_
	   <<" "<<tracklet<<" "<<iSector_<<endl;
    }
    
        
    tracklet->setTrackletIndex(trackletpars_->nTracklets());
    tracklet->setTCIndex(TCIndex_);
    
    if(writeSeeds){
        ofstream fout("seeds.txt", ofstream::app);
        fout << __FILE__ << ":" << __LINE__ << " " << name_ << "_" << iSector_ << " " << tracklet->getISeed() << endl;
        fout.close();
      }
    trackletpars_->addTracklet(tracklet);
    
    int layer=outerFPGAStub->layer().value()+1;
    
    if (layer==2) {
      if (tracklet->validProj(1)) {
	addLayerProj(tracklet,1);
      }
    }
    
    
    for(unsigned int disk=2;disk<6;disk++){
      if (layer==2 && disk==5 ) continue;
      if (tracklet->validProjDisk(disk)) {
	addDiskProj(tracklet,disk);
      }
    }

    return true;
    
  }
  
  
  int round_int( double r ) {
    return (r > 0.0) ? (r + 0.5) : (r - 0.5); 
  }
 
    
private:

  int TCIndex_;
  int layer_;
  int disk_;
  double phimin_;
  double phimax_;
  double phioffset_;
  double rproj_[4];
  int lproj_[4];
  double zproj_[3];
  int dproj_[3];

  unsigned int maxtracklet_; //maximum numbor of tracklets that be stored
  
  double zprojoverlap_[4];

  vector<FPGAAllStubs*> innerallstubs_;
  vector<FPGAAllStubs*> outerallstubs_;
  vector<FPGAStubPairs*> stubpairs_;

  FPGATrackletParameters* trackletpars_;

  FPGATrackletProjections* trackletproj_L1PHI1_;
  FPGATrackletProjections* trackletproj_L1PHI2_;
  FPGATrackletProjections* trackletproj_L1PHI3_;
  FPGATrackletProjections* trackletproj_L1PHI4_;
  FPGATrackletProjections* trackletproj_L1PHI5_;
  FPGATrackletProjections* trackletproj_L1PHI6_;
  FPGATrackletProjections* trackletproj_L1PHI7_;
  FPGATrackletProjections* trackletproj_L1PHI8_;

  FPGATrackletProjections* trackletproj_L2PHI1_;
  FPGATrackletProjections* trackletproj_L2PHI2_;
  FPGATrackletProjections* trackletproj_L2PHI3_;
  FPGATrackletProjections* trackletproj_L2PHI4_;

  FPGATrackletProjections* trackletproj_L3PHI1_;
  FPGATrackletProjections* trackletproj_L3PHI2_;
  FPGATrackletProjections* trackletproj_L3PHI3_;
  FPGATrackletProjections* trackletproj_L3PHI4_;

  FPGATrackletProjections* trackletproj_L4PHI1_;
  FPGATrackletProjections* trackletproj_L4PHI2_;
  FPGATrackletProjections* trackletproj_L4PHI3_;
  FPGATrackletProjections* trackletproj_L4PHI4_;

  FPGATrackletProjections* trackletproj_L5PHI1_;
  FPGATrackletProjections* trackletproj_L5PHI2_;
  FPGATrackletProjections* trackletproj_L5PHI3_;
  FPGATrackletProjections* trackletproj_L5PHI4_;

  FPGATrackletProjections* trackletproj_L6PHI1_;
  FPGATrackletProjections* trackletproj_L6PHI2_;
  FPGATrackletProjections* trackletproj_L6PHI3_;
  FPGATrackletProjections* trackletproj_L6PHI4_;

  FPGATrackletProjections* trackletproj_D1PHI1_;
  FPGATrackletProjections* trackletproj_D1PHI2_;
  FPGATrackletProjections* trackletproj_D1PHI3_;
  FPGATrackletProjections* trackletproj_D1PHI4_;

  FPGATrackletProjections* trackletproj_D2PHI1_;
  FPGATrackletProjections* trackletproj_D2PHI2_;
  FPGATrackletProjections* trackletproj_D2PHI3_;
  FPGATrackletProjections* trackletproj_D2PHI4_;

  FPGATrackletProjections* trackletproj_D3PHI1_;
  FPGATrackletProjections* trackletproj_D3PHI2_;
  FPGATrackletProjections* trackletproj_D3PHI3_;
  FPGATrackletProjections* trackletproj_D3PHI4_;

  FPGATrackletProjections* trackletproj_D4PHI1_;
  FPGATrackletProjections* trackletproj_D4PHI2_;
  FPGATrackletProjections* trackletproj_D4PHI3_;
  FPGATrackletProjections* trackletproj_D4PHI4_;

  FPGATrackletProjections* trackletproj_D5PHI1_;
  FPGATrackletProjections* trackletproj_D5PHI2_;
  FPGATrackletProjections* trackletproj_D5PHI3_;
  FPGATrackletProjections* trackletproj_D5PHI4_;


  
  FPGATrackletProjections* trackletproj_L1Plus_; 
  FPGATrackletProjections* trackletproj_L1Minus_;
			                         
  FPGATrackletProjections* trackletproj_L2Plus_; 
  FPGATrackletProjections* trackletproj_L2Minus_;
			                         
  FPGATrackletProjections* trackletproj_L3Plus_; 
  FPGATrackletProjections* trackletproj_L3Minus_;
			                         
  FPGATrackletProjections* trackletproj_L4Plus_; 
  FPGATrackletProjections* trackletproj_L4Minus_;
			                         
  FPGATrackletProjections* trackletproj_L5Plus_; 
  FPGATrackletProjections* trackletproj_L5Minus_;
			                         
  FPGATrackletProjections* trackletproj_L6Plus_; 
  FPGATrackletProjections* trackletproj_L6Minus_;


  FPGATrackletProjections* trackletproj_D1Plus_; 
  FPGATrackletProjections* trackletproj_D1Minus_;
			                         
  FPGATrackletProjections* trackletproj_D2Plus_; 
  FPGATrackletProjections* trackletproj_D2Minus_;
			                         
  FPGATrackletProjections* trackletproj_D3Plus_; 
  FPGATrackletProjections* trackletproj_D3Minus_;
			                         
  FPGATrackletProjections* trackletproj_D4Plus_; 
  FPGATrackletProjections* trackletproj_D4Minus_;
			                         
  FPGATrackletProjections* trackletproj_D5Plus_; 
  FPGATrackletProjections* trackletproj_D5Minus_;

public:
  static IMATH_TrackletCalculator ITC_L1L2;
  static IMATH_TrackletCalculator ITC_L2L3;
  static IMATH_TrackletCalculator ITC_L3L4;
  static IMATH_TrackletCalculator ITC_L5L6;
  
  static IMATH_TrackletCalculatorDisk ITC_F1F2;
  static IMATH_TrackletCalculatorDisk ITC_F3F4;
  static IMATH_TrackletCalculatorDisk ITC_B1B2;
  static IMATH_TrackletCalculatorDisk ITC_B3B4;

  static IMATH_TrackletCalculatorOverlap ITC_L1F1;
  static IMATH_TrackletCalculatorOverlap ITC_L2F1;
  static IMATH_TrackletCalculatorOverlap ITC_L1B1;
  static IMATH_TrackletCalculatorOverlap ITC_L2B1;
    
};

IMATH_TrackletCalculator FPGATrackletCalculator::ITC_L1L2{1,2};
IMATH_TrackletCalculator FPGATrackletCalculator::ITC_L2L3{2,3};
IMATH_TrackletCalculator FPGATrackletCalculator::ITC_L3L4{3,4};
IMATH_TrackletCalculator FPGATrackletCalculator::ITC_L5L6{5,6};

IMATH_TrackletCalculatorDisk FPGATrackletCalculator::ITC_F1F2{1,2};
IMATH_TrackletCalculatorDisk FPGATrackletCalculator::ITC_F3F4{3,4};
IMATH_TrackletCalculatorDisk FPGATrackletCalculator::ITC_B1B2{-1,-2};
IMATH_TrackletCalculatorDisk FPGATrackletCalculator::ITC_B3B4{-3,-4};

IMATH_TrackletCalculatorOverlap FPGATrackletCalculator::ITC_L1F1{1,1};
IMATH_TrackletCalculatorOverlap FPGATrackletCalculator::ITC_L2F1{2,1};
IMATH_TrackletCalculatorOverlap FPGATrackletCalculator::ITC_L1B1{1,-1};
IMATH_TrackletCalculatorOverlap FPGATrackletCalculator::ITC_L2B1{2,-1};

#endif
