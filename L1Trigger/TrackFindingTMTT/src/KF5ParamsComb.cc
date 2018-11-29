///=== This is the Kalman Combinatorial Filter for 4 helix parameters track fit algorithm.
 
 
#include "L1Trigger/TrackFindingTMTT/interface/KF5ParamsComb.h"
#include "L1Trigger/TrackFindingTMTT/interface/kalmanState.h"
#include "L1Trigger/TrackFindingTMTT/interface/StubCluster.h"
#define CKF_DEBUG

namespace TMTT {


/*
// Scattering constants - HISTORIC NOT USED.

static unsigned nlayer_eta[25] = 
{ 6, 6, 6, 6,
6, 6, 6, 6, 6, 6, 6, 7, 7, 7,
7, 7, 7, 7, 6, 6, 6, 6, 6, 6};

static double matx_outer[25] = {
0.16, 0.17, 0.18, 0.19, 0.20, 
0.21, 0.26, 0.22, 0.26, 0.38,
0.41, 0.40, 0.44, 0.50, 0.54,
0.60, 0.44, 0.48, 0.60, 0.68,
0.50, 0.48, 0.64, 0.39, 0.20
};

static double matx_inner[25] = {
0.14, 0.1, 0.1, 0.1, 0.1, 
0.1, 0.1, 0.1, 0.1, 0.1, 
0.12, 0.1, 0.1, 0.1, 0.15,
0.20, 0.25, 0.25, 0.3, 0.3,
0.35, 0.40, 0.40, 0.6, 0.6
};
*/

static double wrapRadian( double t ){

  if( t > 0 ){
    while( t > M_PI ) t-= 2*M_PI; 
  }
  else{
    while( t < - M_PI ) t+= 2*M_PI; 
  }
  return t;
}



KF5ParamsComb::KF5ParamsComb(const Settings* settings, const uint nPar, const string &fitterName ) : L1KalmanComb(settings, nPar, fitterName ){

  hdxmin[INV2R] = -1.1e-4;
  hdxmax[INV2R] = +1.1e-4;
  hdxmin[PHI0] = -6.e-3;
  hdxmax[PHI0] = +6.e-3;
  hdxmin[Z0] = -4.1;
  hdxmax[Z0] = +4.1;
  hdxmin[T] = -6.;
  hdxmax[T] = +6.;
  hdxmin[D0] = -1.001;
  hdxmax[D0] = +1.001;

  hxmin[INV2R] = -0.3 * 0.0057;
  hxmax[INV2R] = +0.3 * 0.0057;
  hxmin[PHI0] = -0.3;
  hxmax[PHI0] = +0.3;
  hxmin[Z0] = -120;
  hxmax[Z0] = +120;
  hxmin[T] = -6.;
  hxmax[T] = +6.;
  hxmin[D0] = -3.5;
  hxmax[D0] = +3.5;

  hddMeasmin[PHI0] = -1.e1;
  hddMeasmax[PHI0] = +1.e1;

  hresmin[PHI0] = -0.5;
  hresmax[PHI0] = +0.5;

  hresmin[PHI0] = -10.;
  hresmax[PHI0] = +10.;

  hxaxtmin[INV2R] = -1.e-3;
  hxaxtmax[INV2R] = +1.e-3;
  hxaxtmin[PHI0] = -1.e-1;
  hxaxtmax[PHI0] = +1.e-1;
  hxaxtmin[Z0] = -10.;
  hxaxtmax[Z0] = +10.;
  hxaxtmin[T] = -1.e-0;
  hxaxtmax[T] = +1.e-0;
  hxaxtmin[D0] = -1.001;
  hxaxtmax[D0] = +1.001;
}


std::map<std::string, double> KF5ParamsComb::getTrackParams(const kalmanState *state )const{

  std::vector<double> x = state->xa();
  std::map<std::string, double> y;
  y["qOverPt"] = x.at(INV2R) / getSettings()->invPtToInvR() * 2.; 
  y["phi0"] = wrapRadian( x.at(PHI0) + sectorPhi() );
  y["z0"] = x.at(Z0);
  y["t"] = x.at(T);
  y["d0"] = x.at(D0);
  return y;
}

/* Get track params with beam-spot constraint & track fit chi2 from applying it. */

std::map<std::string, double> KF5ParamsComb::getTrackParams_BeamConstr( const kalmanState *state, double& chi2 ) const {
  std::map<std::string, double> y;
  std::vector<double> x = state->xa();
  TMatrixD cov_xa       = state->pxxa(); 
  double deltaChi2 = (x.at(D0) * x.at(D0)) / cov_xa[D0][D0];
  chi2 = state->chi2() + deltaChi2;
  // Apply beam-spot constraint to helix params in transverse plane only, as most sensitive to it.
  x[INV2R] -= x.at(D0) * (cov_xa[INV2R][D0] / cov_xa[D0][D0]); 
  x[PHI0 ] -= x.at(D0) * (cov_xa[PHI0 ][D0] / cov_xa[D0][D0]); 
  x[D0   ]  = 0.0;
  y["qOverPt"] = x.at(INV2R) / getSettings()->invPtToInvR() * 2.; 
  y["phi0"]    = wrapRadian( x.at(PHI0) + sectorPhi() );
  y["z0"]      = x.at(Z0);
  y["t"]       = x.at(T);
  y["d0"]      = x.at(D0);
  return y;
}

 
/* The Kalman measurement matrix = derivative of helix intercept w.r.t. helix params 
 * Here I always measure phi(r), and z(r) */
TMatrixD KF5ParamsComb::H(const StubCluster* stubCluster)const{
  TMatrixD h(2, nPar_);
  double r = stubCluster->r();
  h(PHI,INV2R) = -r;
  h(PHI,PHI0) = 1;
  h(PHI,D0) = -1./r;
  h(Z,Z0) = 1;
  h(Z,T) = r;
  return h;
}

// Not used?

TMatrixD KF5ParamsComb::dH(const StubCluster* stubCluster)const{

  double dr(0);
  if(stubCluster->layerId() > 10){
    dr = stubCluster->sigmaZ();
  }

  double r = stubCluster->r();

  TMatrixD h(2, nPar_);
  h(PHI,INV2R) = -dr;
  h(PHI,D0) = dr/(r*r);
  h(Z,T) = dr;

  return h;
}
 
/* Seed the state vector */
std::vector<double> KF5ParamsComb::seedx(const L1track3D& l1track3D)const{

  std::vector<double> x(nPar_);
  x[INV2R] = getSettings()->invPtToInvR() * l1track3D.qOverPt()/2;
  x[PHI0]  = wrapRadian( l1track3D.phi0() - sectorPhi() );
  x[Z0]    = l1track3D.z0();
  x[T]     = l1track3D.tanLambda();
  x[D0]    = 0;
    
  return x;
}

/* Seed the covariance matrix */
TMatrixD KF5ParamsComb::seedP(const L1track3D& l1track3D)const{
  TMatrixD p(nPar_,nPar_);

  double c = getSettings()->invPtToInvR() / 2; 

  // Assumed track seed (from HT) uncertainty in transverse impact parameter.
  const float d0Sigma = 1.0;

  if ( getSettings()->numEtaRegions() == 18 ) { 
      
    // optimised for 18x2 with additional error factor in pt/phi to avoid pulling towards wrong HT params
    p(INV2R,INV2R) = 0.0157 * 0.0157 * c * c * 4; 
    p(PHI0,PHI0) = 0.0051 * 0.0051 * 4; 
    p(Z0,Z0) = 5.0 * 5.0; 
    p(T,T) = 0.25 * 0.25 * 4; // IRT: increased by factor 4, as was affecting fit chi2.
    p(D0,D0) = d0Sigma * d0Sigma;  

  } else {
      
    // choose large errors
    p(INV2R,INV2R) = 0.0157 * 0.0157 * c * c * 10; 
    p(PHI0,PHI0) = 0.0051 * 0.0051 * 10; 
    p(Z0,Z0) = 5.0 * 5.0; 
    p(T,T) = 0.25 * 0.25 * 10;
    p(D0,D0) = d0Sigma * d0Sigma;  
      
  }

  return p;
}

/* The forecast matrix
 * (here equals identity matrix) */
TMatrixD KF5ParamsComb::F(const StubCluster* stubCluster, const kalmanState *state )const{
  TMatrixD F(nPar_,nPar_);
  for(unsigned int n = 0; n < nPar_; n++)
    F(n, n) = 1;
  return F;
}

/* the vector of measurements */
std::vector<double> KF5ParamsComb::d(const StubCluster* stubCluster )const{
  std::vector<double> meas;
  meas.resize(2);
  meas[PHI] = wrapRadian( stubCluster->phi() - sectorPhi() );
  meas[Z] = stubCluster->z();
  return meas;
}

// Assumed hit resolution in (phi,z)
TMatrixD KF5ParamsComb::PddMeas(const StubCluster* stubCluster, const kalmanState *state )const{

  double inv2R = (getSettings()->invPtToInvR()) * 0.5 * state->candidate().qOverPt(); // alternatively use state->xa().at(INV2R)
  double inv2R2 = inv2R * inv2R;

  double tanl = state->xa().at(T);  // factor of 0.9 improves rejection
  double tanl2 = tanl * tanl; 

  TMatrixD p(2,2);

  double vphi(0);
  double vz(0);
  double vcorr(0);

  // consider error due to integerisation only for z (r in encap) coord when enabled
  double err_digi2(0);
  if (getSettings()->enableDigitize()) err_digi2 = 0.15625 * 0.15625 / 12.0;

  double a = stubCluster->sigmaX() * stubCluster->sigmaX();
  double b = stubCluster->sigmaZ() * stubCluster->sigmaZ() + err_digi2;
  double invr2 = (1.0 / stubCluster->r()) * (1.0 / stubCluster->r());

  // Scattering term scaling as 1/Pt.
  double sigmaScat = getSettings()->kalmanMultiScattTerm()/(state->candidate().pt());
  double sigmaScat2 = sigmaScat * sigmaScat;

  if ( stubCluster->barrel() ) {

    vphi = (a * invr2) + sigmaScat2;

    if (stubCluster->tiltedBarrel()) {
      // Convert uncertainty in (r,phi) to (z,phi).
      float scaleTilted = 1.;
      if (getSettings()->kalmanHOtilted()) {
	if ( getSettings()->useApproxB() ) { // Simple firmware approximation
	  scaleTilted = getApproxB(stubCluster->z(), stubCluster->r());
	} else {                             // Exact C++ implementation. 
	  float tilt = stubCluster->moduleTilt();
	  float scaleTilted = sin(tilt) + cos(tilt)*tanl;
	}
      }
      float scaleTilted2 = scaleTilted*scaleTilted;
      // This neglects the non-radial strip effect, assumed negligeable for PS.
      vz = b * scaleTilted2;
    } else {
      vz = b;
    }

    if (getSettings()->kalmanHOdodgy()) {
      // Use original (Dec. 2016) dodgy implementation was this, with HOprojZcorr = HOalpha = 0.
      vz = b;
    }

  } else {

    double beta = 0.;
    if (not stubCluster->psModule()) {   // Neglect these terms in PS 
      // Add correlation term related to conversion of stub residuals from (r,phi) to (z,phi).
      if (getSettings()->kalmanHOprojZcorr() == 2) beta += -inv2R;
      // Add alpha correction for non-radial 2S endcap strips..
      if (getSettings()->kalmanHOalpha()     == 2) beta += -stubCluster->alpha();  // alpha is 0 except in endcap 2S disks
    }
    double beta2 = beta * beta;
    vphi = a * invr2 + b * beta2 + sigmaScat2;
    vcorr = b * (beta * tanl);

    if (getSettings()->kalmanHOdodgy()) {
      // Original buggy implementation was this, with HOprojZcorr = HOalpha = 0.
      vphi = (a * invr2) + (b * inv2R2) + sigmaScat2;
      vcorr = 0.;
    }

    vz = (b * tanl2);

  }

  p(PHI, PHI) = vphi;
  p(Z, Z) = vz;
  p(PHI, Z) = vcorr;
  p(Z, PHI) = vcorr;

  return p;

}

// State uncertainty due to scattering -- HISTORIC NOT USED
TMatrixD KF5ParamsComb::PxxModel( const kalmanState *state, const StubCluster *stubCluster )const
{

  TMatrixD p(nPar_,nPar_);

  /*
    if( getSettings()->kalmanMultiScattFactor() ){

    unsigned i_eta = abs( stubCluster->eta() / 0.1 );
    if( i_eta > 24 ) i_eta = 24;
    double dl = matx_outer[i_eta] / nlayer_eta[i_eta];

    unsigned stub_itr = state->nextLayer();

    const kalmanState * last_update_state = state->last_update_state();
    unsigned last_itr(1);
    if( last_update_state ) last_itr = last_update_state->nextLayer();
    dl = ( stub_itr - last_itr ) * dl; 

    if( dl ){
    std::map<std::string, double> y = getTrackParams( state );
    double dtheta0 = 1./sqrt(3) * 0.0136 * fabs(y["qOverPt"]) * sqrt(dl)*( 1+0.038*log(dl) ); 
    dtheta0 *= getSettings()->kalmanMultiScattFactor();
    p(PHI0, PHI0) = dtheta0 * dtheta0; // Despite the name, I think this is uncertainty in phi0. I guess uncertainty in theta0 neglected compared to detector resolution.
    }
    }
  */

  return p;
}

std::string KF5ParamsComb::getParams(){
  return "KF5ParamsComb";
}


bool KF5ParamsComb::isGoodState( const kalmanState &state )const
{

  unsigned nStubLayers = state.nStubLayers();
  bool goodState( true );

  // todo : make configurable

  // N.B. Code below changed by Alexander Morton to allow tracking down to Pt = 2 GeV.

  double pt=fabs( getSettings()->invPtToInvR() / (2*state.xa()[INV2R]) ); 
  double z0=fabs( state.xa()[Z0] ); 
std::cout << "nStubLayers "<< nStubLayers << ", pt = " << pt << ", z0 = " << z0 << ", chi2 " << state.chi2() << std::endl;
 
  // state parameter selections
  if( nStubLayers >= 2 ){
      
    if( z0 > 15. ) goodState = false;
      
    const double tolerance = (nStubLayers >= 4)  ?  0.05  :  0.1; // Loosen this for nStubLayers = 2 ???
    if( pt < getSettings()->houghMinPt() - tolerance) goodState = false;
    
    if( nStubLayers >= 3 ){      
      double d0=fabs( state.xa()[D0] ); 
      if( d0 > 10. ) goodState = false;
    }
  }

  // chi2 selections
  if (getSettings()->kalmanMultiScattTerm() < 0.0001) { // scattering ignored
    if( nStubLayers == 2 ) {
      if (state.chi2() > 15.0) goodState=false; // No separate pT selection needed
    } else if ( nStubLayers == 3 ) {
      if (state.chi2() > 100.0 && pt > 2.7) goodState=false;
      if (state.chi2() > 120.0 && pt <= 2.7) goodState=false;
    } else if ( nStubLayers >= 4 ) {  // NEEDS TUNING FOR 5 OR 6 LAYERS !!!
      if (state.chi2() > 320.0 && pt > 2.7) goodState=false;
      if (state.chi2() > 1420.0 && pt <= 2.7) goodState=false;
    }

  } else { // scattering taken into account.

    if( nStubLayers == 2 ) {
      if (state.chi2() > 10.0) goodState=false; // No separate pT selection needed
    } else if ( nStubLayers == 3 ) {  
      if (state.chi2() > 30.0) goodState=false;
    } else if ( nStubLayers == 4 ) {  
      if (state.chi2() > 80.0) goodState=false;
    } else if ( nStubLayers == 5 ) {  // NEEDS TUNING FOR 5 OR 6 LAYERS !!!
      if (state.chi2() > 120.0) goodState=false;
    } else if ( nStubLayers >= 6 ) {  // NEEDS TUNING FOR 5 OR 6 LAYERS !!!
      if (state.chi2() > 160.0) goodState=false;
    }
  }

  if ( getSettings()->kalmanDebugLevel() >= 1 ) {
    if (not goodState) cout<<"State veto: nl="<<nStubLayers<<" c2="<<state.chi2()<<" pt="<<pt<<" mc="<<tpa_->pt()<<endl; 
    if (goodState) cout<<"State kept: nl="<<nStubLayers<<" c2="<<state.chi2()<<" pt="<<pt<<" mc="<<tpa_->pt()<<endl; 
  }

  return goodState;
}

}
