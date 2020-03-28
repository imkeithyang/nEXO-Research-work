void AnalyzeTotalEnergy()
{
   FILE *fp;
   fp=fopen("/Users/Tiger/nexo_py/txt/bb2n_TotalEnergy.txt", "ab+");
   if(fp == NULL) exit(-1);
   TFile *f = new TFile("/Users/Tiger/nexo_py/Data 0vbb/bb2n/bb2n_seed_10.root");
   if (f == 0) {
      printf("Error: cannot open http://lcg-heppkg.web.cern.ch/lcg-heppkg/ROOT/eventdata.root!\n");
      return;
   }
   
   TDirectory* D1; TDirectory* D2; TTree* tree; //Declare Needed Variable
   f->GetObject("Event", D1); D1->GetObject("Sim", D2); D2->GetObject("SimEvent", tree);


   TBranchElement* branch = (TBranchElement*) tree->GetBranch("fTotalEventEnergy"); //Get Needed Branch
   Long64_t numberevents = tree->GetEntries();
   
   // Loop through Branch to write each entry to txt File
   for (Long64_t i=0;i<numberevents;i++){
     tree -> GetEntry(i);
     fprintf(fp,"%f\n",(float)branch->GetValue(i, 0)); //write in txt File
   }
   fprintf(stderr,"Total Energy get to end \n");
   fprintf(stderr,"Total Number of Events: %lld\n",numberevents);
   fclose(fp);

   return 0;
}
void AnalyzeGen()
{
   //FILE *fp;
   //fp=fopen("/Users/Tiger/nexo_py/txt/bb2n_TotalEnergy.txt", "ab+");
   //if(fp == NULL) exit(-1);
   TFile *f = new TFile("/Users/Tiger/nexo_py/Data 0vbb/bb2n/bb2n_seed_2.root");
   if (f == 0) {
      printf("Error: cannot open http://lcg-heppkg.web.cern.ch/lcg-heppkg/ROOT/eventdata.root!\n");
      return;
   }
   
   TDirectory* D1; TDirectory* D2; TTree* tree; //Declare Needed Variable
   f->GetObject("Event", D1); D1->GetObject("Sim", D2); D2->GetObject("SimEvent", tree);


   TBranchElement* branch = (TBranchElement*) tree->GetBranch("fGenZ"); //Get Needed Branch
   Long64_t numberevents = tree->GetEntries();
   float max = 200;
   float min = -1000;
   float halfz = 0;
   
   // Loop through Branch to write each entry to txt File
   for (Long64_t i=0;i<numberevents;i++){
     tree -> GetEntry(i);
     //fprintf(fp,"%f\n",(float)branch->GetValue(i, 0));
     if ((float)branch->GetValue(i, 0) > max) max = branch->GetValue(i, 0);
     if ((float)branch->GetValue(i, 0) < min) min = branch->GetValue(i, 0);//write in txt File
   }
   halfz = (max - min)/2;
   fprintf(stderr,"Total Energy get to end \n");
   fprintf(stderr,"Total Number of Events: %lld\n",numberevents);
   fprintf(stderr,"max %f\n", max);
   fprintf(stderr,"min %f\n", min);
   fprintf(stderr,"halfz %f\n", halfz);
   //fclose(fp);

   return 0;
}