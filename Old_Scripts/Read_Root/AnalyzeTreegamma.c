void AnalyzeTreegamma()
{
   FILE *fpx; FILE *fpy; FILE *fpz; FILE *fpE; FILE *fpTe;
   fpx=fopen("/Users/Tiger/nexo_py/txt/gamma_x.txt", "ab+");
   fpy=fopen("/Users/Tiger/nexo_py/txt/gamma_y.txt", "ab+");
   fpz=fopen("/Users/Tiger/nexo_py/txt/gamma_z.txt", "ab+");
   fpE=fopen("/Users/Tiger/nexo_py/txt/gamma_EnergyDeposit.txt", "ab+");
   fpTe=fopen("/Users/Tiger/nexo_py/txt/gamma_TotalEnergy.txt", "ab+");
   if(fpx == NULL) exit(-1);
   TFile *f = new TFile("/Users/Tiger/nexo_py/Data/gamma/gamma_seed_4.root");
   if (f == 0) {
      printf("Error: cannot open http://lcg-heppkg.web.cern.ch/lcg-heppkg/ROOT/eventdata.root!\n");
      return;
   }
   
   TDirectory* D1; TDirectory* D2; TTree* tree; //Declare Needed Variable
   f->GetObject("Event", D1); D1->GetObject("Sim", D2); D2->GetObject("SimEvent", tree);

   TBranchElement* branchE = (TBranchElement*) tree->GetBranch("fEnergyDeposit"); 
   TBranchElement* branchx = (TBranchElement*) tree->GetBranch("fXpos"); 
   TBranchElement* branchy = (TBranchElement*) tree->GetBranch("fYpos");
   TBranchElement* branchz = (TBranchElement*) tree->GetBranch("fZpos");
   TBranchElement* branchTot = (TBranchElement*) tree->GetBranch("fTotalEventEnergy");

   Long64_t numberevents = tree->GetEntries();
   UInt_t max = 0;
   int total = 0;
   // Loop through Branch to write each entry to txt File
   for (Long64_t i=0;i<numberevents;i++){
     tree -> GetEntry(i);
     if (branchTot->GetValue(i, 0) < 2) {continue;}
     fprintf(fpTe, "%f\n", branchTot->GetValue(i, 0));
      for(UInt_t j=0;j< 15000;j++){
        if ((branchx->GetValue(j, 0) == 0 && branchx->GetValue(j+1, 0) == 0)
             && (branchy->GetValue(j, 0) == 0 && branchy->GetValue(j+1, 0) == 0)
             && (branchz->GetValue(j, 0) == 0 && branchz->GetValue(j+1, 0) == 0)) {
          if (j > max) max = j;
          total += j;
          break;
        }
        fprintf(fpE,"%f\n",branchE->GetValue(j, 0));
        fprintf(fpx,"%f\n",branchx->GetValue(j, 0));
        fprintf(fpy,"%f\n",branchy->GetValue(j, 0));
        fprintf(fpz,"%f\n",branchz->GetValue(j, 0));
        if (((branchE->GetValue(j+1, 0) < 0.000005) && (branchE->GetValue(j+2, 0) < 0.000005))) {
          if ((branchx->GetValue(j+1, 0) - branchx->GetValue(j+2, 0) > 10 || branchx->GetValue(j+1, 0) - branchx->GetValue(j+2, 0) < -10) 
            || (branchy->GetValue(j+1, 0) - branchy->GetValue(j+2, 0) > 10 || branchy->GetValue(j+1, 0) - branchy->GetValue(j+2, 0) < -10) 
            || (branchz->GetValue(j+1, 0) - branchz->GetValue(j+2, 0) > 10 || branchz->GetValue(j+1, 0) - branchz->GetValue(j+2, 0) < -10)) {
          float totx = 0;
          float toty = 0;
          float totz = 0;
          for (int k = 2; k < 7; k++){
            totx += (branchx->GetValue(j+k,0) - branchx->GetValue(j+k+1, 0));
            toty += (branchy->GetValue(j+k,0) - branchy->GetValue(j+k+1, 0));
            totz += (branchz->GetValue(j+k,0) - branchz->GetValue(j+k+1, 0));
          }
          if ((totx > 50 || totx < -50)
            || (toty > 50 || toty < -50)
            || (totz > 50 || totz < -50)) {
            //fprintf(stderr, "%f\n", totx);
          //fprintf(stderr, "%f\n", toty);
          //fprintf(stderr, "%f\n", totz);
          break;
        }
      }
        }
      }
      fprintf(fpE,"%s\n","seprate"); 
      fprintf(fpx,"%s\n","seprate");
      fprintf(fpy,"%s\n","seprate"); 
      fprintf(fpz,"%s\n","seprate");
   }
   fprintf(stderr,"x get to end: %u\n", max);
   fprintf(stderr,"Total Number of Events: %lld\n",numberevents);
   fprintf(stderr,"Total Entry in fXpos: %u\n", total);
   fprintf(stderr,"Change seed, current seed 4. \n"); 

   fclose(fpx);
   fclose(fpy);
   fclose(fpz);
   fclose(fpE);
   fclose(fpTe);

   return 0;
}
