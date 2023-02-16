
Int_t AddGoodRuns(AliAnalysisAlien* plugin,TString lhcPeriod,TString mcprod="") {
  //
  // Adds good runs from the Monalisa Run Condition Table
  //
  if(mcprod=="") plugin->SetRunPrefix("000"); // DATA
  
  Int_t firstrun=0,lastrun=9999999;
  Int_t nruns=0,ngoodruns=0;
  
  
  if(lhcPeriod=="LHC15o_Gir") {
    if(mcprod=="") {
      nruns= 1;
      Int_t runlist[15] ={246766, 246945, 246928, 246846, 246845, 246844, 246810, 246809, 246808, 246807, 246805, 246804, 246765, 246760, 246759};
      for(Int_t k=0;k<nruns;k++){
	if(runlist[k]<firstrun || runlist[k]>lastrun) continue;
	plugin->AddRunNumber(runlist[k]);
	ngoodruns++;
      }
    }
    plugin->SetNrunsPerMaster(ngoodruns);
  }
    
    if(lhcPeriod=="LHC18r_Gir") {
      if(mcprod=="") {
        nruns= 1;
        Int_t runlist[] ={}; // add good runs for the 18r you want to run
        for(Int_t k=0;k<nruns;k++){
      if(runlist[k]<firstrun || runlist[k]>lastrun) continue;
      plugin->AddRunNumber(runlist[k]);
      ngoodruns++;
        }
      }
      plugin->SetNrunsPerMaster(ngoodruns);
    }
    
    if(lhcPeriod=="LHC18q_Gir") {
      if(mcprod=="") {
        nruns= 1;
        Int_t runlist[] ={}; // add good runs for the 18q you want to run
        for(Int_t k=0;k<nruns;k++){
      if(runlist[k]<firstrun || runlist[k]>lastrun) continue;
      plugin->AddRunNumber(runlist[k]);
      ngoodruns++;
        }
      }
      plugin->SetNrunsPerMaster(ngoodruns);
    }


return ngoodruns;
}
