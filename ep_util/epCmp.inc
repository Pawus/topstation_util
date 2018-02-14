/*  dernière modification :                                               */
/*         13 01 2016 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel Déom (sdeom@epadesa.fr)                              */

/* Pour fonctionner il faut inclure préalablement les boites à outils :   */
/*  pas de boite à outils                                                 */

/* Liste des routines                                                     */


/* Procédures utiles                                                      */

/* Sommets                                                                */
proc,ProcFB=epcFB                      /* radical des composants "bornes" */
proc,ProcFC=epcFC                       /* radical des composants "clous" */
proc,ProcFG=epcFG                    /* radical des composants "gravures" */
proc,ProcFP=epcFP                     /* radical des composants "piquets" */
proc,ProcFS=epcFS            /* radical des composants "sommets arpentés" */
proc,ProcKf=epcKf           /* radical des composants "points de support" */
proc,ProcKfn=epcKfn           /* radical des composants "points nouveaux" */

/* Parcellaire                                                            */
proc,ProcPaf=hbcPaf         /* radical des composants "Parcelle foncière" */
proc,ProcFPO=hbcFPO/* radical des composants "Parcelle foncière ancienne" */
proc,ProcF=hbcF       /* radical des composants "Parcelle projetée (lot)" */
proc,ProcFL=hbcFL             /* radical des composants "Limite foncière" */
proc,ProcFLP=hbcFLP  /* radical des composants "Limite foncière projetée" */

/* Volumétrie                                                             */
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
