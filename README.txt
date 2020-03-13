Ιωάννης Δαλιάνης


Τα δεδομένα για τα diseaseRecords των ασθενών αποθηκεύονται μία μόνο φορά στη μνήμη.
Χρησιμοποιείται μια Απλά Συνδεδεμένη Λίστα για να κρατάει τους αρχικούς δείκτες προς
τα diseaseRecords η οποία δε μεταβάλλεται καθόλου μέχρι το τέλος της εκτέλεσης του προγράμματος.
Οι άλλες δομές αποθηκεύουν πάλι μόνο δείκτες στα diseaseRecords και όταν αυτές σβήνονται,
δε πειράζουν καθόλου τα diseaseRecords. Τα diseaseRecords σβήνονται μόνο στο τέλος που αδειάζει
η Απλά Συνδεδεμένη Λίστα.

Παραδοχές:
Έστω ότι οι τιμές βάσει των οποίων εισάγονται και κατανέμονται νέοι κόμβοι στο AVL Δέντρο
ονομάζονται AVL κλειδιά.
Τα AVL κλειδιά που έχουν τιμή ίση με αυτή του τρέχοντος AVL κόμβου κατανέμονται προς τα
δεξιά παιδιά του, μαζί δηλαδή με
τους AVL κόμβους που έχουν μεγαλύτερες τιμές AVL κλειδιών από αυτόν.

Η συνάρτηση για τα AVL performRotations ελέγχει αν μετά από μία εισαγωγή στο δέντρο απαιτείται
κάποιο rotation. Για ένα κόμβο existent ελέγχεται πρώτα για rotation το δεξί του υπόδεντρο και
έπειτα το αριστερό. Οι έλεγχοι που γίνονται με τις μεταβλητές balance, newcompare,
does_it_have_at_least_one_not_NULL_child εξασφαλίζουν ότι για να γίνει rotation στο
subtree ενός κόμβου πρέπει και το balance factor να έχει τιμή μικρότερη του -1 ή μεγαλύτερη του 1
και ο καινούριος κόμβος added να έχει εισαχθεί στο υπόδεντρο που ελέγχουμε αλλά και το child node του
κόμβου existent να έχει τουλάχιστον ένα παιδί. Αν δεν έχει σημαίνει ότι το child node του existent
είναι αυτό που μόλις εισήχθη, οπότε δεν γίνεται κάποιο rotation στο συγκεκριμένο υπόδεντρο.

Είναι πιθανό τα rotations στην υλοποίησή μου να τα έχω ονομάσει αντίθετα σε σχέση με την πλειονότητα
των παραδειγμάτων που υπάρχουν στο ίντερνετ, π.χ. LL αντί για RR κ.λ.π.

Η συνάρτηση get_child_nodes επιστρέφει το πλήθος child ενός κόμβου του AVL. Υλοποιήθηκε για κάποιες
δοκιμές αλλά δε χρησιμοποιείται για την εργασία.













91 Nikolakis Stokos MERS-COV China 28-05-2008 25-08-2008
67 Richard Williams COVID-2019 France 02-02-2003 01-06-2013
28 Crystal Stokes FLU-2018 Switzerland 26-03-2005 18-07-2019
36 Paris Pakis SARS-1 Uganda 07-09-2008 10-12-2007
40 Dylan Webb SARS-1 Australia 15-06-2000 05-01-2015
4 Makis Makakis MERS-COV Australia 03-07-2006 16-02-2006
84 Julie Martin SARS-COV-2 Australia 10-07-2008 15-12-2016
78 Timothy Prince FLU-2018 Germany 11-09-2001 10-12-2013
91 Jasmin Gomez MERS-COV China 28-05-2008 25-08-2008
23 Tanya Huang SARS-1 USA 07-09-2006 10-12-2007
33 Daniel Olsen H1N1 Italy 20-11-2003 31-08-2011
46 Whitney Taylor COVID-2019 Switzerland 12-08-2007 15-09-2012
1 Andrea Rosario EVD Vietnam 06-09-2002 22-01-2012
50 Kathryn Todd FLU-2018 Germany 15-02-2000 07-09-2015
52 Amanda Osborn SARS-COV-2 France 08-12-2005 -
80 Maurice Mason MERS-COV Egypt 10-06-2010 13-11-2019
88 Scott Brown H1N1 France 25-04-2003 07-06-2019
1 Giannis Kostas EVD Vietnam 06-09-2002 22-01-2012
86 Mike Bazovski MERS-COV Egypt 10-06-2010 13-06-2010
33 Paris Pakis SARS-1 USA 11-12-2007 10-12-2007
8220 Phillip Luna MERS-COV Switzerland 06-03-2005 29-05-2005
296 Rebecca Holden FLU-2018 Switzerland 03-08-2012 10-10-2015
5012 Joseph Jones EVD Denmark 15-11-2005 02-08-2008
6017 Lauren Hamilton COVID-2019 France 18-05-2012 31-12-2012
143 Donald James SARS-1 Greece 03-03-2001 17-09-2003
6005 Glenda Miller FLU-2018 Argentina 22-08-2014 -
5007 Robert Stanley H1N1 Egypt 10-03-2003 28-07-2014
3013 Paul Oneill COVID-2019 Argentina 27-02-2005 23-09-2015
8748 Sheila Brown SARS-COV-2 France 06-12-2001 15-09-2018
2163 Amber Johnson EVD Denmark 12-09-2007 15-04-2017
4303 Emily Lucas MERS-COV Denmark 07-10-2000 01-09-2004
3478 Bradley Gomez MERS-COV Russia 07-10-2010 13-05-2011








ΤΟ ΤΕΛΙΚΟ ΜΟΥ ΘΑ ΕΙΝΑΙ ΤΟ AVL
ΟΤΙ ΚΑΙΝΟΥΡΙΟ ΓΡΑΦΩ ΤΟ ΓΡΑΦΩ ΣΤΟ AVL ΤΟ ΠΕΡΝΩ ΣΤΟ FINAL ΚΑΙ ΜΕΤΑ ΤΟ
ΔΟΚΙΜΑΖΩ ΚΑΙ ΜΕΤΑ ΤΟ ΑΦΗΝΩ ΣΤΟ AVL