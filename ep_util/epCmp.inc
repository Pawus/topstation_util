/*  derni�re modification :                                               */
/*         13 01 2016 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel D�om (sdeom@epadesa.fr)                              */

/* Pour fonctionner il faut inclure pr�alablement les boites � outils :   */
/*  pas de boite � outils                                                 */

/* Liste des routines                                                     */


/* Proc�dures utiles                                                      */

/* Sommets                                                                */
proc,ProcFB=epcFB                      /* radical des composants "bornes" */
proc,ProcFC=epcFC                       /* radical des composants "clous" */
proc,ProcFG=epcFG                    /* radical des composants "gravures" */
proc,ProcFP=epcFP                     /* radical des composants "piquets" */
proc,ProcFS=epcFS            /* radical des composants "sommets arpent�s" */
proc,ProcKf=epcKf           /* radical des composants "points de support" */
proc,ProcKfn=epcKfn           /* radical des composants "points nouveaux" */

/* Parcellaire                                                            */
proc,ProcPaf=hbcPaf         /* radical des composants "Parcelle fonci�re" */
proc,ProcFPO=hbcFPO/* radical des composants "Parcelle fonci�re ancienne" */
proc,ProcF=hbcF       /* radical des composants "Parcelle projet�e (lot)" */
proc,ProcFL=hbcFL             /* radical des composants "Limite fonci�re" */
proc,ProcFLP=hbcFLP  /* radical des composants "Limite fonci�re projet�e" */

/* Volum�trie                                                             */
proc,ProcFCD=hbcFCD           /* radical des composants "Coupe de volume" */
proc,ProcFCO=hbcFCO  /* radical des composants "Coupe de volume ancienne" */
proc,ProcFCL=hbcFCL /* radical des composants "Limite de coupe de volume" */
proc,ProcFED=hbcFED             /* radical des composants "EDD en volume" */
proc,ProcFEO=hbcFEO      /* radical des composants "EDD en volume ancien" */
proc,ProcFEd=hbcFEd  /* radical des composants "EDD en volume en attente" */
proc,ProcFep=hbcFep    /* radical des composants "Projet d'EDD en volume" */
proc,ProcFLD=hbcFLD                    /* radical des composants "Volume" */
proc,ProcFLO=hbcFLO             /* radical des composants "Volume ancien" */
proc,ProcFXV=hbcFXV           /* radical des composants "Texte de volume" */
proc,ProcNiv=epcNiv                    /* radical des composants "Niveau" */

/* ------------------------- DEBUT DES ROUTINES ------------------------- */
