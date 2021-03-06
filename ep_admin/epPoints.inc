/* version 0.1 du                                                         */
/*  derni�re modification :                                               */
/*         05 03 2013 (SD)                                                */
/*  auteur :                                                              */
/*         SD Samuel D�om (sdeom@epadesa.fr)                              */


/* Liste des routines (en ordre alphab�tique)                             */

/*  NetPoint(�mat) Modifie le sommet dont le matricule est donn� dans     */
/*         �mat pour la faire correspondre au standard EPADESA            */
/*         derni�re modification : 02 12 2012 (SD)                        */
/*  NetRad(�rad,�prc_sel_in) Supprime, pour les composants de la          */
/*         s�lection, dont le radical est indiqu�, l'attribut &v57:ir si  */
/*         celui-ci est �galement ce radical                              */
/*         derni�re modification : 02 12 2012 (SD)                        */
/*  RmatIr(�sel) R�immatricule parmi la s�lection, les composants destin�s*/
/*         � �tre re-immatricul� avec un radical de sommet foncier        */
/*         (attribut &v57:ir), puis supprime ces attributs inutiles       */
/*         derni�re modification : 24 01 2012 (SD)                        */
/*  RmatRad(�rad,�prc_sel_in) R�immatricule parmi la s�lection, les       */
/*         composants destin�s � �tre re-immatricul� avec le radical      */
/*         indiqu� et dont ce n'est pas le radical                        */
/*         derni�re modification : 02 12 2012 (SD)                        */
/*  SelRad(�rad,�prc_sel_in,�prc_sel_out) S�lectionne parmi une s�lection */
/*         les composants destin�s � �tre re-immatricul� avec le radical  */
/*         indiqu� et les place dans la s�lection sp�cifi�e               */
/*         derni�re modification : 02 12 2012 (SD)                        */

/* Proc�dures utiles                                                      */
proc,ProcFB=epcFB                      /* radical des composants "bornes" */
proc,ProcFC=epcFC                       /* radical des composants "clous" */
proc,ProcFG=epcFG                    /* radical des composants "gravures" */
proc,ProcFP=epcFP                     /* radical des composants "piquets" */
proc,ProcFS=epcFS            /* radical des composants "sommets arpent�s" */
proc,ProcKf=epcKf           /* radical des composants "points de support" */
proc,ProcKfn=epcKfn           /* radical des composants "points nouveaux" */

/* ------------------------- DEBUT DES ROUTINES ------------------------- */

rout,RmatIr(�sel)
/* Reimmatricule parmi les composants appartenant � la s�lection indiqu�e */
/*  dans �sel, ceux dont la rallonge &v57:ir contient un radical de       */
/*  foncier, par ce radical, puis supprime les attributs &v57:ir devenus  */
/*  inutiles                                                              */
{
  var,�int,�sel_rad
  /* on d�termine les radicaux � traiter (sommets fonciers)               */
  Rad1=Kf         /* radical par d�faut des composants "sommets arpent�s" */
  Rad2=Kfn         /* radical par d�faut des composants "points nouveaux" */
  Rad3=FB                   /* radical par d�faut des composants "bornes" */
  Rad4=FC                    /* radical par d�faut des composants "clous" */
  Rad5=FG                 /* radical par d�faut des composants "gravures" */
  Rad6=FP                  /* radical par d�faut des composants "piquets" */
  Rad7=FS         /* radical par d�faut des composants "sommets arpent�s" */
  /* adoption des radicaux indiqu�s par les proc�dures de radical de la   */
  /*  base si elles existent                                              */
  for,"1->�int","�int<8","�int+1->�int"
  {
	if,"defprc(Proc[Rad[�int]])"
    {
      Rad[�int]=[[Proc[Rad[�int]]]]
    }
  }
  
  /* sauvegarde de la s�lection dans un domaine temporaire                */
  domi,EP_TEMP_RMATIR,[�sel]
  if,"JtDebug"
  {
    impq,`S�lection [�sel] plac�e dans le domaine EP_TEMP_RMATIR`
	impq,`  contenu de EP_TEMP_RMATIR :`
    rdcl,!dom(EP_TEMP_RMATIR)
  }
  /* on r�immatricule les composants, radical par radical                 */
  for,"1->�int","�int<8","�int+1->�int"
  {
    run,RmatRad([Rad[�int]],"[�sel]")
  }
  /* on supprime les attributs &v57:ir devenus inutiles                   */
  for,"1->�int","�int<8","�int+1->�int"
  {
	run,NetRad([Rad[�int]],"!dom(EP_TEMP_RMATIR)")
  }
  /* on vide le domaine temporaire                                        */
  if,"JtDebug"
  {
	impq,`Fin de RmatIr, contenu de EP_TEMP_RMATIR :`
    rdcl,!dom(EP_TEMP_RMATIR)
  }
  domo,EP_TEMP_RMATIR,!dom(EP_TEMP_RMATIR)
}

rout,SelRad(�rad,�prc_sel_in,�prc_sel_out)
/* S�lectionne parmi les composants appartenant � la s�lection indiqu�e   */
/*  dans �prc_sel_in, ceux dont la rallonge &v57:ir contient le radical   */
/*  sp�cifi� dans �rad et dont ce n'est radical, cr�� une  s�lection dont */
/*  le nom sera celui contenu dans �prcl_sel_out                          */
{
  /* verification que �prc_sel_out est un nom de s�lection valide         */
  /* v�rification que �prc_sel_in correspond � une s�lection valide       */
  [�prc_sel_out]=([�prc_sel_in])*!test(&v57:ir==[�rad])*~[�rad]
}

rout,RmatRad(�rad,�prc_sel_in)
/* R�immatricule parmi les composants appartenant � la s�lection          */
/*  indiqu�e dans �prc_sel_in, ceux dont la rallonge &v57:ir contient le  */
/*  radical sp�cifi� dans �rad et dont ce n'est radical, en leur          */
/*  attribuant ce radical                                                 */
{
  run,SelRad([�rad],"[�prc_sel_in]",!EpTemp)
  rmat,!EpTemp,[�rad]
  !sele,!EpTemp
}

rout,NetRad(�rad,�prc_sel_in)
/* Supprime l'attribut &v57:ir des composants appartenant � la s�lection  */
/*  indiqu�e dans �prc_sel_in, de radical �rad et dont l'attribut &v57:ir */
/*  est �galement ce radical                                              */
{
  !EpTemp=([�prc_sel_in])*!test(&v57:ir==[�rad])*[�rad]
  runs,!EpTemp
  {
    ral,[mm]&v57:ir=
  }
  !sele,!EpTemp
}

rout,NetPoint(�mat)
/* Modifie le sommet dont le matricule est donn� dans la proc�dure �mat   */
/*   pour la faire correspondre au standard EPADESA                       */
{
  !cmpe,[�mat],D
  [�mat]:Md=EP_PNT_PARCELLE
  ral,[�mat]&T1:Idp=""
}