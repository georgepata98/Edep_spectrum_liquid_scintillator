{
    TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
    TH1F *combinedHisto = nullptr;

    int num;
    string rootFileName, histoName;

    cout << "\nFisierele root trebuie sa fie in acelasi folder cu acest program !" << endl;
    cout << "Nr. de fisiere root: "; cin >> num;
    cout << "Numele fisierelor root (fara extensie si fara a specifica ID-ul Run-ului): "; cin >> rootFileName;
    cout << "Numele histogramelor din fisierele root: "; cin >> histoName;
    cout << "\n!!! ATENTIE: trebuie sa fie doar 1 histograma per fisier root !!!" << endl << endl;


    // Loop pe toate fisierele root cu cate 1 histograma fiecare
    // Se incarca histograma totala in combinedHisto
    for(int i=0; i<num; ++i)
    {
        TFile *files = TFile::Open((rootFileName + std::to_string(i) + ".root").c_str());
        if(!files) { return 1; }

        TH1F *histograms = (TH1F*)files->Get(histoName.c_str());  //numele histogramelor din fiecare fisier root
        if(!histograms)
        {
            cout << "\nEROARE: Nu s-a gasit histograma " << histoName << endl;
            return 1;
        }
        else { histograms->Print(); }  //printeaza info generale din histograma curenta

        if(!combinedHisto)
        {
            combinedHisto = (TH1F*)histograms->Clone("combinedHisto");
            combinedHisto->SetDirectory(0);
        }
        else { combinedHisto->Add(histograms); }

        files->Close();
    }

    

    // Crearea unui fisier root cu histograma combinedHisto
    if(combinedHisto)
    {
        TFile outputFile("combinedOutput.root", "RECREATE");
        combinedHisto->Write();
        outputFile.Close();
    }

    string energy;
    cout << "\nEnergia fotonilor incidenti pentru care s-a realizat histograma, in keV: "; cin >> energy;

    combinedHisto->SetTitle(("Spectrul energiei depozitate de fotonii cu " + energy + " keV in LS").c_str());
    combinedHisto->GetXaxis()->SetTitle("Energy [keV]");
    combinedHisto->GetYaxis()->SetTitle("Counts");
    combinedHisto->Draw();
    c1->Update();


    return 0;
}