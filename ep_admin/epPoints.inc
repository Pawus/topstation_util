/* version 0.1 du                                                         */
/*  dernière modification :                                               */
/*         05 03 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel Déom (sdeom@epadesa.fr)                              */


/* Liste des routines (en ordre alphabétique)                             */

/*  NetPoint(§mat) Modifie le sommet dont le matricule est donné dans     */
/*         §mat pour la faire correspondre au standard EPADESA            */
/*         dernière modification : 02 12 2012 (SD)                        */
/*  NetRad(§rad,§prc_sel_in) Supprime, pour les composants de la          */
/*         sélection, dont le radical est indiqué, l'attribut &v57:ir si  */
/*         celui-ci est également ce radical                              */
/*         dernière modification : 02 12 2012 (SD)                        */
/*  RmatIr(§sel) Réimmatricule parmi la sélection, les composants destinés*/
/*         à être re-immatriculé avec un radical de sommet foncier        */
/*         (attribut &v57:ir), puis supprime ces attributs inutiles       */
/*         dernière modification : 24 01 2012 (SD)                        */
/*  RmatRad(§rad,§prc_sel_in) Réimmatricule parmi la sélection, les       */
/*         composants destinés à être re-immatriculé avec le radical      */
/*         indiqué et dont ce n'est pas le radical                        */
/*         dernière modification : 02 12 2012 (SD)                        */
/*  SelRad(§rad,§prc_sel_in,§prc_sel_out) Sélectionne parmi une sélection */
/*         les composants destinés à être re-immatriculé avec le radical  */
/*         indiqué et les place dans la sélection spécifiée               */
/*         dernière modification : 02 12 2012 (SD)                        */

/* Procédures utiles                                                      */
proc,ProcFB=epcFB                      /* radical des composants "bornes" */
proc,ProcFC=epcFC                       /* radical des composants "clous" */
proc,ProcFG=epcFG                    /* radical des composants "gravures" */
proc,ProcFP=epcFP                     /* radical des composants "piquets" */
proc,ProcFS=epcFS            /* radical des composants "sommets arpentés" */
proc,ProcKf=epcKf           /* radical des composants "points de support" */
proc,ProcKfn=epcKfn           /* radical des composants "points nouveaux" */

/* ------------------------- DEBUT DES ROUTINES ------------------------- */

rout,RmatIr(§sel)
/* Reimmatricule parmi les composants appartenant à la sélection indiquée */
/*  dans §sel, ceux dont la rallonge &v57:ir contient un radical de       */
/*  foncier, par ce radical, puis supprime les attributs &v57:ir devenus  */
/*  inutiles                                                              */
{
  var,§int,§sel_rad
  /* on détermine les radicaux à traiter (sommets fonciers)               */
  Rad1=Kf         /* radical par défaut des composants "sommets arpentés" */
  Rad2=Kfn         /* radical par défaut des composants "points nouveaux" */
  Rad3=FB                   /* radical par défaut des composants "bornes" */
  Rad4=FC                    /* radical par défaut des composants "clous" */
  Rad5=FG                 /* radical par défaut des composants "gravures" */
  Rad6=FP                  /* radical par défaut des composants "piquets" */
  Rad7=FS         /* radical par défaut des composants "sommets arpentés" */
  /* adoption des radicaux indiqués par les procédures de radical de la   */
  /*  base si elles existent                                              */
  for,"1->§int","§int<8","§int+1->§int"
  {
	if,"defprc(Proc[Rad[§int]])"
    {
      Rad[§int]=[[Proc[Rad[§int]]]]
    }
  }
  
  /* sauvegarde de la sélection dans un domaine temporaire                */
  domi,EP_TEMP_RMATIR,[§sel]
  if,"JtDebug"
  {
    impq,`Sélection [§sel] placée dans le domaine EP_TEMP_RMATIR`
	impq,`  contenu de EP_TEMP_RMATIR :`
    rdcl,!dom(EP_TEMP_RMATIR)
  }
  /* on réimmatricule les composants, radical par radical                 */
  for,"1->§int","§int<8","§int+1->§int"
  {
    run,RmatRad([Rad[§int]],"[§sel]")
  }
  /* on supprime les attributs &v57:ir devenus inutiles                   */
  for,"1->§int","§int<8","§int+1->§int"
  {
	run,NetRad([Rad[§int]],"!dom(EP_TEMP_RMATIR)")
  }
  /* on vide le domaine temporaire                                        */
  if,"JtDebug"
  {
	impq,`Fin de RmatIr, contenu de EP_TEMP_RMATIR :`
    rdcl,!dom(EP_TEMP_RMATIR)
  }
  domo,EP_TEMP_RMATIR,!dom(EP_TEMP_RMATIR)
}

rout,SelRad(§rad,§prc_sel_in,§prc_sel_out)
/* Sélectionne parmi les composants appartenant à la sélection indiquée   */
/*  dans §prc_sel_in, ceux dont la rallonge &v57:ir contient le radical   */
/*  spécifié dans §rad et dont ce n'est radical, créé une  sélection dont */
/*  le nom sera celui contenu dans §prcl_sel_out                          */
{
  /* verification que §prc_sel_out est un nom de sélection valide         */
  /* vérification que §prc_sel_in correspond à une sélection valide       */
  [§prc_sel_out]=([§prc_sel_in])*!test(&v57:ir==[§rad])*~[§rad]
}

rout,RmatRad(§rad,§prc_sel_in)
/* Réimmatricule parmi les composants appartenant à la sélection          */
/*  indiquée dans §prc_sel_in, ceux dont la rallonge &v57:ir contient le  */
/*  radical spécifié dans §rad et dont ce n'est radical, en leur          */
/*  attribuant ce radical                                                 */
{
  run,SelRad([§rad],"[§prc_sel_in]",!EpTemp)
  rmat,!EpTemp,[§rad]
  !sele,!EpTemp
}

rout,NetRad(§rad,§prc_sel_in)
/* Supprime l'attribut &v57:ir des composants appartenant à la sélection  */
/*  indiquée dans §prc_sel_in, de radical §rad et dont l'attribut &v57:ir */
/*  est également ce radical                                              */
{
  !EpTemp=([§prc_sel_in])*!test(&v57:ir==[§rad])*[§rad]
  runs,!EpTemp
  {
    ral,[mm]&v57:ir=
  }
  !sele,!EpTemp
}

rout,NetPoint(§mat)
/* Modifie le sommet dont le matricule est donné dans la procédure §mat   */
/*   pour la faire correspondre au standard EPADESA                       */
{
  !cmpe,[§mat],D
  [§mat]:Md=EP_PNT_PARCELLE
  ral,[§mat]&T1:Idp=""
}