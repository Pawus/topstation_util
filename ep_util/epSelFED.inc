/*  dernière modification :                                               */
/*         13 01 2016 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel Déom (sdeom@epadesa.fr)                              */

/* Pour fonctionner il faut inclure préalablement les boites à outils :   */
/*  epCmp (dans ep_util)                                                  */

/* Liste des routines                                                     */
/*  SelFED(§fed) Sélectionner l'ensemble des composants nécessaires à un  */
/*  état descriptif de division en volumes                                */
/*        Dernière modification : 13/01/2016                              */

/* Procédures utiles                                                      */
/*  pas de procédures particulières                                       */

/* ------------------------- DEBUT DES ROUTINES ------------------------- */

rout,SelFED(§fed,§prc_sel)
/*  Cette routine sélectionne l'ensemble des composants qui forment       */
/*      l'état descriptif de division en volumes dont le matricule est    */
/*      contenu dans la procédure §fed et les ajoute à la sélection dont  */
/*      le nom est contenu dans la procédure dont le nom est donné par    */
/*      contenu dans la procédure §fed et les ajoute à la sélection dont  */
/*  Dernière modification : 13 01 2016 (SD)                               */
{
  var,§dom
  
  !SelFed_temp=0
  
  !SelOnc_temp=!onc([§fed])
  !SelFed_temp<!SelOnc_temp*[[ProcFCD]]
  !SelFed_temp<!SelOnc_temp*[[ProcFCO]]
  !SelFed_temp<!SelOnc_temp*[[ProcFCL]]
  !SelFed_temp<!SelOnc_temp*[[ProcFED]]
  !SelFed_temp<!SelOnc_temp*[[ProcFEO]]
  !SelFed_temp<!SelOnc_temp*[[ProcFEd]]
  !SelFed_temp<!SelOnc_temp*[[ProcFep]]
  !SelFed_temp<!SelOnc_temp*[[ProcFLD]]
  !SelFed_temp<!SelOnc_temp*[[ProcFLO]]
  !SelFed_temp<!SelOnc_temp*[[ProcFXV]]
  !SelFed_temp<!SelOnc_temp*[[ProcNiv]]
  
  !SelUtil_temp=!util(!SelFed_temp)
  !SelFed_temp<!SelUtil_temp*[[ProcFB]]
  !SelFed_temp<!SelUtil_temp*[[ProcFC]]
  !SelFed_temp<!SelUtil_temp*[[ProcFG]]
  !SelFed_temp<!SelUtil_temp*[[ProcFP]]
  !SelFed_temp<!SelUtil_temp*[[ProcFS]]
  !SelFed_temp<!SelUtil_temp*[[ProcKf]]
  !SelFed_temp<!SelUtil_temp*[[ProcKfn]]

  /* on récupère ce qui figure sur les plans de niveaux (Dimg etc..)      */
  runs,!SelFed_temp*[[ProcNiv]] /* on parcours les niveaux                */
  {
    runr,[mm],D /* nous faisons l'hypothése qu'il n'y a qu'un domaine */
    {
      §dom=[[rr]:]
      !SelFed_temp<!util(!dom([§dom]))
    }
  }
  
  [[§prc_sel]]<!SelFed_temp
  
  !sele,!SelFed_temp
  !sele,!SelOnc_temp
  !sele,!SelUtil_temp
}